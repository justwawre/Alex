#include <vector>
#include <memory>
#include "shape.h"
#include "circle.h"
#include "smiley.h"
#include "../toolkit.h"

using namespace std;

void rotate_all(vector<Shape *> &v, int angle) // must using < xxx *>
{
    FUNC_HEAD();
    for (auto p : v)
    {
        if (Smiley *pp = dynamic_cast<Smiley *>(p))
        {
            p->rotate(angle);
            pp->wink(3);
        }
        else
        {
            p->rotate(angle);
        }
    }
}

template <typename C, typename Oper>
void for_all(C &c, Oper op) // assume that C is a container of pointers
{
    for (auto &x : c)
        op(*x); // pass op() a reference to each element pointed to
}

void test_template()
{
    FUNC_HEAD();
    vector<unique_ptr<Shape>> v;

    Shape *eye1 = new Circle{Point(25, 20), 5};
    Shape *eye2 = new Circle{Point(35, 20), 5};
    Shape *mouth = new Circle{Point(30, 35), 5};
    v.push_back(unique_ptr<Shape>{eye1});
    v.push_back(unique_ptr<Shape>{eye2});
    v.push_back(unique_ptr<Shape>{mouth});

    for_all(v, [](Shape &s) { s.draw(); });     // draw_all()
    for_all(v, [](Shape &s) { s.rotate(45); }); // rotate_all(45)
}

void test_poly()
{
    FUNC_HEAD();
    Point p(30, 30);
    cout << p << endl;
    Smiley *face = new Smiley(p, 10);

    Shape *eye1 = new Circle{Point(25, 20), 5};
    Shape *eye2 = new Circle{Point(35, 20), 5};
    Shape *mouth = new Circle{Point(30, 35), 5};

    face->add_eye(eye1);
    face->add_eye(eye2);
    face->set_mouth(mouth);

    face->draw();

    vector<Shape *> v;
    v.push_back(face);
    rotate_all(v, 30);

    //everything added into the Smiley, will delete during deconstruction
    delete face;
}

int main()
{
    test_poly();
    test_template();

    return 0;
}