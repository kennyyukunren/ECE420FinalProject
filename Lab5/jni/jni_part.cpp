#include <jni.h>
#include <opencv2/core/core.hpp>
#include <android/log.h>

using namespace std;
using namespace cv;

typedef unsigned char uint8;

extern "C" {

// function declaration for manual color conversion
uint8* YUV2RGB(uint8, int, int);

JNIEXPORT void JNICALL Java_org_ece420_lab5_Sample4View_YUV2RGB(JNIEnv*, jobject, jlong addrYuv, jlong addrRgba)
{
    Mat* pYUV=(Mat*)addrYuv;
    Mat* pRGB=(Mat*)addrRgba;

    /*************** INSERT CODE TO CONVERT AN ENTIRE IMAGE FROM FROM YUV420sp TO ARGB ******************/
    //pYUV.at<>;
    Size s=(*pYUV).size();
    int height = s.height;
    int width = s.width;
    Size s1=(*pRGB).size();
    int height_1=s1.height;
    int width_1=s1.width;
    //logCat
            char buf[128];
            sprintf(buf,"iteration height=%d width=%d \n"
            		"height_1=%d width_1=%d",height, width,height_1,width_1);
            __android_log_write(ANDROID_LOG_INFO, "Dimension Info", buf);

    int size = width*height;
    int height_img=height*4/6;
    size=4*size/6;
    int offset = size;
    uint8 y1, y2, y3, y4;
	int u,v;
	uint8* RGBReturnArray1;
	uint8* RGBReturnArray2;
	uint8* RGBReturnArray3;
	uint8* RGBReturnArray4;
    // Vec3b intensity = pYUV.at<Vec3b>(y, x);
    // i along Y and the final pixels
    // k along pixels U and V
	// i along row
	// j along columns
	int k=0;
    for(int j=0;  j < height_img; j+=2) {
    	for(int i=0; i<width;i+=2){

    		y1 = ((*pYUV).at<uchar>(Point(i,j  )));
    		y2 = ((*pYUV).at<uchar>(Point(i+1,j)));
    		y3 = ((*pYUV).at<uchar>(Point(i, j+1)));
    		y4 = ((*pYUV).at<uchar>(Point(i+1, j+1)));
    		u  = ((*pYUV).at<uchar>(Point(offset+k+1)));
    		v  = ((*pYUV).at<uchar>(Point(offset+k)));
    		v = v-128;
    		u = u-128;

    		//[2] is y [1] is u [0] is v
			RGBReturnArray1=YUV2RGB(y1, u, v);
			RGBReturnArray2=YUV2RGB(y2, u, v);
			RGBReturnArray3=YUV2RGB(y3, u, v);
			RGBReturnArray4=YUV2RGB(y4, u, v);
    		for(int l=0; l<4; l++){
			(*pRGB).at<Vec4b>(Point(i,j)).val[l]=RGBReturnArray1[l];
			(*pRGB).at<Vec4b>(Point(i+1,j)).val[l]=RGBReturnArray2[l];
			(*pRGB).at<Vec4b>(Point(i,j+1)).val[l]=RGBReturnArray3[l];
			(*pRGB).at<Vec4b>(Point(i+1,j+1)).val[l]=RGBReturnArray4[l];
    		}
			k+=2;
    	}
    }
}


JNIEXPORT void JNICALL Java_org_ece420_lab5_Sample4View_HistEQ(JNIEnv* env, jobject thiz, jlong addrYuv, jlong addrRgba)
{
    Mat* pYUV=(Mat*)addrYuv;
    Mat* pRGB=(Mat*)addrRgba;

    Size s=(*pYUV).size();
    int height = s.height;
    int width = s.width;
    Size s1=(*pRGB).size();
    int height_1=s1.height;
    int width_1=s1.width;
    //logCat
            char buf[128];
            sprintf(buf,"iteration height=%d width=%d \n"
            		"height_1=%d width_1=%d",height, width,height_1,width_1);
            __android_log_write(ANDROID_LOG_INFO, "Dimension Info", buf);

    int size = width*height;
    int height_img=height*4/6;
    size=4*size/6;
    int offset = size;
    uint8 y1, y2, y3, y4;
   	int u,v;
   	int i;
   	uint8* RGBReturnArray1;
   	uint8* RGBReturnArray2;
   	uint8* RGBReturnArray3;
   	uint8* RGBReturnArray4;

   	int histo[256];
   	int cdf[256];
   	for(i=0;i<256;i++){
   		histo[i]=0;
   	}
   	for(i=0;i<size;i++){
   		histo[(*pYUV).at<uchar>(i)]+=1;
   	}
   	cdf[0]=histo[0];
   	for(i=1;i<256;i++){
   		cdf[i]=cdf[i-1]+histo[i];
   	}
   	for(i=0; i<256; i++){
   		cdf[i]=cdf[i]*254/cdf[255];
   	}
   	for(i=0;i<size;i++){
   		(*pYUV).at<uchar>(i)=cdf[(*pYUV).at<uchar>(i)];
   		if(i!=0 && ((i % width) > width/2)){
   			i+= width/2-1;
   		}
   	}
    // Vec3b intensity = pYUV.at<Vec3b>(y, x);
    // i along Y and the final pixels
    // k along pixels U and V
	// i along row
	// j along columns
	int k=0;
    for(int j=0;  j < height_img; j+=2) {
    	for(int i=0; i<width;i+=2){

    		y1 = ((*pYUV).at<uchar>(Point(i,j  )));
    		y2 = ((*pYUV).at<uchar>(Point(i+1,j)));
    		y3 = ((*pYUV).at<uchar>(Point(i, j+1)));
    		y4 = ((*pYUV).at<uchar>(Point(i+1, j+1)));
    		u  = ((*pYUV).at<uchar>(Point(offset+k+1)));
    		v  = ((*pYUV).at<uchar>(Point(offset+k)));
    		v = v-128;
    		u = u-128;

    		//[2] is y [1] is u [0] is v
			RGBReturnArray1=YUV2RGB(y1, u, v);
			RGBReturnArray2=YUV2RGB(y2, u, v);
			RGBReturnArray3=YUV2RGB(y3, u, v);
			RGBReturnArray4=YUV2RGB(y4, u, v);
    		for(int l=0; l<4; l++){
			(*pRGB).at<Vec4b>(Point(i,j)).val[l]=RGBReturnArray1[l];
			(*pRGB).at<Vec4b>(Point(i+1,j)).val[l]=RGBReturnArray2[l];
			(*pRGB).at<Vec4b>(Point(i,j+1)).val[l]=RGBReturnArray3[l];
			(*pRGB).at<Vec4b>(Point(i+1,j+1)).val[l]=RGBReturnArray4[l];
    		}
			k+=2;
    	}
    }
// EXAMPLE SHOWING HOW TO DISPLAY DEBUGGING INFORMATION TO ADB LOGCAT
//        char buf[128];
//        sprintf(buf,"iteration i=%d",i);
//        __android_log_write(ANDROID_LOG_INFO, "Example Logging", buf);


}

uint8* YUV2RGB(uint8 y, int u, int v) {

	/**************** INSERT CODE TO CONVERT A YUV PIXEL TO A 32-BIT INT REPRESENTING AN ARGB PIXEL ****************/

	uint8 RGB_array[4];	//0:b 1:g 2:r initialize arary
	int r,g,b;

	r=(int)y+(int)(1.14f*v);			//r
	g=(int)y-(int)(0.581f*v+0.395f*u);	//g
	b=(int)y+(int)(2.033f*u);			//b
	r = r>255? 255:(r<0? 0:r);
	g = g>255? 255:(g<0? 0:g);
	b = b>255? 255:(b<0? 0:b);
	//return 0xff000000 | (r<<16) | (g<<8) | b;
	RGB_array[2]=(uint8)b;
	RGB_array[1]=(uint8)g;
	RGB_array[0]=(uint8)r;
	RGB_array[3]=0xFF;
	return RGB_array;

}
}

