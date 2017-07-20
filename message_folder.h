#pragma once

#include <iostream>
#include <set>
#include <string>

using namespace std;

class Folder;
class Message
{
    friend void swap(Message& lhs, Message& rhs);
    friend class Folder;
public:
    explicit Message(const std::string &str = string()) :
        contents(str) {}
    // 拷贝构造函数
    Message(const Message&);
    // 拷贝赋值运算符
    Message& operator =(const Message&);
    // 析构函数
    ~Message();

    void save(Folder&); //从给定Folder集合中添加、删除本Message
    void remove(Folder*);

private:
    std::string contents;
    std::set<Folder*> folders;
    void add_to_Folders(const Message&);
    void remove_from_Folders();

    // 两个另外添加的、配合Folder类的辅助函数
    void addFldr(Folder*);
    //void remove(Folder&);
};

Message::Message(const Message& m) :
    contents(m.contents), folders(m.folders)
{
    add_to_Folders(m);
}
Message::~Message()
{
    remove_from_Folders();
}
Message& Message::operator =(const Message& m)
{
    remove_from_Folders();
    contents = m.contents;
    folders = m.folders;
    add_to_Folders(m);
    return *this;
}

class Folder
{
public:
    Folder() = default;
    Folder(const Folder&);
    Folder& operator =(const Folder&);
    ~Folder();
    // 将消息添加到、删除出 本Folder
    void remMsg(Message *m) { msgs.erase(m); }
    void addMsg(Message *m) { msgs.insert(m); }
    // 接口函数
    std::string& show()
    {
        for (auto msg : msgs)
            cout << msg->contents << " ";
        cout << endl;
    }
private:
    std::set<Message*> msgs;
    void add_to_Messages(const Folder&);
    void remove_from_Messages();
};
void Message::save(Folder &f) //从给定Folder集合中添加、删除本Message
{
    this->folders.insert(&f);
    f.addMsg(this);
}

// 将本Message添加到指向m的Folder中
void Message::add_to_Folders(const Message &m)
{
    for (auto f : m.folders)
        f->addMsg(this);   // 将本Message添加到此Folder中
}
void Message::remove_from_Folders()
{
    for (auto f : this->folders)
        f->remMsg(this);   // 从该Folder中删除本Messgae
}

void Message::addFldr(Folder* f)
{
    folders.insert(f);
}
void Message::remove(Folder *f)
{
    this->folders.erase(f);
    f->remMsg(this);
}


void Folder::add_to_Messages(const Folder &f)
{
    for (auto msg : f.msgs)
        msg->addFldr(this);
}
void Folder::remove_from_Messages()
{
    while (!msgs.empty())
        (*msgs.begin())->remove(this);
}
Folder::Folder(const Folder& f) : msgs(f.msgs)
{
    add_to_Messages(f);
}
Folder::~Folder()
{
    remove_from_Messages();
}
Folder& Folder::operator =(const Folder& f)
{
    remove_from_Messages();
    msgs = f.msgs;
    add_to_Messages(f);
    return *this;
}

void swap(Message& lhs, Message& rhs)
{
    using std::swap;
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);
    std::swap(lhs.contents, rhs.contents);  // 使用swap(string&, string&)
    std::swap(lhs.folders, rhs.folders);    // 使用swap(set&, set&)
    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}
