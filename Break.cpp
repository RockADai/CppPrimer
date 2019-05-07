/*
* C++ Primer 练习5.20答案
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
    vector<string> strVec;
    string str,currStr;
    while(cin >> str){
        if(str == currStr){
            cout << "Repeat at: " << str << endl;
            break;
        }
        currStr = str;
    }
    cout << "Finish" << endl;
    return 0;
}