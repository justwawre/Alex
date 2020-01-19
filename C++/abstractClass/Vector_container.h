#ifndef Vector_container_h
#define Vector_container_h

#include "Container.h"
#include <initializer_list>

class Vector_container : public Container
{
private:
    double *elem;
    int sz;

public:
    Vector_container();
    /* 
    if no explicit,  
        Vector_container v = 7;  
    compilation is OK, and it will call Vector_container(int s)
    if explicit, the compiler will report
        error: no viable conversion from 'int' to 'Vector_container'
     */
    explicit Vector_container(int s);
    Vector_container(const Vector_container &a);            //copy constructor
    Vector_container(Vector_container &&a);                 //move constructor
    Vector_container &operator=(const Vector_container &a); //copy assignment
    Vector_container &operator=(Vector_container &&a);      //move assignment; The && means ‘‘rvalue reference’’

    ~Vector_container(); //deconstructor

    Vector_container(std::initializer_list<double>);
    void push_back(double);

    double &operator[](int i);
    int size() const;
    virtual std::string ss() { return "Vector_container"; }
    std::string name() { return "Vector_container"; }
};

#endif