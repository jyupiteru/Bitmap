
#pragma once
#include<Windows.h>
#include<stdio.h>

/**
* @brief ������\��������֐�
* @param buf�@�A�h���X�n�� �\�������������������� �����̕ϐ��͕\���s��
*/
void PrintChar(const char *buf,COORD pos);

/**
* @brief ������\������@�����̕ϐ��\���� 20���܂ŕ\���\
* @param number �\��������������������
*/
void PrintNum(int  num,COORD pos);