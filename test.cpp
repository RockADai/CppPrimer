#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

class Test{
public:
    int val;
    Test(){cout << "默认构造" << endl;}
    Test(int m):val(m){cout << "构造" << endl;}
    Test(Test &t){
        val = t.val;
        cout << "拷贝构造" << endl;
    }
    Test &operator=(const Test &rhs){
        val = rhs.val;
        cout << "拷贝赋值运算符" << endl;
        return *this;
    }
    ~Test(){cout << "析构" << endl;}
};

int main(){
    Test t1;
    Test t2(1);
    Test t3(t2);
    t1 = t3;
    return 0;
}
