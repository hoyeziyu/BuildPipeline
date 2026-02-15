cmake_minimum_required(VERSION 3.23)

find_package(GTest REQUIRED) 

add_executable(GreeterTests main.cpp)
target_link_libraries(GreeterTests PRIVATE 
	GreeterLib
	GTest::gtest        # The core gtest library 
	GTest::gtest_main   # Provides a main() function 
)

gtest_discover_tests(GreeterTests PROPERTIES
  LABELS "library"
  ENVIRONMENT 
    "ASAN_OPTIONS=detect_stack_use_after_return=1" 
)