#ifndef LEVEL_H
#define LEVEL_H

#include "../Header/tools.h"
#include "../Header/levelmap.h"
#include "../Header/enemy.h"
#include "../Header/player.h"

enum LevelState
{
    LEVELINIT, PLAYING, WIN, LOSE
};
class Level
{
    public:
        //关卡计时器
        Level(LevelMap * map, int enemyPic, const Counter & counter, std::map<std::string, Sound *> & soundSrc);
        virtual ~Level();
        virtual void update() = 0;
        virtual void draw() = 0;
        void readEnemy(const char * fileName);
        LevelState getState();
        void setState(LevelState newState);
    protected:
        void addEnemy(Counter time, int HP, float vx, float vy);
        LevelState state;
        //存放地图块的指针
        LevelMap * levelMap;
        //存放对应矩阵的指针
        MapKind ** mapValue;
        //敌人图片
        int enemyPic;
        //敌人参数
        std::vector<std::tuple<Counter, int, float, float>> enemyParam;
        //现在敌人数目
        unsigned int enemyCount;
        //存放敌人
        std::vector <Enemy*> enemies;
        //关卡计时器
        const Counter & counter;
        //音效
        std::map<std::string, Sound*> & soundSrc;
};

class SoloLevel : public Level
{
    public:
        SoloLevel(Player * player, int enemyPic, LevelMap * map, const Counter & counter, std::map<std::string, Sound*> & soundSrc, int initX, int initY);
        ~SoloLevel();
        virtual void update();
        virtual void draw();
    private:
        Player * player;
        int initX;
        int initY;
};

#endif