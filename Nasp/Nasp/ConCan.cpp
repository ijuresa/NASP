
#include "ConCan.h"
#include <stdexcept>

ConCan::ConCan(cv::Mat) { }

ConCan::ConCan() { }

ConCan::~ConCan() { }

//Getters
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

//Setters

/*****************************************************************************
 *	INPUT for all image processing using this class	
 *																				
 *****************************************************************************
 *	Size of image will be checked, it will be shrinked to 800x640 and saved to 
 *		*_inputImgShrinked 
 *	Second it will be converted to grayscale and saved to _inputImgGrayscale
 *	The original image(nor shrinked nor grayscaled) will be saved to _inputImg 
 *		* var for future usage
*****************************************************************************/
void ConCan::setInputImage(cv::Mat inputImg) {
	cv::Size imgSize(800, 640);

	if ((inputImg.size().height > 800) || (inputImg.size().width > 640)) {
		//Save img as shrinked
		cv::resize(inputImg, _inputImgShrinked, imgSize, CV_INTER_AREA);
		_shrinked = true;

		//Convert to grayscale
		cv::cvtColor(_inputImgShrinked, _inputImgGrayscale, CV_RGB2GRAY);
		_grayscale = true;
		_inputImg = inputImg;
	}
	else { }
}

//Image should be grayscale (NOT IMPLEMENTED)
void ConCan::setInputImageCanny(cv::Mat inputImg, int thresh, int maxThresh) { }

void ConCan::calculateCanny(int thresh, int maxThresh) {
	_thresh = thresh;
	_maxThresh = maxThresh;

	//Check if grayscale image exists
	if (_inputImgGrayscale.empty()) {
		throw std::invalid_argument("No grayscale image found");
	}
	cv::Canny(_inputImgGrayscale, _imgCanny, _thresh, thresh * 2, 3);
}

//Ordinary edge detection using threshold --> IMAGE MUST BE in 
//GRAYSCALE, SHRINKED and BLURRED
void ConCan::setInputThresholdImage(cv::Mat inputImg, int thresh) {

}

void ConCan::findContours() {
	cv::findContours(_imgCanny, 
					_contours, 
					_hierarchy, 
					CV_RETR_TREE, 
					CV_CHAIN_APPROX_SIMPLE,
					cv::Point(0, 0)); 
}
