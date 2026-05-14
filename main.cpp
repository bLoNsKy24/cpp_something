#include <iostream>;
void doNothing(int&){}
int main(){
    std::cout << sizeof(int) << "\n";
    std::cout << -(-5); 
    int x {2};
    x = 5;
    std::cout << x;
    return 0;
}