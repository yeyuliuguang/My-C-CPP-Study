#include <iostream>
using namespace std;

int main()
{

  // 算术运算符
  int a = 21;
  int b = 10;
  int c;
 
  // 加法
  c = a + b;
  cout << "Line 1 - c 的值是 " << c << endl;

  // 减法
  c = a - b;
  cout << "Line 2 - c 的值是 " << c << endl;

  // 乘法
  c = a * b;
  cout << "Line 3 - c 的值是 " << c << endl;

  // 除法
  c = a / b;
  cout << "Line 4 - c 的值是 " << c << endl;

  // 取模运算符，整除后，取余数
  c = a % b;
  cout << "Line 5 - c 的值是 " << c << endl;

  // 先赋值后自加1
  c = a++;
  cout << "Line 6 - c 的值是 " << c << endl;

  // 先赋值后自减1
  c = a--;
  cout << "Line 7 - c 的值是 " << c << endl;

  return 0;
}