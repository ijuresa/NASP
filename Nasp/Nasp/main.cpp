
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>
#include <stdexcept>

#include "ConCan.h"
#include "GaussianBlur.h"


int main() {
	//TODO: Make automatically folder reader. Can be imgRead and then save 
	//attributes to xml file
	//Read image
	cv::Mat inputImg, inputImgGrayscale, inputImgShrinked;
	cv::vector<cv::Vec3f> circles;
		

	inputImg = cv::imread("C:\\Users\\ivanj\\Documents\\Visual Studio 2013"
		"\\NASP\\tmpDataset\\Original\\IMG1.jpg");
	
	
	//Canny and contours TEST
	ConCan newConCan = ConCan::ConCan();
	
	//Setting input Image => shrinked and converted to grayscale
	newConCan.setInputImage(inputImg);

	//Setting parameters for Canny and it's calculation
	try {
		newConCan.calculateCanny(100, 255);
	}
	catch(std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}
	

	cv::Mat getCanny = newConCan.getInputImageCanny();

	newConCan.findContours();
	cv::vector<cv::vector<cv::Point>> getContours = newConCan.getContours();
	cv::vector<cv::Vec4i> getHierarchy = newConCan.getHierarchy();


	//Only used for testing --> TO BE removed
	cv::Mat drawing = cv::Mat::zeros(getCanny.size(), CV_8UC3);
	cv::Scalar currColor = cv::Scalar(255, 255, 255);
	for (int i = 0; i < getContours.size(); i++) {
		cv::drawContours(drawing, getContours, i, currColor, 2, 8, 
			getHierarchy, 0, cv::Point());
	}
	
	//Displaying pictures side by side!
	//All pictures are 640x800
	cv::Size firstImgSize = newConCan.getInputImgGrayscale().size();
	cv::Size secondImgSize = newConCan.getInputImageCanny().size();

	cv::Mat collectedImg(firstImgSize.height, firstImgSize.width +
		secondImgSize.width, CV_8UC1);

	cv::Mat LEFT(collectedImg, cv::Rect(0, 0, firstImgSize.width,
		firstImgSize.height));
	newConCan.getInputImgGrayscale().copyTo(LEFT);

	cv::Mat RIGHT(collectedImg, cv::Rect(firstImgSize.width, 0,
		secondImgSize.width,
		secondImgSize.height));
	newConCan.getInputImageCanny().copyTo(RIGHT);

	//cv::imshow("Contours", collectedImg);
	cv::imwrite("Img7ConCan.jpg", collectedImg);
	
	//Check contour convexity?
	//TODO: See how to fix this --> Error: Contours not good enough
	//bool checkCon = cv::isContourConvex(getContours);
	//std::cout << "Is?! " << checkCon << std::endl;;
	
	if (inputImg.empty()) {
		std::cout << "Image Empty" << std::endl;
		return -1;
	}

	//Set size for currently loaded picture
	cv::Size newSize(800, 600);
	cv::resize(inputImg, inputImgShrinked, newSize, CV_INTER_AREA);

	//Convert to grayscale
	cv::cvtColor(inputImgShrinked, inputImgGrayscale, CV_RGB2GRAY);

	cv::HoughCircles(inputImgGrayscale, circles, CV_HOUGH_GRADIENT,
		1, 30, 200, 50, 0, 0);
	std::cout << "Number of circles found " << circles.size() << std::endl;

	for (int i = 0; i < circles.size(); i++) {
		
		cv::Point tempCenter(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int tempRadius = cvRound(circles[i][2]);

		std::cout << "Circle number: " << i << " Center is at: x=> " <<
			tempCenter.x << " and y=> " << tempCenter.y << " Radius: " << 
			tempRadius << std::endl;

		//Circle center
		cv::circle(inputImgShrinked, tempCenter, tempRadius, 
			cv::Scalar(0, 255, 0), -1, 8, 0);

		//Circle outline
		cv::circle(inputImgShrinked, tempCenter, tempRadius, 
			cv::Scalar(0, 0, 255), 3, 8, 0);
	}

	//cv::imshow("Image", inputImgShrinked);
	cv::waitKey(0);

	return 0;
}