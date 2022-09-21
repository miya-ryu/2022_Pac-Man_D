#include "DxLib.h"
#include "Red_Enemy.h"
#include "Player.h"
#include <math.h>
#include "Stage.h"

R_ENEMY r_enemy;

int EnemeyCheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
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

void R_ENEMY::Initialize() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);  // �G�L����
	LoadDivGraph("images/eyes.png", 4, 4, 1, 32, 32, eyesimages);  // �G�L�����̖�

	r_enemy.speed = 1;             // �ړ����x
	r_enemy.angle = 4;             // �����̌���
	r_enemy.count = 0;             // �A�j���[�V�����J�E���g
	r_enemy.ER_count = 0;          // �C�W�P��ԃJ�E���g
	r_enemy.image = 0;             // �摜�ϐ�
	r_enemy.eyeimage = 3;          // �ڂ̉摜�ϐ�
	r_enemy.izikeimage = 16;       // �C�W�P��Ԃ̉摜�ϐ�
	r_enemy.e_izikeimage = 16;     // �C�W�P��ԓ_�ł̉摜�ϐ�
	r_enemy.R_Hitflg = FALSE;      // �C�W�P��Ԕ���t���O
	r_enemy.ER_Hitflg = FALSE;     // �C�W�P��ԓ_�Ńt���O
	r_enemy.PR_Hitflg = FALSE;     // �C�W�P��ԂŃv���C���[�ɓ����������̃t���O
	r_enemy.eyeflg = FALSE;        // �G�l�~�[�ڏ��
	r_enemy.Initiaflg = FALSE;     // �G�l�~�[������
	r_enemy.HitCount = 0;          // �v���C���[���S���̃G�l�~�[�A�j���[�V����
	r_enemy.c = 0;                 // 
	r_enemy.flg = FALSE;           // 

	// �����ʒu��ۑ�
	r_enemy.x = ENEMY_POS_X;
	r_enemy.y = ENEMY_POS_Y;

	//�����蔻��
	r_enemy.recordX = r_enemy.x;
	r_enemy.recordY = r_enemy.y;

	r_enemy.top = ENEMY_POS_Y - ENEMY_POS_HITBOX;
	r_enemy.left = ENEMY_POS_X - ENEMY_POS_HITBOX;
	r_enemy.right = ENEMY_POS_X + ENEMY_POS_HITBOX;
	r_enemy.bottom = ENEMY_POS_Y + ENEMY_POS_HITBOX;

	r_enemy.recordTop = r_enemy.top;
	r_enemy.recordRight = r_enemy.right;
	r_enemy.recordBottom = r_enemy.bottom;
	r_enemy.recordLeft = r_enemy.left;

	// ���g�̏���������
	//���g�̃t���O����
	r_enemy.Top = FALSE;
	r_enemy.Bottom = FALSE;
	r_enemy.Left = TRUE;
	r_enemy.Right = TRUE;
	//���g�̍��W
	//��
	r_enemy.ENEMY_AVATAR_POS_X[0] = ENEMY_POS_X;
	r_enemy.ENEMY_AVATAR_POS_Y[0] = ENEMY_POS_Y - 24;
	//�E
	r_enemy.ENEMY_AVATAR_POS_X[1] = ENEMY_POS_X + 24;
	r_enemy.ENEMY_AVATAR_POS_Y[1] = ENEMY_POS_Y;
	//��
	r_enemy.ENEMY_AVATAR_POS_X[2] = ENEMY_POS_X;
	r_enemy.ENEMY_AVATAR_POS_Y[2] = ENEMY_POS_Y + 24;
	//��
	r_enemy.ENEMY_AVATAR_POS_X[3] = ENEMY_POS_X - 24;
	r_enemy.ENEMY_AVATAR_POS_Y[3] = ENEMY_POS_Y;

	// �O��̃L�[���͏���
	r_enemy.CheckNumber = 12;

	//���g�̓����蔻��
	for (int i = 0; i < 4; i++) {
		r_enemy.avatar_left[i] = ENEMY_AVATAR_POS_X[i] - ENEMY_POS_HITBOX;
		r_enemy.avatar_top[i] = ENEMY_AVATAR_POS_Y[i] - ENEMY_POS_HITBOX;
		r_enemy.avatar_right[i] = ENEMY_AVATAR_POS_X[i] + ENEMY_POS_HITBOX;
		r_enemy.avatar_bottom[i] = ENEMY_AVATAR_POS_Y[i] + ENEMY_POS_HITBOX;
	}
}

void R_ENEMY::Update() {
	//�O��̍��W�擾
	r_enemy.recordX = r_enemy.x;
	r_enemy.recordY = r_enemy.y;

	r_enemy.recordTop = r_enemy.top;
	r_enemy.recordRight = r_enemy.right;
	r_enemy.recordBottom = r_enemy.bottom;
	r_enemy.recordLeft = r_enemy.left;

	//���g�̍��W
	for (int i = 0; i < 4; i++) {
		r_enemy.record_avatar_bottom[i] = r_enemy.avatar_bottom[i];
		r_enemy.record_avatar_left[i] = r_enemy.avatar_left[i];
		r_enemy.record_avatar_right[i] = r_enemy.avatar_right[i];
		r_enemy.record_avatar_top[i] = r_enemy.avatar_top[i];
	}

	// �v���C���[��ǂ������鏈��
	if (r_enemy.R_Hitflg == FALSE && mStage.MoveFlg == TRUE && mPlayer.Hitflg == FALSE) { // �p���[�G�T������Ă��Ȃ���
		// �E����
		if (r_enemy.angle == 2) {
			if (r_enemy.Right == TRUE) {
				if (mPlayer.x < r_enemy.x) { // ������
					r_enemy.angle = 4;
				}
				else if (mPlayer.y < r_enemy.y) { // �����
					r_enemy.angle = 1;
				}
				else if (mPlayer.y > r_enemy.y) { // ������
					r_enemy.angle = 3;
				}
			}
			else if (r_enemy.Right == FALSE) {
				if (mPlayer.x < r_enemy.x) { // ������
					if (r_enemy.Left == FALSE) {
						r_enemy.angle = 4;
					}
				}
				else if (mPlayer.y < r_enemy.y) { // �����
					if (r_enemy.Top == FALSE) {
						r_enemy.angle = 1;
					}
				}
				else if (mPlayer.y > r_enemy.y) { // ������
					if (r_enemy.Bottom == FALSE) {
						r_enemy.angle = 3;
					}
				}
				// �E����
				r_enemy.x += r_enemy.speed;
				// �����蔻��
				r_enemy.left += r_enemy.speed;
				r_enemy.right += r_enemy.speed;
				//���g
				for (int i = 0; i < 4; i++) {
					r_enemy.avatar_right[i] += r_enemy.speed;
					r_enemy.avatar_left[i] += r_enemy.speed;
				}
				r_enemy.eyeimage = 1;
				//DrawString(0, 530, "�E�ɐi��ł��܂�", 0xff00ff);
			}
		}
		// ������
		else if (r_enemy.angle == 4) {
			if (r_enemy.Left == TRUE) {
				if (mPlayer.x > r_enemy.x) { // �E����
					r_enemy.angle = 2;
				}
				else if (mPlayer.y < r_enemy.y) { // �����
					r_enemy.angle = 1;
				}
				else if (mPlayer.y > r_enemy.y) { // ������
					r_enemy.angle = 3;
				}
			}
			else if (r_enemy.Left == FALSE) {
				if (mPlayer.x > r_enemy.x) { // �E����
					if (r_enemy.Right == FALSE) {
						r_enemy.angle = 2;
					}
				}
				else if (mPlayer.y < r_enemy.y) { // �����
					if (r_enemy.Top == FALSE) {
						r_enemy.angle = 1;
					}
				}
				else if (mPlayer.y > r_enemy.y) { // ������
					if (r_enemy.Bottom == FALSE) {
						r_enemy.angle = 3;
					}
				}
				// ������
				r_enemy.x -= r_enemy.speed;
				//�����蔻��
				r_enemy.left -= r_enemy.speed;
				r_enemy.right -= r_enemy.speed;
				//���g
				for (int i = 0; i < 4; i++) {
					r_enemy.avatar_right[i] -= r_enemy.speed;
					r_enemy.avatar_left[i] -= r_enemy.speed;
				}
				r_enemy.eyeimage = 3;
				//DrawString(0, 530, "���ɐi��ł��܂�", 0xff00ff);
			}
		}
		//������
		else if (r_enemy.angle == 3) {
			if (r_enemy.Bottom == TRUE) {
				if (mPlayer.x > r_enemy.x) { // �E����
					r_enemy.angle = 2;
				}
				else if (mPlayer.x < r_enemy.x) { // ������
					r_enemy.angle = 4;
				}
				else if (mPlayer.y < r_enemy.y) { // �����
					r_enemy.angle = 1;
				}
			}
			else if (r_enemy.Bottom == FALSE) {
				if (mPlayer.x > r_enemy.x) { // �E����
					if (r_enemy.Right == FALSE) {
						r_enemy.angle = 2;
					}
				}
				else if (mPlayer.x < r_enemy.x) { // ������
					if (r_enemy.Left == FALSE) {
						r_enemy.angle = 4;
					}
				}
				else if (mPlayer.y < r_enemy.y) { // �����
					if (r_enemy.Top == FALSE) {
						r_enemy.angle = 1;
					}
				}
				//������
				r_enemy.y += r_enemy.speed;
				//�����蔻��
				r_enemy.top += r_enemy.speed;
				r_enemy.bottom += r_enemy.speed;
				//���g
				for (int i = 0; i < 4; i++) {
					r_enemy.avatar_top[i] += r_enemy.speed;
					r_enemy.avatar_bottom[i] += r_enemy.speed;
				}
				r_enemy.eyeimage = 2;
				//DrawString(0, 530, "���ɐi��ł��܂�", 0xff00ff);
			}
		}
		//�����
		else if (r_enemy.angle == 1) {
			if (r_enemy.Top == TRUE) {
				if (mPlayer.x > r_enemy.x) { // �E����
					r_enemy.angle = 2;
				}
				else if (mPlayer.x < r_enemy.x) { // ������
					r_enemy.angle = 4;
				}
				else if (mPlayer.y > r_enemy.y) { // ������
					r_enemy.angle = 3;
				}
			}
			else if (r_enemy.Top == FALSE) {
				if (mPlayer.x > r_enemy.x) { // �E����
					if (r_enemy.Right == FALSE) {
						r_enemy.angle = 2;
					}
				}
				else if (mPlayer.x < r_enemy.x) { // ������
					if (r_enemy.Left == FALSE) {
						r_enemy.angle = 4;
					}
				}
				else if (mPlayer.y > r_enemy.y) { // ������
					if (r_enemy.Bottom == FALSE) {
						r_enemy.angle = 3;
					}
				}
				//�����
				r_enemy.y -= r_enemy.speed;
				//�����蔻��
				r_enemy.top -= r_enemy.speed;
				r_enemy.bottom -= r_enemy.speed;
				//���g
				for (int i = 0; i < 4; i++) {
					r_enemy.avatar_top[i] -= r_enemy.speed;
					r_enemy.avatar_bottom[i] -= r_enemy.speed;
				}
				r_enemy.eyeimage = 0;
				//DrawString(0, 530, "��ɐi��ł��܂�", 0xff00ff);
			}
		}
	}
	else if (r_enemy.R_Hitflg == TRUE) { // �p���[�G�T���������
		if (r_enemy.PR_Hitflg == FALSE) { // �v���C���[�Ɠ������Ă��Ȃ�������
			r_enemy.speed = 0.8;
			// �E����
			if (r_enemy.angle == 2) {
				if (r_enemy.Right == TRUE) {
					if (mPlayer.x < r_enemy.x) { // ������
						r_enemy.angle = 4;
					}
					else if (mPlayer.y < r_enemy.y) { // �����
						r_enemy.angle = 1;
					}
					else if (mPlayer.y > r_enemy.y) { // ������
						r_enemy.angle = 3;
					}
				}
				else if (r_enemy.Right == FALSE) {
					if (mPlayer.x < r_enemy.x) { // ������
						if (r_enemy.Left == FALSE) {
							r_enemy.angle = 4;
						}
					}
					else if (mPlayer.y < r_enemy.y) { // �����
						if (r_enemy.Top == FALSE) {
							r_enemy.angle = 1;
						}
					}
					else if (mPlayer.y > r_enemy.y) { // ������
						if (r_enemy.Bottom == FALSE) {
							r_enemy.angle = 3;
						}
					}
					// �E����
					r_enemy.x -= r_enemy.speed;
					// �����蔻��
					r_enemy.left -= r_enemy.speed;
					r_enemy.right -= r_enemy.speed;
					//���g
					for (int i = 0; i < 4; i++) {
						r_enemy.avatar_right[i] -= r_enemy.speed;
						r_enemy.avatar_left[i] -= r_enemy.speed;
					}
					//DrawString(0, 550, "���ɐi��ł��܂�", 0xff00ff);
				}
			}
			// ������
			else if (r_enemy.angle == 4) {
				if (r_enemy.Left == TRUE) {
					if (mPlayer.x > r_enemy.x) { // �E����
						r_enemy.angle = 2;
					}
					else if (mPlayer.y < r_enemy.y) { // �����
						r_enemy.angle = 1;
					}
					else if (mPlayer.y > r_enemy.y) { // ������
						r_enemy.angle = 3;
					}
				}
				else if (r_enemy.Left == FALSE) {
					if (mPlayer.x > r_enemy.x) { // �E����
						if (r_enemy.Right == FALSE) {
							r_enemy.angle = 2;
						}
					}
					else if (mPlayer.y < r_enemy.y) { // �����
						if (r_enemy.Top == FALSE) {
							r_enemy.angle = 1;
						}
					}
					else if (mPlayer.y > r_enemy.y) { // ������
						if (r_enemy.Bottom == FALSE) {
							r_enemy.angle = 3;
						}
					}
					// ������
					r_enemy.x += r_enemy.speed;
					//�����蔻��
					r_enemy.left += r_enemy.speed;
					r_enemy.right += r_enemy.speed;
					//���g
					for (int i = 0; i < 4; i++) {
						r_enemy.avatar_right[i] += r_enemy.speed;
						r_enemy.avatar_left[i] += r_enemy.speed;
					}
					//DrawString(0, 550, "�E�ɐi��ł��܂�", 0xff00ff);
				}
			}
			//������
			else if (r_enemy.angle == 3) {
				if (r_enemy.Bottom == TRUE) {
					if (mPlayer.x > r_enemy.x) { // �E����
						r_enemy.angle = 2;
					}
					else if (mPlayer.x < r_enemy.x) { // ������
						r_enemy.angle = 4;
					}
					else if (mPlayer.y < r_enemy.y) { // �����
						r_enemy.angle = 1;
					}
				}
				else if (r_enemy.Bottom == FALSE) {
					if (mPlayer.x > r_enemy.x) { // �E����
						if (r_enemy.Right == FALSE) {
							r_enemy.angle = 2;
						}
					}
					else if (mPlayer.x < r_enemy.x) { // ������
						if (r_enemy.Left == FALSE) {
							r_enemy.angle = 4;
						}
					}
					else if (mPlayer.y < r_enemy.y) { // �����
						if (r_enemy.Top == FALSE) {
							r_enemy.angle = 1;
						}
					}
					//������
					r_enemy.y -= r_enemy.speed;
					//�����蔻��
					r_enemy.top -= r_enemy.speed;
					r_enemy.bottom -= r_enemy.speed;
					//���g
					for (int i = 0; i < 4; i++) {
						r_enemy.avatar_top[i] -= r_enemy.speed;
						r_enemy.avatar_bottom[i] -= r_enemy.speed;
					}
					//DrawString(0, 530, "��ɐi��ł��܂�", 0xff00ff);
				}
			}
			//�����
			else if (r_enemy.angle == 1) {
				if (r_enemy.Top == TRUE) {
					if (mPlayer.x > r_enemy.x) { // �E����
						r_enemy.angle = 2;
					}
					else if (mPlayer.x < r_enemy.x) { // ������
						r_enemy.angle = 4;
					}
					else if (mPlayer.y > r_enemy.y) { // ������
						r_enemy.angle = 3;
					}
				}
				else if (r_enemy.Top == FALSE) {
					if (mPlayer.x > r_enemy.x) { // �E����
						if (r_enemy.Right == FALSE) {
							r_enemy.angle = 2;
						}
					}
					else if (mPlayer.x < r_enemy.x) { // ������
						if (r_enemy.Left == FALSE) {
							r_enemy.angle = 4;
						}
					}
					else if (mPlayer.y > r_enemy.y) { // ������
						if (r_enemy.Bottom == FALSE) {
							r_enemy.angle = 3;
						}
					}
					//�����
					r_enemy.y += r_enemy.speed;
					//�����蔻��
					r_enemy.top += r_enemy.speed;
					r_enemy.bottom += r_enemy.speed;
					//���g
					for (int i = 0; i < 4; i++) {
						r_enemy.avatar_top[i] += r_enemy.speed;
						r_enemy.avatar_bottom[i] += r_enemy.speed;
					}
					//DrawString(0, 530, "���ɐi��ł��܂�", 0xff00ff);
				}
			}
		}
		else if (r_enemy.PR_Hitflg == TRUE) { // �v���C���[�Ɠ������Ă����珉���ʒu�ɖ߂�
			if (r_enemy.eyeflg == TRUE) {
				r_enemy.speed = 3;
				// �E����
				if (r_enemy.angle == 2) {
					if (r_enemy.Right == TRUE) {
						if (ENEMY_POS_X < r_enemy.x) { // ������
							r_enemy.angle = 4;
						}
						else if (ENEMY_POS_Y < r_enemy.y) { // �����
							r_enemy.angle = 1;
						}
						else if (ENEMY_POS_Y > r_enemy.y) { // ������
							r_enemy.angle = 3;
						}
					}
					else if (r_enemy.Right == FALSE) {
						if (ENEMY_POS_X < r_enemy.x) { // ������
							if (r_enemy.Left == FALSE) {
								r_enemy.angle = 4;
							}
						}
						else if (ENEMY_POS_Y < r_enemy.y) { // �����
							if (r_enemy.Top == FALSE) {
								r_enemy.angle = 1;
							}
						}
						else if (ENEMY_POS_Y > r_enemy.y) { // ������
							if (r_enemy.Bottom == FALSE) {
								r_enemy.angle = 3;
							}
						}
						// �E����
						r_enemy.x += r_enemy.speed;
						// �����蔻��
						r_enemy.left += r_enemy.speed;
						r_enemy.right += r_enemy.speed;
						//���g
						for (int i = 0; i < 4; i++) {
							r_enemy.avatar_right[i] += r_enemy.speed;
							r_enemy.avatar_left[i] += r_enemy.speed;
						}
						r_enemy.eyeimage = 1;
						//DrawString(0, 530, "�E�ɐi��ł��܂�", 0xff00ff);
					}
				}
				// ������
				else if (r_enemy.angle == 4) {
					if (r_enemy.Left == TRUE) {
						if (ENEMY_POS_X > r_enemy.x) { // �E����
							r_enemy.angle = 2;
						}
						else if (ENEMY_POS_Y < r_enemy.y) { // �����
							r_enemy.angle = 1;
						}
						else if (ENEMY_POS_Y > r_enemy.y) { // ������
							r_enemy.angle = 3;
						}
					}
					else if (r_enemy.Left == FALSE) {
						if (ENEMY_POS_X > r_enemy.x) { // �E����
							if (r_enemy.Right == FALSE) {
								r_enemy.angle = 2;
							}
						}
						else if (ENEMY_POS_Y < r_enemy.y) { // �����
							if (r_enemy.Top == FALSE) {
								r_enemy.angle = 1;
							}
						}
						else if (ENEMY_POS_Y > r_enemy.y) { // ������
							if (r_enemy.Bottom == FALSE) {
								r_enemy.angle = 3;
							}
						}
						// ������
						r_enemy.x -= r_enemy.speed;
						//�����蔻��
						r_enemy.left -= r_enemy.speed;
						r_enemy.right -= r_enemy.speed;
						//���g
						for (int i = 0; i < 4; i++) {
							r_enemy.avatar_right[i] -= r_enemy.speed;
							r_enemy.avatar_left[i] -= r_enemy.speed;
						}
						r_enemy.eyeimage = 3;
						//DrawString(0, 530, "���ɐi��ł��܂�", 0xff00ff);
					}
				}
				//������
				else if (r_enemy.angle == 3) {
					if (r_enemy.Bottom == TRUE) {
						if (ENEMY_POS_X > r_enemy.x) { // �E����
							r_enemy.angle = 2;
						}
						else if (ENEMY_POS_X < r_enemy.x) { // ������
							r_enemy.angle = 4;
						}
						else if (ENEMY_POS_Y < r_enemy.y) { // �����
							r_enemy.angle = 1;
						}
					}
					else if (r_enemy.Bottom == FALSE) {
						if (ENEMY_POS_X > r_enemy.x) { // �E����
							if (r_enemy.Right == FALSE) {
								r_enemy.angle = 2;
							}
						}
						else if (ENEMY_POS_X < r_enemy.x) { // ������
							if (r_enemy.Left == FALSE) {
								r_enemy.angle = 4;
							}
						}
						else if (ENEMY_POS_Y < r_enemy.y) { // �����
							if (r_enemy.Top == FALSE) {
								r_enemy.angle = 1;
							}
						}
						//������
						r_enemy.y += r_enemy.speed;
						//�����蔻��
						r_enemy.top += r_enemy.speed;
						r_enemy.bottom += r_enemy.speed;
						//���g
						for (int i = 0; i < 4; i++) {
							r_enemy.avatar_top[i] += r_enemy.speed;
							r_enemy.avatar_bottom[i] += r_enemy.speed;
						}
						r_enemy.eyeimage = 2;
						//DrawString(0, 530, "���ɐi��ł��܂�", 0xff00ff);
					}
				}
				//�����
				else if (r_enemy.angle == 1) {
					if (r_enemy.Top == TRUE) {
						if (ENEMY_POS_X > r_enemy.x) { // �E����
							r_enemy.angle = 2;
						}
						else if (ENEMY_POS_X < r_enemy.x) { // ������
							r_enemy.angle = 4;
						}
						else if (ENEMY_POS_Y > r_enemy.y) { // ������
							r_enemy.angle = 3;
						}
					}
					else if (r_enemy.Top == FALSE) {
						if (ENEMY_POS_X > r_enemy.x) { // �E����
							if (r_enemy.Right == FALSE) {
								r_enemy.angle = 2;
							}
						}
						else if (ENEMY_POS_X < r_enemy.x) { // ������
							if (r_enemy.Left == FALSE) {
								r_enemy.angle = 4;
							}
						}
						else if (ENEMY_POS_Y > r_enemy.y) { // ������
							if (r_enemy.Bottom == FALSE) {
								r_enemy.angle = 3;
							}
						}
						//�����
						r_enemy.y -= r_enemy.speed;
						//�����蔻��
						r_enemy.top -= r_enemy.speed;
						r_enemy.bottom -= r_enemy.speed;
						//���g
						for (int i = 0; i < 4; i++) {
							r_enemy.avatar_top[i] -= r_enemy.speed;
							r_enemy.avatar_bottom[i] -= r_enemy.speed;
						}
						r_enemy.eyeimage = 0;
						//DrawString(0, 530, "��ɐi��ł��܂�", 0xff00ff);
					}
				}
				// �����ʒu�ɖ߂�����
				if (ENEMY_POS_X == r_enemy.x + 1) {
					r_enemy.eyeflg = FALSE;
					r_enemy.speed = 1;
				}
			}
		}
	}

	// �G�l�~�[�ƃv���C���[�̓����蔻��
	if (EnemeyCheckHit(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom)) {
		if (r_enemy.R_Hitflg == TRUE || r_enemy.ER_Hitflg == TRUE) { // �C�W�P��Ԃœ���������
			r_enemy.PR_Hitflg = TRUE;
			r_enemy.eyeflg = TRUE;
		}
	}

	// �A�j���[�V����
	++r_enemy.count;  // �J�E���g�J�n
	if (r_enemy.count >= 8) {  // �l�ɂ���ăA�j���[�V�����̃X�s�[�h���ω�����0�ɋ߂�������
		r_enemy.image++;
		r_enemy.izikeimage++;
		r_enemy.e_izikeimage++;
		r_enemy.count = 0;  // �J�E���g���Z�b�g
	}
	if (r_enemy.R_Hitflg == FALSE) { // �����C�W�P��ԂłȂ����
		if (r_enemy.image >= 2) { // �ʏ�̉摜�؂�ւ�
			r_enemy.image = 0;    // �摜���Z�b�g
		}
	}
	else if (r_enemy.R_Hitflg == TRUE) { // �����C�W�P��ԂȂ�
		if (r_enemy.izikeimage >= 18) { // �C�W�P�摜�؂�ւ�
			r_enemy.izikeimage = 16; // �摜���Z�b�g
		}
	}
	if (r_enemy.ER_Hitflg == TRUE) { // �����C�W�P��Ԃ��I��肻���Ȃ�
		if (r_enemy.e_izikeimage >= 20) { // �C�W�P�_�ŉ摜�؂�ւ�
			r_enemy.e_izikeimage = 16; // �摜���Z�b�g
		}
	}

	// ���[�v�g���l��
	if (r_enemy.x >= 878) {
		r_enemy.x = 352;

		//���g
		//��
		r_enemy.avatar_right[0] = 352 + ENEMY_POS_HITBOX;
		r_enemy.avatar_left[0] = 352 - ENEMY_POS_HITBOX;
		//��
		r_enemy.avatar_left[2] = 352 - ENEMY_POS_HITBOX;
		r_enemy.avatar_right[2] = 352 + ENEMY_POS_HITBOX;
		//�E
		r_enemy.avatar_left[1] = 352 + 24 - ENEMY_POS_HITBOX;
		r_enemy.avatar_right[1] = 352 + 24 + ENEMY_POS_HITBOX;
		//��
		r_enemy.avatar_right[3] = 352 - 24 - ENEMY_POS_HITBOX;
		r_enemy.avatar_left[3] = 352 - 24 + ENEMY_POS_HITBOX;
	}
	else if (r_enemy.x <= 352) {
		r_enemy.x = 878;

		//���g
		//��
		r_enemy.avatar_right[0] = 878 + ENEMY_POS_HITBOX;
		r_enemy.avatar_left[0] = 878 - ENEMY_POS_HITBOX;
		//��
		r_enemy.avatar_left[2] = 878 - ENEMY_POS_HITBOX;
		r_enemy.avatar_right[2] = 878 + ENEMY_POS_HITBOX;
		//�E
		r_enemy.avatar_left[1] = 878 + 24 - ENEMY_POS_HITBOX;
		r_enemy.avatar_right[1] = 878 + 24 + ENEMY_POS_HITBOX;
		//��
		r_enemy.avatar_right[3] = 878 - 24 - ENEMY_POS_HITBOX;
		r_enemy.avatar_left[3] = 878 - 24 + ENEMY_POS_HITBOX;
	}

	// �C�W�P��ԃt���O
	if (r_enemy.R_Hitflg == TRUE) {
		++r_enemy.ER_count;
	}
	// �v���C���[���S���̃G�l�~�[�A�j���[�V����
	if (mPlayer.Hitflg == TRUE) {
		r_enemy.HitCount++;
		int a = 5; int b = 10;
		if (r_enemy.HitCount == a ) {
			r_enemy.image = 0;
			a += 5;
		}
		else if (r_enemy.HitCount == b) {
			r_enemy.image = 1;
			b += 5;
		}
		if (r_enemy.HitCount == 80) {
			flg = TRUE;
		}
	}
}

void R_ENEMY::Draw() {
	//����������������
	if (mPlayer.Hitflg == TRUE && flg == FALSE) {
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, r_enemy.images[r_enemy.image], TRUE, FALSE);
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, r_enemy.eyesimages[r_enemy.eyeimage], TRUE, FALSE);
	}
	//PC�ɓ��������Ƃ��ɏ�����
	if (flg == TRUE) {
		/*DrawRotaGraph(r_enemy.x, r_enemy.y, 0, 0, images[r_enemy.image], TRUE, FALSE); 
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE); */
	}
	//�X�^�[�g�̎��̂ݔ�\��
	if (mStage.StateFlg == FALSE || mStage.GameOverFlg == TRUE) {
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0, 0, r_enemy.images[r_enemy.image], TRUE, FALSE);
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0, 0, r_enemy.eyesimages[r_enemy.eyeimage], TRUE, FALSE);
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0, 0, r_enemy.images[r_enemy.izikeimage], TRUE, FALSE);
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0, 0, r_enemy.images[r_enemy.e_izikeimage], TRUE, FALSE);
	}
	//�X�^�[�g���̌Œ�\��
	else if (mStage.StateFlg == TRUE){
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[0], TRUE, FALSE); 
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, eyesimages[3], TRUE, FALSE); 
	}
	// �p���[�G�T������Ă��Ȃ����AMoveflg�œ����ĉ\���APac�ɓ������Ă��Ȃ���
	if (r_enemy.R_Hitflg == FALSE && mStage.MoveFlg == TRUE && mPlayer.Hitflg == FALSE) {
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[r_enemy.image], TRUE, FALSE); // �G�L�����\��
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE); // �G�L�����̖ڕ\��
		//DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE); // �����蔻��`��
		//DrawString(0, 150, "�p���[�G�T�F����", 0x0000ff);
	}
	else if (r_enemy.R_Hitflg == TRUE) { // �p���[�G�T������Ă�����
		if (r_enemy.PR_Hitflg == FALSE) { // �v���C���[�Ɠ������Ă��Ȃ����
			if (r_enemy.ER_count <= 480) {
				DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, r_enemy.images[r_enemy.izikeimage], TRUE, FALSE); // �C�W�P��ԕ\��
				//DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE); // �����蔻��`��
				//DrawString(0, 150, "�p���[�G�T�F����F10�b�J�E���g", 0x0000ff);
			}
			else if (r_enemy.ER_count > 480 && r_enemy.ER_count <= 600) {
				r_enemy.ER_Hitflg = TRUE;
				DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, r_enemy.images[r_enemy.e_izikeimage], TRUE, FALSE); // �C�W�P��ԕ\��
				//DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE); // �����蔻��`��
				//DrawString(0, 150, "�p���[�G�T�F����F�c��2�b", 0x0000ff);
			}
			else {
				r_enemy.R_Hitflg = FALSE;
				r_enemy.ER_Hitflg = FALSE;
				r_enemy.ER_count = 0;
				mPlayer.timercount = 0;
			}
		}
		else if (r_enemy.PR_Hitflg == TRUE) { // �v���C���[�Ɠ������Ă�����
			if (r_enemy.eyeflg == TRUE) { // �ڏ�ԂɂȂ�����
				DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, r_enemy.eyesimages[r_enemy.eyeimage], TRUE, FALSE); // �G�L�����̖ڕ\��
				//DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE); // �����蔻��`��
				//DrawString(0, 150, "�p���[�G�T�F����F�v���C���[�ƐڐG", 0x0000ff);
			}
			else if (r_enemy.eyeflg == FALSE) { // �ڏ�Ԃ̃G�l�~�[�������ʒu�ɖ߂�����
				r_enemy.R_Hitflg = FALSE;
				r_enemy.PR_Hitflg = FALSE;
				r_enemy.ER_Hitflg = FALSE;
				r_enemy.ER_count = 0;
				mPlayer.timercount = 0;
				//DrawString(0, 150, "�p���[�G�T�F�����F�����ʒu�ɖ߂�܂���", 0x0000ff);
			}
		}
	}

	if (r_enemy.Initiaflg == TRUE) {
		// �����ʒu�ɖ߂�
		r_enemy.x = ENEMY_POS_X;
		r_enemy.y = ENEMY_POS_Y;
		r_enemy.top = ENEMY_POS_Y - ENEMY_POS_HITBOX;
		r_enemy.left = ENEMY_POS_X - ENEMY_POS_HITBOX;
		r_enemy.right = ENEMY_POS_X + ENEMY_POS_HITBOX;
		r_enemy.bottom = ENEMY_POS_Y + ENEMY_POS_HITBOX;
		r_enemy.Initiaflg = FALSE;

		//���g�̓����蔻��
		for (int i = 0; i < 4; i++) {
			r_enemy.avatar_left[i] = ENEMY_AVATAR_POS_X[i] - ENEMY_POS_HITBOX;
			r_enemy.avatar_top[i] = ENEMY_AVATAR_POS_Y[i] - ENEMY_POS_HITBOX;
			r_enemy.avatar_right[i] = ENEMY_AVATAR_POS_X[i] + ENEMY_POS_HITBOX;
			r_enemy.avatar_bottom[i] = ENEMY_AVATAR_POS_Y[i] + ENEMY_POS_HITBOX;
		}

		r_enemy.flg = FALSE;
		r_enemy.HitCount = 0;

		if (mStage.life == 2) {
			//mStage.life = 1;
			mStage.GameOverFlg = TRUE;
		}
		/*else if(mStage.life == 1) {
			mStage.life = 0;
		}
		else if(mStage.life == 0){
			mStage.GameOverFlg = TRUE;
		}*/
	}

	////���g�̕\��
	//for (int i = 0; i < 4; i++) {
	//	DrawBox(r_enemy.avatar_left[i], r_enemy.avatar_top[i], r_enemy.avatar_right[i], r_enemy.avatar_bottom[i], 0x00ffff, FALSE);
	//}

	/*if (r_enemy.Top == FALSE) {
		DrawString(0, 410, "�㐬��", 0xff00ff);
	}
	if (r_enemy.Right == FALSE) {
		DrawString(0, 430, "�E����", 0xff00ff);
	}
	if (r_enemy.Bottom == FALSE) {
		DrawString(0, 450, "������", 0xff00ff);
	}
	if (r_enemy.Left == FALSE) {
		DrawString(0, 470, "������", 0xff00ff);
	}

	if (r_enemy.angle == 1) {
		DrawString(0, 510, "���݂̃A���O���͏�ł�", 0xff00ff);
	}
	else if (r_enemy.angle == 2) {
		DrawString(0, 510, "���݂̃A���O���͉E�ł�", 0xff00ff);
	}
	else if (r_enemy.angle == 3) {
		DrawString(0, 510, "���݂̃A���O���͉��ł�", 0xff00ff);
	}
	else if (r_enemy.angle == 4) {
		DrawString(0, 510, "���݂̃A���O���͍��ł�", 0xff00ff);
	}*/

	////�i�߂鎞
	////��
	//if (r_enemy.Top == TRUE) {
	//	DrawBox(r_enemy.avatar_left[0], r_enemy.avatar_top[0], r_enemy.avatar_right[0], r_enemy.avatar_bottom[0], 0xff00ff, true);
	//}
	//else if (r_enemy.Top == FALSE) {
	//	DrawBox(r_enemy.avatar_left[0], r_enemy.avatar_top[0], r_enemy.avatar_right[0], r_enemy.avatar_bottom[0], 0xff0000, true);
	//}
	////�E
	//if (r_enemy.Right == TRUE) {
	//	DrawBox(r_enemy.avatar_left[1], r_enemy.avatar_top[1], r_enemy.avatar_right[1], r_enemy.avatar_bottom[1], 0xff00ff, true);
	//}
	//else if (r_enemy.Right == FALSE) {
	//	DrawBox(r_enemy.avatar_left[1], r_enemy.avatar_top[1], r_enemy.avatar_right[1], r_enemy.avatar_bottom[1], 0xff0000, true);
	//}
	////��
	//if (r_enemy.Bottom == TRUE) {
	//	DrawBox(r_enemy.avatar_left[2], r_enemy.avatar_top[2], r_enemy.avatar_right[2], r_enemy.avatar_bottom[2], 0xff00ff, true);
	//}
	//else if (r_enemy.Bottom == FALSE) {
	//	DrawBox(r_enemy.avatar_left[2], r_enemy.avatar_top[2], r_enemy.avatar_right[2], r_enemy.avatar_bottom[2], 0xff0000, true);
	//}
	////��
	//if (r_enemy.Left == TRUE) {
	//	DrawBox(r_enemy.avatar_left[3], r_enemy.avatar_top[3], r_enemy.avatar_right[3], r_enemy.avatar_bottom[3], 0xff00ff, true);
	//}
	//else if (r_enemy.Left == FALSE) {
	//	DrawBox(r_enemy.avatar_left[3], r_enemy.avatar_top[3], r_enemy.avatar_right[3], r_enemy.avatar_bottom[3], 0xff0000, true);
	//}
}