#include "ImageData.h"

ImageData::ImageData() { }

ImageData::ImageData(QString _input) {
    this->originalPath = _input;
}

QString ImageData::getOriginalPath() {
    return originalPath;
}

cv::Mat ImageData::getInputImgGrayscale() const {
    return _inputImgGrayscale;
}

void ImageData::setInputImgGrayscale(const cv::Mat &inputImgGrayscale) {
    _inputImgGrayscale = inputImgGrayscale;
}

cv::Mat ImageData::getInputImgShrinked() const {
    return _inputImgShrinked;
}

void ImageData::setInputImgShrinked(const cv::Mat &inputImgShrinked)
{
    _inputImgShrinked = inputImgShrinked;
}

cv::Mat ImageData::getInputImgCanny() const {
    return _inputImgCanny;
}

void ImageData::setInputImgCanny(const cv::Mat &inputImgCanny) {
    _inputImgCanny = inputImgCanny;
}

cv::Size ImageData::getSize() {
    return imgSize;
}

void ImageData::printOriginalPath() {
    qDebug() << "Original Path = " << originalPath;
}
