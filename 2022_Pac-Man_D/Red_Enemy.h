#pragma once

static int ENEMY_POS_X = 612;
static int ENEMY_POS_Y = 252;
static float ENEMY_STAGE_HITBOX = 11;

// �e�N���X��
class R_ENEMY {
private:

public:
	~R_ENEMY();  // c�����FInalize�Ɠ�������
	void R_Initialize();
	void Update();
	void Draw();

	// �G�̉摜�ۊǔz��
	static const int MaxImage = 20;
	static const int MaxEyeImage = 4;
	int images[MaxImage];
	int eyesimages[MaxEyeImage];
	int image, eyeimage, Hitimage;
	// �G�Ɋւ���ϐ�
	int x, y, x1, y1;
	int absX, absY;
	int angle;
	int speed;
	int recordX, recordY;
	//Player�Ƃ̓����蔻��
	int top, right, bottom, left;
	int recordTop, recordRight, recordBottom, recordLeft;
	int count;
	// �G�̍��W��ۊǂ���ϐ�
	int w, h;	// �� w ���� h;
	int CheckHit;
	// �C�W�P�����X�^�[���
	bool R_Hitflg;
	//�ǂɓ��������t���O
	bool E_StageHitflg;
	//�v���C���[�ɓ���������
	bool E_EnemeyHitflg;
};

extern R_ENEMY r_enemy;