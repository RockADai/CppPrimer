#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Date{
private:
    unsigned year;
    unsigned month;
    unsigned day;
public:
    Date();
    Date(string date_str);
    ~Date();
    void show();
};

#endif
