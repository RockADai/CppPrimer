/*
* C++ Primer 第五版中Quote类实现
*/

#ifndef QUOTE_H
#define QUOTE_H

#include <iostream>
#include <string>

class Quote{
public:
    Quote() = default;
    Quote(const std::string &,double);
    std::string isbn() const;
    
    //以下函数需要动态绑定
    virtual double net_price(std::size_t) const;
    virtual void debug();
    virtual ~Quote() = default;
private:
    std::string bookNo;
protected:
    double price = 0.0;
};

Quote::Quote(const std::string &book,double sales_price):bookNo(book),price(sales_price){}

std::string Quote::isbn() const{
    return bookNo;
}

double Quote::net_price(std::size_t n) const{
    return n*price;
}

void Quote::debug(){
    std::cout << "In Quote class" << std::endl;
    std::cout << "ISBN:" << bookNo << std::endl;
    std::cout << "Price:" << price << std::endl;
}

#endif
