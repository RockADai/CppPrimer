/*
* C++ Primer 第五版中Token类实现
* 该类用于管理匿名union
*/

#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

class Token{
public:
    //因为union含有一个string成员，所以Token必须定义拷贝控制
    Token():tok(INT),ival{0}{}
    Token(const Token &t):tok(t.tok){copyUnion(t);}
    Token &operator=(const Token &);
    //如果union含有一个string成员则必须进行销毁
    ~Token(){
        if(tok == STR)
            sval.~basic_string();
    }
    //以下赋值运算符负责设置union的不同成员
    Token &operator=(const std::string &);
    Token &operator=(char);
    Token &operator=(int);
    Token &operator=(double);
private:
    enum {INT,CHAR,DBL,STR} tok;//判别式
    union{
        char cval;
        int ival;
        double dval;
        std::string sval;
    };//每个Token对象含有一个该未命名union类型的未命名成员
    void copyUnion(const Token &);//检查判别式并酌情拷贝union成员
};

Token &Token::operator=(const std::string &s){
    if(tok == STR)//若当前存储为string可直接赋值
        sval = s;
    else
        new(&sval) std::string(s);//否则先构建一个string
    tok = STR;
    return *this;
}

Token &Token::operator=(int i){
    if(tok == STR)
        sval.~basic_string();
    ival = i;
    tok = INT;
    return *this;
}

Token &Token::operator=(char c){
    if(tok == STR)
        sval.~basic_string();
    cval = c;
    tok = CHAR;
    return *this;
}

Token &Token::operator=(double d){
    if(tok == STR)
        sval.~basic_string();
    dval = d;
    tok = DBL;
    return *this;
}

Token &Token::operator=(const Token &t){
    //若此对象值为string,而t不是，则必须释放原来的string
    if(tok == STR && t.tok != STR)
        sval.~basic_string();
    if(tok == STR && t.tok == STR)
        sval = t.sval;
    t.tokt.tok
    return *sl
}

#endif
