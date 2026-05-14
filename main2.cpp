#include <iostream>
int main()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;
    std::cout << "Enter another one: ";
    int y{};
    std::cin >> y;
    std::cout << x << "+" << y << " is " << x + y << ".\n";
    std::cout << x << "-" << y << " is " << x - y << ".\n";
    return 0;
}
