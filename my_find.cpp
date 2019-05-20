/*
* C++ Primer 第五版练习16.4答案
*/

#include <iostream>
#include <vector>
#include <list>
#include <string>

#define USE_VECTOR
using namespace std;

template <typename T_iter,typename T_val>
T_iter my_find(T_iter first,T_iter last,const T_val &val){
    for( ;first != last;first++)//遍历迭代器区间
        if(*first == val)//标准库容器重载了==运算符，此处可直接比较
            break;
    return first;//返回找到的第一个值为val的位置，若未找到则返回区间最末尾元素
}

//测试入口
int main(){
    const vector<int> vec{1,1,2,2,2,3,4,5,6,10,17,17,17};//测试用例1
    const list<string> ls{"fuck","you","code","son","of","a","bitch"};//测试用例2
#ifdef USE_VECTOR
    cout << *(my_find(vec.begin(),vec.end(),10)) << endl;
#else
    cout << *(my_find(ls.begin(),ls.end(),"cod")) << endl;
#endif
    return 0;
}