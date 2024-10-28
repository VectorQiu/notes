/**
 * \file            functions.c
 * \brief           functions
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
/* includes ----------------------------------------------------------------- */
#include "./template/functions.h"

/* private config ----------------------------------------------------------- */

/* private define ----------------------------------------------------------- */

/* private typedef enum ----------------------------------------------------- */

/* private typedef struct --------------------------------------------------- */

/* private typedef function ------------------------------------------------- */

/* private variables -------------------------------------------------------- */

/* private function prototypes ---------------------------------------------- */
/**
 * \brief           Rule 3
 * \note            - Align all function prototypes (with the same/similar
 *                  functionality) for better readability
 */
/* OK, function names aligned */
static void      set(int32_t a);
static my_type_t get(void);
static my_ptr_t* get_ptr(void);

/* Wrong */
// clang-format off
void  set_name(int32_t a);
const char * get_name(void);

// clang-format on

/* public variables --------------------------------------------------------- */

/* public functions --------------------------------------------------------- */
/**
 * \brief           Rule 4
 * \note            Function implementation MUST include return type and
 *                  optional other keywords in separate line
 */
/* OK */
int32_t
foo(void) {
    return 0;
}

/* OK */
static const char*
get_string(void) {
    return "Hello world!\r\n";
}

/* Wrong */
// clang-format off
int32_t foo(void) {
    return 0;
}

// clang-format on

/* private functions -------------------------------------------------------- */

/* ----------------------------- end of file -------------------------------- */
