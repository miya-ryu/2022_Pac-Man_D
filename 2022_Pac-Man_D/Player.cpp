#include "DxLib.h"
#include "Player.h"
#include "Input.h"

Player mPlayer;

Player::Player() {
	mPlayer.x = 640;
	mPlayer.y = 360;
	mPlayer.move = 2;
	mPlayer.count = 0;
	mPlayer.image = 0;
}

void Player::Player_Update() {
	++count;
	if (count >= 3) {
		mPlayer.image++;
		count = 0;
	}
	if (mPlayer.image >= 3) {
		mPlayer.image = 0;
	}
	if (iNowKey & PAD_INPUT_RIGHT){
		mPlayer.x += mPlayer.move;
	}
	else if (iNowKey & PAD_INPUT_LEFT) {
		mPlayer.x -= mPlayer.move;
	}
	else if (iNowKey & PAD_INPUT_UP) {
		mPlayer.y -= mPlayer.move;
	}

	else if (iNowKey & PAD_INPUT_DOWN) {
		mPlayer.y += mPlayer.move;
	}
}

void Player::Player_Draw(){
	LoadDivGraph("images/pacman.png", 12, 12, 1, 32, 32, mPlayerImage);
	DrawGraph(mPlayer.x, mPlayer.y, mPlayerImage[mPlayer.image], TRUE);
}

