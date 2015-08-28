// Lst_LsiToBmp.cpp : �������̨Ӧ�ó������ڵ㡣

#include "stdafx.h"
/***********************�����Ķ���***********************************/
unsigned char* pBmpBuf[] = { NULL };			 //����ͼ�����ݵ�ָ��
int SJDX[] = { NULL };							 //����ͼ�����ݵĴ�Сָ��
int SJDZ[] = { NULL };
int nmax=20;
char* Flname[] = { NULL };							 //����ͼ�����ݵ�ָ��
int MaxF=1;							             //������ļ�����
int bmpHeight;									 //ͼ��ĸ߶�
int biBitCount;									 //ͼ�����ͣ�����λ��
//int i;
RGBQUAD* pColorTable;							 //��ɫ��ָ��
LSTIFILE infoHead;						         //����LST LBI��������ȡλͼ��Ϣ���ڴ棬����ڱ���infoHead��
FILE* fp[99] = { NULL };									     //open_S�ر�����


/****************************************************************************
//�Ӱ��ļ��������   ƫ��   ��С  ����
*****************************************************************************/

int ReadFileFromPak(LONG fofs, int fSize, byte* _dst)
{
	if (fofs == NULL)
		return -1;

	fseek(&fp, fofs, SEEK_SET);
	fread(_dst, fSize, 1, fp);

	return 0;
}
/****************************************************************************
��ȡͼ���λͼ���ݡ���ȡ��߶ȡ���ɫ������λ�����������ȫ�ֱ�����
*****************************************************************************/
int readBmp(char* bmpName)
{
	errno_t err;									 //open_S�ر�����
	if ((err = fopen_s(&fp, bmpName, "rb")) != 0)		 //�Զ����ƶ��ķ�ʽ��ָ����ͼ���ļ� 
	{
		printf("���ļ�ʧ��nn");
//		return 0;
	}
	fread(&infoHead, sizeof(infoHead), 1, fp);     //��ȡλͼ����Ϣͷ���ڴ�  ��ַ����С���ֽڸ������ļ�
	cout << "00x=" << &infoHead << endl;
	//int a = 0;
	//for (size_t a = 0; a < 10; a++)
	//{
	//	SJDZ[a] = infoHead.biDiZhi[a];
	//	cout << SJDZ[a] << endl;
	//}

	int i = 0; int x = 0; int y = 1; int z = 0;
	while (  i < nmax )
	{
		cout << "01x=" << x << " y=" << y << " z=" << z << endl;
		SJDZ[x] = infoHead.biDiZhi[x];
			if (i == 99)
			{
				cout << "99x==========================" << x << "y=" << y << "z=" << z << endl;
				cout << "1��ȡ�ļ�   " << i << "���ļ���Сs��" << SJDX[x] << "=" << infoHead.biDiZhi[x] << "-" << infoHead.biDiZhi[z] << "   ���" << endl;
				
					if (SJDX[i] != 0)
					{
						 MaxF++;							             //������ļ�����

					}
			}
			else
			{
				cout << "02x=" << x << " y=" << y << " z=" << z << endl;
				if (infoHead.biDiZhi[y] != 0)
				{
					SJDX[x] = infoHead.biDiZhi[y] - infoHead.biDiZhi[z];
					cout << "2��ȡ�ļ�   " << i << "���ļ���Сs��" << SJDX[x] << "=" << infoHead.biDiZhi[y] << "-" << infoHead.biDiZhi[z] << "   ���" << endl;
					if (SJDX[i] != 0)
					{
						MaxF++;							             //������ļ�����

					}
				}
				else
				{
					SJDX[x] = infoHead.biDiZhi[z];
					cout << "3��ȡ�ļ�   " << i << "���ļ���Сs��" << SJDX[x] << "=" << infoHead.biDiZhi[z] << "   ���" << endl;
					if (SJDX[i] != 0)
					{
						MaxF++;							             //������ļ�����

					}
				}
				x++; z++; y++;
			}
			cout << "03x=" << x << " y=" << y << " z=" << z << endl;


			i++;
	}
	//return MaxF;

	return 0;
	/***************************************************************
	               ����λͼ���ݵ��ڴ棬���ݴ�С����100������
	***************************************************************/
	//for ( i = 0; i < 100; i++){
	//	if (SJDX[i] != 0)
	//	{
	//		pBmpBuf[i] = new unsigned char[SJDX[i]];     //�ռ��С=λͼ��width*height( ����width����Ϊ4�ı�����
	//		fread(pBmpBuf[i], SJDX[i], 1, fp);		   //��ȡλͼ���ݵ��ڴ�  ��ַ����С���ֽڸ������ļ�

	//		cout << "����ռ�����   " << i << "���ļ���С" << SJDX[i] << "   �ɹ�" << endl;
	//	}
	//}
	//cout << "03x=" << SJDX[0] << " y=" << SJDX[1] << " z=" << SJDX[2] << endl;
	////fclose(fp);										 //�رմ򿪵��ļ�
	//cout << "   ��ȡ�ɹ�" << endl;
	//return 1 ;											   //��ȡ�ļ��ɹ�

}
/***************************************************************************************************
��ָ������д���ļ���
***************************************************************************************************/
bool saveBmp(char* bmpName, unsigned char* imgBuf, int sjdx)
{			//      �ļ�����             λͼ���ݣ�    ���ݴ�С

	//���λͼ����ָ��Ϊ0����û����������
	if (!imgBuf)
	{
		printf("�ļ���ȡʧ��û����������nn");
		return 0;
	}
	//��ɫ���С�����ֽ�Ϊ��λ���Ҷ�ͼ��Ϊ1024;��ɫͼ��Ϊ0
	//int colorTablesize = 0;
	//if (biBitCount == 8)
	//	colorTablesize = 1024;//���洢ͼ������ÿ���ֽ���Ϊ4�ı���
	//int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;
	//�Զ�����д�ķ�ʽ���ļ�
	errno_t err;									 //open_S�ر�����
	FILE* fp;									     //open_S�ر�����
	err = fopen_s(&fp, bmpName, "wb"); 			     //���ļ�//���
	fwrite(imgBuf, sjdx, 1, fp);
	//fclose(fp);
	return 1;												//д���ļ��ɹ�
}
/*********************************************************************************************************************
λͼ�������
********************************************************************************************************************/

int ReadName(char* bmpName)
{
	//readBmp(bmpName);
	cout << "  99�ɹ�" << endl;
	////����ָ��BMP�ļ����ڴ�
	//readBmp(bmpName);
	//���ͼ�����Ϣ
	//ÿ���ֽ���
	cout << "NAME=" << bmpName << endl;

	/***************************************************************************
	��������
	***************************************************************************/
	int changdu;
	char lbt[] = ".lbt";
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	
	//char bfname[_MAX_FNAME];
	char ext[_MAX_EXT];
	char fnames[_MAX_FNAME];
	char numnames[] = "1";
	//changdu = strlen(bmpName);								//��ȡ�ļ����ĳ���
	_splitpath_s(bmpName, drive, dir, fname, ext);	        //�ֽ�·��
	//          ��·��  ������ �� Ŀ¼���ļ�������չ����
	cout << "�ļ���Ϊ" << fname << endl;
	//char bfname[] = {NULL};
	//bfname = fname;
	//char* bbfname = bfname;
	//cout << "NAME=" << bfname << bbfname << endl;
	cout << "MaxF" << MaxF << endl;

	int i=0;
	while (i < MaxF)
	{

		
		cout << "�ļ���Ϊ" << fname << endl;
			_itoa(i, numnames, 10);									//����Ϊ������ת��Ϊ�ַ��� int--->char*
			strcpy(fnames,fname);									//�����ַ���
			strcat_s(fnames, sizeof(fname), numnames);                        //�ϲ�2���ַ���

			cout << "�ļ�����" << bmpName << "��Ϊ" << fnames << "   �ɹ�" << endl;
			strcat_s(fnames, sizeof(fnames)+4, lbt);                        //�ϲ�2���ַ���
			cout << "�ļ�����" << bmpName << "��Ϊ" << fnames << "   �ɹ�" << endl;
			//bbfname = bfname;
			Flname[i] = fnames;
			//ͼƬ������ٴ洢
			cout << "NAME=" << fnames << endl;

		
			//      �ļ�����ͼ������
		
			
			cout << "�к�" << i << Flname[i] << endl;
			//changdu = strlen(bmpName);								//��ȡ�ļ����ĳ���
			//_splitpath_s(bmpName, drive, dir, fname, ext);	        //�ֽ�·��
			i++;

	}
	return 0;
	//delete[] pBmpBuf;
	//if (biBitCount == 8)
	//	delete[] pColorTable;
}

void pixHandle(char* bmpName)
{

	int ret;
	readBmp(bmpName);
	ReadName(bmpName);
	errno_t err;									 //open_S�ر�����
	if ((err = fopen_s(&fp, bmpName, "rb")) != 0)		 //�Զ����ƶ��ķ�ʽ��ָ����ͼ���ļ� 
	{
		printf("���ļ�ʧ��nn");
		//		return 0;
	}
	fread(&infoHead, sizeof(infoHead), 1, fp);     //��ȡλͼ����Ϣͷ���ڴ�  ��ַ����С���ֽڸ������ļ�
	cout << "00x=" << &infoHead << endl;
	int a = 0;
	while ( a < 10)
	{
		SJDZ[a] = infoHead.biDiZhi[a];
		cout << SJDZ[a] << endl;
		a++;
	}
	//SJDX[0] = infoHead.biDiZhi[1];
	//cout << "01   shuju==_" << SJDZ[a] << "_   SJDX_" << SJDX[a] << "_   SJ_" << pBmpBuf[a] << endl;
	int i = 0;
	while (i<MaxF)
	{
		cout << SJDZ[i] << endl; pBmpBuf[i]
ReadFileFromPak(SJDZ[i], SJDX[i],);

		cout << "n02   shuju==_" << infoHead.biDiZhi[1] << "_   SJDX_" << SJDX[i] << "_   SJ_" << pBmpBuf[i] << endl;

		//                 �ļ���ַ��   ���ݴ�Сͼ������  , 
		saveBmp(Flname[i], pBmpBuf[i], SJDX[i]);
		cout << "03  shuju==_" << Flname[i] << "_   SJDX_" << SJDX[i] << "_   SJ_" << pBmpBuf[i] << endl;

		//      �ļ�����ͼ������  ,    ���ݴ�С
	}
	

}



void main(int   argc, char*   argv[])
{
	
	pixHandle(argv[1]);
	fclose(fp);

}
