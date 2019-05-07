#include <iostream>
#include "Sales_item.h"

/*
* C++ Primer第1章最后的Sales_item系列练习
*/

int main(){
    Sales_item book,currBook;
    if(std::cin >> currBook){
        int cnt = 1;
        while(std::cin >> book){
            if(compareIsbn(book,currBook))
                ++cnt;
            else{
                std::cout << currBook.isbn() << " " << cnt << std::endl;
                currBook = book;
                cnt = 1;
            }
        }
    }
    return 0;
}