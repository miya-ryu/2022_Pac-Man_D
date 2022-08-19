#include "DxLib.h"
#include "Game.h"
#include "Input.h"
#include "Player.h"
#include "Stage.h"

Game mGame;

void Game::Game_Update() {
	mPlayer.Player_Update();
	mStage.Stage_Update();
	if (iNowKey & PAD_INPUT_7 || iNowKey & PAD_INPUT_9) {
		DxLib_End();
	}

}

void Game::Game_Draw(){
	mStage.Stage_Draw();
	mPlayer.Player_Draw();
}