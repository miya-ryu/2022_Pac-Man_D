#include "DxLib.h"
#include "Stage.h"
#include "Player.h"

Stage mStage;

//変数
static int mStageChip[1];
//StageMap格納
int stagedata[]{
	1,2,2,2,2,2,2,2,2,2,3,
	4,0,0,0,0,0,0,0,0,0,5,
	4,0,8,9,10,0,8,9,10,0,5,
	4,0,11,0,12,0,11,0,12,0,5,
	4,0,13,15,14,0,13,15,14,0,5,
	0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,2,0,0,0,0,
};
//当たり判定
int CheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	int L1 = x1;		//左
	int R1 = x1 + w1;	//右
	int L2 = x2;		//左
	int R2 = w2;	//右

	if (R1 < L2) return 0;
	if (R2 < L1) return 0;

	int U1 = y1;		//上
	int D1 = y1 + h1;	//下
	int U2 = y2;		//上
	int D2 = h2;	//下

	if (D1 < U2)return 0;
	if (D2 < U1)return 0;

	//当たっている
	return 1;
}

//初期化処理
Stage::Stage(){
	SIZE_STAGE_X = 32;
	SIZE_STAGE_Y = 32;
	NUM_STAGE_X = 11;
	NUM_STAGE_Y = 7;
	NUM_STAGE_IMAGE = 16;
	mStageChip[NUM_STAGE_IMAGE];
}

//更新処理
void Stage::Stage_Update() {
	//当たり判定
	for (int j = 0; j < NUM_STAGE_Y; j++) {
		for (int i = 0; i < NUM_STAGE_X; i++) {
			int no = stagedata[i + j * NUM_STAGE_X];

			if (mStageChip[no] != 0) {
				DrawBox(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, i * SIZE_STAGE_X + SIZE_STAGE_X, j * SIZE_STAGE_Y + SIZE_STAGE_Y, 0xffff00, FALSE);
				if (CheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, mPlayer.left, mPlayer.top, mPlayer.right, mPlayer.bottom)) {
					//移動
					mPlayer.x = mPlayer.recordX;
					mPlayer.y = mPlayer.recordY;

					//当たり判定移動
					mPlayer.top = mPlayer.recordTop;
					mPlayer.right = mPlayer.recordRight;
					mPlayer.bottom = mPlayer.recordBottom;
					mPlayer.left = mPlayer.recordLeft;
				}
			}
		}
	}
}

//描画処理
void Stage::Stage_Draw() {
	Stage::Stage_Storage();
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
	//mStageChip[0] = LoadGraph("images/pacman.png");
	//外周
	mStageChip[1] = LoadGraph("images/tiles/outercorner_narrow_top_left.png");
	mStageChip[2] = LoadGraph("images/tiles/outerwall_bottom.png");
	mStageChip[3] = LoadGraph("images/tiles/outernose_narrow_top_right.png");
	mStageChip[4] = LoadGraph("images/tiles/outerwall_right.png");
	mStageChip[5] = LoadGraph("images/tiles/outerwall_wall_left.png");
	mStageChip[6] = LoadGraph("images/tiles/outerwall_left.png");
	mStageChip[7] = LoadGraph("images/tiles/corner_bottom_left.png");

	//中身
	mStageChip[8] = LoadGraph("images/tiles/outercorner_top_left.png");
	mStageChip[9] = LoadGraph("images/tiles/outerwall_top.png");
	mStageChip[10] = LoadGraph("images/tiles/outercorner_top_right.png");
	mStageChip[11] = LoadGraph("images/tiles/outerwall_left.png");
	mStageChip[12] = LoadGraph("images/tiles/outerwall_right.png");
	mStageChip[13] = LoadGraph("images/tiles/outercorner_bottom_left.png");
	mStageChip[14] = LoadGraph("images/tiles/outercorner_bottom_right.png");
	mStageChip[15] = LoadGraph("images/tiles/outerwall_bottom.png");
	mStageChip[16] = LoadGraph("images/tiles/outercorner_narrow_bottom_right.png");
}