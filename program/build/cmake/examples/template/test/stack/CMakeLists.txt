# Add an executable target named 'test_stack' using the source file 'test_stack.c' located in the 'stack' directory.
add_executable(test_stack test_stack.c)

# Link the 'test_stack' target with the 'unity' and 'stack' libraries privately.
# This means 'unity' and 'stack' will only be linked for this target and not for any targets that depend on 'test_stack'.
target_link_libraries(test_stack PRIVATE unity stack)
