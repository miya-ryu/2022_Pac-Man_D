#pragma once
#include "DxLib.h"
//変数
class Stage {
private:
	int NUM_STAGE_X;
	int NUM_STAGE_Y;
	int NUM_STAGE_IMAGE;
	//int mStageChip[];
	//int mStageUI[5];
	int mStageNum[10];		//数字の画像配列
	int mStagePacman[11];	//パックマン画像配列
	int mStageFruit[13];	//フルーツ画像配列
	int TimeCount = 0;
	float Startsize = 0.8;
	float Startsize1 = 0.8;
public:
	int mStageUI[5];		//ステージＵＩ画像配列
	int StartFlg = false;
	int SIZE_STAGE_X;
	int SIZE_STAGE_Y;
	int SIZE_ESA_X;
	int SIZE_ESA_Y;
	void Stage_Initialize();
	void Stage_Update();
	void Stage_Draw();
	void Stage_Storage();
};

extern Stage mStage;