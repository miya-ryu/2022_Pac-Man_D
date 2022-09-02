#include "DxLib.h"
#include "Pink_Enemy.h"
#include "Player.h"

P_ENEMY p_enemy;

P_ENEMY::P_ENEMY() {
	p_enemy.x = 120;        // 初期位置縦
	p_enemy.y = 360;        // 初期位置横
	p_enemy.speed = 1;      // 移動速度
	p_enemy.directionX = 0; // X方向
	p_enemy.directionY = 0; // Y方向
	p_enemy.count = 0;      // アニメーションカウント
	p_enemy.image = 2;      // 画像変数
	p_enemy.eyeimage = 0;   // 目の画像変数
}

P_ENEMY::~P_ENEMY() {
	//DeleteGraph(images[0]);
}

void P_ENEMY::Update() {
	// プレイヤーを追いかける処理
	if (mPlayer.x >= p_enemy.x + 1) {       // 右向き
		p_enemy.x += p_enemy.speed;
		p_enemy.eyeimage = 1;
	}
	else if (mPlayer.x <= p_enemy.x - 1) {  // 左向き
		p_enemy.x -= p_enemy.speed;
		p_enemy.eyeimage = 3;
	}
	if (mPlayer.y >= p_enemy.y + 1) {       // 下向き
		p_enemy.y += p_enemy.speed;
		p_enemy.eyeimage = 2;
	}
	else if (mPlayer.y <= p_enemy.y - 1) {  // 上向き
		p_enemy.y -= p_enemy.speed;
		p_enemy.eyeimage = 0;
	}

	// アニメーション
	++count;  // カウント開始
	if (count >= 8) {  // 値によってアニメーションのスピードが変化する0に近い程速い
		p_enemy.image++;
		count = 0;  // カウントリセット
	}
	if (p_enemy.image >= 4) { // 画像の切り替え
		p_enemy.image = 2;    // 画像リセット
	}

	// ワープトンネル
	if (p_enemy.x >= 1280) {
		p_enemy.x = 0;
	}
	else if (p_enemy.x <= 0) {
		p_enemy.x = 1280;
	}
}

void P_ENEMY::Draw() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);  // 敵キャラ
	LoadDivGraph("images/eyes.png", 4, 4, 1, 32, 32, eyesimages);  // 敵キャラの目
	DrawRotaGraph(p_enemy.x, p_enemy.y, 1, 0, images[p_enemy.image], TRUE, FALSE);  // 敵キャラ表示
	DrawRotaGraph(p_enemy.x, p_enemy.y, 1, 0, eyesimages[p_enemy.eyeimage], TRUE, FALSE);  // 敵キャラの目表示
}