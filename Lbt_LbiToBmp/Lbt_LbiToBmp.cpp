// Lbt_LbiToBmp.cpp : �������̨Ӧ�ó������ڵ㡣
//
// BmpToBmp.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
/***********************�����Ķ���***********************************/
unsigned char* pBmpBuf;							 //����ͼ�����ݵ�ָ��
char* name;										 //����ͼ�����ݵ�ָ��
int bmpWidth;									 //ͼ��Ŀ��
int bmpHeight;									 //ͼ��ĸ߶�
int biBitCount;									 //ͼ�����ͣ�����λ��
RGBQUAD* pColorTable;							 //��ɫ��ָ��
//BITMAPINFOHEADER infoHead;						 //����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���infoHead��
LBTIFILE infoHead;						     //����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���infoHead��
char Fname[] = "L";								 //�����ļ�������
/****************************************************************************
��ȡͼ���λͼ���ݡ���ȡ��߶ȡ���ɫ������λ�����������ȫ�ֱ�����
*****************************************************************************/
bool readBmp(char* bmpName)
{
	errno_t err;									 //open_S�ر�����
	FILE* fp;									     //open_S�ر�����

	if ((err = fopen_s(&fp, bmpName, "rb")) != 0)		 //�Զ����ƶ��ķ�ʽ��ָ����ͼ���ļ� 
	{
		printf("���ļ�ʧ��nn");
		return 0;
	}


	//fseek(fp, sizeof(BITMAPFILEHEADER), 0);				   //����λͼ���ļ�ͷ             �ļ�����С��ƫ��
	fread(&infoHead, sizeof(LBTIFILE), 1, fp);     //��ȡλͼ����Ϣͷ���ڴ�  ��ַ����С���ֽڸ������ļ�
	bmpWidth = infoHead.biWidth;
	bmpHeight = infoHead.biHeight;
	biBitCount = infoHead.biBitCount;
	//�������������ͼ��ÿ��������ռ���ֽ���������Ϊ���ı�����
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
	//�Ҷ�ͼ������ɫ������ɫ��Ϊ256
	if (biBitCount == 8)
	{
		//������ɫ������Ҫ�Ŀռ䣬����ɫ����ڴ�
		pColorTable = new RGBQUAD[256];
		fread(pColorTable, sizeof(RGBQUAD), 256, fp);	   //��ȡλͼ�ĵ�ɫ�嵽�ڴ�  ��ַ����С���ֽڸ������ļ�
	}
	//����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
	pBmpBuf = new unsigned char[lineByte * bmpHeight];     //�ռ��С=λͼ��width*height( ����width����Ϊ4�ı�����
	fread(pBmpBuf, 1, lineByte * bmpHeight, fp);		   //��ȡλͼ���ݵ��ڴ�  ��ַ����С���ֽڸ������ļ�
	fclose(fp);											   //�رմ򿪵��ļ�
	cout << "���ļ�   " << bmpName << "   �ɹ�" << endl;
	return 1;											   //��ȡ�ļ��ɹ�
}
/***************************************************************************************************
��ָ������д���ļ���
***************************************************************************************************/
bool saveBmp(char* bmpName, unsigned char* imgBuf, int width, int height, int biBitCount, RGBQUAD* pColorTable)
{			//      �ļ�����             λͼ���ݣ�    ͼ���   ͼ��ߣ�     ͼ��λ����      ɫ�ʱ�

	//���λͼ����ָ��Ϊ0����û����������
	if (!imgBuf)
	{
		printf("�ļ���ȡʧ��û����������nn");
		return 0;
	}
	//��ɫ���С�����ֽ�Ϊ��λ���Ҷ�ͼ��Ϊ1024;��ɫͼ��Ϊ0
	int colorTablesize = 0;
	if (biBitCount == 8)
		colorTablesize = 1024;//���洢ͼ������ÿ���ֽ���Ϊ4�ı���
	int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;
	//�Զ�����д�ķ�ʽ���ļ�
	errno_t err;									 //open_S�ر�����
	FILE* fp;									     //open_S�ر�����

	err = fopen_s(&fp, bmpName, "wb"); 			    //���ļ�//���

	/**************************************************************************************************************************
	����λͼ�ļ�ͷ�ṹ��������д�ļ�ͷ��Ϣ��д���ļ�
	***************************************************************************************************************************/
	BITMAPFILEHEADER fileHead;								//����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���fileHead��
	fileHead.bfType = 0x4D42;								// bmp ����
	//bfSize��ͼ���ļ�4������֮��
	fileHead.bfSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+colorTablesize + lineByte * height;
	// �ļ�ͷBITMAPFILEHEADER+λͼ��ϢͷBITMAPINFOHEADER+��ɫ��RGBQUAD+ͼ���ʵ������BYTE
	fileHead.bfReserved1 = 0;//����
	fileHead.bfReserved2 = 0;//����
	//bfOffBits��ͼ���ļ�ǰ3����������ռ�֮��
	fileHead.bfOffBits = 54 + colorTablesize;
	//д�ļ�ͷ���ļ�
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);
	/****************************************************************
	����λͼ��Ϣͷ�ṹ��������д��Ϣͷ��Ϣ
	***********************************************/
	BITMAPINFOHEADER infoHead;								//�����ļ���Ϣͷ
	infoHead.biBitCount = biBitCount;						//ͼ��λ��
	infoHead.biClrImportant = 0;							//��ɫ��������Ŀ
	infoHead.biClrUsed = 0;									//λͼʵ��ʹ�õĲ�ɫ���е���ɫ������
	infoHead.biCompression = 0;								//ͼ������ѹ��������
	infoHead.biHeight = height;								//ͼ��ĸ߶�
	infoHead.biPlanes = 1;									//ΪĿ���豸˵��λ��������ֵ����Ϊ1
	infoHead.biSize = 40;									//BITMAPINFOHEADER�ṹ����Ҫ���ֽ���
	infoHead.biSizeImage = lineByte * height;				//ͼ��Ĵ�С�����ֽ�Ϊ��λ������BI_RGB��ʽʱ��������Ϊ0
	infoHead.biWidth = width;								//ͼ��Ŀ��
	infoHead.biXPelsPerMeter = 0;							//ˮƽ�ֱ���
	infoHead.biYPelsPerMeter = 0;							//��ֱ�ֱ���
	//дλͼ��Ϣͷ���ڴ�
	fwrite(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);
	//����Ҷ�ͼ������ɫ��д���ļ�
	if (biBitCount == 8)
		fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);
	//дλͼ���ݽ��ļ�
	fwrite(imgBuf, height * lineByte, 1, fp);
	fclose(fp);
	return 1;												//д���ļ��ɹ�
}
/*********************************************************************************************************************
λͼ�������
********************************************************************************************************************/

void pixHandle(char* bmpName)
{

	////����ָ��BMP�ļ����ڴ�
	readBmp(bmpName);
	//���ͼ�����Ϣ
	cout << "width=" << bmpWidth << "/nheight=" << bmpHeight << "/nBitCount=" << biBitCount << endl;
	//ÿ���ֽ���
	cout << "NAME=" << bmpName << endl;
	
	/***************************************************************************
	��������
	***************************************************************************/
	int changdu;
	int Fchangdu;
	int bmpchangdu;
	char kzm2[] = ".bmp";
	changdu = strlen(bmpName);								//��ȡ�ļ����ĳ���
	Fchangdu = changdu - 4;
	bmpchangdu = changdu - 4;
	strncpy_s(Fname, changdu, bmpName, changdu - 4);					//��ȡ�ı�   Ŀ���ַ���,Ŀ���ַ����е��ַ���,Դ�ַ���,Ҫ���Ƶ��ַ��������� _TRUNCATE.
	cout << "�ļ�����" << bmpName << "��Ϊ" << Fname << "   �ɹ�" << endl;
	strcat_s(Fname, sizeof(changdu)+3, kzm2);                                    //�ϲ�2���ַ���
	cout << "�ļ�����" << bmpName << "��Ϊ" << Fname << "   �ɹ�" << endl;
	char* writePath = Fname;
	//ͼƬ������ٴ洢
	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
	//      �ļ�����ͼ�����ݣ�ͼ���ͼ��ߣ�ͼ��λ����ɫ�ʱ�
	delete[] pBmpBuf;
	if (biBitCount == 8)
		delete[] pColorTable;
}
void main(int   argc, char*   argv[])
{
	pixHandle(argv[1]);
}
