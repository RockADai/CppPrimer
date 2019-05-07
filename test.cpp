#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool find(vector<int>::iterator,vector<int>::iterator,int);

int main(){
    const char ca[] = {'h','e','l','l','o'};
    const char *cp = ca;
    while(*cp){
        cout << *cp <<endl;
        ++cp;
    }
    return 0;
}

bool find(vector<int>::iterator iter1,vector<int>::iterator iter2,int target){
    for(iter1;iter1 != iter2;iter1++)
        if(*iter1 == target)
            return true;
    return false;  
}