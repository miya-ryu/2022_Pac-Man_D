#pragma once

static int f_Time;  // ����J�n����
static int f_Count;  // �J�E���^
static float f_Fps;  // fps

class System {
private:

public:
	bool Update();
	void Draw();
	void Wait();

	const int F = 60;  // ���ϗp�T���v�����l
	const int FPS = 60;  // FPS�ݒ�
};

extern System mSystem;