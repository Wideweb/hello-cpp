#include "hello.h"
#include <iostream>

using namespace std;

int main() {
    int result = sayHello("Hello, man");
    return result == HELLO_SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE;
}