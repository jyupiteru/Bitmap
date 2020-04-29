
#define _CRT_SECURE_NO_WARNINGS

#include"../Sub/Sub.h"
#include<Windows.h>
#include<stdio.h>

#pragma once

#define COLOR_BLUE		0
#define COLOR_GREEN		1
#define COLOR_RED		2


#define IMAGE_HEIGHT	10
#define IMAGE_WIDTH		50

typedef struct{
	COORD halfSize;

	CHAR_INFO  imageData[IMAGE_HEIGHT][IMAGE_WIDTH];
}tagIMAGE_INFO;

typedef struct
{
	CHAR_INFO ScreenInfo[IMAGE_HEIGHT][IMAGE_WIDTH];//�X�N���[���ɓ]������CHAR_INFO �����Ɏg�������摜���R�s�[
	COORD size = { IMAGE_WIDTH , IMAGE_HEIGHT };//�������މ摜�̃T�C�Y
	COORD StartPoint = { 0,0 };//DrawStartPoint���g���`�ʂ���̂�0,0�ł悵
	SMALL_RECT ScreenData = { 0,0,IMAGE_WIDTH - 1,IMAGE_HEIGHT };//�������މ摜�̏㉺�A���E������

}tagSCREEN_INFO;

void BitmapRead(const char* name, tagIMAGE_INFO* imageinfo);

void BitmapSet(COORD pos, tagIMAGE_INFO* imageinfo);

int Define16Color(int blue,int green,int red);

//HIDE_COLOR�ɂ͓��߂�����F�����邱��

void ResetScreen(void);//��ʗpCHAR_INFO�����Z�b�g����

void Draw(void);//�X�N���[���pCHAR_INFO�𗠃X�N���[���ɃR�s�[
