#include "DxLib.h"
#include <math.h>
#include "system.h"

System mSystem;

void System::Initialize() {
	mSystem.f_StartTime = 0;
	mSystem.f_Count = 0;
	mSystem.f_Fps = 0;
}
void System::Update() {
	if (f_Count == 0) {  // 1�t���[���ڂɎ������L��
		mSystem.f_StartTime = GetNowCount();  // ���݂̃J�E���^�̒l���擾
	}
	if (f_Count == F) {  // �������ϐ��l�Ɠ����Ȃ�
		int t = GetNowCount();  // t�Ɍ��݂̃J�E���^�̒l����
		mSystem.f_Fps = 1000.f / ((t - mSystem.f_StartTime) / (float)F);  // 
		mSystem.f_Count = 0;  // �J�E���^��0�ɂ���
		mSystem.f_StartTime = t;  // ����J�n������t����
	}
	mSystem.f_Count++;  // �J�E���g�����Z
}
void System::Draw() {
	// FPS��\��
	DrawFormatString(950, 400, GetColor(255, 255, 255), "%.1f", mSystem.f_Fps);
}
void System::Wait() {
	int tookTime = GetNowCount() - mSystem.f_StartTime;  // ������������
	int waitTime = mSystem.f_Count * 1000 / FPS - tookTime;  // �҂ׂ�����
	if (waitTime > 0) {  // �҂ׂ����Ԃ�0���傫�����
		Sleep(waitTime);  // �ҋ@
		DrawString(950, 420, "����", 0xffffff);
	}
}