#ifndef GAME_H
#define GAME_H

#include "util.h"
#include "ObjMgr.h"

class Game
{
    public:
        Game(const char * bgmFile);
        ~Game();
        void process();
        void readObj(const char * fileName);
    private:
        void addObj(Object4D * obj);
        Sound * bgm;
        ObjMgr * objmgr;
};

#endif