#pragma once

class Sound {
private:
	bool Flg = FALSE;
public:
	int numSound = 2;
	int bgm[15];
	bool Izike = FALSE;		//イジケモードのフラグ
	int Vol = 100;			//SE音量変更
	void Sound_Handle();
	void SoundStart();
	void SoundUpdate();
	void SoundDelete();
	void SoundStop();
};

extern Sound mSound;


