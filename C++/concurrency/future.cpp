/*  $ g++  future.cpp  -lpthread
 std::future 则是提供了一个访问异步操作结果的途径
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include "../toolkit.h"
using namespace std;

int test_future()
{
    FUNC_HEAD();
    // 将一个返回值为7 的lambda 表达式封装到task 中
    //  packaged_task 的模板参数为要封装函数的类型
    packaged_task<int()> task([]() { return 7; });
    // 获得task 的future
    future<int> result = task.get_future(); // 在一个线程中执行task
    thread(move(task)).detach();
    cout << " Waiting ... ";
    result.wait();
    // 输出执行结果
    cout << " Done !" << endl
               << " Result is " << result.get() << '\n';
}

int main()
{
    test_future();

    return 0;
}