#pragma once
#include "Red_Enemy.h"

// �e�N���X�ԁ@�q�N���X��
class B_ENEMY : public R_ENEMY{
private:

public:
	B_ENEMY();
	~B_ENEMY();
	void Update();
	void Draw();
};

extern B_ENEMY b_enemy;
