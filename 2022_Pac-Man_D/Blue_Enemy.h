#pragma once
#include "Red_Enemy.h"

// 親クラス赤　子クラス青
class B_ENEMY : public R_ENEMY{
private:

public:
	B_ENEMY();
	~B_ENEMY();
	void Update();
	void Draw();
};

extern B_ENEMY b_enemy;
