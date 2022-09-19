#include "DxLib.h"
#include "Game.h"
#include "Input.h"
#include "Player.h"
#include "Red_Enemy.h"
#include "Pink_Enemy.h"
#include "Blue_Enemy.h"
#include "Orange_Enemy.h"
#include "Stage.h"
#include "title.h"
#include "sound.h"

Game mGame;

void Game::Game_Initialize() {
	mPlayer.Player_Initialize();
	mStage.Stage_Initialize();
	r_enemy.Initialize();
	b_enemy.Initialize();
	mSound.Sound_Handle();
	mSound.SoundStart();
}

void Game::Game_Update() {
	mSound.SoundUpdate();
	mPlayer.Player_Update();
	r_enemy.Update();
	//p_enemy.Update();
	b_enemy.Update();
	//o_enemy.Update();
	mStage.Stage_Update();
	if (iNowKey & PAD_INPUT_7 || iNowKey & PAD_INPUT_9) {
		DxLib_End();
	}
}

void Game::Game_Draw(){
	mStage.Stage_Draw(); 
	mPlayer.Player_Draw();
	r_enemy.Draw();
	//p_enemy.Draw();
	b_enemy.Draw();
	//o_enemy.Draw();
}