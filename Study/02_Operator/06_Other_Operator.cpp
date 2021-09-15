#include <iostream>
using namespace std;

int main()
{
   int a = 4;
   short b;
   double c;

   int *ptr;

   /* sizeof 运算符实例 */
   cout << "LLine 1 - 变量 a 的大小 = " << sizeof(a) << endl;
   cout << "LLine 2 - 变量 b 的大小 = " << sizeof(b) << endl;
   cout << "LLine 3 - 变量 c 的大小 = " << sizeof(c) << endl;

   /* & 和 * 运算符实例 */
   ptr = &a; /* 'ptr' 现在包含 'a' 的地址 */
   cout << "a 的值是" << a << endl;
   cout << "*ptr 的值是" << *ptr << endl;

   /* 三元运算符实例 */
   a = 10;
   // 如果条件为真 ? 则值为 X : 否则值为 Y
   b = (a == 1) ? 20 : 30;
   cout << "b 的值是 " << b << endl;

   b = (a == 10) ? 20 : 30;
   cout << "b 的值是 " << b << endl;

   return 0;
}