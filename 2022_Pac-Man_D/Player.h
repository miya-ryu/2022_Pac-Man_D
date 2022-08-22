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
	int recordX, recordY;	//êiÇﬂÇ»Ç≠Ç∑ÇÈ
	int top, right, bottom, left;	//ìñÇΩÇËîªíË
	int recordTop, recordRight, recordBottom, recordLeft;	//ìñÇΩÇ¡ÇΩÇÁêiÇﬂÇ»Ç≠Ç∑ÇÈ

	int move;
	int count;
	int image;
	static const int MaxImage = 11;
	int muki;
	//äiî[
	int mPlayerImage[MaxImage];


	
	
};

extern Player mPlayer;