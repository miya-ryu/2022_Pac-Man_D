#pragma once

class Sound {
private:
	int bgm[15];
public:
	void Sound_Handle();
	void SoundStart();
	void SoundDelete();
	void SoundStop();
};

extern Sound mSound;

