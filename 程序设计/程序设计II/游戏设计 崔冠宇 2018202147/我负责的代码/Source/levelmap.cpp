#include "../Header/levelmap.h"

MapBlock::MapBlock(std::vector<int> & blocksPic, int x1, int y1, int x2, int y2, MapKind kind): 
mapHandle(blocksPic.at(kind)), x1(x1), y1(y1), x2(x2), y2(y2), kind(kind){}

MapBlock::~MapBlock(){}

void MapBlock::draw()
{
    DrawExtendGraph(x1, y1, x2, y2, mapHandle, TRUE);
}

MapKind MapBlock::getKind() const
{
    return kind;
}

LevelMap::LevelMap(std::vector<int> & blocksPic, MapKind * kinds, int xNum, int yNum, int startX, int startY):
xNum(xNum), yNum(yNum)
{
    //根据屏幕长、宽和地图块横纵数目计算每块的长度
    int blockX = SCREEN_X / xNum;
    int blockY = SCREEN_Y / yNum;
    //每一行
    for(int i = 0; i < yNum; i++)
    {
        //每一列
        for(int j = 0; j < xNum; j++)
        {
            maps.push_back(new MapBlock(blocksPic, startX + j * blockX, startY + i * blockY,
            startX + (j + 1) * blockX, startY + (i + 1) * blockY, kinds[i * xNum + j]));
        }
    }
}
LevelMap::~LevelMap()
{
    for(int i = 0; i < xNum * yNum; i++)
    {
        delete maps[i];
    }
}
void LevelMap::draw()
{
    for(int i = 0; i < xNum * yNum; i++)
    {
        maps.at(i) -> draw();
    }
}
int LevelMap::getXNum() const
{
    return xNum;
}
int LevelMap::getYNum() const
{
    return yNum;
}

MapKind LevelMap::getKind(int x, int y) const 
{
    return maps[y * xNum + x] -> getKind();
}
