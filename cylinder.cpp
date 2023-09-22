#include <iostream>
#include <cmath>
int main(){
    double radius = 0;
    double height = 0;
    double pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067;
    std::cout << "Cylinder Volume Calculator!!!\n";
    std::cout << "Radius of Your Cylinder (cm): ";
    std::cin >> radius;
    std::cout << "Height of Your Cylinder (cm): ";
    std::cin >> height;
    double volume = 0;

    //volume = pi*(radius * radius)*height; // version without cmath
    volume = M_PI*pow(radius, 2)*height; //with cmath
    std::cout << "The Volume of Your Cylinder is " << volume << "cm^3";
}
