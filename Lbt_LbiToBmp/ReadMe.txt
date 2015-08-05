========================================================================
    控制台应用程序：Lbt_LbiToBmp 项目概述
========================================================================


定义了LBT  LBI 文件的数组
typedef struct tagLBTIFILE {/*  */
	WORD       bfType;		 //标识符
	LONG       biWidth;		 //位图的宽度
	LONG       biHeight;		 //位图的高度
	WORD       biBitCount;		 //位图的位数
} LBTIFILE;


