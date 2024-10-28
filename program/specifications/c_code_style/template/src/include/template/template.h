/**
 * \brief           Rule 1
 * \note            - Leave single empty line at the end of file
 *                  - Every file MUST include doxygen annotation for file and
 *                  brief description followed by empty line (when using
 *                  doxygen)
 */
/**
 * \file            template.h
 * \brief           Template include file
 * \date            2024-10-28
 */
/* Here is empty line */

/**
 * \brief           Rule 2
 * \note            - Every file (header or source) MUST include license
 *                  (opening comment includes single asterisk as this MUST be
 *                  ignored by doxygen)
 *                  - Use the same license as already used by project/library
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
#ifndef __TEMPLATE_H__
#define __TEMPLATE_H__

/* includes ----------------------------------------------------------------- */
#include <stddef.h>
#include <stdint.h>

/**
 * \brief           Rule 3
 * \note            - Header file MUST include guard #ifndef
 *                  - Header file MUST include C++ check
 *                  - Include external header files outside C++ check
 *                  - Include external header files with STL C files first
 *                  followed by application custom files
 *                  - Header file MUST include only every other header file in
 *                  order to compile correctly, but not more (.c should include
 *                  the rest if REQUIRED)
 *                  - Header file MUST only expose module public
 *                  variables/types/functions
 *                  - Use extern for global module variables in header file,
 *                  define them in source file later
 */

/**
 * \brief           Rule 4
 * \note            - Never include .c files in another .c file
 *                  - .c file should first include corresponding .h file, later
 *                  others, unless otherwise explicitly necessary
 *                  - Do not include module private declarations in header file
 */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \defgroup        template manager
 * \brief           template manager
 * \{
 */

/* public config ------------------------------------------------------------ */

/* public define ------------------------------------------------------------ */

/* public typedef enum ------------------------------------------------------ */

/* public typedef struct ---------------------------------------------------- */

/* public typedef function -------------------------------------------------- */

/* public variables extern -------------------------------------------------- */
extern int32_t my_variable; /* This is global variable declaration in header */

/* public functions --------------------------------------------------------- */
/* For low-level code. */

/* For high-level code. */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TEMPLATE_H__ */

/* ----------------------------- end of file -------------------------------- */
