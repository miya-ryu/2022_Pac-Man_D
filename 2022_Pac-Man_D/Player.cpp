#include "DxLib.h"
#include "Player.h"
#include "Input.h"
#include "Red_Enemy.h"

Player mPlayer;

//当たり判定
int PlayerCheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	int L1 = x1;		//左
	int R1 = w1;		//右
	int L2 = x2;		//左
	int R2 = w2;		//右

	if (R1 < L2) return 0;
	if (R2 < L1) return 0;

	int U1 = y1;		//上
	int D1 = h1;		//下
	int U2 = y2;		//上
	int D2 = h2;		//下

	if (D1 < U2) return 0;
	if (D2 < U1) return 0;

	//当たっている
	return 1;
}

void Player::Player_Initialize() {
	//移動
	mPlayer.x = PLAYER_POS_X;
	mPlayer.y = PLAYER_POS_Y;

	//当たり判定
	mPlayer.p_left = PLAYER_POS_X - PLAYER_CENTER_HITBOX;
	mPlayer.p_top = PLAYER_POS_Y - PLAYER_CENTER_HITBOX;
	mPlayer.p_right = PLAYER_POS_X + PLAYER_CENTER_HITBOX;
	mPlayer.p_bottom = PLAYER_POS_Y + PLAYER_CENTER_HITBOX;

	//Stage当たり判定
	mPlayer.s_left = PLAYER_POS_X - PLAYER_POS_HITBOX;
	mPlayer.s_top = PLAYER_POS_Y - PLAYER_POS_HITBOX;
	mPlayer.s_right = PLAYER_POS_X + PLAYER_POS_HITBOX;
	mPlayer.s_bottom = PLAYER_POS_Y + PLAYER_POS_HITBOX;

	//画像格納
	LoadDivGraph("images/pacman.png", 12, 12, 1, 32, 32, mPlayerImage);

	//アングル
	mPlayer.muki = 4;

	//移動
	mPlayer.move = 2;

	//前回の座標格納
	mPlayer.recordX = mPlayer.x;
	mPlayer.recordY = mPlayer.y;

	mPlayer.recordSTop = mPlayer.s_top;
	mPlayer.recordSRight = mPlayer.s_right;
	mPlayer.recordSBottom = mPlayer.s_bottom;
	mPlayer.recordSLeft = mPlayer.s_left;

	mPlayer.recordPtop = mPlayer.p_top;
	mPlayer.recordPright = mPlayer.p_right;
	mPlayer.recordPbottom = mPlayer.p_bottom;
	mPlayer.recordPleft = mPlayer.p_left;

	//画像処理
	mPlayer.count = 0;
	mPlayer.image = 0;

	mPlayer.Hitflg = FALSE;
}

void Player::Player_Update() {
	++count;

	//前回の座標を取得
	mPlayer.recordX = mPlayer.x;
	mPlayer.recordY = mPlayer.y;
	//前回の座標（ステージHitbox）
	mPlayer.recordSTop = mPlayer.s_top;
	mPlayer.recordSRight = mPlayer.s_right;
	mPlayer.recordSBottom = mPlayer.s_bottom;
	mPlayer.recordSLeft = mPlayer.s_left;
	//前回の座標（PlayerHitbox）
	mPlayer.recordPtop = mPlayer.p_top;
	mPlayer.recordPright = mPlayer.p_right;
	mPlayer.recordPbottom = mPlayer.p_bottom;
	mPlayer.recordPleft = mPlayer.p_left;

	//画像処理
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
	if (PlayerCheckHit(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, r_enemy.left, r_enemy.top,r_enemy.right,r_enemy.bottom)) {
		mPlayer.Hitflg = TRUE;
	}

	//移動処理
	//右
	if (iNowKey & PAD_INPUT_RIGHT){
		mPlayer.muki = 2;
		if (count >= 3) {
			mPlayer.image++;
			count = 0;
		}
		if (mPlayer.image % 3 == 0) {
			mPlayer.image = 3;
		}
	}
	//左
	else if (iNowKey & PAD_INPUT_LEFT) {
		mPlayer.muki = 4;
		if (count >= 3) {
			mPlayer.image++;
			count = 0;
		}
		if (mPlayer.image % 3 == 0) {
			mPlayer.image = 9;
		}
	}
	//上
	else if (iNowKey & PAD_INPUT_UP) {
		mPlayer.muki = 1;
		if (count >= 3) {
			mPlayer.image++;
			count = 0;
		}
		if (mPlayer.image % 3 == 0) {
			mPlayer.image = 0;
		}
	}
	//下
	else if (iNowKey & PAD_INPUT_DOWN) {
		mPlayer.muki = 3;
		if (count >= 3) {
			mPlayer.image++;
			count = 0;
		}
		if (mPlayer.image % 3 == 0) {
			mPlayer.image = 6;
		}
	}

	//移動
	//上
	if (mPlayer.muki == 1) {
		mPlayer.y -= mPlayer.move;
		//HitBox移動
		mPlayer.p_top -= mPlayer.move;
		mPlayer.p_bottom -= mPlayer.move;
		mPlayer.s_top -= mPlayer.move;
		mPlayer.s_bottom -= mPlayer.move;
	}
	//右
	else if (mPlayer.muki == 2) {
		mPlayer.x += mPlayer.move;
		//HitBox移動
		mPlayer.p_left += mPlayer.move;
		mPlayer.p_right += mPlayer.move;
		mPlayer.s_left += mPlayer.move;
		mPlayer.s_right += mPlayer.move;
	}
	//下
	else if (mPlayer.muki == 3) {
		mPlayer.y += mPlayer.move;
		//HitBox移動
		mPlayer.p_top += mPlayer.move;
		mPlayer.p_bottom += mPlayer.move;
		mPlayer.s_top += mPlayer.move;
		mPlayer.s_bottom += mPlayer.move;
	}
	//左
	else if (mPlayer.muki == 4) {
		mPlayer.x -= mPlayer.move;
		//HitBox移動
		mPlayer.p_left -= mPlayer.move;
		mPlayer.p_right -= mPlayer.move;
		mPlayer.s_left -= mPlayer.move;
		mPlayer.s_right -= mPlayer.move;
	}

	// ワープ
	if (mPlayer.x >= 890) {
		mPlayer.x = 340;
		//HitBox移動
		mPlayer.p_right = 340 + PLAYER_CENTER_HITBOX;
		mPlayer.p_left = 340 - PLAYER_CENTER_HITBOX;
		mPlayer.s_right = 340 + PLAYER_POS_HITBOX;
		mPlayer.s_left = 340 - PLAYER_POS_HITBOX;
	}
	else if (mPlayer.x <= 340) {
		mPlayer.x = 890;
		//HitBox移動
		mPlayer.p_right = 890 + PLAYER_CENTER_HITBOX;
		mPlayer.p_left = 890 - PLAYER_CENTER_HITBOX;
		mPlayer.s_right = 890 + PLAYER_POS_HITBOX;
		mPlayer.s_left = 890 - PLAYER_POS_HITBOX;
	}
}

void Player::Player_Draw(){
	if (mPlayer.Hitflg == FALSE) {
		//Player表示
		DrawRotaGraph(mPlayer.x, mPlayer.y, 0.75, 0, mPlayerImage[mPlayer.image], TRUE, FALSE);
	}
	else if(mPlayer.Hitflg == TRUE){
		//DxLib_End();
	}
	//Stage当たり判定表示
	DrawBox(mPlayer.s_left, mPlayer.s_top, mPlayer.s_right, mPlayer.s_bottom, 0x00ff00, FALSE);
	//Center当たり判定表示
	DrawBox(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, 0xff00ff, TRUE);
}