#include "DxLib.h"
#include <math.h>
#include "system.h"

System mSystem;

bool System::Update() {
	if (f_Count == 0) {  // 1フレーム目に時刻を記憶
		f_Time = GetNowCount();  // 現在のカウンタの値を取得
	}
	if (f_Count == F) {  // もし平均数値と同じなら
		int t = GetNowCount();  // tに現在のカウンタの値を代入
		f_Fps = 1000.f / ((t - f_Time) / (float)F);  // 
		f_Count = 0;  // カウンタを0にする
		f_Time = t;  // 測定開始時刻にtを代入
	}
	f_Count++;  // カウントを加算
	return true;
}
void System::Draw() {
	// FPSを表示
	DrawFormatString(950, 400, GetColor(255, 255, 255), "%.1f", f_Fps);
}
void System::Wait() {
	int tookTime = GetNowCount() - f_Time;  // かかった時間
	int waitTime = f_Count * 1000 / FPS - tookTime;  // 待つべき時間
	if (waitTime > 0) {  // 待つべき時間が0より大きければ
		Sleep(waitTime);  // 待機
	}
}