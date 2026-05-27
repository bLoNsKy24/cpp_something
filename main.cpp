#include <iostream>
void doDoPrint() {
    std::cout << "Hello, World!\n";
}

void doPrint() {
    std::cout << "starting doPrint()\n";
    doDoPrint();
    std::cout << "ending doPrint()\n";
}

int main() {
    std::cout << "starting main()\n";
    doPrint();
    std::cout << "ending main()\n";
    return 0;
}