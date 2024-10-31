# 拉取 Unity 测试框架
include(FetchContent)

FetchContent_Declare(
    unity
    URL https://github.com/ThrowTheSwitch/Unity/archive/refs/tags/v2.6.0.tar.gz
    URL_HASH SHA256=aa4c9fb1ae5fc5242f914c65f3557e817e40cb37f04a31e5ff76d1ab89dbf674
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(unity)

enable_testing()  # 启用测试

add_subdirectory(calculator)
add_subdirectory(stack)

# 添加测试到 CTest
add_test(NAME StackTests COMMAND test_stack)
add_test(NAME CalculatorTests COMMAND test_calculator)
