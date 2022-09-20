#include "DxLib.h"
#include "Pink_Enemy.h"
#include "Player.h"
#include <math.h>
#include "Stage.h"

P_ENEMY p_enemy;

int P_EnemeyCheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
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

void P_ENEMY::Initialize() {
	LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, images);  // 敵キャラ
	LoadDivGraph("images/eyes.png", 4, 4, 1, 32, 32, eyesimages);  // 敵キャラの目

	p_enemy.speed = 1;             // 移動速度
	p_enemy.angle = 4;             // 初期の向き
	p_enemy.count = 0;             // アニメーションカウント
	p_enemy.ER_count = 0;          // イジケ状態カウント
	p_enemy.image = 2;             // 画像変数
	p_enemy.eyeimage = 3;          // 目の画像変数
	p_enemy.izikeimage = 16;       // イジケ状態の画像変数
	p_enemy.e_izikeimage = 16;     // イジケ状態点滅の画像変数
	//p_enemy.E_StageHitflg = FALSE; // 壁との当たり判定フラグ
	p_enemy.R_Hitflg = FALSE;      // イジケ状態判定フラグ
	p_enemy.ER_Hitflg = FALSE;     // イジケ状態点滅フラグ
	p_enemy.PR_Hitflg = FALSE;     // イジケ状態でプレイヤーに当たった時のフラグ
	p_enemy.eyeflg = FALSE;        // エネミー目状態
	p_enemy.Initiaflg = FALSE;     // エネミー初期化

	// 初期位置を保存
	p_enemy.x = P_ENEMY_POS_X;
	p_enemy.y = P_ENEMY_POS_Y;

	//当たり判定
	p_enemy.recordX = p_enemy.x;
	p_enemy.recordY = p_enemy.y;

	p_enemy.top = P_ENEMY_POS_Y - P_ENEMY_POS_HITBOX;
	p_enemy.left = P_ENEMY_POS_X - P_ENEMY_POS_HITBOX;
	p_enemy.right = P_ENEMY_POS_X + P_ENEMY_POS_HITBOX;
	p_enemy.bottom = P_ENEMY_POS_Y + P_ENEMY_POS_HITBOX;

	p_enemy.recordTop = p_enemy.top;
	p_enemy.recordRight = p_enemy.right;
	p_enemy.recordBottom = p_enemy.bottom;
	p_enemy.recordLeft = p_enemy.left;

	// 分身の初期化処理
	//分身のフラグ処理
	p_enemy.Top = FALSE;
	p_enemy.Bottom = FALSE;
	p_enemy.Left = TRUE;
	p_enemy.Right = TRUE;
	//分身の座標
	//上
	p_enemy.ENEMY_AVATAR_POS_X[0] = P_ENEMY_POS_X;
	p_enemy.ENEMY_AVATAR_POS_Y[0] = P_ENEMY_POS_Y - 24;
	//右
	p_enemy.ENEMY_AVATAR_POS_X[1] = P_ENEMY_POS_X + 24;
	p_enemy.ENEMY_AVATAR_POS_Y[1] = P_ENEMY_POS_Y;
	//下
	p_enemy.ENEMY_AVATAR_POS_X[2] = P_ENEMY_POS_X;
	p_enemy.ENEMY_AVATAR_POS_Y[2] = P_ENEMY_POS_Y + 24;
	//左
	p_enemy.ENEMY_AVATAR_POS_X[3] = P_ENEMY_POS_X - 24;
	p_enemy.ENEMY_AVATAR_POS_Y[3] = P_ENEMY_POS_Y;

	// 前回のキー入力処理
	p_enemy.CheckNumber = 12;

	//分身の当たり判定
	for (int i = 0; i < 4; i++) {
		p_enemy.avatar_left[i] = ENEMY_AVATAR_POS_X[i] - P_ENEMY_POS_HITBOX;
		p_enemy.avatar_top[i] = ENEMY_AVATAR_POS_Y[i] - P_ENEMY_POS_HITBOX;
		p_enemy.avatar_right[i] = ENEMY_AVATAR_POS_X[i] + P_ENEMY_POS_HITBOX;
		p_enemy.avatar_bottom[i] = ENEMY_AVATAR_POS_Y[i] + P_ENEMY_POS_HITBOX;
	}
}

void P_ENEMY::Update() {
	//前回の座標取得
	p_enemy.recordX = p_enemy.x;
	p_enemy.recordY = p_enemy.y;

	p_enemy.recordTop = p_enemy.top;
	p_enemy.recordRight = p_enemy.right;
	p_enemy.recordBottom = p_enemy.bottom;
	p_enemy.recordLeft = p_enemy.left;

	//前回の座標移動
	p_enemy.absX = mPlayer.x - p_enemy.x;
	p_enemy.absY = mPlayer.y - p_enemy.y;

	//絶対値を求める
	if (p_enemy.absX <= 0) {
		p_enemy.absX = p_enemy.absX * -1;
	}
	if (p_enemy.absY <= 0) {
		p_enemy.absY = p_enemy.absY * -1;
	}

	//分身の座標
	for (int i = 0; i < 4; i++) {
		p_enemy.record_avatar_bottom[i] = p_enemy.avatar_bottom[i];
		p_enemy.record_avatar_left[i] = p_enemy.avatar_left[i];
		p_enemy.record_avatar_right[i] = p_enemy.avatar_right[i];
		p_enemy.record_avatar_top[i] = p_enemy.avatar_top[i];
	}

	// プレイヤーを追いかける処理
	if (p_enemy.R_Hitflg == FALSE && mStage.MoveFlg == TRUE) { // パワーエサを取っていない時
		// 右向き
		if (p_enemy.angle == 2) {
			if (p_enemy.Right == TRUE) {
				if (mPlayer.x < p_enemy.x) { // 左向き
					p_enemy.angle = 4;
				}
				else if (mPlayer.y < p_enemy.y) { // 上向き
					p_enemy.angle = 1;
				}
				else if (mPlayer.y > p_enemy.y) { // 下向き
					p_enemy.angle = 3;
				}
			}
			else if (p_enemy.Right == FALSE) {
				if (mPlayer.x < p_enemy.x) { // 左向き
					if (p_enemy.Left == FALSE) {
						p_enemy.angle = 4;
					}
				}
				else if (mPlayer.y < p_enemy.y) { // 上向き
					if (p_enemy.Top == FALSE) {
						p_enemy.angle = 1;
					}
				}
				else if (mPlayer.y > p_enemy.y) { // 下向き
					if (p_enemy.Bottom == FALSE) {
						p_enemy.angle = 3;
					}
				}
				// 右向き
				p_enemy.x += p_enemy.speed;
				// 当たり判定
				p_enemy.left += p_enemy.speed;
				p_enemy.right += p_enemy.speed;
				//分身
				for (int i = 0; i < 4; i++) {
					p_enemy.avatar_right[i] += p_enemy.speed;
					p_enemy.avatar_left[i] += p_enemy.speed;
				}
				p_enemy.eyeimage = 1;
			}
		}
		// 左向き
		else if (p_enemy.angle == 4) {
			if (p_enemy.Left == TRUE) {
				if (mPlayer.x > p_enemy.x) { // 右向き
					p_enemy.angle = 2;
				}
				else if (mPlayer.y < p_enemy.y) { // 上向き
					p_enemy.angle = 1;
				}
				else if (mPlayer.y > p_enemy.y) { // 下向き
					p_enemy.angle = 3;
				}
			}
			else if (p_enemy.Left == FALSE) {
				if (mPlayer.x > p_enemy.x) { // 右向き
					if (p_enemy.Right == FALSE) {
						p_enemy.angle = 2;
					}
				}
				else if (mPlayer.y < p_enemy.y) { // 上向き
					if (p_enemy.Top == FALSE) {
						p_enemy.angle = 1;
					}
				}
				else if (mPlayer.y > p_enemy.y) { // 下向き
					if (p_enemy.Bottom == FALSE) {
						p_enemy.angle = 3;
					}
				}
				// 左向き
				p_enemy.x -= p_enemy.speed;
				//当たり判定
				p_enemy.left -= p_enemy.speed;
				p_enemy.right -= p_enemy.speed;
				//分身
				for (int i = 0; i < 4; i++) {
					p_enemy.avatar_right[i] -= p_enemy.speed;
					p_enemy.avatar_left[i] -= p_enemy.speed;
				}
				p_enemy.eyeimage = 3;
			}
		}
		//下向き
		else if (p_enemy.angle == 3) {
			if (p_enemy.Bottom == TRUE) {
				if (mPlayer.x > p_enemy.x) { // 右向き
					p_enemy.angle = 2;
				}
				else if (mPlayer.x < p_enemy.x) { // 左向き
					p_enemy.angle = 4;
				}
				else if (mPlayer.y < p_enemy.y) { // 上向き
					p_enemy.angle = 1;
				}
			}
			else if (p_enemy.Bottom == FALSE) {
				if (mPlayer.x > p_enemy.x) { // 右向き
					if (p_enemy.Right == FALSE) {
						p_enemy.angle = 2;
					}
				}
				else if (mPlayer.x < p_enemy.x) { // 左向き
					if (p_enemy.Left == FALSE) {
						p_enemy.angle = 4;
					}
				}
				else if (mPlayer.y < p_enemy.y) { // 上向き
					if (p_enemy.Top == FALSE) {
						p_enemy.angle = 1;
					}
				}
				//下向き
				p_enemy.y += p_enemy.speed;
				//当たり判定
				p_enemy.top += p_enemy.speed;
				p_enemy.bottom += p_enemy.speed;
				//分身
				for (int i = 0; i < 4; i++) {
					p_enemy.avatar_top[i] += p_enemy.speed;
					p_enemy.avatar_bottom[i] += p_enemy.speed;
				}
				p_enemy.eyeimage = 2;
			}
		}
		//上向き
		else if (p_enemy.angle == 1) {
			if (p_enemy.Top == TRUE) {
				if (mPlayer.x > p_enemy.x) { // 右向き
					p_enemy.angle = 2;
				}
				else if (mPlayer.x < p_enemy.x) { // 左向き
					p_enemy.angle = 4;
				}
				else if (mPlayer.y > p_enemy.y) { // 下向き
					p_enemy.angle = 3;
				}
			}
			else if (p_enemy.Top == FALSE) {
				if (mPlayer.x > p_enemy.x) { // 右向き
					if (p_enemy.Right == FALSE) {
						p_enemy.angle = 2;
					}
				}
				else if (mPlayer.x < p_enemy.x) { // 左向き
					if (p_enemy.Left == FALSE) {
						p_enemy.angle = 4;
					}
				}
				else if (mPlayer.y > p_enemy.y) { // 下向き
					if (p_enemy.Bottom == FALSE) {
						p_enemy.angle = 3;
					}
				}
				//上向き
				p_enemy.y -= p_enemy.speed;
				//当たり判定
				p_enemy.top -= p_enemy.speed;
				p_enemy.bottom -= p_enemy.speed;
				//分身
				for (int i = 0; i < 4; i++) {
					p_enemy.avatar_top[i] -= p_enemy.speed;
					p_enemy.avatar_bottom[i] -= p_enemy.speed;
				}
				p_enemy.eyeimage = 0;
			}
		}
	}
	else if (p_enemy.R_Hitflg == TRUE) { // パワーエサを取った時
		if (p_enemy.PR_Hitflg == FALSE) { // プレイヤーと当たっていなかったら
			p_enemy.speed = 0.8;
			// 右向き
			if (p_enemy.angle == 2) {
				if (p_enemy.Right == TRUE) {
					if (mPlayer.x < p_enemy.x) { // 左向き
						p_enemy.angle = 4;
					}
					else if (mPlayer.y < p_enemy.y) { // 上向き
						p_enemy.angle = 1;
					}
					else if (mPlayer.y > p_enemy.y) { // 下向き
						p_enemy.angle = 3;
					}
				}
				else if (p_enemy.Right == FALSE) {
					if (mPlayer.x < p_enemy.x) { // 左向き
						if (p_enemy.Left == FALSE) {
							p_enemy.angle = 4;
						}
					}
					else if (mPlayer.y < p_enemy.y) { // 上向き
						if (p_enemy.Top == FALSE) {
							p_enemy.angle = 1;
						}
					}
					else if (mPlayer.y > p_enemy.y) { // 下向き
						if (p_enemy.Bottom == FALSE) {
							p_enemy.angle = 3;
						}
					}
					// 右向き
					p_enemy.x -= p_enemy.speed;
					// 当たり判定
					p_enemy.left -= p_enemy.speed;
					p_enemy.right -= p_enemy.speed;
					//分身
					for (int i = 0; i < 4; i++) {
						p_enemy.avatar_right[i] -= p_enemy.speed;
						p_enemy.avatar_left[i] -= p_enemy.speed;
					}
				}
			}
			// 左向き
			else if (p_enemy.angle == 4) {
				if (p_enemy.Left == TRUE) {
					if (mPlayer.x > p_enemy.x) { // 右向き
						p_enemy.angle = 2;
					}
					else if (mPlayer.y < p_enemy.y) { // 上向き
						p_enemy.angle = 1;
					}
					else if (mPlayer.y > p_enemy.y) { // 下向き
						p_enemy.angle = 3;
					}
				}
				else if (p_enemy.Left == FALSE) {
					if (mPlayer.x > p_enemy.x) { // 右向き
						if (p_enemy.Right == FALSE) {
							p_enemy.angle = 2;
						}
					}
					else if (mPlayer.y < p_enemy.y) { // 上向き
						if (p_enemy.Top == FALSE) {
							p_enemy.angle = 1;
						}
					}
					else if (mPlayer.y > p_enemy.y) { // 下向き
						if (p_enemy.Bottom == FALSE) {
							p_enemy.angle = 3;
						}
					}
					// 左向き
					p_enemy.x += p_enemy.speed;
					//当たり判定
					p_enemy.left += p_enemy.speed;
					p_enemy.right += p_enemy.speed;
					//分身
					for (int i = 0; i < 4; i++) {
						p_enemy.avatar_right[i] += p_enemy.speed;
						p_enemy.avatar_left[i] += p_enemy.speed;
					}
				}
			}
			//下向き
			else if (p_enemy.angle == 3) {
				if (p_enemy.Bottom == TRUE) {
					if (mPlayer.x > p_enemy.x) { // 右向き
						p_enemy.angle = 2;
					}
					else if (mPlayer.x < p_enemy.x) { // 左向き
						p_enemy.angle = 4;
					}
					else if (mPlayer.y < p_enemy.y) { // 上向き
						p_enemy.angle = 1;
					}
				}
				else if (p_enemy.Bottom == FALSE) {
					if (mPlayer.x > p_enemy.x) { // 右向き
						if (p_enemy.Right == FALSE) {
							p_enemy.angle = 2;
						}
					}
					else if (mPlayer.x < p_enemy.x) { // 左向き
						if (p_enemy.Left == FALSE) {
							p_enemy.angle = 4;
						}
					}
					else if (mPlayer.y < p_enemy.y) { // 上向き
						if (p_enemy.Top == FALSE) {
							p_enemy.angle = 1;
						}
					}
					//下向き
					p_enemy.y -= p_enemy.speed;
					//当たり判定
					p_enemy.top -= p_enemy.speed;
					p_enemy.bottom -= p_enemy.speed;
					//分身
					for (int i = 0; i < 4; i++) {
						p_enemy.avatar_top[i] -= p_enemy.speed;
						p_enemy.avatar_bottom[i] -= p_enemy.speed;
					}
				}
			}
			//上向き
			else if (p_enemy.angle == 1) {
				if (p_enemy.Top == TRUE) {
					if (mPlayer.x > p_enemy.x) { // 右向き
						p_enemy.angle = 2;
					}
					else if (mPlayer.x < p_enemy.x) { // 左向き
						p_enemy.angle = 4;
					}
					else if (mPlayer.y > p_enemy.y) { // 下向き
						p_enemy.angle = 3;
					}
				}
				else if (p_enemy.Top == FALSE) {
					if (mPlayer.x > p_enemy.x) { // 右向き
						if (p_enemy.Right == FALSE) {
							p_enemy.angle = 2;
						}
					}
					else if (mPlayer.x < p_enemy.x) { // 左向き
						if (p_enemy.Left == FALSE) {
							p_enemy.angle = 4;
						}
					}
					else if (mPlayer.y > p_enemy.y) { // 下向き
						if (p_enemy.Bottom == FALSE) {
							p_enemy.angle = 3;
						}
					}
					//上向き
					p_enemy.y += p_enemy.speed;
					//当たり判定
					p_enemy.top += p_enemy.speed;
					p_enemy.bottom += p_enemy.speed;
					//分身
					for (int i = 0; i < 4; i++) {
						p_enemy.avatar_top[i] += p_enemy.speed;
						p_enemy.avatar_bottom[i] += p_enemy.speed;
					}
				}
			}
		}
		else if (p_enemy.PR_Hitflg == TRUE) { // プレイヤーと当たっていたら初期位置に戻る
			if (p_enemy.eyeflg == TRUE) {
				p_enemy.speed = 3;
				// 右向き
				if (p_enemy.angle == 2) {
					if (p_enemy.Right == TRUE) {
						if (ENEMY_POS_X < p_enemy.x) { // 左向き
							p_enemy.angle = 4;
						}
						else if (ENEMY_POS_Y < p_enemy.y) { // 上向き
							p_enemy.angle = 1;
						}
						else if (ENEMY_POS_Y > p_enemy.y) { // 下向き
							p_enemy.angle = 3;
						}
					}
					else if (p_enemy.Right == FALSE) {
						if (ENEMY_POS_X < p_enemy.x) { // 左向き
							if (p_enemy.Left == FALSE) {
								p_enemy.angle = 4;
							}
						}
						else if (ENEMY_POS_Y < p_enemy.y) { // 上向き
							if (p_enemy.Top == FALSE) {
								p_enemy.angle = 1;
							}
						}
						else if (ENEMY_POS_Y > p_enemy.y) { // 下向き
							if (p_enemy.Bottom == FALSE) {
								p_enemy.angle = 3;
							}
						}
						// 右向き
						p_enemy.x += p_enemy.speed;
						// 当たり判定
						p_enemy.left += p_enemy.speed;
						p_enemy.right += p_enemy.speed;
						//分身
						for (int i = 0; i < 4; i++) {
							p_enemy.avatar_right[i] += p_enemy.speed;
							p_enemy.avatar_left[i] += p_enemy.speed;
						}
						p_enemy.eyeimage = 1;
					}
				}
				// 左向き
				else if (p_enemy.angle == 4) {
					if (p_enemy.Left == TRUE) {
						if (ENEMY_POS_X > p_enemy.x) { // 右向き
							p_enemy.angle = 2;
						}
						else if (ENEMY_POS_Y < p_enemy.y) { // 上向き
							p_enemy.angle = 1;
						}
						else if (ENEMY_POS_Y > p_enemy.y) { // 下向き
							p_enemy.angle = 3;
						}
					}
					else if (p_enemy.Left == FALSE) {
						if (ENEMY_POS_X > p_enemy.x) { // 右向き
							if (p_enemy.Right == FALSE) {
								p_enemy.angle = 2;
							}
						}
						else if (ENEMY_POS_Y < p_enemy.y) { // 上向き
							if (p_enemy.Top == FALSE) {
								p_enemy.angle = 1;
							}
						}
						else if (ENEMY_POS_Y > p_enemy.y) { // 下向き
							if (p_enemy.Bottom == FALSE) {
								p_enemy.angle = 3;
							}
						}
						// 左向き
						p_enemy.x -= p_enemy.speed;
						//当たり判定
						p_enemy.left -= p_enemy.speed;
						p_enemy.right -= p_enemy.speed;
						//分身
						for (int i = 0; i < 4; i++) {
							p_enemy.avatar_right[i] -= p_enemy.speed;
							p_enemy.avatar_left[i] -= p_enemy.speed;
						}
						p_enemy.eyeimage = 3;
					}
				}
				//下向き
				else if (p_enemy.angle == 3) {
					if (p_enemy.Bottom == TRUE) {
						if (ENEMY_POS_X > p_enemy.x) { // 右向き
							p_enemy.angle = 2;
						}
						else if (ENEMY_POS_X < p_enemy.x) { // 左向き
							p_enemy.angle = 4;
						}
						else if (ENEMY_POS_Y < p_enemy.y) { // 上向き
							p_enemy.angle = 1;
						}
					}
					else if (p_enemy.Bottom == FALSE) {
						if (ENEMY_POS_X > p_enemy.x) { // 右向き
							if (p_enemy.Right == FALSE) {
								p_enemy.angle = 2;
							}
						}
						else if (ENEMY_POS_X < p_enemy.x) { // 左向き
							if (p_enemy.Left == FALSE) {
								p_enemy.angle = 4;
							}
						}
						else if (ENEMY_POS_Y < p_enemy.y) { // 上向き
							if (p_enemy.Top == FALSE) {
								p_enemy.angle = 1;
							}
						}
						//下向き
						p_enemy.y += p_enemy.speed;
						//当たり判定
						p_enemy.top += p_enemy.speed;
						p_enemy.bottom += p_enemy.speed;
						//分身
						for (int i = 0; i < 4; i++) {
							p_enemy.avatar_top[i] += p_enemy.speed;
							p_enemy.avatar_bottom[i] += p_enemy.speed;
						}
						p_enemy.eyeimage = 2;
					}
				}
				//上向き
				else if (p_enemy.angle == 1) {
					if (p_enemy.Top == TRUE) {
						if (ENEMY_POS_X > p_enemy.x) { // 右向き
							p_enemy.angle = 2;
						}
						else if (ENEMY_POS_X < p_enemy.x) { // 左向き
							p_enemy.angle = 4;
						}
						else if (ENEMY_POS_Y > p_enemy.y) { // 下向き
							p_enemy.angle = 3;
						}
					}
					else if (p_enemy.Top == FALSE) {
						if (ENEMY_POS_X > p_enemy.x) { // 右向き
							if (p_enemy.Right == FALSE) {
								p_enemy.angle = 2;
							}
						}
						else if (ENEMY_POS_X < p_enemy.x) { // 左向き
							if (p_enemy.Left == FALSE) {
								p_enemy.angle = 4;
							}
						}
						else if (ENEMY_POS_Y > p_enemy.y) { // 下向き
							if (p_enemy.Bottom == FALSE) {
								p_enemy.angle = 3;
							}
						}
						//上向き
						p_enemy.y -= p_enemy.speed;
						//当たり判定
						p_enemy.top -= p_enemy.speed;
						p_enemy.bottom -= p_enemy.speed;
						//分身
						for (int i = 0; i < 4; i++) {
							p_enemy.avatar_top[i] -= p_enemy.speed;
							p_enemy.avatar_bottom[i] -= p_enemy.speed;
						}
						p_enemy.eyeimage = 0;
					}
				}
				// 初期位置に戻った時
				if (ENEMY_POS_X == p_enemy.x) {
					p_enemy.eyeflg = FALSE;
				}
			}
		}
	}

	// エネミーとプレイヤーの当たり判定
	if (P_EnemeyCheckHit(mPlayer.p_left, mPlayer.p_top, mPlayer.p_right, mPlayer.p_bottom, p_enemy.left, p_enemy.top, p_enemy.right, p_enemy.bottom)) {
		if (p_enemy.R_Hitflg == TRUE || p_enemy.ER_Hitflg == TRUE) { // イジケ状態で当たったら
			p_enemy.PR_Hitflg = TRUE;
			p_enemy.eyeflg = TRUE;
		}
	}

	// アニメーション
	++p_enemy.count;  // カウント開始
	if (p_enemy.count >= 8) {  // 値によってアニメーションのスピードが変化する0に近い程速い
		p_enemy.image++;
		p_enemy.izikeimage++;
		p_enemy.e_izikeimage++;
		p_enemy.count = 0;  // カウントリセット
	}
	if (p_enemy.R_Hitflg == FALSE) { // もしイジケ状態でなければ
		if (p_enemy.image >= 4) { // 通常の画像切り替え
			p_enemy.image = 2;    // 画像リセット
		}
	}
	else if (p_enemy.R_Hitflg == TRUE) { // もしイジケ状態なら
		if (p_enemy.izikeimage >= 18) { // イジケ画像切り替え
			p_enemy.izikeimage = 16; // 画像リセット
		}
	}
	if (p_enemy.ER_Hitflg == TRUE) { // もしイジケ状態が終わりそうなら
		if (p_enemy.e_izikeimage >= 20) { // イジケ点滅画像切り替え
			p_enemy.e_izikeimage = 16; // 画像リセット
		}
	}

	// ワープトンネル
	if (p_enemy.x >= 878) {
		p_enemy.x = 352;

		//分身
		//上
		p_enemy.avatar_right[0] = 352 + P_ENEMY_POS_HITBOX;
		p_enemy.avatar_left[0] = 352 - P_ENEMY_POS_HITBOX;
		//下
		p_enemy.avatar_left[2] = 352 - P_ENEMY_POS_HITBOX;
		p_enemy.avatar_right[2] = 352 + P_ENEMY_POS_HITBOX;
		//右
		p_enemy.avatar_left[1] = 352 + 24 - P_ENEMY_POS_HITBOX;
		p_enemy.avatar_right[1] = 352 + 24 + P_ENEMY_POS_HITBOX;
		//左
		p_enemy.avatar_right[3] = 352 - 24 - P_ENEMY_POS_HITBOX;
		p_enemy.avatar_left[3] = 352 - 24 + P_ENEMY_POS_HITBOX;
	}
	else if (p_enemy.x <= 352) {
		p_enemy.x = 878;

		//分身
		//上
		p_enemy.avatar_right[0] = 878 + P_ENEMY_POS_HITBOX;
		p_enemy.avatar_left[0] = 878 - P_ENEMY_POS_HITBOX;
		//下
		p_enemy.avatar_left[2] = 878 - P_ENEMY_POS_HITBOX;
		p_enemy.avatar_right[2] = 878 + P_ENEMY_POS_HITBOX;
		//右
		p_enemy.avatar_left[1] = 878 + 24 - P_ENEMY_POS_HITBOX;
		p_enemy.avatar_right[1] = 878 + 24 + P_ENEMY_POS_HITBOX;
		//左
		p_enemy.avatar_right[3] = 878 - 24 - P_ENEMY_POS_HITBOX;
		p_enemy.avatar_left[3] = 878 - 24 + P_ENEMY_POS_HITBOX;
	}

	// イジケ状態フラグ
	if (p_enemy.R_Hitflg == TRUE) {
		++p_enemy.ER_count;
	}
}

void P_ENEMY::Draw() {
	if (mStage.StateFlg == FALSE || mStage.GameOverFlg == TRUE) {		//スタートの時のみ表示
		DrawRotaGraph(p_enemy.x, p_enemy.y, 0, 0, p_enemy.images[p_enemy.image], TRUE, FALSE);
		DrawRotaGraph(p_enemy.x, p_enemy.y, 0, 0, p_enemy.eyesimages[p_enemy.eyeimage], TRUE, FALSE);
	}
	else if (mStage.StateFlg == TRUE) {
		DrawRotaGraph(p_enemy.x, p_enemy.y, 0.75, 0, p_enemy.images[2], TRUE, FALSE);
		DrawRotaGraph(p_enemy.x, p_enemy.y, 0.75, 0, p_enemy.eyesimages[3], TRUE, FALSE);
	}

	if (p_enemy.R_Hitflg == FALSE && mStage.MoveFlg == TRUE) { // パワーエサを取っていなければ
		DrawRotaGraph(p_enemy.x, p_enemy.y, 0.75, 0, p_enemy.images[p_enemy.image], TRUE, FALSE); // 敵キャラ表示
		DrawRotaGraph(p_enemy.x, p_enemy.y, 0.75, 0, p_enemy.eyesimages[p_enemy.eyeimage], TRUE, FALSE); // 敵キャラの目表示
		//DrawBox(p_enemy.left, p_enemy.top, p_enemy.right, p_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
	}
	else if (p_enemy.R_Hitflg == TRUE) { // パワーエサを取っていたら
		if (p_enemy.PR_Hitflg == FALSE) { // プレイヤーと当たっていなければ
			if (p_enemy.ER_count <= 480) {
				DrawRotaGraph(p_enemy.x, p_enemy.y, 0.75, 0, p_enemy.images[p_enemy.izikeimage], TRUE, FALSE); // イジケ状態表示
				//DrawBox(p_enemy.left, p_enemy.top, p_enemy.right, p_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
			}
			else if (p_enemy.ER_count > 480 && p_enemy.ER_count <= 600) {
				p_enemy.ER_Hitflg = TRUE;
				DrawRotaGraph(p_enemy.x, p_enemy.y, 0.75, 0, p_enemy.images[p_enemy.e_izikeimage], TRUE, FALSE); // イジケ状態表示
				//DrawBox(p_enemy.left, p_enemy.top, p_enemy.right, p_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
			}
			else {
				p_enemy.R_Hitflg = FALSE;
				p_enemy.ER_Hitflg = FALSE;
				p_enemy.ER_count = 0;
				mPlayer.timercount = 0;
			}
		}
		else if (p_enemy.PR_Hitflg == TRUE) { // プレイヤーと当たっていたら
			if (p_enemy.eyeflg == TRUE) { // 目状態になったら
				DrawRotaGraph(p_enemy.x, p_enemy.y, 0.75, 0, p_enemy.eyesimages[p_enemy.eyeimage], TRUE, FALSE); // 敵キャラの目表示
				//DrawBox(p_enemy.left, p_enemy.top, p_enemy.right, p_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
			}
			else if (p_enemy.eyeflg == FALSE) { // 目状態のエネミーが初期位置に戻ったら
				p_enemy.R_Hitflg = FALSE;
				p_enemy.PR_Hitflg = FALSE;
				p_enemy.ER_Hitflg = FALSE;
				p_enemy.ER_count = 0;
				mPlayer.timercount = 0;
			}
		}
	}

	if (p_enemy.Initiaflg == TRUE) {
		// 初期位置に戻す
		p_enemy.x = P_ENEMY_POS_X;
		p_enemy.y = P_ENEMY_POS_Y;
		p_enemy.top = P_ENEMY_POS_Y - P_ENEMY_POS_HITBOX;
		p_enemy.left = P_ENEMY_POS_X - P_ENEMY_POS_HITBOX;
		p_enemy.right = P_ENEMY_POS_X + P_ENEMY_POS_HITBOX;
		p_enemy.bottom = P_ENEMY_POS_Y + P_ENEMY_POS_HITBOX;
		p_enemy.Initiaflg = FALSE;

		//分身の当たり判定
		for (int i = 0; i < 4; i++) {
			p_enemy.avatar_left[i] = ENEMY_AVATAR_POS_X[i] - P_ENEMY_POS_HITBOX;
			p_enemy.avatar_top[i] = ENEMY_AVATAR_POS_Y[i] - P_ENEMY_POS_HITBOX;
			p_enemy.avatar_right[i] = ENEMY_AVATAR_POS_X[i] + P_ENEMY_POS_HITBOX;
			p_enemy.avatar_bottom[i] = ENEMY_AVATAR_POS_Y[i] + P_ENEMY_POS_HITBOX;
		}
	}

	////分身の表示
	//for (int i = 0; i < 4; i++) {
	//	DrawBox(p_enemy.avatar_left[i], p_enemy.avatar_top[i], p_enemy.avatar_right[i], p_enemy.avatar_bottom[i], 0x00ffff, FALSE);
	//}

	////進める時
	////上
	//if (p_enemy.Top == TRUE) {
	//	DrawBox(p_enemy.avatar_left[0], p_enemy.avatar_top[0], p_enemy.avatar_right[0], p_enemy.avatar_bottom[0], 0xff00ff, true);
	//}
	//else if (p_enemy.Top == FALSE) {
	//	DrawBox(p_enemy.avatar_left[0], p_enemy.avatar_top[0], p_enemy.avatar_right[0], p_enemy.avatar_bottom[0], 0xff0000, true);
	//}
	////右
	//if (p_enemy.Right == TRUE) {
	//	DrawBox(p_enemy.avatar_left[1], p_enemy.avatar_top[1], p_enemy.avatar_right[1], p_enemy.avatar_bottom[1], 0xff00ff, true);
	//}
	//else if (p_enemy.Right == FALSE) {
	//	DrawBox(p_enemy.avatar_left[1], p_enemy.avatar_top[1], p_enemy.avatar_right[1], p_enemy.avatar_bottom[1], 0xff0000, true);
	//}
	////下
	//if (p_enemy.Bottom == TRUE) {
	//	DrawBox(p_enemy.avatar_left[2], p_enemy.avatar_top[2], p_enemy.avatar_right[2], p_enemy.avatar_bottom[2], 0xff00ff, true);
	//}
	//else if (p_enemy.Bottom == FALSE) {
	//	DrawBox(p_enemy.avatar_left[2], p_enemy.avatar_top[2], p_enemy.avatar_right[2], p_enemy.avatar_bottom[2], 0xff0000, true);
	//}
	////左
	//if (p_enemy.Left == TRUE) {
	//	DrawBox(p_enemy.avatar_left[3], p_enemy.avatar_top[3], p_enemy.avatar_right[3], p_enemy.avatar_bottom[3], 0xff00ff, true);
	//}
	//else if (p_enemy.Left == FALSE) {
	//	DrawBox(p_enemy.avatar_left[3], p_enemy.avatar_top[3], p_enemy.avatar_right[3], p_enemy.avatar_bottom[3], 0xff0000, true);
	//}
}