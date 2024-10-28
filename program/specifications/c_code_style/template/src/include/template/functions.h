/**
 * \file            functions.h
 * \brief           function
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
 * This file is part of  template library.
 *
 * Author:          Vector Qiu <vetor.qiu@gmail.com>
 * Version:         v0.0.1
 */
#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

/* includes ----------------------------------------------------------------- */
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \defgroup        functions manager
 * \brief           functions manager
 * \{
 */

/* public config ------------------------------------------------------------ */

/* public define ------------------------------------------------------------ */

/* public typedef enum ------------------------------------------------------ */

/* public typedef struct ---------------------------------------------------- */
typedef uint8_t  my_type_t;
typedef uint32_t my_ptr_t;

typedef struct {
    uint32_t a;
} my_struct_t;

/* public typedef function -------------------------------------------------- */
/**
 * \brief           Rule 1
 * \note            - Every function which may have access from outside its
 *                  module, MUST include function prototype (or declaration)
 *                  - Function name MUST be lowercase, optionally separated with
 *                  underscore _ character
 *
 */
/* OK */
void my_func(void);
void myfunc(void);

/* Wrong */
void MYFunc(void);
void myFunc();

/**
 * \brief           Rule 2
 * \note            - When function returns pointer, align asterisk to return
 *                  type
 *
 */
/* OK */
const char*  my_func02(void);
my_struct_t* my_func03(int32_t a, int32_t b);

/* Wrong */
// clang-format off
const char *my_func04(void);
my_struct_t * my_func05(void);
// clang-format on

/* Wrong */
/*
void set(int32_t a);
const char * get(void);
*/
/* public variables extern -------------------------------------------------- */

/* public functions --------------------------------------------------------- */
/* For low-level code. */

/* For high-level code. */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FUNCTIONS_H__ */

/* ----------------------------- end of file -------------------------------- */
