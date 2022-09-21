#include "SceneMgr.h"
#include "title.h"
#include "Game.h"
#include "system.h"

static eScene mScene = eScene_Title;	//現シーンの管理変数
static eScene mNextScene = eScene_None; //次シーンの管理変数

static void SceneMgr_InitializeModule(eScene scene);
static void SceneMgr_FinalizeModule(eScene scene);

//初期化
void SceneMgr_Initialize() {
	SceneMgr_InitializeModule(mScene);
}

//終了処理
void SceneMgr_Finalize() {
	SceneMgr_FinalizeModule(mScene);
}

//更新
void SceneMgr_Update() {
	mSystem.Update();
	if (mNextScene != eScene_None) {
		SceneMgr_FinalizeModule(mScene);
		mScene = mNextScene;
		mNextScene = eScene_None;
		SceneMgr_InitializeModule(mScene);
	}
	switch (mScene)
	{
	case eScene_Title:
		mTitle.Title_Update();
		break;
	case eScene_Game:
		mGame.Game_Update();
		break;
	}
}

//描画
void SceneMgr_Draw() {
	switch (mScene)
	{
	case eScene_Title:
		mTitle.Title_Move();
		mTitle.Title_Draw();
		break;
	case eScene_Game:
		mGame.Game_Draw();
		break;
	}
	//mSystem.Draw();
}


void SceneMgr_ChangeScene(eScene NextScene) {
	mNextScene = NextScene;				//次のシーンセット
}

//sceneモジュールを初期化
static void SceneMgr_InitializeModule(eScene scene) {
	mSystem.Initialize();
	switch (scene)
	{
	case eScene_Title:
		mTitle.Title_Initialize();
		break;
	case eScene_Game:
		mGame.Game_Initialize();
		break;


	}
}

//sceneモジュール終了処理
static void SceneMgr_FinalizeModule(eScene scene) {
	switch (scene)
	{
	case eScene_Title:
		mTitle.Title_Finalize();
		break;
	}
}