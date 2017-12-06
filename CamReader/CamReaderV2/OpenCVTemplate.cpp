#include "stdafx.h"
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>

#include "genetic-algo/Vec3.h"


using namespace std;
using namespace cv;

struct HSV {
	int H;
	int S;
	int V;
};
struct HSVRANGE {
	string name;
	HSV min;
	HSV max;
};

struct DOT {
	string color;
	Point pt;
};



int main() {
	Vec3 reee(500,0,0);
	cout << reee << endl;
	VideoCapture cap(0);

	
	if (!cap.isOpened())
	{
		cout << "Cannot open the video cam" << endl;

	}

	
	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	cout << "Frame size : " << dWidth << " x " << dHeight << endl;

	Mat frame;

	///SCHERM BLAUW
	HSV hsvstructBlueMin;
	hsvstructBlueMin.H = 0;
	hsvstructBlueMin.S = 200;
	hsvstructBlueMin.V = 200;
	// 6 238 255
	HSV hsvstructBlueMax;
	hsvstructBlueMax.H = 20;
	hsvstructBlueMax.S = 245;
	hsvstructBlueMax.V = 255;

	///ROOD
	HSV hsvstructRedMin;
	hsvstructRedMin.H = 110;
	hsvstructRedMin.S = 175;
	hsvstructRedMin.V = 175;
	/// 115 221 255
	HSV hsvstructRedMax;
	hsvstructRedMax.H = 125;
	hsvstructRedMax.S = 230;
	hsvstructRedMax.V = 255;


	vector<HSVRANGE> colors;
	HSVRANGE red;
	red.name = "RED";
	red.min = hsvstructRedMin;
	red.max = hsvstructRedMax;

	HSVRANGE blue;
	blue.name = "BLUE";
	blue.min = hsvstructBlueMin;
	blue.max = hsvstructBlueMax;

	colors.push_back(red);
	colors.push_back(blue);


	while (1)
	{

		
		bool bSuccess = cap.read(frame);

		
		if (!bSuccess)
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}
		

		Mat hsv;

		cvtColor(frame, hsv, COLOR_RGB2HSV);
		imshow("test", frame);
		std::cout << "start" << std::endl;
		if (waitKey(1) == 27)
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
		


		vector<DOT> positions;


		for (HSVRANGE range : colors)
		{
			
			Mat gray_image;
			//cvtColor(frame, gray_image, CV_BGR2GRAY);
			inRange(hsv, Scalar(range.min.H, range.min.S, range.min.V), Scalar(range.max.H, range.max.S, range.max.V), gray_image);



			// Het tonen van grijswaarde beeld
			//imshow("MyVideo", gray_image);

			Mat binaryImage;
			Mat binaryImageShow;
			threshold(gray_image, binaryImage, 150, 1, CV_THRESH_BINARY);
			threshold(gray_image, binaryImageShow, 200, 200, CV_THRESH_BINARY);
			////imshow("threshold", binaryImageShow);
			int erosion_size = 2;
			Mat element = getStructuringElement(MORPH_RECT,
				Size(2 * erosion_size + 1, 2 * erosion_size + 1),
				Point(erosion_size, erosion_size));

			Mat erosion_dst;
			/// Apply the erosion operation
			dilate(binaryImage, erosion_dst, element);

			GaussianBlur(erosion_dst, erosion_dst, Size(5,5), 0);
			imshow(range.name, erosion_dst * 255);
			Mat binary16S;
			Mat binary16SShow;
			erosion_dst.convertTo(binary16S, CV_16S);
			binaryImageShow.convertTo(binary16SShow, CV_8U);
			////imshow("binary", binary16S * 255);


			Mat labeledImage2;
			vector<Point2d *> firstpixelVec2;
			vector<Point2d *> posVec2;
			vector<int> areaVec2;
			labelBLOBsInfo(binary16S, labeledImage2, firstpixelVec2, posVec2,areaVec2);
			//show16SImageStretch(labeledImage2, "Labeled Image 2");
			Point colorPosition;
			if (posVec2.size() != 0)
			{
				//std::cout << firstpixelVec2.size() << std::endl;
				//std::cout << "blobs:" << blobs << std::endl;
				//std::cout << "found points:" << posVec2.size() << std::endl;
				//std::cout << "internal point " << posVec2[0]->x << "-" << posVec2[0]->y << std::endl;
				colorPosition = Point(firstpixelVec2[0]->x, firstpixelVec2[0]->y);
			}
			DOT foundDot;
			foundDot.color = range.name;
			foundDot.pt = colorPosition;
			positions.push_back(foundDot);

			waitKey(1);
	
		}

		std::cout << "------" << std::endl;
		for (DOT d : positions)
		{
			
			std::cout << "Point " << d.pt.x << "-" << d.pt.y <<  " " <<  d.color << std::endl;
			
		}
		std::cout << "------" << std::endl;
		//std::cout << "boi" << std::endl;



		if (waitKey(1) == 27)
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
		return 0;
}


