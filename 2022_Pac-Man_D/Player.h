#pragma once
#include "DxLib.h"

class Player {
private:
	int x, y;
	int move;

	static const int MaxImage = 11;

	//Ši”[
	int mPlayerImage[MaxImage];

public:
	Player();
	void Player_Update();
	void Player_Draw();
};

extern Player mPlayer;