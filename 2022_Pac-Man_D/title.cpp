#include "DxLib.h"
#include "title.h"
#include "Input.h"
#include "SceneMgr.h"

Title mTitle;
int count = 0;

void Title::Title_Initialize() {
	title = LoadGraph("images/title/title.png");
}

void Title::Title_Update() {
	//if (CheckHitKey(KEY_INPUT_SPACE) != 0) {
	//	SceneMgr_ChangeScene(eScene_Game); //シーンをゲーム画面に変更
	//	DeleteGraph(title);
	//}
	if (iNowKey & PAD_INPUT_START || CheckHitKey(KEY_INPUT_SPACE)) { //startボタンが押されていたら
		switch (MenuNumber) { //シーンによって処理を分岐
		case 0: //現在の画面がメニューなら
			SceneMgr_ChangeScene(eScene_Game); //シーンをゲーム画面に変更
			break;
		case 1:
			SceneMgr_ChangeScene(eScene_End); //シーンをゲーム画面に変更
			break;
		}
	}
}

void Title::Title_Draw() {
	DrawGraph(0, 0, title, false);
}

void Title::Title_Finalize() {
	DeleteGraph(title);
}