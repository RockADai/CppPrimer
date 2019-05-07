/*
* C++ Primer 练习5.23-5.25答案
*/

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

int main(){
    int a,b;
    while(cin >> a >> b){
        try{
            if(b == 0)
                throw runtime_error("The second num is 0.\n");
            cout << static_cast<double>(a)/b << endl;
        }
        catch(runtime_error err)
        {
            cerr << err.what() << "try again." << endl;
        }
    }
    return 0;
}