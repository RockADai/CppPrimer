/*
* C++ Primer 第五版中Basket类实现
*/

#ifndef BASKET_H
#define BASKET_H

#include "Quote.h"

class Basket{
public:
    //使用合成的默认构造函数和拷贝控制成员
    void add_item(const shared_ptr<Quote> &);
    double total_receipt(ostream &) const;//打印每本书总价和购物篮中所有书总价
private:
    static bool compare(const shared_ptr<Quote> &lhs,const shared_ptr<Quote> &rhs){
        return lhs->isbn() < rhs->isbn();
    }//比较shared_ptr
    multiset<shared_ptr<Quote>,decltype(compare) *> items{compare};//保存多个报价，按compare排序
};

void Basket::add_item(const shared_ptr<Quote> &sale){
    items.insert(sale);
}

double Basket::total_receipt(ostream &os) const{
    double sum = 0.0;
    for(auto iter = items.cbegin();iter != items.cend();iter = items.upper_bound(*iter))
        sum += print_total(os,**iter,items.count(*iter));
    os << "Total Sale: " << sum << endl;
    return sum;
}

#endif
