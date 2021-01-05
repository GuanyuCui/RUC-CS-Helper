#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//一些DxLib初始设定
    //不输出Log文件
    SetOutApplicationLogValidFlag(FALSE);
    //窗口标题
    SetMainWindowText("My4DPlayground G.Cui @ INFO.RUC");
    //窗口模式
    ChangeWindowMode(TRUE);
    SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_NATIVE);
    //窗口大小和ColorBit
    SetGraphMode(SCREEN_X, SCREEN_Y, 16);
    //DxLib初始化
    if(DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0) return -1;
    SetDrawScreen(DX_SCREEN_BACK);

	ChangeLightTypeDir(VGet(0.0f, -1.0f, 0.0f));

	Game * My4DPlayGround = new Game("bgm.mp3");
	My4DPlayGround -> readObj("./obj.objects");	
	
    while(ProcessMessage() == 0)
    {
		//刷新屏幕
		ClearDrawScreen();

		My4DPlayGround -> process();

		ScreenFlip();
		//截图功能
		if (CheckHitKey(KEY_INPUT_P))
		{
			DATEDATA Date;
			GetDateTime(&Date);
			char sp_path[128] = {0} ;
			sprintf_s(sp_path, "./SnapShot/My4DPlayground %d.%d.%d %d_%d_%d.bmp", Date.Year, Date.Mon, Date.Day, Date.Hour, Date.Min, Date.Sec);
			SaveDrawScreen(0, 0, SCREEN_X, SCREEN_Y, sp_path);
		}
		//退出
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
		//60.0fps
		WaitTimer(int(1000 / FPS));
    }
	delete My4DPlayGround;
	//结束
	DxLib_End();
    return 0;
}