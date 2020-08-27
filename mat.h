// functions of matrix operations
#ifndef __MAT_
#define __MAT_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
//#include <random>
#include <time.h>

#define full 0
#define same 1
#define valid 2

typedef struct Mat2DSize{
	int c; //width
	int r; // height
}nSize;

float** rotate180(float** mat, nSize matSize);// rorate matrix 180 degree

void addmat(float** res, float** mat1, nSize matSize1, float** mat2, nSize matSize2);// matrix addition

float** correlation(float** map,nSize mapSize,float** inputData,nSize inSize,int type);// correlation

float** cov(float** map,nSize mapSize,float** inputData,nSize inSize,int type); // covolution operation

// matrix upsampling
float** UpSample(float** mat,nSize matSize,int upc,int upr);

// enlarge two-dimensional matrix edge 
float** matEdgeExpand(float** mat,nSize matSize,int addc,int addr);

// shrink two-dimentional matrix edge
float** matEdgeShrink(float** mat,nSize matSize,int shrinkc,int shrinkr);

void savemat(float** mat,nSize matSize,const char* filename);

void multifactor(float** res, float** mat, nSize matSize, float factor);// matrix * factor

float summat(float** mat,nSize matSize);// sum of all the elements in matrix

char * combine_strings(char *a, char *b);

char* intTochar(int i);

#endif
