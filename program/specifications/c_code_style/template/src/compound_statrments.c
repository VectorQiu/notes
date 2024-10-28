/**
 * \file            compound_statrments.c
 * \brief           compound statrments source file
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
#include "./template/compound_statrments.h"

#include <stdio.h>

/* private config ----------------------------------------------------------- */

/* private define ----------------------------------------------------------- */

/* private typedef enum ----------------------------------------------------- */

/* private typedef struct --------------------------------------------------- */

/* private typedef function ------------------------------------------------- */

/* private variables -------------------------------------------------------- */

/* private function prototypes ---------------------------------------------- */
static int32_t do_a(void);
static void    do_b(int32_t b);
static void    do_c(void);
static uint8_t check(void);

/* public variables --------------------------------------------------------- */

/* public functions --------------------------------------------------------- */
/**
 * \brief           Rule 1
 * \note            - Every compound statement MUST include opening and closing
 *                  curly bracket, even if it includes only 1 nested statement
 *                  - Every compound statement MUST include single indent; when
 *                  nesting statements, include 1 indent size for each nest
 */
void
rule01(void) {
    uint8_t c;

    c = 1;
    /* OK */
    if (c) {
        do_a();
    } else {
        do_b(c);
    }

    /* Wrong */
    // clang-format off
    if (c)
        do_a();
    else
        do_b(c);


    /* Wrong */
    if (c) do_a();
    else do_b(c);
    // clang-format on
}

/**
 * \brief           Rule 2
 * \note            - In case of if or if-else-if statement, else MUST be in the
 *                  same line as closing bracket of first statement
 */
void
rule02(void) {
    uint8_t a, b;

    a = 1;
    b = 0;

    /* OK */
    if (a) {

    } else if (b) {

    } else {
    }

    /* Wrong */
    // clang-format off
    if (a) {

    }
    else {
    }

    /* Wrong */
    if (a) {

    }
    else
    {
    }
    // clang-format on
}

/**
 * \brief           Rule 3
 * \note            - In case of do-while statement, while part MUST be in the
 *                  same line as closing bracket of do part
 */
void
rule03(void) {
    /* OK */
    do {
        int32_t a;
        a = do_a();
        do_b(a);
    } while (check());

    // clang-format off
    /* Wrong */
    do
    {
        /* ... */
    } while (check());

    /* Wrong */
    do {
        /* ... */
    }
    while (check());
    // clang-format on
}

/**
 * \brief           Rule 4
 * \note            - Indentation is REQUIRED for every opening bracket
 *                  - Compound statement MUST include curly brackets, even in
 *                  the case of a single statement.
 */
void
rule04(void) {
    uint8_t a, c;

    a = 1;
    c = 0;

    if (a) {
        do_a();
    } else {
        do_b(a);
        if (c) {
            do_c();
        }
    }

    // clang-format off
    /* Wrong */
    if (a) do_b(a);
    else do_c();

    if (a) do_a(); else do_b(a);
    // clang-format on
}

/**
 * \brief           Rule 5
 * \note            - Empty while, do-while or for loops MUST include brackets
 *                  - If while (or for, do-while, etc) is empty (it can be the
 *                  case in embedded programming), use empty single-line
 *                  brackets
 */
void
rule05(void) {
    /* OK */
    while (check()) {
    }

    /* Wrong */
    // clang-format off
    while (check()); /* Wrong, curly brackets are missing. Can lead to compiler
                        warnings or unintentional bugs */

    while (check()) { }
    while (check()) {}
    // clang-format on
}

/**
 * \brief           Rule 6
 * \note            - Always prefer using loops in this order: for, do-while,
 *                  while
 *                  - Avoid incrementing variables inside loop block if
 *                  possible, see examples
 */
void
rule06(void) {

    /* Not recommended */
    int32_t a = 0;
    while (a < 10) {
        /* ... */
        ++a;
    }

    /* Better */
    for (size_t a = 0; a < 10; ++a) {
    }

    /* Better, if inc may not happen in every cycle */
    for (size_t a = 0; a < 10;) {
        if (check()) {
            ++a;
        }
    }
}

/**
 * \brief           Rule 7
 * \note            - Inline if statement MAY be used only for assignment or
 *                  function call operations
 *
 */
void
rule07(void) {
    /* OK */
    int a = check() ? 1 : 0;   /* Assignment */
    do_b(check() ? 1 : 0);     /* Function call */
    switch (check() ? 1 : 0) { /* ... */
    } /* OK */

    /* Wrong, this code is not well maintenable */
    check() ? do_a() : do_c();

    /* Rework to have better program flow */
    if (check()) {
        do_a();
    } else {
        do_c();
    }
}

/**
 * \brief           Rule 8 Switch statement
 * \note            - Add single indent for every case statement
 *                  - Use additional single indent for break statement in each
 *                  case or default statement
 *                  - Always include default statement
 *                  - If local variables are REQUIRED, use curly brackets and
 *                  put break statement inside.
 *                    - Put opening curly bracket in the same line as case
 *                      statement
 */
void
rule08(void) {
    /* OK, every case has single indent */
    /* OK, every break has additional indent */
    switch (check()) {
        case 0: do_a(); break;
        case 1: do_b(1); break;
        default: break;
    }

    // clang-format off
    /* Wrong, case indent missing */
    switch (check()) {
    case 0:
        do_a();
        break;
    case 1:
        do_b(1);
        break;
    default:
        break;
    }

    /* Wrong */
    switch (check()) {
        case 0:
            do_a();
        break;      /* Wrong, break MUST have indent as it is under case */
        case 1:
        do_b(1);     /* Wrong, indent under case is missing */
        break;
        default:
            break;
    }
    // clang-format on

    switch (check()) {
        /* OK */
        case 0: {
            int32_t a, b;
            char    c;
            a = 5;
            /* ... */
            break;
        }
            // clang-format off
        /* Wrong */
        case 1: {
            int32_t a;
            break;
        }

        /* Wrong, break shall be inside */
        case 2: {
            int32_t a;
        } break;
            // clang-format on
    }
}

/* private functions -------------------------------------------------------- */
/**
 * \brief           do a
 *
 * \return          int32_t
 */
static int32_t
do_a(void) {
    printf("do a ...\n");
    return 1;
}

/**
 * \brief           do b
 *
 * \param[in]       b:
 */
static void
do_b(int32_t b) {
    printf("do b ...\n");
}

/**
 * \brief           do c
 *
 */
static void
do_c(void) {
    printf("do c ...\n");
}

/**
 * \brief           check
 *
 * \return          uint8_t
 */
static uint8_t
check(void) {
    return 1;
}

/* ----------------------------- end of file -------------------------------- */
