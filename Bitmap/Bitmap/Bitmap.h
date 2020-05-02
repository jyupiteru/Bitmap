
#define _CRT_SECURE_NO_WARNINGS

#include<Windows.h>
#include<stdio.h>

#pragma once

//!@brief	�F�U�蕪�����Ɏg�p����}�N��
enum  E_COLOR{
BLUE = 0,	//!<��
GREEN,		//!<��
RED			//!<��
};

//!@brief		�摜�̏c�̍ő�T�C�Y
//!@details		�����Ŏw�肷�邱��
#define IMAGE_HEIGHT 50

//!@brief		�摜�̉��̍ő�T�C�Y
//!@details		�����Ŏw�肷�邱��
#define IMAGE_WIDTH  50


//!@brief		�`�ʐ�̏c�̍ő�T�C�Y
#define SCREEN_HEIGHT	100

//!@brief		�`�ʐ�̉��̍ő�T�C�Y
#define SCREEN_WIDTH	100



//!@brief	�摜�̏������\����
typedef struct{
	COORD halfSize;										//!<�摜�̔����̑傫��
	CHAR_INFO  imageData[IMAGE_HEIGHT][IMAGE_WIDTH];	//!<�摜���i�F�j��ێ�
}tagIMAGE_INFO;


//!@brief	�`�ʐ�̏������\����
//!@details	�ȉ��p���b�g�ƌĂ�
typedef struct
{
	CHAR_INFO ScreenInfo[SCREEN_HEIGHT][SCREEN_WIDTH];			//!<�X�N���[���ɓ]������CHAR_INFO �����Ɏg�������摜���R�s�[
	COORD size = { SCREEN_WIDTH , SCREEN_HEIGHT };				//!<�������މ摜�̃T�C�Y
	COORD StartPoint = { 0,0 };									//!<3D�ɂ����郏�[���h���W�̂悤�Ȃ���
	SMALL_RECT ScreenData = { 0,0,SCREEN_WIDTH - 1,SCREEN_HEIGHT };//!<�������މ摜�̏㉺�A���E������
}tagSCREEN_INFO;


//!@brief			BMP�摜�̓ǂݍ���
//!@param name		�ǂݍ��݂����摜���A�h���X���݂œ����
//!@param imageifo	�摜�̏�������\���̂̃A�h���X������
void BitmapRead(const char* name, tagIMAGE_INFO* imageinfo);


//!@brief			BMP�摜���p���b�g�ɃZ�b�g����֐�
//!@param pos		�摜��`�ʂ��钆�S�ʒu���w��
//!@param imageinfo �`�ʂ������摜��������
void BitmapSet(COORD pos, tagIMAGE_INFO* imageinfo);


//!@brief		�F�̕��ފ֐�
//!@param blue	�̏�������
//!@param green	�΂̏�������
//!@param red	�Ԃ̏�������
//!@details		�����ōł��߂�16�F�ɕ��ނ��Ă���
int Define16Color(int blue,int green,int red);


//!@brief		�p���b�g������������֐�
void ResetScreen(void);


//!@brief		�p���b�g���R���\�[���ɓ]������֐�
void Draw();