# test/stack/CMakeLists.txt

# 添加测试可执行文件
add_executable(test_stack test_stack.c)

# 链接 calculator 和 stack 库
target_link_libraries(test_stack PRIVATE calculator stack)

# 包含头文件路径
target_include_directories(test_stack PRIVATE
    ${CMAKE_SOURCE_DIR}/src/calculator/include
    ${CMAKE_SOURCE_DIR}/src/stack/include
)

# 添加测试
enable_testing()
add_test(NAME StackTest COMMAND test_stack)
