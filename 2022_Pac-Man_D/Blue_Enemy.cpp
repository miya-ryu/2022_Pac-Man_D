#include "DxLib.h"
#include "Blue_Enemy.h"
#include "Player.h"
#include <math.h>
#include "Stage.h"

B_ENEMY b_enemy;

int B_EnemeyCheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
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

void B_ENEMY::Initialize() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);  // �G�L����
	LoadDivGraph("images/eyes.png", 4, 4, 1, 32, 32, eyesimages);  // �G�L�����̖�

	b_enemy.speed = 1;             // �ړ����x
	b_enemy.angle = 4;             // �����̌���
	b_enemy.count = 0;             // �A�j���[�V�����J�E���g
	b_enemy.ER_count = 0;          // �C�W�P��ԃJ�E���g
	b_enemy.image = 4;             // �摜�ϐ�
	b_enemy.eyeimage = 3;          // �ڂ̉摜�ϐ�
	b_enemy.izikeimage = 16;       // �C�W�P��Ԃ̉摜�ϐ�
	b_enemy.e_izikeimage = 16;     // �C�W�P��ԓ_�ł̉摜�ϐ�
	//b_enemy.E_StageHitflg = FALSE; // �ǂƂ̓����蔻��t���O
	b_enemy.R_Hitflg = FALSE;      // �C�W�P��Ԕ���t���O
	b_enemy.ER_Hitflg = FALSE;     // �C�W�P��ԓ_�Ńt���O
	b_enemy.PR_Hitflg = FALSE;     // �C�W�P��ԂŃv���C���[�ɓ����������̃t���O
	b_enemy.eyeflg = FALSE;        // �G�l�~�[�ڏ��
	b_enemy.Initiaflg = FALSE;     // �G�l�~�[������

	// �����ʒu��ۑ�
	b_enemy.x = B_ENEMY_POS_X;
	b_enemy.y = B_ENEMY_POS_Y;

	//�����蔻��
	b_enemy.recordX = b_enemy.x;
	b_enemy.recordY = b_enemy.y;

	b_enemy.top = B_ENEMY_POS_Y - B_ENEMY_POS_HITBOX;
	b_enemy.left = B_ENEMY_POS_X - B_ENEMY_POS_HITBOX;
	b_enemy.right = B_ENEMY_POS_X + B_ENEMY_POS_HITBOX;
	b_enemy.bottom = B_ENEMY_POS_Y + B_ENEMY_POS_HITBOX;

	b_enemy.recordTop = b_enemy.top;
	b_enemy.recordRight = b_enemy.right;
	b_enemy.recordBottom = b_enemy.bottom;
	b_enemy.recordLeft = b_enemy.left;

	// ���g�̏���������
	//���g�̃t���O����
	b_enemy.Top = FALSE;
	b_enemy.Bottom = FALSE;
	b_enemy.Left = TRUE;
	b_enemy.Right = TRUE;
	//���g�̍��W
	//��
	b_enemy.ENEMY_AVATAR_POS_X[0] = B_ENEMY_POS_X;
	b_enemy.ENEMY_AVATAR_POS_Y[0] = B_ENEMY_POS_Y - 24;
	//�E
	b_enemy.ENEMY_AVATAR_POS_X[1] = B_ENEMY_POS_X + 24;
	b_enemy.ENEMY_AVATAR_POS_Y[1] = B_ENEMY_POS_Y;
	//��
	b_enemy.ENEMY_AVATAR_POS_X[2] = B_ENEMY_POS_X;
	b_enemy.ENEMY_AVATAR_POS_Y[2] = B_ENEMY_POS_Y + 24;
	//��
	b_enemy.ENEMY_AVATAR_POS_X[3] = B_ENEMY_POS_X - 24;
	b_enemy.ENEMY_AVATAR_POS_Y[3] = B_ENEMY_POS_Y;

	// �O��̃L�[���͏���
	b_enemy.CheckNumber = 12;

	//���g�̓����蔻��
	for (int i = 0; i < 4; i++) {
		b_enemy.avatar_left[i] = ENEMY_AVATAR_POS_X[i] - B_ENEMY_POS_HITBOX;
		b_enemy.avatar_top[i] = ENEMY_AVATAR_POS_Y[i] - B_ENEMY_POS_HITBOX;
		b_enemy.avatar_right[i] = ENEMY_AVATAR_POS_X[i] + B_ENEMY_POS_HITBOX;
		b_enemy.avatar_bottom[i] = ENEMY_AVATAR_POS_Y[i] + B_ENEMY_POS_HITBOX;
	}
}

void B_ENEMY::Update() {
	//�O��̍��W�擾
	b_enemy.recordX = b_enemy.x;
	b_enemy.recordY = b_enemy.y;

	b_enemy.recordTop = b_enemy.top;
	b_enemy.recordRight = b_enemy.right;
	b_enemy.recordBottom = b_enemy.bottom;
	b_enemy.recordLeft = b_enemy.left;

	//�O��̍��W�ړ�
	b_enemy.absX = mPlayer.x - b_enemy.x;
	b_enemy.absY = mPlayer.y - b_enemy.y;

	//��Βl�����߂�
	if (b_enemy.absX <= 0) {
		b_enemy.absX = b_enemy.absX * -1;
	}
	if (b_enemy.absY <= 0) {
		b_enemy.absY = b_enemy.absY * -1;
	}

	//���g�̍��W
	for (int i = 0; i < 4; i++) {
		b_enemy.record_avatar_bottom[i] = b_enemy.avatar_bottom[i];
		b_enemy.record_avatar_left[i] = b_enemy.avatar_left[i];
		b_enemy.record_avatar_right[i] = b_enemy.avatar_right[i];
		b_enemy.record_avatar_top[i] = b_enemy.avatar_top[i];
	}

	// �v���C���[��ǂ������鏈��
	if (b_enemy.R_Hitflg == FALSE) { // �p���[�G�T������Ă��Ȃ���
		b_enemy.speed = 1;
		// �E����
		if (b_enemy.angle == 2) {
			if (b_enemy.Right == TRUE) {
				if (mPlayer.x < b_enemy.x) { // ������
					b_enemy.angle = 4;
				}
				else if (mPlayer.y < b_enemy.y) { // �����
					b_enemy.angle = 1;
				}
				else if (mPlayer.y > b_enemy.y) { // ������
					b_enemy.angle = 3;
				}
			}
			else if (b_enemy.Right == FALSE) {
				if (mPlayer.x < b_enemy.x) { // ������
					if (b_enemy.Left == FALSE) {
						b_enemy.angle = 4;
					}
				}
				else if (mPlayer.y < b_enemy.y) { // �����
					if (b_enemy.Top == FALSE) {
						b_enemy.angle = 1;
					}
				}
				else if (mPlayer.y > b_enemy.y) { // ������
					if (b_enemy.Bottom == FALSE) {
						b_enemy.angle = 3;
					}
				}
				// �E����
				b_enemy.x += b_enemy.speed;
				// �����蔻��
				b_enemy.left += b_enemy.speed;
				b_enemy.right += b_enemy.speed;
				//���g
				for (int i = 0; i < 4; i++) {
					b_enemy.avatar_right[i] += b_enemy.speed;
					b_enemy.avatar_left[i] += b_enemy.speed;
				}
				b_enemy.eyeimage = 1;
			}
		}
		// ������
		else if (b_enemy.angle == 4) {
			if (b_enemy.Left == TRUE) {
				if (mPlayer.x > b_enemy.x) { // �E����
					b_enemy.angle = 2;
				}
				else if (mPlayer.y < b_enemy.y) { // �����
					b_enemy.angle = 1;
				}
				else if (mPlayer.y > b_enemy.y) { // ������
					b_enemy.angle = 3;
				}
			}
			else if (b_enemy.Left == FALSE) {
				if (mPlayer.x > b_enemy.x) { // �E����
					if (b_enemy.Right == FALSE) {
						b_enemy.angle = 2;
					}
				}
				else if (mPlayer.y < b_enemy.y) { // �����
					if (b_enemy.Top == FALSE) {
						b_enemy.angle = 1;
					}
				}
				else if (mPlayer.y > b_enemy.y) { // ������
					if (b_enemy.Bottom == FALSE) {
						b_enemy.angle = 3;
					}
				}
				// ������
				b_enemy.x -= b_enemy.speed;
				//�����蔻��
				b_enemy.left -= b_enemy.speed;
				b_enemy.right -= b_enemy.speed;
				//���g
				for (int i = 0; i < 4; i++) {
					b_enemy.avatar_right[i] -= b_enemy.speed;
					b_enemy.avatar_left[i] -= b_enemy.speed;
				}
				b_enemy.eyeimage = 3;
			}
		}
		//������
		else if (b_enemy.angle == 3) {
			if (b_enemy.Bottom == TRUE) {
				if (mPlayer.x > b_enemy.x) { // �E����
					b_enemy.angle = 2;
				}
				else if (mPlayer.x < b_enemy.x) { // ������
					b_enemy.angle = 4;
				}
				else if (mPlayer.y < b_enemy.y) { // �����
					b_enemy.angle = 1;
				}
			}
			else if (b_enemy.Bottom == FALSE) {
				if (mPlayer.x > b_enemy.x) { // �E����
					if (b_enemy.Right == FALSE) {
						b_enemy.angle = 2;
					}
				}
				else if (mPlayer.x < b_enemy.x) { // ������
					if (b_enemy.Left == FALSE) {
						b_enemy.angle = 4;
					}
				}
				else if (mPlayer.y < b_enemy.y) { // �����
					if (b_enemy.Top == FALSE) {
						b_enemy.angle = 1;
					}
				}
				//������
				b_enemy.y += b_enemy.speed;
				//�����蔻��
				b_enemy.top += b_enemy.speed;
				b_enemy.bottom += b_enemy.speed;
				//���g
				for (int i = 0; i < 4; i++) {
					b_enemy.avatar_top[i] += b_enemy.speed;
					b_enemy.avatar_bottom[i] += b_enemy.speed;
				}
				b_enemy.eyeimage = 2;
			}
		}
		//�����
		else if (b_enemy.angle == 1) {
			if (b_enemy.Top == TRUE) {
				if (mPlayer.x > b_enemy.x) { // �E����
					b_enemy.angle = 2;
				}
				else if (mPlayer.x < b_enemy.x) { // ������
					b_enemy.angle = 4;
				}
				else if (mPlayer.y > b_enemy.y) { // ������
					b_enemy.angle = 3;
				}
			}
			else if (b_enemy.Top == FALSE) {
				if (mPlayer.x > b_enemy.x) { // �E����
					if (b_enemy.Right == FALSE) {
						b_enemy.angle = 2;
					}
				}
				else if (mPlayer.x < b_enemy.x) { // ������
					if (b_enemy.Left == FALSE) {
						b_enemy.angle = 4;
					}
				}
				else if (mPlayer.y > b_enemy.y) { // ������
					if (b_enemy.Bottom == FALSE) {
						b_enemy.angle = 3;
					}
				}
				//�����
				b_enemy.y -= b_enemy.speed;
				//�����蔻��
				b_enemy.top -= b_enemy.speed;
				b_enemy.bottom -= b_enemy.speed;
				//���g
				for (int i = 0; i < 4; i++) {
					b_enemy.avatar_top[i] -= b_enemy.speed;
					b_enemy.avatar_bottom[i] -= b_enemy.speed;
				}
				b_enemy.eyeimage = 0;
			}
		}
	}
	else if (b_enemy.R_Hitflg == TRUE) { // �p���[�G�T���������
		if (b_enemy.PR_Hitflg == FALSE) { // �v���C���[�Ɠ������Ă��Ȃ�������
			b_enemy.speed = 1.6;
			// �E����
			if (b_enemy.angle == 2) {
				if (b_enemy.Right == TRUE) {
					if (mPlayer.x < b_enemy.x) { // ������
						b_enemy.angle = 4;
					}
					else if (mPlayer.y < b_enemy.y) { // �����
						b_enemy.angle = 1;
					}
					else if (mPlayer.y > b_enemy.y) { // ������
						b_enemy.angle = 3;
					}
				}
				else if (b_enemy.Right == FALSE) {
					if (mPlayer.x < b_enemy.x) { // ������
						if (b_enemy.Left == FALSE) {
							b_enemy.angle = 4;
						}
					}
					else if (mPlayer.y < b_enemy.y) { // �����
						if (b_enemy.Top == FALSE) {
							b_enemy.angle = 1;
						}
					}
					else if (mPlayer.y > b_enemy.y) { // ������
						if (b_enemy.Bottom == FALSE) {
							b_enemy.angle = 3;
						}
					}
					// �E����
					b_enemy.x -= b_enemy.speed;
					// �����蔻��
					b_enemy.left -= b_enemy.speed;
					b_enemy.right -= b_enemy.speed;
					//���g
					for (int i = 0; i < 4; i++) {
						b_enemy.avatar_right[i] -= b_enemy.speed;
						b_enemy.avatar_left[i] -= b_enemy.speed;
					}
				}
			}
			// ������
			else if (b_enemy.angle == 4) {
				if (b_enemy.Left == TRUE) {
					if (mPlayer.x > b_enemy.x) { // �E����
						b_enemy.angle = 2;
					}
					else if (mPlayer.y < b_enemy.y) { // �����
						b_enemy.angle = 1;
					}
					else if (mPlayer.y > b_enemy.y) { // ������
						b_enemy.angle = 3;
					}
				}
				else if (b_enemy.Left == FALSE) {
					if (mPlayer.x > b_enemy.x) { // �E����
						if (b_enemy.Right == FALSE) {
							b_enemy.angle = 2;
						}
					}
					else if (mPlayer.y < b_enemy.y) { // �����
						if (b_enemy.Top == FALSE) {
							b_enemy.angle = 1;
						}
					}
					else if (mPlayer.y > b_enemy.y) { // ������
						if (b_enemy.Bottom == FALSE) {
							b_enemy.angle = 3;
						}
					}
					// ������
					b_enemy.x += b_enemy.speed;
					//�����蔻��
					b_enemy.left += b_enemy.speed;
					b_enemy.right += b_enemy.speed;
					//���g
					for (int i = 0; i < 4; i++) {
						b_enemy.avatar_right[i] += b_enemy.speed;
						b_enemy.avatar_left[i] += b_enemy.speed;
					}
				}
			}
			//������
			else if (b_enemy.angle == 3) {
				if (b_enemy.Bottom == TRUE) {
					if (mPlayer.x > b_enemy.x) { // �E����
						b_enemy.angle = 2;
					}
					else if (mPlayer.x < b_enemy.x) { // ������
						b_enemy.angle = 4;
					}
					else if (mPlayer.y < b_enemy.y) { // �����
						b_enemy.angle = 1;
					}
				}
				else if (b_enemy.Bottom == FALSE) {
					if (mPlayer.x > b_enemy.x) { // �E����
						if (b_enemy.Right == FALSE) {
							b_enemy.angle = 2;
						}
					}
					else if (mPlayer.x < b_enemy.x) { // ������
						if (b_enemy.Left == FALSE) {
							b_enemy.angle = 4;
						}
					}
					else if (mPlayer.y < b_enemy.y) { // �����
						if (b_enemy.Top == FALSE) {
							b_enemy.angle = 1;
						}
					}
					//������
					b_enemy.y -= b_enemy.speed;
					//�����蔻��
					b_enemy.top -= b_enemy.speed;
					b_enemy.bottom -= b_enemy.speed;
					//���g
					for (int i = 0; i < 4; i++) {
						b_enemy.avatar_top[i] -= b_enemy.speed;
						b_enemy.avatar_bottom[i] -= b_enemy.speed;
					}
				}
			}
			//�����
			else if (b_enemy.angle == 1) {
				if (b_enemy.Top == TRUE) {
					if (mPlayer.x > b_enemy.x) { // �E����
						b_enemy.angle = 2;
					}
					else if (mPlayer.x < b_enemy.x) { // ������
						b_enemy.angle = 4;
					}
					else if (mPlayer.y > b_enemy.y) { // ������
						b_enemy.angle = 3;
					}
				}
				else if (b_enemy.Top == FALSE) {
					if (mPlayer.x > b_enemy.x) { // �E����
						if (b_enemy.Right == FALSE) {
							b_enemy.angle = 2;
						}
					}
					else if (mPlayer.x < b_enemy.x) { // ������
						if (b_enemy.Left == FALSE) {
							b_enemy.angle = 4;
						}
					}
					else if (mPlayer.y > b_enemy.y) { // ������
						if (b_enemy.Bottom == FALSE) {
							b_enemy.angle = 3;
						}
					}
					//�����
					b_enemy.y += b_enemy.speed;
					//�����蔻��
					b_enemy.top += b_enemy.speed;
					b_enemy.bottom += b_enemy.speed;
					//���g
					for (int i = 0; i < 4; i++) {
						b_enemy.avatar_top[i] += b_enemy.speed;
						b_enemy.avatar_bottom[i] += b_enemy.speed;
					}
				}
			}
		}
		else if (b_enemy.PR_Hitflg == TRUE) { // �v���C���[�Ɠ������Ă����珉���ʒu�ɖ߂�
			if (b_enemy.eyeflg == TRUE) {
				b_enemy.speed = 3;
				// �E����
				if (b_enemy.angle == 2) {
					if (b_enemy.Right == TRUE) {
						if (ENEMY_POS_X < b_enemy.x) { // ������
							b_enemy.angle = 4;
						}
						else if (ENEMY_POS_Y < b_enemy.y) { // �����
							b_enemy.angle = 1;
						}
						else if (ENEMY_POS_Y > b_enemy.y) { // ������
							b_enemy.angle = 3;
						}
					}
					else if (b_enemy.Right == FALSE) {
						if (ENEMY_POS_X < b_enemy.x) { // ������
							if (b_enemy.Left == FALSE) {
								b_enemy.angle = 4;
							}
						}
						else if (ENEMY_POS_Y < b_enemy.y) { // �����
							if (b_enemy.Top == FALSE) {
								b_enemy.angle = 1;
							}
						}
						else if (ENEMY_POS_Y > b_enemy.y) { // ������
							if (b_enemy.Bottom == FALSE) {
								b_enemy.angle = 3;
							}
						}
						// �E����
						b_enemy.x += b_enemy.speed;
						// �����蔻��
						b_enemy.left += b_enemy.speed;
						b_enemy.right += b_enemy.speed;
						//���g
						for (int i = 0; i < 4; i++) {
							b_enemy.avatar_right[i] += b_enemy.speed;
							b_enemy.avatar_left[i] += b_enemy.speed;
						}
						b_enemy.eyeimage = 1;
					}
				}
				// ������
				else if (b_enemy.angle == 4) {
					if (b_enemy.Left == TRUE) {
						if (ENEMY_POS_X > b_enemy.x) { // �E����
							b_enemy.angle = 2;
						}
						else if (ENEMY_POS_Y < b_enemy.y) { // �����
							b_enemy.angle = 1;
						}
						else if (ENEMY_POS_Y > b_enemy.y) { // ������
							b_enemy.angle = 3;
						}
					}
					else if (b_enemy.Left == FALSE) {
						if (ENEMY_POS_X > b_enemy.x) { // �E����
							if (b_enemy.Right == FALSE) {
								b_enemy.angle = 2;
							}
						}
						else if (ENEMY_POS_Y < b_enemy.y) { // �����
							if (b_enemy.Top == FALSE) {
								b_enemy.angle = 1;
							}
						}
						else if (ENEMY_POS_Y > b_enemy.y) { // ������
							if (b_enemy.Bottom == FALSE) {
								b_enemy.angle = 3;
							}
						}
						// ������
						b_enemy.x -= b_enemy.speed;
						//�����蔻��
						b_enemy.left -= b_enemy.speed;
						b_enemy.right -= b_enemy.speed;
						//���g
						for (int i = 0; i < 4; i++) {
							b_enemy.avatar_right[i] -= b_enemy.speed;
							b_enemy.avatar_left[i] -= b_enemy.speed;
						}
						b_enemy.eyeimage = 3;
					}
				}
				//������
				else if (b_enemy.angle == 3) {
					if (b_enemy.Bottom == TRUE) {
						if (ENEMY_POS_X > b_enemy.x) { // �E����
							b_enemy.angle = 2;
						}
						else if (ENEMY_POS_X < b_enemy.x) { // ������
							b_enemy.angle = 4;
						}
						else if (ENEMY_POS_Y < b_enemy.y) { // �����
							b_enemy.angle = 1;
						}
					}
					else if (b_enemy.Bottom == FALSE) {
						if (ENEMY_POS_X > b_enemy.x) { // �E����
							if (b_enemy.Right == FALSE) {
								b_enemy.angle = 2;
							}
						}
						else if (ENEMY_POS_X < b_enemy.x) { // ������
							if (b_enemy.Left == FALSE) {
								b_enemy.angle = 4;
							}
						}
						else if (ENEMY_POS_Y < b_enemy.y) { // �����
							if (b_enemy.Top == FALSE) {
								b_enemy.angle = 1;
							}
						}
						//������
						b_enemy.y += b_enemy.speed;
						//�����蔻��
						b_enemy.top += b_enemy.speed;
						b_enemy.bottom += b_enemy.speed;
						//���g
						for (int i = 0; i < 4; i++) {
							b_enemy.avatar_top[i] += b_enemy.speed;
							b_enemy.avatar_bottom[i] += b_enemy.speed;
						}
						b_enemy.eyeimage = 2;
					}
				}
				//�����
				else if (b_enemy.angle == 1) {
					if (b_enemy.Top == TRUE) {
						if (ENEMY_POS_X > b_enemy.x) { // �E����
							b_enemy.angle = 2;
						}
						else if (ENEMY_POS_X < b_enemy.x) { // ������
							b_enemy.angle = 4;
						}
						else if (ENEMY_POS_Y > b_enemy.y) { // ������
							b_enemy.angle = 3;
						}
					}
					else if (b_enemy.Top == FALSE) {
						if (ENEMY_POS_X > b_enemy.x) { // �E����
							if (b_enemy.Right == FALSE) {
								b_enemy.angle = 2;
							}
						}
						else if (ENEMY_POS_X < b_enemy.x) { // ������
							if (b_enemy.Left == FALSE) {
								b_enemy.angle = 4;
							}
						}
						else if (ENEMY_POS_Y > b_enemy.y) { // ������
							if (b_enemy.Bottom == FALSE) {
								b_enemy.angle = 3;
							}
						}
						//�����
						b_enemy.y -= b_enemy.speed;
						//�����蔻��
						b_enemy.top -= b_enemy.speed;
						b_enemy.bottom -= b_enemy.speed;
						//���g
						for (int i = 0; i < 4; i++) {
							b_enemy.avatar_top[i] -= b_enemy.speed;
							b_enemy.avatar_bottom[i] -= b_enemy.speed;
						}
						b_enemy.eyeimage = 0;
					}
				}
				// �����ʒu�ɖ߂�����
				if (ENEMY_POS_X == b_enemy.x) {
					b_enemy.eyeflg = FALSE;
				}
			}
		}
	}

	// �G�l�~�[�ƃv���C���[�̓����蔻��
	if (B_EnemeyCheckHit(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, b_enemy.left, b_enemy.top, b_enemy.right, b_enemy.bottom)) {
		if (b_enemy.R_Hitflg == TRUE || b_enemy.ER_Hitflg == TRUE) { // �C�W�P��Ԃœ���������
			b_enemy.PR_Hitflg = TRUE;
			b_enemy.eyeflg = TRUE;
		}
	}

	// �A�j���[�V����
	++b_enemy.count;  // �J�E���g�J�n
	if (b_enemy.count >= 8) {  // �l�ɂ���ăA�j���[�V�����̃X�s�[�h���ω�����0�ɋ߂�������
		b_enemy.image++;
		b_enemy.izikeimage++;
		b_enemy.e_izikeimage++;
		b_enemy.count = 0;  // �J�E���g���Z�b�g
	}
	if (b_enemy.R_Hitflg == FALSE) { // �����C�W�P��ԂłȂ����
		if (b_enemy.image >= 6) { // �ʏ�̉摜�؂�ւ�
			b_enemy.image = 4;    // �摜���Z�b�g
		}
	}
	else if (b_enemy.R_Hitflg == TRUE) { // �����C�W�P��ԂȂ�
		if (b_enemy.izikeimage >= 18) { // �C�W�P�摜�؂�ւ�
			b_enemy.izikeimage = 16; // �摜���Z�b�g
		}
	}
	if (b_enemy.ER_Hitflg == TRUE) { // �����C�W�P��Ԃ��I��肻���Ȃ�
		if (b_enemy.e_izikeimage >= 20) { // �C�W�P�_�ŉ摜�؂�ւ�
			b_enemy.e_izikeimage = 16; // �摜���Z�b�g
		}
	}

	// ���[�v�g���l��
	if (b_enemy.x >= 878) {
		b_enemy.x = 352;

		//���g
		//��
		b_enemy.avatar_right[0] = 352 + B_ENEMY_POS_HITBOX;
		b_enemy.avatar_left[0] = 352 - B_ENEMY_POS_HITBOX;
		//��
		b_enemy.avatar_left[2] = 352 - B_ENEMY_POS_HITBOX;
		b_enemy.avatar_right[2] = 352 + B_ENEMY_POS_HITBOX;
		//�E
		b_enemy.avatar_left[1] = 352 + 24 - B_ENEMY_POS_HITBOX;
		b_enemy.avatar_right[1] = 352 + 24 + B_ENEMY_POS_HITBOX;
		//��
		b_enemy.avatar_right[3] = 352 - 24 - B_ENEMY_POS_HITBOX;
		b_enemy.avatar_left[3] = 352 - 24 + B_ENEMY_POS_HITBOX;
	}
	else if (b_enemy.x <= 352) {
		b_enemy.x = 878;

		//���g
		//��
		b_enemy.avatar_right[0] = 878 + B_ENEMY_POS_HITBOX;
		b_enemy.avatar_left[0] = 878 - B_ENEMY_POS_HITBOX;
		//��
		b_enemy.avatar_left[2] = 878 - B_ENEMY_POS_HITBOX;
		b_enemy.avatar_right[2] = 878 + B_ENEMY_POS_HITBOX;
		//�E
		b_enemy.avatar_left[1] = 878 + 24 - B_ENEMY_POS_HITBOX;
		b_enemy.avatar_right[1] = 878 + 24 + B_ENEMY_POS_HITBOX;
		//��
		b_enemy.avatar_right[3] = 878 - 24 - B_ENEMY_POS_HITBOX;
		b_enemy.avatar_left[3] = 878 - 24 + B_ENEMY_POS_HITBOX;
	}

	// �C�W�P��ԃt���O
	if (b_enemy.R_Hitflg == TRUE) {
		++b_enemy.ER_count;
	}
}

void B_ENEMY::Draw() {
	if (mStage.StateFlg == FALSE || mStage.GameOverFlg == TRUE) {		//�X�^�[�g�̎��̂ݕ\��
		DrawRotaGraph(b_enemy.x, b_enemy.y, 0, 0, b_enemy.images[b_enemy.image], TRUE, FALSE);
		DrawRotaGraph(b_enemy.x, b_enemy.y, 0, 0, b_enemy.eyesimages[b_enemy.eyeimage], TRUE, FALSE);
	}
	else if (mStage.StateFlg == TRUE) {
		DrawRotaGraph(b_enemy.x, b_enemy.y, 0.75, 0, b_enemy.images[4], TRUE, FALSE);
		DrawRotaGraph(b_enemy.x, b_enemy.y, 0.75, 0, b_enemy.eyesimages[3], TRUE, FALSE);
	}

	if (b_enemy.R_Hitflg == FALSE && mStage.MoveFlg == TRUE) { // �p���[�G�T������Ă��Ȃ����
		DrawRotaGraph(b_enemy.x, b_enemy.y, 0.75, 0, b_enemy.images[b_enemy.image], TRUE, FALSE); // �G�L�����\��
		DrawRotaGraph(b_enemy.x, b_enemy.y, 0.75, 0, b_enemy.eyesimages[b_enemy.eyeimage], TRUE, FALSE); // �G�L�����̖ڕ\��
		DrawBox(b_enemy.left, b_enemy.top, b_enemy.right, b_enemy.bottom, 0x00ffff, FALSE); // �����蔻��`��
	}
	else if (b_enemy.R_Hitflg == TRUE) { // �p���[�G�T������Ă�����
		if (b_enemy.PR_Hitflg == FALSE) { // �v���C���[�Ɠ������Ă��Ȃ����
			if (b_enemy.ER_count <= 480) {
				DrawRotaGraph(b_enemy.x, b_enemy.y, 0.75, 0, b_enemy.images[b_enemy.izikeimage], TRUE, FALSE); // �C�W�P��ԕ\��
				DrawBox(b_enemy.left, b_enemy.top, b_enemy.right, b_enemy.bottom, 0x00ffff, FALSE); // �����蔻��`��
			}
			else if (b_enemy.ER_count > 480 && b_enemy.ER_count <= 600) {
				b_enemy.ER_Hitflg = TRUE;
				DrawRotaGraph(b_enemy.x, b_enemy.y, 0.75, 0, b_enemy.images[b_enemy.e_izikeimage], TRUE, FALSE); // �C�W�P��ԕ\��
				DrawBox(b_enemy.left, b_enemy.top, b_enemy.right, b_enemy.bottom, 0x00ffff, FALSE); // �����蔻��`��
			}
			else {
				b_enemy.R_Hitflg = FALSE;
				b_enemy.ER_Hitflg = FALSE;
				b_enemy.ER_count = 0;
				mPlayer.timercount = 0;
			}
		}
		else if (b_enemy.PR_Hitflg == TRUE) { // �v���C���[�Ɠ������Ă�����
			if (b_enemy.eyeflg == TRUE) { // �ڏ�ԂɂȂ�����
				DrawRotaGraph(b_enemy.x, b_enemy.y, 0.75, 0, b_enemy.eyesimages[b_enemy.eyeimage], TRUE, FALSE); // �G�L�����̖ڕ\��
				DrawBox(b_enemy.left, b_enemy.top, b_enemy.right, b_enemy.bottom, 0x00ffff, FALSE); // �����蔻��`��
			}
			else if (b_enemy.eyeflg == FALSE) { // �ڏ�Ԃ̃G�l�~�[�������ʒu�ɖ߂�����
				b_enemy.R_Hitflg = FALSE;
				b_enemy.PR_Hitflg = FALSE;
				b_enemy.ER_Hitflg = FALSE;
				b_enemy.ER_count = 0;
				mPlayer.timercount = 0;
			}
		}
	}

	if (b_enemy.Initiaflg == TRUE) {
		// �����ʒu�ɖ߂�
		b_enemy.x = B_ENEMY_POS_X;
		b_enemy.y = B_ENEMY_POS_Y;
		b_enemy.top = B_ENEMY_POS_Y - B_ENEMY_POS_HITBOX;
		b_enemy.left = B_ENEMY_POS_X - B_ENEMY_POS_HITBOX;
		b_enemy.right = B_ENEMY_POS_X + B_ENEMY_POS_HITBOX;
		b_enemy.bottom = B_ENEMY_POS_Y + B_ENEMY_POS_HITBOX;
		b_enemy.Initiaflg = FALSE;

		//���g�̓����蔻��
		for (int i = 0; i < 4; i++) {
			b_enemy.avatar_left[i] = ENEMY_AVATAR_POS_X[i] - B_ENEMY_POS_HITBOX;
			b_enemy.avatar_top[i] = ENEMY_AVATAR_POS_Y[i] - B_ENEMY_POS_HITBOX;
			b_enemy.avatar_right[i] = ENEMY_AVATAR_POS_X[i] + B_ENEMY_POS_HITBOX;
			b_enemy.avatar_bottom[i] = ENEMY_AVATAR_POS_Y[i] + B_ENEMY_POS_HITBOX;
		}

		if (mStage.life == 2) {
			mStage.life = 1;
		}
		else if (mStage.life == 1) {
			mStage.life = 0;
		}
		else if (mStage.life == 0) {
			mStage.GameOverFlg = true;
		}
	}

	//���g�̕\��
	for (int i = 0; i < 4; i++) {
		DrawBox(b_enemy.avatar_left[i], b_enemy.avatar_top[i], b_enemy.avatar_right[i], b_enemy.avatar_bottom[i], 0x00ffff, FALSE);
	}

	//�i�߂鎞
	//��
	if (b_enemy.Top == TRUE) {
		DrawBox(b_enemy.avatar_left[0], b_enemy.avatar_top[0], b_enemy.avatar_right[0], b_enemy.avatar_bottom[0], 0xff00ff, true);
	}
	else if (b_enemy.Top == FALSE) {
		DrawBox(b_enemy.avatar_left[0], b_enemy.avatar_top[0], b_enemy.avatar_right[0], b_enemy.avatar_bottom[0], 0xff0000, true);
	}
	//�E
	if (b_enemy.Right == TRUE) {
		DrawBox(b_enemy.avatar_left[1], b_enemy.avatar_top[1], b_enemy.avatar_right[1], b_enemy.avatar_bottom[1], 0xff00ff, true);
	}
	else if (b_enemy.Right == FALSE) {
		DrawBox(b_enemy.avatar_left[1], b_enemy.avatar_top[1], b_enemy.avatar_right[1], b_enemy.avatar_bottom[1], 0xff0000, true);
	}
	//��
	if (b_enemy.Bottom == TRUE) {
		DrawBox(b_enemy.avatar_left[2], b_enemy.avatar_top[2], b_enemy.avatar_right[2], b_enemy.avatar_bottom[2], 0xff00ff, true);
	}
	else if (b_enemy.Bottom == FALSE) {
		DrawBox(b_enemy.avatar_left[2], b_enemy.avatar_top[2], b_enemy.avatar_right[2], b_enemy.avatar_bottom[2], 0xff0000, true);
	}
	//��
	if (b_enemy.Left == TRUE) {
		DrawBox(b_enemy.avatar_left[3], b_enemy.avatar_top[3], b_enemy.avatar_right[3], b_enemy.avatar_bottom[3], 0xff00ff, true);
	}
	else if (b_enemy.Left == FALSE) {
		DrawBox(b_enemy.avatar_left[3], b_enemy.avatar_top[3], b_enemy.avatar_right[3], b_enemy.avatar_bottom[3], 0xff0000, true);
	}
}