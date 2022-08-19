#include "DxLib.h"
#include "Player.h"
#include "Input.h"

Player mPlayer;

Player::Player() {
	mPlayer.x = PLAYER_POS_X;
	mPlayer.y = PLAYER_POS_Y;
	mPlayer.recordX = mPlayer.x;
	mPlayer.recordY = mPlayer.y;
	mPlayer.move = 2;
	mPlayer.left = PLAYER_POS_X;
	mPlayer.top = PLAYER_POS_Y;
	mPlayer.right = PLAYER_POS_X + 32;
	mPlayer.bottom = PLAYER_POS_Y + 32;
}

void Player::Player_Update() {
	mPlayer.recordX = mPlayer.x;
	mPlayer.recordY = mPlayer.y;
	if (iNowKey & PAD_INPUT_RIGHT){
		mPlayer.x += mPlayer.move;
		mPlayer.left += mPlayer.move;
		mPlayer.right += mPlayer.move;
	}
	else if (iNowKey & PAD_INPUT_LEFT) {
		mPlayer.x -= mPlayer.move;
		mPlayer.left -= mPlayer.move;
		mPlayer.right -= mPlayer.move;
	}
	else if (iNowKey & PAD_INPUT_UP) {
		mPlayer.y -= mPlayer.move;
		mPlayer.top -= mPlayer.move;
		mPlayer.bottom -= mPlayer.move;
	}
	else if (iNowKey & PAD_INPUT_DOWN) {
		mPlayer.y += mPlayer.move;
		mPlayer.top += mPlayer.move;
		mPlayer.bottom += mPlayer.move;
	}
}

void Player::Player_Draw(){
	LoadDivGraph("images/pacman.png", 12, 12, 1, 32, 32, mPlayerImage);
	DrawGraph(mPlayer.x, mPlayer.y, mPlayerImage[1], TRUE);
	DrawBox(mPlayer.left, mPlayer.top, mPlayer.right, mPlayer.bottom, 0x00ff00, FALSE);
}