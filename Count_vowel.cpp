/*
* C++ Primer 练习5.10(5.9)答案
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
    char val;
    int asum = 0,esum = 0,isum = 0,osum = 0,usum = 0;
    while(cin >> val){
        if(val == 'a' || val == 'A')
            ++asum;
        else if(val == 'e' || val == 'E')
            ++esum;
        else if(val == 'i' || val == 'I')
            ++isum;
        else if(val == 'o' || val == 'O')
            ++osum;
        else if(val == 'u' || val == 'U')
            ++usum;
    }
    cout << "a:" << asum << endl;
    cout << "e:" << esum << endl;
    cout << "i:" << isum << endl;
    cout << "o:" << osum << endl;
    cout << "u:" << usum << endl;
    return 0;
}