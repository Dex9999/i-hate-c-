#include <iostream>

int main(){
    int test = 32;

    while(true){
    std::cout << "char�" << test << ": " << (char)test << "\n";
    ++test;
    std::cin.ignore();
    }

}
