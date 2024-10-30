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
typedef enum {
    STACK_TYPE_NONE = 0,
    STACK_TYPE_CHAR,
    STACK_TYPE_STRING,
    STACK_TYPE_INT,
    STACK_TYPE_FLOAT,
    STACK_TYPE_DOUBLE,
    STACK_TYPE_MAX,
} stack_data_type_e;

/* public typedef struct ---------------------------------------------------- */
typedef struct {
    void* data;
    stack_data_type_e type;
} stack_node_t;

typedef void* stack_t;

/* public functions --------------------------------------------------------- */
stack_t stack_init(size_t depth);
int8_t push(stack_t s, stack_node_t node);
int8_t pop(stack_t s, stack_node_t* node);
int8_t peek(stack_t s, stack_node_t* node);
int8_t stack_is_empty(stack_t s);
int8_t stack_is_full(stack_t s);
void stack_free(stack_t s);
/**
 * \}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STACK_H__ */

/* ----------------------------- end of file -------------------------------- */
