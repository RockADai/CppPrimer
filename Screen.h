#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Screen
{
public:
    typedef std::string::size_type pos;
    friend class Window_mgr;

    Screen() = default;
    Screen(pos ht,pos wd):height(ht),width(wd),contents(ht*wd,' '){}
    Screen(pos ht,pos wd,char c):height(ht),width(wd),contents(ht*wd,c){}
    ~Screen(){}

    char get() const{return contents[cursor];}
    inline char get(pos ht,pos wd) const;
    inline Screen &set(char);
    inline Screen &set(pos,pos,char);
    Screen &move(pos r,pos c);

    Screen &display(ostream &);
    const Screen &display(ostream &) const;
private:
    pos cursor = 0;
    pos height = 0,width = 0;
    string contents;
    void do_display(ostream &os) const{os << contents;}
};

class Window_mgr{
public:
    using ScreenIndex = vector<Screen>::size_type;
    void clear(ScreenIndex);
private:
    vector<Screen> screens{Screen(24,80,' ')};
};

#endif