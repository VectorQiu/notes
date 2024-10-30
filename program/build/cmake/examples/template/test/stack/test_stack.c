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
 * This file is part of  stack library.
 *
 * Author:          Vector Qiu <vetor.qiu@gmail.com>
 * Version:         v0.0.1
 */
/* includes ----------------------------------------------------------------- */
#include "unity.h"

#include "./calculator/stack.h"

void
set_up(void) {
    // 在每个测试之前运行
}

void
tear_down(void) {
    // 在每个测试之后运行
}

void
test_stack_init(void) {
    stack_t stack = stack_init(10);
    TEST_ASSERT_NOT_NULL(stack);
    TEST_ASSERT_EQUAL_INT(10, ((prv_stack_t*)stack)->num);
    TEST_ASSERT_EQUAL_INT(-1, ((prv_stack_t*)stack)->top);
    stack_free(stack);
}

void
test_stack_push_pop(void) {
    stack_t stack = stack_init(2);
    TEST_ASSERT_NOT_NULL(stack);

    stack_node_t node;

    // 测试推入整数
    int32_t int_data = 42;
    node.data = &int_data;
    node.type = STACK_TYPE_INT;
    TEST_ASSERT_EQUAL_INT(0, push(stack, node));

    // 测试弹出整数
    stack_node_t popped_node;
    TEST_ASSERT_EQUAL_INT(0, pop(stack, &popped_node));
    TEST_ASSERT_EQUAL_INT(int_data, *(int32_t*)popped_node.data);
    free(popped_node.data);

    // 测试栈满
    node.data = &int_data;
    node.type = STACK_TYPE_INT;
    push(stack, node);
    node.data = &int_data;
    TEST_ASSERT_EQUAL_INT(0, push(stack, node));  // 第二次推入成功
    TEST_ASSERT_EQUAL_INT(-2, push(stack, node)); // 栈满时返回 -2

    stack_free(stack);
}

void
test_stack_peek(void) {
    stack_t stack = stack_init(10);
    TEST_ASSERT_NOT_NULL(stack);

    stack_node_t node;
    int32_t      int_data = 42;
    node.data = &int_data;
    node.type = STACK_TYPE_INT;
    push(stack, node);

    stack_node_t peeked_node;
    TEST_ASSERT_EQUAL_INT(0, peek(stack, &peeked_node));
    TEST_ASSERT_EQUAL_INT(int_data, *(int32_t*)peeked_node.data);

    stack_free(stack);
}

void
test_stack_empty_full(void) {
    stack_t stack = stack_init(2);
    TEST_ASSERT_NOT_NULL(stack);
    TEST_ASSERT_EQUAL_INT(1, stack_is_empty(stack));
    TEST_ASSERT_EQUAL_INT(0, stack_is_full(stack));

    int32_t      int_data = 42;
    stack_node_t node = {.data = &int_data, .type = STACK_TYPE_INT};
    push(stack, node);
    TEST_ASSERT_EQUAL_INT(0, stack_is_empty(stack));
    TEST_ASSERT_EQUAL_INT(0, stack_is_full(stack));

    push(stack, node);
    TEST_ASSERT_EQUAL_INT(1, stack_is_full(stack));

    stack_free(stack);
}

void
test_stack_free(void) {
    stack_t stack = stack_init(2);
    TEST_ASSERT_NOT_NULL(stack);
    stack_free(stack); // 检查是否能正常释放
}

int
main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_stack_init);
    RUN_TEST(test_stack_push_pop);
    RUN_TEST(test_stack_peek);
    RUN_TEST(test_stack_empty_full);
    RUN_TEST(test_stack_free);

    return UNITY_END();
}

/* ----------------------------- end of file -------------------------------- */
