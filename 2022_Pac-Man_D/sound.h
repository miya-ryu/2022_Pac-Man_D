#pragma once

class Sound {
private:
	bool Flg = false;
public:
	int numSound = 2;
	int bgm[15];
	bool EatingFlg = false;
	bool Izike = false;		//�C�W�P���[�h�̃t���O
	int Vol = 100;			//SE���ʕύX
	void Sound_Handle();
	void SoundStart();
	void SoundUpdate();
	void SoundDelete();
	void SoundStop();
};

extern Sound mSound;


