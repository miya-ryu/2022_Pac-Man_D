#include "DxLib.h"
#include "Pink_Enemy.h"

P_ENEMY p_enemy;

P_ENEMY::P_ENEMY() {

}

P_ENEMY::~P_ENEMY() {
	//DeleteGraph(Enemy_image[0]);
}

void P_ENEMY::Update() {

}

void P_ENEMY::Draw() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, Enemy_image);
	DrawRotaGraph(672, 360, 1, 0, Enemy_image[2], TRUE, FALSE);
}