#include "stdafx.h"
#include "CamReader.h"


CamReader::CamReader()
{
	//Initialise rnages
	hsvstructBlueMin.H = 0;
	hsvstructBlueMin.S = 230;
	hsvstructBlueMin.V = 253;
	
	hsvstructBlueMax.H = 20;
	hsvstructBlueMax.S = 245;
	hsvstructBlueMax.V = 255;


	hsvstructRedMin.H = 110;
	hsvstructRedMin.S = 215;
	hsvstructRedMin.V = 253;
	
	hsvstructRedMax.H = 125;
	hsvstructRedMax.S = 230;
	hsvstructRedMax.V = 255;

}




CamReader::~CamReader()
{
}
