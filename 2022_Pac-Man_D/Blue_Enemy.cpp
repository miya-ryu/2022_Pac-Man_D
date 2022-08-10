#include "DxLib.h"
#include "Blue_Enemy.h"

B_ENEMY b_enemy;

B_ENEMY::B_ENEMY() {
	b_enemy.EnemyX = 704;
	b_enemy.EnemyY = 360;
}

B_ENEMY::~B_ENEMY() {
	//DeleteGraph(Enemy_image[0]);
}

void B_ENEMY::Update() {

}

void B_ENEMY::Draw() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, Enemy_image);
	DrawRotaGraph(b_enemy.EnemyX, b_enemy.EnemyY, 1, 0, Enemy_image[4], TRUE, FALSE);
}