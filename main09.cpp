#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;
int main()
{
    Mat src,dst;
    src = imread("F:/Qt/OpenCV/20/OPenCV20/1.jpg");
    if(src.empty())
    {
        qDebug()<<"could not load image...\n";
        return -1;
    }

    char INPUT_TITLE[] = "input image";
    char OUTPUT_TITLE[] = "blur image";
    namedWindow(INPUT_TITLE,CV_WINDOW_AUTOSIZE);
    namedWindow(OUTPUT_TITLE,CV_WINDOW_AUTOSIZE);
    imshow(INPUT_TITLE,src);

    blur(src,dst,Size(11,11),Point(-1,-1));//均值模糊
    imshow(OUTPUT_TITLE,dst);

    Mat gblur;
    //sigmaX，表示高斯核函数在X方向的的标准偏差。sigmaY，表示高斯核函数在Y方向的的标准偏差。
    //若sigmaY为零，就将它设为sigmaX，如果sigmaX和sigmaY都是0，那么就由ksize.width和ksize.height计算出来。
    GaussianBlur(src,gblur,Size(11,11),11,11);
    imshow("gaussian blur",gblur);

    waitKey(0);
    return 0;
}
