// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
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


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
/**********************************************************
*********************LBT_LBI�ļ���Ϣͷ*********************
**********************************************************/
typedef struct tagLBTIFILE {/*  */
	WORD       bfType;							 //��ʶ��
	LONG       biWidth;							 //λͼ�Ŀ��
	LONG       biHeight;						 //λͼ�ĸ߶�
	WORD       biBitCount;						 //λͼ��λ��
} LBTIFILE;
/**********************************************************
*********************LST_LSI�ļ���Ϣͷ*********************
**********************************************************/
typedef struct tagLSTIFILE {/*  */
	WORD       bfType;							 //��ʶ��
	LONG       biCount;							 //�ļ�������
	LONG       biDiZhi[100];						//�ļ���ƫ����
	//WORD       biBitCount;						 //λͼ��λ��
} LSTIFILE;