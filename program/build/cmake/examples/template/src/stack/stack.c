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
/**
 * \brief           Private stack structure
 */
typedef struct {
    int32_t num;         /*!< Maximum number of elements in the stack */
    stack_node_t* nodes; /*!< Pointer to stack nodes */
    int32_t top;         /*!< Index of the top element in the stack */
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
stack_init(int32_t depth) {
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
 * \return          \ref:STACK_SUCCESS on success, member of \ref stack_error_t
 *                  otherwise
 */
stack_error_t
push(stack_t s, stack_node_t node) {
    if (s == NULL) {
        return STACK_ERROR_NULL_POINTER;
    }

    if (stack_is_full(s)) {
        return STACK_ERROR_FULL;
    }

    if (node.type <= STACK_TYPE_NONE || node.type >= STACK_TYPE_MAX) {
        return STACK_ERROR_INVALID_TYPE;
    }

    prv_stack_t* stack = s;
    ++stack->top;
    stack->nodes[stack->top].data = malloc(sizeof(node.data));
    if (stack->nodes[stack->top].data == NULL) {
        --stack->top;
        return STACK_ERROR_MEMORY;
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
            --stack->top;
            return STACK_ERROR_INVALID_TYPE; /* Invalid type */
    }
    stack->nodes[stack->top].type = node.type;

    return STACK_SUCCESS;
}

/**
 * \brief           Pop stacks
 *
 * \param[in]       s: Pointer of stack structure
 * \param[in]       node: Pop stack node
 * \return          \ref:STACK_SUCCESS on success, member of \ref stack_error_t
 *                  otherwise
 * \note            The caller is responsible for freeing the memory of the
 *                  popped node's data after use to avoid memory leaks.
 */
stack_error_t
pop(stack_t s, stack_node_t* node) {
    if (s == NULL) {
        return STACK_ERROR_NULL_POINTER;
    }

    if (stack_is_empty(s)) {
        return STACK_ERROR_EMPTY;
    }

    prv_stack_t* stack = s;
    *node = stack->nodes[stack->top];
    --stack->top;
    return STACK_SUCCESS;
}

/**
 * \brief           Look at the top element of the stack
 *
 * \param[in]       s: Pointer of stack structure
 * \param[in]       node: The node of the element at the top of the stack
 * \return          \ref:STACK_SUCCESS on success, member of \ref stack_error_t
 *                  otherwise
 */
stack_error_t
peek(stack_t s, stack_node_t* node) {
    if (s == NULL) {
        return STACK_ERROR_NULL_POINTER;
    }

    if (stack_is_empty(s)) {
        return STACK_ERROR_EMPTY;
    }

    prv_stack_t* stack = s;
    *node = stack->nodes[stack->top];
    return STACK_SUCCESS;
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
 * \brief           Get the remaining space in the stack
 *
 * \param[in]       s: Pointer to the stack structure
 * \return          The number of available spaces in the stack,
 *                  or -1 if the stack pointer is NULL
 */
int32_t
stack_remaining_space(stack_t s) {
    if (s == NULL) {
        return -1; /* Return -1 if the stack pointer is NULL */
    }

    prv_stack_t* stack = s;
    return stack->num - (stack->top + 1); /* Total capacity minus used spaces */
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
