
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
	CHAR_INFO ScreenInfo[IMAGE_HEIGHT][IMAGE_WIDTH];//スクリーンに転送するCHAR_INFO ここに使いたい画像をコピー
	COORD size = { IMAGE_WIDTH , IMAGE_HEIGHT };//書き込む画像のサイズ
	COORD StartPoint = { 0,0 };//DrawStartPointを使い描写するので0,0でよし
	SMALL_RECT ScreenData = { 0,0,IMAGE_WIDTH - 1,IMAGE_HEIGHT };//書き込む画像の上下、左右を入れる

}tagSCREEN_INFO;

void BitmapRead(const char* name, tagIMAGE_INFO* imageinfo);

void BitmapSet(COORD pos, tagIMAGE_INFO* imageinfo);

int Define16Color(int blue,int green,int red);

//HIDE_COLORには透過させる色を入れること

void ResetScreen(void);//画面用CHAR_INFOをリセットする

void Draw(void);//スクリーン用CHAR_INFOを裏スクリーンにコピー
