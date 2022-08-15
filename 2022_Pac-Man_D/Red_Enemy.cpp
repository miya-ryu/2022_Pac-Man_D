#include "DxLib.h"
#include "Red_Enemy.h"
#include "Player.h"

R_ENEMY r_enemy;

R_ENEMY::R_ENEMY() {
	r_enemy.x = 140;       // 初期位置縦
	r_enemy.y = 360;       // 初期位置横
	r_enemy.speed = 2;     // 移動速度
	r_enemy.direction = 0; // 方向
	r_enemy.count = 0;     // アニメーションカウント
	r_enemy.image = 0;     // 画像変数
	r_enemy.eyeimage = 0;  // 目の画像変数
	r_enemy.num = 0;
}

R_ENEMY::~R_ENEMY() {
	//DeleteGraph(images[0]);
}

void R_ENEMY::Update() {
	/*if (r_enemy.x != mPlayer.x || r_enemy.y != mPlayer.y) {
		r_enemy.x += r_enemy.speed;
		r_enemy.y += r_enemy.speed;
		r_enemy.x = mPlayer.x;
		r_enemy.y = mPlayer.y;
	}
	else if (r_enemy.x == mPlayer.x || r_enemy.y == mPlayer.y) {
		DrawFormatString(100, 100, (255, 255, 255), "当たった");
	}*/


	// アニメーション
	++count;  // カウント開始
	if (count >= 8) {  // 値によってアニメーションのスピードが変化する0に近い程速い
		r_enemy.image++;
		count = 0;  // カウントリセット
	}
	if (r_enemy.image >= 2) { // 画像の切り替え
		r_enemy.image = 0;    // 画像リセット
	}

	//num = rand() % 99 + 0;

	//r_enemy.x += r_enemy.speed;

	r_enemy.direction = mPlayer.x - r_enemy.x;

	r_enemy.x -= r_enemy.direction * r_enemy.speed;

	if (num == 0) {       // 右向き
		r_enemy.eyeimage = 1;
		r_enemy.x += r_enemy.speed;
	}
	else if (num == 1) {  // 左向き
		r_enemy.eyeimage = 3;
		r_enemy.x -= r_enemy.speed;
	}
	else if (num == 2) {  // 上向き
		r_enemy.eyeimage = 0;
		r_enemy.x -= r_enemy.speed;
	}
	else if (num == 3) {  // 下向き
		r_enemy.eyeimage = 2;
		r_enemy.x += r_enemy.speed;
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
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);  // 敵キャラ
	LoadDivGraph("images/eyes.png", 4, 4, 1, 32, 32, eyesimages);  // 敵キャラの目
	DrawRotaGraph(r_enemy.x, r_enemy.y, 1, 0, images[r_enemy.image], TRUE, FALSE);  // 敵キャラ表示
	DrawRotaGraph(r_enemy.x, r_enemy.y, 1, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE);  // 敵キャラの目表示
}