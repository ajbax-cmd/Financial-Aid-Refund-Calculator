#include "OriginationFee.h"
#include <fstream>
using namespace std;

void OriginationFee::setOrigFee(double input)
{
	fstream File;
	File.open("OriginationFee.txt", ios::out);
	{
		File << input;
	}
	File.close();
}

double OriginationFee::getOrigFee()
{
	fstream File;
	File.open("OriginationFee.txt", ios::in);
	if (File.fail())
	{
		OrigFee = 0.00;
	}
	else
	{
		File >> OrigFee;
	}
	File.close();
	return OrigFee;
}


