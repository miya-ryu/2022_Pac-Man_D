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
	//	SceneMgr_ChangeScene(eScene_Game); //�V�[�����Q�[����ʂɕύX
	//	DeleteGraph(title);
	//}
	if (CheckHitKey(KEY_INPUT_SPACE) != 0) { //Z�L�[��������Ă�����
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