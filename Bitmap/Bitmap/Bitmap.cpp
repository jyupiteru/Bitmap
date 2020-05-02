
#include "Bitmap.h"

//色情報
int BasicColorData[16][3] = {//bgrの順
	{  12,  12,  12 },	//<?BLACK 
	{ 218,  55,   0 },	//<?DARK_BLUE
	{  15, 161,  19 },	//<?DARK_GREEN 
	{ 218, 151,  58 },	//<?DARK_CYAN
	{  30,  15, 197 },	//<?DARK_RED
	{ 151,  22, 135 },  //<?DARK_VIOLET
	{   0, 156, 197 },	//<?DARK_YELLOW
	{ 204, 204, 204 },	//<?GRAY
	{ 118, 118, 118 },	//<?LIGHT_GRAY
	{ 255, 120,  58 },  //<?BLUE
	{  12, 198,  22 },	//<?GREEN 
	{ 214, 214,  96 },	//<?CYAN
	{  83,  72, 230 },	//<?RED 
	{ 157,   0, 180 },	//<?VIOLET
	{ 168, 241, 249 },	//<?YELLOW 
	{ 242, 242, 242 }	//<?WHITE
};


unsigned char img[SCREEN_HEIGHT][SCREEN_WIDTH][3] = { 0 };
unsigned char img8bit[SCREEN_HEIGHT][SCREEN_WIDTH] = { 0 };
unsigned char bitColorData[256][3];


tagSCREEN_INFO screenInfo;

void BitmapRead(const char* name, tagIMAGE_INFO* imageinfo)
{
	int header;
	int headersize;
	unsigned int colorbit;	//何bitのビットマップか
	int usecolor;			//カラーパレットの色数
	int width;
	int height;
	FILE* fp = fopen(name, "rb");
	if (fp != NULL)
	{
		int i, k;
		int w_count;
		//ファイルヘッダ
		fseek(fp, 10, SEEK_SET);
		fread(&header, sizeof(int), 1, fp);			//10-13		ファイルヘッダーから画像データまでの距離


		//ここから情報ヘッダ
		fread(&headersize, sizeof(int), 1, fp);		//14-17		情報ヘッダのサイズが入っている

		fread(&width, sizeof(int), 1, fp);			//18-21		画像の横幅取得
		fread(&height, sizeof(int), 1, fp);			//22-25		画像の縦幅取得


		//情報ヘッダの形式によって内容が違うので
		switch (headersize)
		{
		case 12://OS2/2 V1形式
			fseek(fp, 24, SEEK_SET);//16
			fread(&colorbit, sizeof(unsigned int), 1, fp);
			break;

		case  40://windows 
		case 108://V4ヘッダ
		case 124://V5ヘッダ
		default: //OS/2 V2
			fseek(fp, 28, SEEK_SET);
			fread(&colorbit, sizeof(unsigned int), 1, fp);
			break;
		}


		//ここからカラーパレット coreヘッダ非対応
		if (colorbit == 8)
		{
			fseek(fp, 46, SEEK_SET);
			fread(&usecolor, sizeof(int), 1, fp);//カラーパレットの色の数取得
			if (usecolor == 0)
			{
				usecolor = 1 << colorbit;
			}
			fseek(fp, headersize + 14, SEEK_SET);//14はファイルヘッダのサイズ
			i = 0;

			while (i < usecolor)//カラーパレットコピー
			{
				fread(&bitColorData[i][E_COLOR::BLUE], sizeof(unsigned char), 1, fp);
				fread(&bitColorData[i][E_COLOR::GREEN], sizeof(unsigned char), 1, fp);
				fread(&bitColorData[i][E_COLOR::RED], sizeof(unsigned char), 1, fp);
				fseek(fp, sizeof(unsigned char), SEEK_CUR);
				i++;
			}
			i = 0;
			while (i < usecolor)//パレット16色分類
			{
				bitColorData[i][0] = Define16Color(bitColorData[i][E_COLOR::BLUE],
					bitColorData[i][E_COLOR::GREEN], bitColorData[i][E_COLOR::RED]);
				i++;
			}
		}
		if (colorbit == 24)
		{
			fseek(fp, header, SEEK_SET);//画像データまで飛ばす
		}

		int j = width;

		if (height > IMAGE_HEIGHT)
		{
			height = IMAGE_HEIGHT;
		}
		if (width > IMAGE_WIDTH)
		{
			width = IMAGE_WIDTH;
		}

		i = height - 1;
		imageinfo->halfSize.Y = height/2;//画像の縦を渡す
		imageinfo->halfSize.X = width/2;//画像の横を渡す


		//BMPの読み込み　BMPは上下逆なので下から詰める
		while (0 <= i)//逆縦ループ
		{
			w_count = 0;

			while (w_count < j)//横ループ
			{
				if (colorbit == 24)//各画像の色情報をコピー
				{
					fread(&img[i][w_count][E_COLOR::BLUE], sizeof(char), 1, fp);
					fread(&img[i][w_count][E_COLOR::GREEN], sizeof(char), 1, fp);
					fread(&img[i][w_count][E_COLOR::RED], sizeof(char), 1, fp);
				}
				else if (colorbit == 8)//各画像の色のある場所をコピー
				{
					fread(&img8bit[i][w_count], sizeof(char), 1, fp);//8ビット
				}
				w_count++;
			}

			w_count %= 4;
			w_count = 4 - w_count;
			//bmpのデータは4バイトの倍数じゃないとき0x00追加するのでそれを読み飛ばす作業
			while (w_count != 4)
			{
				fseek(fp, 1, SEEK_CUR);
				w_count++;
			}
			i--;
		}
		fclose(fp); //ファイルを閉じる


		i = 0;
		k = 0;
		int color = 0;
		while (i < height)//縦ループ
		{
			w_count = 0;

			//色の振り分け等
			while (w_count < width)//横ループ
			{
				if (colorbit == 24)//24bit画像の場合
				{
					color = Define16Color
					(img[i][w_count][E_COLOR::BLUE], img[i][w_count][E_COLOR::GREEN], img[i][w_count][E_COLOR::RED]);
				}
				else if (colorbit == 8)//8bit画像の場合
				{
					color = bitColorData[img8bit[i][w_count]][0];
				}
				color--;
				imageinfo->imageData[i][w_count].Attributes = color << 4;//背景なので4左シフトする
				imageinfo->imageData[i][w_count].Char.AsciiChar = ' ';
				w_count++;
			}

			i++;
		}
	}
}


void BitmapSet(COORD pos, tagIMAGE_INFO* imageinfo)
{

	CHAR_INFO* ScreenInfo = &screenInfo.ScreenInfo[0][0];

	//配列がアドレスで渡されているためここでは一つの長い行として考える

	//画像の縦横のどこかが範囲より外に完全に出ていないか判定
	if (false
		|| (pos.X + imageinfo->halfSize.X > 0 //左の完全判定
		&& pos.Y + imageinfo->halfSize.Y > 0 //上の判定
		&& pos.X - imageinfo->halfSize.X < SCREEN_WIDTH//右の判定
		&& pos.Y - imageinfo->halfSize.Y < SCREEN_HEIGHT//下の完全判定
		))
	{

		int w_count = 0;
		int h_count = 0;//今どの行が操作対象になっているか

		while (pos.Y-imageinfo->halfSize.Y + h_count < 0)//画像が上の線を超えたとき映らないように
		{
			h_count++;
		}

		ScreenInfo += (pos.Y - imageinfo->halfSize.Y + h_count) * SCREEN_WIDTH + (pos.X - imageinfo->halfSize.X);//描写開始位置に移動




		while (false
			|| imageinfo->halfSize.Y*2 > h_count //縦のカウント
			&& SCREEN_WIDTH * SCREEN_HEIGHT //下の一番マックス 
			> (pos.Y - imageinfo->halfSize.Y + h_count) * SCREEN_WIDTH//今の画像の表示開始しようとしている行の座標
			)
		{

			w_count = 0;
			int k = pos.X-imageinfo->halfSize.X;
			while (k < 0)//画像が左の線よりでかいときの処理
			{
				k++;
				w_count++;
				ScreenInfo++;
			}

			while (false
				|| imageinfo->halfSize.X*2 > w_count
				&& pos.X-imageinfo->halfSize.X + w_count < SCREEN_WIDTH)
			{
				ScreenInfo->Attributes = imageinfo->imageData[h_count][w_count].Attributes;
				ScreenInfo->Char.AsciiChar = imageinfo->imageData[h_count][w_count].Char.AsciiChar;

				ScreenInfo++;
				w_count++;
			}

			//右の線よりでかいときの処理
			while (false
				|| imageinfo->halfSize.X*2-w_count > 0
				)
			{
				ScreenInfo++;
				w_count++;
			}

			h_count++;
			ScreenInfo += (SCREEN_WIDTH - imageinfo->halfSize.X*2);//画像の次の行へ移動

		}
	}
}


int Define16Color(int Blue, int Green, int Red)
{
	//3次元の距離の求め方(x-x2)^2+(y1-y2)^2+(z1-z2)^2
	int Red_Distance;
	int Green_Distance;
	int Blue_Distance;
	int distance;
	int colorcount = 0;
	int color = 0;
	int colordistance = 1000000;
	while (16 > colorcount)
	{
		Blue_Distance = BasicColorData[colorcount][E_COLOR::BLUE] - Blue;
		Green_Distance = BasicColorData[colorcount][E_COLOR::GREEN] - Green;
		Red_Distance = BasicColorData[colorcount][E_COLOR::RED] - Red;

		distance = (Red_Distance * Red_Distance + Green_Distance * Green_Distance + Blue_Distance * Blue_Distance);
		//もし求めたい色と規定色の距離が前のやつよりも近いなら通る
		if (colordistance > distance)
		{
			color = colorcount + 1;
			colordistance = distance;
		}
		colorcount++;
	}
	return color;
}


void ResetScreen(void)//書き込んだスクリーン用CHAR_INFO渡す
{
	COORD coord = {SCREEN_WIDTH,SCREEN_HEIGHT};
	CHAR_INFO* ScreenInfo = &screenInfo.ScreenInfo[0][0];
	ZeroMemory(ScreenInfo, sizeof(CHAR_INFO) * coord.X * coord.Y);
}


void Draw()//SCREEN_SCREEN_INFOを渡す
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsoleOutput(handle, (CHAR_INFO*)screenInfo.ScreenInfo,
		screenInfo.size, screenInfo.StartPoint, &screenInfo.ScreenData);
}
