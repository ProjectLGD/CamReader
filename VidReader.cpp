#include "stdafx.h"
#include "VidReader.h"


VidReader::VidReader()
{
	//Initialise values

	hsvstructBlueMin.H = 0;
	hsvstructBlueMin.S = 200;
	hsvstructBlueMin.V = 200;

	hsvstructBlueMax.H = 20;
	hsvstructBlueMax.S = 245;
	hsvstructBlueMax.V = 255;

	
	hsvstructRedMin.H = 110;
	hsvstructRedMin.S = 175;
	hsvstructRedMin.V = 175;
	
	hsvstructRedMax.H = 125;
	hsvstructRedMax.S = 230;
	hsvstructRedMax.V = 255;

	cap = new VideoCapture(1);
	//waitKey(500);
	if (!cap->isOpened())
		cout << "Cannot open the video cam" << endl;

	double dWidth = cap->get(CV_CAP_PROP_FRAME_WIDTH);
	double dHeight = cap->get(CV_CAP_PROP_FRAME_HEIGHT);
	cout << "Frame size : " << dWidth << " x " << dHeight << endl;



}

DOT VidReader::getDot(Mat hsv,HSVRANGE range)
{
	Mat gray_image;

	inRange(hsv, Scalar(range.min.H, range.min.S, range.min.V), Scalar(range.max.H, range.max.S, range.max.V), gray_image);

	Mat binaryImage;
	Mat binaryImageShow;
	threshold(gray_image, binaryImage, 150, 1, CV_THRESH_BINARY);
	threshold(gray_image, binaryImageShow, 200, 200, CV_THRESH_BINARY);
	
	int erosion_size = 2;
	Mat element = getStructuringElement(MORPH_RECT,
		Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		Point(erosion_size, erosion_size));

	Mat erosion_dst;
	/// Apply the erosion operation
	dilate(binaryImage, erosion_dst, element);

	GaussianBlur(erosion_dst, erosion_dst, Size(5, 5), 0);

	Mat binary16S;
	Mat binary16SShow;
	erosion_dst.convertTo(binary16S, CV_16S);
	

	Mat labeledImage2;
	vector<Point2d *> firstpixelVec2;
	vector<Point2d *> posVec2;
	vector<int> areaVec2;
	labelBLOBsInfo(binary16S, labeledImage2, firstpixelVec2, posVec2, areaVec2);

	Point colorPosition;
	if (posVec2.size() != 0)
		colorPosition = Point(firstpixelVec2[0]->y, firstpixelVec2[0]->x);
	
	DOT foundDot;
	foundDot.color = range.color;
	foundDot.pt = colorPosition;
	
	return foundDot;
}

vector<DOT> VidReader::getPositions(Mat &snapshot)
{
	

	Mat frame;

	//Setup search range
	vector<HSVRANGE> colors;
	HSVRANGE red;
	red.color = DOT_TYPE::RED;
	red.min = hsvstructRedMin;
	red.max = hsvstructRedMax;

	HSVRANGE blue;
	blue.color =DOT_TYPE::BLUE;
	blue.min = hsvstructBlueMin;
	blue.max = hsvstructBlueMax;

	colors.push_back(red);
	colors.push_back(blue);


	bool bSuccess = cap->read(frame);
	snapshot = frame;

	if (!bSuccess)
		cout << "Cannot read a frame from video stream" << endl;		


	Mat hsv;

	cvtColor(frame, hsv, COLOR_RGB2HSV);
	imshow("test", frame);
	std::cout << "start" << std::endl;
	waitKey(1);

	vector<DOT> positions;



	for (HSVRANGE range : colors)
		positions.push_back(getDot(hsv, range));

	std::cout << "position size:" << positions.size() << std::endl;

	return positions;


}

VidReader::~VidReader()
{
}
