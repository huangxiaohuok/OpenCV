#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;
using namespace std;

Mat src,hsv,hue;
int bins = 12;
void Hist_Add_Backprojection(int,void*);
int main()
{

    src = imread("F:/Qt/OpenCV/27/OPenCV27/1.jpg");
    if(src.empty())
    {
        qDebug()<<"could not load image...\n";
        return -1;
    }
    const char* window_image = "input_image";
    namedWindow(window_image,CV_WINDOW_NORMAL);
    namedWindow("BackProj",CV_WINDOW_NORMAL);
    namedWindow("Histogram",CV_WINDOW_NORMAL);

    cvtColor(src,hsv,CV_BGR2HSV);
    hue.create(hsv.size(),hsv.depth());
    int nchannels[] = {0,0};
    mixChannels(&hsv,1,&hue,1,nchannels,1);//mixChannels主要就是把输入的矩阵（或矩阵数组）的某些通道拆分复制给对应的输出矩阵（或矩阵数组）的某些通道中，其中的对应关系就由fromTo参数指定.
    createTrackbar("Histogram Bins:",window_image,&bins,180,Hist_Add_Backprojection);
    Hist_Add_Backprojection(0,0);

    imshow(window_image,src);
    waitKey(0);
    return 0;
}
void Hist_Add_Backprojection(int,void*)
{
    float range[] = {0,180};
    const float* histRanges = {range};
    Mat h_hist;
    calcHist(&hue,1,0,Mat(),h_hist,1,&bins,&histRanges,true,false);
    normalize(h_hist,h_hist,0,255,NORM_MINMAX,-1,Mat());

    Mat backPrjImage;
    calcBackProject(&hue,1,0,h_hist,backPrjImage,&histRanges,1,true);
    imshow("BackProj",backPrjImage);

    int hist_h = 400;
    int hist_w = 400;
    Mat histImage(hist_h,hist_w,CV_8UC3,Scalar(0,0,0));
    int bin_w = (hist_w/bins);
    for(int i = 1;i<bins;i++)
    {
        rectangle(histImage,Point((i-1)*bin_w,(hist_h - cvRound(h_hist.at<float>(i - 1) * (400/255)))),
                  Point(i * bin_w,hist_h),Scalar(0,0,255),-1);
    }
    imshow("Histogram",histImage);

    return;
}

