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
	//	SceneMgr_ChangeScene(eScene_Game); //�V�[�����Q�[����ʂɕύX
	//	DeleteGraph(title);
	//}
	if (iNowKey & PAD_INPUT_START || CheckHitKey(KEY_INPUT_SPACE)) { //start�{�^����������Ă�����
		switch (MenuNumber) { //�V�[���ɂ���ď����𕪊�
		case 0: //���݂̉�ʂ����j���[�Ȃ�
			SceneMgr_ChangeScene(eScene_Game); //�V�[�����Q�[����ʂɕύX
			break;
		case 1:
			SceneMgr_ChangeScene(eScene_End); //�V�[�����Q�[����ʂɕύX
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