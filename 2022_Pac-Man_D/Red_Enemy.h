#pragma once

static int ENEMY_POS_X = 612;
static int ENEMY_POS_Y = 252;
static float ENEMY_POS_HITBOX = 11;

// 親クラス赤
class R_ENEMY {
private:

public:
	void Initialize();
	void Update();
	void Draw();

	// 敵の画像保管配列
	static const int MaxImage = 20;
	static const int MaxEyeImage = 4;
	int images[MaxImage];
	int eyesimages[MaxEyeImage];
	int image, eyeimage, izikeimage, e_izikeimage;
	// 敵に関する変数
	int x, y, x1, y1;
	int angle;
	float speed;
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
	// イジケモンスター点滅状態
	bool ER_Hitflg;
	int ER_count;
	// イジケモンスターがプレイヤーに当たった状態
	bool PR_Hitflg;
	// エネミー目状態
	bool eyeflg;
	// 壁に当たったフラグ
	bool Initiaflg;
	// 座標計算
	int xy, xy2, xx, yy;
	// 分身処理
	int ENEMY_AVATAR_POS_X[4];
	int ENEMY_AVATAR_POS_Y[4];
	int avatar_top[4];
	int avatar_right[4];
	int avatar_left[4];
	int avatar_bottom[4];
	int record_avatar_top[4];
	int record_avatar_right[4];
	int record_avatar_left[4];
	int record_avatar_bottom[4];
	bool Left, Right, Top, Bottom;
	int CheckNumber;
	// プレイヤー死亡時のエネミーアニメーション
	int HitCount;
	int c;
	bool flg;		//pacに当たって敵を消すフラグ管理
};

extern R_ENEMY r_enemy;