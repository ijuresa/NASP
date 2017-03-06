#include "ColorBlobDetector.h"

ColorBlobDetector::ColorBlobDetector() { }

ColorBlobDetector::ColorBlobDetector(ColorBlobDetector *local, cv::Point
                                     _clickedAt) {
    this->clickedAt = _clickedAt;
}

void ColorBlobDetector::setHsvColor(cv::Scalar hsvColor, int it) {
    this->it = it;
    this->hsvColor = hsvColor;
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

/**
 * @brief ColorBlobDetector::isContour
 *          Check if clickedPoint is inside desired contour
 *
 * @param _checkMe clickedPoint
 * @param _lContour Contour to be checked
 * @return true(1) When Point is inside contour
 */
bool ColorBlobDetector::isContour(cv::Point _checkMe,
                                 std::vector<cv::Point> _lContour) {

    double r = cv::pointPolygonTest(_lContour, _checkMe, false);
    qDebug() << "r = " << r;

    //Return only when r == 1 - then Point is inside contour
    //If it's not then it is r == -1
    return r == 1;
}

void ColorBlobDetector::processImage(cv::Mat _inputImage, int it) {
    double minContourArea = 0.1;

    cv::cvtColor(_inputImage, mHsvMat, cv::COLOR_RGB2HSV_FULL);

    cv::inRange(mHsvMat, mLowerBound, mUpperBound, mMask);

    cv::dilate(mMask, mDilatedMask, cv::Mat());

    std::vector<std::vector<cv::Point>> lContours;
    cv::findContours(mDilatedMask, lContours, mHierarchy, cv::RETR_TREE,
                     cv::CHAIN_APPROX_SIMPLE);

    qDebug() << "Number of contours" << lContours.size();
    std::vector<std::vector<cv::Point>>::iterator lEach = lContours.begin();

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
    bool isInside = false;
    for(int i = 0; i < lContours.size(); i ++) {
        if((cv::contourArea(lContours[i]) > minContourArea * maxArea)) {
            if(isInside = isContour(clickedAt, lContours[i])) {
                mContours.push_back(lContours[i]);
                qDebug() << "Contours pushed: " << cv::contourArea(lContours[i]);
            }
        }
    }

    //Interpolate
    std::vector<cv::Point> approxRectangle;
    double d = 0;
    do {
        d = d + 1;
        cv::approxPolyDP(mContours[0], approxRectangle, d, true);
        qDebug() << approxRectangle.size() << " " << d;
    } while (approxRectangle.size() > 4);
    mContours.push_back(approxRectangle);

    cv::RNG rng(12345);
    cv::Mat drawing = cv::Mat::zeros(mDilatedMask.size(), CV_8UC3);
    for(int i = 0; i < mContours.size(); i ++) {
        cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255),
                              rng.uniform(0,255) );
        cv::drawContours(drawing, mContours, i, color, 2, 8, mHierarchy,
                         0, cv::Point());

    }

    double width = 6;
    double distance = 50;
    double contourArea = cv::contourArea(approxRectangle);
    if(!isCalculated) {
        //Width     6.00  cm
        //Distance  50.00 cm



        //setFocalLenght((contourArea * distance) / width);
        setFocalLenght(18887.5);
        isCalculated = true;
    }


    //qDebug() << "ContourArea = " << contourArea;
    qDebug() << "FocalLenght = " << getFocalLenght();

    setDistanceToCamera(width, getFocalLenght(), contourArea);

    qDebug() << "Distance to Camera, computed = " << getDistanceToCamera();

    cv::namedWindow("Contours", CV_WINDOW_AUTOSIZE);
    cv::imshow("Contours", drawing);
}

void ColorBlobDetector::setPoint(cv::Point _point) {
    this->clickedAt = _point;
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

cv::Point ColorBlobDetector::getClickedAt() const
{
    return clickedAt;
}

void ColorBlobDetector::setClickedAt(const cv::Point &value)
{
    clickedAt = value;
}

cv::Scalar ColorBlobDetector::getHsvColor() const
{
    return hsvColor;
}

cv::Scalar ColorBlobDetector::getBlueColor() const
{
    return blueColor;
}

void ColorBlobDetector::setBlueColor(const cv::Scalar &value)
{
    blueColor = value;
}

cv::Scalar ColorBlobDetector::getGreenColor() const
{
    return greenColor;
}

void ColorBlobDetector::setGreenColor(const cv::Scalar &value)
{
    greenColor = value;
}

cv::Scalar ColorBlobDetector::getYellowColor() const
{
    return yellowColor;
}

void ColorBlobDetector::setYellowColor(const cv::Scalar &value)
{
    yellowColor = value;
}

cv::Scalar ColorBlobDetector::getOrangeColor() const
{
    return orangeColor;
}

void ColorBlobDetector::setOrangeColor(const cv::Scalar &value)
{
    orangeColor = value;
}

cv::Scalar ColorBlobDetector::getRedColor() const
{
    return redColor;
}

void ColorBlobDetector::setRedColor(const cv::Scalar &value)
{
    redColor = value;
}

double ColorBlobDetector::getDistanceToCamera() const
{
    return distanceToCamera;
}

void ColorBlobDetector::setDistanceToCamera(double knownWidth,
                                            double focalLenght,
                                            double perceivedWidth) {

    distanceToCamera = (knownWidth * focalLenght) / perceivedWidth;
}

double ColorBlobDetector::getFocalLenght() const
{
    return focalLenght;
}

void ColorBlobDetector::setFocalLenght(double value)
{
    focalLenght = value;
}
