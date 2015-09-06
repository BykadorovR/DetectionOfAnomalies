#ifndef RAY_H_
#define RAY_H_

#include "Point.h"

class Ray {
 private:
 	Point* point;
 	Point* direction;
 	Point* current;
 public:
 	Ray(Point& _point, Point& _direction) {
		point = new Point(_point.getX(), _point.getY());
		direction = new Point(_direction.getX(), _direction.getY());
		current = new Point (_point);
	}


 	Point* getCenter() {
 		return point;
 	}

 	Point* getDirection() {
 		return direction;
 	}

 	void setDirection(Point& _direction) {
 		direction->setX(_direction.getX());
 		direction->setY(_direction.getY());
 	}

 	Point* getNextPoint() {
 		current->setX(current->getX()+direction->getX());
 		current->setY(current->getY()+direction->getY());
 		return current;
 	}

};

#endif /* RAY_H_ */