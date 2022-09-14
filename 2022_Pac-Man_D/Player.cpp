#include "DxLib.h"
#include "Player.h"
#include "Input.h"
#include "Red_Enemy.h"
#include "Stage.h"
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

//����������
void Player::Player_Initialize() {
	//�ړ�
	mPlayer.x = PLAYER_POS_X;
	mPlayer.y = PLAYER_POS_Y;
	//���S�̓����蔻��̍��W
	mPlayer.Hitflg = FALSE;		//�G�l�~�[�Ƃ̃q�b�g�t���O
	mPlayer.p_left = PLAYER_POS_X - PLAYER_CENTER_HITBOX;
	mPlayer.p_top = PLAYER_POS_Y - PLAYER_CENTER_HITBOX;
	mPlayer.p_right = PLAYER_POS_X + PLAYER_CENTER_HITBOX;
	mPlayer.p_bottom = PLAYER_POS_Y + PLAYER_CENTER_HITBOX;
	//Stage�Ƃ̓����蔻��
	mPlayer.P_StageHitflg = FALSE;		//�X�e�[�W�Ƃ̃q�b�g�t���O
	mPlayer.s_left = PLAYER_POS_X - PLAYER_POS_HITBOX;
	mPlayer.s_top = PLAYER_POS_Y - PLAYER_POS_HITBOX;
	mPlayer.s_right = PLAYER_POS_X + PLAYER_POS_HITBOX;
	mPlayer.s_bottom = PLAYER_POS_Y + PLAYER_POS_HITBOX;
	//�ړ��摜�i�[
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
	mPlayer.image = 0;

	//���g�̏���������
	//���g�̃t���O����
	mPlayer.Top = FALSE;
	mPlayer.Bottom = FALSE;
	mPlayer.Left = TRUE;
	mPlayer.Right = TRUE;
	//���g�̍��W
	//��
	mPlayer.PLAYER_AVATAR_POS_X[0] = PLAYER_POS_X;
	mPlayer.PLAYER_AVATAR_POS_Y[0] = PLAYER_POS_Y - 24;
	//�E
	mPlayer.PLAYER_AVATAR_POS_X[1] = PLAYER_POS_X + 24;
	mPlayer.PLAYER_AVATAR_POS_Y[1] = PLAYER_POS_Y;
	//��
	mPlayer.PLAYER_AVATAR_POS_X[2] = PLAYER_POS_X;
	mPlayer.PLAYER_AVATAR_POS_Y[2] = PLAYER_POS_Y + 24;
	//��
	mPlayer.PLAYER_AVATAR_POS_X[3] = PLAYER_POS_X - 24;
	mPlayer.PLAYER_AVATAR_POS_Y[3] = PLAYER_POS_Y;

	//���g�̓����蔻����W
	for (int i = 0; i <= 3; i++) {
		mPlayer.avatar_left[i] = PLAYER_AVATAR_POS_X[i] - PLAYER_POS_HITBOX;
		mPlayer.avatar_top[i] = PLAYER_AVATAR_POS_Y[i] - PLAYER_POS_HITBOX;
		mPlayer.avatar_right[i] = PLAYER_AVATAR_POS_X[i] + PLAYER_POS_HITBOX;
		mPlayer.avatar_bottom[i] = PLAYER_AVATAR_POS_Y[i] + PLAYER_POS_HITBOX;
	}
}
void Player::Player_Update() {
	//�摜�J�E���g
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

	//���g�̍��W
	for (int i = 0; i <= 3; i++) {
		mPlayer.record_avatar_bottom[i] = mPlayer.avatar_bottom[i];
		mPlayer.record_avatar_left[i] = mPlayer.avatar_left[i];
		mPlayer.record_avatar_right[i] = mPlayer.avatar_right[i];
		mPlayer.record_avatar_top[i] = mPlayer.avatar_top[i];
	}

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

	//�G�l�~�[�Ƃ̓����蔻��
	if (PlayerCheckHit(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom)) {
		//mPlayer.Hitflg = TRUE;
	}

	//�L�[���͏���(�X�e�[�W�ɐG��Ă��Ȃ���)
	if (mPlayer.P_StageHitflg == FALSE) {
		//�E
		if (iNowKey & PAD_INPUT_RIGHT){
			//�ǂ��Ȃ�
			if (mPlayer.Right == FALSE) {
				mPlayer.iNowAngle = 2;
				mPlayer.iOldAngle = mPlayer.iNowAngle;
			}
			//�ǂ�����
			else if (mPlayer.Right == TRUE) {
				mPlayer.iOldAngle = 2;
				//mPlayer.iKeepAngle = mPlayer.iNowAngle;
				//mPlayer.iNowAngle = mPlayer.iOldAngle;
				//mPlayer.iOldAngle = mPlayer.iKeepAngle;
			}
		}
		//��
		else if (iNowKey & PAD_INPUT_LEFT) {
			//�ǂ��Ȃ�
			if (mPlayer.Left == FALSE) {
				mPlayer.iNowAngle = 4;
				mPlayer.iOldAngle = mPlayer.iNowAngle;
			}
			//�ǂ�����
			else if (mPlayer.Left == TRUE) {
				mPlayer.iOldAngle = 4;
			}
		}
		//��
		else if (iNowKey & PAD_INPUT_UP) {
			//�ǂ��Ȃ�
			if (mPlayer.Top == FALSE) {
				mPlayer.iNowAngle = 1;
				mPlayer.iOldAngle = mPlayer.iNowAngle;
			}
			//�ǂ�����
			else if (mPlayer.Top == TRUE) {
				mPlayer.iOldAngle = 1;
			}
		}
		//��
		else if (iNowKey & PAD_INPUT_DOWN) {
			//�ǂ��Ȃ�
			if (mPlayer.Bottom == FALSE) {
				mPlayer.iNowAngle = 3;
				mPlayer.iOldAngle = mPlayer.iNowAngle;
			}
			//�ǂ�����
			else if (mPlayer.Bottom == TRUE) {
				mPlayer.iOldAngle = 3;
			}
		}
	}

	//�O��̓��̓L�[�����邩�ǂ���
	if (mPlayer.x % 12 == 0) {
		//����
		if (mPlayer.Top == FALSE && mPlayer.iOldAngle == 1) {
			mPlayer.iNowAngle = mPlayer.iOldAngle;
		}
		//�݂�
		else if (mPlayer.Right == FALSE && mPlayer.iOldAngle == 2) {
			mPlayer.iNowAngle = mPlayer.iOldAngle;
		}
		//����
		else if (mPlayer.Bottom == FALSE && mPlayer.iOldAngle == 3) {
			mPlayer.iNowAngle = mPlayer.iOldAngle;
		}
		//�Ђ���
		else if (mPlayer.Left == FALSE && mPlayer.iOldAngle == 4) {
			mPlayer.iNowAngle = mPlayer.iOldAngle;
		}
	}
	 
	//Player�̈ړ�
	if (mPlayer.Hitflg == FALSE) {
		//��
		if (mPlayer.iNowAngle == 1) {
			mPlayer.y -= mPlayer.move;
			//HitBox�ړ�
			mPlayer.p_top -= mPlayer.move;
			mPlayer.p_bottom -= mPlayer.move;
			mPlayer.s_top -= mPlayer.move;
			mPlayer.s_bottom -= mPlayer.move;

			//���g
			for (int i = 0; i <= 3; i++) {
				mPlayer.avatar_top[i] -= mPlayer.move;
				mPlayer.avatar_bottom[i] -= mPlayer.move;
			}

		}
		//�E
		else if (mPlayer.iNowAngle == 2) {
			mPlayer.x += mPlayer.move;
			//HitBox�ړ�
			mPlayer.p_left += mPlayer.move;
			mPlayer.p_right += mPlayer.move;
			mPlayer.s_left += mPlayer.move;
			mPlayer.s_right += mPlayer.move;

			//���g
			for (int i = 0; i <= 3; i++) {
				mPlayer.avatar_left[i] += mPlayer.move;
				mPlayer.avatar_right[i] += mPlayer.move;
			}
		}
		//��
		else if (mPlayer.iNowAngle == 3) {
			mPlayer.y += mPlayer.move;
			//HitBox�ړ�
			mPlayer.p_top += mPlayer.move;
			mPlayer.p_bottom += mPlayer.move;
			mPlayer.s_top += mPlayer.move;
			mPlayer.s_bottom += mPlayer.move;

			//���g
			for (int i = 0; i <= 3; i++) {
				mPlayer.avatar_top[i] += mPlayer.move;
				mPlayer.avatar_bottom[i] += mPlayer.move;
			}
		}
		//��
		else if (mPlayer.iNowAngle == 4) {
			mPlayer.x -= mPlayer.move;
			//HitBox�ړ�
			mPlayer.p_left -= mPlayer.move;
			mPlayer.p_right -= mPlayer.move;
			mPlayer.s_left -= mPlayer.move;
			mPlayer.s_right -= mPlayer.move;

			//���g
			for (int i = 0; i <= 3; i++) {
				mPlayer.avatar_right[i] -= mPlayer.move;
				mPlayer.avatar_left[i] -= mPlayer.move;
			}
		}
	}

	// ���[�v(���̂܂�)
	if (mPlayer.x >= 890) {
		mPlayer.x = 340;
		//HitBox�ړ�
		mPlayer.p_right = 340 + PLAYER_CENTER_HITBOX;
		mPlayer.p_left = 340 - PLAYER_CENTER_HITBOX;
		mPlayer.s_right = 340 + PLAYER_POS_HITBOX;
		mPlayer.s_left = 340 - PLAYER_POS_HITBOX;

		//���g
		//��
		mPlayer.avatar_right[0] = 340 + PLAYER_POS_HITBOX;
		mPlayer.avatar_left[0] = 340 - PLAYER_POS_HITBOX;
		//��
		mPlayer.avatar_left[2] = 340 - PLAYER_POS_HITBOX;
		mPlayer.avatar_right[2] = 340 + PLAYER_POS_HITBOX;
		//�E
		mPlayer.avatar_left[1] = 340 + 24 - PLAYER_POS_HITBOX;
		mPlayer.avatar_right[1] = 340 + 24 + PLAYER_POS_HITBOX;
		//��
		mPlayer.avatar_right[3] = 340 - 24 - PLAYER_POS_HITBOX;
		mPlayer.avatar_left[3] = 340 - 24 + PLAYER_POS_HITBOX;
	}
	else if (mPlayer.x <= 340) {
		mPlayer.x = 890;
		//HitBox�ړ�
		mPlayer.p_right = 890 + PLAYER_CENTER_HITBOX;
		mPlayer.p_left = 890 - PLAYER_CENTER_HITBOX;
		mPlayer.s_right = 890 + PLAYER_POS_HITBOX;
		mPlayer.s_left = 890 - PLAYER_POS_HITBOX;

		//���g
		//��
		mPlayer.avatar_right[0] = 890 + PLAYER_POS_HITBOX;
		mPlayer.avatar_left[0] = 890 - PLAYER_POS_HITBOX;
		//��
		mPlayer.avatar_left[2] = 890 - PLAYER_POS_HITBOX;
		mPlayer.avatar_right[2] = 890 + PLAYER_POS_HITBOX;
		//�E
		mPlayer.avatar_left[1] = 890 + 24 - PLAYER_POS_HITBOX;
		mPlayer.avatar_right[1] = 890 + 24 + PLAYER_POS_HITBOX;
		//��
		mPlayer.avatar_right[3] = 890 - 24 - PLAYER_POS_HITBOX;
		mPlayer.avatar_left[3] = 890 - 24 + PLAYER_POS_HITBOX;
	}
}
void Player::Player_Draw() {
	if (mPlayer.Hitflg == FALSE) {
		//Player�\��
		DrawRotaGraph(mPlayer.x, mPlayer.y, 0.75, 0, mPlayer.mPlayerMoveImage[mPlayer.image], TRUE, FALSE);
		mPlayer.deletecount = 0;
	}
	else if (mPlayer.Hitflg == TRUE) {
		mPlayer.deletecount++;

		if (mPlayer.deletecount % 5 == 0) {
			mPlayer.deleteimage++;
		}
		DrawRotaGraph(mPlayer.x, mPlayer.y, 0.75, 0, mPlayer.mPlayerDeleteImage[mPlayer.deleteimage], TRUE, FALSE);
	}
	//���g�̕\��
	for (int i = 0; i <= 3; i++) {
		DrawBox(mPlayer.avatar_left[i], mPlayer.avatar_top[i], mPlayer.avatar_right[i], mPlayer.avatar_bottom[i], 0x00ffff, FALSE);
	}

	if (mPlayer.Top == FALSE) {
		DrawString(0, 0, "�㐬��", 0xff00ff);
	}
	if (mPlayer.Right == FALSE) {
		DrawString(0, 20, "�E����", 0xff00ff);
	}
	if (mPlayer.Bottom == FALSE) {
		DrawString(0, 40, "������", 0xff00ff);
	}
	if (mPlayer.Left == FALSE) {
		DrawString(0, 60, "������", 0xff00ff);
	}
	if (mPlayer.P_StageHitflg == TRUE) {
		DrawString(0, 80, "�������Ă��܂�", 0xff00ff);
	}
	else if (mPlayer.P_StageHitflg == FALSE) {
		DrawString(0, 80, "�������Ă��܂���", 0xff00ff);
	}

	if (mPlayer.iNowAngle == 1) {
		DrawString(0, 100, "���݂̃A���O���͏�ł�", 0xff00ff);
	}
	else if (mPlayer.iNowAngle == 2) {
		DrawString(0, 100, "���݂̃A���O���͉E�ł�", 0xff00ff);
	} 
	else if (mPlayer.iNowAngle == 3) {
		DrawString(0, 100, "���݂̃A���O���͉��ł�", 0xff00ff);
	}
	else if (mPlayer.iNowAngle == 4) {
		DrawString(0, 100, "���݂̃A���O���͍��ł�", 0xff00ff);
	}

	if (mPlayer.iOldAngle == 1) {
		DrawString(0, 120, "�O��̃A���O���͏�ł�", 0xff00ff);
	}
	else if (mPlayer.iOldAngle == 2) {
		DrawString(0, 120, "�O��̃A���O���͉E�ł�", 0xff00ff);
	}
	else if (mPlayer.iOldAngle == 3) {
		DrawString(0, 120, "�O��̃A���O���͉��ł�", 0xff00ff);
	}
	else if (mPlayer.iOldAngle == 4) {
		DrawString(0, 120, "�O��̃A���O���͍��ł�", 0xff00ff);
	}
	//Stage�����蔻��\��
	DrawBox(mPlayer.s_left, mPlayer.s_top, mPlayer.s_right, mPlayer.s_bottom, 0x00ff00, FALSE);
	//Center�����蔻��\��
	DrawBox(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, 0xff00ff, TRUE);
}