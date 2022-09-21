#include "DxLib.h"
#include "title.h"
#include "Input.h"
#include "SceneMgr.h"
#include "Stage.h"
#include "Game.h"
#define Scroll_Speed -10;		//スクロール　スピード

Title mTitle;

void Title::Title_Initialize() {
	TitleY = 720;
	title = LoadGraph("images/title/title.png");
}

void Title::Title_Update() {
	if (iNowKey & PAD_INPUT_8) { //startボタンが押されていたら
		mGame.Game_Initialize();
		//mStage.GameOverFlg = FALSE;
		SceneMgr_ChangeScene(eScene_Game); //シーンをゲーム画面に変更
	}
}

void Title::Title_Draw() {
	DrawGraph(0, TitleY, title, false);
}

void Title::Title_Finalize() {
	DeleteGraph(title);
}

void Title::Title_Move() {			//スクロール処理
	if (TitleY != 0) {
		TitleY += Scroll_Speed;
	}
}