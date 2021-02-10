#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;

int main()
{
    Mat src,dst;
    src = imread("F:/Qt/OpenCV/14/OPenCV14/OPenCV14/1.jpg");
    if(src.empty())
    {
        qDebug()<<"could not load image...\n";
        return -1;
    }
    char INPUT_WIN[] = "input image";
    char OUTPUT_WIN[] = "sample image";

    namedWindow(INPUT_WIN,CV_WINDOW_AUTOSIZE);
    imshow(INPUT_WIN,src);

    //上采样（放大）
    pyrUp(src,dst,Size(src.cols*2,src.rows*2));
    imshow(OUTPUT_WIN,dst);

    //降采样（缩小）
    Mat s_down;
    pyrDown(src,s_down,Size(src.cols/2,src.rows/2));
    imshow("sample down",s_down);

    //DOG,高斯不同
    Mat gray_src,g1,g2,dogImg;
    cvtColor(src,gray_src,CV_BGR2GRAY);
    GaussianBlur(gray_src,g1,Size(5,5),0,0);
    GaussianBlur(g1,g2,Size(5,5),0,0);
    subtract(g1,g2,dogImg,Mat());
    //归一化显示
    normalize(dogImg,dogImg,255,0,NORM_MINMAX);
    imshow("DOG Imge",dogImg);

    waitKey(0);
    return 0;

}
