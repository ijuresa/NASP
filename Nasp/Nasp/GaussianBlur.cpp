#include "GaussianBlur.h"

//Input Image must be shrinked and in Grayscale (FOR NOW)
GaussianBlur::GaussianBlur(cv::Mat) { }

GaussianBlur::GaussianBlur() { }

GaussianBlur::~GaussianBlur() { }

void GaussianBlur::setGrayscaleImage(cv::Mat inputImageGrayscale) {
	_inputImgGrayscale = inputImageGrayscale;
}


void GaussianBlur::setBlurImage(cv::Size()) {
	//cv::GaussianBlur

}


//TODO: Show images


//Getters
cv::Mat GaussianBlur::getBlurImage() {
	return _inputImgGaussianBlurr;
}

cv::Mat GaussianBlur::getGrayscaleImage() {
	return _inputImgGrayscale;
}

