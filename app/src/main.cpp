#include <iostream>
#include <greeter/Greeter.h> // Namespaced include 
#include <spdlog/spdlog.h> 

int main() {
	std::cout << get_greeting();
	spdlog::info(get_greeting());
	return 0;
}