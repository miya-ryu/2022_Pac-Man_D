#include "DxLib.h"
#include "Orange_Enemy.h"

O_ENEMY o_enemy;

O_ENEMY::O_ENEMY() {
	o_enemy.EnemyX = 736;
	o_enemy.EnemyY = 360;
}

O_ENEMY::~O_ENEMY() {
	//DeleteGraph(Enemy_image[0]);
}

void O_ENEMY::Update() {

}

void O_ENEMY::Draw() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, Enemy_image);
	DrawRotaGraph(o_enemy.EnemyX, o_enemy.EnemyY, 1, 0, Enemy_image[6], TRUE, FALSE);
}