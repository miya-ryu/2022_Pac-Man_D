#include "DxLib.h"

int iOldKey; //�O��̓��̓L�[
int iNowKey; //����̓��̓L�[
int iKeyFlg; //���̓L�[���

void InputKey(void) {
	//���̓L�[�擾
	iOldKey = iNowKey;
	iNowKey = GetJoypadInputState(DX_INPUT_PAD1);
	iKeyFlg = iNowKey & ~iOldKey;
}