/*
* C++ Primer 第五版练习，实现Message类和Folder类
*/

#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <string>
#include <set>

using namespace std;

class Message{
    friend class Folder;
    friend void swap(Message &,Message &);
public:
    explicit Message(const string &);
    Message(const Message &);
    Message(Message &&);
    Message &operator=(const Message &);
    ~Message();

    void save(Folder &);//从指定Folder中添加Message
    void remove(Folder &);//从指定Folder中删除Message
    void move_Folders(Message *);//从本Message移动Folder指针
private:
    string contents;//实际消息文本
    set<Folder*> folders;//包含本Message的Folder
    //拷贝控制使用的工具函数
    //将本Message添加到指向参数的Folder中
    void add_to_Folders(const Message &);
    //从folders中每个Folder删除本Message
    void remove_from_Folders();
};

class Folder{
public:
    Folder();
    Folder(const Folder &);
    ~Folder();
    Folder &operator=(const Folder &);

    void addMsg(Message *);//上面需要用this作为参数，故此处使用指针
    void remMsg(Message *);
private:
    set<Message *> messages;
};

//Message类实现
Message::Message(const string &str = ""):contents(str){}

Message::Message(const Message &m):contents(m.contents),folders(m.folders){
    add_to_Folders(m);//将新创建的Message对象的指针添加到每个包含原Message的Folder中
}

Message::Message(Message &&m):contents(std::move(m.contents)){
    move_Folders(&m);
}

Message &Message::operator=(const Message &rhs){
    //通过先删除指针再插入它们来处理自赋值情况
    remove_from_Folders();//更新已有Folder
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_Folders(rhs);//添加本Message
    return *this;
}

Message::~Message(){
    remove_from_Folders();//确保没有任何Folder保存正在销毁的Message的指针
}

void Message::save(Folder &f){
    folders.insert(&f);//添加给定Folder到Folder列表
    f.addMsg(this);//将本Message添加到f的Message集合中
}

void Message::remove(Folder &f){
    folders.erase(&f);//从Folder列表中删除给定Folder
    f.remMsg(this);//将本Message从f的Message集合中删除
}

void Message::add_to_Folders(const Message &m){
    for(auto f : m.folders)//对每个包含m的Folder
        f->addMsg(this);//添加一个指向本Message的指针
}

void Message::remove_from_Folders(){
    for(auto f : folders)//对folders每个指针
        f->remMsg(this);//从该Folder删除本Message
}

void Message::move_Folders(Message *m){
    folders = std::move(m->folders);//使用set的移动赋值运算符
    for(auto f : folders){//对每个Folder
        f->remMsg(m);//从Folder中删除旧Message
        f->addMsg(this);//将本Message添加到Folder中
    }
    m->folders.clear();//确保销毁m是无害的
}

//自定义swap函数实现
void swap(Message &lhs,Message &rhs){
    using std::swap;
    //将每个消息的指针从所在Folder中删除
    for(auto f : lhs.folders)
        f->remMsg(&lhs);
    for(auto f : rhs.folders)
        f->remMsg(&rhs);
    //交换contents和Folder指针set
    swap(lhs.folders,rhs.folders);
    swap(lhs.contents,rhs.contents);
    //将每个Message的指针添加到新Folder中
    for(auto f : lhs.folders)
        f->addMsg(&lhs);
    for(auto f : rhs.folders)
        f->addMsg(&rhs);
}

//Folder类实现
Folder::Folder(){}

Folder::Folder(const Folder &f):messages(f.messages){}

Folder::~Folder(){}

Folder &Folder::operator=(const Folder &rhs){
    messages = rhs.messages;
    return *this;
}

void Folder::addMsg(Message *m){
    messages.insert(m);
}

void Folder::remMsg(Message *m){
    messages.erase(m);
}

#endif
