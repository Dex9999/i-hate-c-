#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    int num = 1000000;
    std::vector<int> calculatedFactors = {0};
    std::filesystem::path sourceFile("output.txt");
    std::ofstream file("file.txt");
    int total = 0;
    if (file.is_open())
    {


        bool prime = true;
        std::cout << "Prime numbers:\n";

        // include for all factors
        for(int i = 1; i < num; i++)
        {
            bool prime = true;
            for(int j = 2; j < i - 1; j++)
            {
                if (i%j == 0)
                {
                    prime = false;
                    break;
                }
            }
            if(prime)
            {
                std::cout << i << "\n";
                file << i << "\n";
                total++;
            }
        }
        std::cout << "In total, there are " << total << " prime numbers between 1 and 1000000.\n\n";
        file << "In total, there are " << total << " prime numbers between 1 and 1000000.\n\n";

        file.close();
        std::cout << "Output file created successfully." << std::endl;
    }
    else
    {
        std::cerr << "Failed to create the file." << std::endl;
    }
}
