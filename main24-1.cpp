#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;
using namespace std;

int main()
{

    Mat src,dst;
    src = imread("F:/Qt/OpenCV/24/OPenCV24/1.jpg");
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

    //cvtColor(src,src,CV_BGR2GRAY);
//    equalizeHist(
//       InputArray src,//输入图像，必须是8-bit的单通道图像
//       OutputArray dst// 输出结果
//        )
    vector<Mat> channels;//定义存储的容器
    split(src,channels);//图像通道分离
    Mat bluechannel = channels[0];//b通道图像
    equalizeHist(bluechannel,bluechannel);//直方图均衡化，是一种提高图像对比度的方法，拉伸图像灰度值范围。
    Mat greenchannel = channels[1];//g通道图像
    equalizeHist(greenchannel,greenchannel);
    Mat redchannel = channels[2];//r通道图像
    equalizeHist(redchannel,redchannel);

    merge(channels,dst);//合并通道
    imshow(OUTPUT_TITLE,dst);

    waitKey(0);
    return 0;
}
