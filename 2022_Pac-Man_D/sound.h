#pragma once

class Sound {
private:
	int bgm[16];
public:
	void Sound_Handle();
	void SoundStart();
	void SoundDelete();
	void SoundStop();
};

extern Sound mSound;

