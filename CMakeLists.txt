cmake_minimum_required(VERSION 3.16)

set(ASSET_FILES
  logo.png
  config.json
)

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

# Bring in our components
add_subdirectory(greeter) # The library 
add_subdirectory(app)     # The executable