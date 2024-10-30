# 设置系统名称和处理器
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)  # 或者根据你的目标架构选择 arm 或其他

# 设置工具链前缀（通常不需要在 Windows 上指定前缀）
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

# 设置编译器标志
set(FLAGS "-Wall -Wextra -O2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}")

# 设置可执行文件后缀
set(CMAKE_EXECUTABLE_SUFFIX ".exe")

# 设置链接器（可选，通常 Clang 会自动处理）
set(CMAKE_LINKER "lld-link")  # 如果你想使用 lld 链接器
