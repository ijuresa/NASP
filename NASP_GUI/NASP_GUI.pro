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

INCLUDEPATH += C:/Users/Adela/Documents/GitHub/NASP/opencv/build/include/

win32:CONFIG(release, debug|release): LIBS += -LC:/Users/Adela/Documents/GitHub/NASP/opencv/build/x64/vc12/lib \
    -lopencv_calib3d2413 \
    -lopencv_contrib2413 \
    -lopencv_core2413 \
    -lopencv_features2d2413 \
    -lopencv_flann2413 \
    -lopencv_gpu2413 \
    -lopencv_highgui2413 \
    -lopencv_imgproc2413 \
    -lopencv_legacy2413 \
    -lopencv_ml2413 \
    -lopencv_nonfree2413 \
    -lopencv_objdetect2413 \
    -lopencv_photo2413 \
    -lopencv_ocl2413 \
    -lopencv_stitching2413 \
    -lopencv_superres2413 \
    -lopencv_ts2413 \
    -lopencv_video2413 \
    -lopencv_videostab2413

else:win32:CONFIG(debug, debug|release): LIBS += -LC:/Users/Adela/Documents/GitHub/NASP/opencv/build/x64/vc12/lib \
    -lopencv_calib3d2413d \
    -lopencv_contrib2413d \
    -lopencv_core2413d \
    -lopencv_features2d2413d \
    -lopencv_flann2413d \
    -lopencv_gpu2413d \
    -lopencv_highgui2413d \
    -lopencv_imgproc2413d \
    -lopencv_legacy2413d \
    -lopencv_ml2413d \
    -lopencv_nonfree2413d \
    -lopencv_objdetect2413d \
    -lopencv_photo2413d \
    -lopencv_ocl2413d \
    -lopencv_stitching2413d \
    -lopencv_superres2413d \
    -lopencv_ts2413d \
    -lopencv_video2413d \
    -lopencv_videostab2413d




