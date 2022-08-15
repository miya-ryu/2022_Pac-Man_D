#include "DxLib.h"
#include "Red_Enemy.h"
#include "Player.h"

R_ENEMY r_enemy;

R_ENEMY::R_ENEMY() {
	r_enemy.x = 140;       // �����ʒu�c
	r_enemy.y = 360;       // �����ʒu��
	r_enemy.speed = 2;     // �ړ����x
	r_enemy.direction = 0; // ����
	r_enemy.count = 0;     // �A�j���[�V�����J�E���g
	r_enemy.image = 0;     // �摜�ϐ�
	r_enemy.eyeimage = 0;  // �ڂ̉摜�ϐ�
	r_enemy.num = 0;
}

R_ENEMY::~R_ENEMY() {
	//DeleteGraph(images[0]);
}

void R_ENEMY::Update() {
	/*if (r_enemy.x != mPlayer.x || r_enemy.y != mPlayer.y) {
		r_enemy.x += r_enemy.speed;
		r_enemy.y += r_enemy.speed;
		r_enemy.x = mPlayer.x;
		r_enemy.y = mPlayer.y;
	}
	else if (r_enemy.x == mPlayer.x || r_enemy.y == mPlayer.y) {
		DrawFormatString(100, 100, (255, 255, 255), "��������");
	}*/


	// �A�j���[�V����
	++count;  // �J�E���g�J�n
	if (count >= 8) {  // �l�ɂ���ăA�j���[�V�����̃X�s�[�h���ω�����0�ɋ߂�������
		r_enemy.image++;
		count = 0;  // �J�E���g���Z�b�g
	}
	if (r_enemy.image >= 2) { // �摜�̐؂�ւ�
		r_enemy.image = 0;    // �摜���Z�b�g
	}

	//num = rand() % 99 + 0;

	//r_enemy.x += r_enemy.speed;

	r_enemy.direction = mPlayer.x - r_enemy.x;

	r_enemy.x -= r_enemy.direction * r_enemy.speed;

	if (num == 0) {       // �E����
		r_enemy.eyeimage = 1;
		r_enemy.x += r_enemy.speed;
	}
	else if (num == 1) {  // ������
		r_enemy.eyeimage = 3;
		r_enemy.x -= r_enemy.speed;
	}
	else if (num == 2) {  // �����
		r_enemy.eyeimage = 0;
		r_enemy.x -= r_enemy.speed;
	}
	else if (num == 3) {  // ������
		r_enemy.eyeimage = 2;
		r_enemy.x += r_enemy.speed;
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