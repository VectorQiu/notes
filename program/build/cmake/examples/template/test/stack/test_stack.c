/**
 * \file            test_stack.c
 * \brief           test stack
 * \date            2024-10-29
 */

/*
 * Copyright (c) 2024 Vector Qiu
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of the stack library.
 *
 * Author:          Vector Qiu <vetor.qiu@gmail.com>
 * Version:         v0.0.1
 */
/* includes ----------------------------------------------------------------- */
#include <stdlib.h>
#include <unity.h>
#include "./stack/stack.h"

/* public functions --------------------------------------------------------- */
/**
 * \brief           Set up test environment
 *
 * This function is called before each test case is run. It can be used
 * to initialize resources or set up any required state before
 * executing a test.
 */
void
setUp(void) {
    /* This function is called before each test runs. */
}

/**
 * \brief           Tear down test environment
 *
 * This function is called after each test case is executed. It can be
 * used to clean up resources or reset state to ensure that tests do
 * not interfere with one another.
 */
void
tearDown(void) {
    /* This function is called after each test runs. */
}

/**
 * \brief           Test stack initialization
 *
 * This test checks the stack initialization function. It verifies that
 * the stack is created successfully by asserting that the returned
 * pointer is not NULL.
 */
void
test_stack_init(void) {
    /* Test the stack initialization. */
    stack_t stack = stack_init(10);
    TEST_ASSERT_NOT_NULL(stack); /* Check that the stack is not NULL. */
    stack_free(stack);           /* Free the allocated stack. */
}

/**
 * \brief           Test pushing and popping from the stack
 *
 * This test checks the push and pop operations of the stack. It verifies
 * that pushing an integer onto the stack works correctly and that
 * popping retrieves the correct value. It also tests the behavior
 * when the stack is full.
 */
void
test_stack_push_pop(void) {
    /* Test pushing and popping from the stack. */
    stack_t stack = stack_init(2);
    TEST_ASSERT_NOT_NULL(
        stack); /* Ensure the stack was created successfully. */

    stack_node_t node; /* Declare a stack node. */

    /* Test pushing an integer onto the stack. */
    int32_t int_data = 42;      /* Integer data to be pushed onto the stack. */
    node.data = &int_data;      /* Set the node's data to the integer. */
    node.type = STACK_TYPE_INT; /* Set the node type to integer. */
    TEST_ASSERT_EQUAL_INT(
        0, push(stack, node)); /* Push the node and check for success. */

    /* Test popping an integer from the stack. */
    stack_node_t popped_node; /* Declare a node to hold the popped value. */
    TEST_ASSERT_EQUAL_INT(
        0, pop(stack, &popped_node)); /* Pop the node and check for success. */
    TEST_ASSERT_EQUAL_INT(
        int_data,
        *(int32_t*)popped_node
             .data); /* Verify the popped value matches the pushed value. */
    free(popped_node.data); /* Free the popped node's data. */

    /* Test stack full condition. */
    node.data = &int_data;      /* Reuse the integer data for another push. */
    node.type = STACK_TYPE_INT; /* Ensure the node type is set. */
    push(stack, node);          /* Push the first node. */
    node.data = &int_data;      /* Set up for the second push. */
    TEST_ASSERT_EQUAL_INT(
        0, push(stack, node)); /* The second push should succeed. */
    TEST_ASSERT_EQUAL_INT(
        -2,
        push(stack,
             node)); /* The third push should fail since the stack is full. */

    stack_free(stack); /* Free the stack resources. */
}

/**
 * \brief           Test peeking the top of the stack
 *
 * This test checks the peek operation of the stack. It verifies that
 * peeking retrieves the top value without removing it from the stack.
 */
void
test_stack_peek(void) {
    /* Test peeking at the top value of the stack. */
    stack_t stack = stack_init(10);
    TEST_ASSERT_NOT_NULL(
        stack); /* Ensure the stack was created successfully. */

    stack_node_t node;          /* Declare a stack node. */
    int32_t int_data = 42;      /* Integer data to be pushed onto the stack. */
    node.data = &int_data;      /* Set the node's data to the integer. */
    node.type = STACK_TYPE_INT; /* Set the node type to integer. */
    push(stack, node);          /* Push the node onto the stack. */

    stack_node_t peeked_node; /* Declare a node to hold the peeked value. */
    TEST_ASSERT_EQUAL_INT(
        0, peek(stack,
                &peeked_node)); /* Peek at the stack and check for success. */
    TEST_ASSERT_EQUAL_INT(
        int_data,
        *(int32_t*)peeked_node
             .data); /* Verify the peeked value matches the pushed value. */

    stack_free(stack); /* Free the stack resources. */
}

/**
 * \brief           Test stack empty and full states
 *
 * This test checks the functions that determine if the stack is empty
 * or full. It verifies the states before and after pushing elements onto
 * the stack.
 */
void
test_stack_empty_full(void) {
    /* Test checking if the stack is empty or full. */
    stack_t stack = stack_init(2);
    TEST_ASSERT_NOT_NULL(
        stack); /* Ensure the stack was created successfully. */
    TEST_ASSERT_EQUAL_INT(
        1,
        stack_is_empty(stack)); /* Check that the stack is empty initially. */
    TEST_ASSERT_EQUAL_INT(
        0,
        stack_is_full(stack)); /* Check that the stack is not full initially. */

    int32_t int_data = 42; /* Integer data to be pushed onto the stack. */
    stack_node_t node = {
        .data = &int_data,
        .type = STACK_TYPE_INT}; /* Create a stack node for the integer. */
    push(stack, node);           /* Push the node onto the stack. */
    TEST_ASSERT_EQUAL_INT(
        0,
        stack_is_empty(stack)); /* Check that the stack is no longer empty. */
    TEST_ASSERT_EQUAL_INT(
        0, stack_is_full(stack)); /* Check that the stack is still not full. */

    push(stack, node); /* Push the second node onto the stack. */
    TEST_ASSERT_EQUAL_INT(
        1, stack_is_full(stack)); /* Now the stack should be full. */

    stack_free(stack); /* Free the stack resources. */
}

/**
 * \brief           Test stack free function
 *
 * This test checks the stack free function to ensure it can release
 * the memory allocated for the stack without errors.
 */
void
test_stack_free(void) {
    /* Test freeing the stack. */
    stack_t stack = stack_init(2);
    TEST_ASSERT_NOT_NULL(
        stack);        /* Ensure the stack was created successfully. */
    stack_free(stack); /* Check if the stack can be freed without issues. */
}

/* private functions -------------------------------------------------------- */
/**
 * \brief           Main function for running tests
 *
 * This function initializes the Unity test framework, runs all the
 * defined test cases, and returns the test results.
 */
int
main(void) {
    /* Main function to run the tests. */
    UNITY_BEGIN(); /* Initialize the Unity test framework. */

    RUN_TEST(test_stack_init);       /* Run the stack initialization test. */
    RUN_TEST(test_stack_push_pop);   /* Run the push and pop test. */
    RUN_TEST(test_stack_peek);       /* Run the peek test. */
    RUN_TEST(test_stack_empty_full); /* Run the empty/full test. */
    RUN_TEST(test_stack_free);       /* Run the free test. */

    return UNITY_END(); /* Finalize and return the test results. */
}

/* ----------------------------- end of file -------------------------------- */
