#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;

int main(int argc, char *argv[])
{
    Mat src,dst;
    src = imread("F:/Qt/OpenCV/10/OPenCV10/1.jpg");
    if(src.empty())
    {
        qDebug()<<"could not load image...\n";
        return -1;
    }
    namedWindow("input image",CV_WINDOW_NORMAL);
    imshow("input image",src);

    //medianBlur(src,dst,3);//中值模糊,ksize必须大于1并且为奇数
    bilateralFilter(src,dst,15,100,3);//双边模糊
    namedWindow("BiBlur Filter Result",CV_WINDOW_NORMAL);
    imshow("BiBlur Filter Result",dst);

    //Mat gblur;
    //GaussianBlur(src,gblur,Size(15,15),3,3);//高斯模糊
    //imshow("Gaussion Blur Demo",gblur);
    Mat resultImg;
    Mat kernel = (Mat_<int>(3,3)<<0,-1,0,-1,5,-1,0,-1,0);
    filter2D(dst,resultImg,-1,kernel,Point(-1,-1),0);//提高对比度
    namedWindow("Final Result",CV_WINDOW_NORMAL);
    imshow("Final Result",resultImg);


    waitKey(0);
    return 0;

}

