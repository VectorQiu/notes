/**
 * \file            main.c
 * \brief           main
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
 * This file is part of calculator library.
 *
 * Author:          Vector Qiu <vetor.qiu@gmail.com>
 * Version:         v0.0.1
 */
/* includes ----------------------------------------------------------------- */
#include <stdio.h>
#include "./calculator/calculator.h"

/* public functions --------------------------------------------------------- */
int32_t
main(int32_t argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <Infix Expression>\n", argv[0]);
        return 1;
    }

    const char* expression = argv[1];
    int32_t result;
    eval_error_t error_code = evaluate_expression(expression, &result);
    if (error_code == EVAL_SUCCESS) {
        printf("Result: %d\n", result);
    } else {
        printf("Entering expression is wrong.\n");
    }
    return 0;
}

/* ----------------------------- end of file -------------------------------- */
