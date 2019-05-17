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

#endif
