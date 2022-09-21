#include "DxLib.h"
#include "Red_Enemy.h"
#include "Player.h"
#include <math.h>
#include "Stage.h"

R_ENEMY r_enemy;

int EnemeyCheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
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

void R_ENEMY::Initialize() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);  // 敵キャラ
	LoadDivGraph("images/eyes.png", 4, 4, 1, 32, 32, eyesimages);  // 敵キャラの目

	r_enemy.speed = 1;             // 移動速度
	r_enemy.angle = 4;             // 初期の向き
	r_enemy.count = 0;             // アニメーションカウント
	r_enemy.ER_count = 0;          // イジケ状態カウント
	r_enemy.image = 0;             // 画像変数
	r_enemy.eyeimage = 3;          // 目の画像変数
	r_enemy.izikeimage = 16;       // イジケ状態の画像変数
	r_enemy.e_izikeimage = 16;     // イジケ状態点滅の画像変数
	r_enemy.R_Hitflg = FALSE;      // イジケ状態判定フラグ
	r_enemy.ER_Hitflg = FALSE;     // イジケ状態点滅フラグ
	r_enemy.PR_Hitflg = FALSE;     // イジケ状態でプレイヤーに当たった時のフラグ
	r_enemy.eyeflg = FALSE;        // エネミー目状態
	r_enemy.Initiaflg = FALSE;     // エネミー初期化
	r_enemy.HitCount = 0;          // プレイヤー死亡時のエネミーアニメーション
	r_enemy.c = 0;                 // 
	r_enemy.flg = FALSE;           // 

	// 初期位置を保存
	r_enemy.x = ENEMY_POS_X;
	r_enemy.y = ENEMY_POS_Y;

	//当たり判定
	r_enemy.recordX = r_enemy.x;
	r_enemy.recordY = r_enemy.y;

	r_enemy.top = ENEMY_POS_Y - ENEMY_POS_HITBOX;
	r_enemy.left = ENEMY_POS_X - ENEMY_POS_HITBOX;
	r_enemy.right = ENEMY_POS_X + ENEMY_POS_HITBOX;
	r_enemy.bottom = ENEMY_POS_Y + ENEMY_POS_HITBOX;

	r_enemy.recordTop = r_enemy.top;
	r_enemy.recordRight = r_enemy.right;
	r_enemy.recordBottom = r_enemy.bottom;
	r_enemy.recordLeft = r_enemy.left;

	// 分身の初期化処理
	//分身のフラグ処理
	r_enemy.Top = FALSE;
	r_enemy.Bottom = FALSE;
	r_enemy.Left = TRUE;
	r_enemy.Right = TRUE;
	//分身の座標
	//上
	r_enemy.ENEMY_AVATAR_POS_X[0] = ENEMY_POS_X;
	r_enemy.ENEMY_AVATAR_POS_Y[0] = ENEMY_POS_Y - 24;
	//右
	r_enemy.ENEMY_AVATAR_POS_X[1] = ENEMY_POS_X + 24;
	r_enemy.ENEMY_AVATAR_POS_Y[1] = ENEMY_POS_Y;
	//下
	r_enemy.ENEMY_AVATAR_POS_X[2] = ENEMY_POS_X;
	r_enemy.ENEMY_AVATAR_POS_Y[2] = ENEMY_POS_Y + 24;
	//左
	r_enemy.ENEMY_AVATAR_POS_X[3] = ENEMY_POS_X - 24;
	r_enemy.ENEMY_AVATAR_POS_Y[3] = ENEMY_POS_Y;

	// 前回のキー入力処理
	r_enemy.CheckNumber = 12;

	//分身の当たり判定
	for (int i = 0; i < 4; i++) {
		r_enemy.avatar_left[i] = ENEMY_AVATAR_POS_X[i] - ENEMY_POS_HITBOX;
		r_enemy.avatar_top[i] = ENEMY_AVATAR_POS_Y[i] - ENEMY_POS_HITBOX;
		r_enemy.avatar_right[i] = ENEMY_AVATAR_POS_X[i] + ENEMY_POS_HITBOX;
		r_enemy.avatar_bottom[i] = ENEMY_AVATAR_POS_Y[i] + ENEMY_POS_HITBOX;
	}
}

void R_ENEMY::Update() {
	//前回の座標取得
	r_enemy.recordX = r_enemy.x;
	r_enemy.recordY = r_enemy.y;

	r_enemy.recordTop = r_enemy.top;
	r_enemy.recordRight = r_enemy.right;
	r_enemy.recordBottom = r_enemy.bottom;
	r_enemy.recordLeft = r_enemy.left;

	//分身の座標
	for (int i = 0; i < 4; i++) {
		r_enemy.record_avatar_bottom[i] = r_enemy.avatar_bottom[i];
		r_enemy.record_avatar_left[i] = r_enemy.avatar_left[i];
		r_enemy.record_avatar_right[i] = r_enemy.avatar_right[i];
		r_enemy.record_avatar_top[i] = r_enemy.avatar_top[i];
	}

	// プレイヤーを追いかける処理
	if (r_enemy.R_Hitflg == FALSE && mStage.MoveFlg == TRUE && mPlayer.Hitflg == FALSE) { // パワーエサを取っていない時
		// 右向き
		if (r_enemy.angle == 2) {
			if (r_enemy.Right == TRUE) {
				if (mPlayer.x < r_enemy.x) { // 左向き
					r_enemy.angle = 4;
				}
				else if (mPlayer.y < r_enemy.y) { // 上向き
					r_enemy.angle = 1;
				}
				else if (mPlayer.y > r_enemy.y) { // 下向き
					r_enemy.angle = 3;
				}
			}
			else if (r_enemy.Right == FALSE) {
				if (mPlayer.x < r_enemy.x) { // 左向き
					if (r_enemy.Left == FALSE) {
						r_enemy.angle = 4;
					}
				}
				else if (mPlayer.y < r_enemy.y) { // 上向き
					if (r_enemy.Top == FALSE) {
						r_enemy.angle = 1;
					}
				}
				else if (mPlayer.y > r_enemy.y) { // 下向き
					if (r_enemy.Bottom == FALSE) {
						r_enemy.angle = 3;
					}
				}
				// 右向き
				r_enemy.x += r_enemy.speed;
				// 当たり判定
				r_enemy.left += r_enemy.speed;
				r_enemy.right += r_enemy.speed;
				//分身
				for (int i = 0; i < 4; i++) {
					r_enemy.avatar_right[i] += r_enemy.speed;
					r_enemy.avatar_left[i] += r_enemy.speed;
				}
				r_enemy.eyeimage = 1;
				//DrawString(0, 530, "右に進んでいます", 0xff00ff);
			}
		}
		// 左向き
		else if (r_enemy.angle == 4) {
			if (r_enemy.Left == TRUE) {
				if (mPlayer.x > r_enemy.x) { // 右向き
					r_enemy.angle = 2;
				}
				else if (mPlayer.y < r_enemy.y) { // 上向き
					r_enemy.angle = 1;
				}
				else if (mPlayer.y > r_enemy.y) { // 下向き
					r_enemy.angle = 3;
				}
			}
			else if (r_enemy.Left == FALSE) {
				if (mPlayer.x > r_enemy.x) { // 右向き
					if (r_enemy.Right == FALSE) {
						r_enemy.angle = 2;
					}
				}
				else if (mPlayer.y < r_enemy.y) { // 上向き
					if (r_enemy.Top == FALSE) {
						r_enemy.angle = 1;
					}
				}
				else if (mPlayer.y > r_enemy.y) { // 下向き
					if (r_enemy.Bottom == FALSE) {
						r_enemy.angle = 3;
					}
				}
				// 左向き
				r_enemy.x -= r_enemy.speed;
				//当たり判定
				r_enemy.left -= r_enemy.speed;
				r_enemy.right -= r_enemy.speed;
				//分身
				for (int i = 0; i < 4; i++) {
					r_enemy.avatar_right[i] -= r_enemy.speed;
					r_enemy.avatar_left[i] -= r_enemy.speed;
				}
				r_enemy.eyeimage = 3;
				//DrawString(0, 530, "左に進んでいます", 0xff00ff);
			}
		}
		//下向き
		else if (r_enemy.angle == 3) {
			if (r_enemy.Bottom == TRUE) {
				if (mPlayer.x > r_enemy.x) { // 右向き
					r_enemy.angle = 2;
				}
				else if (mPlayer.x < r_enemy.x) { // 左向き
					r_enemy.angle = 4;
				}
				else if (mPlayer.y < r_enemy.y) { // 上向き
					r_enemy.angle = 1;
				}
			}
			else if (r_enemy.Bottom == FALSE) {
				if (mPlayer.x > r_enemy.x) { // 右向き
					if (r_enemy.Right == FALSE) {
						r_enemy.angle = 2;
					}
				}
				else if (mPlayer.x < r_enemy.x) { // 左向き
					if (r_enemy.Left == FALSE) {
						r_enemy.angle = 4;
					}
				}
				else if (mPlayer.y < r_enemy.y) { // 上向き
					if (r_enemy.Top == FALSE) {
						r_enemy.angle = 1;
					}
				}
				//下向き
				r_enemy.y += r_enemy.speed;
				//当たり判定
				r_enemy.top += r_enemy.speed;
				r_enemy.bottom += r_enemy.speed;
				//分身
				for (int i = 0; i < 4; i++) {
					r_enemy.avatar_top[i] += r_enemy.speed;
					r_enemy.avatar_bottom[i] += r_enemy.speed;
				}
				r_enemy.eyeimage = 2;
				//DrawString(0, 530, "下に進んでいます", 0xff00ff);
			}
		}
		//上向き
		else if (r_enemy.angle == 1) {
			if (r_enemy.Top == TRUE) {
				if (mPlayer.x > r_enemy.x) { // 右向き
					r_enemy.angle = 2;
				}
				else if (mPlayer.x < r_enemy.x) { // 左向き
					r_enemy.angle = 4;
				}
				else if (mPlayer.y > r_enemy.y) { // 下向き
					r_enemy.angle = 3;
				}
			}
			else if (r_enemy.Top == FALSE) {
				if (mPlayer.x > r_enemy.x) { // 右向き
					if (r_enemy.Right == FALSE) {
						r_enemy.angle = 2;
					}
				}
				else if (mPlayer.x < r_enemy.x) { // 左向き
					if (r_enemy.Left == FALSE) {
						r_enemy.angle = 4;
					}
				}
				else if (mPlayer.y > r_enemy.y) { // 下向き
					if (r_enemy.Bottom == FALSE) {
						r_enemy.angle = 3;
					}
				}
				//上向き
				r_enemy.y -= r_enemy.speed;
				//当たり判定
				r_enemy.top -= r_enemy.speed;
				r_enemy.bottom -= r_enemy.speed;
				//分身
				for (int i = 0; i < 4; i++) {
					r_enemy.avatar_top[i] -= r_enemy.speed;
					r_enemy.avatar_bottom[i] -= r_enemy.speed;
				}
				r_enemy.eyeimage = 0;
				//DrawString(0, 530, "上に進んでいます", 0xff00ff);
			}
		}
	}
	else if (r_enemy.R_Hitflg == TRUE) { // パワーエサを取った時
		if (r_enemy.PR_Hitflg == FALSE) { // プレイヤーと当たっていなかったら
			r_enemy.speed = 0.8;
			// 右向き
			if (r_enemy.angle == 2) {
				if (r_enemy.Right == TRUE) {
					if (mPlayer.x < r_enemy.x) { // 左向き
						r_enemy.angle = 4;
					}
					else if (mPlayer.y < r_enemy.y) { // 上向き
						r_enemy.angle = 1;
					}
					else if (mPlayer.y > r_enemy.y) { // 下向き
						r_enemy.angle = 3;
					}
				}
				else if (r_enemy.Right == FALSE) {
					if (mPlayer.x < r_enemy.x) { // 左向き
						if (r_enemy.Left == FALSE) {
							r_enemy.angle = 4;
						}
					}
					else if (mPlayer.y < r_enemy.y) { // 上向き
						if (r_enemy.Top == FALSE) {
							r_enemy.angle = 1;
						}
					}
					else if (mPlayer.y > r_enemy.y) { // 下向き
						if (r_enemy.Bottom == FALSE) {
							r_enemy.angle = 3;
						}
					}
					// 右向き
					r_enemy.x -= r_enemy.speed;
					// 当たり判定
					r_enemy.left -= r_enemy.speed;
					r_enemy.right -= r_enemy.speed;
					//分身
					for (int i = 0; i < 4; i++) {
						r_enemy.avatar_right[i] -= r_enemy.speed;
						r_enemy.avatar_left[i] -= r_enemy.speed;
					}
					//DrawString(0, 550, "左に進んでいます", 0xff00ff);
				}
			}
			// 左向き
			else if (r_enemy.angle == 4) {
				if (r_enemy.Left == TRUE) {
					if (mPlayer.x > r_enemy.x) { // 右向き
						r_enemy.angle = 2;
					}
					else if (mPlayer.y < r_enemy.y) { // 上向き
						r_enemy.angle = 1;
					}
					else if (mPlayer.y > r_enemy.y) { // 下向き
						r_enemy.angle = 3;
					}
				}
				else if (r_enemy.Left == FALSE) {
					if (mPlayer.x > r_enemy.x) { // 右向き
						if (r_enemy.Right == FALSE) {
							r_enemy.angle = 2;
						}
					}
					else if (mPlayer.y < r_enemy.y) { // 上向き
						if (r_enemy.Top == FALSE) {
							r_enemy.angle = 1;
						}
					}
					else if (mPlayer.y > r_enemy.y) { // 下向き
						if (r_enemy.Bottom == FALSE) {
							r_enemy.angle = 3;
						}
					}
					// 左向き
					r_enemy.x += r_enemy.speed;
					//当たり判定
					r_enemy.left += r_enemy.speed;
					r_enemy.right += r_enemy.speed;
					//分身
					for (int i = 0; i < 4; i++) {
						r_enemy.avatar_right[i] += r_enemy.speed;
						r_enemy.avatar_left[i] += r_enemy.speed;
					}
					//DrawString(0, 550, "右に進んでいます", 0xff00ff);
				}
			}
			//下向き
			else if (r_enemy.angle == 3) {
				if (r_enemy.Bottom == TRUE) {
					if (mPlayer.x > r_enemy.x) { // 右向き
						r_enemy.angle = 2;
					}
					else if (mPlayer.x < r_enemy.x) { // 左向き
						r_enemy.angle = 4;
					}
					else if (mPlayer.y < r_enemy.y) { // 上向き
						r_enemy.angle = 1;
					}
				}
				else if (r_enemy.Bottom == FALSE) {
					if (mPlayer.x > r_enemy.x) { // 右向き
						if (r_enemy.Right == FALSE) {
							r_enemy.angle = 2;
						}
					}
					else if (mPlayer.x < r_enemy.x) { // 左向き
						if (r_enemy.Left == FALSE) {
							r_enemy.angle = 4;
						}
					}
					else if (mPlayer.y < r_enemy.y) { // 上向き
						if (r_enemy.Top == FALSE) {
							r_enemy.angle = 1;
						}
					}
					//下向き
					r_enemy.y -= r_enemy.speed;
					//当たり判定
					r_enemy.top -= r_enemy.speed;
					r_enemy.bottom -= r_enemy.speed;
					//分身
					for (int i = 0; i < 4; i++) {
						r_enemy.avatar_top[i] -= r_enemy.speed;
						r_enemy.avatar_bottom[i] -= r_enemy.speed;
					}
					//DrawString(0, 530, "上に進んでいます", 0xff00ff);
				}
			}
			//上向き
			else if (r_enemy.angle == 1) {
				if (r_enemy.Top == TRUE) {
					if (mPlayer.x > r_enemy.x) { // 右向き
						r_enemy.angle = 2;
					}
					else if (mPlayer.x < r_enemy.x) { // 左向き
						r_enemy.angle = 4;
					}
					else if (mPlayer.y > r_enemy.y) { // 下向き
						r_enemy.angle = 3;
					}
				}
				else if (r_enemy.Top == FALSE) {
					if (mPlayer.x > r_enemy.x) { // 右向き
						if (r_enemy.Right == FALSE) {
							r_enemy.angle = 2;
						}
					}
					else if (mPlayer.x < r_enemy.x) { // 左向き
						if (r_enemy.Left == FALSE) {
							r_enemy.angle = 4;
						}
					}
					else if (mPlayer.y > r_enemy.y) { // 下向き
						if (r_enemy.Bottom == FALSE) {
							r_enemy.angle = 3;
						}
					}
					//上向き
					r_enemy.y += r_enemy.speed;
					//当たり判定
					r_enemy.top += r_enemy.speed;
					r_enemy.bottom += r_enemy.speed;
					//分身
					for (int i = 0; i < 4; i++) {
						r_enemy.avatar_top[i] += r_enemy.speed;
						r_enemy.avatar_bottom[i] += r_enemy.speed;
					}
					//DrawString(0, 530, "下に進んでいます", 0xff00ff);
				}
			}
		}
		else if (r_enemy.PR_Hitflg == TRUE) { // プレイヤーと当たっていたら初期位置に戻る
			if (r_enemy.eyeflg == TRUE) {
				r_enemy.speed = 3;
				// 右向き
				if (r_enemy.angle == 2) {
					if (r_enemy.Right == TRUE) {
						if (ENEMY_POS_X < r_enemy.x) { // 左向き
							r_enemy.angle = 4;
						}
						else if (ENEMY_POS_Y < r_enemy.y) { // 上向き
							r_enemy.angle = 1;
						}
						else if (ENEMY_POS_Y > r_enemy.y) { // 下向き
							r_enemy.angle = 3;
						}
					}
					else if (r_enemy.Right == FALSE) {
						if (ENEMY_POS_X < r_enemy.x) { // 左向き
							if (r_enemy.Left == FALSE) {
								r_enemy.angle = 4;
							}
						}
						else if (ENEMY_POS_Y < r_enemy.y) { // 上向き
							if (r_enemy.Top == FALSE) {
								r_enemy.angle = 1;
							}
						}
						else if (ENEMY_POS_Y > r_enemy.y) { // 下向き
							if (r_enemy.Bottom == FALSE) {
								r_enemy.angle = 3;
							}
						}
						// 右向き
						r_enemy.x += r_enemy.speed;
						// 当たり判定
						r_enemy.left += r_enemy.speed;
						r_enemy.right += r_enemy.speed;
						//分身
						for (int i = 0; i < 4; i++) {
							r_enemy.avatar_right[i] += r_enemy.speed;
							r_enemy.avatar_left[i] += r_enemy.speed;
						}
						r_enemy.eyeimage = 1;
						//DrawString(0, 530, "右に進んでいます", 0xff00ff);
					}
				}
				// 左向き
				else if (r_enemy.angle == 4) {
					if (r_enemy.Left == TRUE) {
						if (ENEMY_POS_X > r_enemy.x) { // 右向き
							r_enemy.angle = 2;
						}
						else if (ENEMY_POS_Y < r_enemy.y) { // 上向き
							r_enemy.angle = 1;
						}
						else if (ENEMY_POS_Y > r_enemy.y) { // 下向き
							r_enemy.angle = 3;
						}
					}
					else if (r_enemy.Left == FALSE) {
						if (ENEMY_POS_X > r_enemy.x) { // 右向き
							if (r_enemy.Right == FALSE) {
								r_enemy.angle = 2;
							}
						}
						else if (ENEMY_POS_Y < r_enemy.y) { // 上向き
							if (r_enemy.Top == FALSE) {
								r_enemy.angle = 1;
							}
						}
						else if (ENEMY_POS_Y > r_enemy.y) { // 下向き
							if (r_enemy.Bottom == FALSE) {
								r_enemy.angle = 3;
							}
						}
						// 左向き
						r_enemy.x -= r_enemy.speed;
						//当たり判定
						r_enemy.left -= r_enemy.speed;
						r_enemy.right -= r_enemy.speed;
						//分身
						for (int i = 0; i < 4; i++) {
							r_enemy.avatar_right[i] -= r_enemy.speed;
							r_enemy.avatar_left[i] -= r_enemy.speed;
						}
						r_enemy.eyeimage = 3;
						//DrawString(0, 530, "左に進んでいます", 0xff00ff);
					}
				}
				//下向き
				else if (r_enemy.angle == 3) {
					if (r_enemy.Bottom == TRUE) {
						if (ENEMY_POS_X > r_enemy.x) { // 右向き
							r_enemy.angle = 2;
						}
						else if (ENEMY_POS_X < r_enemy.x) { // 左向き
							r_enemy.angle = 4;
						}
						else if (ENEMY_POS_Y < r_enemy.y) { // 上向き
							r_enemy.angle = 1;
						}
					}
					else if (r_enemy.Bottom == FALSE) {
						if (ENEMY_POS_X > r_enemy.x) { // 右向き
							if (r_enemy.Right == FALSE) {
								r_enemy.angle = 2;
							}
						}
						else if (ENEMY_POS_X < r_enemy.x) { // 左向き
							if (r_enemy.Left == FALSE) {
								r_enemy.angle = 4;
							}
						}
						else if (ENEMY_POS_Y < r_enemy.y) { // 上向き
							if (r_enemy.Top == FALSE) {
								r_enemy.angle = 1;
							}
						}
						//下向き
						r_enemy.y += r_enemy.speed;
						//当たり判定
						r_enemy.top += r_enemy.speed;
						r_enemy.bottom += r_enemy.speed;
						//分身
						for (int i = 0; i < 4; i++) {
							r_enemy.avatar_top[i] += r_enemy.speed;
							r_enemy.avatar_bottom[i] += r_enemy.speed;
						}
						r_enemy.eyeimage = 2;
						//DrawString(0, 530, "下に進んでいます", 0xff00ff);
					}
				}
				//上向き
				else if (r_enemy.angle == 1) {
					if (r_enemy.Top == TRUE) {
						if (ENEMY_POS_X > r_enemy.x) { // 右向き
							r_enemy.angle = 2;
						}
						else if (ENEMY_POS_X < r_enemy.x) { // 左向き
							r_enemy.angle = 4;
						}
						else if (ENEMY_POS_Y > r_enemy.y) { // 下向き
							r_enemy.angle = 3;
						}
					}
					else if (r_enemy.Top == FALSE) {
						if (ENEMY_POS_X > r_enemy.x) { // 右向き
							if (r_enemy.Right == FALSE) {
								r_enemy.angle = 2;
							}
						}
						else if (ENEMY_POS_X < r_enemy.x) { // 左向き
							if (r_enemy.Left == FALSE) {
								r_enemy.angle = 4;
							}
						}
						else if (ENEMY_POS_Y > r_enemy.y) { // 下向き
							if (r_enemy.Bottom == FALSE) {
								r_enemy.angle = 3;
							}
						}
						//上向き
						r_enemy.y -= r_enemy.speed;
						//当たり判定
						r_enemy.top -= r_enemy.speed;
						r_enemy.bottom -= r_enemy.speed;
						//分身
						for (int i = 0; i < 4; i++) {
							r_enemy.avatar_top[i] -= r_enemy.speed;
							r_enemy.avatar_bottom[i] -= r_enemy.speed;
						}
						r_enemy.eyeimage = 0;
						//DrawString(0, 530, "上に進んでいます", 0xff00ff);
					}
				}
				// 初期位置に戻った時
				if (ENEMY_POS_X == r_enemy.x + 1) {
					r_enemy.eyeflg = FALSE;
					r_enemy.speed = 1;
				}
			}
		}
	}

	// エネミーとプレイヤーの当たり判定
	if (EnemeyCheckHit(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom)) {
		if (r_enemy.R_Hitflg == TRUE || r_enemy.ER_Hitflg == TRUE) { // イジケ状態で当たったら
			r_enemy.PR_Hitflg = TRUE;
			r_enemy.eyeflg = TRUE;
		}
	}

	// アニメーション
	++r_enemy.count;  // カウント開始
	if (r_enemy.count >= 8) {  // 値によってアニメーションのスピードが変化する0に近い程速い
		r_enemy.image++;
		r_enemy.izikeimage++;
		r_enemy.e_izikeimage++;
		r_enemy.count = 0;  // カウントリセット
	}
	if (r_enemy.R_Hitflg == FALSE) { // もしイジケ状態でなければ
		if (r_enemy.image >= 2) { // 通常の画像切り替え
			r_enemy.image = 0;    // 画像リセット
		}
	}
	else if (r_enemy.R_Hitflg == TRUE) { // もしイジケ状態なら
		if (r_enemy.izikeimage >= 18) { // イジケ画像切り替え
			r_enemy.izikeimage = 16; // 画像リセット
		}
	}
	if (r_enemy.ER_Hitflg == TRUE) { // もしイジケ状態が終わりそうなら
		if (r_enemy.e_izikeimage >= 20) { // イジケ点滅画像切り替え
			r_enemy.e_izikeimage = 16; // 画像リセット
		}
	}

	// ワープトンネル
	if (r_enemy.x >= 878) {
		r_enemy.x = 352;

		//分身
		//上
		r_enemy.avatar_right[0] = 352 + ENEMY_POS_HITBOX;
		r_enemy.avatar_left[0] = 352 - ENEMY_POS_HITBOX;
		//下
		r_enemy.avatar_left[2] = 352 - ENEMY_POS_HITBOX;
		r_enemy.avatar_right[2] = 352 + ENEMY_POS_HITBOX;
		//右
		r_enemy.avatar_left[1] = 352 + 24 - ENEMY_POS_HITBOX;
		r_enemy.avatar_right[1] = 352 + 24 + ENEMY_POS_HITBOX;
		//左
		r_enemy.avatar_right[3] = 352 - 24 - ENEMY_POS_HITBOX;
		r_enemy.avatar_left[3] = 352 - 24 + ENEMY_POS_HITBOX;
	}
	else if (r_enemy.x <= 352) {
		r_enemy.x = 878;

		//分身
		//上
		r_enemy.avatar_right[0] = 878 + ENEMY_POS_HITBOX;
		r_enemy.avatar_left[0] = 878 - ENEMY_POS_HITBOX;
		//下
		r_enemy.avatar_left[2] = 878 - ENEMY_POS_HITBOX;
		r_enemy.avatar_right[2] = 878 + ENEMY_POS_HITBOX;
		//右
		r_enemy.avatar_left[1] = 878 + 24 - ENEMY_POS_HITBOX;
		r_enemy.avatar_right[1] = 878 + 24 + ENEMY_POS_HITBOX;
		//左
		r_enemy.avatar_right[3] = 878 - 24 - ENEMY_POS_HITBOX;
		r_enemy.avatar_left[3] = 878 - 24 + ENEMY_POS_HITBOX;
	}

	// イジケ状態フラグ
	if (r_enemy.R_Hitflg == TRUE) {
		++r_enemy.ER_count;
	}
	// プレイヤー死亡時のエネミーアニメーション
	if (mPlayer.Hitflg == TRUE) {
		r_enemy.HitCount++;
		int a = 5; int b = 10;
		if (r_enemy.HitCount == a ) {
			r_enemy.image = 0;
			a += 5;
		}
		else if (r_enemy.HitCount == b) {
			r_enemy.image = 1;
			b += 5;
		}
		if (r_enemy.HitCount == 80) {
			flg = TRUE;
		}
	}
}

void R_ENEMY::Draw() {
	//足だけが動く処理
	if (mPlayer.Hitflg == TRUE && flg == FALSE) {
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, r_enemy.images[r_enemy.image], TRUE, FALSE);
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, r_enemy.eyesimages[r_enemy.eyeimage], TRUE, FALSE);
	}
	//PCに当たったときに消える
	if (flg == TRUE) {
		/*DrawRotaGraph(r_enemy.x, r_enemy.y, 0, 0, images[r_enemy.image], TRUE, FALSE); 
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE); */
	}
	//スタートの時のみ非表示
	if (mStage.StateFlg == FALSE || mStage.GameOverFlg == TRUE) {
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0, 0, r_enemy.images[r_enemy.image], TRUE, FALSE);
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0, 0, r_enemy.eyesimages[r_enemy.eyeimage], TRUE, FALSE);
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0, 0, r_enemy.images[r_enemy.izikeimage], TRUE, FALSE);
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0, 0, r_enemy.images[r_enemy.e_izikeimage], TRUE, FALSE);
	}
	//スタート時の固定表示
	else if (mStage.StateFlg == TRUE){
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[0], TRUE, FALSE); 
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, eyesimages[3], TRUE, FALSE); 
	}
	// パワーエサを取っていないかつ、Moveflgで動いて可能かつ、Pacに当たっていない時
	if (r_enemy.R_Hitflg == FALSE && mStage.MoveFlg == TRUE && mPlayer.Hitflg == FALSE) {
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[r_enemy.image], TRUE, FALSE); // 敵キャラ表示
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE); // 敵キャラの目表示
		//DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
		//DrawString(0, 150, "パワーエサ：無し", 0x0000ff);
	}
	else if (r_enemy.R_Hitflg == TRUE) { // パワーエサを取っていたら
		if (r_enemy.PR_Hitflg == FALSE) { // プレイヤーと当たっていなければ
			if (r_enemy.ER_count <= 480) {
				DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, r_enemy.images[r_enemy.izikeimage], TRUE, FALSE); // イジケ状態表示
				//DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
				//DrawString(0, 150, "パワーエサ：あり：10秒カウント", 0x0000ff);
			}
			else if (r_enemy.ER_count > 480 && r_enemy.ER_count <= 600) {
				r_enemy.ER_Hitflg = TRUE;
				DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, r_enemy.images[r_enemy.e_izikeimage], TRUE, FALSE); // イジケ状態表示
				//DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
				//DrawString(0, 150, "パワーエサ：あり：残り2秒", 0x0000ff);
			}
			else {
				r_enemy.R_Hitflg = FALSE;
				r_enemy.ER_Hitflg = FALSE;
				r_enemy.ER_count = 0;
				mPlayer.timercount = 0;
			}
		}
		else if (r_enemy.PR_Hitflg == TRUE) { // プレイヤーと当たっていたら
			if (r_enemy.eyeflg == TRUE) { // 目状態になったら
				DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, r_enemy.eyesimages[r_enemy.eyeimage], TRUE, FALSE); // 敵キャラの目表示
				//DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
				//DrawString(0, 150, "パワーエサ：あり：プレイヤーと接触", 0x0000ff);
			}
			else if (r_enemy.eyeflg == FALSE) { // 目状態のエネミーが初期位置に戻ったら
				r_enemy.R_Hitflg = FALSE;
				r_enemy.PR_Hitflg = FALSE;
				r_enemy.ER_Hitflg = FALSE;
				r_enemy.ER_count = 0;
				mPlayer.timercount = 0;
				//DrawString(0, 150, "パワーエサ：無し：初期位置に戻りました", 0x0000ff);
			}
		}
	}

	if (r_enemy.Initiaflg == TRUE) {
		// 初期位置に戻す
		r_enemy.x = ENEMY_POS_X;
		r_enemy.y = ENEMY_POS_Y;
		r_enemy.top = ENEMY_POS_Y - ENEMY_POS_HITBOX;
		r_enemy.left = ENEMY_POS_X - ENEMY_POS_HITBOX;
		r_enemy.right = ENEMY_POS_X + ENEMY_POS_HITBOX;
		r_enemy.bottom = ENEMY_POS_Y + ENEMY_POS_HITBOX;
		r_enemy.Initiaflg = FALSE;

		//分身の当たり判定
		for (int i = 0; i < 4; i++) {
			r_enemy.avatar_left[i] = ENEMY_AVATAR_POS_X[i] - ENEMY_POS_HITBOX;
			r_enemy.avatar_top[i] = ENEMY_AVATAR_POS_Y[i] - ENEMY_POS_HITBOX;
			r_enemy.avatar_right[i] = ENEMY_AVATAR_POS_X[i] + ENEMY_POS_HITBOX;
			r_enemy.avatar_bottom[i] = ENEMY_AVATAR_POS_Y[i] + ENEMY_POS_HITBOX;
		}

		r_enemy.flg = FALSE;
		r_enemy.HitCount = 0;

		if (mStage.life == 2) {
			//mStage.life = 1;
			mStage.GameOverFlg = TRUE;
		}
		/*else if(mStage.life == 1) {
			mStage.life = 0;
		}
		else if(mStage.life == 0){
			mStage.GameOverFlg = TRUE;
		}*/
	}

	////分身の表示
	//for (int i = 0; i < 4; i++) {
	//	DrawBox(r_enemy.avatar_left[i], r_enemy.avatar_top[i], r_enemy.avatar_right[i], r_enemy.avatar_bottom[i], 0x00ffff, FALSE);
	//}

	/*if (r_enemy.Top == FALSE) {
		DrawString(0, 410, "上成功", 0xff00ff);
	}
	if (r_enemy.Right == FALSE) {
		DrawString(0, 430, "右成功", 0xff00ff);
	}
	if (r_enemy.Bottom == FALSE) {
		DrawString(0, 450, "下成功", 0xff00ff);
	}
	if (r_enemy.Left == FALSE) {
		DrawString(0, 470, "左成功", 0xff00ff);
	}

	if (r_enemy.angle == 1) {
		DrawString(0, 510, "現在のアングルは上です", 0xff00ff);
	}
	else if (r_enemy.angle == 2) {
		DrawString(0, 510, "現在のアングルは右です", 0xff00ff);
	}
	else if (r_enemy.angle == 3) {
		DrawString(0, 510, "現在のアングルは下です", 0xff00ff);
	}
	else if (r_enemy.angle == 4) {
		DrawString(0, 510, "現在のアングルは左です", 0xff00ff);
	}*/

	////進める時
	////上
	//if (r_enemy.Top == TRUE) {
	//	DrawBox(r_enemy.avatar_left[0], r_enemy.avatar_top[0], r_enemy.avatar_right[0], r_enemy.avatar_bottom[0], 0xff00ff, true);
	//}
	//else if (r_enemy.Top == FALSE) {
	//	DrawBox(r_enemy.avatar_left[0], r_enemy.avatar_top[0], r_enemy.avatar_right[0], r_enemy.avatar_bottom[0], 0xff0000, true);
	//}
	////右
	//if (r_enemy.Right == TRUE) {
	//	DrawBox(r_enemy.avatar_left[1], r_enemy.avatar_top[1], r_enemy.avatar_right[1], r_enemy.avatar_bottom[1], 0xff00ff, true);
	//}
	//else if (r_enemy.Right == FALSE) {
	//	DrawBox(r_enemy.avatar_left[1], r_enemy.avatar_top[1], r_enemy.avatar_right[1], r_enemy.avatar_bottom[1], 0xff0000, true);
	//}
	////下
	//if (r_enemy.Bottom == TRUE) {
	//	DrawBox(r_enemy.avatar_left[2], r_enemy.avatar_top[2], r_enemy.avatar_right[2], r_enemy.avatar_bottom[2], 0xff00ff, true);
	//}
	//else if (r_enemy.Bottom == FALSE) {
	//	DrawBox(r_enemy.avatar_left[2], r_enemy.avatar_top[2], r_enemy.avatar_right[2], r_enemy.avatar_bottom[2], 0xff0000, true);
	//}
	////左
	//if (r_enemy.Left == TRUE) {
	//	DrawBox(r_enemy.avatar_left[3], r_enemy.avatar_top[3], r_enemy.avatar_right[3], r_enemy.avatar_bottom[3], 0xff00ff, true);
	//}
	//else if (r_enemy.Left == FALSE) {
	//	DrawBox(r_enemy.avatar_left[3], r_enemy.avatar_top[3], r_enemy.avatar_right[3], r_enemy.avatar_bottom[3], 0xff0000, true);
	//}
}