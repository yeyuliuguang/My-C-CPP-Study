#include <iostream>
using namespace std;

class My
{

    // 私有
private:
    /* data */

    // 公有
public:
    int a;
    My(/* args */);
    ~My();
};

// 类初始化
My::My(/* args */)
{
    this->a = 10;
}
//析构函数
My::~My()
{
}

int main()
{
    My my; // 类的实例化
    int result=*(int *)&my; // 先取实例my的内存地址,在转化为int类型的指针,然后用 * 运算符取得该地址对应的值
    cout << "my :" << result << endl;

    return 0;
}