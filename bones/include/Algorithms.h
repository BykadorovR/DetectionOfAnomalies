#ifndef ALGORITHMS_H_
#define ALGORITHMS_H_
#include <vector>

using namespace std;
class Algorithms {
 public:
 	Algorithms (const vector<int>& _array);
	int median(int positionInArray, int sizeOfArea);
 private:
 	vector<int> array;
	vector<int> _getArea(int positionInArray, int sizeOfArea);
};

#endif /* ALGORITHMS_H_ */