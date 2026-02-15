cmake_minimum_required(VERSION 3.23)

set(SANITIZE_CONDITION "$<CONFIG:Sanitize>")

if (MSVC)
    # 直接在全局添加标志
    add_compile_options("$<${SANITIZE_CONDITION}:/fsanitize=address>")
    add_compile_options("$<${SANITIZE_CONDITION}:/Zi>")
    add_compile_options("$<${SANITIZE_CONDITION}:/Od>") # 禁用优化，防止溢出代码被优化掉
    
    # 链接选项
    add_link_options("$<${SANITIZE_CONDITION}:/fsanitize=address>")
    add_link_options("$<${SANITIZE_CONDITION}:/INCREMENTAL:NO>")
else()
  set(SANITIZE_FLAGS
    "$<${SANITIZE_CONDITION}:-fsanitize=address>"
    "$<${SANITIZE_CONDITION}:-fno-omit-frame-pointer>"
    "$<${SANITIZE_CONDITION}:-g>"
  )
endif()

add_compile_options(${SANITIZE_FLAGS})
add_link_options(${SANITIZE_FLAGS})