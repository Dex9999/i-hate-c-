#include <iostream>
#include <iomanip>
int main()
{
    double changeInput = 0;
    int change = 0;
    std::cout << "Enter the change needed: $";
    std::cin >> changeInput;
    change = changeInput*100;
    std::cout << "$" << changeInput << " or " << change << " cents is\n\n";
    std::cout << std::setw(13) << "100 bills: " << change/10000 << "\n";
    change %= 10000;
    std::cout << std::setw(13) << "50 bills: " << change/5000 << "\n";
    change %= 5000;
    std::cout << std::setw(13) << "20 bills: " << change/2000 << "\n";
    change %= 2000;
    std::cout << std::setw(13) << "10 bills: " << change/1000 << "\n";
    change %= 1000;
    std::cout << std::setw(13) << "5 bills: " << change/500 << "\n";
    change %= 500;
    std::cout << std::setw(13) << "toonies: " << change/200 << "\n";
    change %= 200;
    std::cout << std::setw(13) << "loonies: " << change/100 << "\n";
    change %= 100;
    std::cout << std::setw(13) << "quarters: " << change/25 << "\n";
    change %= 25;
    std::cout << std::setw(13) << "dimes: " << change/10 << "\n";
    change %= 10;
    int nickels = change/5;
    if(change%5/1 >= 3){
     ++nickels;
    }
    std::cout << std::setw(13) << "nickels: " << nickels << "\n";
}
