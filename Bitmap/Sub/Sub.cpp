
#include "Sub.h"

/**
* @brief ������\��������֐�
* @param buf�@�A�h���X�n�� �\�������������������� �����̕ϐ��͕\���s��
*/
void PrintChar(const char *buf,COORD pos)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD wnum;
	SetConsoleCursorPosition(handle, pos);
	WriteConsole(handle, buf, strlen(buf), &wnum, NULL);
	//writeconsole(�������ރA�h���X,�\�����镶����A������̐��A�A�\��ς݂��Ȃ炸NULL�j
}

/**
* @brief ������\������@�����̕ϐ��\���� 20���܂ŕ\���\
* @param number �\��������������������
*/
void PrintNum(int  num,COORD pos)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	char buff[21];
	snprintf(buff, sizeof(buff), "%d", num);//int�^����char�^�֕ϊ�����
	DWORD wnum;
	SetConsoleCursorPosition(handle, pos);
	WriteConsole(handle, buff, strlen(buff), &wnum, NULL);
}