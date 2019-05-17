/*
* C++ Primer 练习7.4、7.5答案，Person类的声明在Person.h文件中
* 增加了练习7.9的答案
* 按照练习7.15添加了构造函数
*/

#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person{
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

Person::Person(string name,string address):name(name),address(address){}

Person::Person(istream &is){
    read(is,*this);
}

Person::~Person(){}

string const Person::get_name(){
    return name;
}

string const Person::get_address(){
    return address;
}

ostream &Person::print(ostream &os,const Person &per){
    os  << per.name << per.address;
    return os;
}

istream &Person::read(istream &is,Person &per){
    is  >> per.name >> per.address;
    if(is)
        per = Person();//若检测到IO对象则读取并构造成Person对象
    return is;
}

#endif
