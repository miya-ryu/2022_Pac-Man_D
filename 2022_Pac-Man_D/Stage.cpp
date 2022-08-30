#include "DxLib.h"
#include "Stage.h"
#include "Player.h"

Stage mStage;

//変数
static int mStageChip[1];
//StageMap格納
//int stagedata[]{
//	1,2,2,2,2,2,2,2,2,2,3,
//	4,0,0,0,0,0,0,0,0,0,5,
//	4,0,8,9,10,0,8,9,10,0,5,
//	4,0,11,0,12,0,11,0,12,0,5,
//	4,0,13,15,14,0,13,15,14,0,5,
//	0,0,0,0,0,0,0,0,0,0,0,
//	0,0,0,0,0,0,2,0,0,0,0,
//};
int stagedata[]{
	11,23,23,23,23,23,23,23,23,23,29,23,23,23,23,23,23,23,23,23,12,
	25, 0, 0, 0, 0, 0, 0, 0, 0, 0,29, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,
	25, 0,11,23,12, 0,11,23,12, 0,29, 0,11,23,12, 0,11,23,12, 0,24,
	25, 0,25, 0,24, 0,25, 0,24, 0,29, 0,25, 0,24, 0,25, 0,24, 0,24,
	25, 0, 9,26,10, 0, 9,26,10, 0,29, 0, 9,26,10, 0,9, 26,10, 0,24,
	25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,
	25, 0,11,23,12, 0,29, 0,11,23,23,23,12, 0,28, 0,11,23,12, 0,24,
	25, 0, 9,26,10, 0,29, 0, 9,26,26,26,10, 0,28, 0, 9,26,10, 0,24,
	25, 0, 0, 0, 0, 0,29, 0, 0, 0,29, 0, 0, 0,28, 0, 0, 0, 0, 0,24,
	 9,26,26,26,14, 0,29,30,30, 0,29, 0,30,30,28, 0,13,26,26,26,10,
	 0, 0, 0, 0,25, 0,29, 0, 0, 0, 0, 0, 0, 0,28, 0,24, 0, 0, 0, 0,
	 0, 0, 0, 0,25, 0,29, 0,11,23,23,23,12, 0,28, 0,24, 0, 0, 0, 0,
	23,23,23,23, 8, 0,29, 0,25, 0, 0, 0,24, 0,28, 0, 7,23,23,23,23,
	 0, 0, 0, 0, 0, 0, 0, 0,25, 0, 0, 0,24, 0, 0, 0, 0, 0, 0, 0, 0,
	26,26,26,26,14, 0,29, 0, 9,26,26,26,10, 0,28, 0,13,26,26,26,26,
	 0, 0, 0, 0,25, 0,29, 0, 0, 0, 0, 0, 0, 0,28, 0,24, 0, 0, 0, 0,
	 0, 0, 0, 0,25, 0,29, 0,11,23,23,23,12, 0,28, 0,24, 0, 0, 0, 0,
	11,23,23,23, 8, 0,29, 0, 9,26,26,26,10, 0,28, 0, 7,23,23,23,12,
	25, 0, 0, 0, 0, 0, 0, 0, 0, 0,29, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,
	25, 0,26,26,14, 0,27,27,27, 0,29, 0,27,27,27, 0,13,26,26, 0,24,
	25, 0, 0, 0,25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24, 0, 0, 0,24,
	25,26,14, 0,25, 0,29, 0,11,23,23,23,12, 0,28, 0,24, 0,13,26,24,
	25,23, 8, 0,25, 0,29, 0, 9,26,26,26,10, 0,28, 0,24, 0, 7,23,24,
	25, 0, 0, 0, 0, 0,29, 0, 0, 0,29, 0, 0, 0,28, 0, 0, 0, 0, 0,24,
	25, 0,30,30,30,30,30,30,30, 0,29, 0,30,30,30,30,30,30,30, 0,24,
	25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,24,
	 9,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,10,
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
void Stage::Stage_Initialize(){
	//サイズ
	SIZE_STAGE_X = 24;
	SIZE_STAGE_Y = 24;

	//描画数
	NUM_STAGE_X = 21;
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
				if (StageCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, mPlayer.s_left, mPlayer.s_top, mPlayer.s_right, mPlayer.s_bottom)) {
					//移動
					mPlayer.x = mPlayer.recordX;
					mPlayer.y = mPlayer.recordY;

					//当たり判定移動
					//mPlayer.p_right = 
					mPlayer.s_top = mPlayer.recordSTop;
					mPlayer.s_right = mPlayer.recordSRight;
					mPlayer.s_bottom = mPlayer.recordSBottom;
					mPlayer.s_left = mPlayer.recordSLeft;
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
}

//画像格納処理
void Stage::Stage_Storage() {
	//mStageChip[0] = LoadGraph("images/pacman.png");
	// カーブ
	mStageChip[1]  = LoadGraph("images/tiles/corner_bottom_left.png");
	mStageChip[2]  = LoadGraph("images/tiles/corner_bottom_right.png");
	mStageChip[3]  = LoadGraph("images/tiles/corner_top_left.png");
	mStageChip[4]  = LoadGraph("images/tiles/corner_top_right.png");
	// 四角
	mStageChip[5]  = LoadGraph("images/tiles/gate_left.png");
	mStageChip[6]  = LoadGraph("images/tiles/gate_right.png");
	// 二重カーブ
	mStageChip[7]  = LoadGraph("images/tiles/outercorner_bottom_left.png");
	mStageChip[8]  = LoadGraph("images/tiles/outercorner_bottom_right.png");
	mStageChip[9]  = LoadGraph("images/tiles/outercorner_narrow_bottom_left.png");
	mStageChip[10] = LoadGraph("images/tiles/outercorner_narrow_bottom_right.png");
	mStageChip[11] = LoadGraph("images/tiles/outercorner_narrow_top_left.png");
	mStageChip[12] = LoadGraph("images/tiles/outercorner_narrow_top_right.png");
	mStageChip[13] = LoadGraph("images/tiles/outercorner_top_left.png");
	mStageChip[14] = LoadGraph("images/tiles/outercorner_top_right.png");
	// 分かれ道
	mStageChip[15] = LoadGraph("images/tiles/outernose_bottom_left.png");
	mStageChip[16] = LoadGraph("images/tiles/outernose_bottom_right.png");
	mStageChip[17] = LoadGraph("images/tiles/outernose_left_bottom.png");
	mStageChip[18] = LoadGraph("images/tiles/outernose_left_top.png");
	mStageChip[19] = LoadGraph("images/tiles/outernose_right_bottom.png");
	mStageChip[20] = LoadGraph("images/tiles/outernose_right_top.png");
	mStageChip[21] = LoadGraph("images/tiles/outernose_top_left.png");
	//mStageChip[22] = LoadGraph("images/tiles/outernose_top_right.png");
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