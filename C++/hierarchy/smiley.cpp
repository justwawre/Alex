#include "circle.h"
#include "smiley.h"
#include <vector>
using namespace std;

Smiley::~Smiley()
{
    delete mouth;
    for (auto p : eyes)
    {
        delete p;
    }
}

void Smiley::add_eye(Shape *s)
{
    eyes.push_back(s);
}

void Smiley::set_mouth(Shape *s)
{
    mouth = s;
}

void Smiley::wink(int i)
{
    cout << "wink" << endl;
}

void Smiley::draw() const
{
    cout << "the face:" << endl;
    Circle::draw();
    cout << "eyes:" << endl;
    for (auto p : eyes)
    {
        p->draw();
    }
    cout << "mouth:" << endl;
    mouth->draw();
}

void Smiley::move(Point to)
{
    Circle::move(to);
}

void Smiley::rotate(int angle)
{
    cout << "face rotate:" << endl;
    //C++中没有super或parent关键字，想要调父类方法，只能使用明确的[父类名称：：方法名]
    Circle::rotate(angle);
}