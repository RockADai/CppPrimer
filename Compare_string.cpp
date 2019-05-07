/*
* C++ Primer 练习3.4个人答案，在同一个文件中改写
*/

#include <iostream>
#include <string>

//#define COMPARE_LETTER

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(){
    string s1,s2;
    cin >> s1 >> s2;
#ifdef COMPARE_LETTER
    if(s1 == s2)
        return 0;
    else
        s1 > s2 ? (cout << s1 << endl) : (cout << s2 << endl);
#else
    if(s1.size() == s2.size())
        return 0;
    else
        s1.size() > s2.size() ? (cout << s1 << endl) : (cout << s2 << endl);
#endif
    return 0;
}