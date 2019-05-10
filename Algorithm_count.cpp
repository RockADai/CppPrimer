/*
* C++ Primer 第五版练习10.1，10.2答案
*/

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using namespace std;
//#define INT_TO_VECTOR

int main(){
    const int int_val = 12;//随意取给定值
    const string str_val = "fuck";
    vector<int> vec;
    list<string> ls;
    int n;
    string str;
#ifdef INT_TO_VECTOR
    while(cin >> n)
        vec.push_back(n);
    cout << count(vec.cbegin(),vec.cend(),int_val) << endl;
#else
    while(cin >> str)
        ls.push_back(str);
    cout << count(ls.cbegin(),ls.cend(),str_val) << endl;
#endif
    return 0;
}