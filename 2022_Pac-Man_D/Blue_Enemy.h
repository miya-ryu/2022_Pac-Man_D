#pragma once
#include "Red_Enemy.h"

class B_ENEMY : public R_ENEMY{
private:
	int Enemy_image[20];
public:
	B_ENEMY();
	~B_ENEMY();
	void Update();
	void Draw();
};

extern B_ENEMY b_enemy;
