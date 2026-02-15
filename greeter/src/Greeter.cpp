#include <greeter/Greeter.h> // Namespaced include 
#include <iostream>

std::string get_greeting() {
	return "Hello from the modular Greeter library!";
}

std::string Greeter::greet() const {
	char buffer[5];
	std::cout << buffer[5];
	return "Hello from the Greeter class!";
}