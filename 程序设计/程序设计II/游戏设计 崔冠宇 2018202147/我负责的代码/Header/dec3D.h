#ifndef DEC3D_H
#define DEC3D_H

#include "../Header/tools.h"
//高中代码的重构
typedef struct _Point3D
{
    public:
        float x, y, z;
}Point3D;

class Dec3D
{
    public:
        Dec3D(int imgBack, int imgFront, int imgSize);
        void draw();
    private:
        int imgBack, imgFront, imgSize;
        //顶点信息
        VERTEX3D vertex[6];
        //中心点坐标,XYZ方向旋转角度(状态)
        float cenX, cenY, cenZ, rotX, rotY, rotZ;
        //XYZ分速度,XYZ旋转速度(过程)
        float spdX, spdY, spdZ, rotSpdX, rotSpdY, rotSpdZ;
        //淡入淡出使用(淡入标志,淡出标志,显示时间,亮度)
	    bool drawFlag, fadeinFlag, fadeoutFlag;
        int disTime, brt;
};

#endif