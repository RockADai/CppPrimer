#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>

using namespace std;

class Employee{
public:
    Employee();
    Employee(string &);
    Employee(const Employee &) = delete;//Employee对象不应该完全相同，禁止拷贝
    Employee &operator=(const Employee &) = delete;
private:
    string name;
    unsigned ID_num;
    static int flag;
};

#endif
