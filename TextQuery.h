/*
* C++ Primer 第五版中TextQuery类和QueryResult类实现
*/

#ifndef TEXTQUERY_H
#define TEXTQUERY_h

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class QueryResult;
class TextQuery{
public:
    using line_no = vector<string>::size_type;
    TextQuery(ifstream &);
    QueryResult query(const string &) const;
private:
    shared_ptr<vector<string>> file;//输入文件
    map<string,shared_ptr<set<line_no>>> wm;//每个单词到其所在行号的集合的映射
};

class QueryResult{
    friend ostream &print(ostream &,const QueryResult &);
public:
    QueryResult(string,shared_ptr<set<TextQuery::line_no>>,shared_ptr<vector<string>>);
    set<TextQuery::line_no>::iterator begin() const{return lines->begin();}
    set<TextQuery::line_no>::iterator end() const{return lines->end();}
    shared_ptr<vector<string>> get_file() const{return make_shared<vector<string>>(file);}

private:
    string sought;//查询单词
    shared_ptr<set<TextQuery::line_no>> lines;//出现的行号
    shared_ptr<vector<string>> file;//输入文件
};

TextQuery::TextQuery(ifstream &is){
    string text;
    while(getline(is,text)){//对于每一行
        file->push_back(text);//保存此行文本
        int n = file->size()-1;//当前行号
        istringstream line(text);//将行文本分解为单词
        string word;
        while(line >> word){//对于每个单词
            //如果单词不在wm中，以该词为下标在wm中添加一项
            auto &lines = wm[word];//lines的类型是shared_ptr
            if(!lines)
                lines.reset(new set<line_no>);//分配一个新的set
            lines->insert(n);//将行号插入set
        }
    }
}

QueryResult TextQuery::query(const string &sought) const{
    //若未找到sought，返回一个指向此set的指针
    static shared_ptr<set<TextQuery::line_no>> nodata(new set<TextQuery::line_no>);
    //使用find查找单词而非下标运算符，防止将单词添加到wm中
    auto loc = wm.find(sought);
    if(loc == wm.end())
        return QueryResult(sought,nodata,file);//未找到
    else
        return QueryResult(sought,loc->second,file);
}

QueryResult::QueryResult(   string s,
                            shared_ptr<set<TextQuery::line_no>> p,
                            shared_ptr<vector<string>> f):
    sought(s),lines(p),file(f){}

string make_plural(size_t ctr,const string &word,const string &ending){
    return (ctr == 1) ? word : word+ending;
}//输入文本中ctr大于1时word加复数

ostream &print(ostream &os,const QueryResult &qr){
    //若找到单词，打印出现次数和所有出现的位置
    os  << qr.sought << " occurs " << qr.lines->size() << " "
        << make_plural(qr.lines->size(),"time","s") << endl;
    //打印单词出现的每一行
    for(auto num : *qr.lines)//对set中每个单词
        //避免行号从0开始
        os << "\t(line " << num+1 << ")" << *(qr.file->begin()+num) << endl;
    return os;
}

#endif
