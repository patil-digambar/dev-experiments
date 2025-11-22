#include <fmt/core.h>
#include <iostream>
#include "mylib_static.h"
#include "mylib_shared.h"

int main() {
    
    std::cout << greet_static("Alice") << std::endl;
    std::cout << greet_shared("Bob") << std::endl;

    int version = FMT_VERSION;
    fmt::print("Hello, {}! Using fmt version {}.\n", "World", version);

    return 0;
}
