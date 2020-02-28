
//**************************************************************************
//**
//** soundst.h : Heretic 2 : Raven Software, Corp.
//**
//** $RCSfile: soundst.h,v $
//** $Revision: 1.3 $
//** $Date: 2004/05/29 09:53:12 $
//** $Author: skyjake $
//**
//**************************************************************************

#ifndef __SOUNDSTH__
#define __SOUNDSTH__

//#define S_sfx (*gi.sounds)

#define MAX_SND_DIST    2025
#define MAX_CHANNELS    16

/*typedef struct
   {
   char name[8];
   int p1;
   } musicinfo_t; */

/*typedef struct sfxinfo_s
   {
   char tagName[32];
   char lumpname[12]; // Only need 9 bytes, but padded out to be dword aligned
   //struct sfxinfo_s *link; // Make alias for another sound
   int priority; // Higher priority takes precendence
   int usefulness; // Determines when a sound should be cached out
   void *snd_ptr;
   int lumpnum;
   int numchannels; // total number of channels a sound type may occupy
   boolean  changePitch;
   } sfxinfo_t; */

/*typedef struct
   {
   mobj_t *mo;
   int sound_id;
   int handle;
   int volume;
   int pitch;
   int priority;
   char veryloud;
   } channel_t;

   typedef struct
   {
   long id;
   unsigned short priority;
   char *name;
   mobj_t *mo;
   int distance;
   } ChanInfo_t;

   typedef struct
   {
   int channelCount;
   int musicVolume;
   int soundVolume;
   ChanInfo_t chan[16];
   } SoundInfo_t;
 */
//extern int snd_MaxVolume;
//extern int snd_MusicVolume;

int             S_GetSoundID(char *name);
void            S_LevelMusic(void);

/*void S_ShutDown(void);
   void S_Start(void);
   void S_StartSound(mobj_t *origin, int sound_id);
   void S_StartSoundAtVolume(mobj_t *origin, int sound_id, int volume);
   void S_StopSound(mobj_t *origin);
   void S_StopAllSound(void);
   void S_PauseSound(void);
   void S_ResumeSound(void);
   void S_UpdateSounds(mobj_t *listener);
   void S_StartSong(int song, boolean loop);
   void S_StartSongName(char *songLump, boolean loop);
   void S_StopSong(void);
   void S_Init(void);
   void S_Reset(void);
   void S_GetChannelInfo(SoundInfo_t *s);
   void S_SetMusicVolume(void);
   boolean S_GetSoundPlayingInfo(mobj_t *mobj, int sound_id); */

#endif
