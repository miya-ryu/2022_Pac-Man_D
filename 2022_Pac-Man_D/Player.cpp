#include "DxLib.h"
#include "Player.h"
#include "Input.h"
#include "Red_Enemy.h"
#include "Stage.h"
#include <windows.h>

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
	LoadDivGraph("images/pacman.png", 12, 12, 1, 32, 32, mPlayer.mPlayerMoveImage);
	//�A���O��
	mPlayer.iNowAngle = 4;
	mPlayer.iOldAngle = mPlayer.iNowAngle;
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
	//�f���[�g����
	LoadDivGraph("images/dying.png", 11, 11, 1, 32, 32, mPlayer.mPlayerDeleteImage);
	mPlayer.deletecount = 0;
	mPlayer.deleteimage = 0;
	//�摜����
	mPlayer.count = 0;
	mPlayer.timercount = 0;
	mPlayer.image = 0;
	mPlayer.Hitflg = FALSE;
	mPlayer.P_StageHitflg = FALSE;
	mPlayer.Angleflg = FALSE;
	mPlayer.iOldKeyflg = FALSE;
	// ���񂾂Ƃ�
	mPlayer.millisecond = 0.01 * 1000;
}

void Player::Player_Update() {
	++count;
	++mPlayer.deletecount;
	//�O��̍��W��擾
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
		mPlayer.image += 1;
		count = 0;
	}
	if (mPlayer.image % 3 == 0 || mPlayer.image >= 12) {
		if (mPlayer.iNowAngle == 1) {
			mPlayer.image = 0;
		}
		else if (mPlayer.iNowAngle == 2) {
			mPlayer.image = 3;
		}
		else if (mPlayer.iNowAngle == 3) {
			mPlayer.image = 6;
		}
		else if (mPlayer.iNowAngle == 4) {
			mPlayer.image = 9;
		}
	}
	
	// �v���C���[�ƃG�l�~�[�̓����蔻��
	if (PlayerCheckHit(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom)) {
		if (r_enemy.R_Hitflg == TRUE || r_enemy.ER_Hitflg == TRUE) { // イジケ状態で当たったら
			++mPlayer.timercount; // カウント開始
			if (mPlayer.timercount < 2) { // カウントが2より小さければ
				WaitTimer(1000); // 1秒間時間を止める
			}
		}
		else {
			mPlayer.Hitflg = TRUE; // イジケ状態が終わったら元の当たり判定に戻す
			/*mPlayer.x = PLAYER_POS_X;
			mPlayer.y = PLAYER_POS_Y;
			mPlayer.p_left = PLAYER_POS_X - PLAYER_CENTER_HITBOX;
			mPlayer.p_top = PLAYER_POS_Y - PLAYER_CENTER_HITBOX;
			mPlayer.p_right = PLAYER_POS_X + PLAYER_CENTER_HITBOX;
			mPlayer.p_bottom = PLAYER_POS_Y + PLAYER_CENTER_HITBOX;
			mPlayer.s_left = PLAYER_POS_X - PLAYER_POS_HITBOX;
			mPlayer.s_top = PLAYER_POS_Y - PLAYER_POS_HITBOX;
			mPlayer.s_right = PLAYER_POS_X + PLAYER_POS_HITBOX;
			mPlayer.s_bottom = PLAYER_POS_Y + PLAYER_POS_HITBOX;*/
		}
	}

		mPlayer.Hitflg = TRUE;
		Sleep(millisecond);
	}
	//�ړ�����
	//�E
	if (iNowKey & PAD_INPUT_RIGHT) {
		//�O��̃A���O���i�[
		mPlayer.iOldAngle = mPlayer.iNowAngle;
		mPlayer.Angleflg = TRUE;
		mPlayer.iNowAngle = 2;
	}
	//��
	else if (iNowKey & PAD_INPUT_LEFT) {
		//�O��̃A���O���i�[
		mPlayer.iOldAngle = mPlayer.iNowAngle;
		mPlayer.Angleflg = TRUE;
		mPlayer.iNowAngle = 4;
	}
	//��
	else if (iNowKey & PAD_INPUT_UP) {
		//�O��̃A���O���i�[
		mPlayer.iOldAngle = mPlayer.iNowAngle;
		mPlayer.Angleflg = TRUE;
		mPlayer.iNowAngle = 1;
	}
	//��
	else if (iNowKey & PAD_INPUT_DOWN) {
		//�O��̃A���O���i�[
		mPlayer.iOldAngle = mPlayer.iNowAngle;
		mPlayer.Angleflg = TRUE;
		mPlayer.iNowAngle = 3;
	}
	//�ړ�����
	if (mPlayer.Hitflg == FALSE) {
		//��
		if (mPlayer.iNowAngle == 1) {
			mPlayer.y -= mPlayer.move;
			//HitBox�ړ�
			mPlayer.p_top -= mPlayer.move;
			mPlayer.p_bottom -= mPlayer.move;
			mPlayer.s_top -= mPlayer.move;
			mPlayer.s_bottom -= mPlayer.move;
		}
		//�E
		else if (mPlayer.iNowAngle == 2) {
			mPlayer.x += mPlayer.move;
			//HitBox�ړ�
			mPlayer.p_left += mPlayer.move;
			mPlayer.p_right += mPlayer.move;
			mPlayer.s_left += mPlayer.move;
			mPlayer.s_right += mPlayer.move;
		}
		//��
		else if (mPlayer.iNowAngle == 3) {
			mPlayer.y += mPlayer.move;
			//HitBox�ړ�
			mPlayer.p_top += mPlayer.move;
			mPlayer.p_bottom += mPlayer.move;
			mPlayer.s_top += mPlayer.move;
			mPlayer.s_bottom += mPlayer.move;
		}
		//��
		else if (mPlayer.iNowAngle == 4) {
			mPlayer.x -= mPlayer.move;
			//HitBox�ړ�
			mPlayer.p_left -= mPlayer.move;
			mPlayer.p_right -= mPlayer.move;
			mPlayer.s_left -= mPlayer.move;
			mPlayer.s_right -= mPlayer.move;
		}
	}

	// ���[�v
	if (mPlayer.x >= 890) {
		mPlayer.x = 340;
		//HitBox�ړ�
		mPlayer.p_right = 340 + PLAYER_CENTER_HITBOX;
		mPlayer.p_left = 340 - PLAYER_CENTER_HITBOX;
		mPlayer.s_right = 340 + PLAYER_POS_HITBOX;
		mPlayer.s_left = 340 - PLAYER_POS_HITBOX;
	}
	else if (mPlayer.x <= 340) {
		mPlayer.x = 890;
		//HitBox�ړ�
		mPlayer.p_right = 890 + PLAYER_CENTER_HITBOX;
		mPlayer.p_left = 890 - PLAYER_CENTER_HITBOX;
		mPlayer.s_right = 890 + PLAYER_POS_HITBOX;
		mPlayer.s_left = 890 - PLAYER_POS_HITBOX;
	}
}

void Player::Player_Draw() {
	if (mPlayer.Hitflg == FALSE) {
		//Player�\��
		DrawRotaGraph(mPlayer.x, mPlayer.y, 0.75, 0, mPlayer.mPlayerMoveImage[mPlayer.image], TRUE, FALSE);
	}
	else if (mPlayer.Hitflg == TRUE) {
		mPlayer.deletecount++;

		if (mPlayer.deletecount % 5 == 0) {
			mPlayer.deleteimage++;
		}
		DrawRotaGraph(mPlayer.x, mPlayer.y, 0.75, 0, mPlayer.mPlayerDeleteImage[mPlayer.deleteimage], TRUE, FALSE);

		Sleep(millisecond);
		if (mPlayer.deleteimage >= 11) {
			mPlayer.x = PLAYER_POS_X;
			mPlayer.y = PLAYER_POS_Y;
			mPlayer.p_left = PLAYER_POS_X - PLAYER_CENTER_HITBOX;
			mPlayer.p_top = PLAYER_POS_Y - PLAYER_CENTER_HITBOX;
			mPlayer.p_right = PLAYER_POS_X + PLAYER_CENTER_HITBOX;
			mPlayer.p_bottom = PLAYER_POS_Y + PLAYER_CENTER_HITBOX;
			mPlayer.s_left = PLAYER_POS_X - PLAYER_POS_HITBOX;
			mPlayer.s_top = PLAYER_POS_Y - PLAYER_POS_HITBOX;
			mPlayer.s_right = PLAYER_POS_X + PLAYER_POS_HITBOX;
			mPlayer.s_bottom = PLAYER_POS_Y + PLAYER_POS_HITBOX;
			mPlayer.iNowAngle = 4;
			mPlayer.Hitflg = FALSE;
		}
	}
	//Stage�����蔻��\��
	DrawBox(mPlayer.s_left, mPlayer.s_top, mPlayer.s_right, mPlayer.s_bottom, 0x00ff00, FALSE);
	//Center�����蔻��\��
	DrawBox(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, 0xff00ff, TRUE);
}
