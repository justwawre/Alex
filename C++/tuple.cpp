/*
-std=c++1z
 */
#include <tuple>
#include <iostream>
#include <string>
#include <stdexcept>
#include "toolkit.h"
using namespace std;
 
std::tuple<double, char, std::string> get_student(int id)
{
    if (id == 0) return std::make_tuple(3.8, 'A', "Lisa Simpson");
    if (id == 1) return std::make_tuple(2.9, 'C', "Milhouse Van Houten");
    if (id == 2) return std::make_tuple(1.7, 'D', "Ralph Wiggum");
    throw std::invalid_argument("id");
}

/*
std::tuple的一个常见用途是从一个函数返回多个值。

std::tuple是一个模板，允许我们将多个不同类型的成员捆绑成单一对象。每个tuple包含指定数量的成员，但对一个给定的tuple类型，标准库并未限制我们可以定义的成员数量上限。

std::tuple中元素是被紧密地存储的(位于连续的内存区域)，而不是链式结构
*/
void  tuple_test()
{
    FUNC_HEAD();
    
    auto student0 = get_student(0);
    std::cout << "ID: 0, "
              << "GPA: " << std::get<0>(student0) << ", "
              << "grade: " << std::get<1>(student0) << ", "
              << "name: " << std::get<2>(student0) << '\n';
 
    double gpa1;
    char grade1;
    std::string name1;
    std::tie(gpa1, grade1, name1) = get_student(1);
    std::cout << "ID: 1, "
              << "GPA: " << gpa1 << ", "
              << "grade: " << grade1 << ", "
              << "name: " << name1 << '\n';
 
    // C++17 structured binding:
    auto [ gpa2, grade2, name2 ] = get_student(2);
    std::cout << "ID: 2, "
              << "GPA: " << gpa2 << ", "
              << "grade: " << grade2 << ", "
              << "name: " << name2 << '\n';
}

int main()
{
    tuple_test();
    return 0;
}

