/* /////////////////////////////////////////////////////////////////////////
 * File:        systemtools/clasp/main.h
 *
 * Purpose:     main() entry-point helper functions.
 *
 * Created:     29th December 2010
 * Updated:     13th October 2015
 *
 * Home:        http://stlsoft.org/
 *
 * Copyright (c) 2010-2015, Matthew Wilson
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name(s) of Matthew Wilson and Synesis Software nor the names of
 *   any contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/** \file systemtools/clasp/main.h
 *
 * \brief [C-only] main() entry-point helper functions.
 */

#ifndef SYSTEMTOOLS_INCL_SYSTEMTOOLS_CLASP_H_MAIN
#define SYSTEMTOOLS_INCL_SYSTEMTOOLS_CLASP_H_MAIN

/* /////////////////////////////////////////////////////////////////////////
 * Version information
 */

#ifndef SYSTEMTOOLS_DOCUMENTATION_SKIP_SECTION
# define SYSTEMTOOLS_VER_SYSTEMTOOLS_CLASP_H_MAIN_MAJOR     1
# define SYSTEMTOOLS_VER_SYSTEMTOOLS_CLASP_H_MAIN_MINOR     1
# define SYSTEMTOOLS_VER_SYSTEMTOOLS_CLASP_H_MAIN_REVISION  1
# define SYSTEMTOOLS_VER_SYSTEMTOOLS_CLASP_H_MAIN_EDIT      11
#endif /* !SYSTEMTOOLS_DOCUMENTATION_SKIP_SECTION */

/* /////////////////////////////////////////////////////////////////////////
 * Includes
 */

#ifdef __cplusplus
# error This file is not compatible with C++ compilation
#endif /* __cplusplus */

/* CLASP header files */
#include <systemtools/clasp/clasp.h>

/* Standard C header files */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef CLASP_USE_WIDE_STRINGS
# include <wchar.h>
#endif /* CLASP_USE_WIDE_STRINGS */

/* /////////////////////////////////////////////////////////////////////////
 * Functions
 */

static
int
clasp_main_invoke(
    int                                 argc
,   clasp_char_t**                      argv
,   int (*                              pfnMain)(clasp_arguments_t const* args)
,   clasp_char_t const*                 programName
,   clasp_alias_t const*                aliases
,   unsigned                            flags
,   clasp_diagnostic_context_t const*   ctxt
)
{
    clasp_arguments_t const* args;

    int r = clasp_parseArguments(flags, argc, (clasp_char_t const* const*)argv, aliases, ctxt, &args);

    if(r != 0)
    {
#if defined(_MSC_VER)
# if _MSC_VER >= 1400
#  pragma warning(push)
#  pragma warning(disable : 4996)
# endif
#endif

#ifdef CLASP_USE_WIDE_STRINGS
        wchar_t const* const e = _wcserror(r);
#else /* ? CLASP_USE_WIDE_STRINGS */
        char const* const e = strerror(r);
#endif /* CLASP_USE_WIDE_STRINGS */

#if defined(_MSC_VER)
# if _MSC_VER >= 1400
#  pragma warning(pop)
# endif
#endif

        if(NULL == programName)
        {
            programName = CLASP_LITERAL_STRING("process");
        }

        /* Diagnostic logging */
#if defined(PANTHEIOS_INCL_PANTHEIOS_H_PANTHEIOS)
        pantheios_logprintf(PANTHEIOS_SEV_ALERT, PANTHEIOS_LITERAL_STRING("%s: could not start program: arguments parsing failed: "), programName, e);
#endif /* PANTHEIOS_INCL_PANTHEIOS_H_PANTHEIOS */

        /* Contingent report */
        fprintf(stderr, "%s: could not start program: arguments parsing failed: %s\n", programName, e);

        return EXIT_FAILURE;
    }
    else
    {
        int const mr = (*pfnMain)(args);

        clasp_releaseArguments(args);

        return mr;
    }
}

/* ////////////////////////////////////////////////////////////////////// */

#endif /* !SYSTEMTOOLS_INCL_SYSTEMTOOLS_CLASP_H_MAIN */

/* ///////////////////////////// end of file //////////////////////////// */
