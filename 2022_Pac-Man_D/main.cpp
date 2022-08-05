#include "DxLib.h"
#include "Input.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetMainWindowText("Drive_and_Avoid");   //タイトルを設定
	ChangeWindowMode(TRUE);             //ウィンドウモード変更
	SetGraphMode(1280, 720, 32);
	DxLib_Init();                       // DXライブラリ初期化
	SetDrawScreen(DX_SCREEN_BACK);      //裏画面設定

	while (ProcessMessage() == 0) { //メッセージ処理
		ClearDrawScreen(); //画面消去

		InputKey();        //入力

		ScreenFlip();      //画面更新
	}
	DxLib_End(); // DXライブラリ終了処理
	//return 0;
}