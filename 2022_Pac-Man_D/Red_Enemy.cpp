#include "DxLib.h"
#include "Red_Enemy.h"

R_ENEMY r_enemy;

R_ENEMY::R_ENEMY() {
	r_enemy.EnemyX = 640;
	r_enemy.EnemyY = 360;
}

R_ENEMY::~R_ENEMY() {
	//DeleteGraph(Enemy_image[0]);
}

void R_ENEMY::Update() {
	r_enemy.EnemyX += 3;
	if (r_enemy.EnemyX >= 1280) {
		r_enemy.EnemyX = 0;
	}
}

void R_ENEMY::Draw() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, Enemy_image);
	DrawRotaGraph(r_enemy.EnemyX, r_enemy.EnemyY, 1, 0, Enemy_image[0], TRUE, FALSE);
}