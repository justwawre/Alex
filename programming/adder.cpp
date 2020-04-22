#include <iostream>
class adder
{
private:
    int x;

public:
    adder(int i) : x(i) {}
    int add(int y) { return x + y; }
};

int main()
{
    adder add5(5);
    std::cout << add5.add(3);
    return 0;
}