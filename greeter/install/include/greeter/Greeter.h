#pragma once
#include <string>

// A simple function that returns a greeting
std::string get_greeting();

class Greeter {
public:
	std::string greet() const;
};