#include "ColorBlobDetector.h"

ColorBlobDetector::ColorBlobDetector() { }

ColorBlobDetector::ColorBlobDetector(ColorBlobDetector *local) { }

void ColorBlobDetector::setHsvColor(cv::Scalar hsvColor, int it) {
    this->it;
    qDebug() << "Entered setHsvColor";

    double minH = (hsvColor.val[0] >= mColorRadius[0]) ? hsvColor.val[0] -
            mColorRadius.val[0] : 0;

    double maxH = (hsvColor.val[0] <= 255) ? hsvColor.val[0] +
            mColorRadius.val[0] : 255;

    //Set bounds
    mLowerBound.val[0] = minH;
    qDebug() << "mLowerBound val[0]" << mLowerBound.val[0];

    mUpperBound.val[0] = maxH;
    qDebug() << "mUpperBound val[0]" << mUpperBound.val[0];

    mLowerBound.val[1] = hsvColor.val[1] - mColorRadius.val[1];
    qDebug() << "mLowerBound val[1]" << mLowerBound.val[1];

    mUpperBound.val[1] = hsvColor.val[1] + mColorRadius.val[1];
    qDebug() << "mUpperBound val[1]" << mUpperBound.val[1];

    mLowerBound.val[2] = hsvColor.val[2] - mColorRadius.val[2];
    qDebug() << "mLowerBound val[2]" << mLowerBound.val[2];

    mUpperBound.val[2] = hsvColor.val[2] + mColorRadius.val[2];
    qDebug() << "mUpperBound val[2]" << mUpperBound.val[2];

    mLowerBound.val[3] = 0;  
    mLowerBound.val[3] = 255;

    qDebug() << "Exited setHsvColor";
}

void ColorBlobDetector::processImage(cv::Mat _inputImage, int it) {
    double minContourArea = 0.1;

    cv::cvtColor(_inputImage, mHsvMat, cv::COLOR_RGB2HSV_FULL);

    cv::inRange(mHsvMat, mLowerBound, mUpperBound, mMask);

    cv::dilate(mMask, mDilatedMask, cv::Mat());

    cv::vector<cv::vector<cv::Point>> lContours;
    cv::findContours(mDilatedMask, lContours, mHierarchy, cv::RETR_EXTERNAL,
                     cv::CHAIN_APPROX_SIMPLE);

    qDebug() << "Number of contours" << lContours.size();
    cv::vector<cv::vector<cv::Point>>::iterator lEach = lContours.begin();

    //Find max contourArea
    double maxArea = 0;
    for(int i = 0; i < lContours.size(); i ++) {
        double _area = cv::contourArea(lContours[i]);
        if(_area > maxArea) {
            maxArea = _area;
            qDebug() << "MaxArea = " << maxArea;
        }
    }

    mContours.clear();
    lEach = mContours.begin();
    for(int i = 0; i < lContours.size(); i ++) {
        if(cv::contourArea(lContours[i]) > minContourArea * maxArea) {
            mContours.push_back(lContours[i]);
            qDebug() << "Contours pushed: " << cv::contourArea(lContours[i]);
        }
    }

    cv::RNG rng(12345);
    cv::Mat drawing = cv::Mat::zeros(mDilatedMask.size(), CV_8UC3);
    for(int i = 0; i < mContours.size(); i ++) {
        cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255),
                              rng.uniform(0,255) );
        cv::drawContours(drawing, mContours, i, color, 2, 8, mHierarchy,
                         0, cv::Point());
    }
    cv::namedWindow("Contours", CV_WINDOW_AUTOSIZE);
    cv::imshow("Contours", drawing);

}

cv::Scalar ColorBlobDetector::lowerBound() const {
    return mLowerBound;
}

void ColorBlobDetector::setLowerBound(const cv::Scalar &lowerBound) {
    mLowerBound = lowerBound;
}

cv::Scalar ColorBlobDetector::upperBound() const {
    return mUpperBound;
}

void ColorBlobDetector::setUpperBound(const cv::Scalar &upperBound) {
    mUpperBound = upperBound;
}
