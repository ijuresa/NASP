#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main() {
	cv::Mat rawImage = cv::imread("C:\\Users\\ivanj\\Documents\\Visual Studio 2013"
		"\\NASP\\tmpDataset\\Original\\IMG5.jpg");
	cv::Mat bilateralFilteredImage, shrinkedImage, cannyImage;
	cv::Size imgSize(800, 640);

	cv::vector<cv::vector<cv::Point>> _contours;
	
	cv::vector<cv::Vec4i> _hierarchy;

	cv::resize(rawImage, shrinkedImage, imgSize);

	cv::imshow("Original Image", shrinkedImage);
	cv::waitKey(0);

	cv::bilateralFilter(shrinkedImage, bilateralFilteredImage, 5, 175, 175);
	cv::imshow("Filtered", bilateralFilteredImage);
	cv::waitKey(0);

	cv::Canny(bilateralFilteredImage, cannyImage, 55, 175 * 2, 3);
	cv::imshow("Canny", cannyImage);
	cv::waitKey(0);

	cv::findContours(cannyImage, _contours, _hierarchy, CV_RETR_TREE,
		CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	cv::vector<cv::Point> aprox;
	
	double contArea;
	std::vector<size_t> contourListIndex;
	int largContIndex;

	for (size_t i = 0; i < _contours.size(); i ++) {
		std::cout << "# of contour points: " << _contours[i].size() << std::endl;
		std::cout << "Area: " << cv::contourArea(_contours[i]) << std::endl;

		cv::approxPolyDP(_contours[i], aprox, 0.01 * cv::arcLength(_contours[i], true), true);
		contArea = cv::contourArea(_contours[i], false);

		std::cout << "New area?!: " << contArea << std::endl;
		std::cout << "AproxSize ?!?: " << aprox.size() << std::endl;
		
		size_t newSize = aprox.size();
		if ((newSize > 8) & (contArea > 30)) {
			contourListIndex.push_back(i);
			largContIndex = i;
		}
	}

	for (int i = 0; i < contourListIndex.size(); i ++) {
		std::cout << "Vector has:! " << contourListIndex[i] << std::endl;
	}

	for (int i = 0; i < contourListIndex.size(); i ++) {
		cv::drawContours(shrinkedImage, _contours, contourListIndex[i], 
			(255, 0, 0), 2, 8, _hierarchy, 0, cv::Point());
	}
	
	cv::imshow("Detected!", shrinkedImage);
	cv::waitKey(0);


	//Convex Hull
	//Find it for all the contours --> Test
	cv::vector<cv::vector<cv::Point>> hull(contourListIndex.size());

	for (int i = 0; i < contourListIndex.size(); i ++) {
		cv::convexHull(_contours[i], hull[i], false);
		std::cout << "Hull at: " << i << " = " << hull[i] << std::endl;
	}

	//Draw Hull
	for (int i = 0; i < contourListIndex.size(); i ++) {
		cv::drawContours(shrinkedImage, hull, contourListIndex[i],
			(255, 0, 0), 2, 8, cv::vector<cv::Vec4i>(), 0, cv::Point());
	}
	cv::imshow("Hull", shrinkedImage);

	cv::waitKey(0);

	return 0;
}