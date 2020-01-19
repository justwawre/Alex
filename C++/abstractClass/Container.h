#ifndef Container_h
#define Container_h

#include <string>
class Container
{
public:
    virtual double &operator[](int) = 0;
    virtual int size() const = 0;
    virtual std::string name() { return "base"; };
    std::string ss() { return "CONTAINER"; }
    virtual ~Container() {}
};
#endif
