#pragma once
#include "Red_Enemy.h"

// �e�N���X�ԁ@�q�N���X�I�����W
class O_ENEMY : public R_ENEMY{
private:

public:
	O_ENEMY();
	~O_ENEMY();
	void Update();
	void Draw();
};

extern O_ENEMY o_enemy;
