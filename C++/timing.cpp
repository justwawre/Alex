#include <chrono>
#include <thread>
#include <iostream>
#include "toolkit.h"
using namespace std;
using namespace std::chrono;

void system_test()
{
    FUNC_HEAD();
    system_clock::period p;
    cout << "1 tick of system clock=" << p.num << "/" << p.den << " seconds" << endl;
}

void time_points_test()
{
    FUNC_HEAD();

    time_point<system_clock, seconds> tp;
    cout << "to epoch : " << tp.time_since_epoch().count() << " s" << endl;
}

void duration_test()
{
    FUNC_HEAD();

    milliseconds mscond(1000); // 1 second
    cout << mscond.count() << " milliseconds.\n";

    cout << mscond.count() * milliseconds::period::num / milliseconds::period::den;
    cout << " seconds.\n";

    ratio<60, 1> mins;
    cout << "1 min=" << mins.num << "/" << mins.den << " seconds.\n";

    milliseconds ms(54802);
    seconds s = duration_cast<seconds>(ms);
    cout << s.count() << " seconds\n";
}

void suffix_test()
{
    FUNC_HEAD();
    auto t0 = high_resolution_clock::now();
    cout << "this test will call sleep, so it will take some mins" << endl;
    /*
    常量后缀只是对常量做强制类型转换的语法糖
    C++11 以后对这个语法规则做了扩充，不但扩充了常量前缀（和后缀是一个道理），
    还支持了用户自定义常量后缀。我们不妨再举一些例子。
    譬如在新增的前缀中，u8'a' 可用于表示 UTF8 编码的字符；u'汉' 可用于表示 UTF-16 编码的字符，它和 (char16_t)('汉') 是一个道理。
    用户自定义常量后缀里，以 chrono 库中对时长的重载最得精髓。
    */
    this_thread::sleep_for(10ns); // 休眠 10 纳秒
    this_thread::sleep_for(10us); // 休眠 10 微秒
    this_thread::sleep_for(10ms); // 休眠 10 毫秒
    this_thread::sleep_for(10s);  // 休眠 10 秒
    this_thread::sleep_for(1min); // 休眠 1 分钟
    //this_thread::sleep_for(1h + 10min + 20s); // 休眠 1 小时 10 分钟 20 秒

    auto t1 = high_resolution_clock::now();
    cout << "all tests cost:" << duration_cast<milliseconds>(t1 - t0).count() << " msec\n";
}

int main()
{
    system_test();
    time_points_test();
    duration_test();
    suffix_test();

    return 0;
}
