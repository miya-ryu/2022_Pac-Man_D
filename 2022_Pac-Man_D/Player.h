#pragma once
#include "DxLib.h"

class Player {
private:
	int move;
	int count;
	int image;
	static const int MaxImage = 11;

	//Ši”[
	int mPlayerImage[MaxImage];

public:
	Player();
	void Player_Update();
	void Player_Draw();
	int x, y;
	int w, h;
	
};

extern Player mPlayer;