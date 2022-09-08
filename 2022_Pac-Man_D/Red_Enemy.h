#pragma once

static int ENEMY_POS_X = 612;
static int ENEMY_POS_Y = 252;
static float ENEMY_STAGE_HITBOX = 11;

// 親クラス赤
class R_ENEMY {
private:

public:
	~R_ENEMY();  // c言語のFInalizeと同じ処理
	void R_Initialize();
	void Update();
	void Draw();

	// 敵の画像保管配列
	static const int MaxImage = 20;
	static const int MaxEyeImage = 4;
	int images[MaxImage];
	int eyesimages[MaxEyeImage];
	int image, eyeimage, Hitimage;
	// 敵に関する変数
	int x, y, x1, y1;
	int absX, absY;
	int angle;
	int speed;
	int recordX, recordY;
	//Playerとの当たり判定
	int top, right, bottom, left;
	int recordTop, recordRight, recordBottom, recordLeft;
	int count;
	// 敵の座標を保管する変数
	int w, h;	// 幅 w 高さ h;
	int CheckHit;
	// イジケモンスター状態
	bool R_Hitflg;
	//壁に当たったフラグ
	bool E_StageHitflg;
	//プレイヤーに当たった時
	bool E_EnemeyHitflg;
};

extern R_ENEMY r_enemy;