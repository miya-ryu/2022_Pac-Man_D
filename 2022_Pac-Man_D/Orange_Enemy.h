#pragma once
#include "Red_Enemy.h"

// 親クラス赤　子クラスオレンジ
class O_ENEMY : public R_ENEMY{
private:

public:
	O_ENEMY();
	~O_ENEMY();
	void Update();
	void Draw();
};

extern O_ENEMY o_enemy;
