#include <iostream>
#include <iomanip>
int main(){
    double aSeats = 0, bSeats = 0, cSeats = 0, aCost = 14.99, bCost = 11.99, cCost = 8.99;
    std::cout << "How many seats were sold this game?\nA seats sold: ";
    std::cin >> aSeats;
    std::cout << "B seats sold: ";
    std::cin >> bSeats;
    std::cout << "C seats sold: ";
    std::cin >> cSeats;

    std::cout << "This game sold " << aSeats + bSeats + cSeats << " seats and had a total revenue of $" << std::setprecision(2)<<std::fixed<<aSeats*aCost + bSeats*bCost + cSeats*cCost;
}
