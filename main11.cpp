#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;

Mat src,dst,gray_src;
char OUTPUT_WIN[] = "output image";
int element_size = 3;
int max_size = 21;
void CallBack_Demo(int,void *);
int main()
{

    src = imread("F:/Qt/OpenCV/11/OPenCV11/OPenCV11/1.jpg");
    if(src.empty())
    {
        qDebug()<<"could not load image...\n";
        return -1;
    }
    namedWindow("input image",CV_WINDOW_AUTOSIZE);
    imshow("input image",src);

    namedWindow(OUTPUT_WIN,CV_WINDOW_AUTOSIZE);
    createTrackbar("Element Size:",OUTPUT_WIN,&element_size,max_size,CallBack_Demo);

    CallBack_Demo(0,0);

    waitKey(0);
    return 0;
}
void CallBack_Demo(int,void *)
{
    int s = element_size * 2 +1;//必须为奇数
    Mat structureElement = getStructuringElement(MORPH_RECT,Size(s,s),Point(-1,-1));
    //膨胀,最大值替换最小值
     dilate(src,dst,structureElement);
    //腐蚀,最小值替换最大值
    //erode(src,dst,structureElement);


    imshow(OUTPUT_WIN,dst);
}
