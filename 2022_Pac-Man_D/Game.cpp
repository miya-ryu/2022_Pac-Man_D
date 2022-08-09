#include "DxLib.h"
#include "Game.h"
#include "Player.h"

Game mGame;

void Game::Game_Update() {
	mPlayer.Player_Update();
}

void Game::Game_Draw(){
	mPlayer.Player_Draw();
}