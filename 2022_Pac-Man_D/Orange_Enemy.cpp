#include "DxLib.h"
#include "Orange_Enemy.h"

O_ENEMY o_enemy;

O_ENEMY::O_ENEMY() {
	o_enemy.x = 736;
	o_enemy.y = 360;
}

O_ENEMY::~O_ENEMY() {
	//DeleteGraph(images[0]);
}

void O_ENEMY::Update() {

}

void O_ENEMY::Draw() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);
	DrawRotaGraph(o_enemy.x, o_enemy.y, 1, 0, images[6], TRUE, FALSE);
}