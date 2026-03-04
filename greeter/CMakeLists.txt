cmake_minimum_required(VERSION 3.23)
project(GreeterLib VERSION 1.0.0)

add_library(GreeterLib)

target_compile_features(GreeterLib PUBLIC cxx_std_20)

target_sources(GreeterLib
  PRIVATE
    src/Greeter.cpp
  PUBLIC
      FILE_SET HEADERS
      BASE_DIRS "include/" 
      FILES 
      "include/greeter/Greeter.h"	# 多文件继续后面添加
  PRIVATE
      FILE_SET private_headers
      TYPE HEADERS
      BASE_DIRS "src/" 
      FILES "src/InternalDetails.h" 
)

get_target_property( 
  header_sets GreeterLib HEADER_SETS 
) 
foreach(set IN LISTS header_sets)
  get_target_property(
    header_files GreeterLib HEADER_SET_${set}
  )
  message(STATUS "set: ${set}, files: ${header_files}")
endforeach()
