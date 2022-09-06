#include "DxLib.h"
#include "title.h"
#include "Input.h"
#include "SceneMgr.h"

Title mTitle;

void Title::Title_Initialize() {
	title = LoadGraph("images/title/title.png");
}

void Title::Title_Update() {
	//if (CheckHitKey(KEY_INPUT_SPACE) != 0) {
	//	SceneMgr_ChangeScene(eScene_Game); //シーンをゲーム画面に変更
	//	DeleteGraph(title);
	//}
	if (CheckHitKey(KEY_INPUT_SPACE) != 0) { //Zキーが押されていたら
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