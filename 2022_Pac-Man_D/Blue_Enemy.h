#pragma once
#include "Red_Enemy.h"

static int B_ENEMY_POS_X = 588;
static int B_ENEMY_POS_Y = 300;
static float B_ENEMY_POS_HITBOX = 11;

// 親クラス赤　子クラス青
class B_ENEMY : public R_ENEMY{
private:

public:
	void Initialize();
	void Update();
	void Draw();
};

extern B_ENEMY b_enemy;
