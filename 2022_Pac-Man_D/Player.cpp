#include "DxLib.h"
#include "Player.h"
#include "Input.h"
#include "Red_Enemy.h"

Player mPlayer;

//�����蔻��
int PlayerCheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	int L1 = x1;		//��
	int R1 = w1;		//�E
	int L2 = x2;		//��
	int R2 = w2;		//�E

	if (R1 < L2) return 0;
	if (R2 < L1) return 0;

	int U1 = y1;		//��
	int D1 = h1;		//��
	int U2 = y2;		//��
	int D2 = h2;		//��

	if (D1 < U2) return 0;
	if (D2 < U1) return 0;

	//�������Ă���
	return 1;
}

void Player::Player_Initialize() {
	//�ړ�
	mPlayer.x = PLAYER_POS_X;
	mPlayer.y = PLAYER_POS_Y;

	//�����蔻��
	mPlayer.p_left = PLAYER_POS_X - PLAYER_CENTER_HITBOX;
	mPlayer.p_top = PLAYER_POS_Y - PLAYER_CENTER_HITBOX;
	mPlayer.p_right = PLAYER_POS_X + PLAYER_CENTER_HITBOX;
	mPlayer.p_bottom = PLAYER_POS_Y + PLAYER_CENTER_HITBOX;

	//Stage�����蔻��
	mPlayer.s_left = PLAYER_POS_X - PLAYER_POS_HITBOX;
	mPlayer.s_top = PLAYER_POS_Y - PLAYER_POS_HITBOX;
	mPlayer.s_right = PLAYER_POS_X + PLAYER_POS_HITBOX;
	mPlayer.s_bottom = PLAYER_POS_Y + PLAYER_POS_HITBOX;

	//�摜�i�[
	LoadDivGraph("images/pacman.png", 12, 12, 1, 32, 32, mPlayerImage);

	//�A���O��
	mPlayer.muki = 4;

	//�ړ�
	mPlayer.move = 2;

	//�O��̍��W�i�[
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

	//�摜����
	mPlayer.count = 0;
	mPlayer.image = 0;

	mPlayer.Hitflg = FALSE;
}

void Player::Player_Update() {
	++count;

	//�O��̍��W���擾
	mPlayer.recordX = mPlayer.x;
	mPlayer.recordY = mPlayer.y;
	//�O��̍��W�i�X�e�[�WHitbox�j
	mPlayer.recordSTop = mPlayer.s_top;
	mPlayer.recordSRight = mPlayer.s_right;
	mPlayer.recordSBottom = mPlayer.s_bottom;
	mPlayer.recordSLeft = mPlayer.s_left;
	//�O��̍��W�iPlayerHitbox�j
	mPlayer.recordPtop = mPlayer.p_top;
	mPlayer.recordPright = mPlayer.p_right;
	mPlayer.recordPbottom = mPlayer.p_bottom;
	mPlayer.recordPleft = mPlayer.p_left;

	//�摜����
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

	//�ړ�����
	//�E
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
	//��
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
	//��
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
	//��
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

	//�ړ�
	//��
	if (mPlayer.muki == 1) {
		mPlayer.y -= mPlayer.move;
		//HitBox�ړ�
		mPlayer.p_top -= mPlayer.move;
		mPlayer.p_bottom -= mPlayer.move;
		mPlayer.s_top -= mPlayer.move;
		mPlayer.s_bottom -= mPlayer.move;
	}
	//�E
	else if (mPlayer.muki == 2) {
		mPlayer.x += mPlayer.move;
		//HitBox�ړ�
		mPlayer.p_left += mPlayer.move;
		mPlayer.p_right += mPlayer.move;
		mPlayer.s_left += mPlayer.move;
		mPlayer.s_right += mPlayer.move;
	}
	//��
	else if (mPlayer.muki == 3) {
		mPlayer.y += mPlayer.move;
		//HitBox�ړ�
		mPlayer.p_top += mPlayer.move;
		mPlayer.p_bottom += mPlayer.move;
		mPlayer.s_top += mPlayer.move;
		mPlayer.s_bottom += mPlayer.move;
	}
	//��
	else if (mPlayer.muki == 4) {
		mPlayer.x -= mPlayer.move;
		//HitBox�ړ�
		mPlayer.p_left -= mPlayer.move;
		mPlayer.p_right -= mPlayer.move;
		mPlayer.s_left -= mPlayer.move;
		mPlayer.s_right -= mPlayer.move;
	}

	// ���[�v
	if (mPlayer.x >= 1280) {
		mPlayer.x = -32;
		//HitBox�ړ�
		mPlayer.p_right -= mPlayer.move;
		mPlayer.p_left -= mPlayer.move;
		mPlayer.s_right = -17;
		mPlayer.s_left = -47;
	}
	else if (mPlayer.x <= -32) {
		mPlayer.x = 1280;
		//HitBox�ړ�
		mPlayer.p_top -= mPlayer.move;
		mPlayer.p_bottom -= mPlayer.move;
		mPlayer.s_right = 1280 + PLAYER_POS_HITBOX;
		mPlayer.s_left = 1280 - PLAYER_POS_HITBOX;
	}
}

void Player::Player_Draw(){
	if (mPlayer.Hitflg == FALSE) {
		//Player�\��
		DrawRotaGraph(mPlayer.x, mPlayer.y, 0.75, 0, mPlayerImage[mPlayer.image], TRUE, FALSE);
	}
	else if(mPlayer.Hitflg == TRUE){
		DxLib_End();
	}
	//Stage�����蔻��\��
	DrawBox(mPlayer.s_left, mPlayer.s_top, mPlayer.s_right, mPlayer.s_bottom, 0x00ff00, FALSE);
	//Center�����蔻��\��
	DrawBox(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, 0xff00ff, TRUE);
}