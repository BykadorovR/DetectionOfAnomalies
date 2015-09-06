#ifndef UTILS_H_
#define UTILS_H_

#include <set>
#include <vector>
#include <Point.h>
#include <Ray.h>
using namespace std;


int* fromUInt16ToUInt8(int* buffer, int size, int windowCenter, int windowWidth);
int getMinIndex(int* buffer, int size);
int getMaxIndex(int* buffer, int size);
int operatorSobel(int* array, int width, int height, int center);
double mean(set<Point>& array, Point center);
double dispersion(set<Point>& array, Point center);
vector<int> fromSetPointsToVectorDistance(set<Point> edgePoints, Point center);

#endif /* UTILS_H_ */