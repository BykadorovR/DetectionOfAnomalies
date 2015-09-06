#include "Algorithms.h"
#include <cstdlib>
#include <iostream>

Algorithms::Algorithms(const vector<int>& _array) {
	array = _array;
} 

int _compare(const void * x1, const void * x2) {
  return ( *(int*)x1 - *(int*)x2 );
}

int Algorithms::median (int positionInArray, int sizeOfArea) {
	vector<int> area = _getArea(positionInArray, sizeOfArea);
	if (area.empty() || area.size() != sizeOfArea) {
		return -1;
	}
	qsort(&area[0], area.size(), sizeof(int), _compare);
	//TO DO: If size of area is divided by 2 when need to throw exception else return result
	return area[area.size()/2];
}

vector<int> Algorithms::_getArea(int positionInArray, int sizeOfArea) {
	if (positionInArray > array.size() - 1) {
		return vector<int>();
	}
	int edge = sizeOfArea / 2;
	int leftCorner = positionInArray - edge;
	int rightCorner = positionInArray + edge;
	if (leftCorner < 0) {
		leftCorner = 0;
		rightCorner+=edge-positionInArray;
	}
	if (rightCorner > array.size() - 1) {
		rightCorner = array.size() - 1;
		leftCorner-=edge-(array.size()-1-positionInArray);
	}
	int currentSize = rightCorner - leftCorner + 1; 
	vector<int> area(currentSize);
	for (int i = 0; i < currentSize; i++) {
		area[i] = array[leftCorner+i];
	}
	return area;
}