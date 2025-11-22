#include "mylib_static.h"

std::string greet_static(const std::string& name){
    return "Hello, " + name + " from static library!";
}