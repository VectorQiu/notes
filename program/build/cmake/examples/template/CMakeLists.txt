cmake_minimum_required(VERSION 3.22)

# 项目名称和版本
project(TEMPLATE VERSION 0.0.1 LANGUAGES C)

# 添加全局编译选项
set(CMAKE_SOURCE_FILE_ENCODING UTF-8)

add_compile_options("/utf-8")

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)  # 在 Windows 上，通常使用标准而不使用扩展
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 添加 src 子目录
add_subdirectory(src)
add_subdirectory(test)

# 启用测试
enable_testing()
