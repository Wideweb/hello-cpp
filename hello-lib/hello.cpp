#include "hello.h"
#include <iostream>

int sayHello(const char *input) {
    std::cout << input << std::endl;
    return std::cout.good() ? HELLO_SUCCESS : HELLO_FAIL;
}
