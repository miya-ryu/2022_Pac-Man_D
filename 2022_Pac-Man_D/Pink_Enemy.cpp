#include "DxLib.h"
#include "Pink_Enemy.h"
#include "Player.h"

P_ENEMY p_enemy;

P_ENEMY::P_ENEMY() {
	p_enemy.x = 120;        // �����ʒu�c
	p_enemy.y = 360;        // �����ʒu��
	p_enemy.speed = 1;      // �ړ����x
	p_enemy.directionX = 0; // X����
	p_enemy.directionY = 0; // Y����
	p_enemy.count = 0;      // �A�j���[�V�����J�E���g
	p_enemy.image = 2;      // �摜�ϐ�
	p_enemy.eyeimage = 0;   // �ڂ̉摜�ϐ�
}

P_ENEMY::~P_ENEMY() {
	//DeleteGraph(images[0]);
}

void P_ENEMY::Update() {
	// �v���C���[��ǂ������鏈��
	if (mPlayer.x >= p_enemy.x + 1) {       // �E����
		p_enemy.x += p_enemy.speed;
		p_enemy.eyeimage = 1;
	}
	else if (mPlayer.x <= p_enemy.x - 1) {  // ������
		p_enemy.x -= p_enemy.speed;
		p_enemy.eyeimage = 3;
	}
	if (mPlayer.y >= p_enemy.y + 1) {       // ������
		p_enemy.y += p_enemy.speed;
		p_enemy.eyeimage = 2;
	}
	else if (mPlayer.y <= p_enemy.y - 1) {  // �����
		p_enemy.y -= p_enemy.speed;
		p_enemy.eyeimage = 0;
	}

	// �A�j���[�V����
	++count;  // �J�E���g�J�n
	if (count >= 8) {  // �l�ɂ���ăA�j���[�V�����̃X�s�[�h���ω�����0�ɋ߂�������
		p_enemy.image++;
		count = 0;  // �J�E���g���Z�b�g
	}
	if (p_enemy.image >= 4) { // �摜�̐؂�ւ�
		p_enemy.image = 2;    // �摜���Z�b�g
	}

	// ���[�v�g���l��
	if (p_enemy.x >= 1280) {
		p_enemy.x = 0;
	}
	else if (p_enemy.x <= 0) {
		p_enemy.x = 1280;
	}
}

void P_ENEMY::Draw() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);  // �G�L����
	LoadDivGraph("images/eyes.png", 4, 4, 1, 32, 32, eyesimages);  // �G�L�����̖�
	DrawRotaGraph(p_enemy.x, p_enemy.y, 1, 0, images[p_enemy.image], TRUE, FALSE);  // �G�L�����\��
	DrawRotaGraph(p_enemy.x, p_enemy.y, 1, 0, eyesimages[p_enemy.eyeimage], TRUE, FALSE);  // �G�L�����̖ڕ\��
}