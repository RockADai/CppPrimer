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
    ~Blob();
    //添加和删除元素
    void push_back(const string &t);
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
    ~BlobPtr();
    
    string &deref() const;
    BlobPtr &incr();//前缀递增
private:
    shared_ptr<vector<string>> check(size_t,const string&) const;
    weak_ptr<vector<string>> wptr;
    size_t curr;
};

#endif
