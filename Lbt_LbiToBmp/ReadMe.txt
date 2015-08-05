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

_splitpath(分解路径函数)


_splitpath( 
path_buffer,          
drive,                     //盘符
*dir,                       //目录
fname,                 //文件名
ext                       //扩展名
)
