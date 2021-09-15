#include <iostream>
using namespace std;

int main()
{
    int arr[] = {0};
    struct Book{  // Book是结构体类型名
        char title[50];
        char author[50];
        char subject[100];
        int book_id;
    };

    enum DAY
    {
      MON=1, TUE, WED, THU, FRI, SAT, SUN
    };

    auto autotmp = 100;

    cout << "bool   : " << typeid(bool).name() << endl;
    cout << "char   : " << typeid(char).name() << endl;
    cout << "short  : " << typeid(short).name() << endl;
    cout << "int    : " << typeid(int).name() << endl;
    cout << "long   : " << typeid(long).name() << endl;
    cout << "float  : " << typeid(float).name() << endl;
    cout << "double : " << typeid(double).name() << endl;
    cout << "void*  : " << typeid(void*).name() << endl;
    cout << "array  : " << typeid(arr).name() << endl;
    cout << "struct : " << typeid(Book).name() << endl;
    cout << "enum : " << typeid(DAY).name() << endl;

    return 0;
}