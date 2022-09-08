#include "DxLib.h"
#include "Stage.h"
#include "Player.h"
#include "Red_Enemy.h"
#include "Input.h"

Stage mStage;

//変数
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
	NUM_STAGE_IMAGE = 18;
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
				//Playerの当たり判定
				if (StageCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, mPlayer.s_left, mPlayer.s_top, mPlayer.s_right, mPlayer.s_bottom)) {


					if (mStageChip[no] == 17) {
						DrawString(950, 300, "当たっている", (255,255,255));
						DeleteGraph(mStageChip[17]);
					}

					//先行入力受け付け
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

						//ヒットを戻す
						mPlayer.P_StageHitflg = FALSE;
					}
				}

				//Enemyの当たり判定
				if (StageCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom)) {

					// ステージとの当たり判定フラグ
					r_enemy.E_StageHitflg = TRUE;
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
					if (r_enemy.absX > r_enemy.absY) { // 絶対値Xの値が大きいとき
						if (mPlayer.x >= r_enemy.x + 1) { // xの値がプレイヤーの方が大きいとき
							r_enemy.angle = 1; // 右向き
							r_enemy.E_StageHitflg = FALSE;

						}
						else if (mPlayer.x <= r_enemy.x - 1) { // xの値がエネミーの方が大きいとき
							r_enemy.angle = 3; // 左向き
						}
					}
					else if (r_enemy.absX < r_enemy.absY) { // 絶対値Yの値が大きいとき
						if (mPlayer.y >= r_enemy.y + 1) { // yの値がプレイヤーの方が大きいとき
							r_enemy.angle = 2; // 下向き
							if (r_enemy.E_StageHitflg == TRUE) {
								//r_enemy.angle = 1;
							}
							mPlayer.P_StageHitflg = FALSE;
						}
						else if (mPlayer.y <= r_enemy.y - 1) { // yの値がエネミーの方が大きいとき
							r_enemy.angle = 4; // 上向き
							if (r_enemy.E_StageHitflg == TRUE) {
								//r_enemy.angle = 1;
							}
							mPlayer.P_StageHitflg = FALSE;
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
			else if (mStageChip[i] == 0) {
				//前回の入力キーがあるかどうか
				if (mPlayer.iOldKeyflg == TRUE) {
					////右
					//if (mPlayer.iOldmove == 2) {
					//	if (mPlayer.s_top < i * SIZE_STAGE_Y + SIZE_STAGE_Y && mPlayer.s_bottom < i * SIZE_STAGE_Y) {
					//		mPlayer.iNowAngle = 2;
					//		mPlayer.iOldKeyflg = FALSE;
					//	}
					//}
					////下
					//if (mPlayer.iOldmove == 3) {
					//	if (mPlayer.s_)
					//}
					////左
					//if (mPlayer.) {

					//}
					////上
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
			DrawExtendGraph(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, i * SIZE_STAGE_X + SIZE_STAGE_X, j * SIZE_STAGE_Y + SIZE_STAGE_Y, mStageChip[no], FALSE);
		}
	}

	//スコア表示
	DrawGraph(870, 20, mStageUI[0], true);			//ハイスコア
	DrawGraph(930, 130, mStageUI[1], true);			//１up

	//ハイスコア数字表示   初期
	int hnumX = 950;
	for (int cont = 0; cont < 6; cont++) {
		DrawGraph(hnumX, 70, mStageNum[0], true);
		hnumX += 32;
	}

	//1up数字表示   初期
	int numX = 950;
	for (int cont = 0; cont < 6; cont++) {
		DrawGraph(numX, 180, mStageNum[0], true);
		numX += 32;
	}

	//パックマン残機表示
	int pacX = 920;
	int life = 2;
	if (mPlayer.Hitflg == TRUE) {
		life -= 1;
	}
	for (int num = 0; num < life; num++) {
		DrawRotaGraph(pacX, 550, 1.8, 0, mStagePacman[10], TRUE, FALSE);
		pacX += 60;
	}

	//フルーツ表示
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

//画像格納処理
void Stage::Stage_Storage() {
	//エサ
	mStageChip[17] = LoadGraph("images/tiles/dot.png");
	mStageChip[18] = LoadGraph("images/tiles/big_dot.png");
	// 二重カーブ
	mStageChip[1] = LoadGraph("images/tiles/outercorner_bottom_left.png");
	mStageChip[2] = LoadGraph("images/tiles/outercorner_bottom_right.png");
	mStageChip[3] = LoadGraph("images/tiles/outercorner_narrow_bottom_left.png");
	mStageChip[4] = LoadGraph("images/tiles/outercorner_narrow_bottom_right.png");
	mStageChip[5] = LoadGraph("images/tiles/outercorner_narrow_top_left.png");
	mStageChip[6] = LoadGraph("images/tiles/outercorner_narrow_top_right.png");
	mStageChip[7] = LoadGraph("images/tiles/outercorner_top_left.png");
	mStageChip[8] = LoadGraph("images/tiles/outercorner_top_right.png");
	// 二重ライン
	mStageChip[9] = LoadGraph("images/tiles/outerwall_bottom.png");
	mStageChip[10] = LoadGraph("images/tiles/outerwall_left.png");
	mStageChip[11] = LoadGraph("images/tiles/outerwall_right.png");
	mStageChip[12] = LoadGraph("images/tiles/outerwall_top.png");
	// ライン
	mStageChip[13] = LoadGraph("images/tiles/wall_bottom.png");
	mStageChip[14] = LoadGraph("images/tiles/wall_left.png");
	mStageChip[15] = LoadGraph("images/tiles/wall_right.png");
	mStageChip[16] = LoadGraph("images/tiles/wall_top.png");

	//スコア部分UI
	mStageUI[0] = LoadGraph("images/title/hi-score.png");	//ハイスコア文字
	mStageUI[1] = LoadGraph("images/title/1up.png");		//１up文字
	LoadDivGraph("images/title/num.png", 10, 10, 1, 32, 32, mStageNum);	//数字
	LoadDivGraph("images/pacman.png", 11, 11, 1, 32, 32, mStagePacman);	//パックマン
	LoadDivGraph("images/fruit.png", 13, 13, 1, 32, 32, mStageFruit);	//フルーツ
}