#include "DxLib.h"
#include "Red_Enemy.h"
#include "Player.h"

R_ENEMY r_enemy;

R_ENEMY::R_ENEMY() {
	r_enemy.x = 140;        // �����ʒu�c
	r_enemy.y = 360;        // �����ʒu��
	r_enemy.speed = 1;      // �ړ����x
	r_enemy.directionX = 0; // X����
	r_enemy.directionY = 0; // Y����
	r_enemy.count = 0;      // �A�j���[�V�����J�E���g
	r_enemy.image = 0;      // �摜�ϐ�
	r_enemy.eyeimage = 0;   // �ڂ̉摜�ϐ�
	r_enemy.num = 0;
}

R_ENEMY::~R_ENEMY() {
	//DeleteGraph(images[0]);
}

void R_ENEMY::Update() {
	// �v���C���[��ǂ������鏈��
	if (mPlayer.x >= r_enemy.x + 1) {       // �E����
		r_enemy.x += r_enemy.speed;
		r_enemy.eyeimage = 1;
	}
	else if (mPlayer.x <= r_enemy.x - 1) {  // ������
		r_enemy.x -= r_enemy.speed;
		r_enemy.eyeimage = 3;
	}
	if (mPlayer.y >= r_enemy.y + 1) {       // ������
		r_enemy.y += r_enemy.speed;
		r_enemy.eyeimage = 2;
	}
	else if (mPlayer.y <= r_enemy.y - 1) {  // �����
		r_enemy.y -= r_enemy.speed;
		r_enemy.eyeimage = 0;
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
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);  // �G�L����
	LoadDivGraph("images/eyes.png", 4, 4, 1, 32, 32, eyesimages);  // �G�L�����̖�
	DrawRotaGraph(r_enemy.x, r_enemy.y, 1, 0, images[r_enemy.image], TRUE, FALSE);  // �G�L�����\��
	DrawRotaGraph(r_enemy.x, r_enemy.y, 1, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE);  // �G�L�����̖ڕ\��
}