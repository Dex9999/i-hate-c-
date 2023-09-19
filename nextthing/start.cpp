#include <iostream>

int main(){
    long long int number1 = 0;
    long long int number2 = 0;

    std::cout << "please pick a number: ";
    std::cin >> number1;
    std::cout << "\nenter one more please: ";
    std::cin >> number2;

    std::cout << "The sum of " << number1 << " and " << number2 << " is "<< number1+number2 << "!";
}
