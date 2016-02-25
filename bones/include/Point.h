#ifndef POINT_H_
#define POINT_H_

class Point {
 private:
 	double x;
 	double y;
 public:
 	Point (double _x, double _y) {
	 	x = _x;
		y = _y;
	}

	Point (const Point& _point) {
		x = _point.getX();
		y = _point.getY();
	}

	Point (Point& _point) {
		x = _point.getX();
		y = _point.getY();
	}
	
	bool operator< (const Point &right) const
	{

  		return (x < right.getX() || y < right.getY());
	}
	

	double getX() const {
		return x;
	}

	double getY() const {
		return y;
	}

	void setX (int _x) {
		x = _x;
	}

	void setY (int _y) {
		y = _y;
	}
};

#endif /* POINT_H_ */