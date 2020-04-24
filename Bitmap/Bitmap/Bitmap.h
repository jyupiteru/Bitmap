
#define _CRT_SECURE_NO_WARNINGS

#include"../Sub/Sub.h"
#include<Windows.h>
#include<stdio.h>

#pragma once

#define COLOR_BLUE		0
#define COLOR_GREEN		1
#define COLOR_RED		2


#define IMAGE_HEIGHT	100
#define IMAGE_WIDTH		100

typedef struct{
	int width;
	int height;
	CHAR_INFO  imageData[IMAGE_HEIGHT][IMAGE_WIDTH];
}tagIMAGE_INFO;


void BitmapRead(const char* name, tagIMAGE_INFO* imageinfo);

void BitmapDraw(COORD pos, tagIMAGE_INFO* imageinfo);

int Define16Color(int blue,int green,int red);