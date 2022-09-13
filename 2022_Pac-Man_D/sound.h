#pragma once

class Sound {
private:
	int Flg = false;
public:
	int numSound = 2;
	int bgm[15];
	int EatingFlg = false;
	void Sound_Handle();
	void SoundStart();
	void SoundUpdate();
	void SoundDelete();
	void SoundStop();
};

extern Sound mSound;


