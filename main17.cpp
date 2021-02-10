#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;

int main()
{

    Mat src,dst;
    src = imread("F:/Qt/OpenCV/17/OPenCV17/1.jpg");
    if(src.empty())
    {
        qDebug()<<"could not load image...\n";
        return -1;
    }

    char INPUT_WIN[] = "input image";
    char OUTPUT_WIN[] = "output image";

    namedWindow(INPUT_WIN,CV_WINDOW_AUTOSIZE);
    namedWindow(OUTPUT_WIN,CV_WINDOW_AUTOSIZE);
    imshow(INPUT_WIN,src);

//    int flag = 0;
//    int border_type = BORDER_DEFAULT;
//    RNG rng(12345);
//    Scalar color;
//    int top = (int)(0.05*src.rows);
//    int bottom = (int)(0.05*src.rows);
//    int left = (int)(0.05*src.cols);
//    int right = (int)(0.05*src.cols);

//    while (true) {
//        flag = waitKey(500);
//        if((char)flag == 27)
//        {
//            break;
//        }
//        if((char)flag == 'c')
//            border_type = BORDER_CONSTANT;//填充边缘用指定像素值
//        else if((char)flag == 'r')
//            border_type = BORDER_REPLICATE;//填充边缘像素用已知的边缘像素值
//        else if((char)flag == 'w')
//            border_type = BORDER_WRAP;//用另外一边的像素来补偿填充
//        else if((char)flag == 'd')
//            border_type = BORDER_DEFAULT;
//        Scalar color = Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
//        copyMakeBorder(src,dst,top,bottom,left,right,border_type,color);
//        imshow(OUTPUT_WIN,dst);

//    }
    GaussianBlur(src,dst,Size(5,5),0,0,BORDER_WRAP);
    imshow(OUTPUT_WIN,dst);
    waitKey(0);
    return 0;
}

