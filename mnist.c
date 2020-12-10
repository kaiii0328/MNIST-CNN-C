#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "mnist.h"
//intel processors need to reverse header
int ReverseInt(int i)   
{  
	unsigned char *split = (unsigned char*)&i;
	return ((int)split[0])<<24 | split[1]<<16 | split[2]<<8 | split[3];
}

ImgArr read_aImg(const char* filename){
	FILE  *fp=NULL;
	fp=fopen(filename,"rb");
	//void *fp=0x800000000;
	if(fp==NULL)
		printf("open file failed in read_aImg.\n");
	
	int n_rows = 28;  
	int n_cols = 28; 
	int number_of_images =1; 
	
	//initialization
	int i,r,c,offset;
	// init image array
	ImgArr imgarr=(ImgArr)malloc(sizeof(struct MnistImgArr));
	imgarr->ImgNum=number_of_images;
	imgarr->ImgPtr=(MnistImg*)malloc(sizeof(struct MnistImg));

		imgarr->ImgPtr[0].r=n_rows;
		imgarr->ImgPtr[0].c=n_cols;
		imgarr->ImgPtr[0].ImgData=(float**)malloc(n_rows*sizeof(float*));
		for(r = 0; r < n_rows; ++r)      
		{
			imgarr->ImgPtr[0].ImgData[r]=(float*)malloc(n_cols*sizeof(float));
			for(c = 0; c < n_cols; ++c)
			{ 
				unsigned char temp = 0;  
				fread((char*) &temp, sizeof(temp),1,fp); //read a pixel data
				imgarr->ImgPtr[0].ImgData[r][c]=(float)temp/255.0;
				printf(" %3d ",temp);
				/*char *temp = (char*)malloc(sizeof(char));
				offset = r*n_rows + n_cols;
				memcpy(temp,fp+offset,sizeof(char));
				imgarr->ImgPtr[0].ImgData[r][c]=(float)(*temp)/255.0;
				printf(" %3.2f ",(*temp)/255);*/
			}  
			printf("\n");
		}   		
	

	fclose(fp);
	return imgarr;

}
ImgArr read_Img(const char* filename) // read images
{
	FILE  *fp=NULL;
	fp=fopen(filename,"rb");
	if(fp==NULL)
		printf("open file failed\n");
	assert(fp);

	int magic_number = 0;  
	int number_of_images = 0;  
	int n_rows = 0;  
	int n_cols = 0;  
	// read the number of sizeof(magic_number) digits to  &magic_number  
	fread((char*)&magic_number,sizeof(magic_number),1,fp); 
	magic_number = ReverseInt(magic_number);  
	//number_of_images for training or testing
	fread((char*)&number_of_images,sizeof(number_of_images),1,fp);  
	number_of_images = ReverseInt(number_of_images);    
	//read image height
	fread((char*)&n_rows,sizeof(n_rows),1,fp); 
	n_rows = ReverseInt(n_rows);                  
	//read image Width  
	fread((char*)&n_cols,sizeof(n_cols),1,fp); 
	n_cols = ReverseInt(n_cols);  
	
	int i,r,c;

	//initialization for image array
	ImgArr imgarr=(ImgArr)malloc(sizeof(struct MnistImgArr));
	imgarr->ImgNum=number_of_images;
	imgarr->ImgPtr=(MnistImg*)malloc(number_of_images*sizeof(struct MnistImg));

	for(i = 0; i < number_of_images; ++i)  
	{  
		imgarr->ImgPtr[i].r=n_rows;
		imgarr->ImgPtr[i].c=n_cols;
		imgarr->ImgPtr[i].ImgData=(float**)malloc(n_rows*sizeof(float*));		
			for(r = 0; r < n_rows; ++r)      
			{
				imgarr->ImgPtr[i].ImgData[r]=(float*)malloc(n_cols*sizeof(float));
				for(c = 0; c < n_cols; ++c)
				{ 
					unsigned char temp = 0;  
					fread((char*) &temp, sizeof(temp),1,fp); 
					imgarr->ImgPtr[i].ImgData[r][c]=(float)temp/255.0;
				}  
			}   
		
		
		
	}

	fclose(fp);
	return imgarr;
}

LabelArr read_Lable(const char* filename)//read picture label
{
	FILE  *fp=NULL;
	fp=fopen(filename,"rb");
	if(fp==NULL)
		printf("open file failed\n");
	assert(fp);

	int magic_number = 0;  
	int number_of_labels = 0; 
	int label_long = 10;

	//read sizeof(magic_number) number of char to  &magic_number  
	fread((char*)&magic_number,sizeof(magic_number),1,fp); 
	magic_number = ReverseInt(magic_number);  
	//read number_of_images  for training or testing
	fread((char*)&number_of_labels,sizeof(number_of_labels),1,fp);  
	number_of_labels = ReverseInt(number_of_labels);    

	int i,l;

	// label array initialization
	LabelArr labarr=(LabelArr)malloc(sizeof(struct MnistLabelArr));
	labarr->LabelNum=number_of_labels;
	labarr->LabelPtr=(MnistLabel*)malloc(number_of_labels*sizeof(struct MnistLabel));

	for(i = 0; i < number_of_labels; ++i)  
	{  
		labarr->LabelPtr[i].l=10;
		labarr->LabelPtr[i].LabelData=(float*)calloc(label_long,sizeof(float));
		unsigned char temp = 0;  
		fread((char*) &temp, sizeof(temp),1,fp); 
		labarr->LabelPtr[i].LabelData[(int)temp]=1.0;    
	}

	fclose(fp);
	return labarr;	
}

char* intTochar(int i)// number to string
{
	int itemp=i;
	int w=0;
	while(itemp>=10){
		itemp=itemp/10;
		w++;
	}
	char* ptr=(char*)malloc((w+2)*sizeof(char));
	ptr[w+1]='\0';
	int r; // ����
	while(i>=10){
		r=i%10;
		i=i/10;		
		ptr[w]=(char)(r+48);
		w--;
	}
	ptr[w]=(char)(i+48);
	return ptr;
}

char * combine_strings(char *a, char *b) // combine to strings
{
	char *ptr;
	int lena=strlen(a),lenb=strlen(b);
	int i,l=0;
	ptr = (char *)malloc((lena+lenb+1) * sizeof(char));
	for(i=0;i<lena;i++)
		ptr[l++]=a[i];
	for(i=0;i<lenb;i++)
		ptr[l++]=b[i];
	ptr[l]='\0';
	return(ptr);
}

void save_Img(ImgArr imgarr,char* filedir) // save images in a file
{
	int img_number=5;

	int i,r,c;
	for(i=0;i<img_number;i++){
		const char* filename=combine_strings(filedir,combine_strings(intTochar(i),".gray"));
		FILE  *fp=NULL;
		fp=fopen(filename,"wb");
		if(fp==NULL)
			printf("write file failed\n");
		/**unsigned char temp = 0;  
					fread((char*) &temp, sizeof(temp),1,fp); 
					imgarr->ImgPtr[i].ImgData[r][c]=(float)temp/255.0;*/
		for(r=0;r<imgarr->ImgPtr[i].r;r++)
			for (c=0;c<imgarr->ImgPtr[i].c;c++){
				unsigned char temp=0;
				temp =imgarr->ImgPtr[i].ImgData[r][c]*255;
				fwrite((char*)&temp,sizeof(temp),1,fp);
			}			
				
		
		fclose(fp);
	}	
}
