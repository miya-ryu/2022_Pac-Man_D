#include "DxLib.h"
#include "Input.h"
#include "SceneMgr.h"
#include "Game.h"
#include "Red_Enemy.h"
#include "Pink_Enemy.h"
#include "Blue_Enemy.h"
#include "Orange_Enemy.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetMainWindowText("PAC-MAN");   //タイトルを設定
	ChangeWindowMode(TRUE);         //ウィンドウモード変更
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);    //ウィンドウサイズ設定
	if (DxLib_Init() == -1) {       //DXライブラリ初期化
		return -1;                  //エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);  //裏画面設定
	
	//メッセージ処理、画面削除、画面更新
	while (ProcessMessage() == 0) {
		ClearDrawScreen();
		InputKey();        //入力
		mGame.Game_Update();
		mGame.Game_Draw();

		r_enemy.Draw();
		/*p_enemy.Draw();
		b_enemy.Draw();
		o_enemy.Draw();*/

		ScreenFlip();
	}
	DxLib_End(); // DXライブラリ終了処理
	return 0;
}