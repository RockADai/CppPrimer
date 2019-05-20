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

/*
* Blob类实现，使用模板方式
*/
template <typename> class BlobPtr;
template <typename T>
class Blob{
    friend class BlobPtr<T>;
    friend bool operator==<T>(const Blob<T> &,const Blob<T> &);
public:
    typedef typename vector<T>::size_type size_type;
    Blob();
    Blob(initializer_list<T> il);
    size_type size() const{return data->size();}
    bool empty() const{return data->empty();}
    //添加和删除元素
    void push_back(const T &t){data->push_back(t);}
    void push_back(T &&t){data->push_back(move(t));}//移动版本
    void pop_back();
    //访问元素
    T &back();
    T &operator[](size_type i);
private:
    shared_ptr<vector<T>> data;
    //若data[i]无效则抛出msg
    void check(size_type i,const string &msg) const;
};

template <typename T>
bool operator==<T>(const Blob<T> &lhs,const Blob<T> &rhs){
    return lhs.data == rhs.data;
}

template <typename T>
Blob<T>::Blob():data(make_shared<vector<T>>()){}

template <typename T>
Blob<T>::Blob(initializer_list<T> il):data(make_shared<vector<T>>(il)){}

template <typename T>
void Blob<T>::pop_back(){
    check(0,"pop_back on empty Blob");
    data->pop_back();
}

template <typename T>
T &Blob<T>::back(){
    check(0,"back on empty Blob");
    return data->back();
}

template <typename T>
T &Blob<T>::operator[](size_type i){
    check(i,"subscript out of range");
    return (*data)[i];
}

template <typename T>
void Blob<T>::check(size_type i,const string &msg) const{
    if(i >= data->size())
        throw out_of_range(msg);
}

/*
* BlobPtr类实现，使用模板方式
*/

template <typename T>
class BlobPtr{
public:
    BlobPtr():curr(0){}
    BlobPtr(Blob<T> &a,size_t sz = 0):wptr(a.data),curr(sz){}
    T &operator*() const{
        auto p = check(curr,"dereference past end");
        return (*p)[curr];//*p为本对象指向的vector
    }
    //递增和递减
    BlobPtr &operator++();//前置运算符
    BlobPtr &operator--();
private:
    //若检查成功，返回一个指向vector的shared_ptr
    shared_ptr<vector<T>> check(size_t,const string &) const;
    //保存一个weak_ptr，表示底层vector可能被销毁
    weak_ptr<vector<T>> wptr;
    size_t curr;//数组中当前位置
};

//后置：递增/递减对象但返回原值
template <typename T>
BlobPtr<T> &BlobPtr<T>::operator++(){
    //此处无需检查，调用前置递增时会检查
    BlobPtr ret = *this;//保存当前值
    ++*this;//推进1个元素，前置++检查递增是否合法
    return ret;//返回保存状态
}

template <typename T>
BlobPtr<T> &BlobPtr<T>::operator--(){
    //此处无需检查，调用前置递减时会检查
    BlobPtr ret = *this;//保存当前值
    --*this;//回推1个元素，前置--检查递减是否合法
    return ret;//返回保存状态
}

template <typename T>
shared_ptr<vector<T>> BlobPtr<T>::check(size_t i,const string &msg) const{
    auto ret = wptr.lock();
    if(!ret)//底层vector是否存在
        throw runtime_error("unbound BlobPtr");
    if(i >= ret->size())//是否允许递增
        throw out_of_range(msg);
    return ret;
}

#endif
