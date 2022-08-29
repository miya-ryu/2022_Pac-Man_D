#pragma once
#include "DxLib.h"
#include "SceneMgr.h"

static int PLAYER_POS_X = 16 + 8;
static int PLAYER_POS_Y = 16 + 8;
static int PLAYER_POS_HITBOX = 7;
static int PLAYER_CENTER_HITBOX = 2;

class Player {
private:

public:
	void Player_Initialize();
	void Player_Update();
	void Player_Draw();

	int x, y;
	int w, h;
	int recordX, recordY;	//進めなくする
	int s_top, s_right, s_bottom, s_left;	//Stage当たり判定
	int p_top, p_right, p_bottom, p_left;	//Player当たり判定
	int recordSTop, recordSRight, recordSBottom, recordSLeft;	//当たったら進めなくする
	int recordPX, recordPY;

	int move;
	int count;
	int image;
	static const int MaxImage = 11;
	int muki;
	//格納
	int mPlayerImage[MaxImage];


	
	
};

extern Player mPlayer;