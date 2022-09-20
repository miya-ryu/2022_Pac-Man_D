#include "DxLib.h"
#include "Orange_Enemy.h"
#include "Player.h"
#include <math.h>
#include "Stage.h"

O_ENEMY o_enemy;

int O_EnemeyCheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
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

void O_ENEMY::Initialize() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);  // �G�L����
	LoadDivGraph("images/eyes.png", 4, 4, 1, 32, 32, eyesimages);  // �G�L�����̖�

	o_enemy.speed = 1;             // �ړ����x
	o_enemy.angle = 1;             // �����̌���
	o_enemy.count = 0;             // �A�j���[�V�����J�E���g
	o_enemy.ER_count = 0;          // �C�W�P��ԃJ�E���g
	o_enemy.image = 6;             // �摜�ϐ�
	o_enemy.eyeimage = 0;          // �ڂ̉摜�ϐ�
	o_enemy.izikeimage = 16;       // �C�W�P��Ԃ̉摜�ϐ�
	o_enemy.e_izikeimage = 16;     // �C�W�P��ԓ_�ł̉摜�ϐ�
	o_enemy.R_Hitflg = FALSE;      // �C�W�P��Ԕ���t���O
	o_enemy.ER_Hitflg = FALSE;     // �C�W�P��ԓ_�Ńt���O
	o_enemy.PR_Hitflg = FALSE;     // �C�W�P��ԂŃv���C���[�ɓ����������̃t���O
	o_enemy.eyeflg = FALSE;        // �G�l�~�[�ڏ��
	o_enemy.Initiaflg = FALSE;     // �G�l�~�[������
	o_enemy.HitCount = 0;          // �v���C���[���S���̃G�l�~�[�A�j���[�V����
	o_enemy.c = 0;                 // 
	o_enemy.flg = FALSE;           // 

	// �����ʒu��ۑ�
	o_enemy.x = O_ENEMY_POS_X;
	o_enemy.y = O_ENEMY_POS_Y;

	//�����蔻��
	o_enemy.recordX = o_enemy.x;
	o_enemy.recordY = o_enemy.y;

	o_enemy.top = O_ENEMY_POS_Y - O_ENEMY_POS_HITBOX;
	o_enemy.left = O_ENEMY_POS_X - O_ENEMY_POS_HITBOX;
	o_enemy.right = O_ENEMY_POS_X + O_ENEMY_POS_HITBOX;
	o_enemy.bottom = O_ENEMY_POS_Y + O_ENEMY_POS_HITBOX;

	o_enemy.recordTop = o_enemy.top;
	o_enemy.recordRight = o_enemy.right;
	o_enemy.recordBottom = o_enemy.bottom;
	o_enemy.recordLeft = o_enemy.left;

	// ���g�̏���������
	//���g�̃t���O����
	o_enemy.Top = FALSE;
	o_enemy.Bottom = FALSE;
	o_enemy.Left = TRUE;
	o_enemy.Right = TRUE;
	//���g�̍��W
	//��
	o_enemy.ENEMY_AVATAR_POS_X[0] = O_ENEMY_POS_X;
	o_enemy.ENEMY_AVATAR_POS_Y[0] = O_ENEMY_POS_Y - 24;
	//�E
	o_enemy.ENEMY_AVATAR_POS_X[1] = O_ENEMY_POS_X + 24;
	o_enemy.ENEMY_AVATAR_POS_Y[1] = O_ENEMY_POS_Y;
	//��
	o_enemy.ENEMY_AVATAR_POS_X[2] = O_ENEMY_POS_X;
	o_enemy.ENEMY_AVATAR_POS_Y[2] = O_ENEMY_POS_Y + 24;
	//��
	o_enemy.ENEMY_AVATAR_POS_X[3] = O_ENEMY_POS_X - 24;
	o_enemy.ENEMY_AVATAR_POS_Y[3] = O_ENEMY_POS_Y;

	// �O��̃L�[���͏���
	o_enemy.CheckNumber = 12;

	//���g�̓����蔻��
	for (int i = 0; i < 4; i++) {
		o_enemy.avatar_left[i] = ENEMY_AVATAR_POS_X[i] - O_ENEMY_POS_HITBOX;
		o_enemy.avatar_top[i] = ENEMY_AVATAR_POS_Y[i] - O_ENEMY_POS_HITBOX;
		o_enemy.avatar_right[i] = ENEMY_AVATAR_POS_X[i] + O_ENEMY_POS_HITBOX;
		o_enemy.avatar_bottom[i] = ENEMY_AVATAR_POS_Y[i] + O_ENEMY_POS_HITBOX;
	}
}

void O_ENEMY::Update() {
	//�O��̍��W�擾
	o_enemy.recordX = o_enemy.x;
	o_enemy.recordY = o_enemy.y;

	o_enemy.recordTop = o_enemy.top;
	o_enemy.recordRight = o_enemy.right;
	o_enemy.recordBottom = o_enemy.bottom;
	o_enemy.recordLeft = o_enemy.left;

	//���g�̍��W
	for (int i = 0; i < 4; i++) {
		o_enemy.record_avatar_bottom[i] = o_enemy.avatar_bottom[i];
		o_enemy.record_avatar_left[i] = o_enemy.avatar_left[i];
		o_enemy.record_avatar_right[i] = o_enemy.avatar_right[i];
		o_enemy.record_avatar_top[i] = o_enemy.avatar_top[i];
	}

	//�������
	if (mStage.numc < 32 && mStage.MoveFlg == TRUE && mPlayer.Hitflg == FALSE) {
		// �����
		if (o_enemy.angle == 1) {
			if (o_enemy.Top == TRUE) {
				o_enemy.angle = 3;
			}
			else if (o_enemy.Top == FALSE) {
				if (o_enemy.Bottom == FALSE) {
					o_enemy.angle = 3;
				}
				//�����
				o_enemy.y -= o_enemy.speed;
				//�����蔻��
				o_enemy.top -= o_enemy.speed;
				o_enemy.bottom -= o_enemy.speed;
				//���g
				for (int i = 0; i < 4; i++) {
					o_enemy.avatar_top[i] -= o_enemy.speed;
					o_enemy.avatar_bottom[i] -= o_enemy.speed;
				}
				o_enemy.eyeimage = 0;
			}
		}
		//������
		else if (o_enemy.angle == 3) {
			if (o_enemy.Bottom == TRUE) {
				o_enemy.angle = 1;
			}
			else if (o_enemy.Bottom == FALSE) {
				if (o_enemy.Top == FALSE) {
					o_enemy.angle = 1;
				}
				//������
				o_enemy.y += o_enemy.speed;
				//�����蔻��
				o_enemy.top += o_enemy.speed;
				o_enemy.bottom += o_enemy.speed;
				//���g
				for (int i = 0; i < 4; i++) {
					o_enemy.avatar_top[i] += o_enemy.speed;
					o_enemy.avatar_bottom[i] += o_enemy.speed;
				}
				o_enemy.eyeimage = 2;
			}
		}
	}
	else if (mStage.numc > 31) {
		// �v���C���[��ǂ������鏈��
		if (o_enemy.R_Hitflg == FALSE && mStage.MoveFlg == TRUE && mPlayer.Hitflg == FALSE) { // �p���[�G�T������Ă��Ȃ���
			// �E����
			if (o_enemy.angle == 2) {
				if (o_enemy.Right == TRUE) {
					if (mPlayer.x < o_enemy.x) { // ������
						o_enemy.angle = 4;
					}
					else if (mPlayer.y < o_enemy.y) { // �����
						o_enemy.angle = 1;
					}
					else if (mPlayer.y > o_enemy.y) { // ������
						o_enemy.angle = 3;
					}
				}
				else if (o_enemy.Right == FALSE) {
					if (mPlayer.x < o_enemy.x) { // ������
						if (o_enemy.Left == FALSE) {
							o_enemy.angle = 4;
						}
					}
					else if (mPlayer.y < o_enemy.y) { // �����
						if (o_enemy.Top == FALSE) {
							o_enemy.angle = 1;
						}
					}
					else if (mPlayer.y > o_enemy.y) { // ������
						if (o_enemy.Bottom == FALSE) {
							o_enemy.angle = 3;
						}
					}
					// �E����
					o_enemy.x += o_enemy.speed;
					// �����蔻��
					o_enemy.left += o_enemy.speed;
					o_enemy.right += o_enemy.speed;
					//���g
					for (int i = 0; i < 4; i++) {
						o_enemy.avatar_right[i] += o_enemy.speed;
						o_enemy.avatar_left[i] += o_enemy.speed;
					}
					o_enemy.eyeimage = 1;
				}
			}
			// ������
			else if (o_enemy.angle == 4) {
				if (o_enemy.Left == TRUE) {
					if (mPlayer.x > o_enemy.x) { // �E����
						o_enemy.angle = 2;
					}
					else if (mPlayer.y < o_enemy.y) { // �����
						o_enemy.angle = 1;
					}
					else if (mPlayer.y > o_enemy.y) { // ������
						o_enemy.angle = 3;
					}
				}
				else if (o_enemy.Left == FALSE) {
					if (mPlayer.x > o_enemy.x) { // �E����
						if (o_enemy.Right == FALSE) {
							o_enemy.angle = 2;
						}
					}
					else if (mPlayer.y < o_enemy.y) { // �����
						if (o_enemy.Top == FALSE) {
							o_enemy.angle = 1;
						}
					}
					else if (mPlayer.y > o_enemy.y) { // ������
						if (o_enemy.Bottom == FALSE) {
							o_enemy.angle = 3;
						}
					}
					// ������
					o_enemy.x -= o_enemy.speed;
					//�����蔻��
					o_enemy.left -= o_enemy.speed;
					o_enemy.right -= o_enemy.speed;
					//���g
					for (int i = 0; i < 4; i++) {
						o_enemy.avatar_right[i] -= o_enemy.speed;
						o_enemy.avatar_left[i] -= o_enemy.speed;
					}
					o_enemy.eyeimage = 3;
				}
			}
			//������
			else if (o_enemy.angle == 3) {
				if (o_enemy.Bottom == TRUE) {
					if (mPlayer.x > o_enemy.x) { // �E����
						o_enemy.angle = 2;
					}
					else if (mPlayer.x < o_enemy.x) { // ������
						o_enemy.angle = 4;
					}
					else if (mPlayer.y < o_enemy.y) { // �����
						o_enemy.angle = 1;
					}
				}
				else if (o_enemy.Bottom == FALSE) {
					if (mPlayer.x > o_enemy.x) { // �E����
						if (o_enemy.Right == FALSE) {
							o_enemy.angle = 2;
						}
					}
					else if (mPlayer.x < o_enemy.x) { // ������
						if (o_enemy.Left == FALSE) {
							o_enemy.angle = 4;
						}
					}
					else if (mPlayer.y < o_enemy.y) { // �����
						if (o_enemy.Top == FALSE) {
							o_enemy.angle = 1;
						}
					}
					//������
					o_enemy.y += o_enemy.speed;
					//�����蔻��
					o_enemy.top += o_enemy.speed;
					o_enemy.bottom += o_enemy.speed;
					//���g
					for (int i = 0; i < 4; i++) {
						o_enemy.avatar_top[i] += o_enemy.speed;
						o_enemy.avatar_bottom[i] += o_enemy.speed;
					}
					o_enemy.eyeimage = 2;
				}
			}
			//�����
			else if (o_enemy.angle == 1) {
				if (o_enemy.Top == TRUE) {
					if (mPlayer.x > o_enemy.x) { // �E����
						o_enemy.angle = 2;
					}
					else if (mPlayer.x < o_enemy.x) { // ������
						o_enemy.angle = 4;
					}
					else if (mPlayer.y > o_enemy.y) { // ������
						o_enemy.angle = 3;
					}
				}
				else if (o_enemy.Top == FALSE) {
					if (mPlayer.x > o_enemy.x) { // �E����
						if (o_enemy.Right == FALSE) {
							o_enemy.angle = 2;
						}
					}
					else if (mPlayer.x < o_enemy.x) { // ������
						if (o_enemy.Left == FALSE) {
							o_enemy.angle = 4;
						}
					}
					else if (mPlayer.y > o_enemy.y) { // ������
						if (o_enemy.Bottom == FALSE) {
							o_enemy.angle = 3;
						}
					}
					//�����
					o_enemy.y -= o_enemy.speed;
					//�����蔻��
					o_enemy.top -= o_enemy.speed;
					o_enemy.bottom -= o_enemy.speed;
					//���g
					for (int i = 0; i < 4; i++) {
						o_enemy.avatar_top[i] -= o_enemy.speed;
						o_enemy.avatar_bottom[i] -= o_enemy.speed;
					}
					o_enemy.eyeimage = 0;
				}
			}
		}
		else if (o_enemy.R_Hitflg == TRUE) { // �p���[�G�T���������
			if (o_enemy.PR_Hitflg == FALSE) { // �v���C���[�Ɠ������Ă��Ȃ�������
				o_enemy.speed = 0.8;
				// �E����
				if (o_enemy.angle == 2) {
					if (o_enemy.Right == TRUE) {
						if (mPlayer.x < o_enemy.x) { // ������
							o_enemy.angle = 4;
						}
						else if (mPlayer.y < o_enemy.y) { // �����
							o_enemy.angle = 1;
						}
						else if (mPlayer.y > o_enemy.y) { // ������
							o_enemy.angle = 3;
						}
					}
					else if (o_enemy.Right == FALSE) {
						if (mPlayer.x < o_enemy.x) { // ������
							if (o_enemy.Left == FALSE) {
								o_enemy.angle = 4;
							}
						}
						else if (mPlayer.y < o_enemy.y) { // �����
							if (o_enemy.Top == FALSE) {
								o_enemy.angle = 1;
							}
						}
						else if (mPlayer.y > o_enemy.y) { // ������
							if (o_enemy.Bottom == FALSE) {
								o_enemy.angle = 3;
							}
						}
						// �E����
						o_enemy.x -= o_enemy.speed;
						// �����蔻��
						o_enemy.left -= o_enemy.speed;
						o_enemy.right -= o_enemy.speed;
						//���g
						for (int i = 0; i < 4; i++) {
							o_enemy.avatar_right[i] -= o_enemy.speed;
							o_enemy.avatar_left[i] -= o_enemy.speed;
						}
					}
				}
				// ������
				else if (o_enemy.angle == 4) {
					if (o_enemy.Left == TRUE) {
						if (mPlayer.x > o_enemy.x) { // �E����
							o_enemy.angle = 2;
						}
						else if (mPlayer.y < o_enemy.y) { // �����
							o_enemy.angle = 1;
						}
						else if (mPlayer.y > o_enemy.y) { // ������
							o_enemy.angle = 3;
						}
					}
					else if (o_enemy.Left == FALSE) {
						if (mPlayer.x > o_enemy.x) { // �E����
							if (o_enemy.Right == FALSE) {
								o_enemy.angle = 2;
							}
						}
						else if (mPlayer.y < o_enemy.y) { // �����
							if (o_enemy.Top == FALSE) {
								o_enemy.angle = 1;
							}
						}
						else if (mPlayer.y > o_enemy.y) { // ������
							if (o_enemy.Bottom == FALSE) {
								o_enemy.angle = 3;
							}
						}
						// ������
						o_enemy.x += o_enemy.speed;
						//�����蔻��
						o_enemy.left += o_enemy.speed;
						o_enemy.right += o_enemy.speed;
						//���g
						for (int i = 0; i < 4; i++) {
							o_enemy.avatar_right[i] += o_enemy.speed;
							o_enemy.avatar_left[i] += o_enemy.speed;
						}
					}
				}
				//������
				else if (o_enemy.angle == 3) {
					if (o_enemy.Bottom == TRUE) {
						if (mPlayer.x > o_enemy.x) { // �E����
							o_enemy.angle = 2;
						}
						else if (mPlayer.x < o_enemy.x) { // ������
							o_enemy.angle = 4;
						}
						else if (mPlayer.y < o_enemy.y) { // �����
							o_enemy.angle = 1;
						}
					}
					else if (o_enemy.Bottom == FALSE) {
						if (mPlayer.x > o_enemy.x) { // �E����
							if (o_enemy.Right == FALSE) {
								o_enemy.angle = 2;
							}
						}
						else if (mPlayer.x < o_enemy.x) { // ������
							if (o_enemy.Left == FALSE) {
								o_enemy.angle = 4;
							}
						}
						else if (mPlayer.y < o_enemy.y) { // �����
							if (o_enemy.Top == FALSE) {
								o_enemy.angle = 1;
							}
						}
						//������
						o_enemy.y -= o_enemy.speed;
						//�����蔻��
						o_enemy.top -= o_enemy.speed;
						o_enemy.bottom -= o_enemy.speed;
						//���g
						for (int i = 0; i < 4; i++) {
							o_enemy.avatar_top[i] -= o_enemy.speed;
							o_enemy.avatar_bottom[i] -= o_enemy.speed;
						}
					}
				}
				//�����
				else if (o_enemy.angle == 1) {
					if (o_enemy.Top == TRUE) {
						if (mPlayer.x > o_enemy.x) { // �E����
							o_enemy.angle = 2;
						}
						else if (mPlayer.x < o_enemy.x) { // ������
							o_enemy.angle = 4;
						}
						else if (mPlayer.y > o_enemy.y) { // ������
							o_enemy.angle = 3;
						}
					}
					else if (o_enemy.Top == FALSE) {
						if (mPlayer.x > o_enemy.x) { // �E����
							if (o_enemy.Right == FALSE) {
								o_enemy.angle = 2;
							}
						}
						else if (mPlayer.x < o_enemy.x) { // ������
							if (o_enemy.Left == FALSE) {
								o_enemy.angle = 4;
							}
						}
						else if (mPlayer.y > o_enemy.y) { // ������
							if (o_enemy.Bottom == FALSE) {
								o_enemy.angle = 3;
							}
						}
						//�����
						o_enemy.y += o_enemy.speed;
						//�����蔻��
						o_enemy.top += o_enemy.speed;
						o_enemy.bottom += o_enemy.speed;
						//���g
						for (int i = 0; i < 4; i++) {
							o_enemy.avatar_top[i] += o_enemy.speed;
							o_enemy.avatar_bottom[i] += o_enemy.speed;
						}
					}
				}
			}
			else if (o_enemy.PR_Hitflg == TRUE) { // �v���C���[�Ɠ������Ă����珉���ʒu�ɖ߂�
				if (o_enemy.eyeflg == TRUE) {
					o_enemy.speed = 3;
					// �E����
					if (o_enemy.angle == 2) {
						if (o_enemy.Right == TRUE) {
							if (ENEMY_POS_X < o_enemy.x) { // ������
								o_enemy.angle = 4;
							}
							else if (ENEMY_POS_Y < o_enemy.y) { // �����
								o_enemy.angle = 1;
							}
							else if (ENEMY_POS_Y > o_enemy.y) { // ������
								o_enemy.angle = 3;
							}
						}
						else if (o_enemy.Right == FALSE) {
							if (ENEMY_POS_X < o_enemy.x) { // ������
								if (o_enemy.Left == FALSE) {
									o_enemy.angle = 4;
								}
							}
							else if (ENEMY_POS_Y < o_enemy.y) { // �����
								if (o_enemy.Top == FALSE) {
									o_enemy.angle = 1;
								}
							}
							else if (ENEMY_POS_Y > o_enemy.y) { // ������
								if (o_enemy.Bottom == FALSE) {
									o_enemy.angle = 3;
								}
							}
							// �E����
							o_enemy.x += o_enemy.speed;
							// �����蔻��
							o_enemy.left += o_enemy.speed;
							o_enemy.right += o_enemy.speed;
							//���g
							for (int i = 0; i < 4; i++) {
								o_enemy.avatar_right[i] += o_enemy.speed;
								o_enemy.avatar_left[i] += o_enemy.speed;
							}
							o_enemy.eyeimage = 1;
						}
					}
					// ������
					else if (o_enemy.angle == 4) {
						if (o_enemy.Left == TRUE) {
							if (ENEMY_POS_X > o_enemy.x) { // �E����
								o_enemy.angle = 2;
							}
							else if (ENEMY_POS_Y < o_enemy.y) { // �����
								o_enemy.angle = 1;
							}
							else if (ENEMY_POS_Y > o_enemy.y) { // ������
								o_enemy.angle = 3;
							}
						}
						else if (o_enemy.Left == FALSE) {
							if (ENEMY_POS_X > o_enemy.x) { // �E����
								if (o_enemy.Right == FALSE) {
									o_enemy.angle = 2;
								}
							}
							else if (ENEMY_POS_Y < o_enemy.y) { // �����
								if (o_enemy.Top == FALSE) {
									o_enemy.angle = 1;
								}
							}
							else if (ENEMY_POS_Y > o_enemy.y) { // ������
								if (o_enemy.Bottom == FALSE) {
									o_enemy.angle = 3;
								}
							}
							// ������
							o_enemy.x -= o_enemy.speed;
							//�����蔻��
							o_enemy.left -= o_enemy.speed;
							o_enemy.right -= o_enemy.speed;
							//���g
							for (int i = 0; i < 4; i++) {
								o_enemy.avatar_right[i] -= o_enemy.speed;
								o_enemy.avatar_left[i] -= o_enemy.speed;
							}
							o_enemy.eyeimage = 3;
						}
					}
					//������
					else if (o_enemy.angle == 3) {
						if (o_enemy.Bottom == TRUE) {
							if (ENEMY_POS_X > o_enemy.x) { // �E����
								o_enemy.angle = 2;
							}
							else if (ENEMY_POS_X < o_enemy.x) { // ������
								o_enemy.angle = 4;
							}
							else if (ENEMY_POS_Y < o_enemy.y) { // �����
								o_enemy.angle = 1;
							}
						}
						else if (o_enemy.Bottom == FALSE) {
							if (ENEMY_POS_X > o_enemy.x) { // �E����
								if (o_enemy.Right == FALSE) {
									o_enemy.angle = 2;
								}
							}
							else if (ENEMY_POS_X < o_enemy.x) { // ������
								if (o_enemy.Left == FALSE) {
									o_enemy.angle = 4;
								}
							}
							else if (ENEMY_POS_Y < o_enemy.y) { // �����
								if (o_enemy.Top == FALSE) {
									o_enemy.angle = 1;
								}
							}
							//������
							o_enemy.y += o_enemy.speed;
							//�����蔻��
							o_enemy.top += o_enemy.speed;
							o_enemy.bottom += o_enemy.speed;
							//���g
							for (int i = 0; i < 4; i++) {
								o_enemy.avatar_top[i] += o_enemy.speed;
								o_enemy.avatar_bottom[i] += o_enemy.speed;
							}
							o_enemy.eyeimage = 2;
						}
					}
					//�����
					else if (o_enemy.angle == 1) {
						if (o_enemy.Top == TRUE) {
							if (ENEMY_POS_X > o_enemy.x) { // �E����
								o_enemy.angle = 2;
							}
							else if (ENEMY_POS_X < o_enemy.x) { // ������
								o_enemy.angle = 4;
							}
							else if (ENEMY_POS_Y > o_enemy.y) { // ������
								o_enemy.angle = 3;
							}
						}
						else if (o_enemy.Top == FALSE) {
							if (ENEMY_POS_X > o_enemy.x) { // �E����
								if (o_enemy.Right == FALSE) {
									o_enemy.angle = 2;
								}
							}
							else if (ENEMY_POS_X < o_enemy.x) { // ������
								if (o_enemy.Left == FALSE) {
									o_enemy.angle = 4;
								}
							}
							else if (ENEMY_POS_Y > o_enemy.y) { // ������
								if (o_enemy.Bottom == FALSE) {
									o_enemy.angle = 3;
								}
							}
							//�����
							o_enemy.y -= o_enemy.speed;
							//�����蔻��
							o_enemy.top -= o_enemy.speed;
							o_enemy.bottom -= o_enemy.speed;
							//���g
							for (int i = 0; i < 4; i++) {
								o_enemy.avatar_top[i] -= o_enemy.speed;
								o_enemy.avatar_bottom[i] -= o_enemy.speed;
							}
							o_enemy.eyeimage = 0;
						}
					}
					// �����ʒu�ɖ߂�����
					if (ENEMY_POS_X == o_enemy.x) {
						o_enemy.eyeflg = FALSE;
					}
				}
			}
		}
	}

	// �G�l�~�[�ƃv���C���[�̓����蔻��
	if (O_EnemeyCheckHit(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, o_enemy.left, o_enemy.top, o_enemy.right, o_enemy.bottom)) {
		if (o_enemy.R_Hitflg == TRUE || o_enemy.ER_Hitflg == TRUE) { // �C�W�P��Ԃœ���������
			o_enemy.PR_Hitflg = TRUE;
			o_enemy.eyeflg = TRUE;
		}
	}

	// �A�j���[�V����
	++o_enemy.count;  // �J�E���g�J�n
	if (o_enemy.count >= 8) {  // �l�ɂ���ăA�j���[�V�����̃X�s�[�h���ω�����0�ɋ߂�������
		o_enemy.image++;
		o_enemy.izikeimage++;
		o_enemy.e_izikeimage++;
		o_enemy.count = 0;  // �J�E���g���Z�b�g
	}
	if (o_enemy.R_Hitflg == FALSE) { // �����C�W�P��ԂłȂ����
		if (o_enemy.image >= 8) { // �ʏ�̉摜�؂�ւ�
			o_enemy.image = 6;    // �摜���Z�b�g
		}
	}
	else if (o_enemy.R_Hitflg == TRUE) { // �����C�W�P��ԂȂ�
		if (o_enemy.izikeimage >= 18) { // �C�W�P�摜�؂�ւ�
			o_enemy.izikeimage = 16; // �摜���Z�b�g
		}
	}
	if (o_enemy.ER_Hitflg == TRUE) { // �����C�W�P��Ԃ��I��肻���Ȃ�
		if (o_enemy.e_izikeimage >= 20) { // �C�W�P�_�ŉ摜�؂�ւ�
			o_enemy.e_izikeimage = 16; // �摜���Z�b�g
		}
	}

	// ���[�v�g���l��
	if (o_enemy.x >= 878) {
		o_enemy.x = 352;

		//���g
		//��
		o_enemy.avatar_right[0] = 352 + O_ENEMY_POS_HITBOX;
		o_enemy.avatar_left[0] = 352 - O_ENEMY_POS_HITBOX;
		//��
		o_enemy.avatar_left[2] = 352 - O_ENEMY_POS_HITBOX;
		o_enemy.avatar_right[2] = 352 + O_ENEMY_POS_HITBOX;
		//�E
		o_enemy.avatar_left[1] = 352 + 24 - O_ENEMY_POS_HITBOX;
		o_enemy.avatar_right[1] = 352 + 24 + O_ENEMY_POS_HITBOX;
		//��
		o_enemy.avatar_right[3] = 352 - 24 - O_ENEMY_POS_HITBOX;
		o_enemy.avatar_left[3] = 352 - 24 + O_ENEMY_POS_HITBOX;
	}
	else if (o_enemy.x <= 352) {
		o_enemy.x = 878;

		//���g
		//��
		o_enemy.avatar_right[0] = 878 + O_ENEMY_POS_HITBOX;
		o_enemy.avatar_left[0] = 878 - O_ENEMY_POS_HITBOX;
		//��
		o_enemy.avatar_left[2] = 878 - O_ENEMY_POS_HITBOX;
		o_enemy.avatar_right[2] = 878 + O_ENEMY_POS_HITBOX;
		//�E
		o_enemy.avatar_left[1] = 878 + 24 - O_ENEMY_POS_HITBOX;
		o_enemy.avatar_right[1] = 878 + 24 + O_ENEMY_POS_HITBOX;
		//��
		o_enemy.avatar_right[3] = 878 - 24 - O_ENEMY_POS_HITBOX;
		o_enemy.avatar_left[3] = 878 - 24 + O_ENEMY_POS_HITBOX;
	}

	// �C�W�P��ԃt���O
	if (o_enemy.R_Hitflg == TRUE) {
		++o_enemy.ER_count;
	}
	// �v���C���[���S���̃G�l�~�[�A�j���[�V����
	if (mPlayer.Hitflg == TRUE) {
		o_enemy.HitCount++;
		int a = 5; int b = 10;
		if (o_enemy.HitCount == a) {
			o_enemy.image = 6;
			a += 5;
		}
		else if (o_enemy.HitCount == b) {
			o_enemy.image = 7;
			b += 5;
		}
		if (o_enemy.HitCount == 80) {
			flg = TRUE;
		}
	}
}

void O_ENEMY::Draw() {
	//����������������
	if (mPlayer.Hitflg == TRUE && flg == FALSE) {
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0.75, 0, o_enemy.images[o_enemy.image], TRUE, FALSE);
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0.75, 0, o_enemy.eyesimages[o_enemy.eyeimage], TRUE, FALSE);
	}
	//PC�ɓ��������Ƃ��ɏ�����
	if (flg == TRUE) {
		/*DrawRotaGraph(r_enemy.x, r_enemy.y, 0, 0, images[r_enemy.image], TRUE, FALSE);
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE); */
	}
	//�X�^�[�g�̎��̂ݕ\��
	if (mStage.StateFlg == FALSE || mStage.GameOverFlg == TRUE) {
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0, 0, o_enemy.images[o_enemy.image], TRUE, FALSE);
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0, 0, o_enemy.eyesimages[o_enemy.eyeimage], TRUE, FALSE);
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0, 0, o_enemy.images[o_enemy.izikeimage], TRUE, FALSE);
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0, 0, o_enemy.images[o_enemy.e_izikeimage], TRUE, FALSE);
	}
	//�X�^�[�g���̌Œ�\��
	else if (mStage.StateFlg == TRUE) {
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0.75, 0, o_enemy.images[6], TRUE, FALSE);
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0.75, 0, o_enemy.eyesimages[0], TRUE, FALSE);
	}
	//�p���[�G�T������Ă��Ȃ����AMoveflg�œ����ĉ\���APac�ɓ������Ă��Ȃ���
	if (o_enemy.R_Hitflg == FALSE && mStage.MoveFlg == TRUE && mPlayer.Hitflg == FALSE) {
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0.75, 0, o_enemy.images[o_enemy.image], TRUE, FALSE); // �G�L�����\��
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0.75, 0, o_enemy.eyesimages[o_enemy.eyeimage], TRUE, FALSE); // �G�L�����̖ڕ\��
		//DrawBox(o_enemy.left, o_enemy.top, o_enemy.right, o_enemy.bottom, 0x00ffff, FALSE); // �����蔻��`��
	}
	else if (o_enemy.R_Hitflg == TRUE) { // �p���[�G�T������Ă�����
		if (o_enemy.PR_Hitflg == FALSE) { // �v���C���[�Ɠ������Ă��Ȃ����
			if (o_enemy.ER_count <= 480) {
				DrawRotaGraph(o_enemy.x, o_enemy.y, 0.75, 0, o_enemy.images[o_enemy.izikeimage], TRUE, FALSE); // �C�W�P��ԕ\��
				//DrawBox(o_enemy.left, o_enemy.top, o_enemy.right, o_enemy.bottom, 0x00ffff, FALSE); // �����蔻��`��
			}
			else if (o_enemy.ER_count > 480 && o_enemy.ER_count <= 600) {
				o_enemy.ER_Hitflg = TRUE;
				DrawRotaGraph(o_enemy.x, o_enemy.y, 0.75, 0, o_enemy.images[o_enemy.e_izikeimage], TRUE, FALSE); // �C�W�P��ԕ\��
				//DrawBox(o_enemy.left, o_enemy.top, o_enemy.right, o_enemy.bottom, 0x00ffff, FALSE); // �����蔻��`��
			}
			else {
				o_enemy.R_Hitflg = FALSE;
				o_enemy.ER_Hitflg = FALSE;
				o_enemy.ER_count = 0;
				mPlayer.timercount = 0;
			}
		}
		else if (o_enemy.PR_Hitflg == TRUE) { // �v���C���[�Ɠ������Ă�����
			if (o_enemy.eyeflg == TRUE) { // �ڏ�ԂɂȂ�����
				DrawRotaGraph(o_enemy.x, o_enemy.y, 0.75, 0, o_enemy.eyesimages[o_enemy.eyeimage], TRUE, FALSE); // �G�L�����̖ڕ\��
				//DrawBox(o_enemy.left, o_enemy.top, o_enemy.right, o_enemy.bottom, 0x00ffff, FALSE); // �����蔻��`��
			}
			else if (o_enemy.eyeflg == FALSE) { // �ڏ�Ԃ̃G�l�~�[�������ʒu�ɖ߂�����
				o_enemy.R_Hitflg = FALSE;
				o_enemy.PR_Hitflg = FALSE;
				o_enemy.ER_Hitflg = FALSE;
				o_enemy.ER_count = 0;
				mPlayer.timercount = 0;
			}
		}
	}

	if (o_enemy.Initiaflg == TRUE) {
		// �����ʒu�ɖ߂�
		o_enemy.x = O_ENEMY_POS_X;
		o_enemy.y = O_ENEMY_POS_Y;
		o_enemy.top = O_ENEMY_POS_Y - O_ENEMY_POS_HITBOX;
		o_enemy.left = O_ENEMY_POS_X - O_ENEMY_POS_HITBOX;
		o_enemy.right = O_ENEMY_POS_X + O_ENEMY_POS_HITBOX;
		o_enemy.bottom = O_ENEMY_POS_Y + O_ENEMY_POS_HITBOX;
		o_enemy.Initiaflg = FALSE;

		//���g�̓����蔻��
		for (int i = 0; i < 4; i++) {
			o_enemy.avatar_left[i] = ENEMY_AVATAR_POS_X[i] - O_ENEMY_POS_HITBOX;
			o_enemy.avatar_top[i] = ENEMY_AVATAR_POS_Y[i] - O_ENEMY_POS_HITBOX;
			o_enemy.avatar_right[i] = ENEMY_AVATAR_POS_X[i] + O_ENEMY_POS_HITBOX;
			o_enemy.avatar_bottom[i] = ENEMY_AVATAR_POS_Y[i] + O_ENEMY_POS_HITBOX;
		}

		o_enemy.flg = FALSE;
		o_enemy.HitCount = 0;
	}

	////���g�̕\��
	//for (int i = 0; i < 4; i++) {
	//	DrawBox(o_enemy.avatar_left[i], o_enemy.avatar_top[i], o_enemy.avatar_right[i], o_enemy.avatar_bottom[i], 0x00ffff, FALSE);
	//}

	////�i�߂鎞
	////��
	//if (o_enemy.Top == TRUE) {
	//	DrawBox(o_enemy.avatar_left[0], o_enemy.avatar_top[0], o_enemy.avatar_right[0], o_enemy.avatar_bottom[0], 0xff00ff, true);
	//}
	//else if (o_enemy.Top == FALSE) {
	//	DrawBox(o_enemy.avatar_left[0], o_enemy.avatar_top[0], o_enemy.avatar_right[0], o_enemy.avatar_bottom[0], 0xff0000, true);
	//}
	////�E
	//if (o_enemy.Right == TRUE) {
	//	DrawBox(o_enemy.avatar_left[1], o_enemy.avatar_top[1], o_enemy.avatar_right[1], o_enemy.avatar_bottom[1], 0xff00ff, true);
	//}
	//else if (o_enemy.Right == FALSE) {
	//	DrawBox(o_enemy.avatar_left[1], o_enemy.avatar_top[1], o_enemy.avatar_right[1], o_enemy.avatar_bottom[1], 0xff0000, true);
	//}
	////��
	//if (o_enemy.Bottom == TRUE) {
	//	DrawBox(o_enemy.avatar_left[2], o_enemy.avatar_top[2], o_enemy.avatar_right[2], o_enemy.avatar_bottom[2], 0xff00ff, true);
	//}
	//else if (o_enemy.Bottom == FALSE) {
	//	DrawBox(o_enemy.avatar_left[2], o_enemy.avatar_top[2], o_enemy.avatar_right[2], o_enemy.avatar_bottom[2], 0xff0000, true);
	//}
	////��
	//if (o_enemy.Left == TRUE) {
	//	DrawBox(o_enemy.avatar_left[3], o_enemy.avatar_top[3], o_enemy.avatar_right[3], o_enemy.avatar_bottom[3], 0xff00ff, true);
	//}
	//else if (o_enemy.Left == FALSE) {
	//	DrawBox(o_enemy.avatar_left[3], o_enemy.avatar_top[3], o_enemy.avatar_right[3], o_enemy.avatar_bottom[3], 0xff0000, true);
	//}
}