#include <iostream>


int main(){
    int a=1, b=2, c=15;

    if (true){
        std::cout << "a=1,b=2,c=15\n\n";
        //and gate, 0001 & 1111 = 0001, or 1 & 15 = 1
        std::cout << "a & c: " << (a & c) << "\n";
        //or gate, 0001 | 0010 = 0011, or 1 | 2 = 3
        std::cout << "a | b: " << (a | b) << "\n";
        //xor gate (exclusive or), 0001 | 1111 = 1110, or 1 ^ 15 = 14
        std::cout << "a ^ c: " << (a ^ c) << "\n";
        //shift a two to the left, 0001 << 2 = 0100, or 1 << 2 = 4
        std::cout << "a << b: " << (a << b) << "\n";
        //shift a two to the right, 0001 >> 2 = 0000, or 1 >> 2 = 0
        std::cout << "a << b: " << (a >> b) << "\n";
        //not gate, ~00000010 = 11111101, or ~2 = overflow :sob:
        std::cout << "~b: " << (~b) << "\n";
    return 0;
    }
}
