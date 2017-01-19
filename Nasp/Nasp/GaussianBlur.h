
#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class GaussianBlur {
private:
	cv::Mat _inputImgGrayscale, _inputImgGaussianBlurr;
public:
	GaussianBlur(cv::Mat);
	GaussianBlur();
	~GaussianBlur();

	//Show methods
	void GaussianBlur::showBlurredImage();
	void GaussianBlur::showGrayscaleImage();

	//Setters
	void GaussianBlur::setBlurImage(cv::Size());
	void GaussianBlur::setGrayscaleImage(cv::Mat);

	//Getters
	cv::Mat GaussianBlur::getGrayscaleImage();
	cv::Mat GaussianBlur::getBlurImage();

};

