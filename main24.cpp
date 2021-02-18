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
    char OUTPUT_TITLE[] = "output image";
    namedWindow(INPUT_TITLE,CV_WINDOW_AUTOSIZE);
    namedWindow(OUTPUT_TITLE,CV_WINDOW_AUTOSIZE);
    imshow(INPUT_TITLE,src);

    cvtColor(src,src,CV_BGR2GRAY);

//    equalizeHist(
//       InputArray src,//输入图像，必须是8-bit的单通道图像
//       OutputArray dst// 输出结果
//        )

    equalizeHist(src,dst);//直方图均衡化，是一种提高图像对比度的方法，拉伸图像灰度值范围。
    imshow(OUTPUT_TITLE,dst);

    waitKey(0);
    return 0;
}
