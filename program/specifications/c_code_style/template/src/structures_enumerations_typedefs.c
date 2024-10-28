/**
 * \file            structures_enumerations_typedefs.c
 * \brief           structures enumerations typedefs source file
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
#include "./template/structures_enumerations_typedefs.h"

/* private config ----------------------------------------------------------- */

/* private define ----------------------------------------------------------- */

/**
 * \brief           Rule 1
 * \note            - Structure or enumeration name MUST be lowercase with
 *                  optional underscore _ character between words
 *                  - Structure or enumeration may contain typedef keyword
 *                  - All structure members MUST be lowercase
 *                  - All enumeration members SHOULD be uppercase
 *                  - Structure/enumeration MUST follow doxygen documentation
 *                  syntax
 *
 */
/* private typedef enum ----------------------------------------------------- */

/* private typedef struct --------------------------------------------------- */
/* When structure is declared, it may use one of 3 different options: */
/**
 * \brief           1. When structure is declared with name only, it MUST not
 *                  contain _t suffix after its name.
 */
struct struct_name {
    char* a;
    char  b;
};

/**
 * \brief           2. When structure is declared with typedef only, it has to
 *                  contain _t suffix after its name.
 */
typedef struct {
    char* a;
    char  b;
} struct_name_t;

/**
 * \brief           3. When structure is declared with name and typedef, it MUST
 *                  NOT contain _t for basic name and it MUST contain _t suffix
 *                  after its name for typedef part.
 */
typedef struct my_struct_name { /* No _t */
    char* a;
    char  b;
    char  c;
} my_struct_name_t; /* _t */

/**
 * \brief           Rule 3
 * \note            - When new typedef is introduced for function handles,
 *                  use _fn suffix
 */
/* Function accepts 2 parameters and returns uint8_t */
/* Name of typedef has `_fn` suffix */
typedef uint8_t (*my_func_typedef_fn)(uint8_t p1, const char* p2);

/* private typedef function ------------------------------------------------- */

/* private variables -------------------------------------------------------- */
/**
 * \brief           Rule 2
 * \note            - When initializing structure on declaration, use C99
 *                  initialization style
 */
my_struct_name_t name = {
    .a = "name",
    .b = 1,
    .c = 2,
};

/* Wrong */
my_struct_name_t wrong_name = {"wrong", 1, 2};

/* private function prototypes ---------------------------------------------- */

/* public variables --------------------------------------------------------- */

/* public functions --------------------------------------------------------- */

/* private functions -------------------------------------------------------- */

/* ----------------------------- end of file -------------------------------- */
