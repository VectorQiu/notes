# Add an executable target named 'test_calculator' using the source file 'test_calculator.c' located in the 'stack' directory.
add_executable(test_calculator test_calculator.cc)

target_link_libraries(test_calculator PRIVATE
    GTest::GTest
    GTest::Main
    calculator
)

