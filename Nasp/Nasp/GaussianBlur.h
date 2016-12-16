
#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class GaussianBlur {
private:
	cv::Mat _inputImg, _inputImgGaussianBlurr;
public:
	GaussianBlur(cv::Mat)();
	GaussianBlur();
	~GaussianBlur();

	cv::Mat GaussianBlur::getInputImageBlurred();

};

