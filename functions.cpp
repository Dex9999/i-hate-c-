#include <iostream>
using namespace std;float sum(float first,float sec);float product(float first,float sec);int main(){float num1=0.f;float num2=0.f;do{std::cout<<"Enter two numbers: \n";std::cin>>num1;std::cin>>num2;}while(num1<0&&num2<0);std::cout<<"The sum is "<<sum(num1,num2)<<"\nThe product is "<<product(num1,num2);}float sum(float first,float sec){return first+sec;}float product(float first, float sec){return first*sec;}