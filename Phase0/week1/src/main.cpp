#include <iostream>
#include "Fibonacci.hpp"

int getNumFromUser()
{
    int n{};
    std::cout << "Enter a number: ";
    std::cin >> n;
    return n;
}

int main()
{
    std::cout << "Hello World!" << std::endl;

    int num {getNumFromUser()};
    std::cout << "You entered: " << num << std::endl;

    std::cout << "Fibonacci of " << num << " is " << fibonacci(num) << std::endl;
    return 0;
}
