/*
* C++ Primer 练习3.20答案，两种计算方式写在同一个文件中
*/

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#define CHANGE_SUM

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(){
    vector<int> ivec;
    int n;
    while(cin >> n)
        ivec.push_back(n);
#ifndef CHANGE_SUM
    for(int i = 0;i < ivec.size()-1;i++)
        cout << ivec[i+1]+ivec[i] << " ";
#else
    for(int i = 0;i < ivec.size()/2;i++)
        cout << ivec[i]+ivec[ivec.size()-i-1] << " ";
#endif
    cout << endl;
    return 0;
}