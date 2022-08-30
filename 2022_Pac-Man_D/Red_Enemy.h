#pragma once

static int ENEMY_POS_X = 100;
static int ENEMY_POS_Y = 100;
static int ENEMY_CENTER_HITBOX = 4;

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
	int directionX;
	int directionY;
	int recordX, recordY;
	int top, right, bottom, left;	//当たり判定
	int recordTop, recordRight, recordBottom, recordLeft;
	int count;
	int num;
	int Enemy_image[20];
	// 敵の座標を保管する変数
	int w, h;	// 幅 w 高さ h;
	int CheckHit;
	//int HitBoxEnemy(R_ENEMY* e);
};

extern R_ENEMY r_enemy;