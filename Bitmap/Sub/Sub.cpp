
#include "Sub.h"

/**
* @brief 文字を表示させる関数
* @param buf　アドレス渡し 表示させたい文字を入れる 数字の変数は表示不可
*/
void PrintToScreen(const char *buf,COORD pos)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD wnum;
	SetConsoleCursorPosition(handle, pos);
	WriteConsole(handle, buf, strlen(buf), &wnum, NULL);
	//writeconsole(書き込むアドレス,表示する文字列、文字列の数、、予約済みかならずNULL）
}

