#pragma once
#include "DxLib.h"

class Player {
private:
	int x, y;
	int move;
	int count;
	int image;
	static const int MaxImage = 11;
	int muki;
	//Ši”[
	int mPlayerImage[MaxImage];

public:
	Player();
	void Player_Update();
	void Player_Draw();
};

extern Player mPlayer;