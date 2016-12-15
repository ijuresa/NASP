
#include "ConCan.h"

ConCan::ConCan(cv::Mat) {

}

ConCan::ConCan() {

}

ConCan::~ConCan() {

}

cv::Mat ConCan::getInputImage() {
	return _inputImg;
}

cv::Mat ConCan::getInputImgGrayscale() {
	return _inputImgGrayscale;
}

cv::Mat ConCan::getInputImageShrinked() {
	return _inputImgShrinked;
}

cv::vector<cv::vector<cv::Point>> ConCan::getContours() {
	return _contours;
}

cv::Mat ConCan::getInputImageCanny() {
	return _imgCanny;
}

cv::vector<cv::Vec4i> ConCan::getHierarchy() {
	return _hierarchy;
}

void ConCan::setInputImage(cv::Mat inputImg) {
	cv::Size imgSize(800, 640);

	if ((inputImg.size().height > 800) || (inputImg.size().width > 640)) {
		//Save img as shrinked
		cv::resize(inputImg, _inputImgShrinked, imgSize, CV_INTER_AREA);

		//Convert to grayscale
		cv::cvtColor(_inputImgShrinked, _inputImgGrayscale, CV_RGB2GRAY);
		_inputImg = inputImg;
	}
	else { }
}

void ConCan::setInputImageCanny(cv::Mat inputImg, int thresh, int maxThresh) { }

void ConCan::setInputImageCanny(int thresh, int maxThresh) {
	_thresh = thresh;
	_maxThresh = maxThresh;
	cv::Canny(_inputImgGrayscale, _imgCanny, _thresh, thresh * 2, 3);
}

void ConCan::findContours() {
	cv::findContours(_imgCanny, _contours, _hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE,
		cv::Point(0, 0));
}
