#include <iostream>;
void doNothing(int&){}
int main()
{
    std::cout << sizeof(int) << "\n";
    return 0;
}