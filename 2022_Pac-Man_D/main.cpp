#include "DxLib.h"
#include "Input.h"
#include "SceneMgr.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetMainWindowText("PACMAN");   //�^�C�g����ݒ�
	ChangeWindowMode(TRUE);             //�E�B���h�E���[�h�ύX
	SetGraphMode(1280, 720, 32);
	DxLib_Init();                       // DX���C�u����������
	SetDrawScreen(DX_SCREEN_BACK);      //����ʐݒ�

	while (ProcessMessage() == 0) { //���b�Z�[�W����
		ClearDrawScreen(); //��ʏ���

		InputKey();        //����
		mGame.Game_Draw();

		ScreenFlip();      //��ʍX�V
	}
	DxLib_End(); // DX���C�u�����I������
	//return 0;
}