#include "DxLib.h"
#include "Red_Enemy.h"
#include "Player.h"

R_ENEMY r_enemy;

R_ENEMY::R_ENEMY() {
	r_enemy.EnemyX = 640;
	r_enemy.EnemyY = 360;
}

R_ENEMY::~R_ENEMY() {
	//DeleteGraph(Enemy_image[0]);
}

void R_ENEMY::Update() {
	r_enemy.EnemyX += 3;
	if (r_enemy.EnemyX >= 1280) {
		r_enemy.EnemyX = 0;
	}
}

int	CheckHit(int EnemyX, int EnemyY, int w1, int h1, int x, int y, int w, int h)
{
    int L1 = EnemyX;
    int R1 = EnemyX + w1;
    int L2 = x;
    int R2 = x + w;

    if (R1 < L2) return 0;
    if (R2 < L1) return 0;

    int U1 = EnemyY;      // ã
    int D1 = EnemyY + h1; // ‰º(ã+c•)
    int U2 = x;
    int D2 = x + w;

    if (D1 < U2) return 0;
    if (D2 < U1) return 0;


    /* int R_ENEMY::HitBoxEnemy(R_ENEMY* e) {
         int dx1 = e->EnemyX - (e->w / 4);
         int dy1 = e->EnemyY - (e->h / 4);
         int dx2 = dx1 + e->w / 2;
         int dy2 = dy1 + e->h / 2.5;


     }*/

}
    void R_ENEMY::Draw() {
        LoadDivGraph("images/monster.png", 20, 20, 1, 32, 32, Enemy_image);
        DrawRotaGraph(r_enemy.EnemyX, r_enemy.EnemyY, 1, 0, Enemy_image[0], TRUE, FALSE);
    }
    


