#ifndef SHAPE_H
#define SHAPE_H
#include "point.h"
class Shape
{
public:
    Shape() {} //abstrace base class still need constrcutor
    virtual Point center() const = 0;
    virtual void move(Point to) = 0;
    virtual void draw() const = 0;
    virtual void rotate(int) = 0;
    /* Using the default copy or move for a class in a hierarchy is typically a disaster: given only a pointer
to a base, we simply don’t know what members the derived class has , so we can’t know how
to copy them. So, the best thing to do is usually to delete the default copy and move operations,
that is, to eliminate the default definitions of those two operations
 */
    Shape(const Shape &) = delete; // no copy operations
    Shape &operator=(const Shape &) = delete;
    Shape(Shape &&) = delete; // no move operations
    Shape &operator=(Shape &&) = delete;

    virtual ~Shape() {}
};
#endif
