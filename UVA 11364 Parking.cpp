#include <iostream>

int main()
{
    //std::cout << "Hello World!\n";
    int tests;
    std::cin >> tests;
    while (tests--)
    {
        int stores = 0, min = 100, max = 0, temp;
        std::cin >> stores;
        if (!stores) {
            std::cout << "0" << std::endl;
            continue;
        }
        while (stores--)
        {
            std::cin >> temp;
            if (temp < min) min = temp;
            if (temp > max) max = temp;
        }
        std::cout << (max-min)*2 << std::endl;
    }
    return 0;
}
