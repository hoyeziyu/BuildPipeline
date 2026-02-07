#include <greeter/Greeter.h> // Namespaced include 

std::string get_greeting() {
	return "Hello from the modular Greeter library!";
}

std::string Greeter::greet() const {
	return "Hello from the Greeter class!";
}