#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;
using namespace std;

Mat src,dst,map_x,map_y;
int index = 0;
void update_map(void);
int main()
{

    src = imread("F:/Qt/OpenCV/23/OPenCV23/1.JPG");
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

    map_x.create(src.size(),CV_32FC1);
    map_y.create(src.size(),CV_32FC1);

    int c;
    while(true)
    {
        c = waitKey(500);
        if((char) c == 27)
            break;
        index = c % 4;
        update_map();
        remap(src,dst,map_x,map_y,INTER_LINEAR,BORDER_CONSTANT,Scalar(0,255,255));
        imshow(OUTPUT_TITLE,dst);
    }
    return 0;
}
void update_map(void)
{
    for (int row = 0;row <src.rows;row++)
    {
        for (int col = 0;col < src.cols;col++)
        {
            switch (index)
            {
            case 0:
                if(col > (src.cols * 0.25) && col < (src.cols * 0.75) && row > (src.rows * 0.25) && row < (src.rows * 0.75))
                {
                    map_x.at<float>(row,col) = 2 * (col - (src.cols*0.25) + 0.5);
                    map_x.at<float>(row,col) = 2 * (col - (src.cols*0.25) + 0.5);
                }
                else
                {
                     map_x.at<float>(row,col) = 0;
                     map_y.at<float>(row,col) = 0;
                }
                break;
            case 1:
                map_x.at<float>(row,col) = (src.cols - col -1);
                map_y.at<float>(row,col) = row;
                break;
            case 2:
                map_x.at<float>(row,col) = col;
                map_y.at<float>(row,col) = (src.rows - row -1);
                break;
            case 3:
                map_x.at<float>(row,col) = (src.cols - col -1);
                map_y.at<float>(row,col) = (src.rows - row -1);
                break;
            }
        }
    }
}
