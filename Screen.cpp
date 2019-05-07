/*
* C++ Primer 书中Screen类和Window_mgr类实现
*/

#include "Screen.h"

inline char Screen::get(pos r,pos c) const{
    pos row = r*width;
    return contents[row+c];
}

Screen &Screen::move(pos r,pos c){
    pos row = r*width;
    cursor = row+c;
    return *this; 
}

inline Screen &Screen::set(char c){
    contents[cursor] = c;
    return *this;
}

inline Screen &Screen::set(pos r,pos col,char ch){
    contents[r*width+col] = ch;
    return *this;
}

Screen &Screen::display(ostream &os){
    do_display(os);
    return *this;
}
const Screen &Screen::display(ostream &os) const{
    do_display(os);
    return *this;
}


void Window_mgr::clear(ScreenIndex i){
    Screen &s = screens[i];
    s.contents = string(s.height*s.width,' ');
}