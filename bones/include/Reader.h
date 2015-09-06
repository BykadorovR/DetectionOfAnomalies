#ifndef READER_H_
#define READER_H_
#include "gdcmImageReader.h"
#include "string"
#include "vector"
using namespace std;
class Reader {
  private:
    string nameOfFiles;
    /*
    Parsing image
    */
    gdcm::ImageReader reader;
    int intercept;
    int slope;
    int imgSize;
    int imgWidth;
    int imgHeight;
    int windowCenter;
    int windowWidth;
    int* HUValues;
  public:
    Reader (string _nameOfFiles);

	void initializeHUValuesFromUInt16(char* buffer);
	char* readFile();
	int getHU(int x, int y);
	int* getHUArray();
    int getWidth();
    int getHeight();
    int getWindowCenter();
    int getWindowWidth();
};

#endif /* READER_H_ */