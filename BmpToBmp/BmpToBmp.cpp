// BmpToBmp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
/***********************变量的定义***********************************/
unsigned char* pBmpBuf;							 //读入图像数据的指针
char* name;										 //读入图像数据的指针
int bmpWidth;									 //图像的宽度
int bmpHeight;									 //图像的高度
int biBitCount;									 //图像类型，像素位数
RGBQUAD* pColorTable;							 //颜色表指针
BITMAPINFOHEADER infoHead;						 //定义位图信息头结构变量，读取位图信息头进内存，存放在变量infoHead中
char Fname[] = "L";								 //保存文件的名字
/****************************************************************************
读取图像的位图数据、宽度、高度、颜色表及像素位数，并存放在全局变量中
*****************************************************************************/
bool readBmp(char* bmpName)
{
	errno_t err;									 //open_S必备参数
	FILE* fp;									     //open_S必备参数

	if ((err = fopen_s(&fp, bmpName, "rb")) != 0)		 //以二进制读的方式打开指定的图像文件 
	{
		printf("打开文件失败nn");
		return 0;
	}


	fseek(fp, sizeof(BITMAPFILEHEADER), 0);				   //跳过位图的文件头             文件，大小，偏移
	fread(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);     //读取位图的信息头到内存  地址，大小，字节个数，文件
	bmpWidth = infoHead.biWidth;
	bmpHeight = infoHead.biHeight;
	biBitCount = infoHead.biBitCount;
	//定义变量，计算图像每行像素所占的字节数（必须为４的倍数）
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
	//灰度图像有颜色表，且颜色表为256
	if (biBitCount == 8)
	{
		//申请颜色表所需要的空间，读颜色表进内存
		pColorTable = new RGBQUAD[256];
		fread(pColorTable, sizeof(RGBQUAD), 256, fp);	   //读取位图的调色板到内存  地址，大小，字节个数，文件
	}
	//申请位图数据所需要的空间，读位图数据进内存
	pBmpBuf = new unsigned char[lineByte * bmpHeight];     //空间大小=位图的width*height( 其中width必须为4的倍数）
	fread(pBmpBuf, 1, lineByte * bmpHeight, fp);		   //读取位图数据到内存  地址，大小，字节个数，文件
	fclose(fp);											   //关闭打开的文件
	cout << "打开文件   " << bmpName << "   成功" << endl;
	return 1;											   //读取文件成功
}
/***************************************************************************************************
将指定数据写到文件中
***************************************************************************************************/
bool saveBmp(char* bmpName, unsigned char* imgBuf, int width, int height, int biBitCount, RGBQUAD* pColorTable)
{			//      文件名，             位图数据，    图像宽，   图像高，     图像位数，      色彩表

	//如果位图数据指针为0，则没有数据输入
	if (!imgBuf)
	{
		printf("文件读取失败没有数据输入nn");
		return 0;
	}
	//颜色表大小，以字节为单位：灰度图像为1024;彩色图像为0
	int colorTablesize = 0;
	if (biBitCount == 8)
		colorTablesize = 1024;//待存储图像数据每行字节数为4的倍数
	int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;
	//以二进制写的方式打开文件
	errno_t err;									 //open_S必备参数
	FILE* fp;									     //open_S必备参数

	err = fopen_s(&fp, bmpName, "wb"); 			    //打开文件//检测
	
	/**************************************************************************************************************************
	申请位图文件头结构变量，填写文件头信息并写入文件
	***************************************************************************************************************************/
	BITMAPFILEHEADER fileHead;								//定义位图信息头结构变量，读取位图信息头进内存，存放在变量fileHead中
	fileHead.bfType = 0x4D42;								// bmp 类型
	//bfSize是图像文件4个部分之和
	fileHead.bfSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+colorTablesize + lineByte * height;
	// 文件头BITMAPFILEHEADER+位图信息头BITMAPINFOHEADER+彩色表RGBQUAD+图像的实际数据BYTE
	fileHead.bfReserved1 = 0;//保留
	fileHead.bfReserved2 = 0;//保留
	//bfOffBits是图像文件前3个部分所需空间之和
	fileHead.bfOffBits = 54 + colorTablesize;
	//写文件头进文件
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);
	/****************************************************************
	申请位图信息头结构变量，填写信息头信息
	***********************************************/
	BITMAPINFOHEADER infoHead;								//定义文件信息头
	infoHead.biBitCount = biBitCount;						//图像位数
	infoHead.biClrImportant = 0;							//颜色索引的数目
	infoHead.biClrUsed = 0;									//位图实际使用的彩色表中的颜色索引数
	infoHead.biCompression = 0;								//图像数据压缩的类型
	infoHead.biHeight = height;								//图像的高度
	infoHead.biPlanes = 1;									//为目标设备说明位面数，其值设置为1
	infoHead.biSize = 40;									//BITMAPINFOHEADER结构所需要的字节数
	infoHead.biSizeImage = lineByte * height;				//图像的大小，以字节为单位。当用BI_RGB格式时，可设置为0
	infoHead.biWidth = width;								//图像的宽度
	infoHead.biXPelsPerMeter = 0;							//水平分辨率
	infoHead.biYPelsPerMeter = 0;							//垂直分辨率
	//写位图信息头进内存
	fwrite(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);
	//如果灰度图像，有颜色表，写入文件
	if (biBitCount == 8)
		fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);
	//写位图数据进文件
	fwrite(imgBuf, height * lineByte, 1, fp);
	fclose(fp);
	return 1;												//写入文件成功
}
/*********************************************************************************************************************
位图处理过程
********************************************************************************************************************/

void pixHandle(char* bmpName)
{

	////读入指定BMP文件进内存
	readBmp(bmpName);
	//输出图像的信息
	cout << "width=" << bmpWidth << "/nheight=" << bmpHeight << "/nBitCount=" << biBitCount << endl;
	//每行字节数
	cout << "NAME=" << bmpName << endl;
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
	//循环变量定义
	int m = 0, n = 0, pixCount = 0;
	//输出改变像素的文本文件
	//ofstream outfile("图像像素.txt", ios::in | ios::trunc);
	if (biBitCount == 8)   //灰度图像
	{
		//把图像的右上方的1/4变为黑色
		for (int i = bmpHeight / 2; i<bmpHeight; i++)
		{
			for (int j = lineByte / 2; j<lineByte; j++)
			{
				m = *(pBmpBuf + i*lineByte + j) = 0;
				pixCount++;
			}
		}
	}
	else if (biBitCount == 24)     //彩色图像
	{
		for (int i = bmpHeight / 2; i<bmpHeight; i++)
		{
			for (int j = bmpWidth / 2; j<bmpWidth; j++)
			{
				for (int k = 0; k<3; k++)
				{
					m = *(pBmpBuf + i*lineByte + j * 3 + k) = 0; //每像素RGB三个分量分别置为0
					pixCount++;
				}
				n++;
			}
		}
		cout << "总的像素个数为:" << n << endl;
	}
	//reName(bmpName);
	/***************************************************************************
	改名保存
	***************************************************************************/
	int changdu;
	int Fchangdu;
	int bmpchangdu;
	char kzm2[] = ".jpg";
	changdu = strlen(bmpName);								//获取文件名的长度
	Fchangdu = changdu - 4;
	bmpchangdu = changdu - 4;
	strncpy_s(Fname, changdu, bmpName, changdu - 4);					//截取文本   目标字符串,目标字符串中的字符数,源字符串,要复制的字符数，或者 _TRUNCATE.
	cout << "文件名从" << bmpName << "改为" << Fname << "   成功" << endl;
	strcat_s(Fname, sizeof(changdu)+3, kzm2);                                    //合并2个字符串
	cout << "文件名从" << bmpName << "改为" << Fname << "   成功" << endl;
	char* writePath = Fname;
	//图片处理后再存储
	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
	//      文件名，，图像宽，图像高，图像位数，色彩表
	delete[] pBmpBuf;
	if (biBitCount == 8)
		delete[] pColorTable;
}
void main(int   argc, char*   argv[])
{
	pixHandle(argv[1]);
}
