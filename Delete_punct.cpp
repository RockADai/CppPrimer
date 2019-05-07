/*
* C++ Primer ç»ƒä¹ 3.10ç­”æ¡ˆ
*/

#include <iostream>
#include <string>
#include <cctype>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(){
    string str;
    cin >> str;
    int num = str.size();
    for(int i = 0;i < num;i++){
        if(!ispunct(str[i]))
            cout << str[i];
    }
    return 0;
}