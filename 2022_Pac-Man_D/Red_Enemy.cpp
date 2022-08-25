#include "DxLib.h"
#include "Red_Enemy.h"
#include "Player.h"
#include "Stage.cpp"

R_ENEMY r_enemy;

R_ENEMY::R_ENEMY() {
	r_enemy.x = 140;        // 初期位置縦
	r_enemy.y = 360;        // 初期位置横
	r_enemy.speed = 1;      // 移動速度
	r_enemy.directionX = 0; // X方向
	r_enemy.directionY = 0; // Y方向
	r_enemy.count = 0;      // アニメーションカウント
	r_enemy.image = 0;      // 画像変数
	r_enemy.eyeimage = 0;   // 目の画像変数
	r_enemy.num = 0;

	r_enemy.x = ENEMY_POS_X;
	r_enemy.y = ENEMY_POS_Y;
	
	r_enemy.top = ENEMY_POS_X + ENEMY_POS_HITBOX;
	r_enemy.left= ENEMY_POS_Y + ENEMY_POS_HITBOX;
	r_enemy.right = ENEMY_POS_X - ENEMY_POS_HITBOX;
	r_enemy.bottom = ENEMY_POS_Y - ENEMY_POS_HITBOX;

}

R_ENEMY::~R_ENEMY() {
	//DeleteGraph(images[0]);
}

void R_ENEMY::Update() {


	// プレイヤーを追いかける処理
	if (mPlayer.x >= r_enemy.x + 1) {       // 右向き
		r_enemy.x += r_enemy.speed;
		r_enemy.eyeimage = 1;
	}
	else if (mPlayer.x <= r_enemy.x - 1) {  // 左向き
		r_enemy.x -= r_enemy.speed;
		r_enemy.eyeimage = 3;
	}
	if (mPlayer.y >= r_enemy.y + 1) {       // 下向き
		r_enemy.y += r_enemy.speed;
		r_enemy.eyeimage = 2;
	}
	else if (mPlayer.y <= r_enemy.y - 1) {  // 上向き
		r_enemy.y -= r_enemy.speed;
		r_enemy.eyeimage = 0;
	}

	for (int j = 0; j < ENEMY_POS_X; j++) {
		for (int i = 0; i < ENEMY_POS_X; i++) {

			if (CheckHit(i * ENEMY_POS_X, j * ENEMY_POS_Y, ENEMY_POS_X, ENEMY_POS_Y, r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom))
			{
				//移動
				r_enemy.x = r_enemy.recordX;
				r_enemy.y = r_enemy.recordY;

				//当たり判定移動
				r_enemy.top = r_enemy.recordTop;
				r_enemy.right = r_enemy.recordRight;
				r_enemy.bottom = r_enemy.recordBottom;
				r_enemy.left = r_enemy.recordLeft;
			}

			// アニメーション
			++count;  // カウント開始
			if (count >= 8) {  // 値によってアニメーションのスピードが変化する0に近い程速い
				r_enemy.image++;
				count = 0;  // カウントリセット
			}
			if (r_enemy.image >= 2) { // 画像の切り替え
				r_enemy.image = 0;    // 画像リセット
			}

			// ワープトンネル
			if (r_enemy.x >= 1280) {
				r_enemy.x = 0;
			}
			else if (r_enemy.x <= 0) {
				r_enemy.x = 1280;
			}
		}
	}
}

	int	CheckHit(int EnemyX, int EnemyY, int w1, int h1, int x, int y, int w, int h)
	{
		int L1 = EnemyX;	  //右
		int R1 = EnemyX + w1; //左
		int L2 = x;
		int R2 = x + w;

		if (R1 < L2) return 0;
		if (R2 < L1) return 0;

		int U1 = EnemyY;      // 上
		int D1 = EnemyY + h1; // 下(上+縦幅)
		int U2 = x;
		int D2 = x + w;

		if (D1 < U2) return 0;
		if (D2 < U1) return 0;


		return 1;

	}

	void R_ENEMY::Draw() {
		LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);  // 敵キャラ
		LoadDivGraph("images/eyes.png", 4, 4, 1, 32, 32, eyesimages);  // 敵キャラの目
		DrawRotaGraph(r_enemy.x, r_enemy.y, 1, 0, images[r_enemy.image], TRUE, FALSE);  // 敵キャラ表示
		DrawRotaGraph(r_enemy.x, r_enemy.y, 1, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE);  // 敵キャラの目表示
		DrawBox(r_enemy.x, r_enemy.y, r_enemy.x, r_enemy.y, 0x00ff00, FALSE);
	}

