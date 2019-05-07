#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{
private:
    string name;//人员姓名
    string address;//人员住址
public:
    Person() = default;
    Person(string,string);
    Person(istream&);
    ~Person();

    string const get_name();
    string const get_address();
    //应声明成const函数，使内部变量只能被访问，不能被修改

    ostream &print(ostream&,const Person&);
    istream &read(istream&,Person&);
    //读/写Person对象
};

#endif
