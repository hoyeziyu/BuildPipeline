cmake_minimum_required(VERSION 3.21)	# 满足预设要求的最低cmake版本 

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


# Name the overall project
project(Greeter)

include(cmake/Sanitize.cmake)

# Bring in our components
add_subdirectory(greeter) # The library 
add_subdirectory(app)     # The executable

enable_testing() 
add_subdirectory(tests)
add_subdirectory(benchmarks)

# Find the clang-format executable
#[[
	find_program从PATH环境变量中查找可执行文件，并将结果存储在CLANG_FORMAT_EXE变量中。
]]
find_program(CLANG_FORMAT_EXE clang-format) # REQUIRED
set(FORMAT_TARGETS GreeterApp GreeterLib)
set(ALL_SOURCES)

foreach(target IN LISTS FORMAT_TARGETS)
  get_target_property(target_sources ${target} SOURCES)
  get_target_property(target_source_dir ${target} SOURCE_DIR)
  
  # Convert relative paths to absolute paths for this target
  foreach(source ${target_sources})
    if(IS_ABSOLUTE ${source})
      list(APPEND ALL_SOURCES ${source})
    else()
      list(APPEND ALL_SOURCES ${target_source_dir}/${source})
    endif()
  endforeach()
endforeach()

# Check if it was found
if(CLANG_FORMAT_EXE) 
  message(STATUS "Found clang-format at ${CLANG_FORMAT_EXE}") 
  add_custom_target(format 
    COMMENT "Formatting files with clang-format..." 
    COMMAND ${CLANG_FORMAT_EXE} -i ${target_sources} 
  ) 
  message(STATUS "Added 'format' target") 
else() 
   message(WARNING
    "clang-format not found - format target unavailable") 
endif()