#include "../Header/game.h"

#pragma warning(disable : 4996)

Game::Game(std::map <std::string, int> & picDest, std::map <std::string, Sound*> & soundDest, std::map <std::string, MapKind *> & levelMap)
:state(INIT), volume(0, 100, 5, 100), picDest(picDest), soundDest(soundDest), levelMap(levelMap), op(nullptr), ed(nullptr), nowLevelCount(0){}

Game::~Game()
{
    //清理工作
    //因为是加载到内存所以手动释放
    for(std::map<std::string, int>::iterator i = picDest.begin(); i != picDest.end(); i++)
    {
        DeleteGraph(i -> second);
    }
    for(std::map<std::string, Sound*>::iterator i = soundDest.begin(); i != soundDest.end(); i++)
    {
        DeleteSoundMem(i -> second -> getHandle());
        delete i -> second;
    }
    for(std::map<std::string, MapKind*>::iterator i = levelMap.begin(); i != levelMap.end(); i++)
    {
        delete i -> second;
    }
	delete op;
	delete ed;
}

void Game::loadPic(std::string name, const char * fileName)
{
    int imgHandle = LoadGraph(fileName);
    picDest.insert(std::pair<std::string, int>(name, imgHandle));
}
void Game::loadSound(std::string name, const char * fileName, int playType)
{
    soundDest.insert(std::pair<std::string, Sound*>(name, new Sound(fileName, playType)));
}
void Game::readMap(std::string name, int xNum, int yNum, const char * fileName)
{
    MapKind * tmpMap = new MapKind[xNum * yNum];

    FILE * fp;
	if((fp = fopen(fileName, "rb")) == NULL)
	{
		printfDx("Map File Error!");
		return;
	}
	int parsedNum = 0;
	
	while(!feof(fp))
	{
		char line[256] = {0};
		fgets(line, 256, fp);
		if(line[0] == '$')
		{
			continue;
		}
		char * word = strtok(line, ", \r\n");
		while(word != NULL)
		{
			if(strcmp(word, "BLOCK") == 0)
			{
				tmpMap[parsedNum] = BLOCK;
			}
			else if(strcmp(word, "ROAD") == 0)
			{
				tmpMap[parsedNum] = ROAD;
			}
			parsedNum++;
			word = strtok(NULL, ", \r\n");
		}
	}
	if(parsedNum != (xNum * yNum))
	{
		printfDx("Block Num Error!");
	}

    levelMap.insert(std::pair<std::string, MapKind*>(name, tmpMap));
}
void Game::clearMap()
{
    for(std::map<std::string, MapKind*>::iterator i = levelMap.begin(); i != levelMap.end(); i++)
    {
        delete i -> second;
    }
    levelMap.clear();
}
GameState Game::getState()
{
    return this -> state;
}
void Game::setState(GameState newState)
{
    this -> state = newState;
}
void Game::changeVolume(bool isIncrease)
{
	if(isIncrease)
	{
		volume++;
	}
	else volume--;
	for(std::map<std::string, Sound*>::iterator i = soundDest.begin(); i != soundDest.end(); i++)
	{
		ChangeVolumeSoundMem(int(volume.getData() * 255 / 100), (i -> second) -> getHandle());
	}
}
int Game::getVolume()
{
	return volume.getData();
}
KeyState Game::getKeyState(int key)
{
	return kbd.getState(key);
}