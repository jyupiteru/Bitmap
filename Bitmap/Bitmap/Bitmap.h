
#define _CRT_SECURE_NO_WARNINGS

#include"../Sub/Sub.h"
#include<Windows.h>
#include<stdio.h>

#pragma once

#define COLOR_BLUE		0
#define COLOR_GREEN		1
#define COLOR_RED		2


#define SCREEN_HEIGHT	60
#define SCREEN_WIDTH	60

typedef struct{
	COORD halfSize;

	CHAR_INFO  imageData[SCREEN_HEIGHT][SCREEN_WIDTH];
}tagIMAGE_INFO;

typedef struct
{
	CHAR_INFO ScreenInfo[SCREEN_HEIGHT][SCREEN_WIDTH];//�X�N���[���ɓ]������CHAR_INFO �����Ɏg�������摜���R�s�[
	COORD size = { SCREEN_WIDTH , SCREEN_HEIGHT };//�������މ摜�̃T�C�Y
	COORD StartPoint = { 0,0 };//DrawStartPoint���g���`�ʂ���̂�0,0�ł悵
	SMALL_RECT ScreenData = { 0,0,SCREEN_WIDTH - 1,SCREEN_HEIGHT };//�������މ摜�̏㉺�A���E������

}tagSCREEN_INFO;

void BitmapRead(const char* name, tagIMAGE_INFO* imageinfo);

void BitmapSet(COORD pos, tagIMAGE_INFO* imageinfo);

int Define16Color(int blue,int green,int red);

//HIDE_COLOR�ɂ͓��߂�����F�����邱��

void ResetScreen(void);//��ʗpCHAR_INFO�����Z�b�g����

void Draw(void);//�X�N���[���pCHAR_INFO�𗠃X�N���[���ɃR�s�[
