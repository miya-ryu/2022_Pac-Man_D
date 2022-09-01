#include "DxLib.h"
#include "title.h"
#include "Input.h"

Title mTitle;

void Title::Title_Initialize() {
	title = LoadGraph("images / title/title.png");
}

void Title::Title_Update() {
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		DeleteGraph(title);
	}Title_Draw();
}

void Title::Title_Draw() {
	DrawGraph(0, 0, title, true);
}