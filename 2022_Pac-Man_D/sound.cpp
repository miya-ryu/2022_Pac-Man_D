#include "DxLib.h"
#include "sound.h"
#include "Player.h"
#include "Stage.h"
#include "Red_Enemy.h"

Sound mSound;

//�ǂݍ���
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

//�Đ�
void Sound::SoundStart() {
	ChangeVolumeSoundMem(Vol, bgm[numSound]);			//���ʒ����O�`�Q�T�T
	PlaySoundMem(bgm[numSound], DX_PLAYTYPE_BACK);		//���ʉ��Đ�
	Flg = true;
}

void Sound::SoundUpdate() {
	if (Flg == true && r_enemy.flg == TRUE) {
		if (mPlayer.Hitflg == TRUE) {			//�p�b�N�}���G�ɓ��������Ƃ���SE/���ʉ�
			Sound_Handle();
			numSound = 14;
			SoundStart();
			Flg = false;
		}
	}
	//�C�W�P��ԃt���O
	//if (r_enemy.R_Hitflg == TRUE) {
	//	StopSoundMem(bgm[5]);
	//	numSound = 11;
	//	SoundStart();
	//}
	//if (r_enemy.R_Hitflg == FALSE) {
	//	StopSoundMem(bgm[11]);
	//	//PlaySoundMem(bgm[5], DX_PLAYTYPE_BACK);
	//	numSound = 5;
	//	SoundStart();
	//}
}

//�폜
//void Sound::SoundDelete() {
//	DeleteSoundMem(bgm);
//}

//�X�g�b�v
//void Sound::SoundStart() {
//	StopSoundMem(bgm[3]);
//}