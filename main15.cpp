#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;
Mat src,dst,gray_src;
const char* output_title = "binary image";
int threshold_value = 127;
int threshold_max = 255;
int type_value = 2;
int type_max = 4;
void Threshold_Demo(int,void*);

int main()
{

    src = imread("F:/Qt/OpenCV/15/OPenCV15/OPenCV15/1.jpg");
    if(src.empty())
    {
        qDebug()<<"could not load image...\n";
        return -1;
    }

    namedWindow("input image",CV_WINDOW_AUTOSIZE);
    namedWindow(output_title,CV_WINDOW_AUTOSIZE);//如果不创建窗口就不会的看到滚动条
    imshow("input image",src);

    createTrackbar("Threshold Value:",output_title,&threshold_value,threshold_max,Threshold_Demo);
    createTrackbar("Type Value:",output_title,&type_value,type_max,Threshold_Demo);
    Threshold_Demo(0,0);

    waitKey(0);
    return 0;

}
void Threshold_Demo(int,void*)
{
    cvtColor(src,gray_src,CV_BGR2GRAY);
    //threshold(gray_src,dst,threshold_value,threshold_max,THRESH_BINARY);
    //threshold(gray_src,dst,threshold_value,threshold_max,type_value);
    threshold(gray_src,dst,0,255,THRESH_OTSU | type_value);//自动求阈值
    //threshold(gray_src,dst,0,255,THRESH_TRIANGLE | type_value);//自动求阈值
    imshow(output_title,dst);
}
