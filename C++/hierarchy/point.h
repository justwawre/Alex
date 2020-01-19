#ifndef POINT_H
#define POINT_H
#include <iostream>
using namespace std;
class Point
{
private:
    double x;
    double y;

public:
    Point(double x, double y);
    Point(const Point &a);
    //must use friend type
    friend ostream &operator<<(ostream &out, const Point &p);
};
#endif
