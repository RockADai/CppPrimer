/*
* C++ Primer 练习8.4个人答案
* 将按行读取和按单词读取写在同一个文件中
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//#define INPUT_IN_LINE

using namespace std;

int main(){
    string ifile = "test.txt";
    vector<string> vec;
    ifstream input(ifile);
    if(input){
        string buf;
#ifdef INPUT_IN_LINE
        while(getline(input,buf))
            vec.push_back(buf);
#else
        while(input >> buf)
            vec.push_back(buf);
#endif
    }
    else
        cerr << "Failed." << endl;

    //Testing
    for(int i = 0;i < vec.size();i++)
        cout << vec[i] << endl;
    return 0;
}