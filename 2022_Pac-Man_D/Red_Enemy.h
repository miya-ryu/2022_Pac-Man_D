#pragma once

// 親クラス赤
class R_ENEMY {
private:

public:
	R_ENEMY();   // c言語のInitializeと同じ処理
	~R_ENEMY();  // c言語のFInalizeと同じ処理
	void Update();
	void Draw();

	// 敵の画像保管配列
	static const int MaxImage = 20;
	static const int MaxEyeImage = 4;
	int images[MaxImage];
	int eyesimages[MaxEyeImage];
	int image, eyeimage;
	// 敵に関する変数
	int x, y, x1, y1;
	int speed;
	int direction;
	int count;
	int num;
};

extern R_ENEMY r_enemy;