#include "hello.h"
#include <iostream>

int main() {
    int result = sayHello("Hello, man");
    return result == HELLO_SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE;
}