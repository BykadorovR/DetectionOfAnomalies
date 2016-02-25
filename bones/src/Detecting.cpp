#include <Detecting.h>
#include <Utils.h>
#include <math.h>

void Detecting::setMonotonePicture(vector<int> _picture) {
	picture = _picture;
}

Point Detecting::getTreshold (int startX, int startY, int field) {
    Point click (startX,startY);

    int max = 0;
    Point maxPoint(-1,-1);
    Point usedPoint(0,0);
    if (array.size() > 1)
        usedPoint = array[(array.size()-2)];

    for (int i=-field; i<=field; i++)
        for (int j=-field; j<=field; j++) {
            if (j==i && j==0) {
                continue;
            }
            bool avoidPrevTresholds = false;
            for (int k = -1; k <= 1; k++) {
                for (int m = -1; m <= 1; m++) {
                    if ((startX+i) == (usedPoint.getX()+k) && (startY+j) == (usedPoint.getY() + m)) {
                        avoidPrevTresholds = true;
                        break;
                    }
                }
                if (avoidPrevTresholds) break;
            }
            if (avoidPrevTresholds) continue;
            int value = operatorSobel(picture, width, height, (startX+i)+(startY+j)*width);
                if (value > max) {
                    max = value;
                    maxPoint.setX(startX+i);
                    maxPoint.setY(startY+j);
                }

        }
    return maxPoint;
}

void Detecting::setRoI(vector<Point> _RoI) {
	
}

void Detecting::setNullForArray() {
    array.clear();
}

vector<Point> Detecting::getArrayOfPoints() {
    return array;
}


void Detecting::detectingWithPoints(int startX, int startY, int count) {
    Point null(-10, -10);
    Point firstPoint = getTreshold(startX, startY, 2);
    array.push_back(firstPoint);

    for (int i =0; i < count; i++) {
        Point secondPoint = getTreshold(firstPoint.getX(), firstPoint.getY(), 1);
        null = firstPoint;
        firstPoint = secondPoint;
        array.push_back(secondPoint);
    }
}

void Detecting::stepOfRays(int startX, int startY) {
    //TODO: Rename outputValues to picture
    int sob = 0;
    int sobDown = 0;
    int distL = 0;
    int distR = 0;
    int oneTimeL = 0, oneTimeR = 0;
    Point current (0,0);
    Point oldPt (startX,startY);
    Point pt (startX, startY);
    int minX  = 999;
    int maxX = 0;
    int dist = 0;
    int treshold = 100;
    int tresholdOne = treshold;
    int tresholdBack = treshold;
    for (int j =0 ; j<2; j++) {
        while (sobDown < treshold) {
            sobDown = operatorSobel(picture, width, height, pt.getY()*width+pt.getX());
            for (int i =0 ; i<2; i++) {
                Point dir (0, 0);
                if (i == 0) {
                    dir = Point (-1, 0);
                }
                if (i == 1) {
                    dir = Point (1, 0);
                }
                Ray ray(pt,dir);
                current = *ray.getNextPoint();
                int startIndex = current.getY()*width+current.getX();
                int index =0 ;
                while (sob < tresholdOne) {
                    index = current.getY()*width+current.getX();
                    sob = operatorSobel(picture, width, height, current.getY()*width+current.getX());
                    //Ослабляем границу, только если определены distL и distR
                    if (oneTimeL == 1 && oneTimeR == 1) {

                        if (fabs(oldPt.getX()-current.getX()) > (distL+distR)) {
                            treshold -= 7;
                            index = startIndex;
                            break;
                        }
                  }

                    current = *ray.getNextPoint();
                }
                if (i == 0) {
                    if (oneTimeL == 0) {
                        distL = fabs(oldPt.getX() - current.getX());
                        oneTimeL = 1;
                    }
                }
                if (i == 1) {
                    if (oneTimeR == 0) {
                        distR = fabs(oldPt.getX() - current.getX());
                        oneTimeR = 1;
                    }
                }
                tresholdOne = tresholdBack;
                array.push_back(current);
                sob = 0;
            }
            if (j == 0) {
                pt.setY(pt.getY()+1);
            }
            if (j == 1) {
                pt.setY(pt.getY()-1);
            }
        }
        pt.setX(oldPt.getX());
        pt.setY(oldPt.getY());
        sobDown = 0;
    }
}

