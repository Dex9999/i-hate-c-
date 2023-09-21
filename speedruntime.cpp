#include <iostream>

int main(){
    int age = 0;
    std::cout << "How old are you?\n";
    std::cin >> age;

    if(age<=0){
        std::cout << "Really? You're soooo funny (¬_¬)";
    } else{
        std::cout << "It's cool that you are " << age << " years old!";
    }

    return 0;
}

//done in 1:45.05
