#include"cv.h"
#include"highgui.h"
#include<string>
#include<iostream>
using namespace std;
IplImage *pImgCharOne=NULL;  
IplImage *pImgCharTwo=NULL;  
IplImage *pImgCharThree=NULL;  
IplImage *pImgCharFour=NULL;  
IplImage *pImgCharFive=NULL;  
IplImage *pImgCharSix=NULL;  
IplImage *pImgCharSeven=NULL; 
IplImage *pImgCharEight=NULL; 

#define CHARACTER 15
#define TEMPLETENUM  44

const int Num_Templete[TEMPLETENUM][CHARACTER]=
{
	{16,19,10,12,10,10,15,18,110,3,2,2,3,3,3},     //0
	{9,11,10,10,10,10,9,10,79,2,2,2,0,2,12},       //1
	{18,19,3,18,10,10,23,22,123,4,2,2,7,6,8},      //2
	{19,21,11,14,4,20,18,22,129,2,2,4,6,6,7},      //3
	{2,18,11,22,20,21,11,18,123,2,4,2,6,7,5},      //4
	{23,19,20,12,9,20,18,22,143,2,4,4,6,6,6},      //5
	{6,13,17,8,15,20,18,20,117,2,2,4,5,7,6},       //6
	{21,21,0,20,8,12,9,11,102,2,2,2,2,8,15},       //7
	{17,18,18,19,14,20,17,20,143,4,2,4,6,6,6},     //8
	{16,18,15,21,7,19,13,7,116,3,2,2,6,6,5},       //9
	{10,10,16,16,20,20,18,19,129,2,4,2,8,3,6},     //A
	{24,20,20,19,22,22,24,20,171,4,8,4,6,6,6},     //B
	{18,19,20,4,20,8,17,21,127,3,2,4,4,4,4},       //C
	{23,19,11,20,12,20,22,21,148,3,3,3,4,4,4},     //D
	{23,19,21,9,22,8,23,23,148,2,2,2,6,6,6},       //E
	{25,17,20,9,22,8,19,0,120,2,2,2,4,4,4},        //F
	{17,18,22,14,12,24,18,21,146,4,7,4,4,6,6},     //G
	{14,20,18,22,17,22,16,20,149,4,1,4,2,2,2},     //H
	{0,17,0,20,3,20,18,22,100,2,2,4,2,2,2},        //J
	{19,20,26,10,20,20,20,22,157,4,4,4,3,5,11},    //K
	{20,0,20,0,20,0,25,20,105,2,2,2,2,2,2},        //L
	{20,10,27,17,20,10,22,14,140,1,3,3,4,1,5},     //M
	{21,12,25,17,26,12,18,18,149,3,5,3,5,5,6},     //N
	{23,19,18,20,21,8,22,0,131,3,3,2,4,4,4},       //P
	{18,19,20,10,26,15,18,21,147,3,3,4,5,7,5},     //Q
	{26,19,21,18,21,17,20,21,163,4,3,4,4,6,5},     //R
	{18,18,18,10,8,17,17,22,128,4,3,4,6,6,6},      //S
	{22,18,10,10,10,10,10,10,100,2,2,2,33,2,2},    //T
	{18,12,20,10,20,10,19,21,130,3,3,3,2,2,2},     //U
	{20,19,20,20,15,14,9,10,127,4,4,2,9,1,8},      //V
	{21,25,26,28,16,16,21,19,172,6,2,4,13,0,7},    //W
	{21,21,13,13,12,11,22,21,134,4,2,4,8,0,10},    //X
	{21,20,10,11,10,10,10,11,103,3,2,2,5,2,6},     //Y
	{21,23,5,15,15,5,24,20,128,2,2,2,8,8,7},       //Z
	{13,14,10,10,10,10,13,13,93,2,2,2,29,2,29},    //I
	{20,20,13,20,19,12,17,20,141,3,3,4,4,4,4},     //O          //36
	{14,15,17,17,16,10,25,24,138,0,2,4,12,8,9},    //??        //37
	{17,20,17,12,33,28,23,20,170,3,4,7,13,6,4},    //??
	{21,21,23,24,24,25,31,27,196,0,9,6,8,6,7},     //??
	{19,27,20,34,19,36,24,37,216,4,4,7,13,28,3},   //??
	{17,14,23,27,36,40,26,27,210,4,13,4,16,14,14}, //??
	{24,24,32,38,34,32,17,22,223,9,6,10,11,12,9}, // ??
	{22,20,33,37,25,24,24,25,210,13,3,6,12,8,7},   //??
	{20,18,30,25,36,29,24,27,0,5,4,7,8,6} 
};//?? 24,20,30,24,37,30,25,27,0,5,4,7,9,8,???????????? ??????????
char *PlateCode[TEMPLETENUM] =   
{
	"0", "1", "2", "3", "4" ,
	"5","6", "7", "8", "9",
	"A", "B", "C", "D","E",
	"F", "G","H", "J", "K",
	"L", "M", "N","P", "Q",
	"R", "S", "T", "U", "V",
	"W","X", "Y", "Z", "I", "O",
	"??", "??","??", "??", "??","??","??","??"
};
char *Mess[7]={"*", "*","*", "*", "*", "*" ,"*"}; // ??????
//????????????????????
int AdaptiveThreshold(int t, IplImage *Image)
{
	int t1=0,t2=0,tnew=0,i=0,j=0;
	int Allt1=0,Allt2=0,accountt1=0,accountt2=0;
	for(j=0;j<Image->height;j++) //????????t????????????????????????????????????????????t1??t2
	{	
		for(i=0;i<Image->width;i++)
		{
			if(CV_IMAGE_ELEM(Image,uchar,j,i)<t)
			{
				Allt1+=CV_IMAGE_ELEM(Image,uchar,j,i);
				accountt1++;
			}
			else 
			{
				Allt2+=CV_IMAGE_ELEM(Image,uchar,j,i);
				accountt2++;
			}
		}
	}
	t1=Allt1/accountt1;
	t2=Allt2/accountt2;
	tnew=0.5*(t1+t2);
	//??t1??t2??????????t????????????????
	if(tnew==t) 
		return tnew;
	//????????????t1??t2????????????????????
	else 
		AdaptiveThreshold(tnew,Image); 
}


//??????????
void Threshold(IplImage *Image, IplImage *Image_O)
{
	int thresMax=0,thresMin=255,i=0,j=0,t=0;
	//????????????????????????????????????
	for(j=0;j<Image->height;j++)
		for(i=0;i<Image->width;i++)
		{
			if(CV_IMAGE_ELEM(Image,uchar,j,i)>thresMax) 
				thresMax=CV_IMAGE_ELEM(Image,uchar,j,i);
			else if(CV_IMAGE_ELEM(Image,uchar,j,i)<thresMin)   
				thresMin=CV_IMAGE_ELEM(Image,uchar,j,i);
		}

		//??????????????????????  ????????????????????????????????
		cvCanny(Image,Image_O,AdaptiveThreshold((thresMax+thresMin)*0.5,Image),thresMax*0.7,3);

}



//????????+????????
int PlateAreaSearch(IplImage *src, IplImage *pImg_Image, IplImage *pImgResize)
{
	// ????????????
	if (pImg_Image==NULL)	
	{ 
		return 0;	
	}

	IplImage* imgTest =0; 
	int i=0, j=0,k=0,m=0;
	bool flag=0;
	int plate_n=0;  //??????
	int plate_s=0;  //??????
	int plate_e=0;  //??????
	int plate_w=0;  //??????

	int *num_h=new int[MAX(pImg_Image->width,pImg_Image->height)];	 
	if ( num_h==NULL )  
	{
		//MessageBox("memory exhausted!");
		return 0;	
	} 

	//????????????????
	for(i=0;i<pImg_Image->width;i++)
	{
		num_h[i]=0;
	}  

	imgTest = cvCreateImage(cvSize(pImg_Image->width,pImg_Image->height),IPL_DEPTH_8U,1);
	cvCopy(pImg_Image, imgTest); 

	//--????????????
	for(j=0; j<imgTest->height; j++)
	{
		for(i=0;i<imgTest->width-1;i++)
		{
			CV_IMAGE_ELEM(imgTest,uchar,j,i)=CV_IMAGE_ELEM(imgTest,uchar,j,i+1)-CV_IMAGE_ELEM(imgTest,uchar,j,i);  //??????????????????
			//??????????????????
			num_h[j]+=CV_IMAGE_ELEM(imgTest,uchar,j,i)/250;      
		}		
	} 

	int temp_1 = 0;  //????20????????????????????
	int temp_max = 0;  //20?????????????? 
	int temp_i = 0;  //??????????????
	int POINT_X = 18;   //??????????????????????????????????
	int POINT_Y = 2;   //??????????????????????????????????	
	double HIGH_WITH_CAR = 4.8;
	double WITH_X = 0.1;
	double WITH_Y = 0.2;


	for(j=0; j<imgTest->height-20; j++)  
	{
		temp_1=0;
		for(i=0;i<20;i++)  
			temp_1 +=  num_h[i+j];
		if(temp_1>=temp_max)
		{
			temp_max=temp_1;
			temp_i = j;
		}
	}

	//??????????????
	k=temp_i;
	while ( ((num_h[k +1]>POINT_X )||(num_h[k +2]>POINT_X )||(num_h[k]>POINT_X )) && k ) k--;
	plate_n=k+1; 

	//????????????
	k=temp_i+10;
	while (((num_h[k -1]>POINT_X )||(num_h[k-2]>POINT_X )||(num_h[k]>POINT_X ))&&(k<imgTest->height)) k++; 
	plate_s=k;

	//??????????????????????????????
	if ( !(plate_n && plate_s
		&& (plate_n<plate_s) && ((plate_s-plate_n)*HIGH_WITH_CAR < imgTest->width*(1-WITH_X))))
	{
		//MessageBox("????????????!");
		return 0;
	}
	//?????????? 
	else 
	{
		int  max_count = 0;
		int  plate_length = (imgTest->width-(plate_s-plate_n)*HIGH_WITH_CAR);
		plate_w=imgTest->width*WITH_X-1;//???????? ????

		//--???????? ????????
		for(i=0;i<imgTest->width;i++)
			for(j=0;j<imgTest->height-1;j++) 
			{
				CV_IMAGE_ELEM(imgTest,uchar,j,i)=CV_IMAGE_ELEM(imgTest,uchar,j+1,i)-CV_IMAGE_ELEM(imgTest,uchar,j,i);
			}

			for(k=0;k<plate_length;k++)
			{ 
				for(i=0; i<(int)((plate_s-plate_n)*HIGH_WITH_CAR); i++)
					for (j=plate_n;j<plate_s;j++)//???????????? 
					{
						num_h[k] =num_h[k]+ CV_IMAGE_ELEM(imgTest,uchar,j,(i+k))/250;
					}
					if (num_h[k]>max_count)
					{
						max_count = num_h[k];
						plate_w = k;
					}

			}


			CvRect ROI_rect;                 //??????????????????
			ROI_rect.x=plate_w;
			ROI_rect.y=plate_n;
			ROI_rect.width=(plate_s-plate_n)*HIGH_WITH_CAR;
			ROI_rect.height=plate_s-plate_n;

			if ((ROI_rect.width+ROI_rect.x)> pImg_Image->width)
			{
				ROI_rect.width=pImg_Image->width-ROI_rect.x;   
				//MessageBox("????????????????!");
				return 0;
			}

			else
			{
				IplImage *pImg8uROI=NULL;         //????????????  
				pImg8uROI=cvCreateImage(cvSize(ROI_rect.width,ROI_rect.height), src->depth,src->nChannels);


				IplImage *pImg8u11=NULL;        //??????????????
				pImg8u11=cvCreateImage(cvSize(40*HIGH_WITH_CAR,40),pImg8uROI->depth,pImg8uROI->nChannels);

				cvSetImageROI(src,ROI_rect);
				cvCopy(src,pImg8uROI,NULL);
				cvResetImageROI(src);

				pImgResize=cvCreateImage(cvSize(40*HIGH_WITH_CAR,40),IPL_DEPTH_8U,1);	
				cvResize(pImg8uROI,pImg8u11,CV_INTER_LINEAR); //????????

				cvCvtColor(pImg8u11,pImgResize,CV_RGB2GRAY);
				Threshold(pImgResize,pImgResize);

				cvNamedWindow("windows3", 0);

				cvShowImage("windows3", pImgResize);   //????????????????????????

				cvWaitKey();

				//????????????

				if (pImgResize==NULL)  
				{ 
					return 0; 
				} 

				int *num_h=new int[MAX(pImgResize->width,pImgResize->height)];
				if ( num_h==NULL ) 
				{ 	
					//MessageBox("????????memory exhausted");
					return 0;	
				}

				int i=0,j=0,k=0;//???????? 12
				int  letter[16]={0,20,23,43,55,75,78,98,101,121,124,127,147,167,170,207}; // ????????
				bool flag1=0;  

				// ????????
				for(i=0;i<40*HIGH_WITH_CAR;i++)
				{	
					num_h[i]=0; // ??????????
					for(j=0;j<17;j++)  // 0-16
					{
						num_h[i]+=CV_IMAGE_ELEM(pImgResize,uchar,j,i)/45;
					}	
					for(j=24;j<40;j++)  // 24-39
					{
						num_h[i]+=CV_IMAGE_ELEM(pImgResize,uchar,j,i)/45;
					}
				}
				// ?????????????? ????????????????
				int	max_count=0;
				int flag=0; 
				for(i=30;i<40*HIGH_WITH_CAR;i++)
				{
					if(num_h[i]<POINT_Y)
					{
						max_count++;
						if(max_count==11)
						{
							letter[3]=i-11;//??????????????????
							while( (num_h[i]<POINT_Y)||(num_h[i-1]<POINT_Y) ) i++;
							letter[4]=i-1;//????????????????????
							break;
						}
					}
					else
					{
						max_count=0;
					}
				}

				// ??????
				for(i=0;i<40*HIGH_WITH_CAR;i++)
				{
					for(j=17;j<=24;j++)
					{
						num_h[i]+=CV_IMAGE_ELEM(pImgResize,uchar,j,i)/45;
					}
				}

				for(j=letter[3];j>0;j--)//????????????????????????????
				{
					if((num_h[j]<POINT_Y)&&(num_h[j-1]<POINT_Y))
					{
						letter[2]=j;                       //????????????????????
						letter[1]=(j>=23)?j-3:letter[1];   //????????????????????
						letter[0]=(j>=23)?j-23:letter[0];  //????????????????????
						break;
					}
				}

				j=2;  flag=0;flag1=0;//????????
				for(i=letter[4];i<40*HIGH_WITH_CAR;i++)  //??????????????????????????
				{
					if((num_h[i]>POINT_Y)&&(num_h[i-1]>POINT_Y) && !flag )
					{
						flag=1;
						flag1=0;
						letter[2*j]=i-1; //???? ????????????????????
						if(j==7)  //???? ?????????????????????? ???????? ????????,????????,??letter[13]=letter[12]+20
						{
							letter[2*j+1]=((letter[2*j]+20)>40*HIGH_WITH_CAR-1)?40*HIGH_WITH_CAR-1:letter[2*j]+20;
							break;
						}
					}
					else if((num_h[i]<POINT_Y)&&(num_h[i-1]<POINT_Y) && !flag1 && flag)//?????? ????????  
					{
						flag=0;
						flag1=1;
						letter[2*j+1]=i-1;
						j++;
					}  
				}   
				// ????????  
				for(i=0;i<40*HIGH_WITH_CAR-1;i++)
				{
					for(j=0;j<39;j++)
					{
						if(CV_IMAGE_ELEM(pImgResize,uchar,j,i)&&CV_IMAGE_ELEM(pImgResize,uchar,j,i+1)&&CV_IMAGE_ELEM(pImgResize,uchar,j+1,i)) //  01
							CV_IMAGE_ELEM(pImgResize,uchar,j,i)=0;                                                                                                                                                                                                                             //   1

						if(CV_IMAGE_ELEM(pImgResize,uchar,j,i)&&  CV_IMAGE_ELEM(pImgResize,uchar,j,i-1) &&CV_IMAGE_ELEM(pImgResize,uchar,j+1,i))     //  10
							CV_IMAGE_ELEM(pImgResize,uchar,j,i)=0;                                                                                                                                                                                                                               //    1          			

						if(CV_IMAGE_ELEM(pImgResize,uchar,j,i)&&CV_IMAGE_ELEM(pImgResize,uchar,j,i-1) &&CV_IMAGE_ELEM(pImgResize,uchar,j-1,i))         //   1      
							CV_IMAGE_ELEM(pImgResize,uchar,j,i)=0;                                                                                    // 10

						if(CV_IMAGE_ELEM(pImgResize,uchar,j,i)&&CV_IMAGE_ELEM(pImgResize,uchar,j,i+1) &&CV_IMAGE_ELEM(pImgResize,uchar,j-1,i))           // 1      
							CV_IMAGE_ELEM(pImgResize,uchar,j,i)=0;                                                                                 // 01
					}
				}	


				// ??????????????
				pImgCharOne=cvCreateImage(cvSize(20,40),IPL_DEPTH_8U,1);
				pImgCharTwo=cvCreateImage(cvSize(20,40),IPL_DEPTH_8U,1);
				pImgCharThree=cvCreateImage(cvSize(20,40),IPL_DEPTH_8U,1);
				pImgCharFour=cvCreateImage(cvSize(20,40),IPL_DEPTH_8U,1);
				pImgCharFive=cvCreateImage(cvSize(20,40),IPL_DEPTH_8U,1);
				pImgCharSix=cvCreateImage(cvSize(20,40),IPL_DEPTH_8U,1);
				pImgCharSeven=cvCreateImage(cvSize(20,40),IPL_DEPTH_8U,1);
				pImgCharEight=cvCreateImage(cvSize(20,40),IPL_DEPTH_8U,1);

				CvRect ROI_rect1;
				ROI_rect1.x=0.5*(letter[1]+letter[0])-10;
				ROI_rect1.y=0;
				ROI_rect1.width=20;
				ROI_rect1.height=40;
				cvSetImageROI(pImgResize,ROI_rect1);
				cvCopy(pImgResize,pImgCharOne,NULL); //??????1??????
				cvResetImageROI(pImgResize);


				ROI_rect1.x=0.5*(letter[3]+letter[2])-10;
				ROI_rect1.y=0;
				ROI_rect1.width=20;
				ROI_rect1.height=40;
				cvSetImageROI(pImgResize,ROI_rect1);
				cvCopy(pImgResize,pImgCharTwo,NULL); //??????2??????
				cvResetImageROI(pImgResize);


				ROI_rect1.x=0.5*(letter[5]+letter[4])-10;
				ROI_rect1.y=0;
				ROI_rect1.width=20;
				ROI_rect1.height=40;
				cvSetImageROI(pImgResize,ROI_rect1);
				cvCopy(pImgResize,pImgCharThree,NULL); //??????3??????
				cvResetImageROI(pImgResize);

				ROI_rect1.x=0.5*(letter[7]+letter[6])-10;
				ROI_rect1.y=0;
				ROI_rect1.width=20;
				ROI_rect1.height=40;
				cvSetImageROI(pImgResize,ROI_rect1);
				cvCopy(pImgResize,pImgCharFour,NULL); //??????4??????
				cvResetImageROI(pImgResize);

				ROI_rect1.x=0.5*(letter[9]+letter[8])-10;
				ROI_rect1.y=0;
				ROI_rect1.width=20;
				ROI_rect1.height=40;
				cvSetImageROI(pImgResize,ROI_rect1);
				cvCopy(pImgResize,pImgCharFive,NULL); //??????5??????
				cvResetImageROI(pImgResize);

				ROI_rect1.x=0.5*(letter[11]+letter[10])-10;
				ROI_rect1.y=0;
				ROI_rect1.width=20;
				ROI_rect1.height=40;
				cvSetImageROI(pImgResize,ROI_rect1);
				cvCopy(pImgResize,pImgCharSix,NULL); //??????6??????
				cvResetImageROI(pImgResize);

				ROI_rect1.x=0.5*(letter[13]+letter[12])-10;
				ROI_rect1.y=0;
				ROI_rect1.width=20;
				ROI_rect1.height=40;
				cvSetImageROI(pImgResize,ROI_rect1);
				cvCopy(pImgResize,pImgCharSeven,NULL); //??????7??????
				cvResetImageROI(pImgResize);
				cvShowImage("windows3", pImgCharSeven);   //????????????????????????

				cvWaitKey();

				/*ROI_rect1.x=0.5*(letter[15]+letter[14])-10;
				ROI_rect1.y=0;
				ROI_rect1.width=20;	
				ROI_rect1.height=40;
				cvSetImageROI(pImgResize,ROI_rect1);
				cvCopy(pImgResize,pImgCharEight,NULL); //??????8??????
				cvResetImageROI(pImgResize);

				cvShowImage("windows3", pImgCharEight);   //????????????????????????

				cvWaitKey();*/

				// ????????
				delete []num_h;  
				num_h=NULL;

			} 
	} 

	// ????????
	delete []num_h;  
	num_h=NULL;	 
	return 1;
}

//????????
int CodeRecognize(IplImage *imgTest,int num, int char_num)
{
	if (imgTest==NULL)
	{ 
		return 0;
	}

	int i=0,j=0,k=0,t=0;
	int  char_start=0,char_end=0;
	int num_t[CHARACTER]={0};

	switch(num)//??????????
	{
	case 0:  char_start =0;         // ????
		char_end  = 9;
		break;
	case 1:  char_start =10;        // ????
		char_end  = 35;
		break;
	case 2:  char_start =0;       // ??????????
		char_end  = 35;
		break;  
	case 3:  char_start =36;       // ????
		char_end  = TEMPLETENUM-1;
		break;
	default: break;              	
	}	

	// ??????8??????
	for(k=0; k<8; k++)
	{ 
		for(j=int(k/2)*10; j<int(k/2+1)*10; j++)
		{
			for(i=(k%2)*10;i<(k%2+1)*10;i++)
			{		
				num_t[k]+=CV_IMAGE_ELEM(imgTest,uchar,j,i)/255 ;
			}		
		}

		// ??9?????? ??8????????????????9????????
		num_t[8]+= num_t[k];  
	}

	for(i=0;i<20;i++)   
		num_t[9]+=CV_IMAGE_ELEM(imgTest,uchar,10,i)/255 ;
	for(i=0;i<20;i++)
		num_t[10]+=CV_IMAGE_ELEM(imgTest,uchar,20,i)/255 ;
	for(i=0;i<20;i++)
		num_t[11]+=CV_IMAGE_ELEM(imgTest,uchar,30,i)/255 ;

	for(j=0;j<40;j++)
		num_t[12]+=CV_IMAGE_ELEM(imgTest,uchar,j,7)/255;
	for(j=0;j<40;j++)
		num_t[13]+=CV_IMAGE_ELEM(imgTest,uchar,j,10)/255 ;
	for(j=0;j<40;j++)
		num_t[14]+=CV_IMAGE_ELEM(imgTest,uchar,j,13)/255 ;

	int num_tt[CHARACTER]={0};
	int matchnum=0;  //???????? ???????? ??????
	int matchnum_max=0;  
	int matchcode = 0;         // ??????

	j=0;

	for(k=char_start;k<=TEMPLETENUM-1;k++)
	{
		matchnum=0;

		for(i=0;i<8;i++) //??????????
		{
			if (abs(num_t[i]-Num_Templete[k][i])<=2)//????????????????????????
				matchnum++;
		}

		if(Num_Templete[k][i]-abs(num_t[i])<=8)//????9?????????????? 
			matchnum+=2;	
		for(i=9;i<CHARACTER;i++)  // ??????????  
		{
			if (Num_Templete[k][i]>=5)  //?????? ????5 
			{
				if(abs(num_t[i]-Num_Templete[k][i])<=1)
					matchnum+=2;
			}
			else if( num_t[i]==Num_Templete[k][i])
			{ 
				matchnum+=2;
			}
		}
		if(matchnum>matchnum_max)
		{
			matchnum_max=matchnum;  //?????????? ???? 
			matchcode= k;  //???? ???????????? ???? 
		}	
	}
	//????????  ????????????
	Mess[char_num]=PlateCode[matchcode]; //????????????
}

int main()
{
	IplImage *src = NULL;  
	IplImage *pImg8u=NULL;             //??????  
	IplImage *pImg8uSmooth=NULL;       //??????????????  
	IplImage *pImgCanny=NULL;          //??????????  
	IplImage *pImgResize=NULL;         //????????????????????
	src=cvLoadImage("4.png",-1);  
	if(src == NULL)
		return 0;
	pImg8u=cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1);  
	pImg8uSmooth=cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);  
	pImgCanny=cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1); 
	pImgResize=cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1); 

	//cvDilate(src,src);  	        //????????  

	cvCvtColor(src,pImg8u,CV_RGB2GRAY);     //??????????

	cvSmooth(pImg8u,pImg8uSmooth,CV_GAUSSIAN,3,0,0);       //????????????????   

	Threshold(pImg8uSmooth , pImgCanny);  //??????????????

	PlateAreaSearch(src, pImgCanny, pImgResize); //????????

	CodeRecognize(pImgCharOne,3, 0);  //????????
	CodeRecognize(pImgCharTwo,2, 1);  //????????
	CodeRecognize(pImgCharThree,2,2);  //????????
	CodeRecognize(pImgCharFour,2, 3);  //????????
	CodeRecognize(pImgCharFive,2, 4);  //????????
	CodeRecognize(pImgCharSix,2, 5);  //????????
	CodeRecognize(pImgCharSeven,2, 6);  //????????
	CodeRecognize(pImgCharEight,2, 7);  //????????

	for(int i = 0;i < 7;i++) {
		//if(i!=2)
			cout<<Mess[i];
	}
	cout<<endl;

	cvReleaseImage(&src);
	cvReleaseImage(&pImg8u);
	cvReleaseImage(&pImg8uSmooth);
	cvReleaseImage(&pImgCanny);
	cvReleaseImage(&pImgResize);
	cvReleaseImage(&pImgResize);   
	cvReleaseImage(&pImgCharOne);  
	cvReleaseImage(&pImgCharTwo);  
	cvReleaseImage(&pImgCharThree);  
	cvReleaseImage(&pImgCharFour);  
	cvReleaseImage(&pImgCharFive);  
	cvReleaseImage(&pImgCharSix);  
	cvReleaseImage(&pImgCharSeven);  
	system("pause");
	return 0;
}



