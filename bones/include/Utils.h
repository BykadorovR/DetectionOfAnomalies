#ifndef UTILS_H_
#define UTILS_H_

#include <set>
#include <vector>
#include <Point.h>
#include <Ray.h>
using namespace std;


vector<int> fromUInt16ToUInt8(int* buffer, int size, int windowCenter, int windowWidth);
int getMinIndex(int* buffer, int size);
int getMaxIndex(int* buffer, int size);
int operatorSobel(vector<int> array, int width, int height, int center);
double mean(set<Point>& array, Point center);
double dispersion(set<Point>& array, Point center);
void cropImage(vector<int>& src, int sizeX, int sizeY, vector<Point> polygon);

#endif /* UTILS_H_ */