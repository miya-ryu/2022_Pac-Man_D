#include "DxLib.h"
#include "Stage.h"
#include "Player.h"
#include "Red_Enemy.h"

Stage mStage;

//�ϐ�
static int mStageChip[1];

int stagedata[]{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,12,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 5, 5, 5, 5, 5, 5, 5, 5, 5,29, 5, 5, 5, 5, 5, 5, 5, 5, 5,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 5,11,23,12, 5,11,23,12, 5,29, 5,11,23,12, 5,11,23,12, 5,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 6,25, 0,24, 5,25, 0,24, 5,29, 5,25, 0,24, 5,25, 0,24, 6,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 5, 9,26,10, 5, 9,26,10, 5,29, 5, 9,26,10, 5,9, 26,10, 5,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 5,11,23,12, 5,29, 5,11,23,23,23,12, 5,28, 5,11,23,12, 5,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 5, 9,26,10, 5,29, 5, 9,26,26,26,10, 5,28, 5, 9,26,10, 5,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 5, 5, 5, 5, 5,29, 5, 5, 5,29, 5, 5, 5,28, 5, 5, 5, 5, 5,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  9,26,26,26,14, 5,29,30,30, 0,29, 0,30,30,28, 5,13,26,26,26,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0,25, 5,29, 0, 0, 0, 0, 0, 0, 0,28, 5,24, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0,25, 5,29, 0,11,23,23,23,12, 0,28, 5,24, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 23,23,23,23, 8, 5,29, 0,25, 0, 0, 0,24, 0,28, 5, 7,23,23,23,23,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0, 0, 5, 0, 0,25, 0, 0, 0,24, 0, 0, 5, 0, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 26,26,26,26,14, 5,29, 0, 9,26,26,26,10, 0,28, 5,13,26,26,26,26,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0,25, 5,29, 0, 0, 0, 0, 0, 0, 0,28, 5,24, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0,25, 5,29, 0,11,23,23,23,12, 0,28, 5,24, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,23,23,23, 8, 5,29, 0, 9,26,26,26,10, 0,28, 5, 7,23,23,23,12,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 5, 5, 5, 5, 5, 5, 5, 5, 5,29, 5, 5, 5, 5, 5, 5, 5, 5, 5,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 5,26,26,14, 5,27,27,27, 5,29, 5,27,27,27, 5,13,26,26, 5,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 6, 5, 5,25, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,24, 5, 5, 6,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25,26,14, 5,25, 5,29, 5,11,23,23,23,12, 5,28, 5,24, 5,13,26,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25,23, 8, 5,25, 5,29, 5, 9,26,26,26,10, 5,28, 5,24, 5, 7,23,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 5, 5, 5, 5, 5,29, 5, 5, 5,29, 5, 5, 5,28, 5, 5, 5, 5, 5,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 5,30,30,30,30,30,30,30, 5,29, 5,30,30,30,30,30,30,30, 5,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  9,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,10,
};

//�����蔻��
int StageCheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	int L1 = x1;		//��
	int R1 = x1 + w1;	//�E
	int L2 = x2;		//��
	int R2 = w2;		//�E

	if (R1 < L2) return 0;
	if (R2 < L1) return 0;

	int U1 = y1;		//��
	int D1 = y1 + h1;	//��
	int U2 = y2;		//��
	int D2 = h2;		//��

	if (D1 < U2) return 0;
	if (D2 < U1) return 0;

	//�������Ă���
	return 1;
}

//����������
void Stage::Stage_Initialize(){
	//�T�C�Y
	SIZE_STAGE_X = 24;
	SIZE_STAGE_Y = 24;

	//�`�搔
	NUM_STAGE_X = 36;
	NUM_STAGE_Y = 27;

	//�摜�i�[
	NUM_STAGE_IMAGE = 30;
	mStageChip[NUM_STAGE_IMAGE];
	Stage::Stage_Storage();
}

//�X�V����
void Stage::Stage_Update() {
	//�����蔻��
	for (int j = 0; j < NUM_STAGE_Y; j++) {
		for (int i = 0; i < NUM_STAGE_X; i++) {
			int no = stagedata[i + j * NUM_STAGE_X];

			if (mStageChip[no] != 0) {
				DrawBox(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, i * SIZE_STAGE_X + SIZE_STAGE_X, j * SIZE_STAGE_Y + SIZE_STAGE_Y, 0xffff00, FALSE);
				//Player�̓����蔻��
				if (StageCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, mPlayer.s_left, mPlayer.s_top, mPlayer.s_right, mPlayer.s_bottom)) {
					//�ړ�
					mPlayer.x = mPlayer.recordX;
					mPlayer.y = mPlayer.recordY;

					//�����蔻��ړ�
					mPlayer.p_top = mPlayer.recordPtop;
					mPlayer.p_right = mPlayer.recordPright;
					mPlayer.p_bottom = mPlayer.recordPbottom;
					mPlayer.p_left = mPlayer.recordPleft;

					mPlayer.s_top = mPlayer.recordSTop;
					mPlayer.s_right = mPlayer.recordSRight;
					mPlayer.s_bottom = mPlayer.recordSBottom;
					mPlayer.s_left = mPlayer.recordSLeft;
				}

				//Enemy�̓����蔻��
				if (StageCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom)) {
					r_enemy.absX = mPlayer.x - r_enemy.x;
					r_enemy.absY = mPlayer.y - r_enemy.y;

					r_enemy.x = r_enemy.recordX;
					r_enemy.y = r_enemy.recordY;
					
					r_enemy.right = r_enemy.recordRight;
					r_enemy.top = r_enemy.recordTop;
					r_enemy.left = r_enemy.recordLeft;
					r_enemy.bottom = r_enemy.recordBottom;

					//��Βl�̌v�Z
					if (r_enemy.absX < 0) {
						r_enemy.absX = r_enemy.absX * -1;
					}
					if (r_enemy.absY < 0) {
						r_enemy.absY = r_enemy.absY * -1;
					}
					
					

					//X�Ɉړ�
					if (r_enemy.absX > r_enemy.absY) {
						r_enemy.moveX = TRUE;
						r_enemy.moveY = FALSE;
					}
					//Y�Ɉړ�
					else if (r_enemy.absX < r_enemy.absY) {
						r_enemy.moveX = FALSE;
						r_enemy.moveY = TRUE;
					}
				}
			}
		}
	}
}

//�`�揈��
void Stage::Stage_Draw() {
	//�摜�T�C�Y�ύX
	for (int j = 0; j < NUM_STAGE_Y; j++) {
		for (int i = 0; i < NUM_STAGE_X; i++) {
			int no = stagedata[i + j * NUM_STAGE_X];
			DrawExtendGraph(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, i * SIZE_STAGE_X + SIZE_STAGE_X, j * SIZE_STAGE_Y + SIZE_STAGE_Y, mStageChip[no], FALSE);
		}
	}
}

//�摜�i�[����
void Stage::Stage_Storage() {
	//�G�T
	mStageChip[5] = LoadGraph("images/tiles/dot.png");
	mStageChip[6] = LoadGraph("images/tiles/big_dot.png");
	// ��d�J�[�u
	mStageChip[7]  = LoadGraph("images/tiles/outercorner_bottom_left.png");
	mStageChip[8]  = LoadGraph("images/tiles/outercorner_bottom_right.png");
	mStageChip[9]  = LoadGraph("images/tiles/outercorner_narrow_bottom_left.png");
	mStageChip[10] = LoadGraph("images/tiles/outercorner_narrow_bottom_right.png");
	mStageChip[11] = LoadGraph("images/tiles/outercorner_narrow_top_left.png");
	mStageChip[12] = LoadGraph("images/tiles/outercorner_narrow_top_right.png");
	mStageChip[13] = LoadGraph("images/tiles/outercorner_top_left.png");
	mStageChip[14] = LoadGraph("images/tiles/outercorner_top_right.png");
	// ��d���C��
	mStageChip[23] = LoadGraph("images/tiles/outerwall_bottom.png");
	mStageChip[24] = LoadGraph("images/tiles/outerwall_left.png");
	mStageChip[25] = LoadGraph("images/tiles/outerwall_right.png");
	mStageChip[26] = LoadGraph("images/tiles/outerwall_top.png");
	// ���C��
	mStageChip[27] = LoadGraph("images/tiles/wall_bottom.png");
	mStageChip[28] = LoadGraph("images/tiles/wall_left.png");
	mStageChip[29] = LoadGraph("images/tiles/wall_right.png");
	mStageChip[30] = LoadGraph("images/tiles/wall_top.png");
}