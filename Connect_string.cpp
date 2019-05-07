/*
* C++ Primer 练习3.5个人答案，程序添加的空格前用！标记
*/

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(){
    string s;
    string sum;
    while(cin >> s)
        sum += s+"! ";
    cout << sum << endl;
    return 0;
}