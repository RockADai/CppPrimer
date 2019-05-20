/*
* C++ Primer 书中Screen类和Window_mgr类实现
*/

#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <string>

using namespace std;

struct XYC{
    int x = 0;
    int y = 0;
    char c = ' ';
};

template <unsigned N,unsigned M>
class Screen{
public:
    Screen() = default;
    Screen(char c):contents(N*M,c){}

    char get() const{return contents[cursor];}
    Screen set(XYC c){
        cursor = --c.x*width+(--c.y);
        contents[cursor] = c.c;
        return *this;
    }
    template <unsigned NN,unsigned MM>
    friend ostream &operator<<(ostream &os,const Screen<NN,MM> &s);
    template <unsigned NN,unsigned MM>
    friend istream &operator>>(istream &is,Screen<NN,MM> &s);
private:
    unsigned cursor = 0;
    unsigned width = N;
    unsigned height = M;
    string contents;
};

template <unsigned NN,unsigned MM>
ostream &operator<<(ostream &os,const Screen<NN,MM> &s){
    for(unsigned i = 0;i < s.width;i++){
        for(unsigned j = 0;j < s.height;j++)
            putchar(s.contents[i*s.width+j]);
        putchar('\n');
    }
    return os;
}
template <unsigned NN,unsigned MM>
istream &operator>>(istream &is,Screen<NN,MM> &s){
    XYC c;
    is >> c;
    s.set(c);
    return is;
}

#endif
