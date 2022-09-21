#include "SceneMgr.h"
#include "title.h"
#include "Game.h"
#include "system.h"

static eScene mScene = eScene_Title;	//���V�[���̊Ǘ��ϐ�
static eScene mNextScene = eScene_None; //���V�[���̊Ǘ��ϐ�

static void SceneMgr_InitializeModule(eScene scene);
static void SceneMgr_FinalizeModule(eScene scene);

//������
void SceneMgr_Initialize() {
	SceneMgr_InitializeModule(mScene);
}

//�I������
void SceneMgr_Finalize() {
	SceneMgr_FinalizeModule(mScene);
}

//�X�V
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

//�`��
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
	mNextScene = NextScene;				//���̃V�[���Z�b�g
}

//scene���W���[����������
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

//scene���W���[���I������
static void SceneMgr_FinalizeModule(eScene scene) {
	switch (scene)
	{
	case eScene_Title:
		mTitle.Title_Finalize();
		break;
	}
}