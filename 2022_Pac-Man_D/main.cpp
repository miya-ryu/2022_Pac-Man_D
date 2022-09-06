#include "DxLib.h"
#include "Input.h"
#include "SceneMgr.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetMainWindowText("PAC-MAN");   //タイトルを設定
	ChangeWindowMode(TRUE);         //ウィンドウモード変更
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);    //ウィンドウサイズ設定
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);  //裏画面設定

	SceneMgr_Initialize();
	//メッセージ処理、画面削除、画面更新
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		ClearDrawScreen();
		InputKey();        //入力

		SceneMgr_Update();
		SceneMgr_Draw();

		ScreenFlip();
	}
	SceneMgr_Finalize();

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}