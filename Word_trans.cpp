/*
* C++ Primer 第五版中单词转换map程序
*/

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

void word_transform(ifstream &map_file,ifstream &input);//单词转换函数
map<string,string> buildMap(ifstream &map_file);//读取指定文件，建立转换映射
const string &transform(const string &s,const map<string,string> &m);//生成转换文本

int main(){
    ifstream rule_file("trans_rule.txt");
    ifstream trans_file("word_trans_input.txt");
    word_transform(rule_file,trans_file);
    return 0;
}

void word_transform(ifstream &map_file,ifstream &input){
    auto trans_map = buildMap(map_file);//保存转换规则
    string text;
    while(getline(input,text)){//读取输入
        istringstream stream(text);//读取每个单词
        string word;
        bool firstword = true;//控制是否打印空格
        while(stream >> word){
            if(firstword)
                firstword = false;
            else
                cout << " ";
            cout << transform(word,trans_map);
        }
        cout << endl;
    }
}

map<string,string> buildMap(ifstream &map_file){
    map<string,string> trans_map;//保存转换规则
    string key;//要转换的单词
    string value;//替换后的内容
    //读取第一个单词存入key，行中剩余内容存入value
    while(map_file >> key && getline(map_file,value))
        if(value.size() > 1)//检查是否有转换规则
            trans_map[key] = value.substr(1);//跳过前导空格
        else
            throw runtime_error("No rule for "+key);
    return trans_map;
}

const string &transform(const string &s,const map<string,string> &m){
    auto map_it = m.find(s);
    if(map_it != m.cend())
        return map_it->second;//若单词在转换规则中则使用替换短语
    else
        return s;//否则返回原词
}