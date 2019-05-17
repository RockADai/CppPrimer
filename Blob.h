/*
* C++ Primer 第五版中Blob类和Blobptr类实现
*/

#ifndef BLOB_H
#define BLOB_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;
class BlobPtr;

class Blob{
public:
    typedef vector<string>::size_type size_type;
    Blob();
    Blob(initializer_list<string> il);
    size_type size() const;
    bool empty() const;
    friend bool operator==(const Blob &,const Blob &);
    friend bool operator!=(const Blob &,const Blob &);
    ~Blob();
    //添加和删除元素
    void push_back(const string &t);
    void push_back(string &&);
    void pop_back();
    //访问元素
    string &front();
    string &back();

    friend class BlobPtr;
    BlobPtr begin();
    BlobPtr end();
private:
    shared_ptr<vector<string>> data;
    //若data[i]不合法，则抛出一个异常
    void check(size_type i,const string &msg) const;
};

class BlobPtr{
public:
    BlobPtr();
    BlobPtr(Blob &a,size_t sz = 0);
    friend bool operator==(const BlobPtr &,const BlobPtr &);
    friend bool operator!=(const BlobPtr &,const BlobPtr &);
    string &operator*() const;
    string *operator->() const;
    ~BlobPtr();
    
    string &deref() const;
    BlobPtr &incr();//前缀递增
private:
    shared_ptr<vector<string>> check(size_t,const string&) const;
    weak_ptr<vector<string>> wptr;
    size_t curr;
};

//Blob类
Blob::Blob():data(make_shared<vector<string>>()){}

Blob::Blob(initializer_list<string> il):data(make_shared<vector<string>>(il)){}

Blob::size_type Blob::size() const{
    return data->size();
}

bool Blob::empty() const{
    return data->empty();
}

bool operator==(const Blob &lhs,const Blob &rhs){
    return lhs.data == rhs.data;
}

bool operator!=(const Blob &lhs,const Blob &rhs){
    return !(lhs == rhs);
}

string &BlobPtr::operator*() const{
    auto p = check(curr,"dereference past end");
    return (*p)[curr];
}

string *BlobPtr::operator->() const{
    return &this->operator*();
}

Blob::~Blob(){}

void Blob::push_back(const string &t){
    data->push_back(t);
}

void Blob::push_back(string &&s){
    data->push_back(move(s));
}

void Blob::pop_back(){
    check(0,"pop_back on empty Blob");
    data->pop_back();
}

string &Blob::front(){
    check(0,"front on empty Blob");//若vector为空，抛出一个异常
    return data->front();
}

string &Blob::back(){
    check(0,"back on empty Blob");
    return data->back();
}

void Blob::check(size_type i,const string &msg) const{
    if(i >= data->size())
        throw out_of_range(msg);
}

BlobPtr Blob::begin(){
    return BlobPtr(*this);
}

BlobPtr Blob::end(){
    auto ret = BlobPtr(*this,data->size());
    return ret;
}

//BlobPtr类
BlobPtr::BlobPtr():curr(0){}

BlobPtr::BlobPtr(Blob &a,size_t sz = 0):wptr(a.data),curr(sz){}

bool operator==(const BlobPtr &lhs,const BlobPtr &rhs){
    return lhs.curr == rhs.curr;
}

bool operator!=(const BlobPtr &lhs,const BlobPtr &rhs){
    return !(lhs == rhs);
}

BlobPtr::~BlobPtr(){}

string &BlobPtr::deref() const{
    auto p = check(curr,"dereference past end");
    return (*p)[curr];
}

BlobPtr &BlobPtr::incr(){
    check(curr,"increment past end of BlobPtr");
    ++curr;
    return *this;
}

shared_ptr<vector<string>> BlobPtr::check(size_t i,const string &msg) const{
    auto ret = wptr.lock();
    if(!ret)//底层vector是否存在
        throw runtime_error("unbound BlobPtr");
    if(i >= ret->size())//是否允许递增
        throw out_of_range(msg);
    return ret;
}

#endif
