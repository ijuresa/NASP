#ifndef PROCESSIMAGEDATA_H
#define PROCESSIMAGEDATA_H

//Qt
#include <QDebug>

//OpenCv
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>



class ProcessImageData {
public:
    ProcessImageData(cv::Point );
    cv::Scalar calculateHsv(cv::Mat );
private:
    cv::Point clickedAt;
    int x, y;
};

#endif // PROCESSIMAGEDATA_H
