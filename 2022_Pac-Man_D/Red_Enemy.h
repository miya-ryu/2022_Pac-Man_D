#pragma once

class R_ENEMY {
private:
	int Enemy_image[20];
public:
	R_ENEMY();
	~R_ENEMY();
	void Update();
	void Draw();
};

extern R_ENEMY r_enemy;