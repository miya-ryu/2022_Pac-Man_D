#include "DxLib.h"
#include "Player.h"
#include "Input.h"

Player mPlayer;

Player::Player() {
	mPlayer.x = PLAYER_POS_X;
	mPlayer.y = PLAYER_POS_Y;
	mPlayer.muki = 4;
	mPlayer.move = 2;
	mPlayer.recordX = mPlayer.x;
	mPlayer.recordY = mPlayer.y;
	mPlayer.left = PLAYER_POS_X + 10;
	mPlayer.top = PLAYER_POS_Y + 10;
	mPlayer.right = PLAYER_POS_X + 22;
	mPlayer.bottom = PLAYER_POS_Y + 22;
	mPlayer.count = 0;
	mPlayer.image = 0;
}

void Player::Player_Update() {
	++count;
	mPlayer.recordX = mPlayer.x;
	mPlayer.recordY = mPlayer.y;
	if (count >= 3) {
		mPlayer.image++;
		count = 0;
	}
	if (mPlayer.image %3==0) {
		if (mPlayer.muki == 1) {
			mPlayer.image = 0;
		}
		else if (mPlayer.muki == 2) {
			mPlayer.image = 3;
		}
		else if (mPlayer.muki == 3) {
			mPlayer.image = 6;
		}
		else if (mPlayer.muki == 4) {
			mPlayer.image = 9;
		}
	}
	if (iNowKey & PAD_INPUT_RIGHT){
		mPlayer.x += mPlayer.move;
		mPlayer.muki = 2;
		if (count >= 3) {
			mPlayer.image++;
			count = 0;
		}
		if (mPlayer.image %3==0) {
			mPlayer.image = 3;
		}
		mPlayer.left += mPlayer.move;
		mPlayer.right += mPlayer.move;
	}
	else if (iNowKey & PAD_INPUT_LEFT) {
		mPlayer.muki = 4;
		mPlayer.x -= mPlayer.move;
		if (count >= 3) {
			mPlayer.image++;
			count = 0;
		}
		if (mPlayer.image % 3 == 0) {
			mPlayer.image = 9;
		}
		mPlayer.left -= mPlayer.move;
		mPlayer.right -= mPlayer.move;
	}
	else if (iNowKey & PAD_INPUT_UP) {
		mPlayer.muki = 1;
		mPlayer.y -= mPlayer.move;
		if (count >= 3) {
			mPlayer.image++;
			count = 0;
		}
		if (mPlayer.image % 3 == 0) {
			mPlayer.image = 0;
		}
		mPlayer.top -= mPlayer.move;
		mPlayer.bottom -= mPlayer.move;
	}

	else if (iNowKey & PAD_INPUT_DOWN) {
		mPlayer.muki = 3;
		mPlayer.y += mPlayer.move;
		if (count >= 3) {
			mPlayer.image++;
			count = 0;
		}
		if (mPlayer.image % 3 == 0) {
			mPlayer.image = 6;
		}
		mPlayer.top += mPlayer.move;
		mPlayer.bottom += mPlayer.move;
	}

	// ƒ[ƒv
	if (mPlayer.x >= 1280) {
		mPlayer.x = -32;
	}
	else if (mPlayer.x <= -32) {
		mPlayer.x = 1280;
	}
}

void Player::Player_Draw(){
	LoadDivGraph("images/pacman.png", 12, 12, 1, 32, 32, mPlayerImage);
	DrawGraph(mPlayer.x, mPlayer.y, mPlayerImage[mPlayer.image], TRUE);
	DrawBox(mPlayer.left, mPlayer.top, mPlayer.right, mPlayer.bottom, 0x00ff00, FALSE);
}