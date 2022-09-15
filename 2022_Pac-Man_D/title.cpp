#include "DxLib.h"
#include "title.h"
#include "Input.h"
#include "SceneMgr.h"
#define Scroll_Speed -10;		//�X�N���[���@�X�s�[�h

Title mTitle;

void Title::Title_Initialize() {
	title = LoadGraph("images/title/title.png");
}

void Title::Title_Update() {
	if (iNowKey & PAD_INPUT_8 || CheckHitKey(KEY_INPUT_SPACE)) { //start�{�^����������Ă�����
		switch (MenuNumber) { //�V�[���ɂ���ď����𕪊�
		case 0: //���݂̉�ʂ����j���[�Ȃ�
			SceneMgr_ChangeScene(eScene_Game); //�V�[�����Q�[����ʂɕύX
			break;
		case 1:
			SceneMgr_ChangeScene(eScene_End); //�V�[�����G���h��ʂɕύX
			break;
		}
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