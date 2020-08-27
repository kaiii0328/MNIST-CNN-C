#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
//#include <random.h>
#include <time.h>
#include "cnn.h"
#include "mnist.h"


int main()
{
	//reading labels and images for training and tesing.
	/*LabelArr trainLabel = read_Lable("train-labels-idx1-ubyte");
	ImgArr trainImg=read_Img("train-images-idx3-ubyte");	
	LabelArr testLabel=read_Lable("t10k-labels-idx1-ubyte");
	ImgArr testImg=read_Img("t10k-images-idx3-ubyte");*/
	//printf("Finish reading labels and images.\n");
	//nSize inputSize={testImg->ImgPtr[0].c,testImg->ImgPtr[0].r};
	nSize inputSize = {28,28};
	//int outSize=testLabel->LabelPtr[0].l;
	int outSize = 10;
	//save_Img(trainImg,"");
	
	printf("Initialize network.\n\n");
	CNN* cnn=(CNN*)malloc(sizeof(struct cnn_network));
	cnnsetup(cnn,inputSize,outSize);	//initialize cnn network

	/*CNNOpts opts;
	opts.numepochs=1;
	opts.alpha=1.0;
	int trainNum=55000;			//select how many images to train
	printf("Start training.\n");
	cnntrain(cnn,trainImg,trainLabel,opts,trainNum);
	printf("train finished!!\n");*/
	savecnn(cnn,"mnist.cnn");	//save weight data in a file
	
	// import CNN model
	importcnn(cnn,"mnist.cnn");
	/*testing phase, selsect 10000 images to test
	int testNum=10000;
	float incorrectRatio=0.0;
	printf("Begin testing.\n");
	incorrectRatio=cnntest(cnn,testImg,testLabel,testNum);
	printf("Prediction accuracy: %f\%\n",(1-incorrectRatio)*100);
	printf("test finished!!\n");*/
	
	//prediction
	ImgArr predImg=read_aImg("0.gray");	
	predict(cnn,predImg,1);
	return 0;
}
