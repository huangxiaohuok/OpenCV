#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;

int main()
{
    Mat src,dst;
    src = imread("F:/Qt/OpenCV/12/OPenCV12/OPenCV12/1.png");
    if(src.empty())
    {
        qDebug()<<"could not load image...\n";
        return -1;
    }
    namedWindow("input image",CV_WINDOW_AUTOSIZE);
    imshow("input image",src);

    char output_title[] = "morphology demo";
    namedWindow(output_title,CV_WINDOW_AUTOSIZE);
    //获得结构元素
    Mat kernel = getStructuringElement(MORPH_RECT,Size(13,13),Point(-1,-1));
    //开操作open,先腐蚀后膨胀
    //morphologyEx(src,dst,CV_MOP_OPEN,kernel);
    //闭操作close，先膨胀后腐蚀,填充小的洞
    //morphologyEx(src,dst,CV_MOP_CLOSE,kernel);
    //形态学梯度,Morphology Gradient
    morphologyEx(src,dst,CV_MOP_GRADIENT,kernel);
    //顶帽top hat,源图像与开操作之间的差值
    //morphologyEx(src,dst,CV_MOP_TOPHAT,kernel);
    //黑帽,闭操作图像与源图像的差值
    //morphologyEx(src,dst,CV_MOP_BLACKHAT,kernel);
    imshow(output_title,dst);
    waitKey(0);
    return 0;
}
