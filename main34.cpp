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

    //1.改变背景色为黑色-目的是为后面距离变换做准备
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
    //CV_32F是float,像素是在0-1.0之间的任意值，但是它必须通过将每个像素乘以255来转换成8位来保存或显示。
    filter2D(src,imgLaplance,CV_32F,kernel,Point(-1,-1),0,BORDER_DEFAULT);
    //输出值为sharpenImg
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
    //distanceTransform方法用于计算图像中每一个非零点距离离自己最近的零点的距离，
    //distanceTransform的第一个参数为输入的图像，一般为二值图像，第二个Mat矩阵参数dst保存了每一个点与最近的零点的距离信息，
    //图像上越亮的点，代表了离零点的距离越远。
    distanceTransform(binaryImg,distImg,DIST_L1,3);
    //对输出矩阵distImg中的距离进行归一化处理
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
    //(#define CV_8U   0)CV_8U与CV_8UC1的区别：OpenCV中的类型有2个部分，深度(bit)和通道数。该系统足够灵活，可以定义多达512个通道的新类型。
    //碰巧的是，当您指定1个通道时，类型的通道组件将设置为0，这使得结果等同于简单地使用深度CV_8U。
    //distImg.convertTo(dist_8u,CV_8U);
    distImg.convertTo(dist_8u,CV_8UC1);
    vector<vector<Point>> contours;
    //CV_RETR_EXTERNAL只检测最外围轮廓，包含在外围轮廓内的内围轮廓被忽略
    //CV_CHAIN_APPROX_SIMPLE 仅保存轮廓的拐点信息，把所有轮廓拐点处的点保存入contours向量内，拐点与拐点之间直线段上的信息点不予保留
    findContours(dist_8u,contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE,Point(0,0));

    //8.标记,绘制腐蚀的每个Peak轮廓- drawContours
    //S--代表---signed int---有符号整形;U--代表--unsigned int--无符号整形;F--代表--float---------单精度浮点型
    //CV_32SC1:32位有符号单通道
    Mat markers = Mat::zeros(src.size(),CV_32SC1);
    for (size_t i = 0;i < contours.size();i++)
    {
        //thickness = -1代表绘制内部
        drawContours(markers,contours,static_cast<int>(i),
                     Scalar::all(static_cast<int>(i) + 1),-1);

    }
    circle(markers,Point(5,5),3,Scalar(255,255,255),-1);
    imshow(wateshed_win,markers * 1000);
     //9.分水岭变换 watershed
//watershed( InputArray image, InputOutputArray markers )
//第一个参数 image，必须是一个8bit 3通道彩色图像矩阵序列
//第二个参数为输入输出值，必须对第二个参数进行处理，它应该包含不同区域的轮廓，每个轮廓有一个自己唯一的编号，
//轮廓的定位可以通过Opencv中findContours方法实现，这个是执行分水岭之前的要求。
//算法会根据markers传入的轮廓作为种子（也就是所谓的注水点），对图像上其他的像素点根据分水岭算法规则进行判断，
//并对每个像素点的区域归属进行划定，直到处理完图像上所有像素点。
//而区域与区域之间的分界处的值被置为“-1”，以做区分。
//假设在每个区域最小值的位置上(也就是所谓的注水点）打一个洞并且让水以均匀的上升速率从洞中涌出，从低到高淹没整个地形。
//当处在不同的汇聚盆地中的水将要聚合在一起时，修建的大坝将阻止聚合。
//水将达到在水线上只能见到各个水坝的顶部这样一个程度。这些大坝的边界对应于分水岭的分割线。
//所以，它们是由分水岭算法提取出来的(连续的)边界线。
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
            //通过watershed(src,markers)返回的markers正负值判断测试点在目标内还是目标
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
