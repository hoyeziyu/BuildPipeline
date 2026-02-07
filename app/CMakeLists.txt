cmake_minimum_required(VERSION 3.21)

add_executable(GreeterApp src/main.cpp)

target_compile_features(GreeterApp PUBLIC cxx_std_20)

target_include_directories(GreeterApp PUBLIC 
  ${PROJECT_SOURCE_DIR}/greeter/include
)

find_package(spdlog CONFIG REQUIRED) 

target_link_libraries(GreeterApp 
GreeterLib
spdlog::spdlog
)