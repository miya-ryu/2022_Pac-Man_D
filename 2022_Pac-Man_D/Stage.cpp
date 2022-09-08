#include "DxLib.h"
#include "Stage.h"
#include "Player.h"
#include "Red_Enemy.h"
#include "Input.h"

Stage mStage;

//�ϐ�
static int mStageChip[1];

int stagedata[]{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 6,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17,17,17,17,17,17,17,17,17,15,17,17,17,17,17,17,17,17,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17, 5, 9, 6,17, 5, 9, 6,17,15,17, 5, 9, 6,17, 5, 9, 6,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,18,11, 0,10,17,11, 0,10,17,15,17,11, 0,10,17,11, 0,10,18,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17, 3,12, 4,17, 3,12, 4,17,15,17, 3,12, 4,17, 3,12, 4,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17, 5, 9, 6,17,15,17, 5, 9, 9, 9, 6,17,14,17, 5, 9, 6,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17, 3,12, 4,17,15,17, 3,12,12,12, 4,17,14,17, 3,12, 4,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17,17,17,17,17,15,17,17,17,15,17,17,17,14,17,17,17,17,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  3,12,12,12, 8,17,15,16,16, 0,15, 0,16,16,14,17, 7,12,12,12, 4,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0,11,17,15, 0, 0, 0, 0, 0, 0, 0,14,17,10, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0,11,17,15, 0, 5, 9, 9, 9, 6, 0,14,17,10, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  9, 9, 9, 9, 2,17,15, 0,11, 0, 0, 0,10, 0,14,17, 1, 9, 9, 9, 9,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0, 0,17, 0, 0,11, 0, 0, 0,10, 0, 0,17, 0, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 12,12,12,12, 8,17,15, 0, 3,12,12,12, 4, 0,14,17, 7,12,12,12,12,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0,11,17,15, 0, 0, 0, 0, 0, 0, 0,14,17,10, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0,11,17,15, 0, 5, 9, 9, 9, 6, 0,14,17,10, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  5, 9, 9, 9, 2,17,15, 0, 3,12,12,12, 4, 0,14,17, 1, 9, 9, 9, 6,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17,17,17,17,17,17,17,17,17,15,17,17,17,17,17,17,17,17,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17,12,12, 8,17,13,13,13,17,15,17,13,13,13,17, 7,12,12,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,18,17,17,11,17,17,17,17,17,17,17,17,17,17,17,10,17,17,18,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,12, 8,17,11,17,15,17, 5, 9, 9, 9, 6,17,14,17,10,17, 7,12,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11, 9, 2,17,11,17,15,17, 3,12,12,12, 4,17,14,17,10,17, 1, 9,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17,17,17,17,17,15,17,17,17,15,17,17,17,14,17,17,17,17,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17,16,16,16,16,16,16,16,17,15,17,16,16,16,16,16,16,16,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  3,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12, 4,
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
void Stage::Stage_Initialize() {
	//�T�C�Y
	SIZE_STAGE_X = 24;
	SIZE_STAGE_Y = 24;

	//�`�搔
	NUM_STAGE_X = 36;
	NUM_STAGE_Y = 27;

	//�摜�i�[
	NUM_STAGE_IMAGE = 18;
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


					if (mStageChip[no] == 17) {
						DrawString(950, 300, "�������Ă���", (255,255,255));
						DeleteGraph(mStageChip[17]);
					}

					//��s���͎󂯕t��
					mPlayer.P_StageHitflg = TRUE;
					if (mPlayer.P_StageHitflg == TRUE) {
						if (mPlayer.Angleflg == TRUE) {
							if (mPlayer.iOldAngle == 2) {
								mPlayer.iNowAngle = 2;
							}
							else if (mPlayer.iOldAngle == 3) {
								mPlayer.iNowAngle = 3;
							}
							else if (mPlayer.iOldAngle == 4) {
								mPlayer.iNowAngle = 4;
							}
							else if (mPlayer.iOldAngle == 1) {
								mPlayer.iNowAngle = 1;
							}
							mPlayer.Angleflg = FALSE;
						}
						else if (mPlayer.Angleflg == FALSE) {
							if (mPlayer.iOldAngle == mPlayer.iNowAngle) {
								mPlayer.iOldKeyflg = TRUE;
								if (iNowKey & PAD_INPUT_RIGHT) {
									mPlayer.iOldmove = 2;
								}
								else if (iNowKey & PAD_INPUT_DOWN) {
									mPlayer.iOldmove = 3;
								}
								else if (iNowKey & PAD_INPUT_LEFT) {
									mPlayer.iOldmove = 4;
								}
								else if (iNowKey & PAD_INPUT_UP) {
									mPlayer.iOldmove = 1;
								}
							}
						}

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

						//�q�b�g��߂�
						mPlayer.P_StageHitflg = FALSE;
					}
				}

				//Enemy�̓����蔻��
				if (StageCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom)) {

					// �X�e�[�W�Ƃ̓����蔻��t���O
					r_enemy.E_StageHitflg = TRUE;
					//�O��̍��W�ړ�
					r_enemy.absX = mPlayer.x - r_enemy.x;
					r_enemy.absY = mPlayer.y - r_enemy.y;
					//��Βl�����߂�
					if (r_enemy.absX <= 0) {
						r_enemy.absX = r_enemy.absX * -1;
					}
					if (r_enemy.absY <= 0) {
						r_enemy.absY = r_enemy.absY * -1;
					}

					//angle�ݒ�
					if (r_enemy.absX > r_enemy.absY) { // ��ΒlX�̒l���傫���Ƃ�
						if (mPlayer.x >= r_enemy.x + 1) { // x�̒l���v���C���[�̕����傫���Ƃ�
							r_enemy.angle = 1; // �E����
							r_enemy.E_StageHitflg = FALSE;

						}
						else if (mPlayer.x <= r_enemy.x - 1) { // x�̒l���G�l�~�[�̕����傫���Ƃ�
							r_enemy.angle = 3; // ������
						}
					}
					else if (r_enemy.absX < r_enemy.absY) { // ��ΒlY�̒l���傫���Ƃ�
						if (mPlayer.y >= r_enemy.y + 1) { // y�̒l���v���C���[�̕����傫���Ƃ�
							r_enemy.angle = 2; // ������
							if (r_enemy.E_StageHitflg == TRUE) {
								//r_enemy.angle = 1;
							}
							mPlayer.P_StageHitflg = FALSE;
						}
						else if (mPlayer.y <= r_enemy.y - 1) { // y�̒l���G�l�~�[�̕����傫���Ƃ�
							r_enemy.angle = 4; // �����
							if (r_enemy.E_StageHitflg == TRUE) {
								//r_enemy.angle = 1;
							}
							mPlayer.P_StageHitflg = FALSE;
						}
					}

					//������
					if (r_enemy.angle == 5) {
						r_enemy.angle = 1;
					}

					r_enemy.x = r_enemy.recordX;
					r_enemy.y = r_enemy.recordY;

					r_enemy.right = r_enemy.recordRight;
					r_enemy.top = r_enemy.recordTop;
					r_enemy.left = r_enemy.recordLeft;
					r_enemy.bottom = r_enemy.recordBottom;
				}
			}
			else if (mStageChip[i] == 0) {
				//�O��̓��̓L�[�����邩�ǂ���
				if (mPlayer.iOldKeyflg == TRUE) {
					////�E
					//if (mPlayer.iOldmove == 2) {
					//	if (mPlayer.s_top < i * SIZE_STAGE_Y + SIZE_STAGE_Y && mPlayer.s_bottom < i * SIZE_STAGE_Y) {
					//		mPlayer.iNowAngle = 2;
					//		mPlayer.iOldKeyflg = FALSE;
					//	}
					//}
					////��
					//if (mPlayer.iOldmove == 3) {
					//	if (mPlayer.s_)
					//}
					////��
					//if (mPlayer.) {

					//}
					////��
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

	//�X�R�A�\��
	DrawGraph(870, 20, mStageUI[0], true);			//�n�C�X�R�A
	DrawGraph(930, 130, mStageUI[1], true);			//�Pup

	//�n�C�X�R�A�����\��   ����
	int hnumX = 950;
	for (int cont = 0; cont < 6; cont++) {
		DrawGraph(hnumX, 70, mStageNum[0], true);
		hnumX += 32;
	}

	//1up�����\��   ����
	int numX = 950;
	for (int cont = 0; cont < 6; cont++) {
		DrawGraph(numX, 180, mStageNum[0], true);
		numX += 32;
	}

	//�p�b�N�}���c�@�\��
	int pacX = 920;
	int life = 2;
	if (mPlayer.Hitflg == TRUE) {
		life -= 1;
	}
	for (int num = 0; num < life; num++) {
		DrawRotaGraph(pacX, 550, 1.8, 0, mStagePacman[10], TRUE, FALSE);
		pacX += 60;
	}

	//�t���[�c�\��
	int mFruitNum = 0;
	int FruitX = 900;
	int FruitX_2 = 900;

	for (int num = 0; num == 0; num++) {
		for (int y = 0; y < 4; y++) {
			DrawRotaGraph(FruitX, 390, 1.3, 0, mStageFruit[mFruitNum], true, false);
			FruitX += 40;
			mFruitNum += 1;
		}
		for (int y = 0; y < 4; y++) {
			DrawRotaGraph(FruitX_2, 420, 1.3, 0, mStageFruit[mFruitNum], true, false);
			FruitX_2 += 40;
			mFruitNum += 1;
		}
	}

	/*for (int num = 0; num < 13; num++) {
		if (mFruitNum == 0) {
			DrawRotaGraph(FruitX, 390, 1.3, 0, mStageFruit[mFruitNum], true, false);
			FruitX += 40;
		}
		if (mFruitNum % 2 != 0) {
			DrawRotaGraph(FruitX, 390, 1.3, 0, mStageFruit[mFruitNum], true, false);
			FruitX += 40;
		}
		if (mFruitNum == 12) {
			DrawRotaGraph(FruitX, 390, 1.3, 0, mStageFruit[mFruitNum], true, false);
		}
		mFruitNum += 1;
	}*/
}

//�摜�i�[����
void Stage::Stage_Storage() {
	//�G�T
	mStageChip[17] = LoadGraph("images/tiles/dot.png");
	mStageChip[18] = LoadGraph("images/tiles/big_dot.png");
	// ��d�J�[�u
	mStageChip[1] = LoadGraph("images/tiles/outercorner_bottom_left.png");
	mStageChip[2] = LoadGraph("images/tiles/outercorner_bottom_right.png");
	mStageChip[3] = LoadGraph("images/tiles/outercorner_narrow_bottom_left.png");
	mStageChip[4] = LoadGraph("images/tiles/outercorner_narrow_bottom_right.png");
	mStageChip[5] = LoadGraph("images/tiles/outercorner_narrow_top_left.png");
	mStageChip[6] = LoadGraph("images/tiles/outercorner_narrow_top_right.png");
	mStageChip[7] = LoadGraph("images/tiles/outercorner_top_left.png");
	mStageChip[8] = LoadGraph("images/tiles/outercorner_top_right.png");
	// ��d���C��
	mStageChip[9] = LoadGraph("images/tiles/outerwall_bottom.png");
	mStageChip[10] = LoadGraph("images/tiles/outerwall_left.png");
	mStageChip[11] = LoadGraph("images/tiles/outerwall_right.png");
	mStageChip[12] = LoadGraph("images/tiles/outerwall_top.png");
	// ���C��
	mStageChip[13] = LoadGraph("images/tiles/wall_bottom.png");
	mStageChip[14] = LoadGraph("images/tiles/wall_left.png");
	mStageChip[15] = LoadGraph("images/tiles/wall_right.png");
	mStageChip[16] = LoadGraph("images/tiles/wall_top.png");

	//�X�R�A����UI
	mStageUI[0] = LoadGraph("images/title/hi-score.png");	//�n�C�X�R�A����
	mStageUI[1] = LoadGraph("images/title/1up.png");		//�Pup����
	LoadDivGraph("images/title/num.png", 10, 10, 1, 32, 32, mStageNum);	//����
	LoadDivGraph("images/pacman.png", 11, 11, 1, 32, 32, mStagePacman);	//�p�b�N�}��
	LoadDivGraph("images/fruit.png", 13, 13, 1, 32, 32, mStageFruit);	//�t���[�c
}