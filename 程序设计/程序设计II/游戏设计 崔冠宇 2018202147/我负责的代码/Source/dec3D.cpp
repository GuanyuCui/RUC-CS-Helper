#include "../Header/dec3D.h"

//四个由中心点指向顶点的向量(初始值,后进行旋转)
VECTOR baseVec[4] = { VGet(1, 1, 0), VGet(-1, 1, 0), VGet(-1, -1, 0), VGet(1, -1, 0) };

Dec3D::Dec3D(int imgBack, int imgFront, int imgSize):imgBack(imgBack), imgFront(imgFront), imgSize(imgSize)
{
    //顶点参数初始化
	
	vertex[0].norm = VGet(0.0f, 0.0f, -1.0f);
	vertex[0].dif = GetColorU8(255, 255, 255, 128);//GetColorU8(255, 255, 255, 128);
	vertex[0].spc = GetColorU8(255, 255, 255, 128);
	vertex[0].u = 1.0f;
	vertex[0].v = 0.0f;
	vertex[0].su = 0.0f;
	vertex[0].sv = 0.0f;

	vertex[1].norm = VGet(0.0f, 0.0f, -1.0f);
	vertex[1].dif = GetColorU8(255, 255, 255, 128);
	vertex[1].spc = GetColorU8(255, 255, 255, 128);
	vertex[1].u = 0.0f;
	vertex[1].v = 0.0f;
	vertex[1].su = 0.0f;
	vertex[1].sv = 0.0f;

	vertex[2].norm = VGet(0.0f, 0.0f, -1.0f);
	vertex[2].dif = GetColorU8(255, 255, 255, 128);
	vertex[2].spc = GetColorU8(255, 255, 255, 128);
	vertex[2].u = 0.0f;
	vertex[2].v = 1.0f;
	vertex[2].su = 0.0f;
	vertex[2].sv = 0.0f;

	vertex[3].norm = VGet(0.0f, 0.0f, -1.0f);
	vertex[3].dif = GetColorU8(255, 255, 255, 128);
	vertex[3].spc = GetColorU8(255, 255, 255, 128);
	vertex[3].u = 1.0f;
	vertex[3].v = 0.0f;
	vertex[3].su = 0.0f;
	vertex[3].sv = 0.0f;

	vertex[4].norm = VGet(0.0f, 0.0f, -1.0f);
	vertex[4].dif = GetColorU8(255, 255, 255, 128);
	vertex[4].spc = GetColorU8(255, 255, 255, 128);
	vertex[4].u = 0.0f;
	vertex[4].v = 1.0f;
	vertex[4].su = 0.0f;
	vertex[4].sv = 0.0f;

	vertex[5].norm = VGet(0.0f, 0.0f, -1.0f);
	vertex[5].dif = GetColorU8(255, 255, 255, 128);
	vertex[5].spc = GetColorU8(255, 255, 255, 128);
	vertex[5].u = 1.0f;
	vertex[5].v = 1.0f;
	vertex[5].su = 0.0f;
	vertex[5].sv = 0.0f;
	
	drawFlag = false;
    
}

void Dec3D::draw()
{
    //没显示时进行初始化
	if (!drawFlag)
    {
		cenX = static_cast<float>(-50 + GetRand(1100));//-50~1050
		cenY = static_cast<float>(50 + GetRand(800));//50~850
		disTime = 60 + GetRand(140);
		cenZ = static_cast<float>(20 + GetRand(70));
		spdX = static_cast<float>(1.5 - (GetRand(30) / 15.0f));
		spdY = static_cast<float>(-1.5 - (GetRand(20) / 18.0f));
		spdZ = static_cast<float>(-1.0 + GetRand(90) / 40.0f);
		rotX = 0;
		rotY = 0;
		rotZ = 0;
		rotSpdX = static_cast<float>(GetRand(100)/1800.0f);
		rotSpdY = static_cast<float>(GetRand(100)/1800.0f);
		rotSpdZ = static_cast<float>(GetRand(100)/1800.0f);
		brt = 0;
		drawFlag = true;
		fadeinFlag = true;
		fadeoutFlag = false;
	}
    else
    {
        cenX += spdX;
        cenY += spdY;
        cenZ += spdZ;
        rotX += rotSpdX;
        rotY += rotSpdY;
        rotZ += rotSpdZ;

        //获得旋转矩阵
        //三个轴上的旋转矩阵
        MATRIX MXRot = MGetRotX(rotX);
        MATRIX MYRot = MGetRotY(rotY);
        MATRIX MZRot = MGetRotZ(rotZ);

        //旋转时临时使用
        //四个向量
        VECTOR tempVec[4];
        //四个Point对象(右上0,左上1,左下2,右下3)
        Point3D tempPoint[4];
        //旋转并获得坐标
        for (int i = 0; i < 4; i++)
		{
            //四个向量根据矩阵旋转
            tempVec[i] = VTransform(baseVec[i], MXRot);
            tempVec[i] = VTransform(tempVec[i], MYRot);
            tempVec[i] = VTransform(tempVec[i], MZRot);
            //根据中心点和四个向量计算四点坐标
            tempPoint[i].x = cenX + imgSize * tempVec[i].x;
            tempPoint[i].y = cenY + imgSize * tempVec[i].y;
            tempPoint[i].z = cenZ + imgSize * tempVec[i].z;
        }
        //顶点坐标
        vertex[0].pos = VGet(tempPoint[0].x, tempPoint[0].y, tempPoint[0].z);
        vertex[1].pos = VGet(tempPoint[1].x, tempPoint[1].y, tempPoint[1].z);
        vertex[2].pos = VGet(tempPoint[2].x, tempPoint[2].y, tempPoint[2].z);
        vertex[3].pos = VGet(tempPoint[0].x, tempPoint[0].y, tempPoint[0].z);
        vertex[4].pos = VGet(tempPoint[2].x, tempPoint[2].y, tempPoint[2].z);
        vertex[5].pos = VGet(tempPoint[3].x, tempPoint[3].y, tempPoint[3].z);

        //淡入淡出
        if(fadeinFlag)
        {
            brt += 5;
            if(brt >= 255)
            {
                brt = 255;
                fadeinFlag = 0;
            }
        }
        disTime--;
        if(disTime <= 0)
        {
            disTime = 0;
            fadeoutFlag = true;
        }
        if (fadeoutFlag)
        {
            if(brt > 0)
            {
                brt -= 3;
            }
            else brt = 0;
        }
            
        //描画(包括亮度)
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, brt);
        DrawPolygon3D(vertex, 2, imgBack, TRUE);
        DrawPolygon3D(vertex, 2, imgFront, TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        //亮度变为0后，清除
        if(brt <= 0 && fadeoutFlag == 1)
        {
            drawFlag = false;
        }
    }
}
