# 查找 calculator 模块的所有源文件
file(GLOB CALCULATOR_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

# 创建静态库 calculator
add_library(calculator STATIC ${CALCULATOR_SOURCES})

# 添加头文件目录
target_include_directories(calculator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(calculator PRIVATE stack)
