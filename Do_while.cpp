/*
* C++ Primer 练习5.19答案
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
    
    do{
        string str1,str2;
        cout << "Please input two strings: " << endl;
        cin >> str1 >> str2;
        if(str1.length() > str2.length())
            cout << "The shorter one is: " << str2 << endl;
        else
            cout << "The shorter one is: " << str1 << endl;
    }while(cin);
    return 0;
}