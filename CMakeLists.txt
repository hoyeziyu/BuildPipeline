cmake_minimum_required(VERSION 3.16)

# Name the overall project
project(Greeter)

# Bring in our components
add_subdirectory(greeter) # The library 
add_subdirectory(app)     # The executable