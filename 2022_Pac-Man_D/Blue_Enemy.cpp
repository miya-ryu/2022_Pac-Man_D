#include "DxLib.h"
#include "Blue_Enemy.h"
#include "Player.h"
#include <math.h>
#include "Stage.h"

B_ENEMY b_enemy;

int B_EnemeyCheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
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

void B_ENEMY::Initialize() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);  // 敵キャラ
	LoadDivGraph("images/eyes.png", 4, 4, 1, 32, 32, eyesimages);  // 敵キャラの目

	b_enemy.speed = 1;             // 移動速度
	b_enemy.angle = 4;             // 初期の向き
	b_enemy.count = 0;             // アニメーションカウント
	b_enemy.ER_count = 0;          // イジケ状態カウント
	b_enemy.image = 4;             // 画像変数
	b_enemy.eyeimage = 3;          // 目の画像変数
	b_enemy.izikeimage = 16;       // イジケ状態の画像変数
	b_enemy.e_izikeimage = 16;     // イジケ状態点滅の画像変数
	//b_enemy.E_StageHitflg = FALSE; // 壁との当たり判定フラグ
	b_enemy.R_Hitflg = FALSE;      // イジケ状態判定フラグ
	b_enemy.ER_Hitflg = FALSE;     // イジケ状態点滅フラグ
	b_enemy.PR_Hitflg = FALSE;     // イジケ状態でプレイヤーに当たった時のフラグ
	b_enemy.eyeflg = FALSE;        // エネミー目状態
	b_enemy.Initiaflg = FALSE;     // エネミー初期化

	// 初期位置を保存
	b_enemy.x = B_ENEMY_POS_X;
	b_enemy.y = B_ENEMY_POS_Y;

	//当たり判定
	b_enemy.recordX = b_enemy.x;
	b_enemy.recordY = b_enemy.y;

	b_enemy.top = B_ENEMY_POS_Y - B_ENEMY_POS_HITBOX;
	b_enemy.left = B_ENEMY_POS_X - B_ENEMY_POS_HITBOX;
	b_enemy.right = B_ENEMY_POS_X + B_ENEMY_POS_HITBOX;
	b_enemy.bottom = B_ENEMY_POS_Y + B_ENEMY_POS_HITBOX;

	b_enemy.recordTop = b_enemy.top;
	b_enemy.recordRight = b_enemy.right;
	b_enemy.recordBottom = b_enemy.bottom;
	b_enemy.recordLeft = b_enemy.left;

	// 分身の初期化処理
	//分身のフラグ処理
	b_enemy.Top = FALSE;
	b_enemy.Bottom = FALSE;
	b_enemy.Left = TRUE;
	b_enemy.Right = TRUE;
	//分身の座標
	//上
	b_enemy.ENEMY_AVATAR_POS_X[0] = B_ENEMY_POS_X;
	b_enemy.ENEMY_AVATAR_POS_Y[0] = B_ENEMY_POS_Y - 24;
	//右
	b_enemy.ENEMY_AVATAR_POS_X[1] = B_ENEMY_POS_X + 24;
	b_enemy.ENEMY_AVATAR_POS_Y[1] = B_ENEMY_POS_Y;
	//下
	b_enemy.ENEMY_AVATAR_POS_X[2] = B_ENEMY_POS_X;
	b_enemy.ENEMY_AVATAR_POS_Y[2] = B_ENEMY_POS_Y + 24;
	//左
	b_enemy.ENEMY_AVATAR_POS_X[3] = B_ENEMY_POS_X - 24;
	b_enemy.ENEMY_AVATAR_POS_Y[3] = B_ENEMY_POS_Y;

	// 前回のキー入力処理
	b_enemy.CheckNumber = 12;

	//分身の当たり判定
	for (int i = 0; i < 4; i++) {
		b_enemy.avatar_left[i] = ENEMY_AVATAR_POS_X[i] - B_ENEMY_POS_HITBOX;
		b_enemy.avatar_top[i] = ENEMY_AVATAR_POS_Y[i] - B_ENEMY_POS_HITBOX;
		b_enemy.avatar_right[i] = ENEMY_AVATAR_POS_X[i] + B_ENEMY_POS_HITBOX;
		b_enemy.avatar_bottom[i] = ENEMY_AVATAR_POS_Y[i] + B_ENEMY_POS_HITBOX;
	}
}

void B_ENEMY::Update() {
	//前回の座標取得
	b_enemy.recordX = b_enemy.x;
	b_enemy.recordY = b_enemy.y;

	b_enemy.recordTop = b_enemy.top;
	b_enemy.recordRight = b_enemy.right;
	b_enemy.recordBottom = b_enemy.bottom;
	b_enemy.recordLeft = b_enemy.left;

	//前回の座標移動
	b_enemy.absX = mPlayer.x - b_enemy.x;
	b_enemy.absY = mPlayer.y - b_enemy.y;

	//絶対値を求める
	if (b_enemy.absX <= 0) {
		b_enemy.absX = b_enemy.absX * -1;
	}
	if (b_enemy.absY <= 0) {
		b_enemy.absY = b_enemy.absY * -1;
	}

	//分身の座標
	for (int i = 0; i < 4; i++) {
		b_enemy.record_avatar_bottom[i] = b_enemy.avatar_bottom[i];
		b_enemy.record_avatar_left[i] = b_enemy.avatar_left[i];
		b_enemy.record_avatar_right[i] = b_enemy.avatar_right[i];
		b_enemy.record_avatar_top[i] = b_enemy.avatar_top[i];
	}

	// プレイヤーを追いかける処理
	if (b_enemy.R_Hitflg == FALSE) { // パワーエサを取っていない時
		b_enemy.speed = 1;
		// 右向き
		if (b_enemy.angle == 2) {
			if (b_enemy.Right == TRUE) {
				if (mPlayer.x < b_enemy.x) { // 左向き
					b_enemy.angle = 4;
				}
				else if (mPlayer.y < b_enemy.y) { // 上向き
					b_enemy.angle = 1;
				}
				else if (mPlayer.y > b_enemy.y) { // 下向き
					b_enemy.angle = 3;
				}
			}
			else if (b_enemy.Right == FALSE) {
				if (mPlayer.x < b_enemy.x) { // 左向き
					if (b_enemy.Left == FALSE) {
						b_enemy.angle = 4;
					}
				}
				else if (mPlayer.y < b_enemy.y) { // 上向き
					if (b_enemy.Top == FALSE) {
						b_enemy.angle = 1;
					}
				}
				else if (mPlayer.y > b_enemy.y) { // 下向き
					if (b_enemy.Bottom == FALSE) {
						b_enemy.angle = 3;
					}
				}
				// 右向き
				b_enemy.x += b_enemy.speed;
				// 当たり判定
				b_enemy.left += b_enemy.speed;
				b_enemy.right += b_enemy.speed;
				//分身
				for (int i = 0; i < 4; i++) {
					b_enemy.avatar_right[i] += b_enemy.speed;
					b_enemy.avatar_left[i] += b_enemy.speed;
				}
				b_enemy.eyeimage = 1;
			}
		}
		// 左向き
		else if (b_enemy.angle == 4) {
			if (b_enemy.Left == TRUE) {
				if (mPlayer.x > b_enemy.x) { // 右向き
					b_enemy.angle = 2;
				}
				else if (mPlayer.y < b_enemy.y) { // 上向き
					b_enemy.angle = 1;
				}
				else if (mPlayer.y > b_enemy.y) { // 下向き
					b_enemy.angle = 3;
				}
			}
			else if (b_enemy.Left == FALSE) {
				if (mPlayer.x > b_enemy.x) { // 右向き
					if (b_enemy.Right == FALSE) {
						b_enemy.angle = 2;
					}
				}
				else if (mPlayer.y < b_enemy.y) { // 上向き
					if (b_enemy.Top == FALSE) {
						b_enemy.angle = 1;
					}
				}
				else if (mPlayer.y > b_enemy.y) { // 下向き
					if (b_enemy.Bottom == FALSE) {
						b_enemy.angle = 3;
					}
				}
				// 左向き
				b_enemy.x -= b_enemy.speed;
				//当たり判定
				b_enemy.left -= b_enemy.speed;
				b_enemy.right -= b_enemy.speed;
				//分身
				for (int i = 0; i < 4; i++) {
					b_enemy.avatar_right[i] -= b_enemy.speed;
					b_enemy.avatar_left[i] -= b_enemy.speed;
				}
				b_enemy.eyeimage = 3;
			}
		}
		//下向き
		else if (b_enemy.angle == 3) {
			if (b_enemy.Bottom == TRUE) {
				if (mPlayer.x > b_enemy.x) { // 右向き
					b_enemy.angle = 2;
				}
				else if (mPlayer.x < b_enemy.x) { // 左向き
					b_enemy.angle = 4;
				}
				else if (mPlayer.y < b_enemy.y) { // 上向き
					b_enemy.angle = 1;
				}
			}
			else if (b_enemy.Bottom == FALSE) {
				if (mPlayer.x > b_enemy.x) { // 右向き
					if (b_enemy.Right == FALSE) {
						b_enemy.angle = 2;
					}
				}
				else if (mPlayer.x < b_enemy.x) { // 左向き
					if (b_enemy.Left == FALSE) {
						b_enemy.angle = 4;
					}
				}
				else if (mPlayer.y < b_enemy.y) { // 上向き
					if (b_enemy.Top == FALSE) {
						b_enemy.angle = 1;
					}
				}
				//下向き
				b_enemy.y += b_enemy.speed;
				//当たり判定
				b_enemy.top += b_enemy.speed;
				b_enemy.bottom += b_enemy.speed;
				//分身
				for (int i = 0; i < 4; i++) {
					b_enemy.avatar_top[i] += b_enemy.speed;
					b_enemy.avatar_bottom[i] += b_enemy.speed;
				}
				b_enemy.eyeimage = 2;
			}
		}
		//上向き
		else if (b_enemy.angle == 1) {
			if (b_enemy.Top == TRUE) {
				if (mPlayer.x > b_enemy.x) { // 右向き
					b_enemy.angle = 2;
				}
				else if (mPlayer.x < b_enemy.x) { // 左向き
					b_enemy.angle = 4;
				}
				else if (mPlayer.y > b_enemy.y) { // 下向き
					b_enemy.angle = 3;
				}
			}
			else if (b_enemy.Top == FALSE) {
				if (mPlayer.x > b_enemy.x) { // 右向き
					if (b_enemy.Right == FALSE) {
						b_enemy.angle = 2;
					}
				}
				else if (mPlayer.x < b_enemy.x) { // 左向き
					if (b_enemy.Left == FALSE) {
						b_enemy.angle = 4;
					}
				}
				else if (mPlayer.y > b_enemy.y) { // 下向き
					if (b_enemy.Bottom == FALSE) {
						b_enemy.angle = 3;
					}
				}
				//上向き
				b_enemy.y -= b_enemy.speed;
				//当たり判定
				b_enemy.top -= b_enemy.speed;
				b_enemy.bottom -= b_enemy.speed;
				//分身
				for (int i = 0; i < 4; i++) {
					b_enemy.avatar_top[i] -= b_enemy.speed;
					b_enemy.avatar_bottom[i] -= b_enemy.speed;
				}
				b_enemy.eyeimage = 0;
			}
		}
	}
	else if (b_enemy.R_Hitflg == TRUE) { // パワーエサを取った時
		if (b_enemy.PR_Hitflg == FALSE) { // プレイヤーと当たっていなかったら
			b_enemy.speed = 1.6;
			// 右向き
			if (b_enemy.angle == 2) {
				if (b_enemy.Right == TRUE) {
					if (mPlayer.x < b_enemy.x) { // 左向き
						b_enemy.angle = 4;
					}
					else if (mPlayer.y < b_enemy.y) { // 上向き
						b_enemy.angle = 1;
					}
					else if (mPlayer.y > b_enemy.y) { // 下向き
						b_enemy.angle = 3;
					}
				}
				else if (b_enemy.Right == FALSE) {
					if (mPlayer.x < b_enemy.x) { // 左向き
						if (b_enemy.Left == FALSE) {
							b_enemy.angle = 4;
						}
					}
					else if (mPlayer.y < b_enemy.y) { // 上向き
						if (b_enemy.Top == FALSE) {
							b_enemy.angle = 1;
						}
					}
					else if (mPlayer.y > b_enemy.y) { // 下向き
						if (b_enemy.Bottom == FALSE) {
							b_enemy.angle = 3;
						}
					}
					// 右向き
					b_enemy.x -= b_enemy.speed;
					// 当たり判定
					b_enemy.left -= b_enemy.speed;
					b_enemy.right -= b_enemy.speed;
					//分身
					for (int i = 0; i < 4; i++) {
						b_enemy.avatar_right[i] -= b_enemy.speed;
						b_enemy.avatar_left[i] -= b_enemy.speed;
					}
				}
			}
			// 左向き
			else if (b_enemy.angle == 4) {
				if (b_enemy.Left == TRUE) {
					if (mPlayer.x > b_enemy.x) { // 右向き
						b_enemy.angle = 2;
					}
					else if (mPlayer.y < b_enemy.y) { // 上向き
						b_enemy.angle = 1;
					}
					else if (mPlayer.y > b_enemy.y) { // 下向き
						b_enemy.angle = 3;
					}
				}
				else if (b_enemy.Left == FALSE) {
					if (mPlayer.x > b_enemy.x) { // 右向き
						if (b_enemy.Right == FALSE) {
							b_enemy.angle = 2;
						}
					}
					else if (mPlayer.y < b_enemy.y) { // 上向き
						if (b_enemy.Top == FALSE) {
							b_enemy.angle = 1;
						}
					}
					else if (mPlayer.y > b_enemy.y) { // 下向き
						if (b_enemy.Bottom == FALSE) {
							b_enemy.angle = 3;
						}
					}
					// 左向き
					b_enemy.x += b_enemy.speed;
					//当たり判定
					b_enemy.left += b_enemy.speed;
					b_enemy.right += b_enemy.speed;
					//分身
					for (int i = 0; i < 4; i++) {
						b_enemy.avatar_right[i] += b_enemy.speed;
						b_enemy.avatar_left[i] += b_enemy.speed;
					}
				}
			}
			//下向き
			else if (b_enemy.angle == 3) {
				if (b_enemy.Bottom == TRUE) {
					if (mPlayer.x > b_enemy.x) { // 右向き
						b_enemy.angle = 2;
					}
					else if (mPlayer.x < b_enemy.x) { // 左向き
						b_enemy.angle = 4;
					}
					else if (mPlayer.y < b_enemy.y) { // 上向き
						b_enemy.angle = 1;
					}
				}
				else if (b_enemy.Bottom == FALSE) {
					if (mPlayer.x > b_enemy.x) { // 右向き
						if (b_enemy.Right == FALSE) {
							b_enemy.angle = 2;
						}
					}
					else if (mPlayer.x < b_enemy.x) { // 左向き
						if (b_enemy.Left == FALSE) {
							b_enemy.angle = 4;
						}
					}
					else if (mPlayer.y < b_enemy.y) { // 上向き
						if (b_enemy.Top == FALSE) {
							b_enemy.angle = 1;
						}
					}
					//下向き
					b_enemy.y -= b_enemy.speed;
					//当たり判定
					b_enemy.top -= b_enemy.speed;
					b_enemy.bottom -= b_enemy.speed;
					//分身
					for (int i = 0; i < 4; i++) {
						b_enemy.avatar_top[i] -= b_enemy.speed;
						b_enemy.avatar_bottom[i] -= b_enemy.speed;
					}
				}
			}
			//上向き
			else if (b_enemy.angle == 1) {
				if (b_enemy.Top == TRUE) {
					if (mPlayer.x > b_enemy.x) { // 右向き
						b_enemy.angle = 2;
					}
					else if (mPlayer.x < b_enemy.x) { // 左向き
						b_enemy.angle = 4;
					}
					else if (mPlayer.y > b_enemy.y) { // 下向き
						b_enemy.angle = 3;
					}
				}
				else if (b_enemy.Top == FALSE) {
					if (mPlayer.x > b_enemy.x) { // 右向き
						if (b_enemy.Right == FALSE) {
							b_enemy.angle = 2;
						}
					}
					else if (mPlayer.x < b_enemy.x) { // 左向き
						if (b_enemy.Left == FALSE) {
							b_enemy.angle = 4;
						}
					}
					else if (mPlayer.y > b_enemy.y) { // 下向き
						if (b_enemy.Bottom == FALSE) {
							b_enemy.angle = 3;
						}
					}
					//上向き
					b_enemy.y += b_enemy.speed;
					//当たり判定
					b_enemy.top += b_enemy.speed;
					b_enemy.bottom += b_enemy.speed;
					//分身
					for (int i = 0; i < 4; i++) {
						b_enemy.avatar_top[i] += b_enemy.speed;
						b_enemy.avatar_bottom[i] += b_enemy.speed;
					}
				}
			}
		}
		else if (b_enemy.PR_Hitflg == TRUE) { // プレイヤーと当たっていたら初期位置に戻る
			if (b_enemy.eyeflg == TRUE) {
				b_enemy.speed = 3;
				// 右向き
				if (b_enemy.angle == 2) {
					if (b_enemy.Right == TRUE) {
						if (ENEMY_POS_X < b_enemy.x) { // 左向き
							b_enemy.angle = 4;
						}
						else if (ENEMY_POS_Y < b_enemy.y) { // 上向き
							b_enemy.angle = 1;
						}
						else if (ENEMY_POS_Y > b_enemy.y) { // 下向き
							b_enemy.angle = 3;
						}
					}
					else if (b_enemy.Right == FALSE) {
						if (ENEMY_POS_X < b_enemy.x) { // 左向き
							if (b_enemy.Left == FALSE) {
								b_enemy.angle = 4;
							}
						}
						else if (ENEMY_POS_Y < b_enemy.y) { // 上向き
							if (b_enemy.Top == FALSE) {
								b_enemy.angle = 1;
							}
						}
						else if (ENEMY_POS_Y > b_enemy.y) { // 下向き
							if (b_enemy.Bottom == FALSE) {
								b_enemy.angle = 3;
							}
						}
						// 右向き
						b_enemy.x += b_enemy.speed;
						// 当たり判定
						b_enemy.left += b_enemy.speed;
						b_enemy.right += b_enemy.speed;
						//分身
						for (int i = 0; i < 4; i++) {
							b_enemy.avatar_right[i] += b_enemy.speed;
							b_enemy.avatar_left[i] += b_enemy.speed;
						}
						b_enemy.eyeimage = 1;
					}
				}
				// 左向き
				else if (b_enemy.angle == 4) {
					if (b_enemy.Left == TRUE) {
						if (ENEMY_POS_X > b_enemy.x) { // 右向き
							b_enemy.angle = 2;
						}
						else if (ENEMY_POS_Y < b_enemy.y) { // 上向き
							b_enemy.angle = 1;
						}
						else if (ENEMY_POS_Y > b_enemy.y) { // 下向き
							b_enemy.angle = 3;
						}
					}
					else if (b_enemy.Left == FALSE) {
						if (ENEMY_POS_X > b_enemy.x) { // 右向き
							if (b_enemy.Right == FALSE) {
								b_enemy.angle = 2;
							}
						}
						else if (ENEMY_POS_Y < b_enemy.y) { // 上向き
							if (b_enemy.Top == FALSE) {
								b_enemy.angle = 1;
							}
						}
						else if (ENEMY_POS_Y > b_enemy.y) { // 下向き
							if (b_enemy.Bottom == FALSE) {
								b_enemy.angle = 3;
							}
						}
						// 左向き
						b_enemy.x -= b_enemy.speed;
						//当たり判定
						b_enemy.left -= b_enemy.speed;
						b_enemy.right -= b_enemy.speed;
						//分身
						for (int i = 0; i < 4; i++) {
							b_enemy.avatar_right[i] -= b_enemy.speed;
							b_enemy.avatar_left[i] -= b_enemy.speed;
						}
						b_enemy.eyeimage = 3;
					}
				}
				//下向き
				else if (b_enemy.angle == 3) {
					if (b_enemy.Bottom == TRUE) {
						if (ENEMY_POS_X > b_enemy.x) { // 右向き
							b_enemy.angle = 2;
						}
						else if (ENEMY_POS_X < b_enemy.x) { // 左向き
							b_enemy.angle = 4;
						}
						else if (ENEMY_POS_Y < b_enemy.y) { // 上向き
							b_enemy.angle = 1;
						}
					}
					else if (b_enemy.Bottom == FALSE) {
						if (ENEMY_POS_X > b_enemy.x) { // 右向き
							if (b_enemy.Right == FALSE) {
								b_enemy.angle = 2;
							}
						}
						else if (ENEMY_POS_X < b_enemy.x) { // 左向き
							if (b_enemy.Left == FALSE) {
								b_enemy.angle = 4;
							}
						}
						else if (ENEMY_POS_Y < b_enemy.y) { // 上向き
							if (b_enemy.Top == FALSE) {
								b_enemy.angle = 1;
							}
						}
						//下向き
						b_enemy.y += b_enemy.speed;
						//当たり判定
						b_enemy.top += b_enemy.speed;
						b_enemy.bottom += b_enemy.speed;
						//分身
						for (int i = 0; i < 4; i++) {
							b_enemy.avatar_top[i] += b_enemy.speed;
							b_enemy.avatar_bottom[i] += b_enemy.speed;
						}
						b_enemy.eyeimage = 2;
					}
				}
				//上向き
				else if (b_enemy.angle == 1) {
					if (b_enemy.Top == TRUE) {
						if (ENEMY_POS_X > b_enemy.x) { // 右向き
							b_enemy.angle = 2;
						}
						else if (ENEMY_POS_X < b_enemy.x) { // 左向き
							b_enemy.angle = 4;
						}
						else if (ENEMY_POS_Y > b_enemy.y) { // 下向き
							b_enemy.angle = 3;
						}
					}
					else if (b_enemy.Top == FALSE) {
						if (ENEMY_POS_X > b_enemy.x) { // 右向き
							if (b_enemy.Right == FALSE) {
								b_enemy.angle = 2;
							}
						}
						else if (ENEMY_POS_X < b_enemy.x) { // 左向き
							if (b_enemy.Left == FALSE) {
								b_enemy.angle = 4;
							}
						}
						else if (ENEMY_POS_Y > b_enemy.y) { // 下向き
							if (b_enemy.Bottom == FALSE) {
								b_enemy.angle = 3;
							}
						}
						//上向き
						b_enemy.y -= b_enemy.speed;
						//当たり判定
						b_enemy.top -= b_enemy.speed;
						b_enemy.bottom -= b_enemy.speed;
						//分身
						for (int i = 0; i < 4; i++) {
							b_enemy.avatar_top[i] -= b_enemy.speed;
							b_enemy.avatar_bottom[i] -= b_enemy.speed;
						}
						b_enemy.eyeimage = 0;
					}
				}
				// 初期位置に戻った時
				if (ENEMY_POS_X == b_enemy.x) {
					b_enemy.eyeflg = FALSE;
				}
			}
		}
	}

	// エネミーとプレイヤーの当たり判定
	if (B_EnemeyCheckHit(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, b_enemy.left, b_enemy.top, b_enemy.right, b_enemy.bottom)) {
		if (b_enemy.R_Hitflg == TRUE || b_enemy.ER_Hitflg == TRUE) { // イジケ状態で当たったら
			b_enemy.PR_Hitflg = TRUE;
			b_enemy.eyeflg = TRUE;
		}
	}

	// アニメーション
	++b_enemy.count;  // カウント開始
	if (b_enemy.count >= 8) {  // 値によってアニメーションのスピードが変化する0に近い程速い
		b_enemy.image++;
		b_enemy.izikeimage++;
		b_enemy.e_izikeimage++;
		b_enemy.count = 0;  // カウントリセット
	}
	if (b_enemy.R_Hitflg == FALSE) { // もしイジケ状態でなければ
		if (b_enemy.image >= 6) { // 通常の画像切り替え
			b_enemy.image = 4;    // 画像リセット
		}
	}
	else if (b_enemy.R_Hitflg == TRUE) { // もしイジケ状態なら
		if (b_enemy.izikeimage >= 18) { // イジケ画像切り替え
			b_enemy.izikeimage = 16; // 画像リセット
		}
	}
	if (b_enemy.ER_Hitflg == TRUE) { // もしイジケ状態が終わりそうなら
		if (b_enemy.e_izikeimage >= 20) { // イジケ点滅画像切り替え
			b_enemy.e_izikeimage = 16; // 画像リセット
		}
	}

	// ワープトンネル
	if (b_enemy.x >= 878) {
		b_enemy.x = 352;

		//分身
		//上
		b_enemy.avatar_right[0] = 352 + B_ENEMY_POS_HITBOX;
		b_enemy.avatar_left[0] = 352 - B_ENEMY_POS_HITBOX;
		//下
		b_enemy.avatar_left[2] = 352 - B_ENEMY_POS_HITBOX;
		b_enemy.avatar_right[2] = 352 + B_ENEMY_POS_HITBOX;
		//右
		b_enemy.avatar_left[1] = 352 + 24 - B_ENEMY_POS_HITBOX;
		b_enemy.avatar_right[1] = 352 + 24 + B_ENEMY_POS_HITBOX;
		//左
		b_enemy.avatar_right[3] = 352 - 24 - B_ENEMY_POS_HITBOX;
		b_enemy.avatar_left[3] = 352 - 24 + B_ENEMY_POS_HITBOX;
	}
	else if (b_enemy.x <= 352) {
		b_enemy.x = 878;

		//分身
		//上
		b_enemy.avatar_right[0] = 878 + B_ENEMY_POS_HITBOX;
		b_enemy.avatar_left[0] = 878 - B_ENEMY_POS_HITBOX;
		//下
		b_enemy.avatar_left[2] = 878 - B_ENEMY_POS_HITBOX;
		b_enemy.avatar_right[2] = 878 + B_ENEMY_POS_HITBOX;
		//右
		b_enemy.avatar_left[1] = 878 + 24 - B_ENEMY_POS_HITBOX;
		b_enemy.avatar_right[1] = 878 + 24 + B_ENEMY_POS_HITBOX;
		//左
		b_enemy.avatar_right[3] = 878 - 24 - B_ENEMY_POS_HITBOX;
		b_enemy.avatar_left[3] = 878 - 24 + B_ENEMY_POS_HITBOX;
	}

	// イジケ状態フラグ
	if (b_enemy.R_Hitflg == TRUE) {
		++b_enemy.ER_count;
	}
}

void B_ENEMY::Draw() {
	if (mStage.StateFlg == FALSE || mStage.GameOverFlg == TRUE) {		//スタートの時のみ表示
		DrawRotaGraph(b_enemy.x, b_enemy.y, 0, 0, b_enemy.images[b_enemy.image], TRUE, FALSE);
		DrawRotaGraph(b_enemy.x, b_enemy.y, 0, 0, b_enemy.eyesimages[b_enemy.eyeimage], TRUE, FALSE);
	}
	else if (mStage.StateFlg == TRUE) {
		DrawRotaGraph(b_enemy.x, b_enemy.y, 0.75, 0, b_enemy.images[4], TRUE, FALSE);
		DrawRotaGraph(b_enemy.x, b_enemy.y, 0.75, 0, b_enemy.eyesimages[3], TRUE, FALSE);
	}

	if (b_enemy.R_Hitflg == FALSE && mStage.MoveFlg == TRUE) { // パワーエサを取っていなければ
		DrawRotaGraph(b_enemy.x, b_enemy.y, 0.75, 0, b_enemy.images[b_enemy.image], TRUE, FALSE); // 敵キャラ表示
		DrawRotaGraph(b_enemy.x, b_enemy.y, 0.75, 0, b_enemy.eyesimages[b_enemy.eyeimage], TRUE, FALSE); // 敵キャラの目表示
		DrawBox(b_enemy.left, b_enemy.top, b_enemy.right, b_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
	}
	else if (b_enemy.R_Hitflg == TRUE) { // パワーエサを取っていたら
		if (b_enemy.PR_Hitflg == FALSE) { // プレイヤーと当たっていなければ
			if (b_enemy.ER_count <= 480) {
				DrawRotaGraph(b_enemy.x, b_enemy.y, 0.75, 0, b_enemy.images[b_enemy.izikeimage], TRUE, FALSE); // イジケ状態表示
				DrawBox(b_enemy.left, b_enemy.top, b_enemy.right, b_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
			}
			else if (b_enemy.ER_count > 480 && b_enemy.ER_count <= 600) {
				b_enemy.ER_Hitflg = TRUE;
				DrawRotaGraph(b_enemy.x, b_enemy.y, 0.75, 0, b_enemy.images[b_enemy.e_izikeimage], TRUE, FALSE); // イジケ状態表示
				DrawBox(b_enemy.left, b_enemy.top, b_enemy.right, b_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
			}
			else {
				b_enemy.R_Hitflg = FALSE;
				b_enemy.ER_Hitflg = FALSE;
				b_enemy.ER_count = 0;
				mPlayer.timercount = 0;
			}
		}
		else if (b_enemy.PR_Hitflg == TRUE) { // プレイヤーと当たっていたら
			if (b_enemy.eyeflg == TRUE) { // 目状態になったら
				DrawRotaGraph(b_enemy.x, b_enemy.y, 0.75, 0, b_enemy.eyesimages[b_enemy.eyeimage], TRUE, FALSE); // 敵キャラの目表示
				DrawBox(b_enemy.left, b_enemy.top, b_enemy.right, b_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
			}
			else if (b_enemy.eyeflg == FALSE) { // 目状態のエネミーが初期位置に戻ったら
				b_enemy.R_Hitflg = FALSE;
				b_enemy.PR_Hitflg = FALSE;
				b_enemy.ER_Hitflg = FALSE;
				b_enemy.ER_count = 0;
				mPlayer.timercount = 0;
			}
		}
	}

	if (b_enemy.Initiaflg == TRUE) {
		// 初期位置に戻す
		b_enemy.x = B_ENEMY_POS_X;
		b_enemy.y = B_ENEMY_POS_Y;
		b_enemy.top = B_ENEMY_POS_Y - B_ENEMY_POS_HITBOX;
		b_enemy.left = B_ENEMY_POS_X - B_ENEMY_POS_HITBOX;
		b_enemy.right = B_ENEMY_POS_X + B_ENEMY_POS_HITBOX;
		b_enemy.bottom = B_ENEMY_POS_Y + B_ENEMY_POS_HITBOX;
		b_enemy.Initiaflg = FALSE;

		//分身の当たり判定
		for (int i = 0; i < 4; i++) {
			b_enemy.avatar_left[i] = ENEMY_AVATAR_POS_X[i] - B_ENEMY_POS_HITBOX;
			b_enemy.avatar_top[i] = ENEMY_AVATAR_POS_Y[i] - B_ENEMY_POS_HITBOX;
			b_enemy.avatar_right[i] = ENEMY_AVATAR_POS_X[i] + B_ENEMY_POS_HITBOX;
			b_enemy.avatar_bottom[i] = ENEMY_AVATAR_POS_Y[i] + B_ENEMY_POS_HITBOX;
		}

		if (mStage.life == 2) {
			mStage.life = 1;
		}
		else if (mStage.life == 1) {
			mStage.life = 0;
		}
		else if (mStage.life == 0) {
			mStage.GameOverFlg = true;
		}
	}

	//分身の表示
	for (int i = 0; i < 4; i++) {
		DrawBox(b_enemy.avatar_left[i], b_enemy.avatar_top[i], b_enemy.avatar_right[i], b_enemy.avatar_bottom[i], 0x00ffff, FALSE);
	}

	//進める時
	//上
	if (b_enemy.Top == TRUE) {
		DrawBox(b_enemy.avatar_left[0], b_enemy.avatar_top[0], b_enemy.avatar_right[0], b_enemy.avatar_bottom[0], 0xff00ff, true);
	}
	else if (b_enemy.Top == FALSE) {
		DrawBox(b_enemy.avatar_left[0], b_enemy.avatar_top[0], b_enemy.avatar_right[0], b_enemy.avatar_bottom[0], 0xff0000, true);
	}
	//右
	if (b_enemy.Right == TRUE) {
		DrawBox(b_enemy.avatar_left[1], b_enemy.avatar_top[1], b_enemy.avatar_right[1], b_enemy.avatar_bottom[1], 0xff00ff, true);
	}
	else if (b_enemy.Right == FALSE) {
		DrawBox(b_enemy.avatar_left[1], b_enemy.avatar_top[1], b_enemy.avatar_right[1], b_enemy.avatar_bottom[1], 0xff0000, true);
	}
	//下
	if (b_enemy.Bottom == TRUE) {
		DrawBox(b_enemy.avatar_left[2], b_enemy.avatar_top[2], b_enemy.avatar_right[2], b_enemy.avatar_bottom[2], 0xff00ff, true);
	}
	else if (b_enemy.Bottom == FALSE) {
		DrawBox(b_enemy.avatar_left[2], b_enemy.avatar_top[2], b_enemy.avatar_right[2], b_enemy.avatar_bottom[2], 0xff0000, true);
	}
	//左
	if (b_enemy.Left == TRUE) {
		DrawBox(b_enemy.avatar_left[3], b_enemy.avatar_top[3], b_enemy.avatar_right[3], b_enemy.avatar_bottom[3], 0xff00ff, true);
	}
	else if (b_enemy.Left == FALSE) {
		DrawBox(b_enemy.avatar_left[3], b_enemy.avatar_top[3], b_enemy.avatar_right[3], b_enemy.avatar_bottom[3], 0xff0000, true);
	}
}