#include "../Header/level.h"

#pragma warning(disable : 4996)

Level::Level(LevelMap * map, int enemyPic, const Counter & counter, std::map<std::string, Sound *> & soundSrc)
:state(LEVELINIT),levelMap(map), enemyPic(enemyPic), counter(counter), enemyCount(0), soundSrc(soundSrc)
{
    //计算命令矩阵
    int xNum = levelMap -> getXNum();
    int yNum = levelMap -> getYNum();

    mapValue = new MapKind *[xNum];
    for(int i = 0; i < xNum; i++)
    {
        mapValue[i] = new MapKind [yNum];
        for(int j = 0; j < yNum; j++)
        {
            mapValue[i][j] = levelMap -> getKind(i, j);
        }
    }
}

Level::~Level(){}
void Level::addEnemy(Counter time, int HP, float vx, float vy)
{
	std::tuple<Counter, int, float, float> t = std::make_tuple(time, HP, vx, vy);
    enemyParam.push_back(t);
}
void Level::readEnemy(const char * fileName)
{
    FILE * fp;
	if((fp = fopen(fileName, "rb")) == NULL)
	{
		printfDx("Enemy File Error!");
		return;
	}
	
	while(!feof(fp))
	{
		char line[128] = {0};
		fgets(line, 128, fp);
		if(line[0] == '$')
		{
			continue;
		}
        Counter eTime = 0ull;
        int HP = 0;
        float vx = 0.0f;
        float vy = 0.0f;
		sscanf(line, "%llu,%d,%f,%f", &eTime, &HP, &vx, &vy);
        addEnemy(eTime, HP, vx, vy);
	}
}
LevelState Level::getState()
{
    return state;
}
void Level::setState(LevelState newState)
{
    state = newState;
}


SoloLevel::SoloLevel(Player * player, int enemyPic, LevelMap * map, const Counter & counter, std::map<std::string, Sound *> & soundSrc, int initX, int initY)
:Level(map, enemyPic, counter, soundSrc), player(player), initX(initX), initY(initY)
{
}

SoloLevel::~SoloLevel()
{
    int xNum = levelMap -> getXNum();
    int yNum = levelMap -> getYNum();
    for(int i = 0; i < xNum; i++)
    {
        delete[] mapValue[i];
    }
    delete[] mapValue;
    delete levelMap;
    delete player;
    for(unsigned int i = 0; i < enemies.size(); i++)
    {
        delete enemies.at(i);
    }
}

void SoloLevel::update()
{
    //敌人移动
    for(unsigned int i = 0; i < enemyCount; i++)
    {
        //敌人存在
        if(enemies.at(i) -> getShow())
        {
            enemies.at(i) -> move();
        }
        else 
        {
            if(enemies.at(i) -> getSuccess())
            {
                player -> setPlayer(enemies.at(i) -> getHP(), 0);
                if(player -> getHP() <= 0)
                {
                    setState(LOSE);
                }
            }
            soundSrc.at("EnemyDestroy") -> play();
            //增加钱数
            player -> setPlayer(0, 5);
            delete enemies.at(i);
            enemies.erase(enemies.begin() + i);
			enemyCount--;
            player -> setEnemyRef(&enemies);
        }
    }
    for(unsigned int i = 0; i < enemyParam.size(); i++)
    {
        //到时间生产敌人
        if(counter == std::get<0>(enemyParam.at(i)))
        {
            int xNum = levelMap -> getXNum();
            int yNum = levelMap -> getYNum();
            //地图块长宽
            int xLen = SCREEN_X / xNum;
            int yLen = SCREEN_Y / yNum;
            enemies.push_back(new Enemy(mapValue, xNum, yNum, enemyPic, initX, initY, initX * xLen - xLen / 2 + 1, initY * yLen + yLen / 2, std::get<2>(enemyParam.at(i)), std::get<3>(enemyParam.at(i)), std::get<1>(enemyParam.at(i)), xLen));
            enemyCount++;
            player -> setEnemyRef(&enemies);
        }
    }
    //玩家操作, 包含玩家鼠标键盘操作和塔的攻击行为
    player->setTower(levelMap);
    player->updateTower(levelMap);
    if(counter >= std::get<0>(enemyParam.at(enemyParam.size() - 1)) && player -> getHP() > 0 && enemies.size() == 0)
    {
        setState(WIN);
    }
}

void SoloLevel::draw()
{
    //绘制地图
    levelMap -> draw();
    //玩家信息
    player -> showInfo();
    player -> showTowerinfo();
    player -> showRange();
    //绘制敌人
    for(unsigned int i = 0; i < enemies.size(); i++)
    {
        enemies.at(i) -> draw();
    }
}