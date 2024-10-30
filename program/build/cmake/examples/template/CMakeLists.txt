cmake_minimum_required(VERSION 3.22)

# 项目名称和版本
project(TEMPLATE VERSION 0.0.1 LANGUAGES C)

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)  # 在 Windows 上，通常使用标准而不使用扩展
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 指定工具链文件
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/clang.cmake")

# 添加 src 子目录
add_subdirectory(src)
