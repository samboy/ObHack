#ifndef __LZSS_IO_COMPRESSION_H__
#define __LZSS_IO_COMPRESSION_H_

#ifdef __cplusplus
extern          "C" {
#endif

#ifdef WIN32
#	define LZSSEXPORT __stdcall
#elif defined(UNIX)
#	define LZSSEXPORT
#endif

#ifndef EOF
#define EOF    (-1)
#endif

#define F_READ          "r"		   /* for use with pack_fopen() */
#define F_WRITE         "w"
#define F_READ_PACKED   "rp"
#define F_WRITE_PACKED  "wp"
#define F_WRITE_NOPACK  "w!"

#define F_BUF_SIZE      4096	   /* 4K buffer for caching data */
#define F_PACK_MAGIC    0x736C6821L	/* magic number for packed files */
#define F_NOPACK_MAGIC  0x736C682EL	/* magic number for autodetect */
#define F_EXE_MAGIC     0x736C682BL	/* magic number for appended data */

#define LZFILE_FLAG_WRITE   1	   /* the file is being written */
#define LZFILE_FLAG_PACK    2	   /* data is compressed */
#define LZFILE_FLAG_CHUNK   4	   /* file is a sub-chunk */
#define LZFILE_FLAG_EOF     8	   /* reached the end-of-file */
#define LZFILE_FLAG_ERROR   16	   /* an error has occurred */

	typedef struct LZFILE_s {
		int             hndl;	   /* file handle */
		int             flags;	   /* LZFILE_FLAG_* constants */
		unsigned char  *buf_pos;   /* position in buffer */
		int             buf_size;  /* number of bytes in the buffer */
		long            todo;	   /* number of bytes still on the disk */
		struct LZFILE_s *parent;   /* nested, parent file */
		void           *pack_data; /* for LZSS compression */
		char           *filename;  /* name of the file */
		char           *password;  /* current encryption position */
		unsigned char   buf[F_BUF_SIZE];	/* the actual data buffer */
	} LZFILE;

#define lzEOF(f)       ((f)->flags & LZFILE_FLAG_EOF)
#define lzError(f)     ((f)->flags & LZFILE_FLAG_ERROR)

	void LZSSEXPORT lzPassword(char *password);
	LZFILE         *LZSSEXPORT lzOpen(char *filename, char *mode);
	int LZSSEXPORT  lzClose(LZFILE * f);
	LZFILE         *LZSSEXPORT lzOpenChunk(LZFILE * f, int pack);
	LZFILE         *LZSSEXPORT lzCloseChunk(LZFILE * f);
	int LZSSEXPORT  lzSeek(LZFILE * f, int offset);
	int LZSSEXPORT  lzGetW(LZFILE * f);
	long LZSSEXPORT lzGetL(LZFILE * f);
	int LZSSEXPORT  lzPutW(int w, LZFILE * f);
	long LZSSEXPORT lzPutL(long l, LZFILE * f);
	int LZSSEXPORT  lzGetWm(LZFILE * f);
	long LZSSEXPORT lzGetLm(LZFILE * f);
	int LZSSEXPORT  lzPutWm(int w, LZFILE * f);
	long LZSSEXPORT lzPutLm(long l, LZFILE * f);
	long LZSSEXPORT lzRead(void *p, long n, LZFILE * f);
	long LZSSEXPORT lzWrite(void *p, long n, LZFILE * f);
	char           *LZSSEXPORT lzGetS(char *p, int max, LZFILE * f);
	int LZSSEXPORT  lzPutS(char *p, LZFILE * f);
	int LZSSEXPORT  lzGetC(LZFILE * f);
	int LZSSEXPORT  lzPutC(int c, LZFILE * f);

#ifdef __cplusplus
}
#endif
#endif
