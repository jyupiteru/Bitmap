
#define _CRT_SECURE_NO_WARNINGS

#include<Windows.h>
#include<stdio.h>

#pragma once

//!@brief	色振り分け時に使用するマクロ
enum  E_COLOR{
BLUE = 0,	//!<青
GREEN,		//!<緑
RED			//!<赤
};

//!@brief		画像の縦の最大サイズ
//!@details		偶数で指定すること
#define IMAGE_HEIGHT 50

//!@brief		画像の横の最大サイズ
//!@details		偶数で指定すること
#define IMAGE_WIDTH  50


//!@brief		描写先の縦の最大サイズ
#define SCREEN_HEIGHT	100

//!@brief		描写先の横の最大サイズ
#define SCREEN_WIDTH	100



//!@brief	画像の情報を持つ構造体
typedef struct{
	COORD halfSize;										//!<画像の半分の大きさ
	CHAR_INFO  imageData[IMAGE_HEIGHT][IMAGE_WIDTH];	//!<画像情報（色）を保持
}tagIMAGE_INFO;


//!@brief	描写先の情報を持つ構造体
//!@details	以下パレットと呼ぶ
typedef struct
{
	CHAR_INFO ScreenInfo[SCREEN_HEIGHT][SCREEN_WIDTH];			//!<スクリーンに転送するCHAR_INFO ここに使いたい画像をコピー
	COORD size = { SCREEN_WIDTH , SCREEN_HEIGHT };				//!<書き込む画像のサイズ
	COORD StartPoint = { 0,0 };									//!<3Dにおけるワールド座標のようなもの
	SMALL_RECT ScreenData = { 0,0,SCREEN_WIDTH - 1,SCREEN_HEIGHT };//!<書き込む画像の上下、左右を入れる
}tagSCREEN_INFO;


//!@brief			BMP画像の読み込み
//!@param name		読み込みたい画像をアドレス込みで入れる
//!@param imageifo	画像の情報を入れる構造体のアドレスを入れる
void BitmapRead(const char* name, tagIMAGE_INFO* imageinfo);


//!@brief			BMP画像をパレットにセットする関数
//!@param pos		画像を描写する中心位置を指定
//!@param imageinfo 描写したい画像情報を入れる
void BitmapSet(COORD pos, tagIMAGE_INFO* imageinfo);


//!@brief		色の分類関数
//!@param blue	青の情報を入れる
//!@param green	緑の情報を入れる
//!@param red	赤の情報を入れる
//!@details		ここで最も近い16色に分類している
int Define16Color(int blue,int green,int red);


//!@brief		パレットを初期化する関数
void ResetScreen(void);


//!@brief		パレットをコンソールに転送する関数
void Draw();