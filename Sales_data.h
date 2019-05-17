/*
* C++ Primer 书中Sales_data类实现
*/

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

    friend ostream &operator<<(ostream &,const Sales_data &);
    friend istream &operator>>(istream &,Sales_data &);
    friend Sales_data &operator+(const Sales_data &,const Sales_data &);
    Sales_data &operator+=(const Sales_data &);//其余复合赋值运算符与该重载运算符相似

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

Sales_data::Sales_data(const string &s):bookNo(s){}

Sales_data::Sales_data(const string &s,unsigned n,double p):bookNo(s),units_sold(n),revenue(p*n){}

Sales_data::Sales_data(istream &is){
    read(is,*this);
}

ostream &operator<<(ostream &out,const Sales_data &rhs){
    out << rhs.bookNo << '\t' << rhs.units_sold << '\t' 
        << rhs.revenue << '\t' << rhs.avg_price();
    return out;
}

istream &operator>>(istream &in,Sales_data &rhs){
    double price;
    in >> rhs.bookNo >> rhs.units_sold >> price;
    if(in)
        rhs.revenue = rhs.units_sold*price;
    else
        rhs = Sales_data();
    return in;
}

Sales_data &operator+(const Sales_data &lhs,const Sales_data &rhs){
    Sales_data ret(lhs);
    ret += lhs;
    return ret;
}

Sales_data &Sales_data::operator+=(const Sales_data &rhs){
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

string Sales_data::isbn() const{
    return bookNo;
}

Sales_data& Sales_data::combine(const Sales_data &rhs){
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

inline double Sales_data::avg_price() const{
    if(units_sold)
        return revenue/units_sold;
    else
        return 0;
}

Sales_data Sales_data::add(const Sales_data &lhs,const Sales_data &rhs){
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

ostream &Sales_data::print(ostream &os,const Sales_data &item){
    os  << item.isbn() << " " << item.units_sold << " " 
        << item.revenue << " " << item.avg_price();
    return os;
}

istream &Sales_data::read(istream &is,Sales_data &item){
    double price = 0;
    is  >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

bool compareIsbn(Sales_data s1,Sales_data s2){
    return s1.isbn().size() < s2.isbn().size();
}

#endif
