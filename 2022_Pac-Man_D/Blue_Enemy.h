#pragma once
#include "Red_Enemy.h"

static int B_ENEMY_POS_X = 636;
static int B_ENEMY_POS_Y = 252;
static float B_ENEMY_POS_HITBOX = 11;

// �e�N���X�ԁ@�q�N���X��
class B_ENEMY : public R_ENEMY{
private:

public:
	void Initialize();
	void Update();
	void Draw();
};

extern B_ENEMY b_enemy;
