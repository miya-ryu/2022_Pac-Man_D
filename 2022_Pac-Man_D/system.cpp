#include "DxLib.h"
#include <math.h>
#include "system.h"

System mSystem;

void System::Initialize() {
	mSystem.f_StartTime = 0;
	mSystem.f_Count = 0;
	mSystem.f_Fps = 0;
}
void System::Update() {
	if (f_Count == 0) {  // 1フレーム目に時刻を記憶
		mSystem.f_StartTime = GetNowCount();  // 現在のカウンタの値を取得
	}
	if (f_Count == F) {  // もし平均数値と同じなら
		int t = GetNowCount();  // tに現在のカウンタの値を代入
		mSystem.f_Fps = 1000.f / ((t - mSystem.f_StartTime) / (float)F);  // 
		mSystem.f_Count = 0;  // カウンタを0にする
		mSystem.f_StartTime = t;  // 測定開始時刻にtを代入
	}
	mSystem.f_Count++;  // カウントを加算
}
void System::Draw() {
	// FPSを表示
	DrawFormatString(950, 400, GetColor(255, 255, 255), "%.1f", mSystem.f_Fps);
}
void System::Wait() {
	int tookTime = GetNowCount() - mSystem.f_StartTime;  // かかった時間
	int waitTime = mSystem.f_Count * 1000 / FPS - tookTime;  // 待つべき時間
	if (waitTime > 0) {  // 待つべき時間が0より大きければ
		Sleep(waitTime);  // 待機
		DrawString(950, 420, "成功", 0xffffff);
	}
}