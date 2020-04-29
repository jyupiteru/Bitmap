
#include"Bitmap/Bitmap.h"
#include<stdio.h>

int main(void)
{
	ResetScreen();
	tagIMAGE_INFO image;
	COORD pos = { 28,28 };

	BitmapRead("image/colorsample.bmp",&image);

	BitmapSet(pos, &image);
	
	Draw();
	getchar();
}