# Add an executable target named 'test_stack' using the source file 'test_stack.c' located in the 'stack' directory.
add_executable(test_stack test_stack.cc)


target_link_libraries(test_stack PRIVATE
    GTest::GTest
    GTest::Main
    stack
)