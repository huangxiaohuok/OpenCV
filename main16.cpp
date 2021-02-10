#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;

int main()
{

    Mat src,dst;
    src = imread("F:/Qt/OpenCV/15/OPenCV15/OPenCV15/1.jpg");
    if(src.empty())
    {
        qDebug()<<"could not load image...\n";
        return -1;
    }

    char INPUT_WIN[] = "input image";
    char OUTPUT_WIN[] = "Custom Blur Filter Result";

    namedWindow(INPUT_WIN,CV_WINDOW_AUTOSIZE);
    namedWindow(OUTPUT_WIN,CV_WINDOW_AUTOSIZE);
    imshow(INPUT_WIN,src);

    //Robert算子
    //Mat rob_x = (Mat_<int>(2,2)<<1,0,0,-1);//X方向
    //Mat rob_x = (Mat_<int>(2,2)<<0,1,-1,0);//Y方向
    //filter2D(src,dst,-1,rob_x,Point(-1,-1),0,0);
    //imshow(OUTPUT_WIN,dst);

    //Sobel算子
    //Mat Sob_x = (Mat_<int>(3,3)<<-1,0,1,-2,0,2,-1,0,1);//X方向
//    Mat Sob_x = (Mat_<int>(3,3)<<-1,-2,-1,0,0,0,1,2,1);//y方向
//    filter2D(src,dst,-1,Sob_x,Point(-1,-1),0,0);
//    imshow(OUTPUT_WIN,dst);

    //拉普拉斯算子
//    Mat Lpl = (Mat_<int>(3,3)<<0,-1,0,-1,4,-1,0,-1,0);
//    filter2D(src,dst,-1,Lpl,Point(-1,-1),0,0);
//    imshow(OUTPUT_WIN,dst);

    //自定义卷积模糊
    int c = 0;
    int index = 1;
    int ksize = 3;
    while (true) {
        c = waitKey(500);
        if((char) c == 27){
            break;
        }
        ksize = 3 + 2*(index%5) + 1;
        Mat kernel = Mat::ones(Size(ksize,ksize),CV_32F) / (float)(ksize*ksize);
        filter2D(src,dst,-1,kernel,Point(-1,-1),0);
        imshow(OUTPUT_WIN,dst);
        index++;
    }



    //waitKey(0);
    return 0;

}

