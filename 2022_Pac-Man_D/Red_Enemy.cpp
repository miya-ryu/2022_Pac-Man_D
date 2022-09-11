#include "DxLib.h"
#include "Red_Enemy.h"
#include "Player.h"

R_ENEMY r_enemy;

int EnemeyCheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	int L1 = x1;		//左
	int R1 = w1;		//右
	int L2 = x2;		//左
	int R2 = w2;		//右

	if (R1 < L2) return 0;
	if (R2 < L1) return 0;

	int U1 = y1;		//上
	int D1 = h1;		//下
	int U2 = y2;		//上
	int D2 = h2;		//下

	if (D1 < U2) return 0;
	if (D2 < U1) return 0;

	//当たっている
	return 1;
}

void R_ENEMY::Initialize() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);  // 敵キャラ
	LoadDivGraph("images/eyes.png", 4, 4, 1, 32, 32, eyesimages);  // 敵キャラの目

	r_enemy.speed = 1;             // 移動速度
	r_enemy.count = 0;             // アニメーションカウント
	r_enemy.E_count = 0;           // イジケ状態カウント
	r_enemy.image = 0;             // 画像変数
	r_enemy.eyeimage = 0;          // 目の画像変数
	r_enemy.izikeimage = 16;       // イジケ状態の画像変数
	r_enemy.e_izikeimage = 16;     // イジケ状態点滅の画像変数
	r_enemy.E_StageHitflg = FALSE; // 壁との当たり判定フラグ
	r_enemy.E_EnemeyHitflg = FALSE;// プレイヤーとエネミーの当たり判定フラグ
	r_enemy.R_Hitflg = FALSE;      // イジケ状態判定フラグ
	r_enemy.ER_Hitflg = FALSE;     // イジケ状態点滅フラグ

	r_enemy.x = ENEMY_POS_X;
	r_enemy.y = ENEMY_POS_Y;

	// 初期の向き
	r_enemy.angle = 3;

	//当たり判定
	r_enemy.recordX = r_enemy.x;
	r_enemy.recordY = r_enemy.y;

	r_enemy.top = ENEMY_POS_Y - ENEMY_STAGE_HITBOX;
	r_enemy.left = ENEMY_POS_X - ENEMY_STAGE_HITBOX;
	r_enemy.right = ENEMY_POS_X + ENEMY_STAGE_HITBOX;
	r_enemy.bottom = ENEMY_POS_Y + ENEMY_STAGE_HITBOX;

	r_enemy.recordTop = r_enemy.top;
	r_enemy.recordRight = r_enemy.right;
	r_enemy.recordBottom = r_enemy.bottom;
	r_enemy.recordLeft = r_enemy.left;
}

void R_ENEMY::Update() {
	//前回の座標取得
	r_enemy.recordX = r_enemy.x;
	r_enemy.recordY = r_enemy.y;

	r_enemy.recordTop = r_enemy.top;
	r_enemy.recordRight = r_enemy.right;
	r_enemy.recordBottom = r_enemy.bottom;
	r_enemy.recordLeft = r_enemy.left;

	// プレイヤーを追いかける処理
	if (r_enemy.R_Hitflg == FALSE) { // パワーエサを取っていない時
		//右向き
		if (angle == 1) {
			r_enemy.x += r_enemy.speed;

			//当たり判定
			r_enemy.left += r_enemy.speed;
			r_enemy.right += r_enemy.speed;

			r_enemy.eyeimage = 1;
		}
		//下向き
		else if (angle == 2) {
			r_enemy.y += r_enemy.speed;

			//当たり判定
			r_enemy.top += r_enemy.speed;
			r_enemy.bottom += r_enemy.speed;

			r_enemy.eyeimage = 2;
		}
		//左向き
		else if (angle == 3) {
			r_enemy.x -= r_enemy.speed;

			r_enemy.left -= r_enemy.speed;
			r_enemy.right -= r_enemy.speed;

			r_enemy.eyeimage = 3;
		}
		//上向き
		else if (angle == 4) {
			r_enemy.y -= r_enemy.speed;

			//当たり判定
			r_enemy.top -= r_enemy.speed;
			r_enemy.bottom -= r_enemy.speed;

			r_enemy.eyeimage = 0;
		}
	}
	else if (r_enemy.R_Hitflg == TRUE) { // パワーエサを取った時
		//右向き
		if (angle == 1) {
			r_enemy.x -= r_enemy.speed;

			//当たり判定
			r_enemy.left -= r_enemy.speed;
			r_enemy.right -= r_enemy.speed;
		}
		//下向き
		else if (angle == 2) {
			r_enemy.y -= r_enemy.speed;

			//当たり判定
			r_enemy.top -= r_enemy.speed;
			r_enemy.bottom -= r_enemy.speed;
		}
		//左向き
		else if (angle == 3) {
			r_enemy.x += r_enemy.speed;

			r_enemy.left += r_enemy.speed;
			r_enemy.right += r_enemy.speed;
		}
		//上向き
		else if (angle == 4) {
			r_enemy.y += r_enemy.speed;

			//当たり判定
			r_enemy.top += r_enemy.speed;
			r_enemy.bottom += r_enemy.speed;
		}
	}

	// プレイヤーとエネミーの当たり判定
	if (EnemeyCheckHit(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom)) {
		r_enemy.E_EnemeyHitflg = TRUE;
	}

	// アニメーション
	++count;  // カウント開始
	if (count >= 8) {  // 値によってアニメーションのスピードが変化する0に近い程速い
		r_enemy.image++;
		r_enemy.izikeimage++;
		r_enemy.e_izikeimage++;
		count = 0;  // カウントリセット
	}
	if (r_enemy.R_Hitflg == FALSE) { // もしイジケ状態でなければ
		if (r_enemy.image >= 2) { // 通常の画像切り替え
			r_enemy.image = 0;    // 画像リセット
		}
	}
	else if (r_enemy.R_Hitflg == TRUE) { // もしイジケ状態なら
		if (r_enemy.izikeimage >= 18) { // イジケ画像切り替え
			r_enemy.izikeimage = 16; // 画像リセット
		}
	}
	if (r_enemy.ER_Hitflg == TRUE) { // もしイジケ状態が終わりそうなら
		if (r_enemy.e_izikeimage >= 20) { // イジケ点滅画像切り替え
			r_enemy.e_izikeimage = 16; // 画像リセット
		}
	}

	// ワープトンネル
	if (r_enemy.x >= 1280) {
		r_enemy.x = 0;
	}
	else if (r_enemy.x <= 0) {
		r_enemy.x = 1280;
	}

	// イジケ状態フラグ
	if (r_enemy.R_Hitflg == TRUE) {
		++E_count;
	}
}

void R_ENEMY::Draw() {
	if (r_enemy.R_Hitflg == FALSE) {
		if (r_enemy.E_EnemeyHitflg == FALSE) {
			DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[r_enemy.image], TRUE, FALSE);  // 敵キャラ表示
			DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE);  // 敵キャラの目表示
			DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE);
		}
	}
	else if (r_enemy.R_Hitflg == TRUE) {
		if (E_count <= 480) {
			DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[r_enemy.izikeimage], TRUE, FALSE);  // イジケ状態表示
			DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE);
		}
		else if (E_count > 480 && E_count <= 600) {
			ER_Hitflg = TRUE;
			DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[r_enemy.e_izikeimage], TRUE, FALSE);  // イジケ状態表示
			DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE);
		}
		else {
			r_enemy.R_Hitflg = FALSE;
			E_count = 0;
		}
	}
}