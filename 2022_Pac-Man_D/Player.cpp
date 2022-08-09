#include "DxLib.h"
#include "Player.h"

Player mPlayer;

Player::Player() {
	x = 0;
	y = 78;
}

void Player::Player_Draw(){
	LoadDivGraph("images/pacman.png", 12, 12, 1, 32, 32, mPlayerImage);
	DrawGraph(0, 0, mPlayerImage[1], TRUE);
}