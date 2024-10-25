/**
 * \file            generl_rules.c
 * \brief           generl rules
 * \date            2024-10-24
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
#include "template/generl_rules.h"

#include <stdio.h>

/* private config ----------------------------------------------------------- */

/* private define ----------------------------------------------------------- */
#define CONDITION 0

/* private typedef enum ----------------------------------------------------- */

/* private typedef struct --------------------------------------------------- */
typedef struct {
    uint32_t a;
    uint32_t b;
} my_struct_t;

/* private typedef function ------------------------------------------------- */

/* private variables -------------------------------------------------------- */
static int32_t a; /* OK */
// clang-format off
static int32_t b = 4; /* Wrong - this value may not be set at zero
           if linker script&startup files are not properly handled */
// clang-format on

/* private function prototypes ---------------------------------------------- */
static int32_t prv_sum(int32_t a, int32_t b);

/* public variables --------------------------------------------------------- */

/* public functions --------------------------------------------------------- */
/**
 * \brief           Generl Rule 1
 *
 * \note            - clang-format SHOULD be used with formatting file attached
 *                  to this repository (version 15.x is a minimum).
 *                  - Use `C11` standard.
 *                  - Do not use tabs, use spaces instead.
 *                  - Use 4 spaces per indent level.
 *                  - Use 1 spaces between keyword and opening bracket.
 *
 */
void
generl_rule01(void) {
    /* OK */
    if (CONDITION) {
    }

    while (CONDITION) {
    }

    for (int32_t i = 0; i < 10; ++i) {
    }

    do {
    } while (CONDITION);

    // clang-format off
    /* Wrong */
    if(CONDITION){

    }

    while(CONDITION){

    }

    for(int32_t i = 0; i < 10; ++i){

    }

    do {

    } while(CONDITION);
    // clang-format on
}

/**
 * \brief           Generl Rule 2
 *
 * \note            - Do not use space between function name and opening bracket
 *
 */
void
generl_rule02(void) {
    int32_t a;

    a = sum(4, 3); /* OK */

    // clang-format off
    a = sum (4, 3); /* Wrong */
    // clang-format on
}

/**
 * \brief           Generl Rule 3
 *
 * \note            - Never use __ or _ prefix for
 *                  variables/functions/macros/types. This is reserved for C
 *                  language itself
 *                    - Prefer prv_ name prefix for strictly module-private
 *                      (static) functions
 *                    - Prefer libname_int_ or libnamei_ prefix for library
 *                      internal functions, that should not be used by the user
 *                      application while they MUST be used across different
 *                      library internal modules
 *                  - Use only lowercase characters for
 *                  variables/functions/types with optional underscore _ char
 *                  - Opening curly bracket is always at the same line as
 *                  keyword (for, while, do, switch, if, ...)
 */
void
generl_rule03(void) {
    size_t i;

    for (size_t i = 0; i < 5; ++i) { /* OK */
    }

    // clang-format off
    for (i = 0; i < 5; ++i){            /* Wrong */
    }

    for (i = 0; i < 5; ++i)             /* Wrong */
    {
    }
    // clang-format on
}

/**
 * \brief           Generl Rule 4
 *
 * \note            - Use single space before and after comparison and
 *                  assignment operators
 */
void
generl_rule04(void) {
    int32_t a;

    a = 3 + 4;                /* OK */
    for (a = 0; a < 5; ++a) { /* OK */
    }

    // clang-format off
    a=3+4;                  /* Wrong */
    a = 3+4;                /* Wrong */
    for (a=0;a<5;++a) {     /* Wrong */
    }
    // clang-format on
}

/**
 * \brief           Generl Rule 5
 *
 * \note            - Use single space after every comma
 */
void
generl_rule05(void) {
    int32_t a;

    a = prv_sum(5, 4); /* OK */

    // clang-format off
    a = prv_sum(4,3);  /* Wrong */
    // clang-format on
}

/**
 * \brief           Generl Rule 6
 *
 * \note            - Do not initialize global variables to any default value
 *                  (or NULL), implement it in the dedicated init function (if
 *                  REQUIRED).
 *
 *                  In embedded systems, it is very common that RAM memories are
 *                  scattered across different memory locations in the system.
 *                  It quickly becomes tricky to handle all the cases,
 *                  especially when user declares custom RAM sections. Startup
 *                  script is in-charge to set default values (.data and .bss)
 *                  while other custom sections may not be filled with default
 *                  values, which leads to variables with init value won't have
 *                  any effect.
 *
 *                  To be independent of such problem, create init function for
 *                  each module and use it to set default values for all of your
 *                  variables, like so:
 */
void
generl_rule06(void) {}

/**
 * \brief           Generl rule module initialization
 *
 */
void
generl_rule_init(void) {
    a = 0;
    b = 4;
}

/**
 * \brief           Generl Rule 7
 *
 * \note            - Declare all local variables of the same type in the same
 *                  line
 *
 */
void
generl_rule07(void) {
    /* 1 */
    char a; /* OK */

    /* 2 */
    char a, b; /* OK */

    /* 3 */
    char a;
    char b; /* Wrong, variable with char type already exists */
}

/**
 * \brief           Generl Rule 8
 *
 * \note            - Declare local variables in order
 *                      i.Custom structures and enumerations
 *                      ii.Integer types, wider unsigned type first
 *                      iii.Single/Double floating point
 *
 */
void
generl_rule07(void) {
    /* 1 */
    my_struct_t my; /* First custom structures */
    my_struct_t* p; /* Pointers too */

    /* 2 */
    uint32_t a;
    int32_t b;
    uint16_t c;
    int16_t g;
    char h;
    /* ... */

    /* 3 */
    double d;
    float f;
}

/* private functions -------------------------------------------------------- */
/**
 * \brief           Sum `2` numbers
 *
 * \param[in]       a: First value
 * \param[in]       b: Second value
 * \return          Sum of input values
 */
static int32_t
prv_sum(int32_t a, int32_t b) {
    return a + b;
}

/* ----------------------------- end of file -------------------------------- */
