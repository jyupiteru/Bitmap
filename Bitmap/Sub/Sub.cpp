
#include "Sub.h"

/**
* @brief ������\��������֐�
* @param buf�@�A�h���X�n�� �\�������������������� �����̕ϐ��͕\���s��
*/
void PrintToScreen(const char *buf,COORD pos)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD wnum;
	SetConsoleCursorPosition(handle, pos);
	WriteConsole(handle, buf, strlen(buf), &wnum, NULL);
	//writeconsole(�������ރA�h���X,�\�����镶����A������̐��A�A�\��ς݂��Ȃ炸NULL�j
}

