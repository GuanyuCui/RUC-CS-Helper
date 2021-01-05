#include "../Header/tools.h"
#include "../Header/opening.h"
#include "../Header/game.h"
#include "../Header/level.h"

#include "DxLib.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//存储所有图片素材的Map
	std::map <std::string, int> pics;
	//存储所有音效指针的Map
	std::map <std::string, Sound*> sounds;
	//地图块Vector
	std::vector <int> mapBlocksPic;
	//地图Map
	std::map <std::string, MapKind*> levelMaps;

	//帧计时器
	Counter stageCounter = 0ull;
	Counter endingCounter = 0ull;

    //一些DxLib初始设定
    //不输出Log文件
    SetOutApplicationLogValidFlag(FALSE);
    //窗口标题
    SetMainWindowText("程序设计II大作业 4组");
    //窗口模式
    ChangeWindowMode(TRUE);
    //窗口大小和ColorBit
    SetGraphMode(SCREEN_X, SCREEN_Y, 16);
    //DxLib初始化
    if(DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0) return -1;
    //窗口失去焦点仍然运行
    SetAlwaysRunFlag(TRUE);
	//随机数种子初始化
    SRand(int(std::time(0)));

    //字体
    int settingFont = CreateFontToHandle(NULL, 40, 10, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

    //游戏对象
    Game TowerDefense(pics, sounds, levelMaps);
    
    //游戏主循环
    while(true)
    {
        //刷新屏幕
        ClearDrawScreen();
        //处理信息有误
        if(ProcessMessage() == -1)
        {
            break;
        }
        GameState nowGameState = TowerDefense.getState();
        //初始化
        if(nowGameState == INIT)
        {
            //加载一些素材
            TowerDefense.loadPic("TitleBack", "../Image/BackGround.png");
            TowerDefense.loadPic("LevelBack", "../Image/LevelBack.png");
            TowerDefense.loadPic("EndingBack", "../Image/EndingBack.png");
            TowerDefense.loadPic("DecPic0", "../Image/DecPic0.png");
            TowerDefense.loadPic("DecPic1", "../Image/DecPic1.png");
            TowerDefense.loadPic("Staff0", "../Image/Staff0.png");
            TowerDefense.loadPic("Staff1", "../Image/Staff1.png");
            TowerDefense.loadPic("Staff2", "../Image/Staff2.png");
            TowerDefense.loadPic("Staff3", "../Image/Staff3.png");
            TowerDefense.loadPic("Staff4", "../Image/Staff4.png");
            TowerDefense.loadPic("Staff5", "../Image/Staff5.png");

            TowerDefense.loadPic("Gun", "../Image/GunTower.png");
            TowerDefense.loadPic("Arrow", "../Image/ArrowTower.png");
            TowerDefense.loadPic("Magic", "../Image/MagicTower.png");

            TowerDefense.loadPic("GunBullet", "../Image/GunBullet.png");
            TowerDefense.loadPic("ArrowBullet", "../Image/ArrowBullet.png");
            TowerDefense.loadPic("MagicBullet", "../Image/MagicBullet.png");
            
            TowerDefense.loadPic("RITIC", "../Image/RITIC.png");

			TowerDefense.loadPic("Blood", "../Image/blood.png");
			TowerDefense.loadPic("BloodBar", "../Image/bloodbar.png");
			TowerDefense.loadPic("Coin", "../Image/coin.jpg");
			TowerDefense.loadPic("bigSet", "../Image/bigSet.png");
			TowerDefense.loadPic("bigUp", "../Image/bigUp.png");
			TowerDefense.loadPic("littleUp", "../Image/littleUp.png");
            TowerDefense.loadPic("lack", "../Image/lack.png");
			TowerDefense.loadPic("littleSet", "../Image/littleSet.png");
			TowerDefense.loadPic("redRec", "../Image/redRec.png");
			TowerDefense.loadPic("greenRec", "../Image/greenRec.png");
			TowerDefense.loadPic("warning", "../Image/warning.png");
            //-----------
            TowerDefense.loadPic("Enemy1", "../Image/Enemy1.png");
            TowerDefense.loadPic("Enemy2", "../Image/Enemy2.png");

            TowerDefense.loadSound("TitleBackMusic", "../Sound/Music/Gusty Garden.mp3", DX_PLAYTYPE_LOOP);
            TowerDefense.loadSound("LevelBackMusic", "../Sound/Music/Floater Land.mp3", DX_PLAYTYPE_LOOP);
            TowerDefense.loadSound("EndingBackMusic", "../Sound/Music/Ending.mp3", DX_PLAYTYPE_LOOP);
            TowerDefense.loadSound("SelectSFX", "../Sound/Sfx/select.wav", DX_PLAYTYPE_BACK);
            TowerDefense.loadSound("CancelSFX", "../Sound/Sfx/cancel.wav", DX_PLAYTYPE_BACK);
            TowerDefense.loadSound("ChooseSFX", "../Sound/Sfx/choose.wav", DX_PLAYTYPE_BACK);
            TowerDefense.loadSound("EnemyDestroy", "../Sound/Sfx/enemydestroy.wav", DX_PLAYTYPE_BACK);
            TowerDefense.loadSound("TowerAttack", "../Sound/Sfx/towerattack.wav", DX_PLAYTYPE_BACK);
            
            //地图块加载
            mapBlocksPic.push_back(LoadGraph("../Image/MapBlocks/Block.png"));
            mapBlocksPic.push_back(LoadGraph("../Image/MapBlocks/Road.png"));
            
            //状态转移至OPLOADING
            TowerDefense.setState(OPLOADING);
        }
        //标题加载
        else if(nowGameState == OPLOADING)
        {
			//建立开始界面对象
            TowerDefense.op = new Opening(pics.at("TitleBack"), pics.at("DecPic0"), pics.at("DecPic1"), TowerDefense.kbd);
            //图片切割
            int choiceDivs[8] = { 0 };
            LoadDivGraph("../Image/TitleChoice.png", 8, 2, 4, 215, 63, choiceDivs);
            //四个选项
            TowerDefense.op -> addChoice(new TitleChoice(820, 500, choiceDivs[1], choiceDivs[0]));
            TowerDefense.op -> addChoice(new TitleChoice(810, 560, choiceDivs[3], choiceDivs[2]));
            TowerDefense.op -> addChoice(new TitleChoice(790, 620, choiceDivs[5], choiceDivs[4]));
            TowerDefense.op -> addChoice(new TitleChoice(760, 680, choiceDivs[7], choiceDivs[6]));
            
            //光效
            ChangeLightTypeDir(VGet(0.0f, 0.0f, 1.0f));
            SetLightDifColor(GetColorF(1.0f, 0.1f, 0.0f, 0.2f));
            SetLightSpcColor(GetColorF(0.7f, 0.1f, 0.0f, 0.1f));
            TowerDefense.setState(OPENING);
        }
        //标题画面
        else if(nowGameState == OPENING)
        {
            TowerDefense.op -> draw();
            if(TowerDefense.op -> operate())
            {
                sounds.at("SelectSFX") -> play();
            }
			sounds.at("TitleBackMusic") -> play();
            //如果焦点在START上, 同时Z键被按下
            if(TowerDefense.op -> getFocus() == 0 && TowerDefense.getKeyState(KEY_INPUT_Z) == PRESS)
            {
                sounds.at("ChooseSFX") -> play();
                TowerDefense.setState(SLLOADING);
				sounds.at("TitleBackMusic") -> stop();
            }
            //如果焦点在VS START上, 同时Z键被按下
            else if(TowerDefense.op -> getFocus() == 1 && TowerDefense.getKeyState(KEY_INPUT_Z) == PRESS)
            {
                sounds.at("ChooseSFX") -> play();
                TowerDefense.setState(DBLOADING);
				sounds.at("TitleBackMusic") -> stop();
            }
            else if(TowerDefense.op -> getFocus() == 2 && TowerDefense.getKeyState(KEY_INPUT_Z) == PRESS)
            {
                sounds.at("ChooseSFX") -> play();
				TowerDefense.setState(SETTINGS);
            }
            //如果焦点在QUIT上, 同时Z键被按下, 退出
            else if(TowerDefense.op -> getFocus() == TowerDefense.op -> getChoiceNum() - 1 && (TowerDefense.getKeyState(KEY_INPUT_Z) == PRESS || TowerDefense.getKeyState(KEY_INPUT_ESCAPE) == PRESS || TowerDefense.getKeyState(KEY_INPUT_X) == PRESS))
            {
                sounds.at("CancelSFX") -> play();
                TowerDefense.setState(QUIT);
				sounds.at("TitleBackMusic") -> stop();
            }
            //如果按下ESC
            if(TowerDefense.getKeyState(KEY_INPUT_ESCAPE) == PRESS || TowerDefense.getKeyState(KEY_INPUT_X) == PRESS)
            {
				TowerDefense.op -> setFocus(TowerDefense.op -> getChoiceNum() - 1);
                sounds.at("CancelSFX") -> play();
            }
        }
        //单人游戏加载
        else if(nowGameState == SLLOADING)
        {
            //清零帧计数器
            stageCounter = 0ull;
            TowerDefense.nowLevelCount = 0;

            //清零地图
            TowerDefense.clearMap();
            //读取地图
            TowerDefense.readMap("SoloLevel1", 8, 6, "../LevelScript/SoloLevel1.map");
            TowerDefense.readMap("SoloLevel2", 8, 6, "../LevelScript/SoloLevel2.map");

            //构建LevelMap对象
			LevelMap* map1 = new LevelMap(mapBlocksPic, levelMaps.at("SoloLevel1"), 8, 6, 0, 0);
            LevelMap* map2 = new LevelMap(mapBlocksPic, levelMaps.at("SoloLevel2"), 8, 6, 0, 0);

            //构建关卡玩家
            //塔图片
            int T0[3] = { pics.at("Arrow"),pics.at("Gun"), pics.at("Magic") };
            //子弹图片
            int B0[3] = { pics.at("ArrowBullet"),pics.at("GunBullet"), pics.at("MagicBullet") };
            //建造所需金钱
			int b[3] = { 30,40,50 };
            //升级所需金钱
			int u[3] = { 40,50,60 };
			Player* p1 = new Player(100, 70, pics.at("BloodBar"), pics.at("Blood"), pics.at("Coin"), pics.at("RITIC"), sounds);
			p1 -> initTower(T0, T0, B0, B0, b, u, pics.at("littleSet"), pics.at("littleUp"), pics.at("bigSet"), pics.at("bigUp"), pics.at("lack"), pics.at("redRec"), pics.at("greenRec"), pics.at("warning"));

            Player* p2 = new Player(200, 150, pics.at("BloodBar"), pics.at("Blood"), pics.at("Coin"), pics.at("RITIC"), sounds);
			p2 -> initTower(T0, T0, B0, B0, b, u, pics.at("littleSet"), pics.at("littleUp"), pics.at("bigSet"), pics.at("bigUp"), pics.at("lack"), pics.at("redRec"), pics.at("greenRec"), pics.at("warning"));


            //构建关卡对象
			TowerDefense.levels.push_back(new SoloLevel(p1, pics.at("Enemy1"), map1, stageCounter, sounds, 0, 2));
            TowerDefense.levels.push_back(new SoloLevel(p2, pics.at("Enemy2"), map2, stageCounter, sounds, 0, 4));

            //读取敌人数据
            TowerDefense.levels.at(0) -> readEnemy("../LevelScript/SoloLevel1.enm");
            TowerDefense.levels.at(1) -> readEnemy("../LevelScript/SoloLevel2.enm");


            TowerDefense.levels.at(0) -> setState(PLAYING);
            //开始游戏
            TowerDefense.setState(SOLOGAME);
        }
        //单人游戏
        else if(nowGameState == SOLOGAME)
        {
            DrawGraph(0, 0, pics.at("LevelBack"), TRUE);
			sounds.at("LevelBackMusic") -> play();

            LevelState nowLevelState = TowerDefense.levels.at(TowerDefense.nowLevelCount) -> getState();
            if(nowLevelState == PLAYING)
            {
                TowerDefense.levels.at(TowerDefense.nowLevelCount) -> draw();
                TowerDefense.levels.at(TowerDefense.nowLevelCount) -> update();
                DrawFormatStringToHandle(420, 720, GetColor(255, 255, 255), settingFont, "Level:%d", TowerDefense.nowLevelCount + 1);
            }
            else if(nowLevelState == WIN)
            {
                //最后一关赢了
                if (TowerDefense.levels.at(TowerDefense.levels.size() - 1) -> getState() == WIN)
                {
                    TowerDefense.setState(GAMEWIN);
                    for(unsigned int i = 0; i < TowerDefense.levels.size(); i++)
                    {
                        delete TowerDefense.levels.at(i);
                    }
                    TowerDefense.levels.clear();
                    TowerDefense.nowLevelCount = 0;
                    continue;
                }
                TowerDefense.setState(LEVELWIN);
                stageCounter = 0ull;
            }
            else if(nowLevelState == LOSE)
            {
				TowerDefense.setState(GAMELOSE);
                for(unsigned int i = 0; i < TowerDefense.levels.size(); i++)
                {
                    delete TowerDefense.levels.at(i);
                }
                TowerDefense.levels.clear();
                TowerDefense.nowLevelCount = 0;
            }
			if (TowerDefense.getKeyState(KEY_INPUT_ESCAPE) == PRESS || TowerDefense.getKeyState(KEY_INPUT_X) == PRESS)
			{
                sounds.at("CancelSFX") -> play();
				TowerDefense.setState(OPENING);
				sounds.at("LevelBackMusic") -> stop();

                for(unsigned int i = 0; i < TowerDefense.levels.size(); i++)
                {
                    delete TowerDefense.levels.at(i);
                }
				TowerDefense.levels.clear();
                TowerDefense.nowLevelCount = 0;
			}
			stageCounter++;
        }
        //双人游戏加载
        else if(nowGameState == DBLOADING)
        {
            //TODO
			//TowerDefense.levels.push_back(new DoubleLevel(new LevelMap(mapBlocksPic, doubleGameMap, 8, 6, 0, 0)));
            stageCounter = 0ull;
            TowerDefense.setState(DOUBLEGAME);
        }
        //双人游戏
        else if(nowGameState == DOUBLEGAME)
        {
            //TODO
			DrawGraph(0, 0, pics.at("LevelBack"), TRUE);
			sounds.at("LevelBackMusic") -> play();
            DrawStringToHandle(400, 350, "Developing...", GetColor(255, 255, 255), settingFont);
            //TowerDefense.levels.at(0) -> draw();
            //delete TowerDefense.levels.at(0);
			//TowerDefense.levels.clear();
            //TowerDefense.nowLevelCount = 0;
            if(TowerDefense.getKeyState(KEY_INPUT_ESCAPE) == PRESS || TowerDefense.getKeyState(KEY_INPUT_X) == PRESS)
            {
                sounds.at("CancelSFX") -> play();
                TowerDefense.setState(OPENING);
				sounds.at("LevelBackMusic") -> stop();
            }
        }
        else if(nowGameState == LEVELWIN)
        {
            DrawGraph(0, 0, pics.at("LevelBack"), TRUE);
            DrawStringToHandle(400, 300, "LEVEL WIN!", GetColor(255, 255, 255), settingFont);
            DrawStringToHandle(300, 400, "PRESS Z TO CONTINUE", GetColor(255, 255, 255), settingFont);
            if(TowerDefense.getKeyState(KEY_INPUT_Z) == PRESS)
            {
                TowerDefense.nowLevelCount++;
                sounds.at("ChooseSFX") -> play();
                TowerDefense.setState(SOLOGAME);
                TowerDefense.levels.at(TowerDefense.nowLevelCount) -> setState(PLAYING);
            }
            //退出
            if (TowerDefense.getKeyState(KEY_INPUT_ESCAPE) == PRESS || TowerDefense.getKeyState(KEY_INPUT_X) == PRESS)
			{
                sounds.at("CancelSFX") -> play();
				TowerDefense.setState(OPENING);
				sounds.at("LevelBackMusic") -> stop();

                for(unsigned int i = 0; i < TowerDefense.levels.size(); i++)
                {
                    delete TowerDefense.levels.at(i);
                }
				TowerDefense.levels.clear();
                TowerDefense.nowLevelCount = 0;
			}
        }
        //游戏胜利
        else if(nowGameState == GAMEWIN)
        {
            //TODO
            DrawGraph(0, 0, pics.at("LevelBack"), TRUE);
            DrawStringToHandle(420, 300, "YOU WIN!", GetColor(255, 255, 255), settingFont);
            DrawStringToHandle(320, 400, "PRESS Z TO ENDING", GetColor(255, 255, 255), settingFont);
            if(TowerDefense.getKeyState(KEY_INPUT_Z) == PRESS)
            {
                sounds.at("CancelSFX") -> play();
                TowerDefense.setState(EDLOADING);
                sounds.at("LevelBackMusic") -> stop();
            }
        }
        //游戏失败
        else if(nowGameState == GAMELOSE)
        {
            //TODO
            DrawGraph(0, 0, pics.at("LevelBack"), TRUE);
            DrawStringToHandle(400, 300, "YOU LOSE...", GetColor(255, 255, 255), settingFont);
            DrawStringToHandle(350, 400, "PRESS Z TO QUIT", GetColor(255, 255, 255), settingFont);
            if(TowerDefense.getKeyState(KEY_INPUT_Z) == PRESS)
            {
                sounds.at("CancelSFX") -> play();
                TowerDefense.setState(OPENING);
				sounds.at("LevelBackMusic") -> stop();
            }
        }
        //设置
        else if(nowGameState == SETTINGS)
        {
            DrawGraph(0, 0, pics.at("TitleBack"), TRUE);
            DrawStringToHandle(150, 450, "VOLUME", GetColor(255, 200, 150), settingFont);
            DrawFormatStringToHandle(500, 450, GetColor(255, 255, 255), settingFont, "%d%%", TowerDefense.getVolume());
            if(TowerDefense.getKeyState(KEY_INPUT_LEFT) == PRESS || TowerDefense.getKeyState(KEY_INPUT_DOWN) == PRESS)
            {
                TowerDefense.changeVolume(false); 
                sounds.at("SelectSFX") -> play();
            }
            else if(TowerDefense.getKeyState(KEY_INPUT_RIGHT) == PRESS || TowerDefense.getKeyState(KEY_INPUT_UP) == PRESS)
            {
                TowerDefense.changeVolume(true);
                sounds.at("SelectSFX") -> play();
            }
			if (TowerDefense.getKeyState(KEY_INPUT_ESCAPE) == PRESS || TowerDefense.getKeyState(KEY_INPUT_X) == PRESS)
			{
                sounds.at("CancelSFX") -> play();
				TowerDefense.setState(OPENING);
			}
        }
        //结尾加载
        else if(nowGameState == EDLOADING)
        {
			endingCounter = 0ull;
			TowerDefense.ed = new Ending(pics.at("EndingBack"), endingCounter);
			TowerDefense.ed -> addPic(0, new MovingPic(1030.0f, 250.0f, -500, 0, 1050, 800, pics.at("Staff0"), -1.3f, 0));
            TowerDefense.ed -> addPic(400, new MovingPic(1030.0f, 250.0f, -500, 0, 1050, 800, pics.at("Staff1"), -1.3f, 0));
            TowerDefense.ed -> addPic(800, new MovingPic(1030.0f, 250.0f, -500, 0, 1050, 800, pics.at("Staff2"), -1.3f, 0));
            TowerDefense.ed -> addPic(1200, new MovingPic(1030.0f, 250.0f, -500, 0, 1050, 800, pics.at("Staff3"), -1.3f, 0));
            TowerDefense.ed -> addPic(1600, new MovingPic(1030.0f, 250.0f, -500, 0, 1050, 800, pics.at("Staff4"), -1.3f, 0));
            TowerDefense.ed -> addPic(2000, new MovingPic(1030.0f, 200.0f, -1000, 0, 1050, 800, pics.at("Staff5"), -1.3f, 0));
            
            TowerDefense.setState(ENDING);
        }
        //结尾
        else if(nowGameState == ENDING)
        {
			sounds.at("EndingBackMusic") -> play();
			if (TowerDefense.getKeyState(KEY_INPUT_ESCAPE) == PRESS || TowerDefense.getKeyState(KEY_INPUT_Z) == PRESS)
			{
                sounds.at("CancelSFX") -> play();
				TowerDefense.setState(OPENING);
				sounds.at("EndingBackMusic") -> stop();
			}
			TowerDefense.ed -> draw();
            DrawStringToHandle(350, 720, "PRESS Z TO QUIT", GetColor(255, 255, 255), settingFont);
			endingCounter++;
        }
        //退出
        else if(nowGameState == QUIT)
        {
            break;
        }
        ScreenFlip();
        if (TowerDefense.getKeyState(KEY_INPUT_P) == PRESS)
        {
            DATEDATA Date;
            GetDateTime(&Date);
            char sp_path[64];
            sprintf_s(sp_path, "../ScreenShot/TowerDefense %d.%d.%d %d_%d_%d.bmp", Date.Year, Date.Mon, Date.Day, Date.Hour, Date.Min, Date.Sec);
            SaveDrawScreen(0, 0, SCREEN_X, SCREEN_Y, sp_path);
        }
        //fps锁定在50
		WaitTimer(20);
    }

    unsigned int size = unsigned int(mapBlocksPic.size());
    for(unsigned int i = 0; i < size; i++)
    {
        DeleteGraph(mapBlocksPic.at(i));
    }
    //结束
    DxLib_End();
    return 0;
}