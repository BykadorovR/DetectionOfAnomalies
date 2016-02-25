#include "Utils.h"
#include <iostream>
#include <cmath>
#include "Ray.h"


vector<int> fromUInt16ToUInt8(int* buffer, int size, int windowCenter, int windowWidth) {
	vector<int> result(size);
	int minValue = buffer[getMinIndex(buffer, size)];
	int maxValue = buffer[getMaxIndex(buffer, size)];
	int step = (abs(minValue) + abs(maxValue))/size;
	//windowWidth = 1500;
	//windowCenter = 350;
	//https://www.dabsoft.ch/dicom/3/C.11.2.1.2/
	for (int i=0; i<size; i++) {
		if (buffer[i]<=windowCenter - 0.5 - (windowWidth - 1)/2) result[i] = 0;
		else if (buffer[i]>windowCenter-0.5+(windowWidth-1)/2) result[i] = 255;
			else result[i] = ((buffer[i]-(windowCenter-0.5))/(windowWidth-1)+0.5)*255;
	}
	return result;
}

int getMinIndex(int* buffer, int size) {
	int min = buffer[0];
	int index = 0;
	for (int i = 1; i < size; i++) {
		if (buffer[i] < min) {
			index = i;
			min = buffer[i];
		}
    }
	return index;
}

int getMaxIndex(int* buffer, int size) {
	int max = buffer[0];
	int index = 0;
	for (int i = 1; i < size; i++) {
		if (buffer[i] > max) {
			index = i;
			max = buffer[i];
		}
	}
	return index;
}

int operatorSobel(vector<int> array, int width, int height, int center) {
	int GX[3][3] = {{-1, 0, 1},
                 {-2, 0, 2},
                 {-1, 0, 1}};

    int GY[3][3] = {{ 1, 2, 1},
                 { 0, 0, 0},
                 {-1,-2,-1}};
    int sumX = 0, sumY = 0;
    int sum;
    for (int x = -1; x <= 1; x++)
    	for (int y = -1; y <= 1; y++) {
    		int numberImage = center + x*width + y;
    		sumX += array[numberImage]*GX[x+1][y+1];
    		sumY += array[numberImage]*GY[x+1][y+1];
    		sum = sqrt (sumX*sumX+sumY*sumY);
    	}
    return sum;
}

double mean (set<Point>& array, Point center) {
	set<Point>::iterator i;
    int sum = 0;
    for (i = array.begin(); i != array.end(); i++) {
    	sum += abs ((*i).getX() - center.getX());
    }
    sum = sum/array.size();
    return sum;
}

double dispersion (set<Point>& array, Point center) {
	double m = mean(array, center);
	set<Point>::iterator i;
    int sum = 0;
    for (i = array.begin(); i != array.end(); i++) {
    	int tmp = abs ((*i).getX() - center.getX()) - m;
    	sum += tmp*tmp;
    }
    sum = sum / array.size();
    return sqrt(sum);
}

bool _relationOfPointAndPolygon(int x, int y, vector<Point> polygon) {
	for (int i = 1; i < polygon.size(); i++) {
		int A = -(polygon[i].getY() - polygon[i-1].getY());
		int B = polygon[i].getX() - polygon[i-1].getX();
		int C = -(A * polygon[i - 1].getX() + B*(polygon[i - 1].getY()));
		int D = A * x + B * y + C;
		if (D > 0) return false;
	}
	return true;
}

void cropImage(vector<int>& src, int sizeX, int sizeY, vector<Point> polygon) {
	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y < sizeY; y++) {
			if (!_relationOfPointAndPolygon(x, sizeY - y, polygon)) {
				src[x + y*sizeX] = 0;
			}
		}
	}
}