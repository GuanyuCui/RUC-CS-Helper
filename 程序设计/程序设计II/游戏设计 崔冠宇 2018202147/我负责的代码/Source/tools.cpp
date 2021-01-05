#include "../Header/tools.h"

//------------class Sound-------------
Sound::Sound(const char * fileName, int playType): isPlaying(false), playType(playType)
{
    soundHandle = LoadSoundMem(fileName);
}
Sound::Sound(int soundHandle, int playType): isPlaying(false), soundHandle(soundHandle), playType(playType){}
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
int Sound::getHandle()
{
	return soundHandle;
}
bool Sound::getPlayingState()
{
    return isPlaying;
}

KeyBoard::KeyBoard()
{
    states.fill(NOTPRESS);
}
KeyState KeyBoard::getState(int key)
{
    switch(states[key])
    {
        case PRESS:
            if(CheckHitKey(key))
            {
                states[key] = HOLD;
            }
            else
            {
                states[key] = RELEASE;
            }
            break;
        case HOLD:
            if(CheckHitKey(key)){}
            else
            {
                states[key] = RELEASE;
            }
            break;
        case RELEASE:
            if(CheckHitKey(key))
            {
                states[key] = PRESS;
            }
            else
            {
                states[key] = NOTPRESS;
            }
            break;
        case NOTPRESS:
            if(CheckHitKey(key))
            {
                states[key] = PRESS;
            }
            else
            {
                states[key] = NOTPRESS;
            }
    }
    return states[key];
}

Pic::Pic(float x, float y, int imgHandle, bool isBrt, unsigned int brtStep, unsigned int initBrt)
: x(x), y(y), imgHandle(imgHandle), isBrt(isBrt), brt(0, 255, brtStep, initBrt), isShow(true){}

Pic::~Pic()
{
    DeleteGraph(imgHandle);
}

void Pic::draw()
{
    if(isBrt)
    {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, brt.getData());
        DrawGraph(int(x), int(y), imgHandle, TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        brt++;
    }
    else
    {
        DrawGraph(int(x), int(y), imgHandle, TRUE);
    }
}
bool Pic::getShowState() const
{
    return isShow;
}


MovingPic::MovingPic(float x, float y, int showX1, int showY1, int showX2, int showY2, int imgHandle, float vx, float vy, bool isBrt, unsigned int brtStep, unsigned int initBrt)
:Pic(x, y, imgHandle, isBrt, brtStep, initBrt), showX1(showX1), showY1(showY1), showX2(showX2), showY2(showY2), velocity(vx, vy){}

MovingPic::~MovingPic()
{
    DeleteGraph(imgHandle);
}

void MovingPic::draw()
{
    if(int(x) >= showX1 && int(y) >= showY1 && int(x) <= showX2 && int(y) <= showY2)
    {
        Pic::draw();
        x += velocity.getX();
        y += velocity.getY();
    }
    else
    {
        isShow = false;
    }
}

bool MovingPic::getShowState() const
{
    return isShow;
}