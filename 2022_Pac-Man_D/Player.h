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
	int recordX, recordY;	//êiÇﬂÇ»Ç≠Ç∑ÇÈ
	int s_top, s_right, s_bottom, s_left;	//StageìñÇΩÇËîªíË
	int p_top, p_right, p_bottom, p_left;	//PlayerìñÇΩÇËîªíË
	int recordSTop, recordSRight, recordSBottom, recordSLeft;	//ìñÇΩÇ¡ÇΩÇÁêiÇﬂÇ»Ç≠Ç∑ÇÈ
	int recordPX, recordPY;

	int move;
	int count;
	int image;
	static const int MaxImage = 11;
	int muki;
	//äiî[
	int mPlayerImage[MaxImage];


	
	
};

extern Player mPlayer;