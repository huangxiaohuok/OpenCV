#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;
using namespace std;

int main()
{
    Mat src,dst;
    src = imread("F:/Qt/OpenCV/22/OPenCV22/1.png");
    if(src.empty())
    {
        qDebug()<<"could not load image...\n";
        return -1;
    }

    char INPUT_TITLE[] = "input image";
    char OUTPUT_TITLE[] = "output image";
    namedWindow(INPUT_TITLE,CV_WINDOW_AUTOSIZE);
    namedWindow(OUTPUT_TITLE,CV_WINDOW_AUTOSIZE);
    imshow(INPUT_TITLE,src);

    //中值滤波
    Mat moutput;
    medianBlur(src,moutput,3);
    cvtColor(moutput,moutput,CV_BGR2GRAY);

    //霍夫圆检测
    vector<Vec3f> pcircles;
    //HoughCircles(moutput,pcircles,CV_HOUGH_GRADIENT,1,20,150,50,100,150);胶带
    //HoughCircles(moutput,pcircles,CV_HOUGH_GRADIENT,1,20,150,50,50,150);水杯
    HoughCircles(moutput,pcircles,CV_HOUGH_GRADIENT,1,10,150,24,5,50);
    src.copyTo(dst);


    for (int i = 0;i < pcircles.size();i++) {
        Vec3f cc = pcircles[i];
        circle(dst,Point(cc[0],cc[1]),cc[2],Scalar(0,0,255),2,LINE_AA);
        circle(dst,Point(cc[0],cc[1]),2,Scalar(0,0,255),2,LINE_AA);
    }
    imshow(OUTPUT_TITLE,dst);
    waitKey(0);
    return 0;
}

