#pragma once
#include "DxLib.h"
//変数
class Stage {
private:
	int NUM_STAGE_X;
	int NUM_STAGE_Y;
	int NUM_STAGE_IMAGE;
	int mStageNum[10];		//数字の画像配列
	int mStagePacman[11];	//パックマン画像配列
	int mStageFruit[13];	//フルーツ画像配列
	int UpCount = 0;		//1UP表示カウント
	int UpSize = 1;
public:
	bool StateFlg;
	bool MoveFlg;
	bool GameOverFlg;
	int TimeCount = 0;		//スタート表示のカウント
	float Startsize = 0.8;
	float Startsize1 = 0.8;
	int life = 2;			//パックマンライフ管理
	int mStageUI[5];		//ステージＵＩ画像配列
	int StartFlg = false;
	int SIZE_STAGE_X;
	int SIZE_STAGE_Y;
	int SIZE_ESA_X;
	int SIZE_ESA_Y;
	int esaNum = 0;
	void Stage_Initialize();
	void Stage_Update();
	void Stage_Draw();
	void Stage_Storage();
	// エサの数変数
	int num, numc;
	// ステージアニメーション
	int Scount = 0;
	bool Sflg = TRUE;
	bool Wflg;
};

extern Stage mStage;