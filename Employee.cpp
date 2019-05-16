/*
* C++ Primer 第五版练习13.18，13.19中Employee类实现
*/

#include "Employee.h"

extern int Employee::flag = 0;

Employee::Employee(){ID_num = flag++;}

Employee::Employee(string &s):name(s){ID_num = flag++;}
