#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.h"
class Circle : public Shape
{
private:
    Point c; //center
    int r;   //radius
public:
    Circle(Point p, int rr);
    Point center() const; //the prototype just copied from shape.h, time waste
    void move(Point to);
    void draw() const;
    void rotate(int);
    ~Circle();
};

#endif