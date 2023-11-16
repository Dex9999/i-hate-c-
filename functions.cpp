#include <iostream>
int main(){
    int input = 0;
    do{
        std::cout << "Please enter a number between ";
        std::cout << "10 and 15";
        std::cin >> input;
    } while (10>input||input>15);
    std::cout << "thanks";
}
