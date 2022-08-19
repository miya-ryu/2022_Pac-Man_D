#pragma once
#include "DxLib.h"
#include "SceneMgr.h"

static int PLAYER_POS_X = 32;
static int PLAYER_POS_Y = 32;

class Player {
private:

public:
	Player();
	void Player_Update();
	void Player_Draw();

	int x, y;
	int recordX, recordY;
	int top, right, bottom, left;

	int move;
	int count;
	int image;
	static const int MaxImage = 11;
	int muki;
	//Ši”[
	int mPlayerImage[MaxImage];
};

extern Player mPlayer;