#include "DxLib.h"
#include "Red_Enemy.h"
#include "Player.h"

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
	r_enemy.count = 0;             // �A�j���[�V�����J�E���g
	r_enemy.E_count = 0;           // �C�W�P��ԃJ�E���g
	r_enemy.image = 0;             // �摜�ϐ�
	r_enemy.eyeimage = 0;          // �ڂ̉摜�ϐ�
	r_enemy.izikeimage = 16;       // �C�W�P��Ԃ̉摜�ϐ�
	r_enemy.e_izikeimage = 16;     // �C�W�P��ԓ_�ł̉摜�ϐ�
	r_enemy.E_StageHitflg = FALSE; // �ǂƂ̓����蔻��t���O
	r_enemy.E_EnemeyHitflg = FALSE;// �v���C���[�ƃG�l�~�[�̓����蔻��t���O
	r_enemy.R_Hitflg = FALSE;      // �C�W�P��Ԕ���t���O
	r_enemy.ER_Hitflg = FALSE;     // �C�W�P��ԓ_�Ńt���O

	r_enemy.x = ENEMY_POS_X;
	r_enemy.y = ENEMY_POS_Y;

	// �����̌���
	r_enemy.angle = 3;

	//�����蔻��
	r_enemy.recordX = r_enemy.x;
	r_enemy.recordY = r_enemy.y;

	r_enemy.top = ENEMY_POS_Y - ENEMY_STAGE_HITBOX;
	r_enemy.left = ENEMY_POS_X - ENEMY_STAGE_HITBOX;
	r_enemy.right = ENEMY_POS_X + ENEMY_STAGE_HITBOX;
	r_enemy.bottom = ENEMY_POS_Y + ENEMY_STAGE_HITBOX;

	r_enemy.recordTop = r_enemy.top;
	r_enemy.recordRight = r_enemy.right;
	r_enemy.recordBottom = r_enemy.bottom;
	r_enemy.recordLeft = r_enemy.left;
}

void R_ENEMY::Update() {
	//�O��̍��W�擾
	r_enemy.recordX = r_enemy.x;
	r_enemy.recordY = r_enemy.y;

	r_enemy.recordTop = r_enemy.top;
	r_enemy.recordRight = r_enemy.right;
	r_enemy.recordBottom = r_enemy.bottom;
	r_enemy.recordLeft = r_enemy.left;

	// �v���C���[��ǂ������鏈��
	if (r_enemy.R_Hitflg == FALSE) { // �p���[�G�T������Ă��Ȃ���
		//�E����
		if (angle == 1) {
			r_enemy.x += r_enemy.speed;

			//�����蔻��
			r_enemy.left += r_enemy.speed;
			r_enemy.right += r_enemy.speed;

			r_enemy.eyeimage = 1;
		}
		//������
		else if (angle == 2) {
			r_enemy.y += r_enemy.speed;

			//�����蔻��
			r_enemy.top += r_enemy.speed;
			r_enemy.bottom += r_enemy.speed;

			r_enemy.eyeimage = 2;
		}
		//������
		else if (angle == 3) {
			r_enemy.x -= r_enemy.speed;

			r_enemy.left -= r_enemy.speed;
			r_enemy.right -= r_enemy.speed;

			r_enemy.eyeimage = 3;
		}
		//�����
		else if (angle == 4) {
			r_enemy.y -= r_enemy.speed;

			//�����蔻��
			r_enemy.top -= r_enemy.speed;
			r_enemy.bottom -= r_enemy.speed;

			r_enemy.eyeimage = 0;
		}
	}
	else if (r_enemy.R_Hitflg == TRUE) { // �p���[�G�T���������
		//�E����
		if (angle == 1) {
			r_enemy.x -= r_enemy.speed;

			//�����蔻��
			r_enemy.left -= r_enemy.speed;
			r_enemy.right -= r_enemy.speed;
		}
		//������
		else if (angle == 2) {
			r_enemy.y -= r_enemy.speed;

			//�����蔻��
			r_enemy.top -= r_enemy.speed;
			r_enemy.bottom -= r_enemy.speed;
		}
		//������
		else if (angle == 3) {
			r_enemy.x += r_enemy.speed;

			r_enemy.left += r_enemy.speed;
			r_enemy.right += r_enemy.speed;
		}
		//�����
		else if (angle == 4) {
			r_enemy.y += r_enemy.speed;

			//�����蔻��
			r_enemy.top += r_enemy.speed;
			r_enemy.bottom += r_enemy.speed;
		}
	}

	// �v���C���[�ƃG�l�~�[�̓����蔻��
	if (EnemeyCheckHit(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom)) {
		r_enemy.E_EnemeyHitflg = TRUE;
	}

	// �A�j���[�V����
	++count;  // �J�E���g�J�n
	if (count >= 8) {  // �l�ɂ���ăA�j���[�V�����̃X�s�[�h���ω�����0�ɋ߂�������
		r_enemy.image++;
		r_enemy.izikeimage++;
		r_enemy.e_izikeimage++;
		count = 0;  // �J�E���g���Z�b�g
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
	if (r_enemy.x >= 1280) {
		r_enemy.x = 0;
	}
	else if (r_enemy.x <= 0) {
		r_enemy.x = 1280;
	}

	// �C�W�P��ԃt���O
	if (r_enemy.R_Hitflg == TRUE) {
		++E_count;
	}
}

void R_ENEMY::Draw() {
	if (r_enemy.R_Hitflg == FALSE) {
		if (r_enemy.E_EnemeyHitflg == FALSE) {
			DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[r_enemy.image], TRUE, FALSE);  // �G�L�����\��
			DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE);  // �G�L�����̖ڕ\��
			DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE);
		}
	}
	else if (r_enemy.R_Hitflg == TRUE) {
		if (E_count <= 480) {
			DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[r_enemy.izikeimage], TRUE, FALSE);  // �C�W�P��ԕ\��
			DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE);
		}
		else if (E_count > 480 && E_count <= 600) {
			ER_Hitflg = TRUE;
			DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[r_enemy.e_izikeimage], TRUE, FALSE);  // �C�W�P��ԕ\��
			DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE);
		}
		else {
			r_enemy.R_Hitflg = FALSE;
			E_count = 0;
		}
	}
}