#ifndef SMILEY_H
#define SMILEY_H
#include <vector>
#include "shape.h"
#include "circle.h"
using namespace std;

class Smiley final : public Circle
{
private:
    vector<Shape *> eyes;
    Shape *mouth;

public:
    //Smiley(Point p, int r); 由于继承构造,不再需要
    using Circle::Circle;
    //if explict overriding,compile 可以帮助检查base class 是否有可以覆盖的method
    void move(Point to) override;
    void draw() const override;
    void rotate(int) override;

    void add_eye(Shape *s);
    void set_mouth(Shape *s);
    virtual void wink(int i);
    ~Smiley();
};
#endif