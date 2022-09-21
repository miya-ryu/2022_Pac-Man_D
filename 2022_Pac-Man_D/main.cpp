#include "DxLib.h"
#include "Input.h"
#include "SceneMgr.h"
#include <math.h>

class Fps {
	int mStartTime;         //測定開始時刻
	int mCount;             //カウンタ
	float mFps;             //fps
	static const int N = 60;//平均を取るサンプル数
	static const int FPS = 60;	//設定したFPS

public:
	Fps() {
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}

	bool Update() {
		if (mCount == 0) { //1フレーム目なら時刻を記憶
			mStartTime = GetNowCount();
		}
		if (mCount == N) { //60フレーム目なら平均を計算する
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
		int tookTime = GetNowCount() - mStartTime;	//かかった時間
		int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
		if (waitTime > 0) {
			Sleep(waitTime);	//待機
		}
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetMainWindowText("PAC-MAN");   //タイトルを設定
	ChangeWindowMode(TRUE);         //ウィンドウモード変更
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);    //ウィンドウサイズ設定
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);  //裏画面設定

	SceneMgr_Initialize();
	Fps fps;

	//メッセージ処理、画面削除、画面更新
	while (ClearDrawScreen() == 0 && ProcessMessage() == 0) {
		InputKey();        //入力
		SceneMgr_Update();
		SceneMgr_Draw();
		fps.Update();	//更新
		fps.Draw();		//描画

		ScreenFlip();
		fps.Wait();		//待機
	}
	SceneMgr_Finalize();

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}