// Lst_LsiToBmp.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
/***********************变量的定义***********************************/
unsigned char* pBmpBuf[] = { NULL };			 //读入图像数据的指针
int SJDX[] = { NULL };							 //读入图像数据的大小指针
int SJDZ[] = { NULL };
int nmax=20;
char* Flname[] = { NULL };							 //读入图像数据的指针
int MaxF=1;							             //最大子文件个数
int bmpHeight;									 //图像的高度
int biBitCount;									 //图像类型，像素位数
//int i;
RGBQUAD* pColorTable;							 //颜色表指针
LSTIFILE infoHead;						         //定义LST LBI变量，读取位图信息进内存，存放在变量infoHead中
FILE* fp[99] = { NULL };									     //open_S必备参数


/****************************************************************************
//从包文件里读数据   偏移   大小  数据
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
读取图像的位图数据、宽度、高度、颜色表及像素位数，并存放在全局变量中
*****************************************************************************/
int readBmp(char* bmpName)
{
	errno_t err;									 //open_S必备参数
	if ((err = fopen_s(&fp, bmpName, "rb")) != 0)		 //以二进制读的方式打开指定的图像文件 
	{
		printf("打开文件失败nn");
//		return 0;
	}
	fread(&infoHead, sizeof(infoHead), 1, fp);     //读取位图的信息头到内存  地址，大小，字节个数，文件
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
				cout << "1读取文件   " << i << "号文件大小s是" << SJDX[x] << "=" << infoHead.biDiZhi[x] << "-" << infoHead.biDiZhi[z] << "   完成" << endl;
				
					if (SJDX[i] != 0)
					{
						 MaxF++;							             //最大子文件个数

					}
			}
			else
			{
				cout << "02x=" << x << " y=" << y << " z=" << z << endl;
				if (infoHead.biDiZhi[y] != 0)
				{
					SJDX[x] = infoHead.biDiZhi[y] - infoHead.biDiZhi[z];
					cout << "2读取文件   " << i << "号文件大小s是" << SJDX[x] << "=" << infoHead.biDiZhi[y] << "-" << infoHead.biDiZhi[z] << "   完成" << endl;
					if (SJDX[i] != 0)
					{
						MaxF++;							             //最大子文件个数

					}
				}
				else
				{
					SJDX[x] = infoHead.biDiZhi[z];
					cout << "3读取文件   " << i << "号文件大小s是" << SJDX[x] << "=" << infoHead.biDiZhi[z] << "   完成" << endl;
					if (SJDX[i] != 0)
					{
						MaxF++;							             //最大子文件个数

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
	               分配位图数据到内存，数据大小，有100个数据
	***************************************************************/
	//for ( i = 0; i < 100; i++){
	//	if (SJDX[i] != 0)
	//	{
	//		pBmpBuf[i] = new unsigned char[SJDX[i]];     //空间大小=位图的width*height( 其中width必须为4的倍数）
	//		fread(pBmpBuf[i], SJDX[i], 1, fp);		   //读取位图数据到内存  地址，大小，字节个数，文件

	//		cout << "分配空间数据   " << i << "号文件大小" << SJDX[i] << "   成功" << endl;
	//	}
	//}
	//cout << "03x=" << SJDX[0] << " y=" << SJDX[1] << " z=" << SJDX[2] << endl;
	////fclose(fp);										 //关闭打开的文件
	//cout << "   读取成功" << endl;
	//return 1 ;											   //读取文件成功

}
/***************************************************************************************************
将指定数据写到文件中
***************************************************************************************************/
bool saveBmp(char* bmpName, unsigned char* imgBuf, int sjdx)
{			//      文件名，             位图数据，    数据大小

	//如果位图数据指针为0，则没有数据输入
	if (!imgBuf)
	{
		printf("文件读取失败没有数据输入nn");
		return 0;
	}
	//颜色表大小，以字节为单位：灰度图像为1024;彩色图像为0
	//int colorTablesize = 0;
	//if (biBitCount == 8)
	//	colorTablesize = 1024;//待存储图像数据每行字节数为4的倍数
	//int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;
	//以二进制写的方式打开文件
	errno_t err;									 //open_S必备参数
	FILE* fp;									     //open_S必备参数
	err = fopen_s(&fp, bmpName, "wb"); 			     //打开文件//检测
	fwrite(imgBuf, sjdx, 1, fp);
	//fclose(fp);
	return 1;												//写入文件成功
}
/*********************************************************************************************************************
位图处理过程
********************************************************************************************************************/

int ReadName(char* bmpName)
{
	//readBmp(bmpName);
	cout << "  99成功" << endl;
	////读入指定BMP文件进内存
	//readBmp(bmpName);
	//输出图像的信息
	//每行字节数
	cout << "NAME=" << bmpName << endl;

	/***************************************************************************
	改名保存
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
	//changdu = strlen(bmpName);								//获取文件名的长度
	_splitpath_s(bmpName, drive, dir, fname, ext);	        //分解路径
	//          （路径  ，磁盘 ， 目录，文件名，扩展名）
	cout << "文件名为" << fname << endl;
	//char bfname[] = {NULL};
	//bfname = fname;
	//char* bbfname = bfname;
	//cout << "NAME=" << bfname << bbfname << endl;
	cout << "MaxF" << MaxF << endl;

	int i=0;
	while (i < MaxF)
	{

		
		cout << "文件名为" << fname << endl;
			_itoa(i, numnames, 10);									//作用为将整形转换为字符串 int--->char*
			strcpy(fnames,fname);									//复制字符串
			strcat_s(fnames, sizeof(fname), numnames);                        //合并2个字符串

			cout << "文件名从" << bmpName << "改为" << fnames << "   成功" << endl;
			strcat_s(fnames, sizeof(fnames)+4, lbt);                        //合并2个字符串
			cout << "文件名从" << bmpName << "改为" << fnames << "   成功" << endl;
			//bbfname = bfname;
			Flname[i] = fnames;
			//图片处理后再存储
			cout << "NAME=" << fnames << endl;

		
			//      文件名，图像数据
		
			
			cout << "行号" << i << Flname[i] << endl;
			//changdu = strlen(bmpName);								//获取文件名的长度
			//_splitpath_s(bmpName, drive, dir, fname, ext);	        //分解路径
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
	errno_t err;									 //open_S必备参数
	if ((err = fopen_s(&fp, bmpName, "rb")) != 0)		 //以二进制读的方式打开指定的图像文件 
	{
		printf("打开文件失败nn");
		//		return 0;
	}
	fread(&infoHead, sizeof(infoHead), 1, fp);     //读取位图的信息头到内存  地址，大小，字节个数，文件
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

		//                 文件地址，   数据大小图像数据  , 
		saveBmp(Flname[i], pBmpBuf[i], SJDX[i]);
		cout << "03  shuju==_" << Flname[i] << "_   SJDX_" << SJDX[i] << "_   SJ_" << pBmpBuf[i] << endl;

		//      文件名，图像数据  ,    数据大小
	}
	

}



void main(int   argc, char*   argv[])
{
	
	pixHandle(argv[1]);
	fclose(fp);

}
