#include "DxLib.h"
#include "title.h"
#include "Input.h"
#include "SceneMgr.h"
#include "Stage.h"
#include "Game.h"
#define Scroll_Speed -10;		//�X�N���[���@�X�s�[�h

Title mTitle;

void Title::Title_Initialize() {
	TitleY = 720;
	title = LoadGraph("images/title/title.png");
}

void Title::Title_Update() {
	if (iNowKey & PAD_INPUT_8) { //start�{�^����������Ă�����
		mGame.Game_Initialize();
		//mStage.GameOverFlg = FALSE;
		SceneMgr_ChangeScene(eScene_Game); //�V�[�����Q�[����ʂɕύX
	}
}

void Title::Title_Draw() {
	DrawGraph(0, TitleY, title, false);
}

void Title::Title_Finalize() {
	DeleteGraph(title);
}

void Title::Title_Move() {			//�X�N���[������
	if (TitleY != 0) {
		TitleY += Scroll_Speed;
	}
}