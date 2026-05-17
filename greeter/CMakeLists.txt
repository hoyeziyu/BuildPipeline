# "install-tree"，可以用 find_package（） 命令把它添加到项目中
# 安装树就是在文件系统上创建的一个目录，包含了其他开发者使用我们库所需的一切
#   1.编译后的库文件（.a、.lib、.so、.dll）
#   2.公共头文件（Greeter.h）
#   3.find_package（） 查找的 CMake 配置文件

cmake_minimum_required(VERSION 3.16)

project(GreeterLib VERSION 1.0.0)
include(GNUInstallDirs)

add_library(GreeterLib src/Greeter.cpp)
add_library(Greeter::Lib ALIAS GreeterLib)

target_compile_features(GreeterLib PUBLIC cxx_std_17)

set_target_properties(GreeterLib PROPERTIES 
  OUTPUT_NAME Greeter
  EXPORT_NAME Lib
)

target_include_directories(GreeterLib
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

target_sources(GreeterLib
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS "${PROJECT_SOURCE_DIR}/include"
  FILES
    "${PROJECT_SOURCE_DIR}/include/greeter/Greeter.h"
)

install(
  TARGETS GreeterLib
  EXPORT GreeterLibTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT Development
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT Development
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT Development
  FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    COMPONENT Development
)

install(DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)

install(EXPORT GreeterLibTargets
  FILE GreeterLibTargets.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/GreeterLib
  NAMESPACE Greeter::
  COMPONENT Development
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  "cmake/GreeterLibConfig.cmake.in"
  "GreeterLibConfig.cmake"
  INSTALL_DESTINATION
  "${CMAKE_INSTALL_LIBDIR}/cmake/GreeterLib"
)

write_basic_package_version_file(
  "GreeterLibConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/GreeterLibConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/GreeterLibConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/GreeterLib"
  COMPONENT Development
)