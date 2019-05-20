/*
* C++ Primer 第五版中DebugDelete类实现
* 在TextQuery程序中作为删除器使用
*/

#ifndef DEBUGDELETE_H
#define DEBUGDELETE_H

#include <iostream>

class DebugDelete{
public:
    DebugDelete(std::ostream &s = std::cerr):os(s){}
    template <typename T>
    void operator()(T *p) const{
        os << "deleting..." << endl;
        delete p;
    }
private:
    std::ostream &os;
};

#endif
