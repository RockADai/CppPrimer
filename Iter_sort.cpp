/*
* C++ Primer 第五版练习10.31答案
*/

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int main(){
    vector<int> vec;
    istream_iterator<int> str(cin),end;
    unique_copy(str,end,back_inserter(vec));
    sort(vec.begin(),vec.end());
    for(int i = 0;i < vec.size();i++)
        cout << vec[i] << " ";
    cout << endl;
    return 0;
}