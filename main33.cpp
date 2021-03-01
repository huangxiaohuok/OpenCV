#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;
int main()
{
    const int r = 100;
    //CV_8UC1 是指一个8位无符号整型单通道矩阵
    Mat src = Mat::zeros(r * 4,r * 4,CV_8UC1);

    vector<Point2f> vert(6);
    vert[0] = Point(3 * r /2,static_cast<int>(1.34 * r));
    vert[1] = Point(1 * r,2 * r);
    vert[2] = Point(3 * r /2,static_cast<int>(2.866 * r));
    vert[3] = Point(5 * r /2,static_cast<int>(2.866 * r));
    vert[4] = Point(3 * r,2 * r);
    vert[5] = Point(5 * r /2,static_cast<int>(1.34 * r));

    //画六边形
    for(int i = 0;i < 6;i++)
    {
        line(src,vert[i],vert[(i+1)%6],Scalar(255),3,8,0);
    }

    vector<vector<Point>> contours;
    vector<Vec4i> hierachy;
    Mat csrc;
    src.copyTo(csrc);
    findContours(csrc,contours,hierachy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));
    //CV_32FC1是指一个32位浮点型单通矩阵
    Mat raw_dist = Mat::zeros(csrc.size(),CV_32FC1);
//    pointPolygonTest(
//    InputArray  contour,// 输入的轮廓
//    Point2f  pt, // 测试点
//    bool  measureDist // 是否返回距离值，如果是false，1表示在内面，0表示在边界上，-1表示在外部，true返回实际距离
//    )
//    返回数据是double类型
    for (int row = 0;row < raw_dist.rows;row++)
    {
        for (int col = 0;col <raw_dist.cols;col++)
        {
            //点多边形测试,返回测试点Point2f与轮廓contours[0]的距离
            double dist = pointPolygonTest(contours[0],
                    Point2f(static_cast<float>(col),static_cast<float>(row)),true);
            //把测试点Point2f与轮廓contours[0]的距离画在矩阵raw_dist上
            raw_dist.at<float>(row,col) = static_cast<float>(dist);
        }
    }
    double minValue,maxValue;
    //返回最小值及其位置，返回最大值及其位置
    minMaxLoc(raw_dist,&minValue,&maxValue,0,0,Mat());
    Mat drawImg = Mat::zeros(src.size(),CV_8UC3);
    for (int row = 0;row < drawImg.rows;row++)
    {
        for (int col = 0;col <drawImg.cols;col++)
        {
            float dist = raw_dist.at<float>(row,col);
            //如果dist > 0测试点在多边形内
            //如果dist < 0测试点在多边形外
            //如果dist = 0测试点在多边形上
            if(dist > 0)
            {
                //Vec3b color描述一种RGB颜色。color[0]=0,B分量;color[1]=0,G分量;color[2]=255,R分量
                drawImg.at<Vec3b>(row,col)[0] = (uchar)(abs(1.0 - (dist/maxValue)) * 255);
            }
            else if(dist < 0)
            {
                drawImg.at<Vec3b>(row,col)[2] = (uchar)(abs(1.0 - (dist/minValue)) * 255);

            }
            //dist = 0
            else
            {
                drawImg.at<Vec3b>(row,col)[0] = (uchar)(abs(255-dist));
                drawImg.at<Vec3b>(row,col)[1] = (uchar)(abs(255-dist));
                drawImg.at<Vec3b>(row,col)[2] = (uchar)(abs(255-dist));
            }
        }
    }

    namedWindow("input image",CV_WINDOW_AUTOSIZE);
    namedWindow("output image",CV_WINDOW_AUTOSIZE);

    imshow("input image",src);
    imshow("output image",drawImg);

    waitKey(0);
    return 0;
}
