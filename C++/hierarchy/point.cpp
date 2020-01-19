#include "point.h"

Point::Point(double a, double b)
{
    x = a;
    y = b;
}

Point::Point(const Point &a)
{
    x = a.x;
    y = a.y;
}
//在重载输出输入运算符的时候，
//只能采用全局函数的方式（因为我们不能在ostream和istream类中编写成员函数）
ostream &operator<<(ostream &out, const Point &p)
{
    out << "(" << p.x << "," << p.y << ")";
    return out;
}