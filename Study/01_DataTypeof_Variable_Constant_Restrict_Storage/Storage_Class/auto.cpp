#include <iostream>
#include <limits>

using namespace std;

// 函数声明
void func(void);

// static 存储类
static int count = 10; /* 全局变量 */

int main()
{
    // 自 C++ 11 以来，auto 关键字用于两种情况：声明变量时根据初始化表达式自动推断该变量的类型、声明函数时函数返回值的占位符。
    auto f = 3.14;        //double
    auto s("hello");      //const char*
    auto z = new auto(9); // int*
    // auto x1 = 5, x2 = 5.0, x3 = 'r'; //错误，必须是初始化为同一类型

    cout << "f   : " << typeid(f).name() << endl;
    cout << "s   : " << typeid(s).name() << endl;
    cout << "z  : " << typeid(z).name() << endl;

    // register 存储类用于定义存储在寄存器中而不是 RAM 中的局部变量。这意味着变量的最大尺寸等于寄存器的大小（通常是一个词），且不能对它应用一元的 '&' 运算符（因为它没有内存位置）。
    // 寄存器只用于需要快速访问的变量，比如计数器。还应注意的是，定义 'register' 并不意味着变量将被存储在寄存器中，它意味着变量可能存储在寄存器中，这取决于硬件和实现的限制。
    register int miles = 10;
    cout << "register_miles : " << miles << endl;

    // 调用函数func
    func();

    return 0;
}

// 函数定义
void func(void)
{
    static int i = 5; // 局部静态变量
    std::cout << "全局变量 count 为 " << count << endl;
    std::cout << "局部变量 i 为 " << i << endl;
}