#pragma once
class Title {
private:
	int title;
	int MoveY = 720;
public:
	void Title_Initialize();
	void Title_Draw();
	void Title_Update();
	void Title_Finalize();
};

extern Title mTitle;


static int MenuNumber = 0;	//ƒƒjƒ…[ŠÇ——p•Ï”