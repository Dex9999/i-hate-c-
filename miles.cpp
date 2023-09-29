#include <iostream>
#include <iomanip>
#include <cmath>
int main(){
//Modify the program so that it displays the make of car, ✅
//the size of the gas tank, the distance the car can travel on a full tank and mileage(?) ✅
//and display it in a formatted output using the commands covered in this unit. ✅
    double gasLiters = 0, kmPerTank = 0;
    std::string car = "Unknown Car";

    std::cout << "What car do you have? ";
    std::cin >> car;
    car[0] = toupper(car[0]);
    std::cout << "How many liters of gas can your car hold? ";
    std::cin >> gasLiters;
    std::cout << "How far can your car go on a single tank (in km)? ";
    std::cin >> kmPerTank;
    double mileage = kmPerTank/gasLiters;
    mileage = std::round(mileage * 100.0) / 100.0;
    //std::cout << std::setprecision(2) << std::fixed;

    std::cout << "\n\n" << std::setw(10+car.length()) << "Your " << car;
    std::cout << "\n\n"<<std::setw(11+car.length())<<"Mileage: " << mileage << " km/litre";
    std::cout << "\n\n"<<std::setw(22+car.length())<<"Distance on a Full Tank: " << kmPerTank << "km";
    std::cout << "\n\n"<<std::setw(22+car.length())<<"Liters in a Full Tank: " << gasLiters << "L\n\n\n\n";
}
