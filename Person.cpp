/*
* C++ Primer 练习7.4、7.5答案，Person类的声明在Person.h文件中
* 增加了练习7.9的答案
* 按照练习7.15添加了构造函数
*/

#include "Person.h"

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