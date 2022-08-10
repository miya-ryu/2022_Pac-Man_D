#include "DxLib.h"
#include "Pink_Enemy.h"

P_ENEMY p_enemy;

P_ENEMY::P_ENEMY() {
	p_enemy.EnemyX = 672;
	p_enemy.EnemyY = 360;
}

P_ENEMY::~P_ENEMY() {
	//DeleteGraph(Enemy_image[0]);
}

void P_ENEMY::Update() {

}

void P_ENEMY::Draw() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, Enemy_image);
	DrawRotaGraph(p_enemy.EnemyX, p_enemy.EnemyY, 1, 0, Enemy_image[2], TRUE, FALSE);
}