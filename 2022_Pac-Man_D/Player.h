#pragma once
#include "DxLib.h"
#include "SceneMgr.h"

static int PLAYER_POS_X = 32 + 16;
static int PLAYER_POS_Y = 32 + 16;
static int PLAYER_POS_HITBOX = 15;

class Player {
private:

public:
	Player();
	void Player_Update();
	void Player_Draw();

	int x, y;
	int w, h;
	int recordX, recordY;	//進めなくする
	int top, right, bottom, left;	//当たり判定
	int recordTop, recordRight, recordBottom, recordLeft;	//当たったら進めなくする

	int move;
	int count;
	int image;
	static const int MaxImage = 11;
	int muki;
	//格納
	int mPlayerImage[MaxImage];


	
	
};

extern Player mPlayer;