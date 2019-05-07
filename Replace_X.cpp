/*
* C++ Primer 练习3.6、3.8答案，
* 分别用范围for、while、for三种方式编写
*/

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(){
    string s;
    cin >> s;
    //for(char &c : s)
    //    c = 'X';
    int i = 0,num = s.size();
    //while(i < num){
    //   s[i] = 'X';
    //   i++;
    //}
    for(;i < num;i++)
        s[i] = 'X';
    cout << s << endl;
    return 0;
}

/*
* 总结：
* 范围for的确用起来更加方便，但三者对计算资源的占用程度其实相同
* 而while和for更稳定，不易出错
*/