#include "customimage.h"

CustomImage::CustomImage(QString _input) {
    this->originalPath = _input;
}

QString CustomImage::getOriginalPath() {
    return originalPath;
}

cv::Mat CustomImage::getInputImgGrayscale() const {
    return _inputImgGrayscale;
}

void CustomImage::setInputImgGrayscale(const cv::Mat &inputImgGrayscale) {
    _inputImgGrayscale = inputImgGrayscale;
}

cv::Mat CustomImage::getInputImgShrinked() const {
    return _inputImgShrinked;
}

void CustomImage::setInputImgShrinked(const cv::Mat &inputImgShrinked)
{
    _inputImgShrinked = inputImgShrinked;
}

cv::Mat CustomImage::getInputImgCanny() const {
    return _inputImgCanny;
}

void CustomImage::setInputImgCanny(const cv::Mat &inputImgCanny) {
    _inputImgCanny = inputImgCanny;
}

cv::Size CustomImage::getSize() {
    return imgSize;
}

void CustomImage::printOriginalPath() {

    qDebug() << "Original Path = " << originalPath;
}
