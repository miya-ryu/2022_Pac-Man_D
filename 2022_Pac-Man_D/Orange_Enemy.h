#pragma once
#include "Red_Enemy.h"

class O_ENEMY : public R_ENEMY{
private:
	int Enemy_image[20];
public:
	O_ENEMY();
	~O_ENEMY();
	void Update();
	void Draw();
};

extern O_ENEMY o_enemy;
