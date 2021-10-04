#include <iostream>
 
using namespace std;
 
class person
{
private:
    int age;
public:
    person(int nAge)
    {
        this->age = nAge;
    }
 
    bool operator==(const person& ps)
    {
        if (this->age == ps.age)
        {
            return true;
        }
        return false;
    }
};
 
int main()
{
    person p1(10);
    person p2(10);
    cout << "对象p1所在的内存地址为:" << &p1 << endl;
    cout << "对象p2所在的内存地址为:" << &p2 << endl;
    
    if (p1 == p2)
    {
        cout << "p1 等于  p2." << endl;
 
    }
    else
    {
        cout << "p1 不等于 p2." << endl;
    }
    
    return 0;
}
 