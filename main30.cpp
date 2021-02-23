#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;
using namespace std;

Mat src,src_gray,dst;
const char* output_win = "convex hull demo";
int threshold_value = 100;
int threshold_max = 255;
RNG rng(12345);
void Threshold_Callback(int,void*);
int main()
{

    src = imread("F:/Qt/OpenCV/29/OPenCV29/1.jpg");
    if(src.empty())
    {
        qDebug()<<"could not load image...\n";
        return -1;
    }
    namedWindow("input-image",CV_WINDOW_AUTOSIZE);
    namedWindow(output_win,CV_WINDOW_AUTOSIZE);
    const char* trackbar_title = "Threshold Value:";

    cvtColor(src,src_gray,CV_BGR2GRAY);
    blur(src_gray,src_gray,Size(3,3),Point(-1,-1),BORDER_DEFAULT);
    imshow("input-image",src_gray);

    createTrackbar(trackbar_title,output_win,&threshold_value,threshold_max,Threshold_Callback);
    Threshold_Callback(0,0);

    waitKey(0);
    return 0;
}
void Threshold_Callback(int,void*)
{
    Mat bin_output;
    vector<vector<Point>> contours;
    vector<Vec4i> hierachy;

    threshold(src_gray,bin_output,threshold_value,threshold_max,THRESH_BINARY);
    findContours(bin_output,contours,hierachy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));

    vector<vector<Point>> convexs(contours.size());
    for (size_t i = 0 ;i < contours.size();i++)
    {
        convexHull(contours[i],convexs[i],false,true);
    }
    dst = Mat::zeros(src.size(),CV_8UC3);
    vector<Vec4i> empty(0);
    for (size_t k = 0;k < contours.size();k++)
    {
        Scalar color = Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
        //绘制轮廓
        drawContours(dst,contours,k,color,2,LINE_8,hierachy,0,Point(0,0));
        //绘制凸包
        drawContours(dst,convexs,k,color,2,LINE_8,empty,0,Point(0,0));
    }
    imshow(output_win,dst);
}

