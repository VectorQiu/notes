/**
 * \file            calculator.c
 * \brief           Calculator library implementation
 * \date            2024-10-28
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
#include "./calculator/calculator.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./calculator/my_add.h"
#include "./calculator/my_div.h"
#include "./calculator/my_mul.h"
#include "./calculator/my_sub.h"
#include "./stack/stack.h"

/* private function prototypes ---------------------------------------------- */
static int32_t calculate(int32_t a, int32_t b, char operator);
static int32_t precedence(char operator);

/* public functions --------------------------------------------------------- */
/**
 * \brief           Evaluate a mathematical expression in infix notation.
 *
 * This function takes a string representing a mathematical expression
 * in infix notation (e.g., "3 + 5 * ( 2 - 8 )") and computes its result.
 * It uses two stacks: one for numbers and another for operators to handle
 * operator precedence and parentheses.
 *
 * \param[in]       expression: A null-terminated string containing the
 *                              mathematical expression to be evaluated.
 *                              The expression must be properly formatted
 *                              with spaces separating numbers and operators.
 * \return          int32_t: The result of the evaluated expression.
 *                          If there is an error during evaluation,
 *                          the function returns 0.
 */
int32_t
evaluate_expression(const char* expression) {
    stack_t num_stack = stack_init(100);
    stack_t op_stack = stack_init(100);
    if (num_stack == NULL || op_stack == NULL) {
        printf("Error: Stack initialization failed.\n");
        return 0;
    }

    const char* ptr = expression;
    while (*ptr != '\0') {
        if (isspace(*ptr)) { /* jump space */
            ++ptr;
            continue;
        }

        if (isdigit(*ptr)) { /* number */
            int32_t num = 0;
            while (isdigit(*ptr)) { /* read the complete number */
                num = num * 10 + (*ptr - '0');
                ++ptr;
            }

            stack_node_t num_node = {
                .data = malloc(sizeof(int32_t)),
                .type = STACK_TYPE_INT,
            };
            *(int32_t*)num_node.data = num;
            push(num_stack, num_node);
        } else if (*ptr == '(') { /* Left bracket */
            stack_node_t op_node = {
                .data = malloc(sizeof(char)),
                .type = STACK_TYPE_CHAR,
            };
            *(char*)op_node.data = *ptr;
            push(op_stack, op_node);
            ++ptr;
        } else if (*ptr == ')') { /* Right bracket: calculate until you
                                     encounter left brackets */
            while (!stack_is_empty(op_stack)) {
                stack_node_t op_node;
                pop(op_stack, &op_node);
                char op = *(char*)op_node.data;
                free(op_node.data);

                if (op == '(') {
                    break;
                }

                stack_node_t b_node, a_node;
                pop(num_stack, &b_node);
                pop(num_stack, &a_node);
                int32_t result = calculate(*(int32_t*)a_node.data,
                                           *(int32_t*)b_node.data, op);
                free(a_node.data);
                free(b_node.data);

                stack_node_t result_node = {
                    .data = malloc(sizeof(int32_t)),
                    .type = STACK_TYPE_INT,
                };
                *(int32_t*)result_node.data = result;
                push(num_stack, result_node);
            }
            ++ptr;
        } else { /* Operator */
            while (!stack_is_empty(op_stack)) {
                stack_node_t top_op_node;
                peek(op_stack, &top_op_node);
                char top_op = *(char*)top_op_node.data;

                if (precedence(top_op) < precedence(*ptr)) {
                    break; /*the current operating character is higher priority
                              stop */
                }

                pop(op_stack, &top_op_node);
                free(top_op_node.data);

                stack_node_t b_node, a_node;
                pop(num_stack, &b_node);
                pop(num_stack, &a_node);
                int32_t result = calculate(*(int32_t*)a_node.data,
                                           *(int32_t*)b_node.data, top_op);
                free(a_node.data);
                free(b_node.data);

                stack_node_t result_node = {
                    .data = malloc(sizeof(int32_t)),
                    .type = STACK_TYPE_INT,
                };
                *(int32_t*)result_node.data = result;
                push(num_stack, result_node);
            }

            /* the current operating symbol is pressed into the operating zone
             * stack */
            stack_node_t op_node = {
                .data = malloc(sizeof(char)),
                .type = STACK_TYPE_CHAR,
            };
            *(char*)op_node.data = *ptr;
            push(op_stack, op_node);
            ++ptr;
        }
    }

    /* Clean up remaining operators */
    while (!stack_is_empty(op_stack)) {
        stack_node_t op_node;
        pop(op_stack, &op_node);
        char op = *(char*)op_node.data;
        free(op_node.data);

        stack_node_t b_node, a_node;
        pop(num_stack, &b_node);
        pop(num_stack, &a_node);
        int32_t result = calculate(*(int32_t*)a_node.data,
                                   *(int32_t*)b_node.data, op);
        free(a_node.data);
        free(b_node.data);

        stack_node_t result_node = {
            .data = malloc(sizeof(int32_t)),
            .type = STACK_TYPE_INT,
        };
        *(int32_t*)result_node.data = result;
        push(num_stack, result_node);
    }

    int32_t final_result;
    stack_node_t result_node;
    pop(num_stack, &result_node);
    final_result = *(int32_t*)result_node.data;
    free(result_node.data);

    /* Release Stack */
    stack_free(num_stack);
    stack_free(op_stack);

    return final_result;
}

/* private functions -------------------------------------------------------- */
/**
 * \brief           Get the priority of the operator
 *
 * \param[in]       operator: A character representing the operation
 *                            to be performed. It can be '+', '-', '*', or '/'.
 * \return          priority of the operator
 */
static int32_t
precedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

/**
 * \brief           Perform basic arithmetic operations.
 *
 * This function takes two integers and an operator as input,
 * and performs the specified operation. It supports addition,
 * subtraction, multiplication, and division.
 *
 * \param[in]       a: The first operand (integer).
 * \param[in]       b: The second operand (integer).
 * \param[in]       operator: A character representing the operation
 *                            to be performed. It can be '+', '-', '*', or '/'.
 * \return          int32_t: The result of the arithmetic operation.
 *                          If division by zero is attempted, it returns 0.
 */
static int32_t
calculate(int32_t a, int32_t b, char operator) {
    switch (operator) {
        case '+':
            return my_add(a, b);
        case '-':
            return my_sub(a, b);
        case '*':
            return my_mul(a, b);
        case '/':
            if (b == 0) {
                printf("Error: Division by zero.\n");
                return 0; // or handle error as needed
            }
            return my_div(a, b);
        default:
            printf("Error: Invalid operator '%c'.\n", operator);
            return 0; // or handle error as needed
    }
}

/* ----------------------------- end of file -------------------------------- */
