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
	int iNowAngle, iOldAngle;
	bool AngleChange;
	bool Angleflg;
	bool iOldKeyflg;	//�O��̃L�[�t���O
	int iOldmove;

	int move;
	int count;
	int image;
	//�i�[
	static const int MoveImage = 12;
	int mPlayerMoveImage[MoveImage];
	//�G�ɓ��������t���O
	bool Hitflg;
	//�ǂɓ��������t���O
	bool StageHitflg;
	//���񂾂Ƃ�
	static const int DeleteImage = 10;
	int deletecount;
	int deleteimage;
	int mPlayerDeleteImage[DeleteImage];
};

extern Player mPlayer;