cmake_minimum_required(VERSION 3.25)	# 满足预设要求的最低cmake版本 

set(ASSET_FILES
  logo.png
  config.json
)

set(
  CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "The toolchain file"
)
message(STATUS "CMAKE_TOOLCHAIN_FILE  VALUE 用来告诉cmake去哪里找vcpkg: ${CMAKE_TOOLCHAIN_FILE}")

set(ASSET_DEST "${CMAKE_BINARY_DIR}/assets")
# Ensure the destination directory exists
file(MAKE_DIRECTORY ${ASSET_DEST})

foreach(asset IN LISTS ASSET_FILES)
  # Build the full path to the current asset file 
  set(src_path "${CMAKE_CURRENT_SOURCE_DIR}/assets/${asset}")
  # Copy the source file to the destination directory.
  file(COPY ${src_path} DESTINATION ${ASSET_DEST})
  message(STATUS "Copied ${src_path} to asset directory")
endforeach()


# Name the overall project  替换CPACK_PACKAGE_NAME 、CPACK_PACKAGE_VERSION变量
project(
  Greeter VERSION "1.0"
  HOMEPAGE_URL "https://github.com/hoyeziyu/BuildPipeline"
)

include(cmake/Sanitize.cmake)
include(cmake/Format.cmake)

# Bring in our components   add_subdirectory命令形成构建树build-tree依赖
add_subdirectory(greeter) # The library 
add_subdirectory(app)     # The executable

enable_testing() 
add_subdirectory(tests)
add_subdirectory(benchmarks)

# Passing targets we want to format as arguments 这里的顺序很重要
add_clang_format(GreeterLib GreeterApp)


set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
# install 命令将我们build构建目录中杂乱无章的内容复制到一个干净的“安装树”install-tree中；
# CPack 基于此方法进行扩展。它会自动运行此安装install 步骤，然后将安装树的内容打包成一个单一的归档或安装文件
include(CPack)  # CPack生成包的元数据

cpack_add_component(Development
  DISPLAY_NAME "The Greeter Library"
  DESCRIPTION "Compiled Library, Header, and CMake Files"
)