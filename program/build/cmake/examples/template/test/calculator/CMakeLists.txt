# Add an executable target named 'test_calculator' using the source file 'test_calculator.c' located in the 'stack' directory.
add_executable(test_calculator test_calculator.c)

# Link the 'test_calculator' target with the 'unity' and 'calculator' libraries privately.
# This means 'unity' and 'calculator' will only be linked for this target and not for any targets that depend on 'test_calculator'.
target_link_libraries(test_calculator PRIVATE unity calculator)
