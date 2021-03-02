#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
    char input_win[] = "input image";
    char wateshed_win[] = "watershed segmentation demo";
    Mat src = imread("F:/Qt/OpenCV/34/OpenCV34/1.png");
    if(src.empty())
    {
       cout<<"could not load image...\n";
       return -1;
    }
    namedWindow(input_win,CV_WINDOW_AUTOSIZE);
    imshow(input_win,src);

    //1.改变背景色为黑色
    for (int row = 0;row<src.rows;row++)
    {
        for (int col = 0;col < src.cols;col++)
        {
            if(src.at<Vec3b>(row,col) == Vec3b(255,255,255))
            {
                src.at<Vec3b>(row,col)[0] = 0;
                src.at<Vec3b>(row,col)[1] = 0;
                src.at<Vec3b>(row,col)[2] = 0;
            }
        }
    }
    namedWindow("black background",CV_WINDOW_AUTOSIZE);
    imshow("black background",src);
    //2.使用filter2D与拉普拉斯算子实现图像对比度提高，sharp
    Mat kernel = (Mat_<float>(3,3)<<1,1,1,1,-8,1,1,1,1);
    Mat imgLaplance;
    Mat sharpenImg = src;
    filter2D(src,imgLaplance,CV_32F,kernel,Point(-1,-1),0,BORDER_DEFAULT);
    src.convertTo(sharpenImg,CV_32F);
    Mat resultImg = sharpenImg - imgLaplance;

    resultImg.convertTo(resultImg,CV_8UC3);
    imgLaplance.convertTo(imgLaplance,CV_8UC3);
    imshow("sharpen image",resultImg);
    src = resultImg;

    //3转为二值图像通过threshold
    Mat binaryImg;
    cvtColor(src,resultImg,CV_BGR2GRAY);
    threshold(resultImg,binaryImg,40,255,THRESH_BINARY | THRESH_OTSU);
    imshow("binary image",binaryImg);

    //4.距离变换,对距离变换结果进行归一化到[0~1]之间
    Mat distImg;
    distanceTransform(binaryImg,distImg,DIST_L1,3,5);
    normalize(distImg,distImg,0,1,NORM_MINMAX);
    imshow("distance result",distImg);

    //5.使用阈值，再次二值化
    threshold(distImg,distImg,0.4,1,THRESH_BINARY);

    //6.腐蚀得到每个Peak - erode
    Mat k1 = Mat::ones(13,13,CV_8UC1);
    erode(distImg,distImg,k1,Point(-1,-1));
    imshow("distance binary imge",distImg);

    //7.标记,发现轮廓 – findContours
    Mat dist_8u;
    distImg.convertTo(dist_8u,CV_8U);
    vector<vector<Point>> contours;
    findContours(dist_8u,contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE,Point(0,0));

    //8.创建标记,绘制轮廓- drawContours
    Mat markers = Mat::zeros(src.size(),CV_32SC1);
    for (size_t i = 0;i < contours.size();i++)
    {
        drawContours(markers,contours,static_cast<int>(i),
                     Scalar::all(static_cast<int>(i) + 1),-1);

    }
    circle(markers,Point(5,5),3,Scalar(255,255,255),-1);
    imshow("my markers",markers * 1000);
     //9.分水岭变换 watershed
    watershed(src,markers);
    Mat mark = Mat::zeros(markers.size(),CV_8UC1);
    markers.convertTo(mark,CV_8UC1);
    bitwise_not(mark,mark,Mat());
    imshow("watershed image",mark);

    //10.产生随机颜色
    vector<Vec3b> colors;
    for (size_t i = 0;i < contours.size();i++)
    {
        int r = theRNG().uniform(0,255);
        int g = theRNG().uniform(0,255);
        int b = theRNG().uniform(0,255);
        colors.push_back(Vec3b((uchar)b,(uchar)g,(uchar)r));
    }
    //11.填充颜色
    Mat dst = Mat::zeros(markers.size(),CV_8UC3);
    for (int row = 0;row < markers.rows;row++)
    {
        for (int col = 0;col <markers.cols;col++)
        {
            int index = markers.at<int>(row,col);
            if(index > 0 && index <= static_cast<int>(contours.size()))
                dst.at<Vec3b>(row,col) = colors[index - 1];
            else
            {
                dst.at<Vec3b>(row,col) = Vec3b(0,0,0);
            }
        }
    }
    imshow("Final Result",dst);

    waitKey(0);
    return 0;
}
