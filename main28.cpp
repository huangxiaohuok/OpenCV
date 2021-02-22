#include "opencv2/opencv.hpp"
#include <QDebug>

using namespace cv;

Mat src,temp,dst;
//TM_SQDIFF = 0,该方法使用平方差进行匹配，因此最佳的匹配结果在结果为0处，值越大匹配结果越差
//TM_SQDIFF_NORMED = 1,该方法使用归一化的平方差进行匹配，最佳匹配也在结果为0处。
//TM_CCORR = 2,相关性匹配方法，该方法使用源图像与模板图像的卷积结果进行匹配，因此，最佳匹配位置在值最大处，值越小匹配结果越差。
//TM_CCORR_NORMED =3,归一化的相关性匹配方法，与相关性匹配方法类似，最佳匹配位置也是在值最大处。
//TM_CCOEFF = 4,相关性系数匹配方法，该方法使用源图像与其均值的差、模板与其均值的差二者之间的相关性进行匹配，最佳匹配结果在值等于1处，最差匹配结果在值等于-1处，值等于0直接表示二者不相关。
//TM_CCOEFF_NORMED = 5,归一化的相关性系数匹配方法，正值表示匹配的结果较好，负值则表示匹配的效果较差，也是值越大，匹配效果也好。
int match_method = TM_SQDIFF;//TM_SQDIFF = 0;
int max_track = 5;//OpenCV中提供了六种常见的匹配算法
const char* INPUT_T = "input image";
const char* OUTPUT_T = "result image";
const char* match_t = "template match-demo";
void Match_Demo(int,void*);

int main()
{
    //待检测图像
    src = imread("F:/Qt/OpenCV/28/OPenCV28/1.jpg");
    //模板图像
    temp = imread("F:/Qt/OpenCV/28/OPenCV28/2.jpg");
    if(src.empty() || temp.empty())
    {
        qDebug()<<"could not load image...\n";
        return -1;
    }

    namedWindow(INPUT_T,CV_WINDOW_AUTOSIZE);
    namedWindow(OUTPUT_T,CV_WINDOW_AUTOSIZE);
    namedWindow(match_t,CV_WINDOW_AUTOSIZE);
    imshow(INPUT_T,temp);//显示模板图像
    const char* trackbar_title = "Match Algo Type:";
    //把createTrackbar创建在result image窗口中
    createTrackbar(trackbar_title,OUTPUT_T,&match_method,max_track,Match_Demo);
    Match_Demo(0,0);

    waitKey(0);
    return 0;
}
void Match_Demo(int,void*)
{

    int width = src.cols - temp.cols + 1;
    int height = src.rows - temp.rows + 1;
    Mat result(height,width,CV_32FC1);
    /*输出结果(result)，必须是单通道32位浮点数。
    假设源图像WxH,模板图像wxh,则结果必须为W-w+1, H-h+1的大小。
    result数据的含义,模板匹配函数cvMatchTemplate依次计算模板与待测图片的重叠区域的相似度，并将结果存入映射图像result当中，也就是说result图像中的每一个点的值代表了一次相似度比较结果。
   如何从result中获得最佳匹配区域使用函数cvMinMaxLoc(result,&min_val,&max_val,&min_loc,&max_loc,NULL);
   从result中提取最大值（相似度最高）以及最大值的位置（即在result中该最大值max_val的坐标位置max_loc，即模板滑行时左上角的坐标，类似于图中的坐标（x,y）。由此得到：rect=cvRect(max_loc.x,max_loc.y,tmp->width,tmp->height); rect表示最佳的匹配的矩形区域。
    */
    matchTemplate(src,temp,result,match_method,Mat());
    normalize(result,result,0,1,NORM_MINMAX,-1,Mat());//归一化

    Point minLoc;//最小值的位置
    Point maxLoc;//最大值的位置
    double min,max;
    src.copyTo(dst);
    Point temLoc;
//    参数1：InputArray类型的src，输入单通道数组（图像）。
//    参数2：double*类型的minVal，返回最小值的指针。若无须返回，此值置为NULL。
//    参数3：double*类型的maxVal，返回最大值的指针。若无须返回，此值置为NULL。
//    参数4：Point*类型的minLoc，返回最小位置的指针（二维情况下）。若无须返回，此值置为NULL。
//    参数5：Point*类型的maxLoc，返回最大位置的指针（二维情况下）。若无须返回，此值置为NULL。
//    参数6：InputArray类型的mask，用于选择子阵列的可选掩膜。
    minMaxLoc(result,&min,&max,&minLoc,&maxLoc);
    if(match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
        temLoc = minLoc;
    else
        temLoc = maxLoc;
    //绘制矩形
    rectangle(dst,Rect(temLoc.x,temLoc.y,temp.cols,temp.rows),Scalar(0,0,255),2,8);
    rectangle(result,Rect(temLoc.x,temLoc.y,temp.cols,temp.rows),Scalar(0,0,255),2,8);

    imshow(OUTPUT_T,result);
    imshow(match_t,dst);
}
