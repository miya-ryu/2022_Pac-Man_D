#include "DxLib.h"
#include "title.h"
#include "Input.h"
#include "SceneMgr.h"

Title mTitle;

void Title::Title_Initialize() {
	title = LoadGraph("images/title/title.png");
}

void Title::Title_Update() {
	if (iNowKey & PAD_INPUT_START || CheckHitKey(KEY_INPUT_SPACE)) { //start�{�^����������Ă�����
		switch (MenuNumber) { //�V�[���ɂ���ď����𕪊�
		case 0: //���݂̉�ʂ����j���[�Ȃ�
			SceneMgr_ChangeScene(eScene_Game); //�V�[�����Q�[����ʂɕύX
			break;
		case 1:
			SceneMgr_ChangeScene(eScene_End); //�V�[�����G���h��ʂɕύX
			break;
		}
	}

	int Titlecunt;

}

void Title::Title_Draw() {
	DrawGraph(0, 720, title, false);
}

void Title::Title_Finalize() {
	DeleteGraph(title);
}