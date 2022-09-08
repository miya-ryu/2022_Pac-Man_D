#pragma once

class Sound {
private:
	int bgm[15];
	int Flg = false;
public:
	void Sound_Handle();
	void SoundStart();
	void SoundUpdate();
	void SoundDelete();
	void SoundStop();
};

extern Sound mSound;

