#include "DxLib.h"
#include "Pink_Enemy.h"
#include "Player.h"
#include <math.h>
#include "Stage.h"

P_ENEMY p_enemy;

int P_EnemeyCheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
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

void P_ENEMY::Initialize() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);  // �G�L����
	LoadDivGraph("images/eyes.png", 4, 4, 1, 32, 32, eyesimages);  // �G�L�����̖�

	p_enemy.speed = 1;             // �ړ����x
	p_enemy.angle = 4;             // �����̌���
	p_enemy.count = 0;             // �A�j���[�V�����J�E���g
	p_enemy.ER_count = 0;          // �C�W�P��ԃJ�E���g
	p_enemy.image = 2;             // �摜�ϐ�
	p_enemy.eyeimage = 3;          // �ڂ̉摜�ϐ�
	p_enemy.izikeimage = 16;       // �C�W�P��Ԃ̉摜�ϐ�
	p_enemy.e_izikeimage = 16;     // �C�W�P��ԓ_�ł̉摜�ϐ�
	//p_enemy.E_StageHitflg = FALSE; // �ǂƂ̓����蔻��t���O
	p_enemy.R_Hitflg = FALSE;      // �C�W�P��Ԕ���t���O
	p_enemy.ER_Hitflg = FALSE;     // �C�W�P��ԓ_�Ńt���O
	p_enemy.PR_Hitflg = FALSE;     // �C�W�P��ԂŃv���C���[�ɓ����������̃t���O
	p_enemy.eyeflg = FALSE;        // �G�l�~�[�ڏ��
	p_enemy.Initiaflg = FALSE;     // �G�l�~�[������

	// �����ʒu��ۑ�
	p_enemy.x = P_ENEMY_POS_X;
	p_enemy.y = P_ENEMY_POS_Y;

	//�����蔻��
	p_enemy.recordX = p_enemy.x;
	p_enemy.recordY = p_enemy.y;

	p_enemy.top = P_ENEMY_POS_Y - P_ENEMY_POS_HITBOX;
	p_enemy.left = P_ENEMY_POS_X - P_ENEMY_POS_HITBOX;
	p_enemy.right = P_ENEMY_POS_X + P_ENEMY_POS_HITBOX;
	p_enemy.bottom = P_ENEMY_POS_Y + P_ENEMY_POS_HITBOX;

	p_enemy.recordTop = p_enemy.top;
	p_enemy.recordRight = p_enemy.right;
	p_enemy.recordBottom = p_enemy.bottom;
	p_enemy.recordLeft = p_enemy.left;

	// ���g�̏���������
	//���g�̃t���O����
	p_enemy.Top = FALSE;
	p_enemy.Bottom = FALSE;
	p_enemy.Left = TRUE;
	p_enemy.Right = TRUE;
	//���g�̍��W
	//��
	p_enemy.ENEMY_AVATAR_POS_X[0] = P_ENEMY_POS_X;
	p_enemy.ENEMY_AVATAR_POS_Y[0] = P_ENEMY_POS_Y - 24;
	//�E
	p_enemy.ENEMY_AVATAR_POS_X[1] = P_ENEMY_POS_X + 24;
	p_enemy.ENEMY_AVATAR_POS_Y[1] = P_ENEMY_POS_Y;
	//��
	p_enemy.ENEMY_AVATAR_POS_X[2] = P_ENEMY_POS_X;
	p_enemy.ENEMY_AVATAR_POS_Y[2] = P_ENEMY_POS_Y + 24;
	//��
	p_enemy.ENEMY_AVATAR_POS_X[3] = P_ENEMY_POS_X - 24;
	p_enemy.ENEMY_AVATAR_POS_Y[3] = P_ENEMY_POS_Y;

	// �O��̃L�[���͏���
	p_enemy.CheckNumber = 12;

	//���g�̓����蔻��
	for (int i = 0; i < 4; i++) {
		p_enemy.avatar_left[i] = ENEMY_AVATAR_POS_X[i] - P_ENEMY_POS_HITBOX;
		p_enemy.avatar_top[i] = ENEMY_AVATAR_POS_Y[i] - P_ENEMY_POS_HITBOX;
		p_enemy.avatar_right[i] = ENEMY_AVATAR_POS_X[i] + P_ENEMY_POS_HITBOX;
		p_enemy.avatar_bottom[i] = ENEMY_AVATAR_POS_Y[i] + P_ENEMY_POS_HITBOX;
	}
}

void P_ENEMY::Update() {
	//�O��̍��W�擾
	p_enemy.recordX = p_enemy.x;
	p_enemy.recordY = p_enemy.y;

	p_enemy.recordTop = p_enemy.top;
	p_enemy.recordRight = p_enemy.right;
	p_enemy.recordBottom = p_enemy.bottom;
	p_enemy.recordLeft = p_enemy.left;

	//�O��̍��W�ړ�
	p_enemy.absX = mPlayer.x - p_enemy.x;
	p_enemy.absY = mPlayer.y - p_enemy.y;

	//��Βl�����߂�
	if (p_enemy.absX <= 0) {
		p_enemy.absX = p_enemy.absX * -1;
	}
	if (p_enemy.absY <= 0) {
		p_enemy.absY = p_enemy.absY * -1;
	}

	//���g�̍��W
	for (int i = 0; i < 4; i++) {
		p_enemy.record_avatar_bottom[i] = p_enemy.avatar_bottom[i];
		p_enemy.record_avatar_left[i] = p_enemy.avatar_left[i];
		p_enemy.record_avatar_right[i] = p_enemy.avatar_right[i];
		p_enemy.record_avatar_top[i] = p_enemy.avatar_top[i];
	}

	// �v���C���[��ǂ������鏈��
	if (p_enemy.R_Hitflg == FALSE && mStage.MoveFlg == TRUE) { // �p���[�G�T������Ă��Ȃ���
		// �E����
		if (p_enemy.angle == 2) {
			if (p_enemy.Right == TRUE) {
				if (mPlayer.x < p_enemy.x) { // ������
					p_enemy.angle = 4;
				}
				else if (mPlayer.y < p_enemy.y) { // �����
					p_enemy.angle = 1;
				}
				else if (mPlayer.y > p_enemy.y) { // ������
					p_enemy.angle = 3;
				}
			}
			else if (p_enemy.Right == FALSE) {
				if (mPlayer.x < p_enemy.x) { // ������
					if (p_enemy.Left == FALSE) {
						p_enemy.angle = 4;
					}
				}
				else if (mPlayer.y < p_enemy.y) { // �����
					if (p_enemy.Top == FALSE) {
						p_enemy.angle = 1;
					}
				}
				else if (mPlayer.y > p_enemy.y) { // ������
					if (p_enemy.Bottom == FALSE) {
						p_enemy.angle = 3;
					}
				}
				// �E����
				p_enemy.x += p_enemy.speed;
				// �����蔻��
				p_enemy.left += p_enemy.speed;
				p_enemy.right += p_enemy.speed;
				//���g
				for (int i = 0; i < 4; i++) {
					p_enemy.avatar_right[i] += p_enemy.speed;
					p_enemy.avatar_left[i] += p_enemy.speed;
				}
				p_enemy.eyeimage = 1;
			}
		}
		// ������
		else if (p_enemy.angle == 4) {
			if (p_enemy.Left == TRUE) {
				if (mPlayer.x > p_enemy.x) { // �E����
					p_enemy.angle = 2;
				}
				else if (mPlayer.y < p_enemy.y) { // �����
					p_enemy.angle = 1;
				}
				else if (mPlayer.y > p_enemy.y) { // ������
					p_enemy.angle = 3;
				}
			}
			else if (p_enemy.Left == FALSE) {
				if (mPlayer.x > p_enemy.x) { // �E����
					if (p_enemy.Right == FALSE) {
						p_enemy.angle = 2;
					}
				}
				else if (mPlayer.y < p_enemy.y) { // �����
					if (p_enemy.Top == FALSE) {
						p_enemy.angle = 1;
					}
				}
				else if (mPlayer.y > p_enemy.y) { // ������
					if (p_enemy.Bottom == FALSE) {
						p_enemy.angle = 3;
					}
				}
				// ������
				p_enemy.x -= p_enemy.speed;
				//�����蔻��
				p_enemy.left -= p_enemy.speed;
				p_enemy.right -= p_enemy.speed;
				//���g
				for (int i = 0; i < 4; i++) {
					p_enemy.avatar_right[i] -= p_enemy.speed;
					p_enemy.avatar_left[i] -= p_enemy.speed;
				}
				p_enemy.eyeimage = 3;
			}
		}
		//������
		else if (p_enemy.angle == 3) {
			if (p_enemy.Bottom == TRUE) {
				if (mPlayer.x > p_enemy.x) { // �E����
					p_enemy.angle = 2;
				}
				else if (mPlayer.x < p_enemy.x) { // ������
					p_enemy.angle = 4;
				}
				else if (mPlayer.y < p_enemy.y) { // �����
					p_enemy.angle = 1;
				}
			}
			else if (p_enemy.Bottom == FALSE) {
				if (mPlayer.x > p_enemy.x) { // �E����
					if (p_enemy.Right == FALSE) {
						p_enemy.angle = 2;
					}
				}
				else if (mPlayer.x < p_enemy.x) { // ������
					if (p_enemy.Left == FALSE) {
						p_enemy.angle = 4;
					}
				}
				else if (mPlayer.y < p_enemy.y) { // �����
					if (p_enemy.Top == FALSE) {
						p_enemy.angle = 1;
					}
				}
				//������
				p_enemy.y += p_enemy.speed;
				//�����蔻��
				p_enemy.top += p_enemy.speed;
				p_enemy.bottom += p_enemy.speed;
				//���g
				for (int i = 0; i < 4; i++) {
					p_enemy.avatar_top[i] += p_enemy.speed;
					p_enemy.avatar_bottom[i] += p_enemy.speed;
				}
				p_enemy.eyeimage = 2;
			}
		}
		//�����
		else if (p_enemy.angle == 1) {
			if (p_enemy.Top == TRUE) {
				if (mPlayer.x > p_enemy.x) { // �E����
					p_enemy.angle = 2;
				}
				else if (mPlayer.x < p_enemy.x) { // ������
					p_enemy.angle = 4;
				}
				else if (mPlayer.y > p_enemy.y) { // ������
					p_enemy.angle = 3;
				}
			}
			else if (p_enemy.Top == FALSE) {
				if (mPlayer.x > p_enemy.x) { // �E����
					if (p_enemy.Right == FALSE) {
						p_enemy.angle = 2;
					}
				}
				else if (mPlayer.x < p_enemy.x) { // ������
					if (p_enemy.Left == FALSE) {
						p_enemy.angle = 4;
					}
				}
				else if (mPlayer.y > p_enemy.y) { // ������
					if (p_enemy.Bottom == FALSE) {
						p_enemy.angle = 3;
					}
				}
				//�����
				p_enemy.y -= p_enemy.speed;
				//�����蔻��
				p_enemy.top -= p_enemy.speed;
				p_enemy.bottom -= p_enemy.speed;
				//���g
				for (int i = 0; i < 4; i++) {
					p_enemy.avatar_top[i] -= p_enemy.speed;
					p_enemy.avatar_bottom[i] -= p_enemy.speed;
				}
				p_enemy.eyeimage = 0;
			}
		}
	}
	else if (p_enemy.R_Hitflg == TRUE) { // �p���[�G�T���������
		if (p_enemy.PR_Hitflg == FALSE) { // �v���C���[�Ɠ������Ă��Ȃ�������
			p_enemy.speed = 0.8;
			// �E����
			if (p_enemy.angle == 2) {
				if (p_enemy.Right == TRUE) {
					if (mPlayer.x < p_enemy.x) { // ������
						p_enemy.angle = 4;
					}
					else if (mPlayer.y < p_enemy.y) { // �����
						p_enemy.angle = 1;
					}
					else if (mPlayer.y > p_enemy.y) { // ������
						p_enemy.angle = 3;
					}
				}
				else if (p_enemy.Right == FALSE) {
					if (mPlayer.x < p_enemy.x) { // ������
						if (p_enemy.Left == FALSE) {
							p_enemy.angle = 4;
						}
					}
					else if (mPlayer.y < p_enemy.y) { // �����
						if (p_enemy.Top == FALSE) {
							p_enemy.angle = 1;
						}
					}
					else if (mPlayer.y > p_enemy.y) { // ������
						if (p_enemy.Bottom == FALSE) {
							p_enemy.angle = 3;
						}
					}
					// �E����
					p_enemy.x -= p_enemy.speed;
					// �����蔻��
					p_enemy.left -= p_enemy.speed;
					p_enemy.right -= p_enemy.speed;
					//���g
					for (int i = 0; i < 4; i++) {
						p_enemy.avatar_right[i] -= p_enemy.speed;
						p_enemy.avatar_left[i] -= p_enemy.speed;
					}
				}
			}
			// ������
			else if (p_enemy.angle == 4) {
				if (p_enemy.Left == TRUE) {
					if (mPlayer.x > p_enemy.x) { // �E����
						p_enemy.angle = 2;
					}
					else if (mPlayer.y < p_enemy.y) { // �����
						p_enemy.angle = 1;
					}
					else if (mPlayer.y > p_enemy.y) { // ������
						p_enemy.angle = 3;
					}
				}
				else if (p_enemy.Left == FALSE) {
					if (mPlayer.x > p_enemy.x) { // �E����
						if (p_enemy.Right == FALSE) {
							p_enemy.angle = 2;
						}
					}
					else if (mPlayer.y < p_enemy.y) { // �����
						if (p_enemy.Top == FALSE) {
							p_enemy.angle = 1;
						}
					}
					else if (mPlayer.y > p_enemy.y) { // ������
						if (p_enemy.Bottom == FALSE) {
							p_enemy.angle = 3;
						}
					}
					// ������
					p_enemy.x += p_enemy.speed;
					//�����蔻��
					p_enemy.left += p_enemy.speed;
					p_enemy.right += p_enemy.speed;
					//���g
					for (int i = 0; i < 4; i++) {
						p_enemy.avatar_right[i] += p_enemy.speed;
						p_enemy.avatar_left[i] += p_enemy.speed;
					}
				}
			}
			//������
			else if (p_enemy.angle == 3) {
				if (p_enemy.Bottom == TRUE) {
					if (mPlayer.x > p_enemy.x) { // �E����
						p_enemy.angle = 2;
					}
					else if (mPlayer.x < p_enemy.x) { // ������
						p_enemy.angle = 4;
					}
					else if (mPlayer.y < p_enemy.y) { // �����
						p_enemy.angle = 1;
					}
				}
				else if (p_enemy.Bottom == FALSE) {
					if (mPlayer.x > p_enemy.x) { // �E����
						if (p_enemy.Right == FALSE) {
							p_enemy.angle = 2;
						}
					}
					else if (mPlayer.x < p_enemy.x) { // ������
						if (p_enemy.Left == FALSE) {
							p_enemy.angle = 4;
						}
					}
					else if (mPlayer.y < p_enemy.y) { // �����
						if (p_enemy.Top == FALSE) {
							p_enemy.angle = 1;
						}
					}
					//������
					p_enemy.y -= p_enemy.speed;
					//�����蔻��
					p_enemy.top -= p_enemy.speed;
					p_enemy.bottom -= p_enemy.speed;
					//���g
					for (int i = 0; i < 4; i++) {
						p_enemy.avatar_top[i] -= p_enemy.speed;
						p_enemy.avatar_bottom[i] -= p_enemy.speed;
					}
				}
			}
			//�����
			else if (p_enemy.angle == 1) {
				if (p_enemy.Top == TRUE) {
					if (mPlayer.x > p_enemy.x) { // �E����
						p_enemy.angle = 2;
					}
					else if (mPlayer.x < p_enemy.x) { // ������
						p_enemy.angle = 4;
					}
					else if (mPlayer.y > p_enemy.y) { // ������
						p_enemy.angle = 3;
					}
				}
				else if (p_enemy.Top == FALSE) {
					if (mPlayer.x > p_enemy.x) { // �E����
						if (p_enemy.Right == FALSE) {
							p_enemy.angle = 2;
						}
					}
					else if (mPlayer.x < p_enemy.x) { // ������
						if (p_enemy.Left == FALSE) {
							p_enemy.angle = 4;
						}
					}
					else if (mPlayer.y > p_enemy.y) { // ������
						if (p_enemy.Bottom == FALSE) {
							p_enemy.angle = 3;
						}
					}
					//�����
					p_enemy.y += p_enemy.speed;
					//�����蔻��
					p_enemy.top += p_enemy.speed;
					p_enemy.bottom += p_enemy.speed;
					//���g
					for (int i = 0; i < 4; i++) {
						p_enemy.avatar_top[i] += p_enemy.speed;
						p_enemy.avatar_bottom[i] += p_enemy.speed;
					}
				}
			}
		}
		else if (p_enemy.PR_Hitflg == TRUE) { // �v���C���[�Ɠ������Ă����珉���ʒu�ɖ߂�
			if (p_enemy.eyeflg == TRUE) {
				p_enemy.speed = 3;
				// �E����
				if (p_enemy.angle == 2) {
					if (p_enemy.Right == TRUE) {
						if (ENEMY_POS_X < p_enemy.x) { // ������
							p_enemy.angle = 4;
						}
						else if (ENEMY_POS_Y < p_enemy.y) { // �����
							p_enemy.angle = 1;
						}
						else if (ENEMY_POS_Y > p_enemy.y) { // ������
							p_enemy.angle = 3;
						}
					}
					else if (p_enemy.Right == FALSE) {
						if (ENEMY_POS_X < p_enemy.x) { // ������
							if (p_enemy.Left == FALSE) {
								p_enemy.angle = 4;
							}
						}
						else if (ENEMY_POS_Y < p_enemy.y) { // �����
							if (p_enemy.Top == FALSE) {
								p_enemy.angle = 1;
							}
						}
						else if (ENEMY_POS_Y > p_enemy.y) { // ������
							if (p_enemy.Bottom == FALSE) {
								p_enemy.angle = 3;
							}
						}
						// �E����
						p_enemy.x += p_enemy.speed;
						// �����蔻��
						p_enemy.left += p_enemy.speed;
						p_enemy.right += p_enemy.speed;
						//���g
						for (int i = 0; i < 4; i++) {
							p_enemy.avatar_right[i] += p_enemy.speed;
							p_enemy.avatar_left[i] += p_enemy.speed;
						}
						p_enemy.eyeimage = 1;
					}
				}
				// ������
				else if (p_enemy.angle == 4) {
					if (p_enemy.Left == TRUE) {
						if (ENEMY_POS_X > p_enemy.x) { // �E����
							p_enemy.angle = 2;
						}
						else if (ENEMY_POS_Y < p_enemy.y) { // �����
							p_enemy.angle = 1;
						}
						else if (ENEMY_POS_Y > p_enemy.y) { // ������
							p_enemy.angle = 3;
						}
					}
					else if (p_enemy.Left == FALSE) {
						if (ENEMY_POS_X > p_enemy.x) { // �E����
							if (p_enemy.Right == FALSE) {
								p_enemy.angle = 2;
							}
						}
						else if (ENEMY_POS_Y < p_enemy.y) { // �����
							if (p_enemy.Top == FALSE) {
								p_enemy.angle = 1;
							}
						}
						else if (ENEMY_POS_Y > p_enemy.y) { // ������
							if (p_enemy.Bottom == FALSE) {
								p_enemy.angle = 3;
							}
						}
						// ������
						p_enemy.x -= p_enemy.speed;
						//�����蔻��
						p_enemy.left -= p_enemy.speed;
						p_enemy.right -= p_enemy.speed;
						//���g
						for (int i = 0; i < 4; i++) {
							p_enemy.avatar_right[i] -= p_enemy.speed;
							p_enemy.avatar_left[i] -= p_enemy.speed;
						}
						p_enemy.eyeimage = 3;
					}
				}
				//������
				else if (p_enemy.angle == 3) {
					if (p_enemy.Bottom == TRUE) {
						if (ENEMY_POS_X > p_enemy.x) { // �E����
							p_enemy.angle = 2;
						}
						else if (ENEMY_POS_X < p_enemy.x) { // ������
							p_enemy.angle = 4;
						}
						else if (ENEMY_POS_Y < p_enemy.y) { // �����
							p_enemy.angle = 1;
						}
					}
					else if (p_enemy.Bottom == FALSE) {
						if (ENEMY_POS_X > p_enemy.x) { // �E����
							if (p_enemy.Right == FALSE) {
								p_enemy.angle = 2;
							}
						}
						else if (ENEMY_POS_X < p_enemy.x) { // ������
							if (p_enemy.Left == FALSE) {
								p_enemy.angle = 4;
							}
						}
						else if (ENEMY_POS_Y < p_enemy.y) { // �����
							if (p_enemy.Top == FALSE) {
								p_enemy.angle = 1;
							}
						}
						//������
						p_enemy.y += p_enemy.speed;
						//�����蔻��
						p_enemy.top += p_enemy.speed;
						p_enemy.bottom += p_enemy.speed;
						//���g
						for (int i = 0; i < 4; i++) {
							p_enemy.avatar_top[i] += p_enemy.speed;
							p_enemy.avatar_bottom[i] += p_enemy.speed;
						}
						p_enemy.eyeimage = 2;
					}
				}
				//�����
				else if (p_enemy.angle == 1) {
					if (p_enemy.Top == TRUE) {
						if (ENEMY_POS_X > p_enemy.x) { // �E����
							p_enemy.angle = 2;
						}
						else if (ENEMY_POS_X < p_enemy.x) { // ������
							p_enemy.angle = 4;
						}
						else if (ENEMY_POS_Y > p_enemy.y) { // ������
							p_enemy.angle = 3;
						}
					}
					else if (p_enemy.Top == FALSE) {
						if (ENEMY_POS_X > p_enemy.x) { // �E����
							if (p_enemy.Right == FALSE) {
								p_enemy.angle = 2;
							}
						}
						else if (ENEMY_POS_X < p_enemy.x) { // ������
							if (p_enemy.Left == FALSE) {
								p_enemy.angle = 4;
							}
						}
						else if (ENEMY_POS_Y > p_enemy.y) { // ������
							if (p_enemy.Bottom == FALSE) {
								p_enemy.angle = 3;
							}
						}
						//�����
						p_enemy.y -= p_enemy.speed;
						//�����蔻��
						p_enemy.top -= p_enemy.speed;
						p_enemy.bottom -= p_enemy.speed;
						//���g
						for (int i = 0; i < 4; i++) {
							p_enemy.avatar_top[i] -= p_enemy.speed;
							p_enemy.avatar_bottom[i] -= p_enemy.speed;
						}
						p_enemy.eyeimage = 0;
					}
				}
				// �����ʒu�ɖ߂�����
				if (ENEMY_POS_X == p_enemy.x) {
					p_enemy.eyeflg = FALSE;
				}
			}
		}
	}

	// �G�l�~�[�ƃv���C���[�̓����蔻��
	if (P_EnemeyCheckHit(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, p_enemy.left, p_enemy.top, p_enemy.right, p_enemy.bottom)) {
		if (p_enemy.R_Hitflg == TRUE || p_enemy.ER_Hitflg == TRUE) { // �C�W�P��Ԃœ���������
			p_enemy.PR_Hitflg = TRUE;
			p_enemy.eyeflg = TRUE;
		}
	}

	// �A�j���[�V����
	++p_enemy.count;  // �J�E���g�J�n
	if (p_enemy.count >= 8) {  // �l�ɂ���ăA�j���[�V�����̃X�s�[�h���ω�����0�ɋ߂�������
		p_enemy.image++;
		p_enemy.izikeimage++;
		p_enemy.e_izikeimage++;
		p_enemy.count = 0;  // �J�E���g���Z�b�g
	}
	if (p_enemy.R_Hitflg == FALSE) { // �����C�W�P��ԂłȂ����
		if (p_enemy.image >= 4) { // �ʏ�̉摜�؂�ւ�
			p_enemy.image = 2;    // �摜���Z�b�g
		}
	}
	else if (p_enemy.R_Hitflg == TRUE) { // �����C�W�P��ԂȂ�
		if (p_enemy.izikeimage >= 18) { // �C�W�P�摜�؂�ւ�
			p_enemy.izikeimage = 16; // �摜���Z�b�g
		}
	}
	if (p_enemy.ER_Hitflg == TRUE) { // �����C�W�P��Ԃ��I��肻���Ȃ�
		if (p_enemy.e_izikeimage >= 20) { // �C�W�P�_�ŉ摜�؂�ւ�
			p_enemy.e_izikeimage = 16; // �摜���Z�b�g
		}
	}

	// ���[�v�g���l��
	if (p_enemy.x >= 878) {
		p_enemy.x = 352;

		//���g
		//��
		p_enemy.avatar_right[0] = 352 + P_ENEMY_POS_HITBOX;
		p_enemy.avatar_left[0] = 352 - P_ENEMY_POS_HITBOX;
		//��
		p_enemy.avatar_left[2] = 352 - P_ENEMY_POS_HITBOX;
		p_enemy.avatar_right[2] = 352 + P_ENEMY_POS_HITBOX;
		//�E
		p_enemy.avatar_left[1] = 352 + 24 - P_ENEMY_POS_HITBOX;
		p_enemy.avatar_right[1] = 352 + 24 + P_ENEMY_POS_HITBOX;
		//��
		p_enemy.avatar_right[3] = 352 - 24 - P_ENEMY_POS_HITBOX;
		p_enemy.avatar_left[3] = 352 - 24 + P_ENEMY_POS_HITBOX;
	}
	else if (p_enemy.x <= 352) {
		p_enemy.x = 878;

		//���g
		//��
		p_enemy.avatar_right[0] = 878 + P_ENEMY_POS_HITBOX;
		p_enemy.avatar_left[0] = 878 - P_ENEMY_POS_HITBOX;
		//��
		p_enemy.avatar_left[2] = 878 - P_ENEMY_POS_HITBOX;
		p_enemy.avatar_right[2] = 878 + P_ENEMY_POS_HITBOX;
		//�E
		p_enemy.avatar_left[1] = 878 + 24 - P_ENEMY_POS_HITBOX;
		p_enemy.avatar_right[1] = 878 + 24 + P_ENEMY_POS_HITBOX;
		//��
		p_enemy.avatar_right[3] = 878 - 24 - P_ENEMY_POS_HITBOX;
		p_enemy.avatar_left[3] = 878 - 24 + P_ENEMY_POS_HITBOX;
	}

	// �C�W�P��ԃt���O
	if (p_enemy.R_Hitflg == TRUE) {
		++p_enemy.ER_count;
	}
}

void P_ENEMY::Draw() {
	if (mStage.StateFlg == FALSE || mStage.GameOverFlg == TRUE) {		//�X�^�[�g�̎��̂ݕ\��
		DrawRotaGraph(p_enemy.x, p_enemy.y, 0, 0, p_enemy.images[p_enemy.image], TRUE, FALSE);
		DrawRotaGraph(p_enemy.x, p_enemy.y, 0, 0, p_enemy.eyesimages[p_enemy.eyeimage], TRUE, FALSE);
	}
	else if (mStage.StateFlg == TRUE) {
		DrawRotaGraph(p_enemy.x, p_enemy.y, 0.75, 0, p_enemy.images[2], TRUE, FALSE);
		DrawRotaGraph(p_enemy.x, p_enemy.y, 0.75, 0, p_enemy.eyesimages[3], TRUE, FALSE);
	}

	if (p_enemy.R_Hitflg == FALSE && mStage.MoveFlg == TRUE) { // �p���[�G�T������Ă��Ȃ����
		DrawRotaGraph(p_enemy.x, p_enemy.y, 0.75, 0, p_enemy.images[p_enemy.image], TRUE, FALSE); // �G�L�����\��
		DrawRotaGraph(p_enemy.x, p_enemy.y, 0.75, 0, p_enemy.eyesimages[p_enemy.eyeimage], TRUE, FALSE); // �G�L�����̖ڕ\��
		//DrawBox(p_enemy.left, p_enemy.top, p_enemy.right, p_enemy.bottom, 0x00ffff, FALSE); // �����蔻��`��
	}
	else if (p_enemy.R_Hitflg == TRUE) { // �p���[�G�T������Ă�����
		if (p_enemy.PR_Hitflg == FALSE) { // �v���C���[�Ɠ������Ă��Ȃ����
			if (p_enemy.ER_count <= 480) {
				DrawRotaGraph(p_enemy.x, p_enemy.y, 0.75, 0, p_enemy.images[p_enemy.izikeimage], TRUE, FALSE); // �C�W�P��ԕ\��
				//DrawBox(p_enemy.left, p_enemy.top, p_enemy.right, p_enemy.bottom, 0x00ffff, FALSE); // �����蔻��`��
			}
			else if (p_enemy.ER_count > 480 && p_enemy.ER_count <= 600) {
				p_enemy.ER_Hitflg = TRUE;
				DrawRotaGraph(p_enemy.x, p_enemy.y, 0.75, 0, p_enemy.images[p_enemy.e_izikeimage], TRUE, FALSE); // �C�W�P��ԕ\��
				//DrawBox(p_enemy.left, p_enemy.top, p_enemy.right, p_enemy.bottom, 0x00ffff, FALSE); // �����蔻��`��
			}
			else {
				p_enemy.R_Hitflg = FALSE;
				p_enemy.ER_Hitflg = FALSE;
				p_enemy.ER_count = 0;
				mPlayer.timercount = 0;
			}
		}
		else if (p_enemy.PR_Hitflg == TRUE) { // �v���C���[�Ɠ������Ă�����
			if (p_enemy.eyeflg == TRUE) { // �ڏ�ԂɂȂ�����
				DrawRotaGraph(p_enemy.x, p_enemy.y, 0.75, 0, p_enemy.eyesimages[p_enemy.eyeimage], TRUE, FALSE); // �G�L�����̖ڕ\��
				//DrawBox(p_enemy.left, p_enemy.top, p_enemy.right, p_enemy.bottom, 0x00ffff, FALSE); // �����蔻��`��
			}
			else if (p_enemy.eyeflg == FALSE) { // �ڏ�Ԃ̃G�l�~�[�������ʒu�ɖ߂�����
				p_enemy.R_Hitflg = FALSE;
				p_enemy.PR_Hitflg = FALSE;
				p_enemy.ER_Hitflg = FALSE;
				p_enemy.ER_count = 0;
				mPlayer.timercount = 0;
			}
		}
	}

	if (p_enemy.Initiaflg == TRUE) {
		// �����ʒu�ɖ߂�
		p_enemy.x = P_ENEMY_POS_X;
		p_enemy.y = P_ENEMY_POS_Y;
		p_enemy.top = P_ENEMY_POS_Y - P_ENEMY_POS_HITBOX;
		p_enemy.left = P_ENEMY_POS_X - P_ENEMY_POS_HITBOX;
		p_enemy.right = P_ENEMY_POS_X + P_ENEMY_POS_HITBOX;
		p_enemy.bottom = P_ENEMY_POS_Y + P_ENEMY_POS_HITBOX;
		p_enemy.Initiaflg = FALSE;

		//���g�̓����蔻��
		for (int i = 0; i < 4; i++) {
			p_enemy.avatar_left[i] = ENEMY_AVATAR_POS_X[i] - P_ENEMY_POS_HITBOX;
			p_enemy.avatar_top[i] = ENEMY_AVATAR_POS_Y[i] - P_ENEMY_POS_HITBOX;
			p_enemy.avatar_right[i] = ENEMY_AVATAR_POS_X[i] + P_ENEMY_POS_HITBOX;
			p_enemy.avatar_bottom[i] = ENEMY_AVATAR_POS_Y[i] + P_ENEMY_POS_HITBOX;
		}
	}

	////���g�̕\��
	//for (int i = 0; i < 4; i++) {
	//	DrawBox(p_enemy.avatar_left[i], p_enemy.avatar_top[i], p_enemy.avatar_right[i], p_enemy.avatar_bottom[i], 0x00ffff, FALSE);
	//}

	////�i�߂鎞
	////��
	//if (p_enemy.Top == TRUE) {
	//	DrawBox(p_enemy.avatar_left[0], p_enemy.avatar_top[0], p_enemy.avatar_right[0], p_enemy.avatar_bottom[0], 0xff00ff, true);
	//}
	//else if (p_enemy.Top == FALSE) {
	//	DrawBox(p_enemy.avatar_left[0], p_enemy.avatar_top[0], p_enemy.avatar_right[0], p_enemy.avatar_bottom[0], 0xff0000, true);
	//}
	////�E
	//if (p_enemy.Right == TRUE) {
	//	DrawBox(p_enemy.avatar_left[1], p_enemy.avatar_top[1], p_enemy.avatar_right[1], p_enemy.avatar_bottom[1], 0xff00ff, true);
	//}
	//else if (p_enemy.Right == FALSE) {
	//	DrawBox(p_enemy.avatar_left[1], p_enemy.avatar_top[1], p_enemy.avatar_right[1], p_enemy.avatar_bottom[1], 0xff0000, true);
	//}
	////��
	//if (p_enemy.Bottom == TRUE) {
	//	DrawBox(p_enemy.avatar_left[2], p_enemy.avatar_top[2], p_enemy.avatar_right[2], p_enemy.avatar_bottom[2], 0xff00ff, true);
	//}
	//else if (p_enemy.Bottom == FALSE) {
	//	DrawBox(p_enemy.avatar_left[2], p_enemy.avatar_top[2], p_enemy.avatar_right[2], p_enemy.avatar_bottom[2], 0xff0000, true);
	//}
	////��
	//if (p_enemy.Left == TRUE) {
	//	DrawBox(p_enemy.avatar_left[3], p_enemy.avatar_top[3], p_enemy.avatar_right[3], p_enemy.avatar_bottom[3], 0xff00ff, true);
	//}
	//else if (p_enemy.Left == FALSE) {
	//	DrawBox(p_enemy.avatar_left[3], p_enemy.avatar_top[3], p_enemy.avatar_right[3], p_enemy.avatar_bottom[3], 0xff0000, true);
	//}
}