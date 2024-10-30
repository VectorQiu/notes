/**
 * \file            stack.c
 * \brief           Stack data structure
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
 * This file is part of the stack library.
 *
 * Author:          Vector Qiu <vetor.qiu@gmail.com>
 * Version:         v0.0.1
 */
/* includes ----------------------------------------------------------------- */
#include "./stack/stack.h"

#include <stdlib.h>
#include <string.h>

/* private typedef function ------------------------------------------------- */
typedef struct {
    size_t num;
    stack_node_t* nodes;
    int32_t top;
} prv_stack_t;

/* public functions --------------------------------------------------------- */
/**
 * \brief           Stack structure initialization
 *
 * \param[in]       depth: The depth of the stack
 * \return          Pointer to output Stack structure on success, `NULL`
 *                  otherwise
 */
stack_t
stack_init(size_t depth) {
    prv_stack_t* stack;

    stack = malloc(sizeof(prv_stack_t));
    if (stack == NULL) {
        return NULL;
    }

    stack->num = depth;
    stack->top = -1;
    stack->nodes = malloc(depth * sizeof(stack_node_t));
    if (stack->nodes == NULL) {
        free(stack);
        return NULL;
    }

    return (stack_t)stack;
}

/**
 * \brief           Push stacks
 *
 * \param[in]       s: Pointer of stack structure
 * \param[in]       node: Push stack node
 * \return          Successfully returned 0
 *                  When the stack pointer is NULL, return -1
 *                  Stack full, return -2
 *                  Stack node type invalid, return -4
 */
int8_t
push(stack_t s, stack_node_t node) {
    if (s == NULL) {
        return -1;
    }

    if (stack_is_full(s)) {
        return -2;
    }

    if (node.type <= STACK_TYPE_NONE || node.type >= STACK_TYPE_MAX) {
        return -4;
    }

    prv_stack_t* stack = s;
    stack->top += 1;
    stack->nodes[stack->top].data = malloc(sizeof(node.data));
    if (stack->nodes[stack->top].data == NULL) {
        return -5;
    }

    switch (node.type) {
        case STACK_TYPE_CHAR:
            *(char*)stack->nodes[stack->top].data = *(char*)node.data;
            break;
        case STACK_TYPE_STRING:
            stack->nodes[stack->top].data = strdup((char*)node.data);
            break;
        case STACK_TYPE_INT:
            *(int32_t*)stack->nodes[stack->top].data = *(int32_t*)node.data;
            break;
        case STACK_TYPE_FLOAT:
            *(float*)stack->nodes[stack->top].data = *(float*)node.data;
            break;
        case STACK_TYPE_DOUBLE:
            *(double*)stack->nodes[stack->top].data = *(double*)node.data;
            break;
        default:
            free(stack->nodes[stack->top].data);
            return -4; /* Invalid type */
    }
    stack->nodes[stack->top].type = node.type;

    return 0;
}

/**
 * \brief           Pop stacks
 *
 * \param[in]       s: Pointer of stack structure
 * \param[in]       node: Pop stack node
 * \return          Successfully returned 0
 *                  When the stack pointer is NULL, return -1
 *                  Stack empty, return -3
 */
int8_t
pop(stack_t s, stack_node_t* node) {
    if (s == NULL) {
        return -1;
    }

    if (stack_is_empty(s)) {
        return -3;
    }

    prv_stack_t* stack = s;
    *node = stack->nodes[stack->top];
    stack->top -= 1;
    return 0;
}

/**
 * \brief           Look at the top element of the stack
 *
 * \param[in]       s: Pointer of stack structure
 * \param[in]       node: The node of the element at the top of the stack
 * \return          Successfully returned 0
 *                  When the stack pointer is NULL, return -1
 *                  Stack empty, return -3
 */
int8_t
peek(stack_t s, stack_node_t* node) {
    if (s == NULL) {
        return -1;
    }

    if (stack_is_empty(s)) {
        return -3;
    }

    prv_stack_t* stack = s;
    *node = stack->nodes[stack->top];
    return 0;
}

/**
 * \brief           Check if the stack is empty
 *
 * \param[in]       s: Pointer of stack structure
 * \return          The stack is empty and returns 1
 *                  The stack is not empty and returns 0
 *                  When the stack pointer is NULL, return -1
 */
int8_t
stack_is_empty(stack_t s) {
    if (s == NULL) {
        return -1;
    }

    prv_stack_t* stack = s;
    return (stack->top == -1) ? 1 : 0;
}

/**
 * \brief           Check if the stack is full
 *
 * \param[in]       s: Pointer of stack structure
 * \return          The stack is full and returns 1
 *                  The stack is not full and returns 0
 *                  When the stack pointer is NULL, return -1
 */
int8_t
stack_is_full(stack_t s) {
    if (s == NULL) {
        return -1;
    }

    prv_stack_t* stack = s;
    return (stack->top == stack->num - 1) ? 1 : 0;
}

/**
 * \brief           Stack structure free
 *
 * \param[in]       s: Pointer of stack structure
 */
void
stack_free(stack_t s) {
    if (s == NULL) {
        return;
    }

    prv_stack_t* stack = s;
    while (!stack_is_empty(s)) {
        stack_node_t node;
        pop(s, &node);
        if (node.data != NULL) {
            free(node.data);
        }
    }
    free(stack->nodes);
    free(stack);
}

/* ----------------------------- end of file -------------------------------- */
