#ifndef SALESDATA_H
#define SALESDATA_H

#include <iostream>
#include <string>

using namespace std;

class Sales_data{
public:
    Sales_data() = default;
    Sales_data(const string&);
    Sales_data(const string&,unsigned,double);
    Sales_data(istream&);

    string isbn() const;//获取isbn书号
    Sales_data& combine(const Sales_data&);
    inline double avg_price() const;//计算平均价格

    Sales_data add(const Sales_data&,const Sales_data&);//计算两笔交易的和
    ostream &print(ostream&,const Sales_data&);//输出交易数据
    istream &read(istream&,Sales_data&);//读入交易数据
    bool compareIsbn(Sales_data s1,Sales_data s2);//s1的isbn小于s2时返回true
private:
    string bookNo;//图书编号
    unsigned units_sold = 0;//售出件数
    double revenue = 0.0;//收入
};

#endif
