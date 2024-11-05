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

/* private variables -------------------------------------------------------- */
stack_t stack;

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
    stack = stack_init(5); /* Create a deep stack of 5 */
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
    stack_free(stack);
}

/**
 * \brief           Test stack initialization
 *
 * This test checks the stack initialization function. It verifies that
 * the stack is created successfully by asserting that the returned
 * pointer is not NULL and that the stack is initially empty.
 */
void
test_stack_init(void) {
    TEST_ASSERT_NOT_NULL(stack);
    TEST_ASSERT_TRUE(stack_is_empty(stack));
}

/**
 * \brief           Test pushing to the stack
 *
 * This test checks the push function of the stack. It verifies that
 * a node can be successfully pushed onto the stack and that the stack
 * is no longer empty after the operation.
 */
void
test_stack_push(void) {
    stack_node_t* node = malloc(sizeof(stack_node_t));
    node->data = malloc(sizeof(int32_t));
    *(int32_t*)node->data = 10;
    node->type = STACK_TYPE_INT;

    stack_error_t result = push(stack, node);
    TEST_ASSERT_EQUAL(STACK_SUCCESS, result);
    TEST_ASSERT_FALSE(stack_is_empty(stack));
    TEST_ASSERT_EQUAL(4, stack_remaining_space(stack)); // 5 - 1

    stack_node_t* peeked_node = NULL;
    result = peek(stack, &peeked_node);
    TEST_ASSERT_EQUAL(STACK_SUCCESS, result);
    TEST_ASSERT_EQUAL(10, *(int32_t*)peeked_node->data);
}

/**
 * \brief           Test popping from the stack
 *
 * This test checks the pop function of the stack. It verifies that
 * a node can be successfully popped from the stack and that the data
 * returned is correct.
 */
void
test_stack_pop(void) {
    stack_node_t* node = malloc(sizeof(stack_node_t));
    node->data = malloc(sizeof(int32_t));
    *(int32_t*)node->data = 20;
    node->type = STACK_TYPE_INT;
    stack_error_t result = push(stack, node);
    TEST_ASSERT_EQUAL(STACK_SUCCESS, result);

    stack_node_t* popped_node = NULL;
    result = pop(stack, &popped_node);
    TEST_ASSERT_EQUAL(STACK_SUCCESS, result);
    TEST_ASSERT_EQUAL(20, *(int32_t*)popped_node->data);
    free(popped_node->data);
    free(popped_node);
    TEST_ASSERT_TRUE(stack_is_empty(stack)); // Should be empty after pop
}

/**
 * \brief           Test peeking at the top element of the stack
 *
 * This test checks the peek function of the stack. It verifies that
 * the top element can be accessed without removing it from the stack.
 */
void
test_stack_peek(void) {
    stack_node_t* node = malloc(sizeof(stack_node_t));
    node->data = malloc(sizeof(int32_t));
    *(int32_t*)node->data = 30;
    node->type = STACK_TYPE_INT;
    stack_error_t result = push(stack, node);
    TEST_ASSERT_EQUAL(STACK_SUCCESS, result);

    stack_node_t* peeked_node = NULL;
    result = peek(stack, &peeked_node);
    TEST_ASSERT_EQUAL(STACK_SUCCESS, result);
    TEST_ASSERT_EQUAL(30, *(int32_t*)peeked_node->data);
}

/**
 * \brief           Test if the stack is full
 *
 * This test checks the is_full function of the stack. It verifies
 * that the stack reports correctly when it is full after multiple pushes.
 */
void
test_stack_is_full(void) {
    for (int i = 0; i < 5; i++) {
        stack_node_t* node = malloc(sizeof(stack_node_t));
        node->data = malloc(sizeof(int32_t));
        *(int32_t*)node->data = i;
        node->type = STACK_TYPE_INT;
        stack_error_t result = push(stack, node);
        TEST_ASSERT_EQUAL(STACK_SUCCESS, result);
    }
    TEST_ASSERT_TRUE(stack_is_full(stack));
}

/**
 * \brief           Test remaining space in the stack
 *
 * This test checks the remaining_space function of the stack. It verifies
 * that the correct number of available spaces is reported before and
 * after pushing an element onto the stack.
 */
void
test_stack_remaining_space(void) {
    TEST_ASSERT_EQUAL(5, stack_remaining_space(stack)); // Initially, 5 spaces

    stack_node_t* node = malloc(sizeof(stack_node_t));
    node->data = malloc(sizeof(int32_t));
    *(int32_t*)node->data = 10;
    node->type = STACK_TYPE_INT;
    stack_error_t result = push(stack, node);
    TEST_ASSERT_EQUAL(STACK_SUCCESS, result);

    TEST_ASSERT_EQUAL(4, stack_remaining_space(stack)); // After one push
}

/**
 * \brief           Test popping from an empty stack
 *
 * This test checks the pop function when the stack is empty. It verifies
 * that the correct error code is returned when trying to pop from an empty
 * stack.
 */
void
test_stack_pop_empty(void) {
    stack_node_t* node = NULL;
    stack_error_t result = pop(stack, &node);
    TEST_ASSERT_EQUAL(STACK_ERROR_EMPTY, result);
}

/**
 * \brief           Test pushing an invalid type onto the stack
 *
 * This test checks the push function when an invalid node type is used.
 * It verifies that the correct error code is returned when trying to push an
 * invalid type.
 */
void
test_stack_push_invalid_type(void) {
    stack_node_t* node = malloc(sizeof(stack_node_t));
    node->data = NULL; // Invalid type
    node->type = STACK_TYPE_NONE;

    stack_error_t result = push(stack, node);
    TEST_ASSERT_EQUAL(STACK_ERROR_INVALID_TYPE, result);
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
    UNITY_BEGIN();
    RUN_TEST(test_stack_init);
    RUN_TEST(test_stack_push);
    RUN_TEST(test_stack_pop);
    RUN_TEST(test_stack_peek);
    RUN_TEST(test_stack_is_full);
    RUN_TEST(test_stack_remaining_space);
    RUN_TEST(test_stack_pop_empty);
    RUN_TEST(test_stack_push_invalid_type);
    return UNITY_END();
}

/* ----------------------------- end of file -------------------------------- */
