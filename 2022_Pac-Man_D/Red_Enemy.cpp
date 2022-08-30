#include "DxLib.h"
#include "Red_Enemy.h"
#include "Player.h"

R_ENEMY r_enemy;

void R_ENEMY::R_Initialize() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);  // 敵キャラ
	LoadDivGraph("images/eyes.png", 4, 4, 1, 32, 32, eyesimages);  // 敵キャラの目

	r_enemy.speed = 1;      // 移動速度
	r_enemy.directionX = 0; // X方向
	r_enemy.directionY = 0; // Y方向
	r_enemy.count = 0;      // アニメーションカウント
	r_enemy.image = 0;      // 画像変数
	r_enemy.eyeimage = 0;   // 目の画像変数
	r_enemy.num = 0;

	r_enemy.x = ENEMY_POS_X;
	r_enemy.y = ENEMY_POS_Y;
	
	r_enemy.top = ENEMY_POS_Y - ENEMY_CENTER_HITBOX;
	r_enemy.left = ENEMY_POS_X - ENEMY_CENTER_HITBOX;
	r_enemy.right = ENEMY_POS_X + ENEMY_CENTER_HITBOX;
	r_enemy.bottom = ENEMY_POS_Y + ENEMY_CENTER_HITBOX;
}

R_ENEMY::~R_ENEMY() {
	//DeleteGraph(images[0]);
}

void R_ENEMY::Update() {
	// プレイヤーを追いかける処理
	if (mPlayer.x >= r_enemy.x + 1) {       // 右向き
		r_enemy.x += r_enemy.speed;
		r_enemy.left += r_enemy.speed;
		r_enemy.right += r_enemy.speed;
		r_enemy.eyeimage = 1;
	}
	else if (mPlayer.x <= r_enemy.x - 1) {  // 左向き
		r_enemy.x -= r_enemy.speed;
		r_enemy.left -= r_enemy.speed;
		r_enemy.right -= r_enemy.speed;
		r_enemy.eyeimage = 3;
	}
	if (mPlayer.y >= r_enemy.y + 1) {       // 下向き
		r_enemy.y += r_enemy.speed;
		r_enemy.top += r_enemy.speed;
		r_enemy.bottom += r_enemy.speed;
		r_enemy.eyeimage = 2;
	}
	else if (mPlayer.y <= r_enemy.y - 1) {  // 上向き
		r_enemy.y -= r_enemy.speed;
		r_enemy.top -= r_enemy.speed;
		r_enemy.bottom -= r_enemy.speed;
		r_enemy.eyeimage = 0;
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
    
void R_ENEMY::Draw() {
	DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[r_enemy.image], TRUE, FALSE);  // 敵キャラ表示
	DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE);  // 敵キャラの目表示
	DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE);
}
