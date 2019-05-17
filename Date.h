/*
* C++ Primer 练习9.51中Date类实现
*/

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

Date::Date():year(0),month(0){}

Date::Date():year(0),month(0),day(0){}

Date::Date(string date_str){
    if(!date_str.empty()){
        auto pos = date_str.find_last_of("1234567890");
        year = stoul(date_str.substr(pos-3));//从后向前获取年份
        date_str.erase(pos-3);
        if(date_str.find_first_of("ADFJMNOS") != string::npos){
            day = stoul(date_str.substr(date_str.find_first_of("1234567890")));//获取天数
            string str(date_str,0,3);//拷贝输入的前三个字符
            switch (date_str[0])//switch判断处理月份
            {
            case 'J':
                if(str == "Jan")
                    month = 1;
                else if(str == "Jun")
                    month = 6;
                else
                    month = 7;
                break;
            case 'F':
                month = 2;
                break;
            case 'M':
                if(str == "Mar")
                    month = 3;
                else
                    month = 5;
            case 'A':
                if(str == "Apr")
                    month = 4;
                else
                    month = 8;
            case 'S':
                month = 9;
            case 'O':
                month = 10;
            case 'N':
                month = 11;
            case 'D':
                month = 12;
            default:
                break;
            }
        }//处理January 1,1900和Jan 1 1900两种情形
        else{
            month = stoul(date_str);
            if(month > 9)
                day = stoul(date_str.substr(3));
            else
                day = stoul(date_str.substr(2));
        }//处理1/1/1900情形
    }
}

Date::~Date(){}

void Date::show(){
    cout << "Year: " << year << "\t"
         << "Month: " << month << "\t"
         << "Day: " << day << " .";
}

#endif
