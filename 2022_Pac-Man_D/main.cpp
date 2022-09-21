#include "DxLib.h"
#include "Input.h"
#include "SceneMgr.h"
#include <math.h>

class Fps {
	int mStartTime;         //����J�n����
	int mCount;             //�J�E���^
	float mFps;             //fps
	static const int N = 60;//���ς����T���v����
	static const int FPS = 60;	//�ݒ肵��FPS

public:
	Fps() {
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}

	bool Update() {
		if (mCount == 0) { //1�t���[���ڂȂ玞�����L��
			mStartTime = GetNowCount();
		}
		if (mCount == N) { //60�t���[���ڂȂ畽�ς��v�Z����
			int t = GetNowCount();
			mFps = 1000.f / ((t - mStartTime) / (float)N);
			mCount = 0;
			mStartTime = t;
		}
		mCount++;
		return true;
	}

	void Draw() {
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", mFps);
	}

	void Wait() {
		int tookTime = GetNowCount() - mStartTime;	//������������
		int waitTime = mCount * 1000 / FPS - tookTime;	//�҂ׂ�����
		if (waitTime > 0) {
			Sleep(waitTime);	//�ҋ@
		}
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetMainWindowText("PAC-MAN");   //�^�C�g����ݒ�
	ChangeWindowMode(TRUE);         //�E�B���h�E���[�h�ύX
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);    //�E�B���h�E�T�C�Y�ݒ�
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);  //����ʐݒ�

	SceneMgr_Initialize();
	Fps fps;

	//���b�Z�[�W�����A��ʍ폜�A��ʍX�V
	while (ClearDrawScreen() == 0 && ProcessMessage() == 0) {
		InputKey();        //����
		SceneMgr_Update();
		SceneMgr_Draw();
		fps.Update();	//�X�V
		fps.Draw();		//�`��

		ScreenFlip();
		fps.Wait();		//�ҋ@
	}
	SceneMgr_Finalize();

	DxLib_End(); // DX���C�u�����I������
	return 0;
}