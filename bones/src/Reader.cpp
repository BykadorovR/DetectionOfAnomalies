#include "Reader.h"
#include "gdcmDataSet.h"
#include "gdcmAttribute.h"

Reader::Reader(string _nameOfFiles) {
	  nameOfFiles = _nameOfFiles;
	  reader.SetFileName(nameOfFiles.c_str());
	  reader.Read();
}

char* Reader::readFile() {
	gdcm::Image & img = reader.GetImage();
	intercept = img.GetIntercept();
	slope = img.GetSlope();
	imgSize = img.GetBufferLength();
	imgWidth = img.GetColumns();
	imgHeight = img.GetRows();
	char* buffer = new char[imgSize];
	img.GetBuffer(buffer);
	return buffer;
}

int Reader::getWindowCenter() {
	const gdcm::DataSet &ds = reader.GetFile().GetDataSet();
 	gdcm::Attribute<0x0028,0x1050> atCenter;
 	atCenter.Set( ds );
 	windowCenter = atCenter.GetValue();
	return windowCenter;
}

int Reader::getWindowWidth() {
	const gdcm::DataSet &ds = reader.GetFile().GetDataSet();
	gdcm::Attribute<0x0028,0x1051> atWidth;
 	atWidth.Set( ds );
 	windowWidth = atWidth.GetValue();
	return windowWidth;
}


void Reader::initializeHUValuesFromUInt16(char* buffer) {
	unsigned char *ubuffer = new unsigned char[imgSize];
	unsigned char *pubuffer = ubuffer;
	for (unsigned int i = 0; i < imgSize; i++)
	{
		*pubuffer++ = *buffer++;
	}
	int * _HUValues = new int [imgWidth*imgHeight];
	for (int y = 0; y < imgHeight; y ++)
		for (int x = 0; x < imgWidth; x ++) {
			//Вес пикселя = 16 бит, у нас массив char = 8 бит
			//то есть пиксель = char char (8 бит, 8 бит)
			//мы находим первую компоненту = low
			//находим вторую компоненту = high (=low + 1)
			int low = *(ubuffer + 2 * y * imgWidth + 2 * x);
			int high = *(ubuffer + 2 * y * imgWidth + 2 * x + 1);
			high <<=8;
			int value = high | low;
			_HUValues[x+y*imgWidth] = value*slope + intercept;
	}
	HUValues = _HUValues;
}

int Reader::getHU(int x, int y) {
	if (x < imgWidth && x >= 0 && y < imgHeight && y >= 0)
		return HUValues[x+y*imgWidth];
	throw "HU values have wrong range\n";
}

int* Reader::getHUArray() {
	return HUValues;
}



int Reader::getWidth() {
	return imgWidth;
}

int Reader::getHeight() {
	return imgHeight;
}
