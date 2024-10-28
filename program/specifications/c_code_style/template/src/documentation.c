/**
 * \file            documentation.c
 * \brief           documentation source file
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
#include "./template/documentation.h"

/**
 * \brief           Documented code allows doxygen to parse and generate
 *                  html/pdf/latex output, thus it is very important to do it
 *                  properly at an early stage of the project.
 * \note            - Use doxygen-enabled documentation style for variables,
 *                  functions and structures/enumerations
 *                  - Always use \ for doxygen, do not use @
 *                  - Always use 5x4 spaces (5 tabs) offset from beginning of
 *                  line for text
 */
/* private config ----------------------------------------------------------- */

/* private define ----------------------------------------------------------- */
/**
 * \brief           Rule 6
 * \note            - Documentation for macros MUST include hideinitializer
 *                  doxygen command
 */
/**
 * \brief           Get minimal value between `x` and `y`
 * \param[in]       x: First value
 * \param[in]       y: Second value
 * \return          Minimal value between `x` and `y`
 * \hideinitializer
 */
#define MIN(x, y) ((x) < (y) ? (x) : (y))

/* private typedef enum ----------------------------------------------------- */
/**
 * \brief           Rule 2
 * \note            - Every structure/enumeration member MUST include
 *                  documentation
 *                  - Align start of comments between different structure
 *                  members to the same column
 */

/**
 * \brief           Point color enumeration
 */
typedef enum {
    COLOR_RED,   /*!< Red color */
    COLOR_GREEN, /*!< Green color */
    COLOR_BLUE,  /*!< Blue color */
} point_color_t;

/**
 * \brief           My enumeration
 */
typedef enum {
    MY_ERR, /*!< Error value */
    MY_OK   /*!< OK value */
} my_enum_t;

/* private typedef struct --------------------------------------------------- */
/**
 * \brief           This is point struct
 * \note            This structure is used to calculate all point related stuff
 */
typedef struct {
    int32_t x;    /*!< Point X coordinate */
    int32_t y;    /*!< Point Y coordinate */
    int32_t size; /*!< Point size.
                      Since comment is very big,
                      you may go to next line */
} point_t;

/* private typedef function ------------------------------------------------- */
typedef uint8_t type_t;
/* private variables -------------------------------------------------------- */
/**
 * \brief           Rule 1
 * \note            - Holds pointer to first entry in linked list Beginning of
 *                  this text is 5 tabs (20 spaces) from beginning of line
 */
static type_t* list;

/* private function prototypes ---------------------------------------------- */

/* public variables --------------------------------------------------------- */

/* public functions --------------------------------------------------------- */
/**
 * \brief           Rule 3
 * \note            - Documentation for functions MUST be written in function
 *                  implementation (source file usually)
 *                  - Function MUST include brief and all parameters
 *                  documentation
 *                  - Every parameter MUST be noted if it is in or out for input
 *                  and output respectively
 *                  - Function MUST include return parameter if it returns
 *                  something. This does not apply for void functions
 *                  - Function can include other doxygen keywords, such as note
 *                  or warning
 *                  - Use colon : between parameter name and its description
 */

/**
 * \brief           Sum `2` numbers
 * \param[in]       a: First number
 * \param[in]       b: Second number
 * \return          Sum of input values
 */
int32_t
sum(int32_t a, int32_t b) {
    return a + b;
}

/**
 * \brief           Sum `2` numbers and write it to pointer
 * \note            This function does not return value, it stores it to pointer
 *                  instead
 * \param[in]       a: First number
 * \param[in]       b: Second number
 * \param[out]      result: Output variable used to save result
 */
void
void_sum(int32_t a, int32_t b, int32_t* result) {
    *result = a + b;
}

/**
 * \brief           Rule 4
 * \note            - If function returns member of enumeration, use ref keyword
 *                  to specify which one
 */

/**
 * \brief           Check some value
 * \return          \ref MY_OK on success, member of \ref my_enum_t otherwise
 */
my_enum_t
check_value(void) {
    return MY_OK;
}

/**
 * \brief           Rule 5
 * \note            - Use notation (`NULL` => NULL) for constants or numbers
 */
/**
 * \brief           Get data from input array
 * \param[in]       in: Input data
 * \return          Pointer to output data on success, `NULL` otherwise
 */
const void*
get_data(const void* in) {
    return in;
}

/* private functions -------------------------------------------------------- */

/* ----------------------------- end of file -------------------------------- */
