#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

int main(){
    string str;
    cin >> str;
    char *p = new char[1];
    strcpy(p,str.c_str());
    cout << p << endl;
    delete [] p;
    return 0;
}
