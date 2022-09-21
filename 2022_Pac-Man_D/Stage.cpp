#include "DxLib.h"
#include "Stage.h"
#include "Player.h"
#include "Red_Enemy.h"
#include "Pink_Enemy.h"
#include "Blue_Enemy.h"
#include "Orange_Enemy.h"
#include "Input.h"
#include "sound.h"
#include "SceneMgr.h"

Stage mStage;

//変数
static int mStageChip[1];

int stagedata[]{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 6,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17,17,17,17,17,17,17,17,17,38,17,17,17,17,17,17,17,17,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17, 5, 9, 6,17, 5, 9, 6,17,38,17, 5, 9, 6,17, 5, 9, 6,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,18,11, 0,10,17,11, 0,10,17,38,17,11, 0,10,17,11, 0,10,18,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17, 3,12, 4,17, 3,12, 4,17,14,17, 3,12, 4,17, 3,12, 4,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17, 5, 9, 6,17,13,17, 5, 9, 9, 9, 6,17,13,17, 5, 9, 6,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17, 3,12, 4,17,38,17, 3,12,38,12, 4,17,38,17, 3,12, 4,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17,17,17,17,17,38,17,17,17,38,17,17,17,38,17,17,17,17,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  3,12,12,12, 8,17,38,39,16, 0,14, 0,15,39,38,17, 7,12,12,12, 4,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0,11,17,38, 0, 0, 0, 0, 0, 0, 0,38,17,10, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0,11,17,38, 0, 5, 9,19, 9, 6, 0,38,17,10, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  9, 9, 9, 9, 2,17,14, 0,11, 0, 0, 0,10, 0,14,17, 1, 9, 9, 9, 9,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0, 0,17, 0, 0,11, 0, 0, 0,10, 0, 0,17, 0, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 12,12,12,12, 8,17,13, 0, 3,12,12,12, 4, 0,13,17, 7,12,12,12,12,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0,11,17,38, 0, 0, 0, 0, 0, 0, 0,38,17,10, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0, 0, 0, 0,11,17,38, 0, 5, 9, 9, 9, 6, 0,38,17,10, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  5, 9, 9, 9, 2,17,14, 0, 3,12,38,12, 4, 0,14,17, 1, 9, 9, 9, 6,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17,17,17,17,17,17,17,17,17,38,17,17,17,17,17,17,17,17,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17,12,12, 8,17,15,39,16,17,14,17,15,39,16,17, 7,12,12,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,18,17,17,11,17,17,17,17,17, 0,17,17,17,17,17,10,17,17,18,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,12, 8,17,11,17,13,17, 5, 9, 9, 9, 6,17,13,17,10,17, 7,12,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11, 9, 2,17,11,17,38,17, 3,12,38,12, 4,17,38,17,10,17, 1, 9,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17,17,17,17,17,38,17,17,17,38,17,17,17,38,17,17,17,17,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17,15,39,39,39,39,39,16,17,14,17,15,39,39,39,39,39,16,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 11,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,10,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  3,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12, 4,
};

//当たり判定(ステージとのPlayer&Enemy)
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

// 分身の当たり判定
int AisleCheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	int L1 = x1;		//Stage左
	int R1 = x1 + w1;	//Stage右
	int L2 = x2;		//Player左
	int R2 = w2;		//Player右
	int U1 = y1;		//Stage上
	int D1 = y1 + h1;	//Stage下
	int U2 = y2;		//Player上
	int D2 = h2;		//Player下

	if (L1 < L2 && R1 > R2 && D1 > D2 && U1 < U2)return 1;	//箱内に収まっていたらぶつかっている
	else return 0;
}

//初期化処理
void Stage::Stage_Initialize() {
	//サイズ
	SIZE_STAGE_X = 24;
	SIZE_STAGE_Y = 24;

	//エサ
	SIZE_ESA_X = 12;
	SIZE_ESA_Y = 12;

	//描画数
	NUM_STAGE_X = 36;
	NUM_STAGE_Y = 27;

	//画像格納
	NUM_STAGE_IMAGE = 39;
	mStageChip[NUM_STAGE_IMAGE];
	Stage::Stage_Storage();
	//エサの数
	mStage.num = 0, mStage.numc = 0;
	//ステージアニメーション
	mStage.Scount = 0;
	//ゲームオーバーフラグ
	mStage.GameOverFlg = FALSE;
	mStage.StateFlg = FALSE;
	mStage.MoveFlg = FALSE;		//パックマンと敵の移動可能になる
}

//更新処理
void Stage::Stage_Update() {
	//当たり判定
	for (int j = 0; j < NUM_STAGE_Y; j++) {
		for (int i = 0; i < NUM_STAGE_X; i++) {
			int no = stagedata[i + j * NUM_STAGE_X];
			//壁に当たったときの処理
			if (no != 0) {
				//DrawBox(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, i * SIZE_STAGE_X + SIZE_STAGE_X, j * SIZE_STAGE_Y + SIZE_STAGE_Y, 0xffff00, FALSE);
				//分身体の当たり判定
				//分身の処理
				if (mPlayer.x % mPlayer.CheckNumber == 0 && mPlayer.y % mPlayer.CheckNumber == 0) {
					for (int avatar = 0; avatar < 4; avatar++) {
						if (StageCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, mPlayer.avatar_left[avatar], mPlayer.avatar_top[avatar], mPlayer.avatar_right[avatar], mPlayer.avatar_bottom[avatar])) {
							//当たっていたら進めなくする
							if (avatar == 0)mPlayer.Top = TRUE;
							if (avatar == 1)mPlayer.Right = TRUE;
							if (avatar == 2)mPlayer.Bottom = TRUE;
							if (avatar == 3)mPlayer.Left = TRUE;
						}
					}
				}
				// エネミーの分身の処理 赤エネミー
				//if (r_enemy.x % r_enemy.CheckNumber == 0 && r_enemy.y % r_enemy.CheckNumber == 0) {
					for (int e_avatar = 0; e_avatar < 4; e_avatar++) {
						if (AisleCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, r_enemy.avatar_left[e_avatar], r_enemy.avatar_top[e_avatar], r_enemy.avatar_right[e_avatar], r_enemy.avatar_bottom[e_avatar])) {
							//当たっていたら進めなくする
							if (e_avatar == 0)r_enemy.Top = TRUE;
							if (e_avatar == 1)r_enemy.Right = TRUE;
							if (e_avatar == 2)r_enemy.Bottom = TRUE;
							if (e_avatar == 3)r_enemy.Left = TRUE;
						}
					}
				//}
				// 
				// エネミーの分身の処理 ピンクエネミー
				//if (r_enemy.x % r_enemy.CheckNumber == 0 && r_enemy.y % r_enemy.CheckNumber == 0) {
					for (int e_avatar = 0; e_avatar < 4; e_avatar++) {
						if (AisleCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, p_enemy.avatar_left[e_avatar], p_enemy.avatar_top[e_avatar], p_enemy.avatar_right[e_avatar], p_enemy.avatar_bottom[e_avatar])) {
							//当たっていたら進めなくする
							if (e_avatar == 0)p_enemy.Top = TRUE;
							if (e_avatar == 1)p_enemy.Right = TRUE;
							if (e_avatar == 2)p_enemy.Bottom = TRUE;
							if (e_avatar == 3)p_enemy.Left = TRUE;
						}
					}
				//}
				// エネミーの分身の処理 青エネミー
				//if (r_enemy.x % r_enemy.CheckNumber == 0 && r_enemy.y % r_enemy.CheckNumber == 0) {
					for (int e_avatar = 0; e_avatar < 4; e_avatar++) {
						if (AisleCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, b_enemy.avatar_left[e_avatar], b_enemy.avatar_top[e_avatar], b_enemy.avatar_right[e_avatar], b_enemy.avatar_bottom[e_avatar])) {
							//当たっていたら進めなくする
							if (e_avatar == 0)b_enemy.Top = TRUE;
							if (e_avatar == 1)b_enemy.Right = TRUE;
							if (e_avatar == 2)b_enemy.Bottom = TRUE;
							if (e_avatar == 3)b_enemy.Left = TRUE;
						}
					}
				//}
				// エネミーの分身の処理 オレンジエネミー
				//if (r_enemy.x % r_enemy.CheckNumber == 0 && r_enemy.y % r_enemy.CheckNumber == 0) {
					for (int e_avatar = 0; e_avatar < 4; e_avatar++) {
						if (AisleCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, o_enemy.avatar_left[e_avatar], o_enemy.avatar_top[e_avatar], o_enemy.avatar_right[e_avatar], o_enemy.avatar_bottom[e_avatar])) {
							//当たっていたら進めなくする
							if (e_avatar == 0)o_enemy.Top = TRUE;
							if (e_avatar == 1)o_enemy.Right = TRUE;
							if (e_avatar == 2)o_enemy.Bottom = TRUE;
							if (e_avatar == 3)o_enemy.Left = TRUE;
						}
					}
				//}

				//Playerの当たり判定
				if (StageCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, mPlayer.s_left, mPlayer.s_top, mPlayer.s_right, mPlayer.s_bottom)) {
					// エサを食べる処理
					if (stagedata[i + j * NUM_STAGE_X] == 17) {
						stagedata[i + j * NUM_STAGE_X] = 0;
						numc += num + 1; // エサの数を数える
						mSound.numSound = 3;
						mSound.SoundStart();			//エサ食べるときSE再生
					}
					else {
						StopSoundMem(mSound.bgm[3]);
					}
					//いじけSE
					if (stagedata[i + j * NUM_STAGE_X] == 18) {
						stagedata[i + j * NUM_STAGE_X] = 0;
						r_enemy.R_Hitflg = TRUE;
						p_enemy.R_Hitflg = TRUE;
						b_enemy.R_Hitflg = TRUE;
						o_enemy.R_Hitflg = TRUE;
						numc += num + 1; // エサの数を数える
						/*StopSoundMem(mSound.bgm[5]);
						mSound.numSound =11;
						mSound.SoundStart();*/
					}
					else {
						/*StopSoundMem(mSound.bgm[11]);
						mSound.numSound = 5;
						mSound.SoundStart();*/
					}

					//先行入力受け付け
					mPlayer.P_StageHitflg = TRUE;
					if (mPlayer.P_StageHitflg == TRUE) {

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

						//分身
						for (int i = 0; i < 4; i++) {
							mPlayer.avatar_bottom[i] = mPlayer.record_avatar_bottom[i];
							mPlayer.avatar_left[i] = mPlayer.record_avatar_left[i];
							mPlayer.avatar_top[i] = mPlayer.record_avatar_top[i];
							mPlayer.avatar_right[i] = mPlayer.record_avatar_right[i];
						}

						//当たり判定を戻す
						mPlayer.P_StageHitflg = FALSE;
					}
				}
				if (no != 17 && no != 18) {
					// ステージとエネミーの当たり判定 赤エネミー
					if (StageCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom)) {
						//分身
						for (int i = 0; i < 4; i++) {
							r_enemy.avatar_bottom[i] = r_enemy.record_avatar_bottom[i];
							r_enemy.avatar_left[i] = r_enemy.record_avatar_left[i];
							r_enemy.avatar_top[i] = r_enemy.record_avatar_top[i];
							r_enemy.avatar_right[i] = r_enemy.record_avatar_right[i];
						}

						// 壁へのめり込みを防ぐ
						r_enemy.x = r_enemy.recordX;
						r_enemy.y = r_enemy.recordY;

						r_enemy.right = r_enemy.recordRight;
						r_enemy.top = r_enemy.recordTop;
						r_enemy.left = r_enemy.recordLeft;
						r_enemy.bottom = r_enemy.recordBottom;
					}
					// ピンクエネミー
					if (StageCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, p_enemy.left, p_enemy.top, p_enemy.right, p_enemy.bottom)) {
						//分身
						for (int i = 0; i < 4; i++) {
							p_enemy.avatar_bottom[i] = p_enemy.record_avatar_bottom[i];
							p_enemy.avatar_left[i] = p_enemy.record_avatar_left[i];
							p_enemy.avatar_top[i] = p_enemy.record_avatar_top[i];
							p_enemy.avatar_right[i] = p_enemy.record_avatar_right[i];
						}

						// 壁へのめり込みを防ぐ
						p_enemy.x = p_enemy.recordX;
						p_enemy.y = p_enemy.recordY;

						p_enemy.right = p_enemy.recordRight;
						p_enemy.top = p_enemy.recordTop;
						p_enemy.left = p_enemy.recordLeft;
						p_enemy.bottom = p_enemy.recordBottom;
					}
					// 青エネミー
					if (StageCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, b_enemy.left, b_enemy.top, b_enemy.right, b_enemy.bottom)) {
						//分身
						for (int i = 0; i < 4; i++) {
							b_enemy.avatar_bottom[i] = b_enemy.record_avatar_bottom[i];
							b_enemy.avatar_left[i] = b_enemy.record_avatar_left[i];
							b_enemy.avatar_top[i] = b_enemy.record_avatar_top[i];
							b_enemy.avatar_right[i] = b_enemy.record_avatar_right[i];
						}

						// 壁へのめり込みを防ぐ
						b_enemy.x = b_enemy.recordX;
						b_enemy.y = b_enemy.recordY;

						b_enemy.right = b_enemy.recordRight;
						b_enemy.top = b_enemy.recordTop;
						b_enemy.left = b_enemy.recordLeft;
						b_enemy.bottom = b_enemy.recordBottom;
					}
					// オレンジエネミー
					if (StageCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, o_enemy.left, o_enemy.top, o_enemy.right, o_enemy.bottom)) {
						//分身
						for (int i = 0; i < 4; i++) {
							o_enemy.avatar_bottom[i] = o_enemy.record_avatar_bottom[i];
							o_enemy.avatar_left[i] = o_enemy.record_avatar_left[i];
							o_enemy.avatar_top[i] = o_enemy.record_avatar_top[i];
							o_enemy.avatar_right[i] = o_enemy.record_avatar_right[i];
						}

						// 壁へのめり込みを防ぐ
						o_enemy.x = o_enemy.recordX;
						o_enemy.y = o_enemy.recordY;

						o_enemy.right = o_enemy.recordRight;
						o_enemy.top = o_enemy.recordTop;
						o_enemy.left = o_enemy.recordLeft;
						o_enemy.bottom = o_enemy.recordBottom;
					}
				}
			}

			//通路の処理
			if (no == 0 || no == 17 || no == 18) {
				//分身の処理 プレイヤー
				for (int avatar = 0; avatar < 4; avatar++) {
					if (AisleCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, mPlayer.avatar_left[avatar], mPlayer.avatar_top[avatar], mPlayer.avatar_right[avatar], mPlayer.avatar_bottom[avatar])) {
						//当たっていたら進める
						if (avatar == 0)mPlayer.Top = FALSE;
						if (avatar == 1)mPlayer.Right = FALSE;
						if (avatar == 2)mPlayer.Bottom = FALSE;
						if (avatar == 3)mPlayer.Left = FALSE;
					}
				}
				//エネミーの分身の処理
				for (int e_avatar = 0; e_avatar < 4; e_avatar++) {
					// 赤エネミー
					if (AisleCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, r_enemy.avatar_left[e_avatar], r_enemy.avatar_top[e_avatar], r_enemy.avatar_right[e_avatar], r_enemy.avatar_bottom[e_avatar])) {
						//当たっていたら進める
						if (e_avatar == 0)r_enemy.Top = FALSE;
						if (e_avatar == 1)r_enemy.Right = FALSE;
						if (e_avatar == 2)r_enemy.Bottom = FALSE;
						if (e_avatar == 3)r_enemy.Left = FALSE;
					}
					// ピンクエネミー
					if (AisleCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, p_enemy.avatar_left[e_avatar], p_enemy.avatar_top[e_avatar], p_enemy.avatar_right[e_avatar], p_enemy.avatar_bottom[e_avatar])) {
						//当たっていたら進める
						if (e_avatar == 0)p_enemy.Top = FALSE;
						if (e_avatar == 1)p_enemy.Right = FALSE;
						if (e_avatar == 2)p_enemy.Bottom = FALSE;
						if (e_avatar == 3)p_enemy.Left = FALSE;
					}
					// 青エネミー
					if (AisleCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, b_enemy.avatar_left[e_avatar], b_enemy.avatar_top[e_avatar], b_enemy.avatar_right[e_avatar], b_enemy.avatar_bottom[e_avatar])) {
						//当たっていたら進める
						if (e_avatar == 0)b_enemy.Top = FALSE;
						if (e_avatar == 1)b_enemy.Right = FALSE;
						if (e_avatar == 2)b_enemy.Bottom = FALSE;
						if (e_avatar == 3)b_enemy.Left = FALSE;
					}
					// オレンジエネミー
					if (AisleCheckHit(i * SIZE_STAGE_X, j * SIZE_STAGE_Y, SIZE_STAGE_X, SIZE_STAGE_Y, o_enemy.avatar_left[e_avatar], o_enemy.avatar_top[e_avatar], o_enemy.avatar_right[e_avatar], o_enemy.avatar_bottom[e_avatar])) {
						//当たっていたら進める
						if (e_avatar == 0)o_enemy.Top = FALSE;
						if (e_avatar == 1)o_enemy.Right = FALSE;
						if (e_avatar == 2)o_enemy.Bottom = FALSE;
						if (e_avatar == 3)o_enemy.Left = FALSE;
					}
				}
			}
		}
	}
	//スタート文字削除
	mStage.TimeCount++;	
	if (GameOverFlg == FALSE) {
		if (mStage.TimeCount == 140) {//2.5秒後
			mStage.Startsize = 0;      //Player文字消す
		}
		if (mStage.TimeCount == 160) {
			mStage.StateFlg = TRUE;	//パックマンと敵の表示
		}
		if (mStage.TimeCount == 250) {	//4.5秒後
			mStage.Startsize1 = 0;		//Start文字消す
			mStage.MoveFlg = TRUE;		//パックマンと敵の移動可能になる
		}
		else if (mStage.TimeCount == 251) {	//パックマン画像固定解除
			mStage.StateFlg = FALSE;
		}
	}
	else {
		Startsize = 0;
		Startsize1 = 0;
	}

	//1UPの点滅表示
	mStage.UpCount++;
	if (mStage.UpCount == 15) {
		mStage.UpSize = 0;
	}
	else if (mStage.UpCount == 30) {
		mStage.UpSize = 1;
		mStage.UpCount = 0;
	}
	// ゲームオーバー時のタイトル遷移
	if (mStage.GameOverFlg == TRUE) {
		if (iNowKey & PAD_INPUT_8) { //startボタンが押されていたら
			SceneMgr_ChangeScene(eScene_Title); //シーンをタイトル画面に変更
		}
	}
	// ゲームクリア時のステージアニメーション
	if (mStage.numc >= 19) {
		mStage.Scount++;
		if (mStage.Scount == 60) {
			mStage.MoveFlg = FALSE;
			mStage.StateFlg = TRUE;
		}
		if (mStage.Scount == 120) {
			mStage.StateFlg = FALSE;
			mStage.Clearflg = TRUE;
		}

		/*if (mStage.Scount == 10) {
			Stage_Storage();
			mStageChip[1] = mStageChip[21];
			mStageChip[2] = mStageChip[22];
			mStageChip[3] = mStageChip[23];
			mStageChip[4] = mStageChip[24];
			mStageChip[5] = mStageChip[25];
			mStageChip[6] = mStageChip[26];
			mStageChip[7] = mStageChip[27];
			mStageChip[8] = mStageChip[28];
			mStageChip[9] = mStageChip[29];
			mStageChip[10] = mStageChip[30];
			mStageChip[11] = mStageChip[31];
			mStageChip[12] = mStageChip[32];
			mStageChip[13] = mStageChip[33];
			mStageChip[14] = mStageChip[34];
			mStageChip[15] = mStageChip[35];
			mStageChip[16] = mStageChip[36];
			if (mStage.Scount == 20) {
				Stage_Storage();
				mStageChip[21] = mStageChip[1];
				mStageChip[22] = mStageChip[2];
				mStageChip[23] = mStageChip[3];
				mStageChip[24] = mStageChip[4];
				mStageChip[25] = mStageChip[5];
				mStageChip[26] = mStageChip[6];
				mStageChip[27] = mStageChip[7];
				mStageChip[28] = mStageChip[8];
				mStageChip[29] = mStageChip[9];
				mStageChip[30] = mStageChip[10];
				mStageChip[31] = mStageChip[11];
				mStageChip[32] = mStageChip[12];
				mStageChip[33] = mStageChip[13];
				mStageChip[34] = mStageChip[14];
				mStageChip[35] = mStageChip[15];
				mStageChip[36] = mStageChip[16];
				mStage.Scount = 0;
			}
		}*/
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

	//player・readyの表示
	DrawRotaGraph(610, 260, Startsize, 0, mStageUI[2], TRUE, false);	//player　
	DrawRotaGraph(615, 370, Startsize1, 0, mStageUI[3], TRUE, false);	//ready　

	//スコア表示
	DrawGraph(870, 20, mStageUI[0], true);			//ハイスコア
	DrawRotaGraph(930, 145, UpSize, 0, mStageUI[1], TRUE, false);	//１up

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
	for (int num = 0; num < life; num++) {
		DrawRotaGraph(pacX, 550, 1.8, 0, mStagePacman[10], TRUE, FALSE);
		pacX += 60;
	}
	
	//フルーツ表示
	int mFruitNum = 0;
	DrawRotaGraph(940, 390, 1.3, 0, mStageFruit[mFruitNum], true, false);

	//ゲームオーバー表示
	if (GameOverFlg == TRUE) {
		DrawRotaGraph(610, 260, 0.8, 0, mStageUI[2], TRUE, false);
		DrawRotaGraph(615, 370, 0.8, 0, mStageUI[4], TRUE, false);
	}

	//DrawFormatString(0, 0, 0x00ff00, "%d\n", mStage.numc);
}

//画像格納処理
void Stage::Stage_Storage() {
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
	mStageChip[13] = LoadGraph("images/tiles/outercorner_top.png");
	mStageChip[14] = LoadGraph("images/tiles/outercorner_bottom.png");
	mStageChip[15] = LoadGraph("images/tiles/outercorner_right.png");
	mStageChip[16] = LoadGraph("images/tiles/outercorner_left.png");
	mStageChip[38] = LoadGraph("images/tiles/outerwall_wall_center.png");
	mStageChip[39] = LoadGraph("images/tiles/outerwall_wall_tyusin.png");

	// エサ
	mStageChip[17] = LoadGraph("images/tiles/dot.png");
	mStageChip[18] = LoadGraph("images/tiles/big_dot.png");
	// ドア
	mStageChip[19] = LoadGraph("images/tiles/door.png");
	//フルーツ
	mStageChip[20] = LoadGraph("images/fruit1.png");

	// 二重カーブ白バージョン
	mStageChip[21] = LoadGraph("images/tiles_white/outercorner_bottom_left_white.png");
	mStageChip[22] = LoadGraph("images/tiles_white/outercorner_bottom_right_white.png");
	mStageChip[23] = LoadGraph("images/tiles_white/outercorner_narrow_bottom_left_white.png");
	mStageChip[24] = LoadGraph("images/tiles_white/outercorner_narrow_bottom_right_white.png");
	mStageChip[25] = LoadGraph("images/tiles_white/outercorner_narrow_top_left_white.png");
	mStageChip[26] = LoadGraph("images/tiles_white/outercorner_narrow_top_right_white.png");
	mStageChip[27] = LoadGraph("images/tiles_white/outercorner_top_left_white.png");
	mStageChip[28] = LoadGraph("images/tiles_white/outercorner_top_right_white.png");
	// 二重ライン白バージョン
	mStageChip[29] = LoadGraph("images/tiles_white/outerwall_bottom_white.png");
	mStageChip[30] = LoadGraph("images/tiles_white/outerwall_left_white.png");
	mStageChip[31] = LoadGraph("images/tiles_white/outerwall_right_white.png");
	mStageChip[32] = LoadGraph("images/tiles_white/outerwall_top_white.png");
	// ライン白バージョン
	mStageChip[33] = LoadGraph("images/tiles_white/outercorner_top_white.png");
	mStageChip[35] = LoadGraph("images/tiles_white/outercorner_bottom_white.png");
	mStageChip[37] = LoadGraph("images/tiles_white/outercorner_right_white.png");
	mStageChip[36] = LoadGraph("images/tiles_white/outercorner_left_white.png");
	mStageChip[40] = LoadGraph("images/tiles_white/outerwall_wall_center.png");
	mStageChip[41] = LoadGraph("images/tiles_white/outerwall_wall_tyusin.png");

	//スコア部分UI
	mStageUI[0] = LoadGraph("images/title/hi-score.png");	//ハイスコア文字
	mStageUI[1] = LoadGraph("images/title/1up.png");		//１up文字
	mStageUI[2] = LoadGraph("images/title/PLAYER.png");		//player文字
	mStageUI[3] = LoadGraph("images/title/READY.png");		//ready文字
	mStageUI[4] = LoadGraph("images/title/GAMEOVER.png");	//GameOver文字
	LoadDivGraph("images/title/num.png", 10, 10, 1, 32, 32, mStageNum);	//数字
	LoadDivGraph("images/pacman.png", 11, 11, 1, 32, 32, mStagePacman);	//パックマン
	LoadDivGraph("images/fruit.png", 13, 13, 1, 32, 32, mStageFruit);	//フルーツ
}