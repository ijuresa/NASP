#ifndef COLORBLOBDETECTOR_H
#define COLORBLOBDETECTOR_H

//Qt
#include <QVector>
#include <QDebug>

//OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

//Local


class ColorBlobDetector {
public:
    ColorBlobDetector();
    ColorBlobDetector(ColorBlobDetector *, cv::Point );

    void setPoint(cv::Point );
    void setHsvColor(cv::Scalar ,int );
    void processImage(cv::Mat ,int );
    void saveAll();
    bool isContour(cv::Point , cv::vector<cv::Point> );


    cv::Scalar lowerBound() const;
    void setLowerBound(const cv::Scalar &lowerBound);

    cv::Scalar upperBound() const;
    void setUpperBound(const cv::Scalar &upperBound);

    cv::Point getClickedAt() const;
    void setClickedAt(const cv::Point &value);

    cv::Scalar getHsvColor() const;

    cv::Scalar getBlueColor() const;
    void setBlueColor(const cv::Scalar &value);

    cv::Scalar getGreenColor() const;
    void setGreenColor(const cv::Scalar &value);

    cv::Scalar getYellowColor() const;
    void setYellowColor(const cv::Scalar &value);

    cv::Scalar getOrangeColor() const;
    void setOrangeColor(const cv::Scalar &value);

    cv::Scalar getRedColor() const;
    void setRedColor(const cv::Scalar &value);

private:
    //Used for HSV color space
    cv::Scalar mLowerBound;
    cv::Scalar mUpperBound;

    cv::Mat mMask;
    cv::Mat mHsvMat;
    cv::Mat mDilatedMask;
    cv::vector<cv::Vec4i> mHierarchy;

    cv::Scalar hsvColor;

    //For later picture localization
    int it;

    //Colors
    cv::Scalar blueColor;   //front
    cv::Scalar greenColor;  //top
    cv::Scalar yellowColor; //right
    cv::Scalar orangeColor; //left
    cv::Scalar redColor;    //back

    //Contours
    cv::vector<cv::Point> topContour;   //greenColor
    cv::vector<cv::Point> frontContour; //blueColor
    cv::vector<cv::Point> leftContour;  //orangeColor
    cv::vector<cv::Point> rightContour; //yellowColor
    cv::vector<cv::Point> backContour;  //redColor

    //Clicked point
    cv::Point clickedAt;

    //Color radius for range checking in HSV space
    cv::Scalar mColorRadius = cv::Scalar(20, 25, 25, 0);

    cv::vector<cv::vector<cv::Point>> mContours;
};

#endif // COLORBLOBDETECTOR_H
