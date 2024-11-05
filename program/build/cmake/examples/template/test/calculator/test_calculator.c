/**
 * \file            test_calculator.c
 * \brief           Test Calculator
 * \date            2024-10-31
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
 * This file is part of the calculator library.
 *
 * Author:          Vector Qiu <vetor.qiu@gmail.com>
 * Version:         v0.0.1
 */
/* includes ----------------------------------------------------------------- */
#include <unity.h>
#include "./calculator/calculator.h"

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
 * \brief           Test simple addition expression
 *
 * This test checks the evaluation of a simple addition expression
 * "3 + 5" and asserts that the result equals 8.
 */
void
test_evaluate_expression_simple_addition(void) {
    const char* expression = "3 + 5";
    int32_t result;
    eval_error_t error_code = evaluate_expression(expression, &result);
    TEST_ASSERT_EQUAL(EVAL_SUCCESS, error_code);
    TEST_ASSERT_EQUAL_INT32(8, result);
}

/**
 * \brief           Test simple subtraction expression
 *
 * This test checks the evaluation of a simple subtraction expression
 * "10 - 4" and asserts that the result equals 6.
 */
void
test_evaluate_expression_simple_subtraction(void) {
    const char* expression = "10 - 4";
    int32_t result;
    eval_error_t error_code = evaluate_expression(expression, &result);
    TEST_ASSERT_EQUAL(EVAL_SUCCESS, error_code);
    TEST_ASSERT_EQUAL_INT32(6, result);
}

/**
 * \brief           Test simple multiplication expression
 *
 * This test checks the evaluation of a simple multiplication expression
 * "3 * 4" and asserts that the result equals 12.
 */
void
test_evaluate_expression_simple_multiplication(void) {
    const char* expression = "3 * 4";
    int32_t result;
    eval_error_t error_code = evaluate_expression(expression, &result);
    TEST_ASSERT_EQUAL(EVAL_SUCCESS, error_code);
    TEST_ASSERT_EQUAL_INT32(12, result);
}

/**
 * \brief           Test simple division expression
 *
 * This test checks the evaluation of a simple division expression
 * "8 / 2" and asserts that the result equals 4.
 */
void
test_evaluate_expression_simple_division(void) {
    const char* expression = "8 / 2";
    int32_t result;
    eval_error_t error_code = evaluate_expression(expression, &result);
    TEST_ASSERT_EQUAL(EVAL_SUCCESS, error_code);
    TEST_ASSERT_EQUAL_INT32(4, result);
}

/**
 * \brief           Test expression evaluation with parentheses
 *
 * This test checks the evaluation of an expression that includes
 * parentheses: "3 + (2 * 5)" and asserts that the result equals 13.
 */
void
test_evaluate_expression_with_parentheses(void) {
    const char* expression = "3 + (2 * 5)";
    int32_t result;
    eval_error_t error_code = evaluate_expression(expression, &result);
    TEST_ASSERT_EQUAL(EVAL_SUCCESS, error_code);
    TEST_ASSERT_EQUAL_INT32(13, result);
}

/**
 * \brief           Test complex expression evaluation
 *
 * This test checks the evaluation of a complex expression
 * "3 + 5 * (2 - 8)" and asserts that the result equals -27.
 */
void
test_evaluate_expression_complex(void) {
    const char* expression = "3 + 5 * (2 - 8)";
    int32_t result;
    eval_error_t error_code = evaluate_expression(expression, &result);
    TEST_ASSERT_EQUAL(EVAL_SUCCESS, error_code);
    TEST_ASSERT_EQUAL_INT32(-27, result);
}

/**
 * \brief           Test division by zero scenario
 *
 * This test checks the behavior when attempting to divide by zero
 * "10 / 0". It asserts that the result equals 0, as the implementation
 * is expected to handle division by zero.
 */
void
test_evaluate_expression_division_by_zero(void) {
    const char* expression = "10 / 0";
    int32_t result;
    eval_error_t error_code = evaluate_expression(expression, &result);
    TEST_ASSERT_EQUAL(EVAL_ERROR_DIV_BY_ZERO, error_code);
    TEST_ASSERT_EQUAL_INT32(0, result); /* Assuming your implementation returns
                                           0 on division by zero */
}

/**
 * \brief           Test invalid operator scenario
 *
 * This test checks the behavior when an invalid operator is used
 * "5 % 2". It asserts that the result equals 0, as the implementation
 * is expected to return 0 for invalid operators.
 */
void
test_evaluate_expression_invalid_operator(void) {
    const char* expression = "5 % 2"; /* Invalid operator */
    int32_t result;
    eval_error_t error_code = evaluate_expression(expression, &result);
    TEST_ASSERT_EQUAL(EVAL_ERROR_INVALID_OPERATOR, error_code);
    TEST_ASSERT_EQUAL_INT32(0, result); /* Assuming your implementation returns
                                           0 for invalid operators */
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
    UNITY_BEGIN(); /* Initialize unity test framework */

    /* Run all test cases */
    RUN_TEST(test_evaluate_expression_simple_addition);
    RUN_TEST(test_evaluate_expression_simple_subtraction);
    RUN_TEST(test_evaluate_expression_simple_multiplication);
    RUN_TEST(test_evaluate_expression_simple_division);
    RUN_TEST(test_evaluate_expression_with_parentheses);
    RUN_TEST(test_evaluate_expression_complex);
    RUN_TEST(test_evaluate_expression_division_by_zero);
    RUN_TEST(test_evaluate_expression_invalid_operator);

    return UNITY_END(); /* Return to test results */
}

/* ----------------------------- end of file -------------------------------- */
