#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;

int main()
{

    Mat src,dst,gray_src;
    src = imread("F:/Qt/OpenCV/20/OPenCV20/1.jpg");
    if(src.empty())
    {
        qDebug()<<"could not load image...\n";
        return -1;
    }

    char INPUT_WIN[] = "input image";
    char OUTPUT_WIN[] = "output image";

    namedWindow(INPUT_WIN,CV_WINDOW_NORMAL);
    namedWindow(OUTPUT_WIN,CV_WINDOW_NORMAL);
    imshow(INPUT_WIN,src);
    GaussianBlur(src,dst,Size(3,3),0,0);
    cvtColor(dst,gray_src,CV_BGR2GRAY);
    //imshow("gray_src",gray_src);

    Mat xgrad,ygrad;
    Scharr(gray_src,xgrad,CV_16S,1,0);
    Scharr(gray_src,ygrad,CV_16S,0,1);

//    Sobel(gray_src,xgrad,CV_16S,1,0);
//    Sobel(gray_src,ygrad,CV_16S,0,1);
    convertScaleAbs(xgrad,xgrad);
    convertScaleAbs(ygrad,ygrad);
    //imshow("xgrad",xgrad);
    //imshow("ygrad",ygrad);

    Mat xygrad = Mat(xgrad.size(),xgrad.type());
   int width = xgrad.cols;
   int height = ygrad.rows;
   for(int row = 0;row<height;row++){
       for(int col = 0;col<width;col++)
       {
           int xg = xgrad.at<uchar>(row,col);
           int yg = ygrad.at<uchar>(row,col);
           int xy = xg +yg;
           xygrad.at<uchar>(row,col) = saturate_cast<uchar>(xy);
       }
   }
    //addWeighted(xgrad,0.5,ygrad,0.5,0,xygrad);
    threshold(xygrad,xygrad,0,255,THRESH_OTSU | THRESH_BINARY);
    imshow(OUTPUT_WIN,~xygrad);
    imwrite("1-2.jpg",~xygrad);

    waitKey(0);
    return 0;
}
