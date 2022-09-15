#pragma once

static int ENEMY_POS_X = 612;
static int ENEMY_POS_Y = 252;
static float ENEMY_STAGE_HITBOX = 11;

// �e�N���X��
class R_ENEMY {
private:

public:
	void Initialize();
	void Update();
	void Draw();

	// �G�̉摜�ۊǔz��
	static const int MaxImage = 20;
	static const int MaxEyeImage = 4;
	int images[MaxImage];
	int eyesimages[MaxEyeImage];
	int image, eyeimage, izikeimage, e_izikeimage;
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
	// �C�W�P�����X�^�[�_�ŏ��
	bool ER_Hitflg;
	int ER_count;
	// �C�W�P�����X�^�[���v���C���[�ɓ����������
	bool PR_Hitflg;
	// �G�l�~�[�ڏ��
	bool eyeflg;
	// �ǂɓ��������t���O
	//bool E_StageHitflg;
	bool Initiaflg;
	// ���W�v�Z
	int xy, xy2, xx, yy;
};

extern R_ENEMY r_enemy;