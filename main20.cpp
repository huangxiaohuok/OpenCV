#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;
Mat src,dst,gray_src;
int t1_value = 50;
int max_value = 255;
const char* OUTPUT_TITLE = "Canny Result";
void Canny_Demo(int,void*);
int main()
{
    src = imread("F:/Qt/OpenCV/20/OPenCV20/1.jpg");
    if(src.empty())
    {
        qDebug()<<"could not load image...\n";
        return -1;
    }

    char INPUT_TITLE[] = "input image";
    namedWindow(INPUT_TITLE,CV_WINDOW_AUTOSIZE);
    namedWindow(OUTPUT_TITLE,CV_WINDOW_AUTOSIZE);
    imshow(INPUT_TITLE,src);


    cvtColor(src,gray_src,CV_BGR2GRAY);
    createTrackbar("Threshold Value:",OUTPUT_TITLE,&t1_value,max_value,Canny_Demo);
    Canny_Demo(0,0);
    waitKey(0);
    return 0;
}
void Canny_Demo(int,void*)
{
    Mat edge_output;
    blur(gray_src,gray_src,Size(3,3),Point(-1,-1),BORDER_DEFAULT);
    Canny(gray_src,edge_output,t1_value,t1_value*2,3,false);
    imshow(OUTPUT_TITLE,~edge_output);
}
