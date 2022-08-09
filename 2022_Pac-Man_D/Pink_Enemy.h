#pragma once
#include "Red_Enemy.h"

class P_ENEMY : public R_ENEMY{
private:
	int Enemy_image[20];
public:
	P_ENEMY();
	~P_ENEMY();
	void Update();
	void Draw();
};

extern P_ENEMY p_enemy;