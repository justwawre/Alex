#include "circle.h"
#include "point.h"
#include <iostream>
using namespace std;

Circle::Circle(Point p, int rr) : c{p}, r{rr} {}

Point Circle::center() const
{
    return c;
}

void Circle::move(Point to)
{
    c = to;
}

void Circle::draw() const
{
    cout << "cneter is " << c << " radius is " << r << endl;
}

void Circle::rotate(int angle)
{
    cout << "rotate " << angle << " degree" << endl;
}

Circle::~Circle()
{
}