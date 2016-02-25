#ifndef DETECTING_H_
#define DETECTING_H_

#include <vector>
#include <Point.h>
#include <Ray.h>
using namespace std;

class Detecting {
private:
	vector<Point> array;
	vector<Point> RoI;
	vector<int> picture;
	int width, height;
public:
	Detecting (int _width, int _height) {
		width = _width;
		height = _height;
	}
	
	Detecting(vector<int> _picture, int _width, int _height) {
		width = _width;
		height = _height;
		picture = _picture;
	}

	void setMonotonePicture(vector<int> _picture);
	void setRoI(vector<Point> _RoI);
	Point getTreshold (int startX, int startY, int field);
	void stepOfRays(int startX, int startY);
	void detectingWithPoints(int startX, int startY, int count);
	vector<Point> getArrayOfPoints();
	void setNullForArray();


};

#endif /* DETECTING_H_ */