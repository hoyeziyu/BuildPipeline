#include <greeter/Greeter.h>  // Namespaced include
#include <spdlog/spdlog.h>

#include <iostream>

int main() {
    std::cout << "Hello world";
    std::cout << get_greeting();
    spdlog::info(get_greeting());
    return 0;
}