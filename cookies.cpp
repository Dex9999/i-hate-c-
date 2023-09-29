#include <iostream>

int main(){
    double regCookies = 48, numOfCookies = regCookies, sugar = 1.5, butter = 1.0, flour = 2.75;

    std::cout << "How many cookies do you want to make? ";
    std::cin >> numOfCookies;

    double cookieRatio = regCookies/numOfCookies;
    std::cout << "You would need:\n" << sugar/cookieRatio << " Cup" << (sugar/cookieRatio == 1.0 ? "" : "s") << " of Sugar\n" << butter/cookieRatio << " Cup" << (butter/cookieRatio == 1.0 ? "" : "s") << " of Butter and\n" << flour/cookieRatio << " Cup" << (flour/cookieRatio == 1.0 ? "" : "s") << " of Flour\nto make " << numOfCookies << " cookies!";
}
