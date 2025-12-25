#include "header.h"
#include <iostream>

int main()
{
    const char* s = "Hello";
    char* copy = CopyString(s);
    std::cout << "Copy: " << copy << '\n';

    const char* a = "Hello, ";
    const char* b = "world!";
    char* concat = ConcatenateStrings(a, b);
    std::cout << "Concat: " << concat << '\n';

    delete[] copy;
    delete[] concat;
    return 0;
}
