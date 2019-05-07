/*
* C++ Primer 练习3.17答案
*/

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(){
    vector<string> str_vector;
    string str;
    while(cin >> str)
        str_vector.push_back(str);
    for(int i = 0;i < str_vector.size();i++){
        for(int j = 0;j < str_vector[i].length();j++)
            str_vector[i][j] = toupper(str_vector[i][j]);
    }
    for(int i = 0;i < str_vector.size();i++)
        cout << str_vector[i] << " ";
    cout << endl;
    return 0;
}