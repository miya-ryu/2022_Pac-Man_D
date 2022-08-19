#pragma once
#include "DxLib.h"
#include "SceneMgr.h"

static int PLAYER_POS_X = 32;
static int PLAYER_POS_Y = 32;

class Player {
private:
	int move;

	static const int MaxImage = 11;

	//Ši”[
	int mPlayerImage[MaxImage];

public:
	int x, y;
	int recordX, recordY;
	int top, right, bottom, left;
	Player();
	void Player_Update();
	void Player_Draw();
};

extern Player mPlayer;