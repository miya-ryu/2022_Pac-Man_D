#include "DxLib.h"
#include <math.h>
#include "system.h"

System mSystem;

bool System::Update() {
	if (f_Count == 0) {  // 1�t���[���ڂɎ������L��
		f_Time = GetNowCount();  // ���݂̃J�E���^�̒l���擾
	}
	if (f_Count == F) {  // �������ϐ��l�Ɠ����Ȃ�
		int t = GetNowCount();  // t�Ɍ��݂̃J�E���^�̒l����
		f_Fps = 1000.f / ((t - f_Time) / (float)F);  // 
		f_Count = 0;  // �J�E���^��0�ɂ���
		f_Time = t;  // ����J�n������t����
	}
	f_Count++;  // �J�E���g�����Z
	return true;
}
void System::Draw() {
	// FPS��\��
	DrawFormatString(950, 400, GetColor(255, 255, 255), "%.1f", f_Fps);
}
void System::Wait() {
	int tookTime = GetNowCount() - f_Time;  // ������������
	int waitTime = f_Count * 1000 / FPS - tookTime;  // �҂ׂ�����
	if (waitTime > 0) {  // �҂ׂ����Ԃ�0���傫�����
		Sleep(waitTime);  // �ҋ@
	}
}