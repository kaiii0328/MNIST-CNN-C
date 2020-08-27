#ifndef __CNN_
#define __CNN_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
//#include <random.h>
#include <time.h>
#include "mat.h"
#include "mnist.h"

#define AvePool 0
#define MaxPool 1
#define MinPool 2

// ������
typedef struct convolutional_layer{
	int inputWidth;   //width of input images
	int inputHeight;  //height of input images
	int mapSize;      //size of kernel, a mapSize*mapsize square

	int inChannels;   //number of input images
	int outChannels;  //number of output images
	
	// a four-dimentional array to store weight data.
	// the array size is inChannels*outChannels*mapSize*mapSize
	// four-dimentional array depicts the full-connect layer 
	
	float**** mapData;     //store feature data
	float**** dmapData;    //store local gradients for feature map

	float* basicData;   //bias data
	bool isFullConnect; //whether it is full-connect layer
	//bool* connectModel; 

	//the below three variables have same dimentions with output
	float*** v; // input value for activation function
	float*** y; // output of activation value

	// local gradient for output value
	float*** d; 
}CovLayer;

//  pooling layer
typedef struct pooling_layer{
	int inputWidth;   //image width
	int inputHeight;  //image height
	int mapSize;      //kernel size

	int inChannels;   //number of input images
	int outChannels;  //number of output data

	int poolType;     //Pooling method (average pooling / maxpooling)
	float* basicData;   //bias (typo)

	float*** y; // input value for activation function
	float*** d; // local gradient
}PoolLayer;

// full connect layer
typedef struct nn_layer{
	int inputNum;   //input number
	int outputNum;  //output number 

	float** wData; //weight data, inputNum*outputNum
	float* basicData;   //bias

	
	float* v; //input value for activation function
	float* y; // output of activation value
	float* d; // local gradient

	bool isFullConnect; 
}OutLayer;

// nerwork architecture
typedef struct cnn_network{
	int layerNum;
	CovLayer* C1;
	PoolLayer* S2;
	CovLayer* C3;
	PoolLayer* S4;
	OutLayer* O5;

	float* e; //training loss
	float* L; // instaneous error energy
}CNN;

typedef struct train_opts{
	int numepochs; //epochs
	float alpha; // learning rate
}CNNOpts;

void cnnsetup(CNN* cnn,nSize inputSize,int outputSize);// network initialization

void cnntrain(CNN* cnn,	ImgArr inputData,LabelArr outputData,CNNOpts opts,int trainNum); //training 

float cnntest(CNN* cnn, ImgArr inputData,LabelArr outputData,int testNum);//tesing

void savecnn(CNN* cnn, const char* filename);//save cnn data

void importcnn(CNN* cnn, const char* filename); //read cnn data

//initializae covolutoin layer
CovLayer* initCovLayer(int inputWidth,int inputHeight,int mapSize,int inChannels,int outChannels);
//void CovLayerConnect(CovLayer* covL,bool* connectModel);
// initializae pooling layer
PoolLayer* initPoolLayer(int inputWidth,int inputHeigh,int mapSize,int inChannels,int outChannels,int poolType);
//void PoolLayerConnect(PoolLayer* poolL,bool* connectModel);
//initializae full-connect layer
OutLayer* initOutLayer(int inputNum,int outputNum);

//activation function
float activation_Sigma(float input,float bas); // sigma

void cnnff(CNN* cnn,float** inputData); // feedfoward
void cnnbp(CNN* cnn,float* outputData); // backpropagation 
void cnnapplygrads(CNN* cnn,CNNOpts opts,float** inputData);
void predict(CNN* cnn, ImgArr inputData,int testNum);
void cnnclear(CNN* cnn); //clear vyd

/*
	Pooling Function
	input: input data
	inputNum: number of images
	mapSize kernel size
*/
void avgPooling(float** output,nSize outputSize,float** input,nSize inputSize,int mapSize); 

/* 
	full-connect layer feedforward function
	nnSize:size of network
*/
void nnff(float* output,float* input,float** wdata,float* bas,nSize nnSize);

void savecnndata(CNN* cnn,const char* filename,float** inputdata); // save data during training process

#endif
