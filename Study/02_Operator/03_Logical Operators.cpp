#include <iostream>
using namespace std;

int main()
{
    int a = 5;
    int b = 20;

    // 逻辑与运算符。如果两个操作数都非零，则条件为真。
    if (a && b)
    {
        cout << "Line 1 - 条件为真" << endl;
    }

    // 逻辑或运算符。如果两个操作数中有任意一个非零，则条件为真。
    if (a || b)
    {
        cout << "Line 2 - 条件为真" << endl;
    }
    
     /* 改变 a 和 b 的值 */
    a = 0;
    b = 10;
    if (a && b)
    {
        cout << "Line 3 - 条件为真" << endl;
    }
    else
    {
        cout << "Line 4 - 条件不为真" << endl;
    }

    // 逻辑非运算符。用来逆转操作数的逻辑状态。如果条件为真则逻辑非运算符将使其为假。
    if (!(a && b))
    {
        cout << "Line 5 - 条件为真" << endl;
    }

    return 0;
}