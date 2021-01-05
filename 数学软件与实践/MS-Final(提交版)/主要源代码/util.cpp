#include "util.h"

//------------class Sound-------------
Sound::Sound(const char * fileName, int playType): isPlaying(false), playType(playType)
{
    soundHandle = LoadSoundMem(fileName);
}

Sound::~Sound()
{
    DeleteSoundMem(soundHandle);
}
void Sound::play()
{
    if(playType == DX_PLAYTYPE_LOOP)
    {
	    if (isPlaying) return;
        isPlaying = true;
    }
    PlaySoundMem(soundHandle, playType);
}
void Sound::stop()
{
    if(playType == DX_PLAYTYPE_LOOP)
    {
	    if (!isPlaying) return;
        isPlaying = false;
    }
    StopSoundMem(soundHandle);
}