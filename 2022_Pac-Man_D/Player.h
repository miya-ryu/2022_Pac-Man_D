#pragma once
#include "DxLib.h"

class Player {
private:

public:
	Player();
	void Player_Update();
	void Player_Draw();

	int x, y;
	int move;
	int count;
	int image;
	static const int MaxImage = 11;

	//Ši”[
	int mPlayerImage[MaxImage];
};

extern Player mPlayer;