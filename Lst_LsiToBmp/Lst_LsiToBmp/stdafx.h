// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <iostream>
using namespace std;


// TODO:  在此处引用程序需要的其他头文件
/**********************************************************
*********************LBT_LBI文件信息头*********************
**********************************************************/
typedef struct tagLBTIFILE {/*  */
	WORD       bfType;							 //标识符
	LONG       biWidth;							 //位图的宽度
	LONG       biHeight;						 //位图的高度
	WORD       biBitCount;						 //位图的位数
} LBTIFILE;
/**********************************************************
*********************LST_LSI文件信息头*********************
**********************************************************/
typedef struct tagLSTIFILE {/*  */
	WORD       bfType;							 //标识符
	LONG       biCount;							 //文件的数量
	LONG       biDiZhi[100];						//文件的偏移量
	//WORD       biBitCount;						 //位图的位数
} LSTIFILE;