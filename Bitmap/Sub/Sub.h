
#pragma once
#include<Windows.h>

/**
* @brief 文字を表示させる関数
* @param buf　アドレス渡し 表示させたい文字を入れる 数字の変数は表示不可
*/
void PrintToScreen(const char *buf,COORD pos);