
#pragma once
#include<Windows.h>
#include<stdio.h>

/**
* @brief 文字を表示させる関数
* @param buf　アドレス渡し 表示させたい文字を入れる 数字の変数は表示不可
*/
void PrintChar(const char *buf,COORD pos);

/**
* @brief 数字を表示する　数字の変数表示可 20桁まで表示可能
* @param number 表示させたい数字を入れる
*/
void PrintNum(int  num,COORD pos);