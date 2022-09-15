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
	int recordX, recordY;	//i‚ß‚È‚­‚·‚é
	int s_top, s_right, s_bottom, s_left;	//Stage“–‚½‚è”»’è
	int recordSTop, recordSRight, recordSBottom, recordSLeft;	//“–‚½‚Á‚½‚çi‚ß‚È‚­‚·‚é
	int p_top, p_right, p_bottom, p_left;	//Player“–‚½‚è”»’è
	int recordPtop, recordPright, recordPbottom, recordPleft;
	int iNowAngle, iOldAngle;

	int move;
	int count;
	int image;
	//Ši”[
	static const int MoveImage = 12;
	int mPlayerMoveImage[MoveImage];
	//“G‚É“–‚½‚Á‚½ƒtƒ‰ƒO
	bool Hitflg;
	//•Ç‚É“–‚½‚Á‚½ƒtƒ‰ƒO
	bool P_StageHitflg;
	//•ªgˆ—
	int PLAYER_AVATAR_POS_X[4];
	int PLAYER_AVATAR_POS_Y[4];
	int avatar_top[4];
	int avatar_right[4];
	int avatar_left[4];
	int avatar_bottom[4];
	int record_avatar_top[4];
	int record_avatar_right[4];
	int record_avatar_left[4];
	int record_avatar_bottom[4];
	bool Left, Right, Top, Bottom;
	int CheckNumber;

	//Ši”[
	static const int DeleteImage = 11;
	int mPlayerDeleteImage[DeleteImage];
	//€‚ñ‚¾‚Æ‚«
	int deletecount;
	int deleteimage;
};

extern Player mPlayer;