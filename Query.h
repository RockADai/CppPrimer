/*
* C++ Primer 第五版中Query接口类实现
*/

#ifndef QUERY_H
#define QUERY_H

#include "TextQuery.h"

/*
* Query_base类实现
* 该类为抽象基类，具体的查询类型从该类派生，所有成员为private
*/

class Query;
class Query_base{
    friend class Query;
protected:
    using line_no = TextQuery::line_no;//用于eval函数
    virtual ~Query_base() = default;
private:
    virtual QueryResult eval(const TextQuery &) const = 0;//返回与当前Query匹配的QueryResult
    virtual string rep() const = 0;//rep是表示查询的一个string
};

/*
* Query类实现
* 该类为管理Query_base继承体系的接口类
*/

class Query{
    //~q返回一个Query对象，绑定到一个存放q的新NotQuery对象上
    friend Query operator~(const Query &);
    //q1|q2返回一个Query对象，绑定到一个存放q1和q2的新OrQuery对象上
    friend Query operator|(const Query &,const Query &);
    //q1&q2返回一个Query对象，绑定到一个存放q1和q2的新AndQuery对象上
    friend Query operator&(const Query &,const Query &);
public:
    Query(const string &);//构造一个新的WordQuery
    //接口函数：调用对应的Query_base操作
    QueryResult eval(const TextQuery &t) const{return q->eval(t);}
    string rep() const{return q->rep();}
private:
    Query(shared_ptr<Query_base> query):q(query){}
    shared_ptr<Query_base> q;
};

ostream &operator<<(ostream &os,const Query &query){
    //Query::rep通过Query_base指针对rep()进行虚调用
    return os << query.rep();
}

/*
* WordQuery类实现
* 查找一个给定的string，它是在给定的TextQuery对象上实际执行查询的唯一一个操作
*/

class WordQuery : public Query_base{
    friend class Query;//Query使用WordQuery构造函数
    WordQuery(const string &s):query_word(s){}
    //WordQuery是具体的类，将定义所有继承来的纯虚函数
    QueryResult eval(const TextQuery &t) const{return t.query(query_word);}
    string rep() const{return query_word;}
    string query_word;//要查找的单词
};

/*
* NotQuery类实现
* ~运算符生成一个NotQuery，其中保存一个需要取反的Query
*/

class NotQuery : public Query_base{
    friend Query operator~(const Query &);
    NotQuery(const Query &q):query(q){}
    //基类纯虚函数实现
    string rep() const{return "~("+query.rep()+")";}
    QueryResult eval(const TextQuery &) const;//返回运算对象的结果set中不存在的行
    Query query;
};

inline Query operator~(const Query &operand){
    return shared_ptr<Query_base>(new NotQuery(operand));
}

QueryResult NotQuery::eval(const TextQuery &text) const{
    //通过Query运算对象进行虚调用
    auto result = query.eval(text);
    //开始时结果set为空
    auto ret_lines = make_shared<set<line_no>>();
    //必须在运算对象出现的所有行中迭代
    auto beg = result.begin();
    auto end = result.end();
    //对于每一行，若该行不在result中，则添加到结果set
    auto sz = result.get_file()->size();
    for(size_t n = 0;n != sz;++n){
        //若还没处理完result所有行
        //检查当前行是否存在
        if(beg == end || *beg != n)
            ret_lines -> insert(n);//若不在result中则添加这一行
        else if(beg != end)
            ++beg;//否则如果有则继续获取下一行
    }
    return QueryResult(rep(),ret_lines,result.get_file());
}

/*
* BinaryQuery类实现
* 保存操作两个运算对象的查询类型所需的数据
*/

class BinaryQuery : public Query_base{
protected:
    BinaryQuery(const Query &l,const Query &r,string s):lhs(l),rhs(r),opSym(s){}
    //该类为抽象类不定义eval
    string rep() const{
        return "("+lhs.rep()+" "+opSym+" "+rhs.rep()+")";
    }
    Query lhs,rhs;//左侧和右侧运算对象
    string opSym;//运算符名字
};

/*
* AndQuery类实现
* 定义&运算符并操作两个运算对象
*/

class AndQuery : public BinaryQuery{
    friend Query operator&(const Query &,const Query &);
    AndQuery(const Query &left,const Query &right):BinaryQuery(left,right,"&"){}
    //AndQuery已继承rep，只需再定义eval
    QueryResult eval(const TextQuery &) const;//返回运算对象查询结果set的交集
};

inline Query operator&(const Query &lhs,const Query &rhs){
    return shared_ptr<Query_base>(new AndQuery(lhs,rhs));
}

QueryResult AndQuery::eval(const TextQuery &text) const{
    //通过Query成员lhs和rhs进行的虚调用，获取运算对象的查询结果set
    auto right = rhs.eval(text);
    auto left = lhs.eval(text);
    //保存left和right交集
    auto ret_lines = make_shared<set<line_no>>();
    //将两个范围的交集写入一个目的迭代器中
    //本次调用的目的迭代器向ret添加元素
    set_intersection(left.begin(),left.end(),
                    right.begin(),right.end(),inserter(*ret_lines,ret_lines->begin()));
    return QueryResult(rep(),ret_lines,left.get_file());
}

/*
* OrQuery类实现
* 定义|运算符并操作两个运算对象
*/

class OrQuery : public BinaryQuery{
    friend Query operator|(const Query &,const Query &);
    OrQuery(const Query &left,const Query &right):BinaryQuery(left,right,"|"){}
    //OrQuery已继承rep，只需再定义eval
    QueryResult eval(const TextQuery &) const;//返回运算对象查询结果set的并集
};

inline Query operator|(const Query &lhs,const Query &rhs){
    return shared_ptr<Query_base>(new OrQuery(lhs,rhs));
}

QueryResult OrQuery::eval(const TextQuery &text) const{
    //通过Query成员lhs和rhs进行的虚调用，返回每个运算对象的QueryResult
    auto right = rhs.eval(text);
    auto left = lhs.eval(text);
    //将左侧运算对象的行号拷贝到结果set中
    auto ret_lines = make_shared<set<line_no>>(left.begin(),left.end());
    //插入右侧运算对象所得的行号
    ret_lines->insert(right.begin(),right.end());
    //返回一个新的QueryResult，表示lhs和rhs的并集
    return QueryResult(rep(),ret_lines,left.get_file());
}

#endif
