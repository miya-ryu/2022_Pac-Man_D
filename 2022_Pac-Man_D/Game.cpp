#include "DxLib.h"
#include "Game.h"
#include "Player.h"
#include "Red_Enemy.h"
#include "Pink_Enemy.h"
#include "Blue_Enemy.h"
#include "Orange_Enemy.h"

Game mGame;

void Game::Game_Update() {
	mPlayer.Player_Update();
	r_enemy.Update();
	/*p_enemy.Update();
	b_enemy.Update();
	o_enemy.Update();*/
}

void Game::Game_Draw(){
	mPlayer.Player_Draw();
	r_enemy.Draw();
	/*p_enemy.Draw();
	b_enemy.Draw();
	o_enemy.Draw();*/
}