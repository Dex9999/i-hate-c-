#include <iostream>

int main(){
  std::string name = "Declan";
  int age = 16;
  char middleNameInitial = 'C';
  bool takingCompSci = true;
  double income = 100000;
  float pi = 3.141592;

  std::cout << "Hello I'm " << name << " and I am " << age << " years old.\n"<< "My middle inital is " << middleNameInitial << "\nI am " << takingCompSci << "00% taking CompSci in University\nI hope to make $" << income << " per year ;) \nAlso pi is " << pi << "\n";
  return 0;
  }
