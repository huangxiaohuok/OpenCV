#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;
using namespace std;
Mat src,dst;
const char* output_win = "findcontours-demo";
int threshold_value = 100;
int threshold_max = 255;
RNG rng;
void Demo_Contours(int,void*);
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
    imshow("input-image",src);

    cvtColor(src,src,CV_BGR2GRAY);
    const char* trackbar_title = "Threshold Value:";
    createTrackbar(trackbar_title,output_win,&threshold_value,threshold_max,Demo_Contours);
    Demo_Contours(0,0);

    waitKey(0);
    return 0;
}
void Demo_Contours(int,void*)
{
    Mat canny_output;
    vector<vector<Point>> contours;//vector容器里面放了一个vector容器，子容器里放点
    vector<Vec4i> hierachy;//放了4维int向量

    Canny(src,canny_output,threshold_value,threshold_value * 2,3,false);
//    在二值图像上发现轮廓使用findContours(
//    InputOutputArray  binImg, // 输入图像，非0的像素被看成1,0的像素值保持不变，8-bit
//    OutputArrayOfArrays  contours,//  输出数组的数组全部发现的轮廓对象
//    OutputArray,  hierachy// 图该的拓扑结构，可选，该轮廓发现算法正是基于图像拓扑结构实现。
//    int mode, //  轮廓返回的模式
//    int method,// 发现方法
//    Point offset=Point()//  轮廓像素的位移，默认（0, 0）没有位移
//    )
    findContours(canny_output,contours,hierachy,RETR_TREE,
                 CHAIN_APPROX_SIMPLE,Point(0,0));
    dst = Mat::zeros(src.size(),CV_8UC3);
    rng(12345);
//    在二值图像上发现轮廓使用findContours之后对发现的轮廓数据进行绘制显示
//    drawContours(
//    InputOutputArray  binImg, // 输出图像
//    InputArrayOfArrays  contours,//  输入全部发现的轮廓对象
//    Int contourIdx// 轮廓索引号
//    const Scalar & color,// 绘制时候颜色
//    int  thickness,// 绘制线宽
//    int  lineType ,// 线的类型LINE_8
//    InputArray hierarchy,// 输入拓扑结构图
//    int maxlevel,// 最大层数， 0只绘制当前的，1表示绘制绘制当前及其内嵌的轮廓
//    Point offset=Point()// 轮廓位移，可选
    for(size_t i = 0;i<contours.size();i++)
    {
        Scalar color = Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
        drawContours(dst,contours,i,color,2,8,hierachy,0,Point(0,0));
    }
    imshow(output_win,dst);
}
//注意InputOutputArray，OutputArray,InputArrayOfArrays的区别
