#include "DxLib.h"
#include "Orange_Enemy.h"
#include "Player.h"
#include <math.h>
#include "Stage.h"

O_ENEMY o_enemy;

int O_EnemeyCheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
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

void O_ENEMY::Initialize() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);  // 敵キャラ
	LoadDivGraph("images/eyes.png", 4, 4, 1, 32, 32, eyesimages);  // 敵キャラの目

	o_enemy.speed = 1;             // 移動速度
	o_enemy.angle = 1;             // 初期の向き
	o_enemy.count = 0;             // アニメーションカウント
	o_enemy.ER_count = 0;          // イジケ状態カウント
	o_enemy.image = 6;             // 画像変数
	o_enemy.eyeimage = 0;          // 目の画像変数
	o_enemy.izikeimage = 16;       // イジケ状態の画像変数
	o_enemy.e_izikeimage = 16;     // イジケ状態点滅の画像変数
	o_enemy.R_Hitflg = FALSE;      // イジケ状態判定フラグ
	o_enemy.ER_Hitflg = FALSE;     // イジケ状態点滅フラグ
	o_enemy.PR_Hitflg = FALSE;     // イジケ状態でプレイヤーに当たった時のフラグ
	o_enemy.eyeflg = FALSE;        // エネミー目状態
	o_enemy.Initiaflg = FALSE;     // エネミー初期化
	o_enemy.HitCount = 0;          // プレイヤー死亡時のエネミーアニメーション
	o_enemy.c = 0;                 // 
	o_enemy.flg = FALSE;           // 

	// 初期位置を保存
	o_enemy.x = O_ENEMY_POS_X;
	o_enemy.y = O_ENEMY_POS_Y;

	//当たり判定
	o_enemy.recordX = o_enemy.x;
	o_enemy.recordY = o_enemy.y;

	o_enemy.top = O_ENEMY_POS_Y - O_ENEMY_POS_HITBOX;
	o_enemy.left = O_ENEMY_POS_X - O_ENEMY_POS_HITBOX;
	o_enemy.right = O_ENEMY_POS_X + O_ENEMY_POS_HITBOX;
	o_enemy.bottom = O_ENEMY_POS_Y + O_ENEMY_POS_HITBOX;

	o_enemy.recordTop = o_enemy.top;
	o_enemy.recordRight = o_enemy.right;
	o_enemy.recordBottom = o_enemy.bottom;
	o_enemy.recordLeft = o_enemy.left;

	// 分身の初期化処理
	//分身のフラグ処理
	o_enemy.Top = FALSE;
	o_enemy.Bottom = FALSE;
	o_enemy.Left = TRUE;
	o_enemy.Right = TRUE;
	//分身の座標
	//上
	o_enemy.ENEMY_AVATAR_POS_X[0] = O_ENEMY_POS_X;
	o_enemy.ENEMY_AVATAR_POS_Y[0] = O_ENEMY_POS_Y - 24;
	//右
	o_enemy.ENEMY_AVATAR_POS_X[1] = O_ENEMY_POS_X + 24;
	o_enemy.ENEMY_AVATAR_POS_Y[1] = O_ENEMY_POS_Y;
	//下
	o_enemy.ENEMY_AVATAR_POS_X[2] = O_ENEMY_POS_X;
	o_enemy.ENEMY_AVATAR_POS_Y[2] = O_ENEMY_POS_Y + 24;
	//左
	o_enemy.ENEMY_AVATAR_POS_X[3] = O_ENEMY_POS_X - 24;
	o_enemy.ENEMY_AVATAR_POS_Y[3] = O_ENEMY_POS_Y;

	// 前回のキー入力処理
	o_enemy.CheckNumber = 12;

	//分身の当たり判定
	for (int i = 0; i < 4; i++) {
		o_enemy.avatar_left[i] = ENEMY_AVATAR_POS_X[i] - O_ENEMY_POS_HITBOX;
		o_enemy.avatar_top[i] = ENEMY_AVATAR_POS_Y[i] - O_ENEMY_POS_HITBOX;
		o_enemy.avatar_right[i] = ENEMY_AVATAR_POS_X[i] + O_ENEMY_POS_HITBOX;
		o_enemy.avatar_bottom[i] = ENEMY_AVATAR_POS_Y[i] + O_ENEMY_POS_HITBOX;
	}
}

void O_ENEMY::Update() {
	//前回の座標取得
	o_enemy.recordX = o_enemy.x;
	o_enemy.recordY = o_enemy.y;

	o_enemy.recordTop = o_enemy.top;
	o_enemy.recordRight = o_enemy.right;
	o_enemy.recordBottom = o_enemy.bottom;
	o_enemy.recordLeft = o_enemy.left;

	//分身の座標
	for (int i = 0; i < 4; i++) {
		o_enemy.record_avatar_bottom[i] = o_enemy.avatar_bottom[i];
		o_enemy.record_avatar_left[i] = o_enemy.avatar_left[i];
		o_enemy.record_avatar_right[i] = o_enemy.avatar_right[i];
		o_enemy.record_avatar_top[i] = o_enemy.avatar_top[i];
	}

	//初期状態
	if (mStage.numc < 32 && mStage.MoveFlg == TRUE && mPlayer.Hitflg == FALSE) {
		// 上向き
		if (o_enemy.angle == 1) {
			if (o_enemy.Top == TRUE) {
				o_enemy.angle = 3;
			}
			else if (o_enemy.Top == FALSE) {
				if (o_enemy.Bottom == FALSE) {
					o_enemy.angle = 3;
				}
				//上向き
				o_enemy.y -= o_enemy.speed;
				//当たり判定
				o_enemy.top -= o_enemy.speed;
				o_enemy.bottom -= o_enemy.speed;
				//分身
				for (int i = 0; i < 4; i++) {
					o_enemy.avatar_top[i] -= o_enemy.speed;
					o_enemy.avatar_bottom[i] -= o_enemy.speed;
				}
				o_enemy.eyeimage = 0;
			}
		}
		//下向き
		else if (o_enemy.angle == 3) {
			if (o_enemy.Bottom == TRUE) {
				o_enemy.angle = 1;
			}
			else if (o_enemy.Bottom == FALSE) {
				if (o_enemy.Top == FALSE) {
					o_enemy.angle = 1;
				}
				//下向き
				o_enemy.y += o_enemy.speed;
				//当たり判定
				o_enemy.top += o_enemy.speed;
				o_enemy.bottom += o_enemy.speed;
				//分身
				for (int i = 0; i < 4; i++) {
					o_enemy.avatar_top[i] += o_enemy.speed;
					o_enemy.avatar_bottom[i] += o_enemy.speed;
				}
				o_enemy.eyeimage = 2;
			}
		}
	}
	else if (mStage.numc > 31) {
		// プレイヤーを追いかける処理
		if (o_enemy.R_Hitflg == FALSE && mStage.MoveFlg == TRUE && mPlayer.Hitflg == FALSE) { // パワーエサを取っていない時
			// 右向き
			if (o_enemy.angle == 2) {
				if (o_enemy.Right == TRUE) {
					if (mPlayer.x < o_enemy.x) { // 左向き
						o_enemy.angle = 4;
					}
					else if (mPlayer.y < o_enemy.y) { // 上向き
						o_enemy.angle = 1;
					}
					else if (mPlayer.y > o_enemy.y) { // 下向き
						o_enemy.angle = 3;
					}
				}
				else if (o_enemy.Right == FALSE) {
					if (mPlayer.x < o_enemy.x) { // 左向き
						if (o_enemy.Left == FALSE) {
							o_enemy.angle = 4;
						}
					}
					else if (mPlayer.y < o_enemy.y) { // 上向き
						if (o_enemy.Top == FALSE) {
							o_enemy.angle = 1;
						}
					}
					else if (mPlayer.y > o_enemy.y) { // 下向き
						if (o_enemy.Bottom == FALSE) {
							o_enemy.angle = 3;
						}
					}
					// 右向き
					o_enemy.x += o_enemy.speed;
					// 当たり判定
					o_enemy.left += o_enemy.speed;
					o_enemy.right += o_enemy.speed;
					//分身
					for (int i = 0; i < 4; i++) {
						o_enemy.avatar_right[i] += o_enemy.speed;
						o_enemy.avatar_left[i] += o_enemy.speed;
					}
					o_enemy.eyeimage = 1;
				}
			}
			// 左向き
			else if (o_enemy.angle == 4) {
				if (o_enemy.Left == TRUE) {
					if (mPlayer.x > o_enemy.x) { // 右向き
						o_enemy.angle = 2;
					}
					else if (mPlayer.y < o_enemy.y) { // 上向き
						o_enemy.angle = 1;
					}
					else if (mPlayer.y > o_enemy.y) { // 下向き
						o_enemy.angle = 3;
					}
				}
				else if (o_enemy.Left == FALSE) {
					if (mPlayer.x > o_enemy.x) { // 右向き
						if (o_enemy.Right == FALSE) {
							o_enemy.angle = 2;
						}
					}
					else if (mPlayer.y < o_enemy.y) { // 上向き
						if (o_enemy.Top == FALSE) {
							o_enemy.angle = 1;
						}
					}
					else if (mPlayer.y > o_enemy.y) { // 下向き
						if (o_enemy.Bottom == FALSE) {
							o_enemy.angle = 3;
						}
					}
					// 左向き
					o_enemy.x -= o_enemy.speed;
					//当たり判定
					o_enemy.left -= o_enemy.speed;
					o_enemy.right -= o_enemy.speed;
					//分身
					for (int i = 0; i < 4; i++) {
						o_enemy.avatar_right[i] -= o_enemy.speed;
						o_enemy.avatar_left[i] -= o_enemy.speed;
					}
					o_enemy.eyeimage = 3;
				}
			}
			//下向き
			else if (o_enemy.angle == 3) {
				if (o_enemy.Bottom == TRUE) {
					if (mPlayer.x > o_enemy.x) { // 右向き
						o_enemy.angle = 2;
					}
					else if (mPlayer.x < o_enemy.x) { // 左向き
						o_enemy.angle = 4;
					}
					else if (mPlayer.y < o_enemy.y) { // 上向き
						o_enemy.angle = 1;
					}
				}
				else if (o_enemy.Bottom == FALSE) {
					if (mPlayer.x > o_enemy.x) { // 右向き
						if (o_enemy.Right == FALSE) {
							o_enemy.angle = 2;
						}
					}
					else if (mPlayer.x < o_enemy.x) { // 左向き
						if (o_enemy.Left == FALSE) {
							o_enemy.angle = 4;
						}
					}
					else if (mPlayer.y < o_enemy.y) { // 上向き
						if (o_enemy.Top == FALSE) {
							o_enemy.angle = 1;
						}
					}
					//下向き
					o_enemy.y += o_enemy.speed;
					//当たり判定
					o_enemy.top += o_enemy.speed;
					o_enemy.bottom += o_enemy.speed;
					//分身
					for (int i = 0; i < 4; i++) {
						o_enemy.avatar_top[i] += o_enemy.speed;
						o_enemy.avatar_bottom[i] += o_enemy.speed;
					}
					o_enemy.eyeimage = 2;
				}
			}
			//上向き
			else if (o_enemy.angle == 1) {
				if (o_enemy.Top == TRUE) {
					if (mPlayer.x > o_enemy.x) { // 右向き
						o_enemy.angle = 2;
					}
					else if (mPlayer.x < o_enemy.x) { // 左向き
						o_enemy.angle = 4;
					}
					else if (mPlayer.y > o_enemy.y) { // 下向き
						o_enemy.angle = 3;
					}
				}
				else if (o_enemy.Top == FALSE) {
					if (mPlayer.x > o_enemy.x) { // 右向き
						if (o_enemy.Right == FALSE) {
							o_enemy.angle = 2;
						}
					}
					else if (mPlayer.x < o_enemy.x) { // 左向き
						if (o_enemy.Left == FALSE) {
							o_enemy.angle = 4;
						}
					}
					else if (mPlayer.y > o_enemy.y) { // 下向き
						if (o_enemy.Bottom == FALSE) {
							o_enemy.angle = 3;
						}
					}
					//上向き
					o_enemy.y -= o_enemy.speed;
					//当たり判定
					o_enemy.top -= o_enemy.speed;
					o_enemy.bottom -= o_enemy.speed;
					//分身
					for (int i = 0; i < 4; i++) {
						o_enemy.avatar_top[i] -= o_enemy.speed;
						o_enemy.avatar_bottom[i] -= o_enemy.speed;
					}
					o_enemy.eyeimage = 0;
				}
			}
		}
		else if (o_enemy.R_Hitflg == TRUE) { // パワーエサを取った時
			if (o_enemy.PR_Hitflg == FALSE) { // プレイヤーと当たっていなかったら
				o_enemy.speed = 0.8;
				// 右向き
				if (o_enemy.angle == 2) {
					if (o_enemy.Right == TRUE) {
						if (mPlayer.x < o_enemy.x) { // 左向き
							o_enemy.angle = 4;
						}
						else if (mPlayer.y < o_enemy.y) { // 上向き
							o_enemy.angle = 1;
						}
						else if (mPlayer.y > o_enemy.y) { // 下向き
							o_enemy.angle = 3;
						}
					}
					else if (o_enemy.Right == FALSE) {
						if (mPlayer.x < o_enemy.x) { // 左向き
							if (o_enemy.Left == FALSE) {
								o_enemy.angle = 4;
							}
						}
						else if (mPlayer.y < o_enemy.y) { // 上向き
							if (o_enemy.Top == FALSE) {
								o_enemy.angle = 1;
							}
						}
						else if (mPlayer.y > o_enemy.y) { // 下向き
							if (o_enemy.Bottom == FALSE) {
								o_enemy.angle = 3;
							}
						}
						// 右向き
						o_enemy.x -= o_enemy.speed;
						// 当たり判定
						o_enemy.left -= o_enemy.speed;
						o_enemy.right -= o_enemy.speed;
						//分身
						for (int i = 0; i < 4; i++) {
							o_enemy.avatar_right[i] -= o_enemy.speed;
							o_enemy.avatar_left[i] -= o_enemy.speed;
						}
					}
				}
				// 左向き
				else if (o_enemy.angle == 4) {
					if (o_enemy.Left == TRUE) {
						if (mPlayer.x > o_enemy.x) { // 右向き
							o_enemy.angle = 2;
						}
						else if (mPlayer.y < o_enemy.y) { // 上向き
							o_enemy.angle = 1;
						}
						else if (mPlayer.y > o_enemy.y) { // 下向き
							o_enemy.angle = 3;
						}
					}
					else if (o_enemy.Left == FALSE) {
						if (mPlayer.x > o_enemy.x) { // 右向き
							if (o_enemy.Right == FALSE) {
								o_enemy.angle = 2;
							}
						}
						else if (mPlayer.y < o_enemy.y) { // 上向き
							if (o_enemy.Top == FALSE) {
								o_enemy.angle = 1;
							}
						}
						else if (mPlayer.y > o_enemy.y) { // 下向き
							if (o_enemy.Bottom == FALSE) {
								o_enemy.angle = 3;
							}
						}
						// 左向き
						o_enemy.x += o_enemy.speed;
						//当たり判定
						o_enemy.left += o_enemy.speed;
						o_enemy.right += o_enemy.speed;
						//分身
						for (int i = 0; i < 4; i++) {
							o_enemy.avatar_right[i] += o_enemy.speed;
							o_enemy.avatar_left[i] += o_enemy.speed;
						}
					}
				}
				//下向き
				else if (o_enemy.angle == 3) {
					if (o_enemy.Bottom == TRUE) {
						if (mPlayer.x > o_enemy.x) { // 右向き
							o_enemy.angle = 2;
						}
						else if (mPlayer.x < o_enemy.x) { // 左向き
							o_enemy.angle = 4;
						}
						else if (mPlayer.y < o_enemy.y) { // 上向き
							o_enemy.angle = 1;
						}
					}
					else if (o_enemy.Bottom == FALSE) {
						if (mPlayer.x > o_enemy.x) { // 右向き
							if (o_enemy.Right == FALSE) {
								o_enemy.angle = 2;
							}
						}
						else if (mPlayer.x < o_enemy.x) { // 左向き
							if (o_enemy.Left == FALSE) {
								o_enemy.angle = 4;
							}
						}
						else if (mPlayer.y < o_enemy.y) { // 上向き
							if (o_enemy.Top == FALSE) {
								o_enemy.angle = 1;
							}
						}
						//下向き
						o_enemy.y -= o_enemy.speed;
						//当たり判定
						o_enemy.top -= o_enemy.speed;
						o_enemy.bottom -= o_enemy.speed;
						//分身
						for (int i = 0; i < 4; i++) {
							o_enemy.avatar_top[i] -= o_enemy.speed;
							o_enemy.avatar_bottom[i] -= o_enemy.speed;
						}
					}
				}
				//上向き
				else if (o_enemy.angle == 1) {
					if (o_enemy.Top == TRUE) {
						if (mPlayer.x > o_enemy.x) { // 右向き
							o_enemy.angle = 2;
						}
						else if (mPlayer.x < o_enemy.x) { // 左向き
							o_enemy.angle = 4;
						}
						else if (mPlayer.y > o_enemy.y) { // 下向き
							o_enemy.angle = 3;
						}
					}
					else if (o_enemy.Top == FALSE) {
						if (mPlayer.x > o_enemy.x) { // 右向き
							if (o_enemy.Right == FALSE) {
								o_enemy.angle = 2;
							}
						}
						else if (mPlayer.x < o_enemy.x) { // 左向き
							if (o_enemy.Left == FALSE) {
								o_enemy.angle = 4;
							}
						}
						else if (mPlayer.y > o_enemy.y) { // 下向き
							if (o_enemy.Bottom == FALSE) {
								o_enemy.angle = 3;
							}
						}
						//上向き
						o_enemy.y += o_enemy.speed;
						//当たり判定
						o_enemy.top += o_enemy.speed;
						o_enemy.bottom += o_enemy.speed;
						//分身
						for (int i = 0; i < 4; i++) {
							o_enemy.avatar_top[i] += o_enemy.speed;
							o_enemy.avatar_bottom[i] += o_enemy.speed;
						}
					}
				}
			}
			else if (o_enemy.PR_Hitflg == TRUE) { // プレイヤーと当たっていたら初期位置に戻る
				if (o_enemy.eyeflg == TRUE) {
					o_enemy.speed = 3;
					// 右向き
					if (o_enemy.angle == 2) {
						if (o_enemy.Right == TRUE) {
							if (ENEMY_POS_X < o_enemy.x) { // 左向き
								o_enemy.angle = 4;
							}
							else if (ENEMY_POS_Y < o_enemy.y) { // 上向き
								o_enemy.angle = 1;
							}
							else if (ENEMY_POS_Y > o_enemy.y) { // 下向き
								o_enemy.angle = 3;
							}
						}
						else if (o_enemy.Right == FALSE) {
							if (ENEMY_POS_X < o_enemy.x) { // 左向き
								if (o_enemy.Left == FALSE) {
									o_enemy.angle = 4;
								}
							}
							else if (ENEMY_POS_Y < o_enemy.y) { // 上向き
								if (o_enemy.Top == FALSE) {
									o_enemy.angle = 1;
								}
							}
							else if (ENEMY_POS_Y > o_enemy.y) { // 下向き
								if (o_enemy.Bottom == FALSE) {
									o_enemy.angle = 3;
								}
							}
							// 右向き
							o_enemy.x += o_enemy.speed;
							// 当たり判定
							o_enemy.left += o_enemy.speed;
							o_enemy.right += o_enemy.speed;
							//分身
							for (int i = 0; i < 4; i++) {
								o_enemy.avatar_right[i] += o_enemy.speed;
								o_enemy.avatar_left[i] += o_enemy.speed;
							}
							o_enemy.eyeimage = 1;
						}
					}
					// 左向き
					else if (o_enemy.angle == 4) {
						if (o_enemy.Left == TRUE) {
							if (ENEMY_POS_X > o_enemy.x) { // 右向き
								o_enemy.angle = 2;
							}
							else if (ENEMY_POS_Y < o_enemy.y) { // 上向き
								o_enemy.angle = 1;
							}
							else if (ENEMY_POS_Y > o_enemy.y) { // 下向き
								o_enemy.angle = 3;
							}
						}
						else if (o_enemy.Left == FALSE) {
							if (ENEMY_POS_X > o_enemy.x) { // 右向き
								if (o_enemy.Right == FALSE) {
									o_enemy.angle = 2;
								}
							}
							else if (ENEMY_POS_Y < o_enemy.y) { // 上向き
								if (o_enemy.Top == FALSE) {
									o_enemy.angle = 1;
								}
							}
							else if (ENEMY_POS_Y > o_enemy.y) { // 下向き
								if (o_enemy.Bottom == FALSE) {
									o_enemy.angle = 3;
								}
							}
							// 左向き
							o_enemy.x -= o_enemy.speed;
							//当たり判定
							o_enemy.left -= o_enemy.speed;
							o_enemy.right -= o_enemy.speed;
							//分身
							for (int i = 0; i < 4; i++) {
								o_enemy.avatar_right[i] -= o_enemy.speed;
								o_enemy.avatar_left[i] -= o_enemy.speed;
							}
							o_enemy.eyeimage = 3;
						}
					}
					//下向き
					else if (o_enemy.angle == 3) {
						if (o_enemy.Bottom == TRUE) {
							if (ENEMY_POS_X > o_enemy.x) { // 右向き
								o_enemy.angle = 2;
							}
							else if (ENEMY_POS_X < o_enemy.x) { // 左向き
								o_enemy.angle = 4;
							}
							else if (ENEMY_POS_Y < o_enemy.y) { // 上向き
								o_enemy.angle = 1;
							}
						}
						else if (o_enemy.Bottom == FALSE) {
							if (ENEMY_POS_X > o_enemy.x) { // 右向き
								if (o_enemy.Right == FALSE) {
									o_enemy.angle = 2;
								}
							}
							else if (ENEMY_POS_X < o_enemy.x) { // 左向き
								if (o_enemy.Left == FALSE) {
									o_enemy.angle = 4;
								}
							}
							else if (ENEMY_POS_Y < o_enemy.y) { // 上向き
								if (o_enemy.Top == FALSE) {
									o_enemy.angle = 1;
								}
							}
							//下向き
							o_enemy.y += o_enemy.speed;
							//当たり判定
							o_enemy.top += o_enemy.speed;
							o_enemy.bottom += o_enemy.speed;
							//分身
							for (int i = 0; i < 4; i++) {
								o_enemy.avatar_top[i] += o_enemy.speed;
								o_enemy.avatar_bottom[i] += o_enemy.speed;
							}
							o_enemy.eyeimage = 2;
						}
					}
					//上向き
					else if (o_enemy.angle == 1) {
						if (o_enemy.Top == TRUE) {
							if (ENEMY_POS_X > o_enemy.x) { // 右向き
								o_enemy.angle = 2;
							}
							else if (ENEMY_POS_X < o_enemy.x) { // 左向き
								o_enemy.angle = 4;
							}
							else if (ENEMY_POS_Y > o_enemy.y) { // 下向き
								o_enemy.angle = 3;
							}
						}
						else if (o_enemy.Top == FALSE) {
							if (ENEMY_POS_X > o_enemy.x) { // 右向き
								if (o_enemy.Right == FALSE) {
									o_enemy.angle = 2;
								}
							}
							else if (ENEMY_POS_X < o_enemy.x) { // 左向き
								if (o_enemy.Left == FALSE) {
									o_enemy.angle = 4;
								}
							}
							else if (ENEMY_POS_Y > o_enemy.y) { // 下向き
								if (o_enemy.Bottom == FALSE) {
									o_enemy.angle = 3;
								}
							}
							//上向き
							o_enemy.y -= o_enemy.speed;
							//当たり判定
							o_enemy.top -= o_enemy.speed;
							o_enemy.bottom -= o_enemy.speed;
							//分身
							for (int i = 0; i < 4; i++) {
								o_enemy.avatar_top[i] -= o_enemy.speed;
								o_enemy.avatar_bottom[i] -= o_enemy.speed;
							}
							o_enemy.eyeimage = 0;
						}
					}
					// 初期位置に戻った時
					if (ENEMY_POS_X == o_enemy.x) {
						o_enemy.eyeflg = FALSE;
					}
				}
			}
		}
	}

	// エネミーとプレイヤーの当たり判定
	if (O_EnemeyCheckHit(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, o_enemy.left, o_enemy.top, o_enemy.right, o_enemy.bottom)) {
		if (o_enemy.R_Hitflg == TRUE || o_enemy.ER_Hitflg == TRUE) { // イジケ状態で当たったら
			o_enemy.PR_Hitflg = TRUE;
			o_enemy.eyeflg = TRUE;
		}
	}

	// アニメーション
	++o_enemy.count;  // カウント開始
	if (o_enemy.count >= 8) {  // 値によってアニメーションのスピードが変化する0に近い程速い
		o_enemy.image++;
		o_enemy.izikeimage++;
		o_enemy.e_izikeimage++;
		o_enemy.count = 0;  // カウントリセット
	}
	if (o_enemy.R_Hitflg == FALSE) { // もしイジケ状態でなければ
		if (o_enemy.image >= 8) { // 通常の画像切り替え
			o_enemy.image = 6;    // 画像リセット
		}
	}
	else if (o_enemy.R_Hitflg == TRUE) { // もしイジケ状態なら
		if (o_enemy.izikeimage >= 18) { // イジケ画像切り替え
			o_enemy.izikeimage = 16; // 画像リセット
		}
	}
	if (o_enemy.ER_Hitflg == TRUE) { // もしイジケ状態が終わりそうなら
		if (o_enemy.e_izikeimage >= 20) { // イジケ点滅画像切り替え
			o_enemy.e_izikeimage = 16; // 画像リセット
		}
	}

	// ワープトンネル
	if (o_enemy.x >= 878) {
		o_enemy.x = 352;

		//分身
		//上
		o_enemy.avatar_right[0] = 352 + O_ENEMY_POS_HITBOX;
		o_enemy.avatar_left[0] = 352 - O_ENEMY_POS_HITBOX;
		//下
		o_enemy.avatar_left[2] = 352 - O_ENEMY_POS_HITBOX;
		o_enemy.avatar_right[2] = 352 + O_ENEMY_POS_HITBOX;
		//右
		o_enemy.avatar_left[1] = 352 + 24 - O_ENEMY_POS_HITBOX;
		o_enemy.avatar_right[1] = 352 + 24 + O_ENEMY_POS_HITBOX;
		//左
		o_enemy.avatar_right[3] = 352 - 24 - O_ENEMY_POS_HITBOX;
		o_enemy.avatar_left[3] = 352 - 24 + O_ENEMY_POS_HITBOX;
	}
	else if (o_enemy.x <= 352) {
		o_enemy.x = 878;

		//分身
		//上
		o_enemy.avatar_right[0] = 878 + O_ENEMY_POS_HITBOX;
		o_enemy.avatar_left[0] = 878 - O_ENEMY_POS_HITBOX;
		//下
		o_enemy.avatar_left[2] = 878 - O_ENEMY_POS_HITBOX;
		o_enemy.avatar_right[2] = 878 + O_ENEMY_POS_HITBOX;
		//右
		o_enemy.avatar_left[1] = 878 + 24 - O_ENEMY_POS_HITBOX;
		o_enemy.avatar_right[1] = 878 + 24 + O_ENEMY_POS_HITBOX;
		//左
		o_enemy.avatar_right[3] = 878 - 24 - O_ENEMY_POS_HITBOX;
		o_enemy.avatar_left[3] = 878 - 24 + O_ENEMY_POS_HITBOX;
	}

	// イジケ状態フラグ
	if (o_enemy.R_Hitflg == TRUE) {
		++o_enemy.ER_count;
	}
	// プレイヤー死亡時のエネミーアニメーション
	if (mPlayer.Hitflg == TRUE) {
		o_enemy.HitCount++;
		int a = 5; int b = 10;
		if (o_enemy.HitCount == a) {
			o_enemy.image = 6;
			a += 5;
		}
		else if (o_enemy.HitCount == b) {
			o_enemy.image = 7;
			b += 5;
		}
		if (o_enemy.HitCount == 80) {
			flg = TRUE;
		}
	}
}

void O_ENEMY::Draw() {
	//足だけが動く処理
	if (mPlayer.Hitflg == TRUE && flg == FALSE) {
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0.75, 0, o_enemy.images[o_enemy.image], TRUE, FALSE);
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0.75, 0, o_enemy.eyesimages[o_enemy.eyeimage], TRUE, FALSE);
	}
	//PCに当たったときに消える
	if (flg == TRUE) {
		/*DrawRotaGraph(r_enemy.x, r_enemy.y, 0, 0, images[r_enemy.image], TRUE, FALSE);
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE); */
	}
	//スタートの時のみ表示
	if (mStage.StateFlg == FALSE || mStage.GameOverFlg == TRUE) {
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0, 0, o_enemy.images[o_enemy.image], TRUE, FALSE);
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0, 0, o_enemy.eyesimages[o_enemy.eyeimage], TRUE, FALSE);
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0, 0, o_enemy.images[o_enemy.izikeimage], TRUE, FALSE);
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0, 0, o_enemy.images[o_enemy.e_izikeimage], TRUE, FALSE);
	}
	//スタート時の固定表示
	else if (mStage.StateFlg == TRUE) {
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0.75, 0, o_enemy.images[6], TRUE, FALSE);
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0.75, 0, o_enemy.eyesimages[0], TRUE, FALSE);
	}
	//パワーエサを取っていないかつ、Moveflgで動いて可能かつ、Pacに当たっていない時
	if (o_enemy.R_Hitflg == FALSE && mStage.MoveFlg == TRUE && mPlayer.Hitflg == FALSE) {
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0.75, 0, o_enemy.images[o_enemy.image], TRUE, FALSE); // 敵キャラ表示
		DrawRotaGraph(o_enemy.x, o_enemy.y, 0.75, 0, o_enemy.eyesimages[o_enemy.eyeimage], TRUE, FALSE); // 敵キャラの目表示
		//DrawBox(o_enemy.left, o_enemy.top, o_enemy.right, o_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
	}
	else if (o_enemy.R_Hitflg == TRUE) { // パワーエサを取っていたら
		if (o_enemy.PR_Hitflg == FALSE) { // プレイヤーと当たっていなければ
			if (o_enemy.ER_count <= 480) {
				DrawRotaGraph(o_enemy.x, o_enemy.y, 0.75, 0, o_enemy.images[o_enemy.izikeimage], TRUE, FALSE); // イジケ状態表示
				//DrawBox(o_enemy.left, o_enemy.top, o_enemy.right, o_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
			}
			else if (o_enemy.ER_count > 480 && o_enemy.ER_count <= 600) {
				o_enemy.ER_Hitflg = TRUE;
				DrawRotaGraph(o_enemy.x, o_enemy.y, 0.75, 0, o_enemy.images[o_enemy.e_izikeimage], TRUE, FALSE); // イジケ状態表示
				//DrawBox(o_enemy.left, o_enemy.top, o_enemy.right, o_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
			}
			else {
				o_enemy.R_Hitflg = FALSE;
				o_enemy.ER_Hitflg = FALSE;
				o_enemy.ER_count = 0;
				mPlayer.timercount = 0;
			}
		}
		else if (o_enemy.PR_Hitflg == TRUE) { // プレイヤーと当たっていたら
			if (o_enemy.eyeflg == TRUE) { // 目状態になったら
				DrawRotaGraph(o_enemy.x, o_enemy.y, 0.75, 0, o_enemy.eyesimages[o_enemy.eyeimage], TRUE, FALSE); // 敵キャラの目表示
				//DrawBox(o_enemy.left, o_enemy.top, o_enemy.right, o_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
			}
			else if (o_enemy.eyeflg == FALSE) { // 目状態のエネミーが初期位置に戻ったら
				o_enemy.R_Hitflg = FALSE;
				o_enemy.PR_Hitflg = FALSE;
				o_enemy.ER_Hitflg = FALSE;
				o_enemy.ER_count = 0;
				mPlayer.timercount = 0;
			}
		}
	}

	if (o_enemy.Initiaflg == TRUE) {
		// 初期位置に戻す
		o_enemy.x = O_ENEMY_POS_X;
		o_enemy.y = O_ENEMY_POS_Y;
		o_enemy.top = O_ENEMY_POS_Y - O_ENEMY_POS_HITBOX;
		o_enemy.left = O_ENEMY_POS_X - O_ENEMY_POS_HITBOX;
		o_enemy.right = O_ENEMY_POS_X + O_ENEMY_POS_HITBOX;
		o_enemy.bottom = O_ENEMY_POS_Y + O_ENEMY_POS_HITBOX;
		o_enemy.Initiaflg = FALSE;

		//分身の当たり判定
		for (int i = 0; i < 4; i++) {
			o_enemy.avatar_left[i] = ENEMY_AVATAR_POS_X[i] - O_ENEMY_POS_HITBOX;
			o_enemy.avatar_top[i] = ENEMY_AVATAR_POS_Y[i] - O_ENEMY_POS_HITBOX;
			o_enemy.avatar_right[i] = ENEMY_AVATAR_POS_X[i] + O_ENEMY_POS_HITBOX;
			o_enemy.avatar_bottom[i] = ENEMY_AVATAR_POS_Y[i] + O_ENEMY_POS_HITBOX;
		}

		o_enemy.flg = FALSE;
		o_enemy.HitCount = 0;
	}

	////分身の表示
	//for (int i = 0; i < 4; i++) {
	//	DrawBox(o_enemy.avatar_left[i], o_enemy.avatar_top[i], o_enemy.avatar_right[i], o_enemy.avatar_bottom[i], 0x00ffff, FALSE);
	//}

	////進める時
	////上
	//if (o_enemy.Top == TRUE) {
	//	DrawBox(o_enemy.avatar_left[0], o_enemy.avatar_top[0], o_enemy.avatar_right[0], o_enemy.avatar_bottom[0], 0xff00ff, true);
	//}
	//else if (o_enemy.Top == FALSE) {
	//	DrawBox(o_enemy.avatar_left[0], o_enemy.avatar_top[0], o_enemy.avatar_right[0], o_enemy.avatar_bottom[0], 0xff0000, true);
	//}
	////右
	//if (o_enemy.Right == TRUE) {
	//	DrawBox(o_enemy.avatar_left[1], o_enemy.avatar_top[1], o_enemy.avatar_right[1], o_enemy.avatar_bottom[1], 0xff00ff, true);
	//}
	//else if (o_enemy.Right == FALSE) {
	//	DrawBox(o_enemy.avatar_left[1], o_enemy.avatar_top[1], o_enemy.avatar_right[1], o_enemy.avatar_bottom[1], 0xff0000, true);
	//}
	////下
	//if (o_enemy.Bottom == TRUE) {
	//	DrawBox(o_enemy.avatar_left[2], o_enemy.avatar_top[2], o_enemy.avatar_right[2], o_enemy.avatar_bottom[2], 0xff00ff, true);
	//}
	//else if (o_enemy.Bottom == FALSE) {
	//	DrawBox(o_enemy.avatar_left[2], o_enemy.avatar_top[2], o_enemy.avatar_right[2], o_enemy.avatar_bottom[2], 0xff0000, true);
	//}
	////左
	//if (o_enemy.Left == TRUE) {
	//	DrawBox(o_enemy.avatar_left[3], o_enemy.avatar_top[3], o_enemy.avatar_right[3], o_enemy.avatar_bottom[3], 0xff00ff, true);
	//}
	//else if (o_enemy.Left == FALSE) {
	//	DrawBox(o_enemy.avatar_left[3], o_enemy.avatar_top[3], o_enemy.avatar_right[3], o_enemy.avatar_bottom[3], 0xff0000, true);
	//}
}