#include "DxLib.h"
#include "Blue_Enemy.h"

B_ENEMY b_enemy;

B_ENEMY::B_ENEMY() {
	b_enemy.x = 704;
	b_enemy.y = 360;
}

B_ENEMY::~B_ENEMY() {
	//DeleteGraph(images[0]);
}

void B_ENEMY::Update() {

}

void B_ENEMY::Draw() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);
	DrawRotaGraph(b_enemy.x, b_enemy.y, 1, 0, images[4], TRUE, FALSE);
}