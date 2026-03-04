cmake_minimum_required(VERSION 3.23)

# Find the clang-format executable
#[[
	find_program从PATH环境变量中查找可执行文件，并将结果存储在CLANG_FORMAT_EXE变量中。
]]
find_program(CLANG_FORMAT_EXE clang-format) # REQUIRED

function(add_clang_format)
  # Copy all arguments into a variable
  set(FORMAT_TARGETS ${ARGV})
  
  foreach(target IN LISTS FORMAT_TARGETS)   
    # Skip this argument if it is not the name of a target
    if(NOT TARGET ${target})
      message(WARNING
        "Target '${target}' does not exist"
      )
      continue()
    endif()

    get_target_property(target_sources ${target} SOURCES)
    get_target_property(header_sets ${target} HEADER_SETS)
    get_target_property(target_source_dir ${target} SOURCE_DIR)

    # 注意这里ALL_SOURCES可能为空的情况
    set(current_target_files ${target_sources})
    foreach(header_set IN LISTS header_sets)
      get_target_property(
        header_set_files ${target} HEADER_SET_${header_set}
      )
      list(APPEND current_target_files ${header_set_files})
    endforeach()
    
    set(ALL_SOURCES)
    foreach(file IN LISTS current_target_files)
      if(IS_ABSOLUTE ${file} AND EXISTS ${file})
        list(APPEND ALL_SOURCES ${file})
      elseif(EXISTS ${target_source_dir}/${file})
        list(APPEND ALL_SOURCES ${target_source_dir}/${file})
      endif()
    endforeach()
  endforeach()

  if(CLANG_FORMAT_EXE)
    add_custom_target(format
      COMMENT "Formatting files with clang-format..."
      COMMAND ${CLANG_FORMAT_EXE} -i ${ALL_SOURCES}
    )
    message(STATUS "Added 'format' target")
  else()
    message(WARNING
      "clang-format not found - format target unavailable")
  endif()
endfunction()