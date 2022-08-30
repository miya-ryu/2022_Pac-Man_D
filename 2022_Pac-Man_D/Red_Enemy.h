#pragma once

static int ENEMY_POS_X = 612;
static int ENEMY_POS_Y = 24*11;
static int ENEMY_CENTER_HITBOX = 4;
static float ENEMY_STAGE_HITBOX = 7;

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
	int image, eyeimage;
	// �G�Ɋւ���ϐ�
	int x, y, x1, y1;
	int absX, absY;
	bool moveX, moveY;
	int speed;
	int directionX;
	int directionY;
	int recordX, recordY;
	int top, right, bottom, left;	//Player�Ƃ̓����蔻��
	int s_top, s_right, s_bottom, s_left;	//Stage�Ƃ̓����蔻��
	int recordTop, recordRight, recordBottom, recordLeft;
	int count;
	int num;
	int Enemy_image[20];
	// �G�̍��W��ۊǂ���ϐ�
	int w, h;	// �� w ���� h;
	int CheckHit;
	//int HitBoxEnemy(R_ENEMY* e);
};

extern R_ENEMY r_enemy;