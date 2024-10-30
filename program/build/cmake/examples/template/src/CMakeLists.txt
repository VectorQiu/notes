# 添加 calculator 和 stack 子模块目录
add_subdirectory(calculator)
add_subdirectory(stack)

# 定义可执行文件 main，指定 src/main.c 作为源文件
add_executable(main main.c)

# 链接 `calculator` 和 `stack` 库
target_link_libraries(main PRIVATE calculator stack)
