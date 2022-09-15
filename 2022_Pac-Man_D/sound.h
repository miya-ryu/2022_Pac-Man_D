#pragma once

class Sound {
private:
	bool Flg = false;
public:
	int numSound = 2;
	int bgm[15];
	bool EatingFlg = false;
	bool Izike = false;		//イジケモードのフラグ
	int Vol = 100;			//SE音量変更
	void Sound_Handle();
	void SoundStart();
	void SoundUpdate();
	void SoundDelete();
	void SoundStop();
};

extern Sound mSound;


