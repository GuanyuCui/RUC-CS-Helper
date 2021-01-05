#include "ObjMgr.h"

extern float nowW;

ObjMgr::ObjMgr(){}

ObjMgr::~ObjMgr()
{
    for(size_t i = 0; i < objects.size(); i++)
    {
        delete objects[i];
    }
}

void ObjMgr::addObj(Object4D * object)
{
    objects.push_back(object);
}

void ObjMgr::process()
{
    for(size_t i = 0; i < objects.size(); i++)
    {
        objects[i] -> move();
        objects[i] -> draw();
        // 必须是检测后面的, 否则会重复
        for(size_t j = i + 1; j < objects.size(); j++)
        {
            objects[i] -> collideWith(objects[j]);
        }
    }
}