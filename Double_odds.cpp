/*
* C++ Primer 练习4.21答案
*/

#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(){
    vector<int> v;
    int n;
    while(cin >> n)
        v.push_back(n);
    for(auto it = v.begin();it != v.end();++it){
        if(*it%2 == 1)
            *it = *it*2;
        cout << *it << ", ";
    }
    cout << endl;
    return 0;
}