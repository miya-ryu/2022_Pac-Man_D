#pragma once

class System {
private:

public:
	void Update();
	void Draw();
	void Wait();
	void Initialize();
	int f_StartTime;		//����J�n����
	int f_Count;			//�J�E���g
	float f_Fps;			//fps

	const int F = 60;  // ���ϗp�T���v�����l
	const int FPS = 60;  // FPS�ݒ�
};

extern System mSystem;