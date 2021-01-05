#include "Game.h"

float nowW = 0.0f;

// 摄像机角度
float RollAngle = -DX_PI_F / 4.0f;
// 摄像机旋转圈大小 
float RollSize = 1500.0f;
// 摄像机高度
float RollHeight = 1000.0f;

Game::Game(const char * bgmFile)
{
    bgm = new Sound(bgmFile, DX_PLAYTYPE_LOOP);
    objmgr = new ObjMgr();
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);
    bgm -> play();
}

Game::~Game()
{
    bgm -> stop();
    delete bgm;
    delete objmgr;
}

void Game::addObj(Object4D * obj)
{
    objmgr -> addObj(obj);
}

void Game::process()
{
    // 左右键旋转视角
    if( CheckHitKey( KEY_INPUT_LEFT ) == 1 )
    {
        RollAngle -= DX_PI_F / 120.0f ;
    }
    if( CheckHitKey( KEY_INPUT_RIGHT ) == 1 )
    {
        RollAngle += DX_PI_F / 120.0f ;
    }

    // AS键更改圈的大小
    if (CheckHitKey(KEY_INPUT_A))
    {
        RollSize -= 50;
    }
    if (CheckHitKey(KEY_INPUT_S))
    {
        RollSize += 50;
    }

    // 上下键更改高度
    if (CheckHitKey(KEY_INPUT_UP))
    {
        RollHeight += 50;
    }
    if (CheckHitKey(KEY_INPUT_DOWN))
    {
        RollHeight -= 50;
    }

    // ZX键更改 W
    if (CheckHitKey(KEY_INPUT_Z))
    {
        nowW += 0.1f;
    }
    if (CheckHitKey(KEY_INPUT_X))
    {
        nowW -= 0.1f;
    }

    SetCameraPositionAndTarget_UpVecY( VGet(RollSize * std::cos(RollAngle), RollHeight, RollSize * std::sin(RollAngle) ), VGet(0.0f, 0.0f, 0.0f));

    // 绘制坐标轴
    // x
	DrawLine3D(VGet(-1020, 0, 0), VGet(1020, 0, 0), GetColor(0, 0, 255));
    DrawCone3D(VGet(1050, 0, 0), VGet(1020, 0, 0), 20.0f, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
    // y
    DrawLine3D(VGet(0, -820, 0), VGet(0, 820, 0), GetColor(0, 0, 255));
    DrawCone3D(VGet(0, 850, 0), VGet(0, 820, 0), 20.0f, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
    // z
    DrawLine3D(VGet(0, 0, 1020), VGet(0, 0, -1020), GetColor(0, 0, 255));
    DrawCone3D(VGet(0, 0, 1050), VGet(0, 0, 1020), 20.0f, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);

    // 地面
    DrawTriangle3D(VGet(-1000, 0, 1000), VGet(-1000, 0, -1000), VGet(1000, 0, 1000), GetColor(192, 192, 192), TRUE);
    DrawTriangle3D(VGet(1000, 0, -1000), VGet(-1000, 0, -1000), VGet(1000, 0, 1000), GetColor(192, 192, 192), TRUE);

    objmgr -> process();

    DrawFormatString(0, 0, GetColor(255, 255, 255), "摄像机位置: (%.2f, %.2f, %.2f, %.2f)", RollSize * std::cos(RollAngle), RollHeight, RollSize * std::sin(RollAngle), nowW);
    DrawFormatString(0, 25, GetColor(255, 255, 255), "左右键旋转视角, AS键改变与轴的距离");
    DrawFormatString(0, 50, GetColor(255, 255, 255), "上下键更改高度, ZX键更改第四维度");
    DrawFormatString(0, 75, GetColor(255, 255, 255), "P键截图");
}

void Game::readObj(const char * fileName)
{
    // 格式: 属性, 其它
    std::fstream file(fileName);
    if(!file.is_open())
    {
        printfDx("File Read Error!\n");
    }
    else
    {
        //一行行的读取文件
        while(!file.eof())
        {
            //临时字符串
            std::string tmpStr;
            //读一行
            std::getline(file, tmpStr);
            //注释行或者空行
            if(tmpStr[0] == '$' || tmpStr[0] == '\n' || tmpStr.empty())
            {
                continue;
            }
            // 若属性 == Sphere4D
            if(tmpStr == "@Sphere4D")
            {
                // Center(4), Radius, Velocity(4), Mass, Color(3)
                float center[4] = {0.0f};
                float radius = 0.0f;
                float velocity[4] = {0.0f};
                float mass = 0.0f;
                int color[3] = {0};
                // Center(4)
                std::getline(file, tmpStr);
                sscanf_s(tmpStr.c_str(), "Center:(%f,%f,%f,%f)", &center[0], &center[1], &center[2], &center[3]);
                // Radius
                std::getline(file, tmpStr);
                sscanf_s(tmpStr.c_str(), "Radius:%f", &radius);
                // Velocity(4)
                std::getline(file, tmpStr);
                sscanf_s(tmpStr.c_str(), "Velocity:(%f,%f,%f,%f)", &velocity[0], &velocity[1], &velocity[2], &velocity[3]);
                // Mass
                std::getline(file, tmpStr);
                sscanf_s(tmpStr.c_str(), "Mass:%f", &mass);
                // Color
                std::getline(file, tmpStr);
                sscanf_s(tmpStr.c_str(), "Color:RGB(%d,%d,%d)", &color[0], &color[1], &color[2]);
                objmgr -> addObj( new Sphere4D
                    (
                        std::array<float, 4>({center[0], center[1], center[2], center[3]}),
                        radius,
                        std::array<float, 4>({velocity[0], velocity[1], velocity[2], velocity[3]}),
                        mass,
                        GetColor(color[0], color[1], color[2])
                    )
                );
            }
        }
    }
}