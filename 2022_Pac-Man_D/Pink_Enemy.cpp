#include "DxLib.h"
#include "Pink_Enemy.h"

P_ENEMY p_enemy;

P_ENEMY::P_ENEMY() {
	p_enemy.x = 672;
	p_enemy.y = 360;
}

P_ENEMY::~P_ENEMY() {
	//DeleteGraph(images[0]);
}

void P_ENEMY::Update() {

}

void P_ENEMY::Draw() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);
	DrawRotaGraph(p_enemy.x, p_enemy.y, 1, 0, images[2], TRUE, FALSE);
}