#include <iostream>
#include <iomanip>
int main()
{
    long long int pops=0,chips=0,gums=0,smarties=0;
    double popPrice=1.50,chipPrice=1.25,gumPrice=1.65,smartiePrice=1.35;
    std::cout << "   __  __   __  __   _____       _____                          _            _ \n";
    std::cout << "  |  \\/  | |  \\/  | |  __ \\     / ____|                        | |          |_| \n";
    std::cout << "  | \\  / | | \\  / | | |__) |   | (___    _ __     __ _    ___  | | __  ___  |_| \n";
    std::cout << "  | |\\/| | | |\\/| | |  _  /     \\___ \\  | '_ \\   / _` |  / __| | |/ / / __| |_| \n";
    std::cout << "  | |  | | | |  | | | | \\ \\     ____) | | | | | | (_| | | (__  |   <  \\__ \\ |_| \n";
    std::cout << "  |_|  |_| |_|  |_| |_|  \\_\\   |_____/  |_| |_|  \\__,_|  \\___| |_|\\_\\ |___/ (_)\n\n";


    std::cout << std::setw(52) << "How many pops were purchased? ";
    std::cin >> pops;
    std::cout << std::setw(52) <<"How many bags of chips were purchased? ";
    std::cin >> chips;
    std::cout << std::setw(52) <<"How many packs of gum were purchased? ";
    std::cin >> gums;
    std::cout << std::setw(52) <<"How many bags of smarties were purchased? ";
    std::cin >> smarties;

    double totalPrice = pops*popPrice+chips*chipPrice+gums*gumPrice+smarties*smartiePrice;
    double moneyGiven = 0;

    std::cout << "\n"<<std::setw(49)<<"The total purchase is $" << totalPrice <<"\n\n";
    std::cout << std::setw(52)<< "How much did they give you? $";
    std::cin >> moneyGiven;

    long long int change = 0;
    change = (moneyGiven-totalPrice)*100;
    if(moneyGiven == 0){
        std::cout << "\n"<<std::setw(62)<<"Dude you can't just give it to them for free\n";
    } else if(moneyGiven < 0){
        std::cout << "\n"<<std::setw(53)<<"You paid them to take it?!?\n";
    }

    if(change<0){
    std::cout << "\n"<<std::setw(54)<<"They still need to give you:\n";
    change = -change;
    } else if(change>0){
    std::cout << "\n"<<std::setw(50)<<"You should give them:\n";
    } else {
    std::cout << std::setw(60)<<"That's crazy, they gave the exact amount!\n";
    return 0;
    }

    std::cout << std::setw(41) << "$100: " << change/10000 << "\n";
    change %= 10000;
    std::cout << std::setw(41) << "$50: " << change/5000 << "\n";
    change %= 5000;
    std::cout << std::setw(41) << "$20: " << change/2000 << "\n";
    change %= 2000;
    std::cout << std::setw(41) << "$10: " << change/1000 << "\n";
    change %= 1000;
    std::cout << std::setw(41) << "$5: " << change/500 << "\n";
    change %= 500;
    std::cout << std::setw(41) << "$2: " << change/200 << "\n";
    change %= 200;
    std::cout << std::setw(41) << "$1: " << change/100 << "\n";
    change %= 100;
    std::cout << std::setw(42) << "25¢: " << change/25 << "\n";
    change %= 25;
    std::cout << std::setw(42) << "10¢: " << change/10 << "\n";
    change %= 10;
    int nickels = change/5;
    if(change%5/1 >= 3){
     ++nickels;
    }

    // this is canada no pennies for you, no soup 4 u
    std::cout << std::setw(42) << "5¢: " << nickels << "\n";
}
