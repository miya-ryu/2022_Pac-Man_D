#pragma once

// 親クラス赤
class R_ENEMY {
private:

public:
	R_ENEMY();   //c言語のInitializeと同じ処理
	~R_ENEMY();  //c言語のFInalizeと同じ処理
	void Update();
	void Draw();

	// 敵の画像保管配列
	int Enemy_image[20];
	// 敵の座標を保管する変数
	int EnemyX;
	int EnemyY;
};

extern R_ENEMY r_enemy;