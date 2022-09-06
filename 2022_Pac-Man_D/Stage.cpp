#include "DxLib.h"
#include "Stage.h"
#include "Player.h"
#include "Red_Enemy.h"
#include "Input.h"

Stage mStage;

//変数
static int mStageChip[1];

int stagedata[]{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,12,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0,29, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 0,11,23,12, 0,11,23,12, 0,29, 0,11,23,12, 0,11,23,12, 0,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 0,25, 0,24, 0,25, 0,24, 0,29, 0,25, 0,24, 0,25, 0,24, 0,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 0, 9,26,10, 0, 9,26,10, 0,29, 0, 9,26,10, 0,9, 26,10, 0,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 0,11,23,12, 0,29, 0,11,23,23,23,12, 0,28, 0,11,23,12, 0,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 0, 9,26,10, 0,29, 0, 9,26,26,26,10, 0,28, 0, 9,26,10, 0,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 0, 0, 0, 0, 0,29, 0, 0, 0,29, 0, 0, 0,28, 0, 0, 0, 0, 0,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  9,26,26,26,14, 0,29,30,30, 0,29, 0,30,30,28, 0,13,26,26,26,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0,25, 0,29, 0, 0, 0, 0, 0, 0, 0,28, 0,24, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0,25, 0,29, 0,11,23,23,23,12, 0,28, 0,24, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 23,23,23,23, 8, 0,29, 0,25, 0, 0, 0,24, 0,28, 0, 7,23,23,23,23,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0, 0, 0, 0, 0,25, 0, 0, 0,24, 0, 0, 0, 0, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 26,26,26,26,14, 0,29, 0, 9,26,26,26,10, 0,28, 0,13,26,26,26,26,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0,25, 0,29, 0, 0, 0, 0, 0, 0, 0,28, 0,24, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0,25, 0,29, 0,11,23,23,23,12, 0,28, 0,24, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,23,23,23, 8, 0,29, 0, 9,26,26,26,10, 0,28, 0, 7,23,23,23,12,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0,29, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 0,26,26,14, 0,27,27,27, 0,29, 0,27,27,27, 0,13,26,26, 0,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 0, 0, 0,25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24, 0, 0, 0,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25,26,14, 0,25, 0,29, 0,11,23,23,23,12, 0,28, 0,24, 0,13,26,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25,23, 8, 0,25, 0,29, 0, 9,26,26,26,10, 0,28, 0,24, 0, 7,23,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 0, 0, 0, 0, 0,29, 0, 0, 0,29, 0, 0, 0,28, 0, 0, 0, 0, 0,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 0,30,30,30,30,30,30,30, 0,29, 0,30,30,30,30,30,30,30, 0,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  9,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,10,
};

//当たり判定
int StageCheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	int L1 = x1;		//左
	int R1 = x1 + w1;	//右
	int L2 = x2;		//左
	int R2 = w2;		//右

	if (R1 < L2) return 0;
	if (R2 < L1) return 0;

	int U1 = y1;		//上
	int D1 = y1 + h1;	//下
	int U2 = y2;		//上
	int D2 = h2;		//下

	if (D1 < U2) return 0;
	if (D2 < U1) return 0;

	//当たっている
	return 1;
}

//初期化処理
void Stage::Stage_Initialize() {
	//サイズ
	SIZE_STAGE_X = 24;
	SIZE_STAGE_Y = 24;

	//描画数
	NUM_STAGE_X = 36;
	NUM_STAGE_Y = 27;

	//画像格納
	NUM_STAGE_IMAGE = 30;
	mStageChip[NUM_STAGE_IMAGE];
	Stage::Stage_Storage();
}

//更新処理
void Stage::Stage_Update() {
	//当たり判定
	for (int j = 0; j < NUM_STAGE_Y; j++) {
		for (int i = 0; i < NUM_STAGE_X; i++) {
			int no = stagedata[i + j * NUM_STAGE_X];

			if (mStageChip[no] != 0) {
				DrawBox(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, i * SIZE_STAGE_X + SIZE_STAGE_X, j * SIZE_STAGE_Y + SIZE_STAGE_Y, 0xffff00, FALSE);
				////前回の入力キーがあるかどうか
				//if (mPlayer.iOldKeyflg == TRUE) {
				//	//右
				//	if (mPlayer.iOldmove == 2) {
				//		if (mPlayer.s_top < i * SIZE_STAGE_Y + SIZE_STAGE_Y  && mPlayer.s_bottom < i * SIZE_STAGE_Y) {
				//			mPlayer.iNowAngle = 2;
				//			mPlayer.iOldKeyflg = FALSE;
				//		}
				//	}
				//}

				//Playerの当たり判定
				if (StageCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, mPlayer.s_left, mPlayer.s_top, mPlayer.s_right, mPlayer.s_bottom)) {

					////先行入力受け付け
					//mPlayer.StageHitflg = TRUE;
					//if (mPlayer.StageHitflg == TRUE) {
					//	if (mPlayer.Angleflg == TRUE) {
					//		if (mPlayer.iOldAngle == 2) {
					//			mPlayer.iNowAngle = 2;
					//		}
					//		else if (mPlayer.iOldAngle == 3) {
					//			mPlayer.iNowAngle = 3;
					//		}
					//		else if (mPlayer.iOldAngle == 4) {
					//			mPlayer.iNowAngle = 4;
					//		}
					//		else if (mPlayer.iOldAngle == 1) {
					//			mPlayer.iNowAngle = 1;
					//		}
					//		mPlayer.Angleflg = FALSE;
					//	}
					//	else if (mPlayer.Angleflg == FALSE) {
					//		if (mPlayer.iOldAngle == mPlayer.iNowAngle) {
					//			mPlayer.iOldKeyflg = TRUE;
					//			if (iNowKey & PAD_INPUT_RIGHT) {
					//				mPlayer.iOldmove = 2;
					//			}
					//			else if (iNowKey & PAD_INPUT_DOWN) {
					//				mPlayer.iOldmove = 3;
					//			}
					//			else if (iNowKey & PAD_INPUT_LEFT) {
					//				mPlayer.iOldmove = 4;
					//			}
					//			else if (iNowKey & PAD_INPUT_UP) {
					//				mPlayer.iOldmove = 1;
					//			}

								//移動
								mPlayer.x = mPlayer.recordX;
								mPlayer.y = mPlayer.recordY;

								//当たり判定移動
								mPlayer.p_top = mPlayer.recordPtop;
								mPlayer.p_right = mPlayer.recordPright;
								mPlayer.p_bottom = mPlayer.recordPbottom;
								mPlayer.p_left = mPlayer.recordPleft;

								mPlayer.s_top = mPlayer.recordSTop;
								mPlayer.s_right = mPlayer.recordSRight;
								mPlayer.s_bottom = mPlayer.recordSBottom;
								mPlayer.s_left = mPlayer.recordSLeft;
							/*}
						}*/

						//ヒットを戻す
						mPlayer.StageHitflg = FALSE;
					//}
				}

				//Enemyの当たり判定
				if (StageCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom)) {
					//前回の座標移動
					r_enemy.absX = mPlayer.x - r_enemy.x;
					r_enemy.absY = mPlayer.y - r_enemy.y;
					//絶対値を求める
					if (r_enemy.absX <= 0) {
						r_enemy.absX = r_enemy.absX * -1;
					}
					if (r_enemy.absY <= 0) {
						r_enemy.absY = r_enemy.absY * -1;
					}

					//angle設定
					if (r_enemy.absX > r_enemy.absY) {
						if (mPlayer.x >= r_enemy.x + 1) {
							r_enemy.angle = 1;
						}
						else if (mPlayer.x <= r_enemy.x - 1) {
							r_enemy.angle = 3;
						}
					}
					else if (r_enemy.absX < r_enemy.absY) {
						if (mPlayer.y >= r_enemy.y + 1) {
							r_enemy.angle = 2;
						}
						else if (mPlayer.y <= r_enemy.y - 1) {
							r_enemy.angle = 4;
						}
					}

					//初期化
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
		}
	}
}

//描画処理
void Stage::Stage_Draw() {
	//画像サイズ変更
	for (int j = 0; j < NUM_STAGE_Y; j++) {
		for (int i = 0; i < NUM_STAGE_X; i++) {
			int no = stagedata[i + j * NUM_STAGE_X];
			//DrawExtendGraph(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, i * SIZE_STAGE_X + SIZE_STAGE_X, j * SIZE_STAGE_Y + SIZE_STAGE_Y, mStageChip[no], FALSE);
		}
	}
}

//画像格納処理
void Stage::Stage_Storage() {
	// 二重カーブ
	mStageChip[7] = LoadGraph("images/tiles/outercorner_bottom_left.png");
	mStageChip[8] = LoadGraph("images/tiles/outercorner_bottom_right.png");
	mStageChip[9] = LoadGraph("images/tiles/outercorner_narrow_bottom_left.png");
	mStageChip[10] = LoadGraph("images/tiles/outercorner_narrow_bottom_right.png");
	mStageChip[11] = LoadGraph("images/tiles/outercorner_narrow_top_left.png");
	mStageChip[12] = LoadGraph("images/tiles/outercorner_narrow_top_right.png");
	mStageChip[13] = LoadGraph("images/tiles/outercorner_top_left.png");
	mStageChip[14] = LoadGraph("images/tiles/outercorner_top_right.png");
	// 二重ライン
	mStageChip[23] = LoadGraph("images/tiles/outerwall_bottom.png");
	mStageChip[24] = LoadGraph("images/tiles/outerwall_left.png");
	mStageChip[25] = LoadGraph("images/tiles/outerwall_right.png");
	mStageChip[26] = LoadGraph("images/tiles/outerwall_top.png");
	// ライン
	mStageChip[27] = LoadGraph("images/tiles/wall_bottom.png");
	mStageChip[28] = LoadGraph("images/tiles/wall_left.png");
	mStageChip[29] = LoadGraph("images/tiles/wall_right.png");
	mStageChip[30] = LoadGraph("images/tiles/wall_top.png");
}