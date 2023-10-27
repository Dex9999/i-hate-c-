//Assignment - find the sum, average and product of a bunch of numbers
#include <iostream>

int main()
{
    int num;
    int n;
    double sum;
    double product;
    std::string choice = "";
    bool repeat;
    bool validChoice;

    do
    {
        n = 0;
        repeat = false;
        sum = 0;
        product = 1;
        validChoice = true;

        do
        {
            std::cout << "How many numbers would you like to enter (1-10)?";
            std::cin>>num;
        }
        while (num<1 || num >10);

        for(int i = 0; i < num; ++i)
        {
            std::cout << "Enter number #" << i+1 << ": ";
            std::cin >> n;
            sum += n;
            product *= n;
        }

        std::cout << "The sum is " << sum << "\n";
        std::cout << "The average is " << sum/num << "\n";
        std::cout << "The product is " << product << "\n";


        do
        {
            std::cout<<"Do you want to calculate another set? ";
            std::cin>>choice;

            if (choice.size() >= 1)
            {
                char firstChar = choice[0];

                if (firstChar == 'y')
                {
                    validChoice = true;
                    repeat = true;
                } else if(firstChar == 'n'){
                    validChoice = true;
                    repeat = false;
                }
                else
                {
                    validChoice = false;
                    std::cout << "Yes or no, make up your mind\n";
                }
            }
        }
        while(!validChoice);

    }
    while(repeat);
}
