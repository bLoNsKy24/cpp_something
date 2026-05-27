#include <iostream>
int getValue() {
    std::cout << "Enter a value: ";
    int value{};
    std::cin >> value;
    return value;
}
int main() {
    int x{getValue()};
    int y{getValue()};
    std::cout << x << "*" << y << "=" << (x*y) << "\n";
    return 0;


}