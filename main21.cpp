#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;
using namespace std;

int main()
{
    Mat src,src_gray,dst;
    src = imread("F:/Qt/OpenCV/21/OPenCV21/1.png");
    if(src.empty())
    {
        qDebug()<<"could not load image...\n";
        return -1;
    }

    char INPUT_TITLE[] = "input image";
    char OUTPUT_TITLE[] = "output image";
    namedWindow(INPUT_TITLE,CV_WINDOW_NORMAL);
    namedWindow(OUTPUT_TITLE,CV_WINDOW_NORMAL);
    imshow(INPUT_TITLE,src);

    //边缘检测
    Canny(src,src_gray,150,200);
    cvtColor(src_gray,dst,CV_GRAY2BGR);
    //imshow("edge imge",src_gray);

    vector<Vec4f> plines;
    HoughLinesP(src_gray,plines,1,CV_PI/180,10,0,10);
    Scalar color = Scalar(0,0,255);
    for (int i = 0; i < plines.size();i++) {
        Vec4f hline = plines[i];
        line(dst,Point(hline[0],hline[1]),Point(hline[2],hline[3]),color,LINE_AA);
    }
    imshow(OUTPUT_TITLE,dst);

    waitKey(0);
    return 0;
}

