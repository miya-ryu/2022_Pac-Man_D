#pragma once
#include "DxLib.h"
//�ϐ�
class Stage {
private:
	int NUM_STAGE_X;
	int NUM_STAGE_Y;
	int NUM_STAGE_IMAGE;
	//int mStageChip[];
	//int mStageUI[5];
	int mStageNum[10];		//�����̉摜�z��
	int mStagePacman[11];	//�p�b�N�}���摜�z��
	int mStageFruit[13];	//�t���[�c�摜�z��
	int TimeCount = 0;
	float Startsize = 0.8;
	float Startsize1 = 0.8;
public:
	int mStageUI[5];		//�X�e�[�W�t�h�摜�z��
	int StartFlg = false;
	int SIZE_STAGE_X;
	int SIZE_STAGE_Y;
	void Stage_Initialize();
	void Stage_Update();
	void Stage_Draw();
	void Stage_Storage();
};

extern Stage mStage;