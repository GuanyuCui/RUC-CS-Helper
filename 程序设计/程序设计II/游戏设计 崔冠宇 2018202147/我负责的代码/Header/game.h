#ifndef GAME_H
#define GAME_H

#include "../Header/tools.h"
#include "../Header/opening.h"
#include "../Header/level.h"
#include "../Header/ending.h"

//游戏进行状态
enum GameState
{
    INIT, OPLOADING, OPENING, SLLOADING, SOLOGAME, DBLOADING, DOUBLEGAME, LEVELWIN, GAMEWIN, GAMELOSE, SETTINGS, EDLOADING, ENDING, QUIT
};

class Game
{
    public:
        Game(std::map <std::string, int> & picDest, std::map <std::string, Sound*> & soundDest, std::map <std::string, MapKind *> & levelMap);
        ~Game();
        //加载图片
        void loadPic(std::string name, const char * fileName);
        //加载声音
        void loadSound(std::string name, const char * fileName, int playType);
        void readMap(std::string name, int xNum, int yNum, const char * fileName);
        void clearMap();
        //获取游戏状态
        GameState getState();
        //改变游戏状态
        void setState(GameState newState);
        //
        void changeVolume(bool isIncrease);
        int getVolume();
        KeyState getKeyState(int key);
        //键盘
        KeyBoard kbd;
        //开始界面
        Opening * op;
        //结尾名单
        Ending * ed;
        std::vector <Level *> levels;
        unsigned int nowLevelCount;

    private:
        std::map <std::string, int> & picDest;
        std::map <std::string, Sound*> & soundDest;
        std::map <std::string, MapKind *> & levelMap;
        //游戏状态
        GameState state;
        RangedNum<int> volume;
};

#endif