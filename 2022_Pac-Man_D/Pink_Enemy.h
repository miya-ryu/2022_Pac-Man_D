#pragma once
#include "Red_Enemy.h"

// �e�N���X�ԁ@�q�N���X�s���N
class P_ENEMY : public R_ENEMY{
private:

public:
	P_ENEMY();
	~P_ENEMY();
	void Update();
	void Draw();
};

extern P_ENEMY p_enemy;