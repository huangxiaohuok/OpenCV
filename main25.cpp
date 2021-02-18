#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;
using namespace std;

int main()
{

    Mat src;
    src = imread("F:/Qt/OpenCV/18/OPenCV18/1.jpg");
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

   //分通道显示
    vector<Mat> bgr_planes;
//    split(// 把多通道图像分为多个单通道图像
//    const Mat &src, //输入图像
//    Mat* mvbegin）// 输出的通道图像数组

    split(src,bgr_planes);
    //计算直方图
    int histSize = 256;//表示在维度中子区域大小划分，bins=256，划分为256个级别
    float range[] = {0,256};//表示值得范围，灰度值范围为[0~255]之间
    const float *histranges = {range};
    Mat b_hlist,g_hlist,r_hlist;
//    calcHist(
//     const Mat* images,//输入图像指针
//    int images,// 图像数目
//    const int* channels,// 通道数
//    InputArray mask,// 输入mask，可选，不用
//    OutputArray hist,//输出的直方图数据
//    int dims,// 维数
//    const int* histsize,// 直方图级数
//    const float* ranges,// 值域范围
//    bool uniform,// true by default
//    bool accumulate// false by defaut
//    )

    calcHist(&bgr_planes[0],1,0,Mat(),b_hlist,1,&histSize,&histranges,true,false);
    calcHist(&bgr_planes[1],1,0,Mat(),g_hlist,1,&histSize,&histranges,true,false);
    calcHist(&bgr_planes[2],1,0,Mat(),r_hlist,1,&histSize,&histranges,true,false);
    //imshow(OUTPUT_TITLE,b_list);
    //归一化
    int hist_h = 400;
    int hist_w = 512;
    int bin_w = hist_w / histSize;

    Mat histImage(hist_h,hist_w,CV_8UC3,Scalar(0,0,0));
    normalize(b_hlist,b_hlist,0,hist_h,NORM_MINMAX,-1,Mat());
    normalize(g_hlist,g_hlist,0,hist_h,NORM_MINMAX,-1,Mat());
    normalize(r_hlist,r_hlist,0,hist_h,NORM_MINMAX,-1,Mat());

    //绘制直方图
    for (int i = 1;i < histSize;i++) {
        line(histImage,Point((i-1)*bin_w,hist_h - cvRound(b_hlist.at<float>(i - 1))),
             Point((i)*bin_w,hist_h-cvRound(b_hlist.at<float>(i))),Scalar(255,0,0),2,LINE_AA);
        line(histImage,Point((i-1)*bin_w,hist_h - cvRound(g_hlist.at<float>(i - 1))),
             Point((i)*bin_w,hist_h-cvRound(g_hlist.at<float>(i))),Scalar(0,255,0),2,LINE_AA);
        line(histImage,Point((i-1)*bin_w,hist_h - cvRound(r_hlist.at<float>(i - 1))),
             Point((i)*bin_w,hist_h-cvRound(r_hlist.at<float>(i))),Scalar(0,0,255),2,LINE_AA);
    }
    imshow(OUTPUT_TITLE,histImage);
    waitKey(0);
    return 0;
}

