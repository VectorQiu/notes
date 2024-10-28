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
#include <stdlib.h>

/* private config ----------------------------------------------------------- */

/* private define ----------------------------------------------------------- */
#define CONDITION 0

/* private typedef enum ----------------------------------------------------- */

/* private typedef struct --------------------------------------------------- */
typedef enum {
    TYPE1 = 1,
    TYEP2 = 2,
    TYEP3 = 2,
} type_e;

typedef struct {
    uint32_t par1;
    uint32_t par2;
} data_t;

typedef struct {
    data_t type1;
    data_t type2;
} type_data_t;

typedef struct {
    type_e      type;
    type_data_t type_data;
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
 */
void
generl_rule07(void) {
    /* 1 */
    my_struct_t  my; /* First custom structures */
    my_struct_t* p;  /* Pointers too */

    /* 2 */
    uint32_t a;
    int32_t  b;
    uint16_t c;
    int16_t  g;
    char     h;
    /* ... */

    /* 3 */
    double d;
    float  f;
}

/**
 * \brief           Generl Rule 8
 *
 * \note            - Always declare local variables at the beginning of the
 *                  block, before first executable statement.
 *                  - Always add trailing comma in the last element of structure
 *                  (or its children) initialization (this helps clang-format to
 *                  properly format structures). Unless structure is very simple
 *                  and short
 */
void
generl_rule08(void) {
    my_struct_t my_var_1 = {
        .type = TYPE1,
        .type_data =
            {
                .type1 =
                    {
                        .par1 = 0, .par2 = 1, /* Trailing comma here */
                    },                        /* Trailing comma here */
            },                                /* Trailing comma here */
    };
}

/**
 * \brief           Generl Rule 9
 *
 * \note            - Declare counter variables in for loop
 */
void
generl_rule09(void) {
    /* OK */
    for (size_t i = 0; i < 10; ++i) {
    }

    /* OK, if you need counter variable later */
    size_t i;
    for (i = 0; i < 10; ++i) {
        if (i == 5) {
            break;
        }
    }

    if (i == 10) {
    }

    /* Wrong */
    size_t j;
    for (j = 0; i < 10; ++j) {
    }
}

/**
 * \brief           Generl Rule 10
 *
 * \note            - Avoid variable assignment with function call in
 *                  declaration, except for single variables
 */
void
generl_rule10(void) {
    /* Avoid function calls when declaring variable */
    int32_t a, b = sum(1, 2);

    /* Use this */
    int32_t c, d;
    d = sum(1, 2);

    /* This is ok */
    uint8_t i = 3, j = 4;
}

/**
 * \brief           Generl Rule 11
 *
 * \note            - Except char, float or double, always use types declared in
 *                  stdint.h library, eg. uint8_t for unsigned 8-bit, etc.
 *                  - Do not use stdbool.h library. Use 1 or 0 for true or false
 *                  respectively
 */
void
generl_rule11(void) {
    /* OK */
    uint8_t status;
    status = 0;
#if 0
/* Wrong */
#include <stdbool.h>
    bool status = true;
#endif
}

/**
 * \brief           Generl Rule 12
 *
 * \note            - Never compare against true, eg. if (check_func() == 1),
 *                  use if (check_func()) { ... }
 *                  - Always compare pointers against NULL value
 */
void
generl_rule12(void) {
    void* ptr;

    /* ... */

    /* OK, compare against NULL */
    if (ptr == NULL || ptr != NULL) {
    }

    /* Wrong */
    if (ptr || !ptr) {
    }
}

/**
 * \brief           Generl Rule 13
 *
 * \note            - Always use pre-increment (and decrement respectively)
 *                  instead of post-increment (and decrement respectively)
 */
void
generl_rule13(void) {
    int32_t a = 0;
    /* ... */

    a++; /* Wrong */
    ++a; /* OK */

    for (size_t j = 0; j < 10; ++j) { /* OK */
    }
}

/**
 * \brief           Generl Rule 14
 *
 * \note            - Always use size_t for length or size variables
 *                  - Always use const for pointer if function should not modify
 *                  memory pointed to by pointer
 *                  - Always use const for function parameter or variable, if it
 *                  should not be modified
 *
 *                  When d could be modified, data pointed to by d could not be
 *                  modified
 *                  ``` c
 *                  void my_func(const void* d) {
 *
 *                  }
 *                  ```
 *
 *                  When d and data pointed to by d both could not be modified
 *                  ``` c
 *                  void
 *                  my_func(const void* const d) {
 *
 *                  }
 *                  ```
 *
 *                  Not REQUIRED, it is advised
 *                  ``` c
 *                  void
 *                  my_func(const size_t len) {
 *
 *                  }
 *                  ```
 *
 *                  When d should not be modified inside function, only data
 *                  pointed to by d could be modified
 *                  ``` c
 *                  void my_func(void* const d) {
 *
 *                  }
 *                  ```
 */
void
generl_rule14(void) {}

/**
 * \brief           To send data, function should not modify memory pointed to
 *                  by `data` variable thus `const` keyword is important
 *
 * \param[in]       data: data to be sent
 * \param[in]       len: Length of data to be sent
 */
void
send_data(const void* data, size_t len) { /* OK */
    /* Do not cast `void *` or `const void *` */

    /* Function handles proper type for internal usage */
    const uint8_t* d = data;
}

/**
 * \brief           Generl rule 16
 *
 *  \note           - When function may accept pointer of any type, always use
 *                  void *, do not use uint8_t *
 *                    - Function MUST take care of proper casting in
 *                      implementation
 */
void
generl_rule16(void) {
    uint8_t data;

    data = 10;
    send_data(&data, siezof(data));
}

/**
 * \brief           Generl rule 17
 *
 * \note            - Always use brackets with sizeof operator
 *                  - Never use Variable Length Array (VLA). Use dynamic memory
 *                  allocation instead with standard C malloc and free functions
 *                  or if library/project provides custom memory allocation, use
 *                  its implementation
 *
 *                  Wrong, do not use VLA
 *                  ``` c
 *                  void
 *                  my_func(size_t size) {
 *                      int32_t arr[size];
 *                  }
 *                  ```
 */
void
generl_rule17(void) {
    int32_t* arr;

    arr = malloc(sizeof(*arr) * 10); /* OK, Allocate memory */
#if 0
    /* Wrong, brackets for sizeof operator are missing */
    arr = malloc(sizeof *arr * 10);
#endif
    if (arr == NULL) {
        /* FAIL, no memory */
    }

    free(arr); /* Free memory after usage */
}

/**
 * \brief           Generl Rule 18
 *
 * \note            - Always compare variable against zero, except if it is
 *                  treated as boolean type
 *                  - Never compare boolean-treated variables against zero or
 *                  one. Use NOT (!) instead
 */
void
generl_rule18(void) {
    size_t  length = 5; /* Counter variable */
    uint8_t is_ok = 0;  /* Boolean-treated variable */

    if (length) { /* Wrong, length is not treated as boolean */
    }

    if (length > 0) { /* OK, length is treated as counter variable containing
                         multi values, not only 0 or 1 */
    }

    if (length == 0) { /* OK, length is treated as counter variable containing
                          multi values, not only 0 or 1 */
    }

    if (is_ok) { /* OK, variable is treated as boolean */
    }

    if (!is_ok) { /* OK, -||- */
    }

    if (is_ok == 1) { /* Wrong, never compare boolean variable against 1! */
    }

    if (is_ok == 0) { /* Wrong, use ! for negative check */
    }
}

/**
 * \brief           Generl Rule 19
 *
 * \note            - Always use () for comments, even for single-line comment
 *                  - Always include check for C++ with extern keyword in header
 *                  file
 *                  - Every function MUST include doxygen-enabled comment, even
 *                  if function is static
 *                  - Use English names/text for functions, variables, comments
 *                  - Use lowercase characters for variables
 *                  - Use underscore if variable contains multiple names,
 *                  eg. force_redraw. Do not use forceRedraw
 *                  - Never cast function returning void *, eg. uint8_t* ptr =
 *                  (uint8_t *)func_returning_void_ptr(); as void * is safely
 *                  promoted to any other pointer type
 *                    - Use uint8_t* ptr = func_returning_void_ptr(); instead
 *                  - Always use < and > for C Standard Library include files,
 *                  eg. #include <stdlib.h>
 *                  - Always use "" for custom libraries,
 *                  eg. #include "my_library.h"
 *                  - When casting to pointer type, always align asterisk to
 *                  type, eg. uint8_t* t = (uint8_t*)var_width_diff_type
 *                  - Always respect code style already used in project or
 *                  library
 */
void
generl_rule19(void) {
    /* single-line comment */
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
