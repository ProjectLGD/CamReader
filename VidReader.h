#pragma once

#include "dot.h"
class VidReader
{
	struct HSV {
		int H;
		int S;
		int V;
	};
	struct HSVRANGE {
		DOT_TYPE color;
		HSV min;
		HSV max;
	};

private:
	///BLUE
	HSV hsvstructBlueMin;
	// 6 238 255
	HSV hsvstructBlueMax;

	///ROOD
	HSV hsvstructRedMin;
	// 115 221 255
	HSV hsvstructRedMax;

	DOT getDot(Mat hsv,HSVRANGE range);

	VideoCapture *cap;

public:
	VidReader();
	vector<DOT> getPositions(Mat& snapshot);
	~VidReader();
};

