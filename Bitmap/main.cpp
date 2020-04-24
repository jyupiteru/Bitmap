
#include"Bitmap/Bitmap.h"
#include<stdio.h>

int main(void)
{
	tagIMAGE_INFO image;
	COORD pos = { 0,0 };

	BitmapRead("",&image);

	BitmapDraw(pos, &image);

	getchar();
}