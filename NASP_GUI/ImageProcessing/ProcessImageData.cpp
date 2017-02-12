#include "ProcessImageData.h"

ProcessImageData::ProcessImageData(cv::Point _clickedAt) {
    this->clickedAt = _clickedAt;
    this->x = _clickedAt.x;
    this->y = _clickedAt.y;
}

cv::Scalar ProcessImageData::calculateHsv(cv::Mat img) {
    //TODO: Put in processImageData
    cv::Rect touchedRect;
    qDebug() << "Clicked at: " << x << y;

    //Calculate starting points for RECT(x, y)
    touchedRect.x = (x > 4) ?  (x - 4) : 0;
    touchedRect.y = (y > 4) ? (y -4) : 0;
    qDebug() << "RectX =" << touchedRect.x << "RectY" << touchedRect.y;

    //Calculate RectWidth
    touchedRect.width = (x + 4 < (img).cols) ? x + 4 - touchedRect.x :
                        (img).cols -touchedRect.x;
    qDebug() << "Rect width:" << touchedRect.width;

    //Calculate RectHeight
    touchedRect.height = (y + 4 < (img).rows) ? y + 4 -touchedRect.y :
                         (img).rows - touchedRect.y;
    qDebug() << "Rech height:" << touchedRect.height;

    //Get submatrix from touchedRect (8x8)
    //TODO: put in processImageData
    cv::Mat touchedRegionRgba = (img)(touchedRect);
    cv::Mat touchedRegionHsv;

    //Convert from RGB to HSV
    cv::cvtColor(touchedRegionRgba, touchedRegionHsv,
                 cv::COLOR_RGB2HSV_FULL);

    //Total value for each HSV element
    //TODO:Put in processImageData
    cv::Scalar colorHSV = cv::sum(touchedRegionHsv);

    //Get number of points from calculated rectangle
    //TODO: Put in processImageData
    int lPointCount = touchedRect.width * touchedRect.height;

    //Calculate average values by element
    for(int i = 0; i < colorHSV.rows; i ++) {
        colorHSV.val[i] /= lPointCount;
        qDebug() << "On: " << i << "=" << colorHSV.val[i];
    }

    //Release matrices
    touchedRegionHsv.release();
    touchedRegionRgba.release();

    return colorHSV;
}
