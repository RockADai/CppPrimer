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
private:
    string sought;//查询单词
    shared_ptr<set<TextQuery::line_no>> lines;//出现的行号
    shared_ptr<vector<string>> file;//输入文件
};

#endif
