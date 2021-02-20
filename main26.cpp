#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;
using namespace std;

string convertToString(double d);
int main()
{

    Mat base,test1,test2;
    Mat hsvbase,hsvtest1,hsvtest2;
    base = imread("F:/Qt/OpenCV/26/OPenCV26/1.jpg");
    test1 = imread("F:/Qt/OpenCV/26/OPenCV26/2.jpg");
    test2 = imread("F:/Qt/OpenCV/26/OPenCV26/3.jpg");
    if(base.empty() || test1.empty() || test2.empty())
    {
        qDebug()<<"could not load image...\n";
        return -1;
    }
    cvtColor(base,hsvbase,CV_BGR2HSV);//HSV：色度、饱和度、亮度
    cvtColor(test1,hsvtest1,CV_BGR2HSV);
    cvtColor(test2,hsvtest2,CV_BGR2HSV);

    int h_bins = 50; //灰度等级
    int s_bins = 60;
    int histSize[] = {h_bins,s_bins};

    float h_ranges[] = {0,180};//色度范围
    float s_ranges[] = {0,256};//饱和度范围
    const float *ranges[] = {h_ranges,s_ranges};

    //使用0通道和1通道
    int channels[] = {0,1};
    MatND hist_base;
    MatND hist_test1;
    MatND hist_test2;

    calcHist(&hsvbase,1,channels,Mat(),hist_base,2,histSize,ranges,true,false);
    normalize(hist_base,hist_base,0,1,NORM_MINMAX,-1,Mat());

    calcHist(&hsvtest1,1,channels,Mat(),hist_test1,2,histSize,ranges,true,false);
    normalize(hist_test1,hist_test1,0,1,NORM_MINMAX,-1,Mat());

    calcHist(&hsvtest2,1,channels,Mat(),hist_test2,2,histSize,ranges,true,false);
    normalize(hist_test2,hist_test2,0,1,NORM_MINMAX,-1,Mat());

    double basebase = compareHist(hist_base,hist_base,CV_COMP_BHATTACHARYYA);//CV_COMP_INTERSECT
    double basetest1 = compareHist(hist_base,hist_test1,CV_COMP_BHATTACHARYYA);
    double basetest2 = compareHist(hist_base,hist_test2,CV_COMP_BHATTACHARYYA);
    double test1test2 = compareHist(hist_test1,hist_test2,CV_COMP_BHATTACHARYYA);

    Mat test12;
    test2.copyTo(test12);

    putText(base,convertToString(basebase),Point(50,50),
            CV_FONT_HERSHEY_COMPLEX,1,Scalar(0,0,255),2,LINE_AA);
    putText(test1,convertToString(basetest1),Point(50,50),
            CV_FONT_HERSHEY_COMPLEX,1,Scalar(0,0,255),2,LINE_AA);
    putText(test2,convertToString(basetest2),Point(50,50),
            CV_FONT_HERSHEY_COMPLEX,1,Scalar(0,0,255),2,LINE_AA);
    putText(test12,convertToString(test1test2),Point(50,50),
            CV_FONT_HERSHEY_COMPLEX,1,Scalar(0,0,255),2,LINE_AA);

    namedWindow("base",CV_WINDOW_AUTOSIZE);
    namedWindow("test1",CV_WINDOW_AUTOSIZE);
    namedWindow("test2",CV_WINDOW_AUTOSIZE);
    imshow("base",base);
    imshow("test1",test1);
    imshow("test2",test2);
    imshow("test12",test12);

    waitKey(0);
    return 0;
}
string convertToString(double d)
{
    ostringstream os;
    if(os<<d)
        return os.str();
    return "invalid conversion";
}
