#ifndef __MINST_
#define __MINST_
/*
用来读取 MNIST 数据集的函数
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
//#include <random>
#include <time.h>

typedef struct MnistImg{
	int c;           // 宽 column
	int r;           // 高 row
	float** ImgData; // 图像数据二维动态数组
}MnistImg;

typedef struct MnistImgArr{
	int ImgNum;        // 图像个数
	MnistImg* ImgPtr;  // 图像数组的指针
}*ImgArr;              // 存储图像数据的数组

typedef struct MnistLabel{
	int l;            // 标记的长
	float* LabelData; // 标记的数据
}MnistLabel;

typedef struct MnistLabelArr *LabelArr;
struct MnistLabelArr{
	int LabelNum;
	MnistLabel* LabelPtr;
};              // 存储图像标记的数组

LabelArr read_Lable(const char* filename); //读入图像标记

ImgArr read_Img(const char* filename); // 读入图像
ImgArr read_aImg(const char* filename); //读入待预测的图像

void save_Img(ImgArr imgarr,char* filedir); //保存图片

#endif
