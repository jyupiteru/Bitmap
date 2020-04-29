
#include "Bitmap.h"

//�F���
int BasicColorData[16][3] = {//bgr�̏�
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


tagSCREEN_INFO screenInfo;

void BitmapRead(const char* name, tagIMAGE_INFO* imageinfo)
{
	int header;
	int headersize;
	unsigned int colorbit;	//��bit�̃r�b�g�}�b�v��
	int usecolor;			//�J���[�p���b�g�̐F��
	int width;
	int height;
	FILE* fp = fopen(name, "rb");
	if (fp != NULL)
	{
		int i, k;
		int w_count;
		//�t�@�C���w�b�_
		fseek(fp, 10, SEEK_SET);
		fread(&header, sizeof(int), 1, fp);			//10-13		�w�b�_�[����摜�f�[�^�܂ł̋���


		//����������w�b�_
		//fseek(fp, 14, SEEK_SET);					//14�s�ڂ܂ł̓ǂݔ�΂� TODO �ǂݔ�΂����Ȃ��Ă���������
		fread(&headersize, sizeof(int), 1, fp);		//14-17		���w�b�_�̃T�C�Y�������Ă���

		fread(&width, sizeof(int), 1, fp);			//18-21		�摜�̉����擾
		fread(&height, sizeof(int), 1, fp);			//22-25		�摜�̏c���擾


		//���w�b�_�̌`���ɂ���ē��e���Ⴄ�̂�
		switch (headersize)
		{
		case 12://OS2/2 V1�`��
			fseek(fp, 24, SEEK_SET);//16
			fread(&colorbit, sizeof(unsigned int), 1, fp);
			break;

		case 40://windows V3
		case 108://V4�w�b�_

		case 124://V5�w�b�_
			fseek(fp, 28, SEEK_SET);
			fread(&colorbit, sizeof(unsigned int), 1, fp);
			break;

		default:
			break;
		}

		if (colorbit == 8)
		{
			fseek(fp, 46, SEEK_SET);
			fread(&usecolor, sizeof(int), 1, fp);//�J���[�p���b�g�̐F�̐��擾
			if (usecolor == 0)
			{
				usecolor = 1 << colorbit;
			}
			fseek(fp, headersize + 14, SEEK_SET);//14�̓t�@�C���w�b�_�̃T�C�Y
			i = 0;

			while (i < usecolor)//�J���[�p���b�g�R�s�[
			{
				fread(&bitColorData[i][COLOR_BLUE], sizeof(unsigned char), 1, fp);
				fread(&bitColorData[i][COLOR_GREEN], sizeof(unsigned char), 1, fp);
				fread(&bitColorData[i][COLOR_RED], sizeof(unsigned char), 1, fp);
				fseek(fp, sizeof(unsigned char), SEEK_CUR);
				i++;
			}
			i = 0;
			while (i < usecolor)//�p���b�g16�F����
			{
				bitColorData[i][0] = Define16Color(bitColorData[i][COLOR_BLUE],
					bitColorData[i][COLOR_GREEN], bitColorData[i][COLOR_RED]);
				i++;
			}
		}
		if (colorbit == 24)
		{
			fseek(fp, header, SEEK_SET);//�摜�f�[�^�܂Ŕ�΂�
		}

		if (height > IMAGE_HEIGHT)
		{
			height = IMAGE_HEIGHT - 1;
		}
		if (width > IMAGE_WIDTH)
		{
			width = IMAGE_WIDTH - 1;
		}

		i = height - 1;
		imageinfo->halfSize.Y = height/2;//�摜�̏c��n��
		imageinfo->halfSize.X = width/2;//�摜�̉���n��


			//BMP�̓ǂݍ��݁@BMP�͏㉺�t�Ȃ̂ŉ�����l�߂�
		while (0 <= i)//�t�c���[�v
		{
			w_count = 0;

			while (w_count < width)//�����[�v
			{
				if (colorbit == 24)//�e�摜�̐F�����R�s�[
				{
					fread(&img[i][w_count][COLOR_BLUE], sizeof(char), 1, fp);
					fread(&img[i][w_count][COLOR_GREEN], sizeof(char), 1, fp);
					fread(&img[i][w_count][COLOR_RED], sizeof(char), 1, fp);
				}
				else if (colorbit == 8)//�e�摜�̐F�̂���ꏊ���R�s�[
				{
					fread(&img8bit[i][w_count], sizeof(char), 1, fp);//8�r�b�g
				}
				w_count++;
			}

			w_count %= 4;
			w_count = 4 - w_count;
			//bmp�̃f�[�^��4�o�C�g�̔{������Ȃ��Ƃ�0x00�ǉ�����̂ł����ǂݔ�΂����
			while (w_count != 4)
			{
				fseek(fp, 1, SEEK_CUR);
				w_count++;
			}
			i--;
		}
		fclose(fp); //�t�@�C�������


		i = 0;
		k = 0;
		int color = 0;
		while (i < height)//�c���[�v
		{
			w_count = 0;

			//�F�̐U�蕪����
			while (w_count < width)//�����[�v
			{
				if (colorbit == 24)//24bit�摜�̏ꍇ
				{
					color = Define16Color
					(img[i][w_count][COLOR_BLUE], img[i][w_count][COLOR_GREEN], img[i][w_count][COLOR_RED]);
				}
				else if (colorbit == 8)//8bit�摜�̏ꍇ
				{
					color = bitColorData[img8bit[i][w_count]][0];
				}
				color--;
				imageinfo->imageData[i][w_count].Attributes = color << 4;//�w�i�Ȃ̂�4���V�t�g����
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

	//�z�񂪃A�h���X�œn����Ă��邽�߂����ł͈�̒����s�Ƃ��čl����

	//�摜�̏c���̂ǂ������͈͂��O�Ɋ��S�ɏo�Ă��Ȃ�������
	if (false
		|| (pos.X + imageinfo->halfSize.X > 0 //���̊��S����
		&& pos.Y + imageinfo->halfSize.Y > 0 //��̔���
		&& pos.X - imageinfo->halfSize.X < IMAGE_WIDTH//�E�̔���
		&& pos.Y - imageinfo->halfSize.Y < IMAGE_HEIGHT//���̊��S����
		))
	{

		int w_count = 0;
		int h_count = 0;//���ǂ̍s������ΏۂɂȂ��Ă��邩



		while (pos.Y-imageinfo->halfSize.Y + h_count < 0)//�摜����̐��𒴂����Ƃ��f��Ȃ��悤��
		{
			h_count++;
		}

		ScreenInfo += (pos.Y - imageinfo->halfSize.Y + h_count) * IMAGE_WIDTH + (pos.X - imageinfo->halfSize.X);//�`�ʊJ�n�ʒu�Ɉړ�




		while (false
			|| imageinfo->halfSize.Y*2 > h_count //�c�̃J�E���g
			&& IMAGE_WIDTH * IMAGE_HEIGHT //���̈�ԃ}�b�N�X 
			> (pos.Y - imageinfo->halfSize.Y + h_count) * IMAGE_WIDTH//���̉摜�̕\���J�n���悤�Ƃ��Ă���s�̍��W
			)
		{

			w_count = 0;
			int k = pos.X-imageinfo->halfSize.X;
			while (k < 0)//�摜�����̐����ł����Ƃ��̏���
			{
				k++;
				w_count++;
				ScreenInfo++;
			}

			while (false
				|| imageinfo->halfSize.X*2 > w_count
				&& pos.X-imageinfo->halfSize.X + w_count < IMAGE_WIDTH)
			{
				/*COORD pos = {w_count,h_count};
				PrintToScreen("o",pos );*/
				ScreenInfo->Attributes = imageinfo->imageData[h_count][w_count].Attributes;
				ScreenInfo->Char.AsciiChar = imageinfo->imageData[h_count][w_count].Char.AsciiChar;

				ScreenInfo++;
				w_count++;
			}


			//�E�̐����ł����Ƃ��̏���
			while (false
				|| imageinfo->halfSize.X*2-w_count > 0
				//&& UsingImage->width + ImageDetails->position.X > IMAGE_WIDTH
				)
			{
				ScreenInfo++;
				w_count++;
			}

			h_count++;
			ScreenInfo += (IMAGE_WIDTH - imageinfo->halfSize.X*2);//�摜�̎��̍s�ֈړ�

		}
	}
}



/**
* @brief 16�F�̐F�ɐU�蕪���Ԃ�
* @param Blue  �F�̏��
* @param Green �ΐF�̏��
* @param Red   �ԐF�̏��
* @return color ��ԋ߂��F���Ԃ����
* @detail RGB�̐F��16�F�̈�ԋ߂��F�ɂ���@�������v�Z���ł��߂��F�����̐F�ɋ߂��F�ɂȂ�
*/
int Define16Color(int Blue, int Green, int Red)
{
	//3�����̋����̋��ߕ�(x-x2)^2+(y1-y2)^2+(z1-z2)^2

	int Red_Distance;
	int Green_Distance;
	int Blue_Distance;
	int distance;
	int colorcount = 0;
	int color = 0;
	int colordistance = 1000000;
	while (16 > colorcount)
	{
		Blue_Distance = BasicColorData[colorcount][COLOR_BLUE] - Blue;
		Green_Distance = BasicColorData[colorcount][COLOR_GREEN] - Green;
		Red_Distance = BasicColorData[colorcount][COLOR_RED] - Red;

		distance = (Red_Distance * Red_Distance + Green_Distance * Green_Distance + Blue_Distance * Blue_Distance);
		//�������߂����F�ƋK��F�̋������O�̂�����߂��Ȃ�ʂ�
		if (colordistance > distance)
		{
			color = colorcount + 1;
			colordistance = distance;
		}
		colorcount++;
	}
	return color;
}



/**
* @brief �X�N���[���pCHAR_INFO������������
* @return�@�Ȃ�
*/
void ResetScreen(void)//�������񂾃X�N���[���pCHAR_INFO�n��
{
	COORD coord = {IMAGE_WIDTH,IMAGE_HEIGHT};
	CHAR_INFO* ScreenInfo = &screenInfo.ScreenInfo[0][0];
	ZeroMemory(ScreenInfo, sizeof(CHAR_INFO) * coord.X * coord.Y);
}



/**
* @brief ���낢�돑�����񂾃X�N���[���pCHAR_INFO�𗠃X�N���[���ɓ]������
*
* @return�@�Ȃ�
*/
void Draw(void)//IMAGE_SCREEN_INFO��n��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsoleOutput(handle, (CHAR_INFO*)screenInfo.ScreenInfo,
		screenInfo.size, screenInfo.StartPoint, &screenInfo.ScreenData);
}
