/* Donated the the public domain 2012-2020 Sam Trenholme.  Written in 2009,
 * 2012, 2015, 2017, 2018, and 2020.
 *
 * This software is provided 'as is' with no guarantees of correctness or
 * fitness for purpose.
 *
 * This program outputs a list of floating point numbers
 */

/* This is a tiny implementation of the Radio Gatun hash function/
 * stream cipher by Sam Trenholme */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* This determines the word size we use for this particular Radio Gatun
 * implementation; DWR_WORDSIZE needs to be a multiple of 8 */
#define DWR_WORD uint32_t
#define DWR_WORDSIZE 32

/* These are hard coded in the Radio Gatun specification */
#define DWR_MILLSIZE 19
#define DWR_BELTROWS 3
#define DWR_BELTCOL 13
#define DWR_BELTFEED 12
#define DWR_BLANKROUNDS 16

/* The "mill" part of Radio Gatun */
void dwr_mill(DWR_WORD *a) {
	DWR_WORD A[DWR_MILLSIZE];
	DWR_WORD x;
	int i = 0;
	int y = 0;
	int r = 0;
	int z = 0;
	int q = 0;
	for(i = 0; i < DWR_MILLSIZE ; i++) {
		y = (i * 7) % DWR_MILLSIZE;
		r = ((i * (i + 1)) / 2) % DWR_WORDSIZE;
		x = a[y] ^ (a[ ((y + 1) % DWR_MILLSIZE) ] | 
		    (~a[ ((y + 2) % DWR_MILLSIZE) ]));
		if(r > 0) {
			A[i] = (x >> r) | (x << (DWR_WORDSIZE - r));
		} else {
			A[i] = x;
		}
	}
	for(i = 0; i < DWR_MILLSIZE ; i++) {
		y = i;
		z = (i + 1) % DWR_MILLSIZE;
		q = (i + 4) % DWR_MILLSIZE;
		a[i] = A[y] ^ A[z] ^ A[q];
	}
	a[0] ^= 1;
}	

/* The "belt" part of Radio Gatun */
void dwr_belt(DWR_WORD *a, DWR_WORD *b) {
	DWR_WORD q[DWR_BELTROWS];
	int s = 0;
	int i = 0;
	int v = 0;
	for(s = 0; s < DWR_BELTROWS ; s++) {
		q[s] = b[((s * DWR_BELTCOL) + DWR_BELTCOL - 1)];
	}
	for(i = DWR_BELTCOL - 1; i > 0; i--) {
		for(s = 0; s < DWR_BELTROWS ; s++) {
			v = i - 1;
			if(v < 0) {
				v = DWR_BELTCOL - 1;
			}
			b[((s * DWR_BELTCOL) + i)] = 
				b[((s * DWR_BELTCOL) + v)];
		}
	}
	for(s = 0; s < DWR_BELTROWS; s++) {
		b[(s * DWR_BELTCOL)] = q[s];
	}
	for(i = 0; i < DWR_BELTFEED ; i++) {
		s = (i + 1) + ((i % DWR_BELTROWS) * DWR_BELTCOL);
		b[s] ^= a[(i + 1)];
	}
	dwr_mill(a);
	for(i = 0; i < DWR_BELTROWS; i++) {
		a[(i + DWR_BELTCOL)] ^= q[i];
	}
}

/* Convert a null-terminated string in to a Radio Gatun state (doesn't
 * include padding and what not) */
void dwr_input_map(DWR_WORD *a, DWR_WORD *b, uint8_t *v) {
	DWR_WORD p[3];
	int q = 0;
	int c = 0;
	int r = 0;
	int done = 0;
	for(;;) {
		p[0] = p[1] = p[2] = 0;
		for(r = 0; r < 3; r++) {
			for(q = 0; q < DWR_WORDSIZE / 8; q++) {
				int x = 0;
				x = (int)*v;
				v++;
				x &= 0xff;
				if(x == 0) {
					done = 1;
					x = 1; /* Append with single byte
                                                * w/ value of 1 */
				}
				p[r] |= x << (q * 8);
				if(done == 1) {
					for(c = 0; c < 3; c++) {
						b[c * 13] ^= p[c];
						a[16 + c] ^= p[c];
					}
					dwr_belt(a,b);
					return;
				}
			}
		}
		for(c = 0; c < 3; c++) {
			b[c * 13] ^= p[c];
			a[16 + c] ^= p[c];
		}
		dwr_belt(a,b);
	}
}

/* A structure contining a RadioGatun state */
typedef struct {
        DWR_WORD *a;
        DWR_WORD *b;
	int index;
} dwr_rg;

/* These are the "public methods" for this library */

/* Given a null-terminated string, create a RG32 state using the string
 * as the input */
dwr_rg *dwr_init_rg(char *v) {
	dwr_rg *out;
	int c = 0;
	
	out = (dwr_rg *)malloc(sizeof(dwr_rg));
	if(out == 0) {
		return 0;
	}
	out->a = (DWR_WORD *)malloc(DWR_MILLSIZE * sizeof(DWR_WORD) + 1);
	out->b = (DWR_WORD *)malloc(DWR_BELTROWS * DWR_BELTCOL * 
			sizeof(DWR_WORD) + 1);
	if(out->a == 0 || out->b == 0) {
		free(out);
		return 0;
	}

	for(c = 0; c < DWR_MILLSIZE; c++) {
		out->a[c] = 0;
	}
	for(c = 0; c < DWR_BELTROWS * DWR_BELTCOL; c++) {
		out->b[c] = 0;
	}
	out->index = 0;
	dwr_input_map(out->a,out->b,v);
	for(c = 0; c < DWR_BLANKROUNDS; c++) {
		dwr_belt(out->a,out->b);
	}
	return out;
}

/* Destroy a created RG32 state */
void dw_zap_rg(dwr_rg *tozap) {
	if(tozap == 0) {
		return;
	}
	if(tozap->a != 0) {
		free(tozap->a);
	}
	if(tozap->b != 0) {
		free(tozap->b);
	}
	free(tozap);
}

/* Given a RG state, give out a pseudo-random number and update the
 * state */
DWR_WORD dwr_rng(dwr_rg *state) {
	DWR_WORD out;
	if((state->index & 1) == 0) {
		dwr_belt(state->a,state->b);
		out = state->a[1];	
	} else {
		out = state->a[2];
	}
	(state->index)++;
	/* Endian swap so the test vectors match up; this code assumes
         * DWR_WORD is 32-bit */
	out = (out << 24) | 
	    ((out & 0xff00) << 8) |
	    ((out & 0xff0000) >> 8) |
	    (out >> 24);
	return out;
}

/* Main function; remove this if using the above as an API in your program */
int main(int argc, char **argv) {
	dwr_rg *hash;
	int a;
	uint32_t x;
	float y;
	int counter;
	if(argc != 2 && argc != 3) {
		printf("Usage: rg32 {input to hash}\n");
		exit(1);
	}
	hash = dwr_init_rg(argv[1]);
	if(hash == 0) {
		exit(1);
	}
	if(argc != 3) {
		printf("RG32 %s\n",argv[1]);
	}
	for(counter=1;counter<=8;counter++) {
		x = dwr_rng(hash);
		y = x & 0x7FFFFFFF;
		y /= 2147483648.0;
		if(argc == 3) {
			printf("%08x",x);
		} else {
			printf("RG32 test %d: %.6f\n",counter,y);
		}
	}
	if(argc != 2) {puts("");}
}
	
