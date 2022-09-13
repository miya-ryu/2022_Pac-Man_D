#pragma once

static int f_Time;  // 測定開始時刻
static int f_Count;  // カウンタ
static float f_Fps;  // fps

class System {
private:

public:
	bool Update();
	void Draw();
	void Wait();

	const int F = 60;  // 平均用サンプル数値
	const int FPS = 60;  // FPS設定
};

extern System mSystem;