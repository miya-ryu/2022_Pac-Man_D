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
	int recordX, recordY;	//�i�߂Ȃ�����
	float s_top, s_right, s_bottom, s_left;	//Stage�����蔻��
	int recordSTop, recordSRight, recordSBottom, recordSLeft;	//����������i�߂Ȃ�����
	int p_top, p_right, p_bottom, p_left;	//Player�����蔻��
	int recordPtop, recordPright, recordPbottom, recordPleft;

	int move;
	int count;
	int image;
	static const int MaxImage = 11;
	static const int maxImage = 11;
	int muki;
	//�G�ɓ��������t���O
	bool Hitflg;
	//�i�[
	int mPlayerImage[MaxImage];


	
	
};

extern Player mPlayer;