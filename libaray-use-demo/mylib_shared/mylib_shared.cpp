#include "mylib_shared.h"

std::string greet_shared(const std::string& name) {
    return "Hello, " + name + " from shared library!";
}