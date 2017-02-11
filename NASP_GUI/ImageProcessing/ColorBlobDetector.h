#ifndef COLORBLOBDETECTOR_H
#define COLORBLOBDETECTOR_H

//Qt
#include <QVector>
#include <QDebug>

//OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class ColorBlobDetector {
public:
    ColorBlobDetector();
    ColorBlobDetector(ColorBlobDetector *);
    void setHsvColor(cv::Scalar ,int );
    void processImage(cv::Mat ,int );
    void saveAll();


    cv::Scalar lowerBound() const;
    void setLowerBound(const cv::Scalar &lowerBound);

    cv::Scalar upperBound() const;
    void setUpperBound(const cv::Scalar &upperBound);

private:
    //Used for HSV color space
    cv::Scalar mLowerBound;
    cv::Scalar mUpperBound;

    cv::Mat mSpectrum;
    cv::Mat mMask;
    cv::Mat mHsvMat;
    cv::Mat mDilatedMask;
    cv::vector<cv::Vec4i> mHierarchy;

    //For later picture localization
    int it;

    //Color radius for range checking in HSV space
    cv::Scalar mColorRadius = cv::Scalar(20, 25, 25, 0);

    cv::vector<cv::vector<cv::Point>> mContours;
};

#endif // COLORBLOBDETECTOR_H
