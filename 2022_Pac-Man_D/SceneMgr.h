#pragma once
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

typedef enum {
	eScene_Title,
	eScene_Game,
	eScene_End,

	eScene_None,
}eScene;

void SceneMgr_Initialize();
void SceneMgr_Finalize();
void SceneMgr_Update();
void SceneMgr_Draw();

class SceneMgr {
private:

public:
	void SceneMgr_Initialize();
	void SceneMgr_Finalize();
	void SceneMgr_Update();
	void SceneMgr_Draw();
};

extern SceneMgr mSceneMgr;

void SceneMgr_ChangeScene(eScene nextScene);


