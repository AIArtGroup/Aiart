#include <iostream>
#include "OpenNI.h"

// 载入OpenCV头文件
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace openni;
using namespace cv;

Mat fgMaskMOG2;                         // 前景模板，通过MOG2方法生成
Mat result;                         // 输出前景结果

Ptr<BackgroundSubtractorMOG2> pMOG2;        // MOG2 背景消除

int main( int argc, char** argv )
{
    pMOG2= createBackgroundSubtractorMOG2();

    // 初始化OpenNI环境
    OpenNI::initialize();

    // 声明并打开Device设备，我用的是Kinect。
    Device devAnyDevice;
    devAnyDevice.open(ANY_DEVICE );

    // 创建深度数据流
    VideoStream streamDepth;
    streamDepth.create( devAnyDevice, SENSOR_DEPTH );

    // 创建彩色图像数据流
    VideoStream streamColor;
    streamColor.create( devAnyDevice, SENSOR_COLOR );

    // 设置深度图像视频模式
    VideoMode mModeDepth;
    // 分辨率大小
    mModeDepth.setResolution( 640, 480 );
    // 每秒30帧
    mModeDepth.setFps( 30 );
    // 像素格式
    mModeDepth.setPixelFormat( PIXEL_FORMAT_DEPTH_1_MM );

    streamDepth.setVideoMode( mModeDepth);

    // 同样的设置彩色图像视频模式
    VideoMode mModeColor;
    mModeColor.setResolution( 640, 480 );
    mModeColor.setFps( 30 );
    mModeColor.setPixelFormat( PIXEL_FORMAT_RGB888 );

    streamColor.setVideoMode( mModeColor);

    // 图像模式注册
    if( devAnyDevice.isImageRegistrationModeSupported(
        IMAGE_REGISTRATION_DEPTH_TO_COLOR ) )
    {
        devAnyDevice.setImageRegistrationMode( IMAGE_REGISTRATION_DEPTH_TO_COLOR );
    }

    // 打开深度和图像数据流
    streamDepth.start();
    streamColor.start();

    // 创建OpenCV图像窗口
    namedWindow( "Depth Image",  CV_WINDOW_AUTOSIZE );
    namedWindow( "Color Image",  CV_WINDOW_AUTOSIZE );
    namedWindow("Frame");
    namedWindow("FG Mask MOG2");
    // 获得最大深度值
    int iMaxDepth = streamDepth.getMaxPixelValue();

    // 循环读取数据流信息并保存在VideoFrameRef中
    VideoFrameRef  frameDepth;
    VideoFrameRef  frameColor;

    while( true )
    {
        // 读取数据流
        streamDepth.readFrame( &frameDepth );
        streamColor.readFrame( &frameColor );


        // 将深度数据转换成OpenCV格式
        const cv::Mat mImageDepth( frameDepth.getHeight(), frameDepth.getWidth(), CV_16UC1, (void*)frameDepth.getData());
        // 为了让深度图像显示的更加明显一些，将CV_16UC1 ==> CV_8U格式
        cv::Mat mScaledDepth;
        mImageDepth.convertTo( mScaledDepth, CV_8U, 255.0 / iMaxDepth );
        // 显示出深度图像
        cv::imshow( "Depth Image", mScaledDepth );

        // 同样的将彩色图像数据转化成OpenCV格式
        const cv::Mat mImageRGB(frameColor.getHeight(), frameColor.getWidth(), CV_8UC3, (void*)frameColor.getData());
        // 首先将RGB格式转换为BGR格式
        cv::Mat cImageBGR;
        cv::cvtColor( mImageRGB, cImageBGR, CV_RGB2BGR );
        // 然后显示彩色图像
        cv::imshow( "Color Image", cImageBGR );

        pMOG2->apply(cImageBGR, fgMaskMOG2);                        // 获取前景掩模
        //cout<<"pMOG";
        cImageBGR.copyTo(result,fgMaskMOG2);
        result = Scalar::all(0);
        cImageBGR.copyTo(result,fgMaskMOG2);

        imshow("Frame", cImageBGR);
        imshow("FG Mask MOG2", fgMaskMOG2);
        imshow("Result", result);
        //waitKey(30);
        // 终止快捷键



        if( cv::waitKey(1) == 'q')
            break;
    }

    // 关闭数据流
    streamDepth.destroy();
    streamColor.destroy();

    // 关闭设备
    devAnyDevice.close();

    // 最后关闭OpenNI
    openni::OpenNI::shutdown();

    return 0;
}
