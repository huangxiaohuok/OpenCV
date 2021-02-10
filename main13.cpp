#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;

int main()
{
    Mat src,dst;
    src = imread("F:/Qt/OpenCV/13/OPenCV13/OPenCV13/2.png");
    if(src.empty())
    {
        qDebug()<<"could not load image...\n";
        return -1;
    }
    char INPUT_WIN[] = "input image";
    char OUTPUT_WIN[] = "result image";
    namedWindow(INPUT_WIN,CV_WINDOW_AUTOSIZE);
    imshow(INPUT_WIN,src);

    Mat gray_src;
    cvtColor(src,gray_src,CV_BGR2GRAY);//转换为灰度图像
    imshow("gray image",gray_src);

    Mat binImg;
    //转换为二值图像
    adaptiveThreshold(~gray_src,binImg,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,15,-2);
    imshow("binary image",binImg);

    //水平结构元素
    Mat hline = getStructuringElement(MORPH_RECT,Size(src.cols/16,1),Point(-1,-1));
    //垂直结构元素
    Mat vline = getStructuringElement(MORPH_RECT,Size(1,src.rows/16),Point(-1,-1));
    //矩形结构元素
    Mat rect = getStructuringElement(MORPH_RECT,Size(5,5),Point(-1,-1));
    Mat temp;
//    erode(binImg,temp,vline);//腐蚀
//    dilate(temp,dst,vline);//膨胀
    //morphologyEx(binImg,dst,CV_MOP_OPEN,vline);//开操作相当于先腐蚀后膨胀
    morphologyEx(binImg,dst,CV_MOP_OPEN,rect);
    bitwise_not(dst,dst);//取反
    //blur(dst,dst,Size(3,3),Point(-1,-1));
    imshow(OUTPUT_WIN,dst);

    waitKey(0);
    return 0;

}
