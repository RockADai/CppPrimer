/*
* C++ Primer 第五版练习11.3，11.4答案
*/

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <cctype>
#include <algorithm>

using namespace std;

int main(){
    map<string,size_t> word_count;
    fstream input("test.txt");//任取一个输入流
    string word;
    while(input >> word){
        for(string::iterator str_iter = word.begin();str_iter != word.end();str_iter++)
            if(ispunct(*str_iter))
                str_iter = word.erase(str_iter);
            else
                *str_iter = tolower(*str_iter);
        ++word_count[word];
    }
    for(map<string,size_t>::iterator map_iter = word_count.begin();
            map_iter != word_count.end();map_iter++){
        cout << map_iter->first << " ";
        cout << map_iter->second << endl;
    }
    return 0;
}