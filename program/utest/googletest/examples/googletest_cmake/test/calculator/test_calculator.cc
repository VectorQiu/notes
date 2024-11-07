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
#include <gtest/gtest.h>
#include "./calculator/calculator.h"

/* public functions --------------------------------------------------------- */

class CalculatorTest : public ::testing::Test {
  protected:
    void
    SetUp() override {
        /* This function is called before each test runs. */
    }

    void
    TearDown() override {
        /* This function is called after each test runs. */
    }
};

/**
 * \brief           Test simple addition expression
 *
 * This test checks the evaluation of a simple addition expression
 * "3 + 5" and asserts that the result equals 8.
 */
TEST_F(CalculatorTest, SimpleAddition) {
    const char* expression = "3 + 5";
    int32_t result;
    eval_error_t error_code = evaluate_expression(expression, &result);
    EXPECT_EQ(error_code, EVAL_SUCCESS);
    EXPECT_EQ(result, 8);
}

/**
 * \brief           Test simple subtraction expression
 *
 * This test checks the evaluation of a simple subtraction expression
 * "10 - 4" and asserts that the result equals 6.
 */
TEST_F(CalculatorTest, SimpleSubtraction) {
    const char* expression = "10 - 4";
    int32_t result;
    eval_error_t error_code = evaluate_expression(expression, &result);
    EXPECT_EQ(error_code, EVAL_SUCCESS);
    EXPECT_EQ(result, 6);
}

/**
 * \brief           Test simple multiplication expression
 *
 * This test checks the evaluation of a simple multiplication expression
 * "3 * 4" and asserts that the result equals 12.
 */
TEST_F(CalculatorTest, SimpleMultiplication) {
    const char* expression = "3 * 4";
    int32_t result;
    eval_error_t error_code = evaluate_expression(expression, &result);
    EXPECT_EQ(error_code, EVAL_SUCCESS);
    EXPECT_EQ(result, 12);
}

/**
 * \brief           Test simple division expression
 *
 * This test checks the evaluation of a simple division expression
 * "8 / 2" and asserts that the result equals 4.
 */
TEST_F(CalculatorTest, SimpleDivision) {
    const char* expression = "8 / 2";
    int32_t result;
    eval_error_t error_code = evaluate_expression(expression, &result);
    EXPECT_EQ(error_code, EVAL_SUCCESS);
    EXPECT_EQ(result, 4);
}

/**
 * \brief           Test expression evaluation with parentheses
 *
 * This test checks the evaluation of an expression that includes
 * parentheses: "3 + (2 * 5)" and asserts that the result equals 13.
 */
TEST_F(CalculatorTest, ExpressionWithParentheses) {
    const char* expression = "3 + (2 * 5)";
    int32_t result;
    eval_error_t error_code = evaluate_expression(expression, &result);
    EXPECT_EQ(error_code, EVAL_SUCCESS);
    EXPECT_EQ(result, 13);
}

/**
 * \brief           Test complex expression evaluation
 *
 * This test checks the evaluation of a complex expression
 * "3 + 5 * (2 - 8)" and asserts that the result equals -27.
 */
TEST_F(CalculatorTest, ComplexExpression) {
    const char* expression = "3 + 5 * (2 - 8)";
    int32_t result;
    eval_error_t error_code = evaluate_expression(expression, &result);
    EXPECT_EQ(error_code, EVAL_SUCCESS);
    EXPECT_EQ(result, -27);
}

/**
 * \brief           Test division by zero scenario
 *
 * This test checks the behavior when attempting to divide by zero
 * "10 / 0". It asserts that the result equals 0, as the implementation
 * is expected to handle division by zero.
 */
TEST_F(CalculatorTest, DivisionByZero) {
    const char* expression = "10 / 0";
    int32_t result;
    eval_error_t error_code = evaluate_expression(expression, &result);
    EXPECT_EQ(error_code, EVAL_ERROR_DIV_BY_ZERO);
}

/**
 * \brief           Test invalid operator scenario
 *
 * This test checks the behavior when an invalid operator is used
 * "5 % 2". It asserts that the result equals 0, as the implementation
 * is expected to return 0 for invalid operators.
 */
TEST_F(CalculatorTest, InvalidOperator) {
    const char* expression = "5 % 2"; // Invalid operator
    int32_t result;
    eval_error_t error_code = evaluate_expression(expression, &result);
    EXPECT_EQ(error_code, EVAL_ERROR_INVALID_OPERATOR);
}

/* private functions -------------------------------------------------------- */
/**
 * \brief           Main function for running tests
 *
 * This function initializes the Unity test framework, runs all the
 * defined test cases, and returns the test results.
 */
/*
int
main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
*/
/* ----------------------------- end of file -------------------------------- */
