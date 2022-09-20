#pragma once

class System {
private:

public:
	void Update();
	void Draw();
	void Wait();
	void Initialize();
	int f_StartTime;		//測定開始時刻
	int f_Count;			//カウント
	float f_Fps;			//fps

	const int F = 60;  // 平均用サンプル数値
	const int FPS = 60;  // FPS設定
};

extern System mSystem;