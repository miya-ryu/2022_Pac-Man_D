#pragma once

class Sound {
private:
	bool Flg = FALSE;
public:
	int numSound = 2;
	int bgm[15];
	bool Izike = FALSE;		//�C�W�P���[�h�̃t���O
	int Vol = 100;			//SE���ʕύX
	void Sound_Handle();
	void SoundStart();
	void SoundUpdate();
	void SoundDelete();
	void SoundStop();
};

extern Sound mSound;


