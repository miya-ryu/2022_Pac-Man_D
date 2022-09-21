#pragma once
#include "DxLib.h"
#include "SceneMgr.h"

static int PLAYER_POS_X = 612;
static int PLAYER_POS_Y = 492;
static float PLAYER_POS_HITBOX = 11;
static int PLAYER_CENTER_HITBOX = 2;

class Player {
private:
	float size = 0.75;		//pac死んだときの画像サイズ変更
	bool Pac_s;				//pac死んだときの待機時間経過後フラグ管理
public:
	void Player_Initialize();
	void Player_Update();
	void Player_Draw();

	int x, y;
	int w, h;
	int recordX, recordY;	//進めなくする
	int s_top, s_right, s_bottom, s_left;	//Stage当たり判定
	int recordSTop, recordSRight, recordSBottom, recordSLeft;	//当たったら進めなくする
	int p_top, p_right, p_bottom, p_left;	//Player当たり判定
	int recordPtop, recordPright, recordPbottom, recordPleft;
	int iNowAngle, iOldAngle;

	int move;
	int count, timercount;
	int image;

	int pcount = 0;
	//格納
	static const int MoveImage = 12;
	int mPlayerMoveImage[MoveImage];
	//敵に当たったフラグ
	bool Hitflg;
	//壁に当たったフラグ
	bool P_StageHitflg;
	//分身処理
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

	//格納
	static const int DeleteImage = 11;
	int mPlayerDeleteImage[DeleteImage];
	//死んだとき
	int deletecount;
	int deleteimage;
	int millisecond;
	// 座標計算
	int xy, xy2, xx, yy;
	// プレイヤーの○画像
	int clearimage;
};

extern Player mPlayer;