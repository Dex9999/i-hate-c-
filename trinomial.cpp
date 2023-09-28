#include <iostream>

int main()
{
    int range = -1000;
    int i = range;
    int j = range;
    int b = 0;
    int c = 0;
    int sum = 0;
    int product = 0;
    std::cout << "batch simple trinomial factoring solver\n";

    while(true)
    {
        std::cout << "\nb: ";
        std::cin >> b;
        std::cout << "c: ";
        std::cin >> c;
        for(int i = range; i < range*-1; i++)
        {
            for(int j = range; j < range*-1; j++)
            {
                if(i + j == b)
                {
                    if(i*j == c)
                    {
                        std::cout << "\n" << i << ", " << j << "\n";
                    }
                }
            }
        }
    }
}
