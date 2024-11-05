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
#include <stdlib.h>
#include <string.h>
#include "./calculator/my_add.h"
#include "./calculator/my_div.h"
#include "./calculator/my_mul.h"
#include "./calculator/my_sub.h"
#include "./stack/stack.h"

/* private typedef enum ----------------------------------------------------- */
/**
 * \brief           Operator priority
 *
 */
typedef enum {
    OPERATOR_PRIORITY_INVALID = 0, /**< Invalid operator */
    OPERATOR_PRIORITY_LOW = 1,     /**< '+' and '-' operators */
    OPERATOR_PRIORITY_HIGH = 2     /**< '*' and '/' operators */
} operator_priority_t;

/* private function prototypes ---------------------------------------------- */
static eval_error_t calculate(int32_t a, int32_t b, char operator,
                              int32_t * result);
static operator_priority_t precedence(char operator);
static stack_node_t* create_node(const void* data, int type);
static eval_error_t handle_number(const char** ptr, stack_t num_stack);
static eval_error_t handle_operator(const char** ptr, stack_t num_stack,
                                    stack_t op_stack);
static eval_error_t process_operator(stack_t num_stack, char operator);

/* public functions --------------------------------------------------------- */
/**
 * \brief           Evaluate a mathematical expression in infix notation.
 *
 * This function parses and evaluates an infix expression (e.g., "3 + 5 * (2 -
 * 8)"). It handles operator precedence, parentheses, and multiple operators.
 * Two stacks are used: one for numbers and another for operators.
 *
 * \param[in]       expression: A null-terminated string containing the
 *                  mathematical expression to be evaluated.
 * \param[out]      result: A pointer to an integer where the result will be
 *                  stored.
 * \return          \ref:EVAL_SUCCESS on success, member of \ref eval_error_t
 *                  otherwise
 */
eval_error_t
evaluate_expression(const char* expression, int32_t* result) {
    if (expression == NULL || result == NULL) {
        return EVAL_ERROR_NULL_POINTER; /* Invalid input or null result pointer
                                         */
    }

    stack_t num_stack = stack_init(100);
    stack_t op_stack = stack_init(100);
    if (num_stack == NULL || op_stack == NULL) {
        return EVAL_ERROR_STACK_INIT;
    }

    const char* ptr = expression;
    while (*ptr != '\0') {
        if (isspace(*ptr)) { /* Skip spaces */
            ++ptr;
        } else if (isdigit(*ptr)) { /* Process numbers */
            if (handle_number(&ptr, num_stack) != EVAL_SUCCESS) {
                stack_free(num_stack);
                stack_free(op_stack);
                return EVAL_ERROR_MEMORY;
            }
        } else if (*ptr == '(') { /* Left parenthesis */
            stack_node_t* op_node = create_node((void*)ptr, STACK_TYPE_CHAR);
            if (op_node == NULL || op_node->data == NULL) {
                stack_free(num_stack);
                stack_free(op_stack);
                return EVAL_ERROR_MEMORY;
            }
            push(op_stack, op_node);
            ++ptr;
        } else if (*ptr == ')') { /* Right parenthesis */
            while (!stack_is_empty(op_stack)) {
                stack_node_t* op_node;
                if (pop(op_stack, &op_node) != STACK_SUCCESS) {
                    break;
                }
                char op = *(char*)op_node->data;
                free(op_node->data);
                free(op_node);

                if (op == '(') {
                    break; /* Stop at left parenthesis */
                }

                eval_error_t error_code = process_operator(num_stack, op);
                if (error_code != EVAL_SUCCESS) {
                    stack_free(num_stack);
                    stack_free(op_stack);
                    return error_code;
                }
            }
            ++ptr;
        } else { /* Operator */
            if (handle_operator(&ptr, num_stack, op_stack) != EVAL_SUCCESS) {
                stack_free(num_stack);
                stack_free(op_stack);
                return EVAL_ERROR_MEMORY;
            }
        }
    }

    /* Process remaining operators in the stack */
    while (!stack_is_empty(op_stack)) {
        stack_node_t* op_node;
        pop(op_stack, &op_node);
        char op = *(char*)op_node->data;
        free(op_node->data);
        free(op_node);

        eval_error_t error_code = process_operator(num_stack, op);
        if (error_code != EVAL_SUCCESS) {
            stack_free(num_stack);
            stack_free(op_stack);
            return error_code;
        }
    }

    stack_node_t* result_node;
    pop(num_stack, &result_node);
    *result = *(int32_t*)result_node->data;
    free(result_node->data);
    free(result_node);

    /* Release Stack */
    stack_free(num_stack);
    stack_free(op_stack);

    return EVAL_SUCCESS;
}

/* private functions -------------------------------------------------------- */
/**
 * \brief           Get the priority of the operator.
 *
 * \param[in]       operator: A character representing the operation
 *                            to be performed. It can be '+', '-', '*', or '/'.
 * \return          The precedence of the operator, as an enum:
 *                  - OPERATOR_PRIORITY_LOW (1) for '+' and '-'
 *                  - OPERATOR_PRIORITY_HIGH (2) for '*' and '/'
 *                  - OPERATOR_PRIORITY_INVALID (0) for invalid operators
 */
static operator_priority_t
precedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return OPERATOR_PRIORITY_LOW;
        case '*':
        case '/':
            return OPERATOR_PRIORITY_HIGH;
        default:
            return OPERATOR_PRIORITY_INVALID;
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
 *                  to be performed. It can be '+', '-', '*', or '/'.
 * \param[out]      result: The result of the operation.
 * \return          \ref: EVAL_SUCCESS on success, member of \ref eval_error_t
 *                  otherwise
 */
static eval_error_t
calculate(int32_t a, int32_t b, char operator, int32_t * result) {
    switch (operator) {
        case '+':
            *result = my_add(a, b);
            break;
        case '-':
            *result = my_sub(a, b);
            break;
        case '*':
            *result = my_mul(a, b);
            break;
        case '/':
            if (b == 0) {
                return EVAL_ERROR_DIV_BY_ZERO;
            }
            *result = my_div(a, b);
            break;
        default:
            return EVAL_ERROR_INVALID_OPERATOR;
    }

    return EVAL_SUCCESS;
}

/**
 * \brief           Create a stack node with the given data and type.
 *
 * This function allocates memory for a stack node based on the type
 * provided (integer or character) and initializes it with the given data.
 *
 * \param[in]       data: A pointer to the data to be stored in the node.
 * \param[in]       type: The type of data (either STACK_TYPE_INT or
 *                  STACK_TYPE_CHAR).
 * \return          The created stack node, or NULL if memory allocation failed.
 */
static stack_node_t*
create_node(const void* data, int type) {
    stack_node_t* node = malloc(sizeof(stack_node_t));
    if (node == NULL) {
        return NULL;
    }

    node->data = malloc(type == STACK_TYPE_INT ? sizeof(int32_t)
                                               : sizeof(char));
    if (node->data == NULL) {
        free(node);
        return NULL;
    }

    if (type == STACK_TYPE_INT) {
        *(int32_t*)node->data = *(int32_t*)data;
    } else {
        *(char*)node->data = *(char*)data;
    }
    node->type = type;

    return node;
}

/**
 * \brief           Handle a number in the expression.
 *
 * This function reads a sequence of digits from the expression,
 * constructs the corresponding integer, and pushes it onto the number stack.
 *
 * \param[in,out]   ptr: A pointer to the current position in the expression.
 * \param[in]       num_stack: The stack for storing numbers.
 * \return          0 on success, or -1 if memory allocation fails.
 */
static eval_error_t
handle_number(const char** ptr, stack_t num_stack) {
    int32_t num = 0;
    while (isdigit(**ptr)) {
        num = num * 10 + (**ptr - '0');
        ++(*ptr);
    }

    stack_node_t* num_node = create_node(&num, STACK_TYPE_INT);
    if (num_node == NULL || num_node->data == NULL) {
        return EVAL_ERROR_MEMORY;
    }
    push(num_stack, num_node);
    return EVAL_SUCCESS;
}

/**
 * \brief           Handle an operator in the expression.
 *
 * This function processes the current operator, applies it to the numbers
 * on the top of the number stack, and manages the operator stack according
 * to operator precedence.
 *
 * \param[in,out]   ptr: A pointer to the current position in the expression.
 * \param[in]       num_stack: The stack for storing numbers.
 * \param[in]       op_stack: The stack for storing operators.
 * \return          \ref: EVAL_SUCCESS on success, member of \ref eval_error_t
 *                  otherwise
 */
static eval_error_t
handle_operator(const char** ptr, stack_t num_stack, stack_t op_stack) {
    while (!stack_is_empty(op_stack)) {
        stack_node_t* top_op_node;
        peek(op_stack, &top_op_node);
        char top_op = *(char*)top_op_node->data;

        if (precedence(top_op) < precedence(**ptr)) {
            break; /* Current operator has higher precedence */
        }

        pop(op_stack, &top_op_node);
        free(top_op_node->data);

        eval_error_t error_code = process_operator(num_stack, top_op);
        if (error_code != EVAL_SUCCESS) {
            return error_code;
        }
    }

    stack_node_t* op_node = create_node(*ptr, STACK_TYPE_CHAR);
    if (op_node->data == NULL) {
        return EVAL_ERROR_MEMORY;
    }
    push(op_stack, op_node);
    ++(*ptr);
    return EVAL_SUCCESS;
}

/**
 * \brief           Process an operator and apply it to the top two numbers in
 * the stack.
 *
 * This function pops the top two numbers from the number stack, applies the
 * given operator to them, and pushes the result back onto the number stack. It
 * also handles memory management for the stack nodes.
 *
 * \param[in]       num_stack: The stack holding the numbers.
 * \param[in]       operator: The operator to be applied to the two topmost
 *                  numbers in the stack.
 *
 * \return          \ref EVAL_SUCCESS on successful execution,member of \ref
 * e                val_error_t otherwise
 */
static eval_error_t
process_operator(stack_t num_stack, char operator) {
    stack_node_t *b_node, *a_node;
    pop(num_stack, &b_node);
    pop(num_stack, &a_node);

    int32_t result;
    eval_error_t error_code = calculate(
        *(int32_t*)a_node->data, *(int32_t*)b_node->data, operator, & result);
    if (error_code != EVAL_SUCCESS) {
        return error_code;
    }

    free(a_node->data);
    free(a_node);
    free(b_node->data);
    free(b_node);

    stack_node_t* result_node = create_node(&result, STACK_TYPE_INT);
    if (!result_node || !result_node->data) {
        return EVAL_ERROR_MEMORY;
    }
    push(num_stack, result_node);

    return EVAL_SUCCESS;
}

/* ----------------------------- end of file -------------------------------- */
