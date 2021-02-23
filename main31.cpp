#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;
using namespace std;

Mat src,gray_src,drawImg;
int threshold_v = 170;
int threshold_max = 255;
const char* source_win = "input image";
const char* output_win = "rectangle-demo";
RNG rng(12345);
void Contours_CallBack(int,void*);
int main()
{
    src = imread("F:/Qt/OpenCV/31/OPenCV31/1.png");
    if(src.empty())
    {
        qDebug()<<"could not load image...\n";
        return -1;
    }
    cvtColor(src,gray_src,CV_BGR2GRAY);
    blur(gray_src,gray_src,Size(3,3),Point(-1,-1));

    namedWindow(source_win,CV_WINDOW_AUTOSIZE);
    namedWindow(output_win,CV_WINDOW_AUTOSIZE);
    imshow(source_win,src);


    createTrackbar("Threshold Value:",output_win,&threshold_v,threshold_max,Contours_CallBack);
    Contours_CallBack(0,0);

    waitKey(0);
    return 0;
}
void Contours_CallBack(int,void*)
{
    Mat binary_output;
    vector<vector<Point>> contours;
    vector<Vec4i> hierachy;
    threshold(gray_src,binary_output,threshold_v,threshold_max,THRESH_BINARY);
    //发现轮廓
    findContours(binary_output,contours,hierachy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(-1,-1));

    vector<vector<Point>> contours_ploy(contours.size());//要画多少个多边形（好多个轮廓）
    vector<Rect> ploy_rects(contours.size());//要画多少个正方形
    vector<Point2f> ccs(contours.size());//要画多少各圆的圆心
    vector<float> radius(contours.size());//要画多少个圆的半径

    vector<RotatedRect> minRects(contours.size());//旋转矩形RotatedRect
    vector<RotatedRect> myellipse(contours.size());//旋转椭圆

    //typedef unsigned int size_t
    for (size_t i = 0;i <contours.size();i++)
    {
        //approxPolyDP()轮廓周围绘制矩形,基于RDP算法实现,目的是减少多边形轮廓点数
        approxPolyDP(Mat(contours[i]),contours_ploy[i],3,true);//输出值为contours_ploy[i]
        //boundingRect()返回得到轮廓周围最小矩形左上交点坐标和右下角点坐标，绘制一个矩形
        ploy_rects[i] = boundingRect(contours_ploy[i]);
        //minEnclosingCircle(得到最小区域圆形
        //InputArray points, 输入值
        //Point2f& center,  输出圆心位置
        //float& radius)， 输出圆的半径
        minEnclosingCircle(contours_ploy[i],ccs[i],radius[i]);
        if(contours_ploy[i].size() >5)
        {
            //fitEllipse(InputArray  points)得到最小椭圆
            myellipse[i] = fitEllipse(contours_ploy[i]);
            //minAreaRect()得到包覆轮廓的最小斜矩形。
            minRects[i] = minAreaRect(contours_ploy[i]);
        }
    }
    //绘制
    //drawImg = Mat::zeros(src.size(),src.type());
    src.copyTo(drawImg);
    Point2f pts[4];
    for (size_t t = 0;t < contours.size();t++)
    {
        Scalar color = Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
//        rectangle(src,ploy_rects[t],color,2,8);
//        circle(drawImg,ccs[t],radius[t],color,2,8);
        if(contours_ploy[t].size() >5)
        {
            ellipse(drawImg,myellipse[t],color,1,8);
            minRects[t].points(pts);
            for (int r = 0;r<4;r++)
            {
                line(drawImg,pts[r],pts[(r+1)%4],color,1,8);
            }
        }
    }
    imshow(output_win,drawImg);
}

