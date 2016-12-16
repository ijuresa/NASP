#include "GaussianBlur.h"

//Input Image must be shrinked and in Grayscale (FOR NOW)
GaussianBlur::GaussianBlur(cv::Mat) { }

GaussianBlur::GaussianBlur() { }

GaussianBlur::~GaussianBlur() { }


cv::Mat GaussianBlur::getInputImageBlurred() {
	return _inputImgGaussianBlurr;
}

/*
//Check if inputImage needs to be blurred
if (blurr) {
	for (int i = 1; i < max_kernel_lenght; i = i + 2) {
		cv::GaussianBlur(_inputImgShrinked, _inputImgBlurred, cv::Size(i, i),
			0, 0);
	}
}*/