#ifndef LEVELMAP_H
#define LEVELMAP_H

#include "../Header/tools.h"
enum MapKind
{
    //无路, 有路
    BLOCK, ROAD
};

class MapBlock
{
    public:
        //按上面MapKind顺序传入的地图块的int数组
        MapBlock(std::vector<int> & blocksPic, int x1, int y1, int x2, int y2, MapKind kind);
        ~MapBlock();
        void draw();
        MapKind getKind() const;
    private:
        MapKind kind;
        int mapHandle;
        int x1;
        int y1;
        int x2;
        int y2;
};

class LevelMap
{
    public:
        //地图块素材数组
        LevelMap(std::vector<int> & blocksPic, MapKind * kinds, int xNum, int yNum, int startX = 0, int startY = 0);
        ~LevelMap();
        void draw();
        int getXNum() const;
        int getYNum() const;
        MapKind getKind(int x, int y) const;
    private:
        //存放地图块
        std::vector<MapBlock *> maps;
        int xNum;
        int yNum;
};

#endif