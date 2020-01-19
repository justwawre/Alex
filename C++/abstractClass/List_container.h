#ifndef List_container_h
#define List_container_h
#include "Container.h"
#include <list>

class List_container : public Container
{
private:
    std::list<double> ld;

public:
    List_container();
    List_container(std::initializer_list<double>);
    ~List_container();
    double &operator[](int);
    int size() const;
    std::string name() { return "List_container"; }
};

#endif