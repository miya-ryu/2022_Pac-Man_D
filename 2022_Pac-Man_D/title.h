#pragma once
class Title {
private:
	int title;
	int TitleY = 720;
public:
	void Title_Move();
	void Title_Initialize();
	void Title_Draw();
	void Title_Update();
	void Title_Finalize();
};

extern Title mTitle;


static int MenuNumber = 0;	//メニュー管理用変数