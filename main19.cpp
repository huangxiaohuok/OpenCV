#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;

int main()
{

    Mat src,dst,gray_src,edge_image;
    src = imread("F:/Qt/OpenCV/19/OPenCV19/2.jpg");
    if(src.empty())
    {
        qDebug()<<"could not load image...\n";
        return -1;
    }

    char INPUT_WIN[] = "input image";
    char OUTPUT_WIN[] = "output image";

    namedWindow(INPUT_WIN,CV_WINDOW_AUTOSIZE);
    namedWindow(OUTPUT_WIN,CV_WINDOW_AUTOSIZE);
    imshow(INPUT_WIN,src);

    GaussianBlur(src,dst,Size(3,3),0,0);
    cvtColor(dst,gray_src,CV_BGR2GRAY);

    Laplacian(gray_src,edge_image,CV_16S,3);
    convertScaleAbs(edge_image,edge_image);

    threshold(edge_image,edge_image,0,255,THRESH_OTSU | THRESH_BINARY);
    imshow("threshold",~edge_image);
    imwrite("2-1.jpg",~edge_image);

    waitKey(0);
    return 0;
}
