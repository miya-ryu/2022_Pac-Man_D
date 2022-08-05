#include "DxLib.h"
#include "Input.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetMainWindowText("Drive_and_Avoid");   //�^�C�g����ݒ�
	ChangeWindowMode(TRUE);             //�E�B���h�E���[�h�ύX
	SetGraphMode(1280, 720, 32);
	DxLib_Init();                       // DX���C�u����������
	SetDrawScreen(DX_SCREEN_BACK);      //����ʐݒ�

	while (ProcessMessage() == 0) { //���b�Z�[�W����
		ClearDrawScreen(); //��ʏ���

		InputKey();        //����

		ScreenFlip();      //��ʍX�V
	}
	DxLib_End(); // DX���C�u�����I������
	//return 0;
}