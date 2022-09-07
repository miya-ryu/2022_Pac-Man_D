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
	int recordX, recordY;	//進めなくする
	float s_top, s_right, s_bottom, s_left;	//Stage当たり判定
	int recordSTop, recordSRight, recordSBottom, recordSLeft;	//当たったら進めなくする
	int p_top, p_right, p_bottom, p_left;	//Player当たり判定
	int recordPtop, recordPright, recordPbottom, recordPleft;
	int iNowAngle, iOldAngle;
	bool AngleChange;
	bool Angleflg;
	bool iOldKeyflg;	//前回のキーフラグ
	int iOldmove;

	int move;
	int count;
	int image;
	//格納
	static const int MoveImage = 12;
	int mPlayerMoveImage[MoveImage];
	//敵に当たったフラグ
	bool Hitflg;
	//壁に当たったフラグ
	bool StageHitflg;
	//死んだとき
	static const int DeleteImage = 10;
	int deletecount;
	int deleteimage;
	int mPlayerDeleteImage[DeleteImage];
};

extern Player mPlayer;