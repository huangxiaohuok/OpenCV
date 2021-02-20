#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;
using namespace std;

Mat src,hsv,hue;
Mat Hue,Sat,Val;
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
    int nchannels[] = {0,0};//指定被复制通道与要复制到的位置组成的索引对
    mixChannels(&hsv,1,&hue,1,nchannels,1);//mixChannels函数把hsv中0通道的色相值复制到Hue中的0通道
    
    //分离Hue/色相通道
    int ch[] = {0, 0};
    Hue.create(hsv.size(),hsv.depth());
    mixChannels(&hsv, 1, &Hue, 1, ch, 1);
    imshow("H channel", Hue);
    //分离Saturation/饱和度通道
    int ch1[] = {1, 0};
    Sat.create(hsv.size(),hsv.depth());
    mixChannels(&hsv, 1, &Sat, 1, ch1, 1);
    imshow("S channel", Sat);
    //分离Value/色调通道
    int ch2[] = {2, 0};
    Val.create(hsv.size(),hsv.depth());
    mixChannels(&hsv, 1, &Val, 1, ch2, 1);
    imshow("V channel", Val);
    
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
    //反向投影矩阵中某点的值就是它对应的原图像中的点所在区间的灰度直方图值
    //先求出原图像的直方图，再由直方图得到反向投影矩阵，由直方图到反向投影矩阵实际上就是一个反向的过程，所以叫反向
    //该bin值代表了（目标区域）上该像素值出现的概率
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

