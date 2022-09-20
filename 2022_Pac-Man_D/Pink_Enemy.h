#pragma once
#include "Red_Enemy.h"

static int P_ENEMY_POS_X = 612;
static int P_ENEMY_POS_Y = 324;
static float P_ENEMY_POS_HITBOX = 11;

// 親クラス赤　子クラスピンク
class P_ENEMY : public R_ENEMY{
private:

public:
	void Initialize();
	void Update();
	void Draw();
};

extern P_ENEMY p_enemy;