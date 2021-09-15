#include <iostream>
#include <typeinfo> 
using namespace std;

int main(){

    int v1 = 1;
    cout << typeid(v1).name() << endl;

    char v2 = 'a';
    cout << typeid(v2).name() << endl;

    double v3 = 1;
    cout << typeid(v3).name() << endl;

    float v4 = 1.1;
    cout << typeid(v4).name() << endl;

    bool v5 = false; 
    cout << typeid(v5).name() << endl;

    unsigned int unint = 429496;
    cout << typeid(unint).name() << endl;
    string tmp;
    cin >> tmp;
    return 0;
}