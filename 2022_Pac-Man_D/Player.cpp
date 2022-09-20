#include "DxLib.h"
#include "Player.h"
#include "Input.h"
#include "Red_Enemy.h"
#include "Pink_Enemy.h"
#include "Blue_Enemy.h"
#include "Orange_Enemy.h"
#include "Stage.h"
#include "sound.h"

Player mPlayer;

//当たり判定
int PlayerCheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	int L1 = x1;		//左
	int R1 = w1;		//右
	int L2 = x2;		//左
	int R2 = w2;		//右
	if (R1 < L2) return 0;
	if (R2 < L1) return 0;
	int U1 = y1;		//上
	int D1 = h1;		//下
	int U2 = y2;		//上
	int D2 = h2;		//下
	if (D1 < U2) return 0;
	if (D2 < U1) return 0;
	//当たっている
	return 1;
}

//初期化処理
void Player::Player_Initialize() {
	//移動
	mPlayer.x = PLAYER_POS_X;
	mPlayer.y = PLAYER_POS_Y;
	//中心の当たり判定の座標
	mPlayer.Hitflg = FALSE;		//エネミーとのヒットフラグ
	mPlayer.p_left = PLAYER_POS_X - PLAYER_CENTER_HITBOX;
	mPlayer.p_top = PLAYER_POS_Y - PLAYER_CENTER_HITBOX;
	mPlayer.p_right = PLAYER_POS_X + PLAYER_CENTER_HITBOX;
	mPlayer.p_bottom = PLAYER_POS_Y + PLAYER_CENTER_HITBOX;
	//Stageとの当たり判定
	mPlayer.P_StageHitflg = FALSE;		//ステージとのヒットフラグ
	mPlayer.s_left = PLAYER_POS_X - PLAYER_POS_HITBOX;
	mPlayer.s_top = PLAYER_POS_Y - PLAYER_POS_HITBOX;
	mPlayer.s_right = PLAYER_POS_X + PLAYER_POS_HITBOX;
	mPlayer.s_bottom = PLAYER_POS_Y + PLAYER_POS_HITBOX;
	//移動画像格納
	LoadDivGraph("images/pacman.png", 12, 12, 1, 32, 32, mPlayer.mPlayerMoveImage);
	//アングル
	mPlayer.iNowAngle = 4;
	mPlayer.iOldAngle = mPlayer.iNowAngle;
	//移動
	mPlayer.move = 2;
	//前回の座標格納
	mPlayer.recordX = mPlayer.x;
	mPlayer.recordY = mPlayer.y;
	mPlayer.recordSTop = mPlayer.s_top;
	mPlayer.recordSRight = mPlayer.s_right;
	mPlayer.recordSBottom = mPlayer.s_bottom;
	mPlayer.recordSLeft = mPlayer.s_left;
	mPlayer.recordPtop = mPlayer.p_top;
	mPlayer.recordPright = mPlayer.p_right;
	mPlayer.recordPbottom = mPlayer.p_bottom;
	mPlayer.recordPleft = mPlayer.p_left;
	//デリート処理
	LoadDivGraph("images/dying.png", 11, 11, 1, 32, 32, mPlayer.mPlayerDeleteImage);
	mPlayer.deletecount = 0;
	mPlayer.deleteimage = 0;
	//画像処理
	mPlayer.count = 0;
	mPlayer.timercount = 0;
	mPlayer.image = 0;
	mPlayer.Hitflg = FALSE;
	// 死んだとき
	mPlayer.millisecond = 0.01 * 1000;

	//分身の初期化処理
	//分身のフラグ処理
	mPlayer.Top = FALSE;
	mPlayer.Bottom = FALSE;
	mPlayer.Left = TRUE;
	mPlayer.Right = TRUE;
	//分身の座標
	//上
	mPlayer.PLAYER_AVATAR_POS_X[0] = PLAYER_POS_X;
	mPlayer.PLAYER_AVATAR_POS_Y[0] = PLAYER_POS_Y - 24;
	//右
	mPlayer.PLAYER_AVATAR_POS_X[1] = PLAYER_POS_X + 24;
	mPlayer.PLAYER_AVATAR_POS_Y[1] = PLAYER_POS_Y;
	//下
	mPlayer.PLAYER_AVATAR_POS_X[2] = PLAYER_POS_X;
	mPlayer.PLAYER_AVATAR_POS_Y[2] = PLAYER_POS_Y + 24;
	//左
	mPlayer.PLAYER_AVATAR_POS_X[3] = PLAYER_POS_X - 24;
	mPlayer.PLAYER_AVATAR_POS_Y[3] = PLAYER_POS_Y;

	// 前回のキー入力処理
	mPlayer.CheckNumber = 12;

	//分身の当たり判定
	for (int i = 0; i < 4; i++) {
		mPlayer.avatar_left[i] = PLAYER_AVATAR_POS_X[i] - PLAYER_POS_HITBOX;
		mPlayer.avatar_top[i] = PLAYER_AVATAR_POS_Y[i] - PLAYER_POS_HITBOX;
		mPlayer.avatar_right[i] = PLAYER_AVATAR_POS_X[i] + PLAYER_POS_HITBOX;
		mPlayer.avatar_bottom[i] = PLAYER_AVATAR_POS_Y[i] + PLAYER_POS_HITBOX;
	}
}

void Player::Player_Update() {
	//画像カウント
	++count;
	//前回の座標を取得
	mPlayer.recordX = mPlayer.x;
	mPlayer.recordY = mPlayer.y;
	//前回の座標（ステージHitbox）
	mPlayer.recordSTop = mPlayer.s_top;
	mPlayer.recordSRight = mPlayer.s_right;
	mPlayer.recordSBottom = mPlayer.s_bottom;
	mPlayer.recordSLeft = mPlayer.s_left;
	//前回の座標（PlayerHitbox）
	mPlayer.recordPtop = mPlayer.p_top;
	mPlayer.recordPright = mPlayer.p_right;
	mPlayer.recordPbottom = mPlayer.p_bottom;
	mPlayer.recordPleft = mPlayer.p_left;

	//分身の座標
	for (int i = 0; i < 4; i++) {
		mPlayer.record_avatar_bottom[i] = mPlayer.avatar_bottom[i];
		mPlayer.record_avatar_left[i] = mPlayer.avatar_left[i];
		mPlayer.record_avatar_right[i] = mPlayer.avatar_right[i];
		mPlayer.record_avatar_top[i] = mPlayer.avatar_top[i];
	}

	//画像処理
	if (count >= 3) {
		mPlayer.image += 1;
		count = 0;
	}
	if (mPlayer.image % 3 == 0 || mPlayer.image >= 12) {
		if (mPlayer.iNowAngle == 1) {
			mPlayer.image = 0;
		}
		else if (mPlayer.iNowAngle == 2) {
			mPlayer.image = 3;
		}
		else if (mPlayer.iNowAngle == 3) {
			mPlayer.image = 6;
		}
		else if (mPlayer.iNowAngle == 4) {
			mPlayer.image = 9;
		}
	}
	
	// プレイヤーとエネミーの当たり判定 赤エネミー
	if (PlayerCheckHit(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom)) {
		if (mPlayer.Hitflg == FALSE) {
			if (r_enemy.R_Hitflg == TRUE || r_enemy.ER_Hitflg == TRUE) { // イジケ状態で当たったら
				++mPlayer.timercount; // カウント開始
				if (mPlayer.timercount < 2) { // カウントが2より小さければ
					WaitTimer(1000); // 1秒間時間を止める
				}
			}
			else {
				mPlayer.Hitflg = TRUE; // イジケ状態が終わったら元の当たり判定に戻す
			}
		}
	}
	// ピンクエネミー
	if (PlayerCheckHit(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, p_enemy.left, p_enemy.top, p_enemy.right, p_enemy.bottom)) {
		if (mPlayer.Hitflg == FALSE) {
			if (p_enemy.R_Hitflg == TRUE || p_enemy.ER_Hitflg == TRUE) { // イジケ状態で当たったら
				++mPlayer.timercount; // カウント開始
				if (mPlayer.timercount < 2) { // カウントが2より小さければ
					WaitTimer(1000); // 1秒間時間を止める
				}
			}
			else {
				mPlayer.Hitflg = TRUE; // イジケ状態が終わったら元の当たり判定に戻す
			}
		}
	}
	// 青エネミー
	if (PlayerCheckHit(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, b_enemy.left, b_enemy.top, b_enemy.right, b_enemy.bottom)) {
		if (mPlayer.Hitflg == FALSE) {
			if (b_enemy.R_Hitflg == TRUE || b_enemy.ER_Hitflg == TRUE) { // イジケ状態で当たったら
				++mPlayer.timercount; // カウント開始
				if (mPlayer.timercount < 2) { // カウントが2より小さければ
					WaitTimer(1000); // 1秒間時間を止める
				}
			}
			else {
				mPlayer.Hitflg = TRUE; // イジケ状態が終わったら元の当たり判定に戻す
			}
		}
	}
	// オレンジエネミー
	if (PlayerCheckHit(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, o_enemy.left, o_enemy.top, o_enemy.right, o_enemy.bottom)) {
		if (mPlayer.Hitflg == FALSE) {
			if (o_enemy.R_Hitflg == TRUE || o_enemy.ER_Hitflg == TRUE) { // イジケ状態で当たったら
				++mPlayer.timercount; // カウント開始
				if (mPlayer.timercount < 2) { // カウントが2より小さければ
					WaitTimer(1000); // 1秒間時間を止める
				}
			}
			else {
				mPlayer.Hitflg = TRUE; // イジケ状態が終わったら元の当たり判定に戻す
			}
		}
	}

	//キー入力処理(ステージに触れていない時)
	//if (mPlayer.P_StageHitflg == FALSE) {
		//右
		if (iNowKey & PAD_INPUT_RIGHT){
			//壁がない
			if (mPlayer.Right == FALSE) {
				mPlayer.iNowAngle = 2;
				mPlayer.iOldAngle = mPlayer.iNowAngle;
			}
			//壁がある
			else if (mPlayer.Right == TRUE) {
				mPlayer.iOldAngle = 2;
			}
		}
		//左
		else if (iNowKey & PAD_INPUT_LEFT) {
			//壁がない
			if (mPlayer.Left == FALSE) {
				mPlayer.iNowAngle = 4;
				mPlayer.iOldAngle = mPlayer.iNowAngle;
			}
			//壁がある
			else if (mPlayer.Left == TRUE) {
				mPlayer.iOldAngle = 4;
			}
		}
		//上
		else if (iNowKey & PAD_INPUT_UP) {
			//壁がない
			if (mPlayer.Top == FALSE) {
				mPlayer.iNowAngle = 1;
				mPlayer.iOldAngle = mPlayer.iNowAngle;
			}
			//壁がある
			else if (mPlayer.Top == TRUE) {
				mPlayer.iOldAngle = 1;
			}
		}
		//下
		else if (iNowKey & PAD_INPUT_DOWN) {
			//壁がない
			if (mPlayer.Bottom == FALSE) {
				mPlayer.iNowAngle = 3;
				mPlayer.iOldAngle = mPlayer.iNowAngle;
			}
			//壁がある
			else if (mPlayer.Bottom == TRUE) {
				mPlayer.iOldAngle = 3;
			}
		}
	//}

	//前回の入力キーがあるかどうか
	if (mPlayer.x % mPlayer.CheckNumber == 0 && mPlayer.y % mPlayer.CheckNumber == 0) {
		//うえ
		if (mPlayer.Top == FALSE && mPlayer.iOldAngle == 1) {
			mPlayer.iNowAngle = mPlayer.iOldAngle;
		}
		//みぎ
		if (mPlayer.Right == FALSE && mPlayer.iOldAngle == 2) {
			mPlayer.iNowAngle = mPlayer.iOldAngle;
		}
		//した
		if (mPlayer.Bottom == FALSE && mPlayer.iOldAngle == 3) {
			mPlayer.iNowAngle = mPlayer.iOldAngle;
		}
		//ひだり
		if (mPlayer.Left == FALSE && mPlayer.iOldAngle == 4) {
			mPlayer.iNowAngle = mPlayer.iOldAngle;
		}
	}
	 
	

	//移動処理
	if (mPlayer.Hitflg == FALSE && mStage.MoveFlg == TRUE) {
		//上
		if (mPlayer.iNowAngle == 1) {
			mPlayer.y -= mPlayer.move;
			//HitBox移動
			mPlayer.p_top -= mPlayer.move;
			mPlayer.p_bottom -= mPlayer.move;
			mPlayer.s_top -= mPlayer.move;
			mPlayer.s_bottom -= mPlayer.move;

			//分身
			for (int i = 0; i < 4; i++) {
				mPlayer.avatar_top[i] -= mPlayer.move;
				mPlayer.avatar_bottom[i] -= mPlayer.move;
			}

		}
		//右
		else if (mPlayer.iNowAngle == 2) {
			mPlayer.x += mPlayer.move;
			//HitBox移動
			mPlayer.p_left += mPlayer.move;
			mPlayer.p_right += mPlayer.move;
			mPlayer.s_left += mPlayer.move;
			mPlayer.s_right += mPlayer.move;

			//分身
			for (int i = 0; i < 4; i++) {
				mPlayer.avatar_left[i] += mPlayer.move;
				mPlayer.avatar_right[i] += mPlayer.move;
			}
		}
		//下
		else if (mPlayer.iNowAngle == 3) {
			mPlayer.y += mPlayer.move;
			//HitBox移動
			mPlayer.p_top += mPlayer.move;
			mPlayer.p_bottom += mPlayer.move;
			mPlayer.s_top += mPlayer.move;
			mPlayer.s_bottom += mPlayer.move;

			//分身
			for (int i = 0; i < 4; i++) {
				mPlayer.avatar_top[i] += mPlayer.move;
				mPlayer.avatar_bottom[i] += mPlayer.move;
			}
		}
		//左
		else if (mPlayer.iNowAngle == 4) {
			mPlayer.x -= mPlayer.move;
			//HitBox移動
			mPlayer.p_left -= mPlayer.move;
			mPlayer.p_right -= mPlayer.move;
			mPlayer.s_left -= mPlayer.move;
			mPlayer.s_right -= mPlayer.move;

			//分身
			for (int i = 0; i < 4; i++) {
				mPlayer.avatar_right[i] -= mPlayer.move;
				mPlayer.avatar_left[i] -= mPlayer.move;
			}
		}
	}

	// ワープ(そのまま)
	if (mPlayer.x >= 878) {
		mPlayer.x = 352;
		//HitBox移動
		mPlayer.p_right = 352 + PLAYER_CENTER_HITBOX;
		mPlayer.p_left = 352 - PLAYER_CENTER_HITBOX;
		mPlayer.s_right = 352 + PLAYER_POS_HITBOX;
		mPlayer.s_left = 352 - PLAYER_POS_HITBOX;

		//分身
		//上
		mPlayer.avatar_right[0] = 352 + PLAYER_POS_HITBOX;
		mPlayer.avatar_left[0] = 352 - PLAYER_POS_HITBOX;
		//下
		mPlayer.avatar_left[2] = 352 - PLAYER_POS_HITBOX;
		mPlayer.avatar_right[2] = 352 + PLAYER_POS_HITBOX;
		//右
		mPlayer.avatar_left[1] = 352 + 24 - PLAYER_POS_HITBOX;
		mPlayer.avatar_right[1] = 352 + 24 + PLAYER_POS_HITBOX;
		//左
		mPlayer.avatar_right[3] = 352 - 24 - PLAYER_POS_HITBOX;
		mPlayer.avatar_left[3] = 352 - 24 + PLAYER_POS_HITBOX;
	}
	else if (mPlayer.x <= 352) {
		mPlayer.x = 878;
		//HitBox移動
		mPlayer.p_right = 878 + PLAYER_CENTER_HITBOX;
		mPlayer.p_left = 878 - PLAYER_CENTER_HITBOX;
		mPlayer.s_right = 878 + PLAYER_POS_HITBOX;
		mPlayer.s_left = 878 - PLAYER_POS_HITBOX;

		//分身
		//上
		mPlayer.avatar_right[0] = 878 + PLAYER_POS_HITBOX;
		mPlayer.avatar_left[0] = 878 - PLAYER_POS_HITBOX;
		//下
		mPlayer.avatar_left[2] = 878 - PLAYER_POS_HITBOX;
		mPlayer.avatar_right[2] = 878 + PLAYER_POS_HITBOX;
		//右
		mPlayer.avatar_left[1] = 878 + 24 - PLAYER_POS_HITBOX;
		mPlayer.avatar_right[1] = 878 + 24 + PLAYER_POS_HITBOX;
		//左
		mPlayer.avatar_right[3] = 878 - 24 - PLAYER_POS_HITBOX;
		mPlayer.avatar_left[3] = 878 - 24 + PLAYER_POS_HITBOX;
	}
}

void Player::Player_Draw() {
	if (mPlayer.Hitflg == FALSE && mStage.MoveFlg == TRUE) {		//Player表示
		DrawRotaGraph(mPlayer.x, mPlayer.y, 0.75, 0, mPlayer.mPlayerMoveImage[mPlayer.image], TRUE, FALSE);
		mPlayer.deleteimage = 0;
	}
	if(mStage.StateFlg == TRUE){		//スタート時表示
		DrawRotaGraph(mPlayer.x, mPlayer.y, 0.75, 0, mPlayer.mPlayerMoveImage[10], TRUE, FALSE);
	}
	else if (mPlayer.Hitflg == TRUE) {
		mPlayer.deletecount++;

		if (mPlayer.deletecount % 5 == 0) {
			mPlayer.deleteimage++;
		}
		DrawRotaGraph(mPlayer.x, mPlayer.y, 0.75, 0, mPlayer.mPlayerDeleteImage[mPlayer.deleteimage], TRUE, FALSE);

		Sleep(millisecond);
		if (mPlayer.deleteimage >= 11) {
			// プレイヤーの初期化処理
			mPlayer.x = PLAYER_POS_X;
			mPlayer.y = PLAYER_POS_Y;
			mPlayer.p_left = PLAYER_POS_X - PLAYER_CENTER_HITBOX;
			mPlayer.p_top = PLAYER_POS_Y - PLAYER_CENTER_HITBOX;
			mPlayer.p_right = PLAYER_POS_X + PLAYER_CENTER_HITBOX;
			mPlayer.p_bottom = PLAYER_POS_Y + PLAYER_CENTER_HITBOX;
			mPlayer.s_left = PLAYER_POS_X - PLAYER_POS_HITBOX;
			mPlayer.s_top = PLAYER_POS_Y - PLAYER_POS_HITBOX;
			mPlayer.s_right = PLAYER_POS_X + PLAYER_POS_HITBOX;
			mPlayer.s_bottom = PLAYER_POS_Y + PLAYER_POS_HITBOX;
			mPlayer.iNowAngle = 4;
			mPlayer.Hitflg = FALSE;
			r_enemy.Initiaflg = TRUE;
			b_enemy.Initiaflg = TRUE;
			//分身の当たり判定
			for (int i = 0; i < 4; i++) {
				mPlayer.avatar_left[i] = PLAYER_AVATAR_POS_X[i] - PLAYER_POS_HITBOX;
				mPlayer.avatar_top[i] = PLAYER_AVATAR_POS_Y[i] - PLAYER_POS_HITBOX;
				mPlayer.avatar_right[i] = PLAYER_AVATAR_POS_X[i] + PLAYER_POS_HITBOX;
				mPlayer.avatar_bottom[i] = PLAYER_AVATAR_POS_Y[i] + PLAYER_POS_HITBOX;
			}
		}
	}
	if (mStage.GameOverFlg == TRUE) {
		mStage.MoveFlg = false;
	}
	//分身の表示
	for (int i = 0; i < 4; i++) {
		DrawBox(mPlayer.avatar_left[i], mPlayer.avatar_top[i], mPlayer.avatar_right[i], mPlayer.avatar_bottom[i], 0x00ffff, FALSE);
	}

	if (mPlayer.Top == FALSE) {
		DrawString(0, 0, "上成功", 0xff00ff);
	}
	if (mPlayer.Right == FALSE) {
		DrawString(0, 20, "右成功", 0xff00ff);
	}
	if (mPlayer.Bottom == FALSE) {
		DrawString(0, 40, "下成功", 0xff00ff);
	}
	if (mPlayer.Left == FALSE) {
		DrawString(0, 60, "左成功", 0xff00ff);
	}
	if (mPlayer.P_StageHitflg == TRUE) {
		DrawString(0, 80, "当たっています", 0xff00ff);
	}
	else if (mPlayer.P_StageHitflg == FALSE) {
		DrawString(0, 80, "当たっていません", 0xff00ff);
	}

	if (mPlayer.iNowAngle == 1) {
		DrawString(0, 100, "現在のアングルは上です", 0xff00ff);
	}
	else if (mPlayer.iNowAngle == 2) {
		DrawString(0, 100, "現在のアングルは右です", 0xff00ff);
	} 
	else if (mPlayer.iNowAngle == 3) {
		DrawString(0, 100, "現在のアングルは下です", 0xff00ff);
	}
	else if (mPlayer.iNowAngle == 4) {
		DrawString(0, 100, "現在のアングルは左です", 0xff00ff);
	}

	if (mPlayer.iOldAngle == 1) {
		DrawString(0, 120, "前回のアングルは上です", 0xff00ff);
	}
	else if (mPlayer.iOldAngle == 2) {
		DrawString(0, 120, "前回のアングルは右です", 0xff00ff);
	}
	else if (mPlayer.iOldAngle == 3) {
		DrawString(0, 120, "前回のアングルは下です", 0xff00ff);
	}
	else if (mPlayer.iOldAngle == 4) {
		DrawString(0, 120, "前回のアングルは左です", 0xff00ff);
	}

	//進める時
	//上
	if (mPlayer.Top == TRUE) {
		DrawBox(mPlayer.avatar_left[0], mPlayer.avatar_top[0], mPlayer.avatar_right[0], mPlayer.avatar_bottom[0], 0xff00ff, true);
	}
	else if (mPlayer.Top == FALSE) {
		DrawBox(mPlayer.avatar_left[0], mPlayer.avatar_top[0], mPlayer.avatar_right[0], mPlayer.avatar_bottom[0], 0xff0000, true);
	}
	//右
	if (mPlayer.Right == TRUE) {
		DrawBox(mPlayer.avatar_left[1], mPlayer.avatar_top[1], mPlayer.avatar_right[1], mPlayer.avatar_bottom[1], 0xff00ff, true);
	}
	else if (mPlayer.Right == FALSE) {
		DrawBox(mPlayer.avatar_left[1], mPlayer.avatar_top[1], mPlayer.avatar_right[1], mPlayer.avatar_bottom[1], 0xff0000, true);
	}
	//下
	if (mPlayer.Bottom == TRUE) {
		DrawBox(mPlayer.avatar_left[2], mPlayer.avatar_top[2], mPlayer.avatar_right[2], mPlayer.avatar_bottom[2], 0xff00ff, true);
	}
	else if (mPlayer.Bottom == FALSE) {
		DrawBox(mPlayer.avatar_left[2], mPlayer.avatar_top[2], mPlayer.avatar_right[2], mPlayer.avatar_bottom[2], 0xff0000, true);
	}
	//左
	if (mPlayer.Left == TRUE) {
		DrawBox(mPlayer.avatar_left[3], mPlayer.avatar_top[3], mPlayer.avatar_right[3], mPlayer.avatar_bottom[3], 0xff00ff, true);
	}
	else if (mPlayer.Left == FALSE) {
		DrawBox(mPlayer.avatar_left[3], mPlayer.avatar_top[3], mPlayer.avatar_right[3], mPlayer.avatar_bottom[3], 0xff0000, true);
	}
	
	//Stage当たり判定表示
	DrawBox(mPlayer.s_left, mPlayer.s_top, mPlayer.s_right, mPlayer.s_bottom, 0x00ff00, FALSE);
	//Center当たり判定表示
	DrawBox(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, 0xff00ff, TRUE);
}
