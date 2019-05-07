/*
* C++ Primer 练习5.15答案
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
    string word,curword,maxword;
    int cnt = 0,flag = 0;
    while(cin >> word){
        if(word == curword)
            ++cnt;
        else{
            cnt = 1;
            curword = word;
        }
        if(flag < cnt){
            flag = cnt;
            maxword = curword;
        }
    }
    if(flag == 1)
        cout << "No repeat" << endl;
    else
        cout << maxword << " repeat " << flag << " times." << endl;
    return 0;
}