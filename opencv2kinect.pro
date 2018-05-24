TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
INCLUDEPATH += "/home/ubuntu/Downloads/OpenNI-Linux-x64-2.2/Include"

INCLUDEPATH += /home/ubuntu/Downloads/environment/opencv-3.4.1-tbb/include \ /home/ubuntu/Downloads/environment/opencv-3.4.1-tbb/include/opencv \ /home/ubuntu/Downloads/environment/opencv-3.4.1-tbb/include/opencv2

#LIBS += -L"/home/ubuntu/Downloads/OpenNI-Linux-x64-2.2/Samples/Bin" -lMWClosestPoint -lOpenNI2

#LIBS += -L"/home/ubuntu/QSimpleViewer/Bin/x64-Release" -lOpenNI2
LIBS += -L"/home/ubuntu/QMultiDepthViewer/Bin/x64-Release" -lOpenNI2

LIBS += -L"/usr/lib/x86_64-linux-gnu" -lglut

LIBS += -L"/usr/lib/nvidia-384" -lGL

LIBS += -L"/home/ubuntu/Downloads/OpenNI-Linux-x64-2.2/Samples/SimpleViewer/Bin/x64-Release/OpenNI2/Drivers" -lfreenect2-openni2

LIBS += -lfreenect2

LIBS        += /home/ubuntu/Downloads/environment/opencv-3.4.1-tbb/build/lib/libopencv_img_hash.so \
/home/ubuntu/Downloads/environment/opencv-3.4.1-tbb/build/lib/libopencv_img_hash.so.3.4 \
/home/ubuntu/Downloads/environment/opencv-3.4.1-tbb/build/lib/libopencv_img_hash.so.3.4.1\
/home/ubuntu/Downloads/environment/opencv-3.4.1-tbb/build/lib/libopencv_world.so \
/home/ubuntu/Downloads/environment/opencv-3.4.1-tbb/build/lib/libopencv_world.so.3.4\
/home/ubuntu/Downloads/environment/opencv-3.4.1-tbb/build/lib/libopencv_world.so.3.4.1

HEADERS += \
    opencv2kinect.h \
    sharedmatting.h
