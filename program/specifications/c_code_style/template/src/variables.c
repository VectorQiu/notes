/**
 * \file            variables.c
 * \brief           variables source file
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
#include "./template/variables.h"

/* private config ----------------------------------------------------------- */

/* private define ----------------------------------------------------------- */

/* private typedef enum ----------------------------------------------------- */

/* private typedef struct --------------------------------------------------- */

/* private typedef function ------------------------------------------------- */

/* private variables -------------------------------------------------------- */
/**
 * \brief           Rule 1
 * \note            - Make variable name all lowercase with optional
 *                  underscore _ character
 */
/* OK */
int32_t a;
int32_t my_var;
int32_t myvar;

/* Wrong */
int32_t A;
int32_t myVar;
int32_t MYVar;

/* private function prototypes ---------------------------------------------- */

/* public variables --------------------------------------------------------- */

/* public functions --------------------------------------------------------- */
/**
 * \brief           Rule 2
 * \note            - Group local variables together by type
 *
 * \return          uint32_t
 */
uint32_t
foo(void) {
    int32_t a, b; /* OK */

    char a;
    char b; /* Wrong, char type already exists */

    return 1;
}

/**
 * \brief           Rule 3
 * \note            - Do not declare variable after first executable statement
 */
void
test(void) {
    int32_t a;
    a = foo();
    int32_t b; /* Wrong, there is already executable statement */
}

/**
 * \brief           Rule 4
 * \note            - You may declare new variables inside next indent level
 */
void
send(void) {
    int32_t a, b;
    a = foo();

    if (a == 0) {
        int32_t c, d; /* OK, c and d are in if-statement scope */
        c = foo();
        /* Wrong, there was already executable statement inside block */
        int32_t e;
    }
}

/**
 * \brief           Rule 5
 * \note            - Declare pointer variables with asterisk aligned to type
 */
void
rule05(void) {
    /* OK */
    char* a;

    /* Wrong */
    // clang-format off
    char *b;
    char * c;
    // clang-format on
}

/**
 * \brief           Rule 6
 * \note            - When declaring multiple pointer variables, you may declare
 *                  them with asterisk aligned to variable name
 */
void
rule06(void) {
    /* OK */
    char *p, *n;
}

/* private functions -------------------------------------------------------- */

/* ----------------------------- end of file -------------------------------- */
