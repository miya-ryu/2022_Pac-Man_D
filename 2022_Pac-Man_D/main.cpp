#include "DxLib.h"
#include "Input.h"
#include "SceneMgr.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetMainWindowText("PAC-MAN");   //�^�C�g����ݒ�
	ChangeWindowMode(TRUE);         //�E�B���h�E���[�h�ύX
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);    //�E�B���h�E�T�C�Y�ݒ�
	if (DxLib_Init() == -1) {       //DX���C�u����������
		return -1;                  //�G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);  //����ʐݒ�
	
	//���b�Z�[�W�����A��ʍ폜�A��ʍX�V
	while (ProcessMessage() == 0) {
		ClearDrawScreen();
		InputKey();        //����

		mGame.Game_Update();
		mGame.Game_Draw();

		ScreenFlip();
	}
	DxLib_End(); // DX���C�u�����I������
	return 0;
}