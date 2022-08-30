#include "DxLib.h"
#include "Red_Enemy.h"
#include "Player.h"
//#include "Stage.cpp"

R_ENEMY r_enemy;

R_ENEMY::R_ENEMY() {
	r_enemy.speed = 1;      // �ړ����x
	r_enemy.directionX = 0; // X����
	r_enemy.directionY = 0; // Y����
	r_enemy.count = 0;      // �A�j���[�V�����J�E���g
	r_enemy.image = 0;      // �摜�ϐ�
	r_enemy.eyeimage = 0;   // �ڂ̉摜�ϐ�
	r_enemy.num = 0;

	r_enemy.x = ENEMY_POS_X;
	r_enemy.y = ENEMY_POS_Y;

	r_enemy.top = ENEMY_POS_Y - ENEMY_CENTER_HITBOX;
	r_enemy.left = ENEMY_POS_X - ENEMY_CENTER_HITBOX;
	r_enemy.right = ENEMY_POS_X + ENEMY_CENTER_HITBOX;
	r_enemy.bottom = ENEMY_POS_Y + ENEMY_CENTER_HITBOX;

	r_enemy.s_top = ENEMY_POS_Y - ENEMY_STAGE_HITBOX;
	r_enemy.s_left = ENEMY_POS_X - ENEMY_STAGE_HITBOX;
	r_enemy.s_right = ENEMY_POS_X + ENEMY_STAGE_HITBOX;
	r_enemy.s_bottom = ENEMY_POS_Y + ENEMY_STAGE_HITBOX;
}

R_ENEMY::~R_ENEMY() {
	//DeleteGraph(images[0]);
}

//int	CheckHit(int EnemyX, int EnemyY, int w1, int h1, int x, int y, int w, int h)
//{
//	int L1 = EnemyX;	  //�E
//	int R1 = EnemyX + w1; //��
//	int L2 = x;
//	int R2 = x + w;
//
//	if (R1 < L2) return 0;
//	if (R2 < L1) return 0;
//
//	int U1 = EnemyY;      // ��
//	int D1 = EnemyY + h1; // ��(��+�c��)
//	int U2 = x;
//	int D2 = x + w;
//
//	if (D1 < U2) return 0;
//	if (D2 < U1) return 0;
//
//
//	return 1;
//
//}
void R_ENEMY::Update() {
	r_enemy.absX = mPlayer.x - r_enemy.x;
	r_enemy.absY = mPlayer.y - r_enemy.y;

	//��Βl�̌v�Z
	if (r_enemy.absX < 0) {
		r_enemy.absX = r_enemy.absX * -1;
	}
	if (r_enemy.absY < 0) {
		r_enemy.absY = r_enemy.absY * -1;
	}

	//X�Ɉړ�
	if (r_enemy.absX > r_enemy.absY) {
		r_enemy.moveX = TRUE;
		r_enemy.moveY = FALSE;
	}
	//Y�Ɉړ�
	else if (r_enemy.absX < r_enemy.absY) {
		r_enemy.moveX = FALSE;
		r_enemy.moveY = TRUE;
	}

	// �v���C���[��ǂ������鏈��
	if (moveX == TRUE) {
		if (mPlayer.x >= r_enemy.x + 1) {       // �E����
			r_enemy.x += r_enemy.speed;

			//�����蔻��
			r_enemy.left += r_enemy.speed;
			r_enemy.right += r_enemy.speed;

			r_enemy.s_left += r_enemy.speed;
			r_enemy.s_right += r_enemy.speed;

			r_enemy.eyeimage = 1;
		}
		else if (mPlayer.x <= r_enemy.x - 1) {  // ������
			r_enemy.x -= r_enemy.speed;

			//�����蔻��
			r_enemy.left -= r_enemy.speed;
			r_enemy.right -= r_enemy.speed;

			r_enemy.s_left -= r_enemy.speed;
			r_enemy.s_right -= r_enemy.speed;

			r_enemy.eyeimage = 3;
		}
	}
	else if (moveY == TRUE) {
		if (mPlayer.y >= r_enemy.y + 1) {       // ������
			r_enemy.y += r_enemy.speed;

			//�����蔻��
			r_enemy.top += r_enemy.speed;
			r_enemy.bottom += r_enemy.speed;

			r_enemy.s_top += r_enemy.speed;
			r_enemy.s_bottom += r_enemy.speed;

			r_enemy.eyeimage = 2;
		}
		else if (mPlayer.y <= r_enemy.y - 1) {  // �����
			r_enemy.y -= r_enemy.speed;

			//�����蔻��
			r_enemy.top -= r_enemy.speed;
			r_enemy.bottom -= r_enemy.speed;

			r_enemy.s_top -= r_enemy.speed;
			r_enemy.s_bottom -= r_enemy.speed;

			r_enemy.eyeimage = 0;
		}
	}

	for (int j = 0; j < ENEMY_POS_X; j++) {
		for (int i = 0; i < ENEMY_POS_X; i++) {

			//if (CheckHit(i * ENEMY_POS_X, j * ENEMY_POS_Y, ENEMY_POS_X, ENEMY_POS_Y, r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom))
			//{
			//	//�ړ�
			//	r_enemy.x = r_enemy.recordX;
			//	r_enemy.y = r_enemy.recordY;

			//	//�����蔻��ړ�
			//	r_enemy.top = r_enemy.recordTop;
			//	r_enemy.right = r_enemy.recordRight;
			//	r_enemy.bottom = r_enemy.recordBottom;
			//	r_enemy.left = r_enemy.recordLeft;
			//}

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
	}
}

//int	CheckHit(int EnemyX, int EnemyY, int w1, int h1, int x, int y, int w, int h)
//{
//    int L1 = EnemyX;
//    int R1 = EnemyX + w1;
//    int L2 = x;
//    int R2 = x + w;
//
//    if (R1 < L2) return 0;
//    if (R2 < L1) return 0;
//
//    int U1 = EnemyY;      // ��
//    int D1 = EnemyY + h1; // ��(��+�c��)
//    int U2 = x;
//    int D2 = x + w;
//
//    if (D1 < U2) return 0;
//    if (D2 < U1) return 0;


    /* int R_ENEMY::HitBoxEnemy(R_ENEMY* e) {
         int dx1 = e->EnemyX - (e->w / 4);
         int dy1 = e->EnemyY - (e->h / 4);
         int dx2 = dx1 + e->w / 2;
         int dy2 = dy1 + e->h / 2.5;


     }*/

//}
    
void R_ENEMY::Draw() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);  // �G�L����
	LoadDivGraph("images/eyes.png", 4, 4, 1, 32, 32, eyesimages);  // �G�L�����̖�
	DrawRotaGraph(r_enemy.x, r_enemy.y, 1, 0, images[r_enemy.image], TRUE, FALSE);  // �G�L�����\��
	DrawRotaGraph(r_enemy.x, r_enemy.y, 1, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE);  // �G�L�����̖ڕ\��
	DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE);
}
