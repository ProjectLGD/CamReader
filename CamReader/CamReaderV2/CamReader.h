#pragma once
class CamReader
{
	struct HSV {
		int H;
		int S;
		int V;
	};
	struct HSVRANGE {
		std::string name;
		HSV min;
		HSV max;
	};

	struct DOT {
		std::string color;
		Point pt;
	};

	///SCHERM BLAUW
	HSV hsvstructBlueMin;
	// 6 238 255
	HSV hsvstructBlueMax;

	///ROOD
	HSV hsvstructRedMin;
	// 115 221 255
	HSV hsvstructRedMax;
	

private:


public:
	CamReader();
	~CamReader();
};

