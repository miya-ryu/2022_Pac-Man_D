#pragma once

// �e�N���X��
class R_ENEMY {
private:

public:
	struct Enemy;
	R_ENEMY();   //c�����Initialize�Ɠ�������
	~R_ENEMY();  //c�����FInalize�Ɠ�������
	void Update();
	void Draw();

	// �G�̉摜�ۊǔz��
	int Enemy_image[20];
	// �G�̍��W��ۊǂ���ϐ�
	int EnemyX;
	int EnemyY;
	int w, h;	// �� w ���� h;
	int CheckHit;
	//int HitBoxEnemy(R_ENEMY* e);
};

extern R_ENEMY r_enemy;