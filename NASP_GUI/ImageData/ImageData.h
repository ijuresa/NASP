#ifndef IMAGEDATA_H
#define IMAGEDATA_H

//Qt
#include <QString>
#include <QDebug>
#include <QVector>
#include <QDir>
#include <QMessageBox>

//OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//Local


class ImageData{
public:
    ImageData();
    ImageData(QString );

    //Manipulating data functions
    cv::Size getSize();

    //Testing only
    QString getOriginalPath();
    void printOriginalPath();

    cv::Mat getInputImgGrayscale() const;
    void setInputImgGrayscale(const cv::Mat &inputImgGrayscale);

    cv::Mat getInputImgShrinked() const;
    void setInputImgShrinked(const cv::Mat &inputImgShrinked);

    cv::Mat getInputImgCanny() const;
    void setInputImgCanny(const cv::Mat &inputImgCanny);

private:
    //Paths to images
    QString originalPath;
    QString shrinkedPath;

    //Scaled image (800, 640)
    cv::Size imgSize = cv::Size(800, 640);

    //Containers for images
    cv::Mat _inputImgGrayscale, _inputImgShrinked, _inputImgCanny;

};

#endif // IMAGEDATA_H
