/**
 * \file            calculator.h
 * \brief           Calculator library
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
#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

/* includes ----------------------------------------------------------------- */
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \defgroup        Calculator manager
 * \brief           Calculator manager
 * \{
 */
/* public typedef enum ------------------------------------------------------ */
/**
 * \brief           Enum for evaluate_expression error codes
 */
typedef enum {
    EVAL_SUCCESS = 0,            /*!< Success: Evaluation completed */
    EVAL_ERROR_STACK_INIT,       /*!< Error: Stack initialization failed */
    EVAL_ERROR_MEMORY,           /*!< Error: Memory allocation failed */
    EVAL_ERROR_NULL_POINTER,     /*!< Error: Invalid operator or invalid
                                  input expression */
    EVAL_ERROR_DIV_BY_ZERO,      /*!< Error: Division by zero */
    EVAL_ERROR_INVALID_OPERATOR, /*!< Error: Invalid operator */

} eval_error_t;

/* public functions --------------------------------------------------------- */
eval_error_t evaluate_expression(const char* expression, int32_t* result);
/**
 * \}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __CALCULATOR_H__ */

/* ----------------------------- end of file -------------------------------- */
