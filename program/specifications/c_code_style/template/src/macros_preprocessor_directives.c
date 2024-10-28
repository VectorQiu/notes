/**
 * \file            macros_preprocessor_directives.c
 * \brief           macros_preprocessor_directives source file
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
#include "./template/macros_preprocessor_directives.h"

/* private config ----------------------------------------------------------- */

/* private define ----------------------------------------------------------- */
/**
 * \brief           Rule 1
 * \note            - Always use macros instead of literal constants, especially
 *                  for numbers
 *                  - All macros MUST be fully uppercase, with optional
 *                  underscore _ character, except if they are clearly marked as
 *                  function which may be in the future replaced with regular
 *                  function syntax
 */
/* OK */
#define SQUARE(x) ((x) * (x))

/* Wrong */
#define square(x) ((x) * (x))

/**
 * \brief           Rule 2
 * \note            - Always protect input parameters with parentheses
 */
/* OK */
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#if 0
/* Wrong */
#define MIN(x, y) x < y ? x : y
#endif
/**
 * \brief           Rule 3
 * \note            - Always protect final macro evaluation with parenthesis
 */
/* Wrong */
#define MIN(x, y) (x) < (y) ? (x) : (y)
#define SUM(x, y) (x) + (y)
#if 0
/* Imagine result of this equation using wrong SUM implementation */
int32_t x = 5 * SUM(3, 4); /* Expected result is 5 * 7 = 35 */
int32_t x = 5 * (3) + (4); /* It is evaluated to this, final result = 19 which
                              is not what we expect */
#endif
/* Correct implementation */
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define SUM(x, y) ((x) + (y))

/**
 * \brief           Rule 4
 * \note            - When macro uses multiple statements, protect these using
 *                  do {} while (0) statement
 */
typedef struct {
    int32_t px, py;
} point_t;

point_t p; /* Define new point */

#if 0
/* Wrong implementation */

/* Define macro to set point */
#define SET_POINT(p, x, y)                                                     \
    (p)->px = (x);                                                             \
    (p)->py = (y) /* 2 statements. Last one should not implement semicolon */

SET_POINT(&p, 3, 4); /* Set point to position 3, 4. This evaluates to... */
(&p)->px = (3);
(&p)->py = (4); /* ... to this. In this example this is not a problem. */

/* Consider this ugly code, however it is valid by C standard (not recommended)
 */
if (a) {                     /* If a is true */
    if (b)                  /* If b is true */
        SET_POINT(&p, 3, 4); /* Set point to x = 3, y = 4 */
    else
        SET_POINT(&p, 5, 6); /* Set point to x = 5, y = 6 */
}

/* Evaluates to code below. Do you see the problem? */
if (a) {
    if (b)
        (&p)->px = (3); (&p)->py = (4);
    else
        (&p)->px = (5); (&p)->py = (6);

/* Or if we rewrite it a little */
if (a) {
    if (b)
        (&p)->px = (3);
        (&p)->py = (4);
    else
        (&p)->px = (5);
        (&p)->py = (6);
#endif
/*
 * Ask yourself a question: To which `if` statement does the `else` keyword
 * belong?
 *
 * Based on first part of code, answer is straight-forward. To inner `if`
 * statement when we check `b` condition Actual answer: Compilation error as
 * `else` belongs nowhere
 */

/* Better and correct implementation of macro */
#define SET_POINT(p, x, y)                                                     \
    do {                                                                       \
        (p)->px = (x);                                                         \
        (p)->py = (y);                                                         \
    } while (0) /* 2 statements. No semicolon after while loop */
#if 0
    /* Now original code evaluates to */
    if (a) {
        if (b) {
            do {
                (&p)->px = (3);
                (&p)->py = (4);
            } while (0);
        } else {
            do {
                (&p)->px = (5);
                (&p)->py = (6);
            } while (0);
        }
    }


    /* Every part of `if` or `else` contains only `1` inner statement
     * (do-while), hence this is valid evaluation */

    /* To make code perfect, use brackets for every if-ifelse-else statements */
    if (a) {                     /* If a is true */
        if (b) {                 /* If b is true */
            SET_POINT(&p, 3, 4); /* Set point to x = 3, y = 4 */
        } else {
            SET_POINT(&p, 5, 6); /* Set point to x = 5, y = 6 */
        }
    }
#endif

/**
 * \brief           Rule 4
 * \note            - Avoid using #ifdef or #ifndef. Use defined() or !defined()
 *                  instead
 *                  - Always document if/elif/else/endif statements
 */
/* OK */
#if defined(XYZ)
/* Do if XYZ defined */
#else  /* defined(XYZ) */
/* Do if XYZ not defined */
#endif /* !defined(XYZ) */

/* Wrong */
#if defined(XYZ)
/* Do if XYZ defined */
#else
/* Do if XYZ not defined */
#endif

/**
 * \brief           Rule 5
 * \note            - Do not indent sub statements inside #if statement
 */
/* OK */
#if defined(XYZ)
#if defined(ABC)
/* do when ABC defined */
#endif /* defined(ABC) */
#else  /* defined(XYZ) */
/* Do when XYZ not defined */
#endif /* !defined(XYZ) */

// clang-format off
/* Wrong */
#if defined(XYZ)
    #if defined(ABC)
    /* do when ABC defined */
    #endif /* defined(ABC) */
#else  /* defined(XYZ) */
    /* Do when XYZ not defined */
#endif /* !defined(XYZ) */
// clang-format on

/* private typedef enum ----------------------------------------------------- */

/* private typedef struct --------------------------------------------------- */

/* private typedef function ------------------------------------------------- */

/* private variables -------------------------------------------------------- */

/* private function prototypes ---------------------------------------------- */

/* public variables --------------------------------------------------------- */

/* public functions --------------------------------------------------------- */

/* private functions -------------------------------------------------------- */

/* ----------------------------- end of file -------------------------------- */
