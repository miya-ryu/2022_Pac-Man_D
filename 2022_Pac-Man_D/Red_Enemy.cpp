#include "DxLib.h"
#include "Red_Enemy.h"
#include "Player.h"

R_ENEMY r_enemy;

void R_ENEMY::R_Initialize() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);  // �G�L����
	LoadDivGraph("images/eyes.png", 4, 4, 1, 32, 32, eyesimages);  // �G�L�����̖�

	r_enemy.speed = 1;      // �ړ����x
	r_enemy.directionX = 0; // X����
	r_enemy.directionY = 0; // Y����
	r_enemy.count = 0;      // �A�j���[�V�����J�E���g
	r_enemy.image = 0;      // �摜�ϐ�
	r_enemy.eyeimage = 0;   // �ڂ̉摜�ϐ�
	r_enemy.Hitimage = 16;   // �C�W�P�����X�^�[�摜

	r_enemy.x = ENEMY_POS_X;
	r_enemy.y = ENEMY_POS_Y;

	r_enemy.recordX = r_enemy.x;
	r_enemy.recordY = r_enemy.y;

	r_enemy.top = ENEMY_POS_Y - ENEMY_STAGE_HITBOX;
	r_enemy.left = ENEMY_POS_X - ENEMY_STAGE_HITBOX;
	r_enemy.right = ENEMY_POS_X + ENEMY_STAGE_HITBOX;
	r_enemy.bottom = ENEMY_POS_Y + ENEMY_STAGE_HITBOX;

	r_enemy.moveX = TRUE;
	r_enemy.moveY = FALSE;

	r_enemy.recordTop = r_enemy.top;
	r_enemy.recordRight = r_enemy.right;
	r_enemy.recordBottom = r_enemy.bottom;
	r_enemy.recordLeft = r_enemy.left;
	//r_enemy.s_top = ENEMY_POS_Y - ENEMY_STAGE_HITBOX;
	//r_enemy.s_left = ENEMY_POS_X - ENEMY_STAGE_HITBOX;
	//r_enemy.s_right = ENEMY_POS_X + ENEMY_STAGE_HITBOX;
	//r_enemy.s_bottom = ENEMY_POS_Y + ENEMY_STAGE_HITBOX;

	r_enemy.R_Hitflg = true;
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
	if (moveX == TRUE) {
		if (mPlayer.x >= r_enemy.x + 1) {       // �E����
			r_enemy.x += r_enemy.speed;

			//�����蔻��
			r_enemy.left += r_enemy.speed;
			r_enemy.right += r_enemy.speed;

			r_enemy.eyeimage = 1;
		}
		else if (mPlayer.x <= r_enemy.x - 1) {  // ������
			r_enemy.x -= r_enemy.speed;

			//�����蔻��
			r_enemy.left -= r_enemy.speed;
			r_enemy.right -= r_enemy.speed;

			r_enemy.eyeimage = 3;
		}
	}
	else if (moveY == TRUE) {
		if (mPlayer.y >= r_enemy.y + 1) {       // ������
			r_enemy.y += r_enemy.speed;

			//�����蔻��
			r_enemy.top += r_enemy.speed;
			r_enemy.bottom += r_enemy.speed;

			r_enemy.eyeimage = 2;
		}
		else if (mPlayer.y <= r_enemy.y - 1) {  // �����
			r_enemy.y -= r_enemy.speed;

			//�����蔻��
			r_enemy.top -= r_enemy.speed;
			r_enemy.bottom -= r_enemy.speed;

			r_enemy.eyeimage = 0;
		}
	}

	// �A�j���[�V����
	++count;  // �J�E���g�J�n
	if (count >= 8) {  // �l�ɂ���ăA�j���[�V�����̃X�s�[�h���ω�����0�ɋ߂�������
		r_enemy.image++;
		r_enemy.Hitimage++;
		count = 0;  // �J�E���g���Z�b�g
	}
	if (r_enemy.image >= 2) { // �摜�̐؂�ւ�
		r_enemy.image = 0;    // �摜���Z�b�g
	}
	// �C�W�P�����X�^�[���
	/*if (r_enemy.R_Hitflg == true) {
		if (r_enemy.Hitimage >= 18) {
			r_enemy.Hitimage = 16;
		}
	}*/

	// ���[�v�g���l��
	if (r_enemy.x >= 890) {
		r_enemy.x = 340;
	}
	else if (r_enemy.x <= 340) {
		r_enemy.x = 890;
	}
}
    
void R_ENEMY::Draw() {
	DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[r_enemy.image], TRUE, FALSE);  // �G�L�����\��
	DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE);  // �G�L�����̖ڕ\��
	DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE);
	//DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[r_enemy.Hitimage], TRUE, FALSE);  // �C�W�P�����X�^�[��ԕ\��
}
