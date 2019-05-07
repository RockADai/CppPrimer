/*
* C++ Primer 练习3.2个人答案，通过预编译处理
* 将一次读入整行和一次读入一个词写在同一个文件中
*/

#include <iostream>
#include <string>

//#define ONLY_WORD

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::getline;

int main(){
    string s;
#ifdef ONLY_WORD
    while(cin >> s)
        cout << s << endl;
#else
    while(getline(cin,s))
        cout << s << endl;
#endif
    return 0;
}