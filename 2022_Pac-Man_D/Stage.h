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
	int TimeCount = 0;		//�X�^�[�g�\���̃J�E���g
	int UpCount = 0;		//1UP�\���J�E���g
	int UpSize = 1;
	float Startsize = 0.8;
	float Startsize1 = 0.8;
public:
	bool StateFlg;
	bool MoveFlg;
	bool GameOverFlg;
	int life = 2;			//�p�b�N�}�����C�t�Ǘ�
	int mStageUI[5];		//�X�e�[�W�t�h�摜�z��
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