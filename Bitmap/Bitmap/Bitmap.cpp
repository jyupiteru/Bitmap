
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


unsigned char img[IMAGE_HEIGHT][IMAGE_WIDTH][3] = { 0 };
unsigned char img8bit[IMAGE_HEIGHT][IMAGE_WIDTH] = {0};
unsigned char bitColorData[256][3];

void BitmapRead(const char* name, tagIMAGE_INFO* imageinfo)
{
	int header;				
	int headersize;			
	unsigned int colorbit;	//何bitのbmpか
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
		fread(&header, sizeof(int), 1, fp);			//10-13		ヘッダーから画像データまでの距離


		//ここから情報ヘッダ
		//fseek(fp, 14, SEEK_SET);					//14行目までの読み飛ばし TODO 読み飛ばししなくてもいいかも
		fread(&headersize, sizeof(int), 1,fp);		//14-17		情報ヘッダのサイズが入っている

		fread(&width, sizeof(int), 1, fp);			//18-21		画像の横幅取得
		fread(&height, sizeof(int), 1, fp);			//22-25		画像の縦幅取得


		//情報ヘッダの形式によって内容が違うので
		switch (headersize)
		{
		case 12://OS2/2 V1形式
			fseek(fp, 24, SEEK_SET);//16
			fread(&colorbit, sizeof(unsigned int), 1, fp);
			break;

		case 40://windows V3
		case 108://V4ヘッダ

		case 124://V5ヘッダ
			fseek(fp, 28, SEEK_SET);
			fread(&colorbit, sizeof(unsigned int), 1, fp);
			break;

		default:
			break;
		}

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
				fread(&bitColorData[i][COLOR_BLUE], sizeof(unsigned char), 1, fp);
				fread(&bitColorData[i][COLOR_GREEN], sizeof(unsigned char), 1, fp);
				fread(&bitColorData[i][COLOR_RED], sizeof(unsigned char), 1, fp);
				fseek(fp, sizeof(unsigned char), SEEK_CUR);
				i++;
			}
			i = 0;
			while (i < usecolor)//パレット16色分類
			{
				bitColorData[i][0] = Define16Color(bitColorData[i][COLOR_BLUE],
					bitColorData[i][COLOR_GREEN], bitColorData[i][COLOR_RED]);
				i++;
			}
		}
		if (colorbit == 24)
		{
			fseek(fp, header, SEEK_SET);//画像データまで飛ばす
		}
	}
	else
	{
		MessageBox(nullptr, TEXT(name), "Error", MB_OK);//自動でどのファイルが読み込めてないのか通知
	}

}


void BitmapDraw(COORD pos, tagIMAGE_INFO* imageinfo)
{

}


int Define16Color(int blue, int green, int red)
{
	return 0;
}