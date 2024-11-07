# 查找 stack 模块的所有源文件
file(GLOB STACK_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

# 创建静态库 stack
add_library(stack STATIC ${STACK_SOURCES})

# 添加头文件目录
target_include_directories(stack PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
