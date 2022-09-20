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

	r_enemy.speed = 1.8;           // 移動速度
	r_enemy.angle = 4;             // 初期の向き
	r_enemy.count = 0;             // アニメーションカウント
	r_enemy.ER_count = 0;          // イジケ状態カウント
	r_enemy.image = 0;             // 画像変数
	r_enemy.eyeimage = 0;          // 目の画像変数
	r_enemy.izikeimage = 16;       // イジケ状態の画像変数
	r_enemy.e_izikeimage = 16;     // イジケ状態点滅の画像変数
	//r_enemy.E_StageHitflg = FALSE; // 壁との当たり判定フラグ
	r_enemy.R_Hitflg = FALSE;      // イジケ状態判定フラグ
	r_enemy.ER_Hitflg = FALSE;     // イジケ状態点滅フラグ
	r_enemy.PR_Hitflg = FALSE;     // イジケ状態でプレイヤーに当たった時のフラグ
	r_enemy.eyeflg = FALSE;        // エネミー目状態
	r_enemy.Initiaflg = FALSE;     // エネミー初期化

	// 初期位置を保存
	r_enemy.x = ENEMY_POS_X;
	r_enemy.y = ENEMY_POS_Y;

	//当たり判定
	r_enemy.recordX = r_enemy.x;
	r_enemy.recordY = r_enemy.y;

	r_enemy.top = ENEMY_POS_Y - ENEMY_STAGE_HITBOX;
	r_enemy.left = ENEMY_POS_X - ENEMY_STAGE_HITBOX;
	r_enemy.right = ENEMY_POS_X + ENEMY_STAGE_HITBOX;
	r_enemy.bottom = ENEMY_POS_Y + ENEMY_STAGE_HITBOX;

	r_enemy.recordTop = r_enemy.top;
	r_enemy.recordRight = r_enemy.right;
	r_enemy.recordBottom = r_enemy.bottom;
	r_enemy.recordLeft = r_enemy.left;
}

void R_ENEMY::Update() {
	//前回の座標取得
	r_enemy.recordX = r_enemy.x;
	r_enemy.recordY = r_enemy.y;

	r_enemy.recordTop = r_enemy.top;
	r_enemy.recordRight = r_enemy.right;
	r_enemy.recordBottom = r_enemy.bottom;
	r_enemy.recordLeft = r_enemy.left;

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

	r_enemy.xx = r_enemy.x - mPlayer.x;
	r_enemy.yy = r_enemy.y - mPlayer.y;
	r_enemy.xy2 = r_enemy.xx + r_enemy.yy;
	r_enemy.xy = pow(r_enemy.xy2, 2.0);

	mPlayer.xx = mPlayer.x - r_enemy.x;
	mPlayer.yy = mPlayer.y - r_enemy.y;
	mPlayer.xy2 = mPlayer.xx + mPlayer.yy;
	mPlayer.xy = pow(mPlayer.xy2, 2.0);

	// プレイヤーを追いかける処理
	if (r_enemy.R_Hitflg == FALSE && mStage.MoveFlg == TRUE && mPlayer.Hitflg == FALSE) { // パワーエサを取っていない時
		r_enemy.speed = 1.8;
		// 右向き
		if (r_enemy.angle == 2) {
			// 右向き
			//if (mPlayer.x > r_enemy.x) {
				r_enemy.x += r_enemy.speed;

				// 当たり判定
				r_enemy.left += r_enemy.speed;
				r_enemy.right += r_enemy.speed;

				r_enemy.eyeimage = 1;
			//}
			//// 左向き
			//if (mPlayer.x < r_enemy.x) {
			//	r_enemy.x -= r_enemy.speed;

			//	r_enemy.left -= r_enemy.speed;
			//	r_enemy.right -= r_enemy.speed;

			//	r_enemy.eyeimage = 3;
			//}
			//// 下向き
			//else if (mPlayer.y > r_enemy.y) {
			//	r_enemy.y += r_enemy.speed;

			//	r_enemy.top += r_enemy.speed;
			//	r_enemy.bottom += r_enemy.speed;

			//	r_enemy.eyeimage = 2;
			//}
			//// 上向き
			//else if (mPlayer.y < r_enemy.y) {
			//	r_enemy.y -= r_enemy.speed;

			//	r_enemy.top -= r_enemy.speed;
			//	r_enemy.bottom -= r_enemy.speed;

			//	r_enemy.eyeimage = 0;
			//}
		}
		// 左向き
		else if (r_enemy.angle == 4) {
			// 左向き
			//if (mPlayer.x < r_enemy.x) {
				r_enemy.x -= r_enemy.speed;

				r_enemy.left -= r_enemy.speed;
				r_enemy.right -= r_enemy.speed;

				r_enemy.eyeimage = 3;
			//}
			//// 右向き
			//if (mPlayer.x > r_enemy.x) {
			//	r_enemy.x += r_enemy.speed;

			//	r_enemy.left += r_enemy.speed;
			//	r_enemy.right += r_enemy.speed;

			//	r_enemy.eyeimage = 1;
			//}
			//// 下向き
			//if (mPlayer.y > r_enemy.y) {
			//	r_enemy.y += r_enemy.speed;

			//	r_enemy.top += r_enemy.speed;
			//	r_enemy.bottom += r_enemy.speed;

			//	r_enemy.eyeimage = 2;
			//}
			//// 上向き
			//else if (mPlayer.y < r_enemy.y) {
			//	r_enemy.y -= r_enemy.speed;

			//	r_enemy.top -= r_enemy.speed;
			//	r_enemy.bottom -= r_enemy.speed;

			//	r_enemy.eyeimage = 0;
			//}
		}
		//下向き
		else if (r_enemy.angle == 3) {
			//下向き
			//if (mPlayer.y > r_enemy.y) {
				r_enemy.y += r_enemy.speed;

				//当たり判定
				r_enemy.top += r_enemy.speed;
				r_enemy.bottom += r_enemy.speed;

				r_enemy.eyeimage = 2;
			//}
			//// 上向き
			//if (mPlayer.y < r_enemy.y) {
			//	r_enemy.y -= r_enemy.speed;

			//	r_enemy.top -= r_enemy.speed;
			//	r_enemy.bottom -= r_enemy.speed;

			//	r_enemy.eyeimage = 0;
			//}
			//// 左向き
			//else if (mPlayer.x < r_enemy.x) {
			//	r_enemy.x -= r_enemy.speed;

			//	r_enemy.left -= r_enemy.speed;
			//	r_enemy.right -= r_enemy.speed;

			//	r_enemy.eyeimage = 3;
			//}
			//// 右向き
			//else if (mPlayer.x > r_enemy.x) {
			//	r_enemy.x += r_enemy.speed;

			//	r_enemy.left += r_enemy.speed;
			//	r_enemy.right += r_enemy.speed;

			//	r_enemy.eyeimage = 1;
			//}
		}
		//上向き
		else if (r_enemy.angle == 1) {
			//上向き
			//if (mPlayer.y < r_enemy.y) {
				r_enemy.y -= r_enemy.speed;

				//当たり判定
				r_enemy.top -= r_enemy.speed;
				r_enemy.bottom -= r_enemy.speed;

				r_enemy.eyeimage = 0;
			//}
			// 下向き
			//if (mPlayer.y > r_enemy.y) {
			//	r_enemy.y += r_enemy.speed;

			//	r_enemy.top += r_enemy.speed;
			//	r_enemy.bottom += r_enemy.speed;

			//	r_enemy.eyeimage = 2;
			//}
			//// 左向き
			//else if (mPlayer.x < r_enemy.x) {
			//	r_enemy.x -= r_enemy.speed;

			//	r_enemy.left -= r_enemy.speed;
			//	r_enemy.right -= r_enemy.speed;

			//	r_enemy.eyeimage = 3;
			//}
			//// 右向き
			//else if (mPlayer.x > r_enemy.x) {
			//	r_enemy.x += r_enemy.speed;

			//	r_enemy.left += r_enemy.speed;
			//	r_enemy.right += r_enemy.speed;

			//	r_enemy.eyeimage = 1;
			//}
		}
	}
	else if (r_enemy.R_Hitflg == TRUE) { // パワーエサを取った時
		if (r_enemy.PR_Hitflg == FALSE) { // プレイヤーと当たっていなかったら
			r_enemy.speed = 1.6;
			if (r_enemy.absX > r_enemy.absY) { // 絶対値Xの値が大きいとき
			    //右向き
				if (mPlayer.x < r_enemy.x) {
					r_enemy.x += r_enemy.speed;

					//当たり判定
					r_enemy.left += r_enemy.speed;
					r_enemy.right += r_enemy.speed;
				}
				//左向き
				else if (mPlayer.x > r_enemy.x) {
					r_enemy.x -= r_enemy.speed;

					r_enemy.left -= r_enemy.speed;
					r_enemy.right -= r_enemy.speed;
				}
			}
			if (r_enemy.absX < r_enemy.absY) { // 絶対値Yの値が大きいとき
				//上向き
				if (mPlayer.y > r_enemy.y) {
					r_enemy.y -= r_enemy.speed;

					//当たり判定
					r_enemy.top -= r_enemy.speed;
					r_enemy.bottom -= r_enemy.speed;
				}
				//下向き
				else if (mPlayer.y < r_enemy.y) {
					r_enemy.y += r_enemy.speed;

					//当たり判定
					r_enemy.top += r_enemy.speed;
					r_enemy.bottom += r_enemy.speed;
				}
			}
		}
		else if (r_enemy.PR_Hitflg == TRUE) { // プレイヤーと当たっていたら初期位置に戻る
			if (r_enemy.eyeflg == TRUE) {
				r_enemy.speed = 3;
				if (r_enemy.absX > r_enemy.absY) { // 絶対値Xの値が大きいとき
					//右向き
					if (ENEMY_POS_X > r_enemy.x + 1) {
						r_enemy.x += r_enemy.speed;

						//当たり判定
						r_enemy.left += r_enemy.speed;
						r_enemy.right += r_enemy.speed;

						r_enemy.eyeimage = 1;
					}
					//左向き
					else if (ENEMY_POS_X < r_enemy.x - 1) {
						r_enemy.x -= r_enemy.speed;

						//当たり判定
						r_enemy.left -= r_enemy.speed;
						r_enemy.right -= r_enemy.speed;

						r_enemy.eyeimage = 3;
					}
				}
				if (r_enemy.absX < r_enemy.absY) { // 絶対値Yの値が大きいとき
					//下向き
					if (ENEMY_POS_Y > r_enemy.y + 1) {
						r_enemy.y += r_enemy.speed;

						//当たり判定
						r_enemy.top += r_enemy.speed;
						r_enemy.bottom += r_enemy.speed;

						r_enemy.eyeimage = 2;
					}
					//上向き
					else if (ENEMY_POS_Y < r_enemy.y - 1) {
						r_enemy.y -= r_enemy.speed;

						//当たり判定
						r_enemy.top -= r_enemy.speed;
						r_enemy.bottom -= r_enemy.speed;

						r_enemy.eyeimage = 0;
					}
				}
				// 初期位置に戻った時
				if (ENEMY_POS_X == r_enemy.x) {
					r_enemy.eyeflg = FALSE;
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
	++count;  // カウント開始
	if (count >= 8) {  // 値によってアニメーションのスピードが変化する0に近い程速い
		r_enemy.image++;
		r_enemy.izikeimage++;
		r_enemy.e_izikeimage++;
		count = 0;  // カウントリセット
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
	if (r_enemy.x >= 1280) {
		r_enemy.x = 0;
	}
	else if (r_enemy.x <= 0) {
		r_enemy.x = 1280;
	}

	// イジケ状態フラグ
	if (r_enemy.R_Hitflg == TRUE) {
		++r_enemy.ER_count;
	}

	
	if (mPlayer.Hitflg == TRUE) {
		HitCount++;
		int a = 5; int b = 10;
		if (HitCount == a ) {
			r_enemy.image = 0;
			a += 5;
		}
		else if (HitCount == b) {
			r_enemy.image = 1;
			b += 5;
		}
		if (HitCount == 80) {
			flg = TRUE;
		}
	}
}

void R_ENEMY::Draw() {
	if (mPlayer.Hitflg == TRUE && flg == FALSE) {		//足だけが動く処理
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[r_enemy.image], TRUE, FALSE);
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE);
	}
	//PCに当たったときに消える
	if(flg == TRUE) {
		/*DrawRotaGraph(r_enemy.x, r_enemy.y, 0, 0, images[r_enemy.image], TRUE, FALSE); 
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE); */
	}
	else if(mStage.StateFlg == TRUE){		//スタート時の固定表示
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[0], TRUE, FALSE); 
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, eyesimages[3], TRUE, FALSE); 
	}

	if (r_enemy.R_Hitflg == FALSE && mStage.MoveFlg == TRUE && mPlayer.Hitflg == FALSE) { // パワーエサを取っていないかつ、Moveflgで動いて可能かつ、Pacに当たっていない時
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[r_enemy.image], TRUE, FALSE); // 敵キャラ表示
		DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE); // 敵キャラの目表示
		DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
		DrawString(0, 150, "パワーエサ：無し", 0x0000ff);
	}
	else if (r_enemy.R_Hitflg == TRUE) { // パワーエサを取っていたら
		if (r_enemy.PR_Hitflg == FALSE) { // プレイヤーと当たっていなければ
			if (r_enemy.ER_count <= 480) {
				DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[r_enemy.izikeimage], TRUE, FALSE); // イジケ状態表示
				DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
				DrawString(0, 150, "パワーエサ：あり：10秒カウント", 0x0000ff);
			}
			else if (r_enemy.ER_count > 480 && r_enemy.ER_count <= 600) {
				r_enemy.ER_Hitflg = TRUE;
				DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, images[r_enemy.e_izikeimage], TRUE, FALSE); // イジケ状態表示
				DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
				DrawString(0, 150, "パワーエサ：あり：残り2秒", 0x0000ff);
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
				DrawRotaGraph(r_enemy.x, r_enemy.y, 0.75, 0, eyesimages[r_enemy.eyeimage], TRUE, FALSE); // 敵キャラの目表示
				DrawBox(r_enemy.left, r_enemy.top, r_enemy.right, r_enemy.bottom, 0x00ffff, FALSE); // 当たり判定描画
				DrawString(0, 150, "パワーエサ：あり：プレイヤーと接触", 0x0000ff);
			}
			else if (r_enemy.eyeflg == FALSE) { // 目状態のエネミーが初期位置に戻ったら
				r_enemy.R_Hitflg = FALSE;
				r_enemy.PR_Hitflg = FALSE;
				r_enemy.ER_Hitflg = FALSE;
				r_enemy.ER_count = 0;
				mPlayer.timercount = 0;
				DrawString(0, 150, "パワーエサ：無し：初期位置に戻りました", 0x0000ff);
			}
		}
	}

	if (r_enemy.Initiaflg == TRUE) {
		// 初期位置に戻す
		r_enemy.x = ENEMY_POS_X;
		r_enemy.y = ENEMY_POS_Y;
		r_enemy.top = ENEMY_POS_Y - ENEMY_STAGE_HITBOX;
		r_enemy.left = ENEMY_POS_X - ENEMY_STAGE_HITBOX;
		r_enemy.right = ENEMY_POS_X + ENEMY_STAGE_HITBOX;
		r_enemy.bottom = ENEMY_POS_Y + ENEMY_STAGE_HITBOX;
		r_enemy.Initiaflg = FALSE;
		flg = FALSE;
		HitCount = 0;

		if (mStage.life == 2) {
			mStage.life = 1;
		}
		else if(mStage.life == 1) {
			mStage.life = 0;
		}
		else if(mStage.life == 0){
			mStage.GameOverFlg = TRUE;
		}
	}

	DrawString(0, 230, "Enemy", 0xff00ff);
	DrawFormatString(0, 250, 0x0000ff, "Player&EnemyのX座標の距離\n%d", r_enemy.xx);
	DrawFormatString(0, 290, 0x0000ff, "Player&EnemyのY座標の距離\n%d", r_enemy.yy);
	DrawFormatString(0, 330, 0x0000ff, "Player&EnemyのXとYを足した座標の距離\n%d", r_enemy.xy2);
	DrawFormatString(0, 370, 0x0000ff, "Player&EnemyのXとYを足した座標を2乗した距離\n%d", r_enemy.xy);

	DrawString(0, 410, "Player", 0xff00ff);
	DrawFormatString(0, 430, 0x0000ff, "Player&EnemyのX座標の距離\n%d", mPlayer.xx);
	DrawFormatString(0, 470, 0x0000ff, "Player&EnemyのY座標の距離\n%d", mPlayer.yy);
	DrawFormatString(0, 510, 0x0000ff, "Player&EnemyのXとYを足した座標の距離\n%d", mPlayer.xy2);
	DrawFormatString(0, 550, 0x0000ff, "Player&EnemyのXとYを足した座標を2乗した距離\n%d", mPlayer.xy);
}