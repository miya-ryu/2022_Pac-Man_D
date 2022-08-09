#include "DxLib.h"
#include "Red_Enemy.h"

R_ENEMY r_enemy;

R_ENEMY::R_ENEMY() {

}

R_ENEMY::~R_ENEMY() {
	//DeleteGraph(Enemy_image[0]);
}

void R_ENEMY::Update() {

}

void R_ENEMY::Draw() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, Enemy_image);
	DrawRotaGraph(640, 360, 1, 0, Enemy_image[0], TRUE, FALSE);
}