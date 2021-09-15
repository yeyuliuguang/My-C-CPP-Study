#include <iostream>
using namespace std;

int main()
{
    int a = 21;
    int b = 10;


    // 比较相等,为真
    if (a == b)
    {
        cout << "Line 1 - a 等于 b" << endl;
    }

    // 比较不相等,为真
    if (a != b)
    {
        cout << "Line 2 - a 不等于 b" << endl;
    }

    // 小于为真
    if (a < b)
    {
        cout << "Line 2 - a 小于 b" << endl;
    }
    else
    {
        cout << "Line 2 - a 不小于 b" << endl;
    }

    // 大于为真
    if (a > b)
    {
        cout << "Line 3 - a 大于 b" << endl;
    }
    else
    {
        cout << "Line 3 - a 不大于 b" << endl;
    }

    /* 改变 a 和 b 的值 */
    a = 5;
    b = 20;

    // 小于或等于,为真
    if (a <= b)
    {
        cout << "Line 4 - a 小于或等于 b" << endl;
    }

    // 大于或等于,为真
    if (b >= a)
    {
        cout << "Line 5 - b 大于或等于 b" << endl;
    }
    return 0;
}