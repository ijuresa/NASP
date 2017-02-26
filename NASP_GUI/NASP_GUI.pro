#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T14:10:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NASP_GUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version
# of Qt.
# disables all the APIs deprecated before Qt 6.0.0
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000


SOURCES += main.cpp\
    ImageProcessing/ColorBlobDetector.cpp \
    ImageData/ImageData.cpp \
    ImageData/ImageDataHolder.cpp \
    GUI/MainWindow.cpp \
    ImageProcessing/ProcessImageData.cpp

HEADERS  += \
    ImageProcessing/ColorBlobDetector.h \
    ImageData/ImageData.h \
    ImageData/ImageDataHolder.h \
    GUI/MainWindow.h \
    ImageProcessing/ProcessImageData.h

FORMS    += mainwindow.ui

INCLUDEPATH += E:/opencv_mingw/install/include

LIBS += -LE:\\opencv_mingw\\bin \
    libopencv_core320 \
    libopencv_highgui320 \
    libopencv_imgproc320 \
    libopencv_features2d320 \
    libopencv_calib3d320 \
    libopencv_features2d320 \
    libopencv_flann320 \
    libopencv_imgcodecs320 \
    libopencv_ml320 \
    libopencv_objdetect320 \
    libopencv_photo320 \
    libopencv_shape320 \
    libopencv_stitching320 \
    libopencv_superres320 \
    libopencv_video320 \
    libopencv_videoio320 \
    libopencv_videostab320



