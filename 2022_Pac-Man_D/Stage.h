#pragma once
#include "DxLib.h"
//ïœêî

class Stage {
private:
	int NUM_STAGE_X;
	int NUM_STAGE_Y;
	int NUM_STAGE_IMAGE;
	//int mStageChip[];
public:
	int SIZE_STAGE_X;
	int SIZE_STAGE_Y;
	void Stage_Initialize();
	void Stage_Update();
	void Stage_Draw();
	void Stage_Storage();
};

extern Stage mStage;