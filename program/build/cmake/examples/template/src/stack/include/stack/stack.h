/**
 * \file            stack.h
 * \brief           Stack data structure header file
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
 * This file is part of the Stack library.
 *
 * Author:          Vector Qiu <vetor.qiu@gmail.com>
 * Version:         v0.0.1
 */
#ifndef __STACK_H__
#define __STACK_H__

/* includes ----------------------------------------------------------------- */
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \defgroup        Stack data structure manager
 * \brief           Stack data structure manager
 * \{
 */

/* public typedef enum ------------------------------------------------------ */
/**
 * \brief           Data types that can be stored in the stack
 */
typedef enum {
    STACK_TYPE_NONE = 0, /*!< No type (invalid) */
    STACK_TYPE_CHAR,     /*!< Character type */
    STACK_TYPE_STRING,   /*!< String type */
    STACK_TYPE_INT,      /*!< Integer type */
    STACK_TYPE_FLOAT,    /*!< Float type */
    STACK_TYPE_DOUBLE,   /*!< Double type */
    STACK_TYPE_MAX,      /*!< Maximum type value (used for validation) */
} stack_data_type_e;

/**
 * \brief           Stack error codes
 */
typedef enum {
    STACK_SUCCESS = 0,             /*!< Operation successful */
    STACK_ERROR_NULL_POINTER = -1, /*!< Null pointer error */
    STACK_ERROR_FULL = -2,         /*!< Stack full error */
    STACK_ERROR_EMPTY = -3,        /*!< Stack empty error */
    STACK_ERROR_INVALID_TYPE = -4, /*!< Invalid node type error */
    STACK_ERROR_MEMORY = -5        /*!< Memory allocation error */
} stack_error_t;

/* public typedef struct ---------------------------------------------------- */
/**
 * \brief           Stack node structur
 *
 */
typedef struct {
    void* data;             /*!< Pointer to the data stored in the node */
    stack_data_type_e type; /*!< Type of the data stored in the node */
} stack_node_t;

typedef void* stack_t;

/* public functions --------------------------------------------------------- */
stack_t stack_init(int32_t depth);
stack_error_t push(stack_t s, stack_node_t node);
stack_error_t pop(stack_t s, stack_node_t* node);
stack_error_t peek(stack_t s, stack_node_t* node);
int8_t stack_is_empty(stack_t s);
int8_t stack_is_full(stack_t s);
int32_t stack_remaining_space(stack_t s);
void stack_free(stack_t s);
/**
 * \}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STACK_H__ */

/* ----------------------------- end of file -------------------------------- */
