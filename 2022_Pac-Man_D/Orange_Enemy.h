#pragma once
#include "Red_Enemy.h"

static int O_ENEMY_POS_X = 636;
static int O_ENEMY_POS_Y = 300;
static float O_ENEMY_POS_HITBOX = 11;

// 親クラス赤　子クラスオレンジ
class O_ENEMY : public R_ENEMY{
private:

public:
	void Initialize();
	void Update();
	void Draw();
};

extern O_ENEMY o_enemy;
