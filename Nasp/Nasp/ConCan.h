
#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


class ConCan {
private:
	cv::Mat _inputImg, _inputImgGrayscale, _inputImgShrinked;
	int _thresh, _maxThresh;

	cv::Mat _imgCanny;
	cv::vector<cv::vector<cv::Point>> _contours;
	cv::vector<cv::Vec4i> _hierarchy;

	//Used for Gaussian Blur
	int max_kernel_lenght = 31;

public:
	ConCan(cv::Mat);
	ConCan();
	~ConCan();


	//TODO: Fix this ugly code

	void ConCan::findContours();

	//Setters
	void ConCan::setInputImage(cv::Mat inputImg);

	//Note -> Detect Edges by supplying "Your" image
	//Shouldn't be used as Img SIZE isn't default
	void ConCan::setInputImageCanny(cv::Mat inputImg, int thresh, int maxThresh);

	//Note -> Detect Edges for image in object
	void ConCan::setInputImageCanny(int thresh, int maxThresh);

	//Getters
	cv::Mat getInputImage();

	//Note -> Grayscale version of image will only exist from/as shrinked
	cv::Mat ConCan::getInputImgGrayscale();

	cv::Mat ConCan::getInputImageShrinked();

	cv::Mat ConCan::getInputImageCanny();



	cv::vector<cv::vector<cv::Point>> ConCan::getContours();

	cv::vector<cv::Vec4i> ConCan::getHierarchy();


};

