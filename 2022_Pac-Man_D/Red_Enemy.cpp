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
int millisecond2 = 0.01 * 1000;
void R_ENEMY::R_Initialize() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);  // �G�L����
	LoadDivGraph("images/eyes.png", 4, 4, 1, 32, 32, eyesimages);  // �G�L�����̖�

	r_enemy.speed = 1;      // �ړ����x
	r_enemy.count = 0;      // �A�j���[�V�����J�E���g
	r_enemy.image = 0;      // �摜�ϐ�
	r_enemy.eyeimage = 0;   // �ڂ̉摜�ϐ�
	r_enemy.E_StageHitflg = FALSE; // �ǂƂ̓����蔻��t���O
	r_enemy.E_EnemeyHitflg = FALSE;

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

R_ENEMY::~R_ENEMY() {
	//DeleteGraph(images[0]);
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

	if (EnemeyCheckHit(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom)) {
		Sleep(millisecond2);
		r_enemy.E_EnemeyHitflg = TRUE;
	}

	// �A�j���[�V����
	++count;  // �J�E���g�J�n
	if (count >= 8) {  // �l�ɂ���ăA�j���[�V�����̃X�s�[�h���ω�����0�ɋ߂�������
		r_enemy.image++;
		count = 0;  // �J�E���g���Z�b�g
	}
	if (r_enemy.image >= 2) { // �摜�̐؂�ւ�
		r_enemy.image = 0;    // �摜���Z�b�g
	}

	// ���[�v�g���l��
	if (r_enemy.x >= 1280) {
		r_enemy.x = 0;
	}
	else if (r_enemy.x <= 0) {
		r_enemy.x = 1280;
	}
}

void R_ENEMY::Draw() {
	if (r_enemy.E_EnemeyHitflg == FALSE) {
		
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[r_enemy.image], TRUE, FALSE);  // �G�L�����\��
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE);  // �G�L�����̖ڕ\��
		DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE);
	}
	else if (r_enemy.E_EnemeyHitflg == TRUE) {
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[r_enemy.image], TRUE, FALSE);  // �G�L�����\��
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE);  // �G�L�����̖ڕ\��
	}
}