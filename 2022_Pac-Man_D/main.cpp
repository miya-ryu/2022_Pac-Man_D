#include "DxLib.h"
#include "Input.h"
#include "SceneMgr.h"
#include "system.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetMainWindowText("PAC-MAN");   //�^�C�g����ݒ�
	ChangeWindowMode(TRUE);         //�E�B���h�E���[�h�ύX
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);    //�E�B���h�E�T�C�Y�ݒ�
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);  //����ʐݒ�

	SceneMgr_Initialize();

	//���b�Z�[�W�����A��ʍ폜�A��ʍX�V
	while (ProcessMessage() == 0) {
		ClearDrawScreen();
		InputKey();        //����

		SceneMgr_Update();
		SceneMgr_Draw();

		// FPS�Œ�
		/*mSystem.Update();
		mSystem.Draw();
		mSystem.Wait();*/

		ScreenFlip();
	}
	SceneMgr_Finalize();

	DxLib_End(); // DX���C�u�����I������
	return 0;
}