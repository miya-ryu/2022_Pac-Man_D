#include "DxLib.h"
#include "sound.h"
#include "Player.h"

Sound mSound; 

int numSound = 2;

//“Ç‚İ‚İ
void Sound::Sound_Handle() {
	bgm[0] = LoadSoundMem("sounds/Game.mp3");
	bgm[1] = LoadSoundMem("sounds/1CreditSound.mp3");
	bgm[2] = LoadSoundMem("sounds/2StartMusic.mp3");
	bgm[3] = LoadSoundMem("sounds/PacEating.mp3");
	bgm[4] = LoadSoundMem("sounds/4ExtendSound.mp3");
	bgm[5] = LoadSoundMem("sounds/5GhostMove_Normal.mp3");
	bgm[6] = LoadSoundMem("sounds/6GhostMove_Spart1.mp3");
	bgm[7] = LoadSoundMem("sounds/7GhostMove_Spart2.mp3");
	bgm[8] = LoadSoundMem("sounds/8GhostMove_Spart3.mp3");
	bgm[9] = LoadSoundMem("sounds/9GhostMove_Spart4.mp3");
	bgm[10] = LoadSoundMem("sounds/10Pacman_FruitEating.mp3");
	bgm[11] = LoadSoundMem("sounds/11Ghost_Izike.mp3");
	bgm[12] = LoadSoundMem("sounds/12Pacman_GhostEating.mp3");
	bgm[13] = LoadSoundMem("sounds/13Ghost_GoHome.mp3");
	bgm[14] = LoadSoundMem("sounds/14Miss.mp3");
	bgm[15] = LoadSoundMem("sounds/15CoffeBraic.mp3");
}

//Ä¶
void Sound::SoundStart() {
	Sound_Handle();
	ChangeVolumeSoundMem( 100, bgm[numSound]);			//‰¹—Ê’²®‚O`‚Q‚T‚T
	PlaySoundMem(bgm[numSound], DX_PLAYTYPE_BACK);		//Œø‰Ê‰¹Ä¶
	mSound.Flg = true;
}

void Sound::SoundUpdate() {
	if (mSound.Flg == true) {
		if (mPlayer.Hitflg == TRUE) {			//ƒpƒbƒNƒ}ƒ““G‚É“–‚½‚Á‚½‚Æ‚«‚ÌSE/€‚Ê‰¹
			numSound = 14;
			mSound.SoundStart();
			mSound.Flg = false;
		}
	}
	//if (EatingFlg == true) {					//H‚×‚é‚Æ‚«‚Ì‰¹
	//	numSound = 3;
	//	mSound.SoundStart();
	//}

}

//íœ
//void Sound::SoundDelete() {
//	DeleteSoundMem(bgm);
//}

//ƒXƒgƒbƒv
//void Sound::SoundStart() {
//	StopSoundMem(bgm[3]);
//}