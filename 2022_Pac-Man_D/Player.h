#pragma once
#include "DxLib.h"
#include "SceneMgr.h"

static int PLAYER_POS_X = 612;
static int PLAYER_POS_Y = 372;
static float PLAYER_POS_HITBOX = 11;
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
	float s_top, s_right, s_bottom, s_left;	//StageìñÇΩÇËîªíË
	int recordSTop, recordSRight, recordSBottom, recordSLeft;	//ìñÇΩÇ¡ÇΩÇÁêiÇﬂÇ»Ç≠Ç∑ÇÈ
	int p_top, p_right, p_bottom, p_left;	//PlayerìñÇΩÇËîªíË
	int recordPtop, recordPright, recordPbottom, recordPleft;

	int move;
	int count;
	int image;
	static const int MaxImage = 11;
	static const int maxImage = 11;
	int muki;
	//ìGÇ…ìñÇΩÇ¡ÇΩÉtÉâÉO
	bool Hitflg;
	//äiî[
	int mPlayerImage[MaxImage];


	
	
};

extern Player mPlayer;