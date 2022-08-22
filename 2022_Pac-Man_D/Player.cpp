#include "DxLib.h"
#include "Player.h"
#include "Input.h"

Player mPlayer;

Player::Player() {
	//移動
	mPlayer.x = PLAYER_POS_X;
	mPlayer.y = PLAYER_POS_Y;

	//当たり判定
	mPlayer.left = PLAYER_POS_X - PLAYER_POS_HITBOX;
	mPlayer.top = PLAYER_POS_Y - PLAYER_POS_HITBOX;
	mPlayer.right = PLAYER_POS_X + PLAYER_POS_HITBOX;
	mPlayer.bottom = PLAYER_POS_Y + PLAYER_POS_HITBOX;

	//アングル
	mPlayer.muki = 4;

	//移動
	mPlayer.move = 2;

	//当たったとき進めなくする
	mPlayer.recordX = mPlayer.x;
	mPlayer.recordY = mPlayer.y;

	mPlayer.recordTop = mPlayer.top;
	mPlayer.recordRight = mPlayer.right;
	mPlayer.recordBottom = mPlayer.bottom;
	mPlayer.recordLeft = mPlayer.left;

	mPlayer.count = 0;
	mPlayer.image = 0;
}

void Player::Player_Update() {
	++count;

	//前回の座標を取得
	mPlayer.recordX = mPlayer.x;
	mPlayer.recordY = mPlayer.y;
	mPlayer.recordTop = mPlayer.top;
	mPlayer.recordRight = mPlayer.right;
	mPlayer.recordBottom = mPlayer.bottom;
	mPlayer.recordLeft = mPlayer.left;

	//移動
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

	// ワープ
	if (mPlayer.x >= 1280) {
		mPlayer.x = -32;
		mPlayer.right = -48;
		mPlayer.left = -16;
	}
	else if (mPlayer.x <= -32) {
		mPlayer.x = 1280;
		mPlayer.right = 1280 - 16;
		mPlayer.left = 1280 + 16;
	}
}

void Player::Player_Draw(){
	LoadDivGraph("images/pacman.png", 12, 12, 1, 32, 32, mPlayerImage);
	DrawRotaGraph(mPlayer.x, mPlayer.y, 1, 0, mPlayerImage[mPlayer.image], TRUE, FALSE);  // 敵キャラ表示
	DrawBox(mPlayer.left, mPlayer.top, mPlayer.right, mPlayer.bottom, 0x00ff00, FALSE);
}