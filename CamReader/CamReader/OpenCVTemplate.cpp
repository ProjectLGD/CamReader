#include "stdafx.h"
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;
using namespace cv;

struct HSV {
	int H;
	int S;
	int V;
};

struct POS {
	int x;
	int y;
};


int main() {

	Mat frame = imread("C:/Users/Arthur/Google Drive/Minor V&R Project/testbr2.png", CV_LOAD_IMAGE_COLOR);
	imshow("original", frame);

	Mat hsv;

	cvtColor(frame, hsv, COLOR_RGB2HSV);


	///Rechts onder (rood)
	HSV hsvstructMin;
	hsvstructMin.H = 105;
	hsvstructMin.S = 14;
	hsvstructMin.V = 138;
	/// 107 16 140 
	HSV hsvstructMax;
	hsvstructMax.H = 109;
	hsvstructMax.S = 18;
	hsvstructMax.V = 142;

	///LINKSBOVEN (groen)
	/*HSV hsvstructMin;
	hsvstructMin.H = 85;
	hsvstructMin.S = 21;
	hsvstructMin.V = 160;
	/// 90 4 141    86 22 161
	HSV hsvstructMax;
	hsvstructMax.H = 87;
	hsvstructMax.S = 23;
	hsvstructMax.V = 162;*/

	/*///BLAUW
	HSV hsvstructMin;
	hsvstructMin.H = 130;
	hsvstructMin.S = 15;
	hsvstructMin.V = 154;
	/// 130 15 154
	HSV hsvstructMax;
	hsvstructMax.H = 130;
	hsvstructMax.S = 17;
	hsvstructMax.V = 154;*/



	Mat gray_image;
	//cvtColor(frame, gray_image, CV_BGR2GRAY);
	inRange(hsv, Scalar(hsvstructMin.H , hsvstructMin.S, hsvstructMin.V), Scalar(hsvstructMax.H, hsvstructMax.S, hsvstructMax.V), gray_image);



	// Het tonen van grijswaarde beeld
	imshow("MyVideo", gray_image);

	Mat binaryImage;
	Mat binaryImageShow;
	threshold(gray_image, binaryImage, 200, 1, CV_THRESH_BINARY_INV);
	threshold(gray_image, binaryImageShow, 200, 200, CV_THRESH_BINARY_INV);
	imshow("threshold", binaryImageShow);
	int erosion_size = 3;
	Mat element = getStructuringElement(MORPH_RECT,
		Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		Point(erosion_size, erosion_size));

	Mat erosion_dst;
	/// Apply the erosion operation
	erode(binaryImage, erosion_dst, element);

	imshow("erode", erosion_dst*255);
	Mat binary16S;
	Mat binary16SShow;
	erosion_dst.convertTo(binary16S, CV_16S);
	binaryImageShow.convertTo(binary16SShow, CV_8U);
	imshow("binary", binary16S*255);

	//cv::SimpleBlobDetector::Params params;
	//params.minThreshold = 0;
	//params.maxThreshold = 255;

	//// Filter by Area.
	//params.filterByArea = true;
	//params.minArea = 0;
	//params.maxArea = 10000000;

	//// Filter by Circularity
	//params.filterByCircularity = false;
	//params.minCircularity = 0;
	//params.maxCircularity = 1;

	//// Filter by Convexity
	//params.filterByConvexity = false;
	//params.minConvexity = 0;
	//params.maxConvexity = 1;

	//// Filter by Inertia
	//params.filterByInertia = false;
	//params.minInertiaRatio = 0.7;

	//cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);

	//std::vector<cv::KeyPoint> keypoints;
	//detector->detect(binary16S, keypoints);
	//std::cout << keypoints.size() << std::endl;
	//Mat im_with_keypoints;
	//drawKeypoints(binary16S, keypoints, im_with_keypoints, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	//imshow("keypoints", im_with_keypoints*255);


	Mat labeledImage2;
	vector<Point2d *> firstpixelVec2;
	vector<Point2d *> posVec2;
	vector<int> areaVec2;
	int blobs = labelBLOBsInfo(binary16S, labeledImage2, firstpixelVec2, posVec2, areaVec2);
	//show16SImageStretch(labeledImage2, "Labeled Image 2");
	std::cout << firstpixelVec2.size() << std::endl;
	//std::cout << "test" << std::endl;

	
	waitKey(0);
	while (true)
	{
		waitKey(27);
	}


	return 0;
}

