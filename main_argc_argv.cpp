/*
* C++ Primer 练习6.25答案
*/
#include <iostream>
#include <string>

using namespace std;

int main(int argc,char **argv){
    string output;
    for(int i = 1;i != argc;i++){
        output += argv[i];
        output += " ";
    }
    cout << output << endl;
    return 0;
}