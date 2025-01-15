/* /////////////////////////////////////////////////////////////////////////
 * File:    clasp/main.h
 *
 * Purpose: main() entry-point helper functions.
 *
 * Created: 29th December 2010
 * Updated: 15th January 2025
 *
 * Home:    https://github.com/synesissoftware/CLASP/
 *
 * Copyright (c) 2010-2025, Matthew Wilson
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer;
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution;
 * - Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/** \file clasp/main.h
 *
 * \brief [C-only] main() entry-point helper functions.
 */

#ifndef CLASP_INCL_CLASP_H_MAIN
#define CLASP_INCL_CLASP_H_MAIN


/* /////////////////////////////////////////////////////////////////////////
 * version information
 */

#ifndef CLASP_DOCUMENTATION_SKIP_SECTION
# define CLASP_VER_CLASP_H_MAIN_MAJOR       2
# define CLASP_VER_CLASP_H_MAIN_MINOR       0
# define CLASP_VER_CLASP_H_MAIN_REVISION    3
# define CLASP_VER_CLASP_H_MAIN_EDIT        21
#endif /* !CLASP_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifdef __cplusplus
# error This file is not compatible with C++ compilation
#endif /* __cplusplus */

/* CLASP header files */
#include <clasp/clasp.h>

/* Standard C header files */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef CLASP_USE_WIDE_STRINGS
# include <wchar.h>
#endif /* CLASP_USE_WIDE_STRINGS */


/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 */

#ifndef CLASP_MAIN_USE_WINSTL_ERROR_FUNCTIONS

# ifdef CLASP_USE_WIDE_STRINGS

#  if 0
#  elif defined(_MSC_VER) && \
        _MSC_VER < 1600

#   define CLASP_MAIN_USE_WINSTL_ERROR_FUNCTIONS
#  else

#   define CLASP_MAIN_USE_WINSTL_ERROR_FUNCTIONS
#  endif
# endif
#endif

#ifdef CLASP_MAIN_USE_WINSTL_ERROR_FUNCTIONS
# ifndef _WIN32
#  undef CLASP_MAIN_USE_WINSTL_ERROR_FUNCTIONS
# endif
#endif


/* /////////////////////////////////////////////////////////////////////////
 * includes - 2
 */

/* STLSoft header files */

#ifdef CLASP_MAIN_USE_WINSTL_ERROR_FUNCTIONS

# include <winstl/error/error_functions.h>
#endif


/* /////////////////////////////////////////////////////////////////////////
 * implementation
 */

#ifndef CLASP_DOCUMENTATION_SKIP_SECTION

# ifdef CLASP_MAIN_USE_WINSTL_ERROR_FUNCTIONS

#  ifdef CLASP_USE_WIDE_STRINGS

#   define clasp_main_internal_strerror_(en)                winstl_C_format_message_strerror_w((en))
static
void
clasp_main_internal_freeerror_(wchar_t const* es)
{
    winstl_C_format_message_free_buff_w((wchar_t*)es);
}
#  else /* ? CLASP_USE_WIDE_STRINGS */

#   define clasp_main_internal_strerror_(en)                winstl_C_format_message_strerror_a((en))
#   define clasp_main_internal_freeerror_(es)               winstl_C_format_message_free_buff_a((es))
#  endif /* CLASP_USE_WIDE_STRINGS */
# else /* ? CLASP_MAIN_USE_WINSTL_ERROR_FUNCTIONS */

#  if defined(_MSC_VER) && \
      _MSC_VER >= 1400

static
#   ifdef CLASP_USE_WIDE_STRINGS

wchar_t*
#   else /* ? CLASP_USE_WIDE_STRINGS */

char*
#   endif /* CLASP_USE_WIDE_STRINGS */
clasp_main_internal_strerror_(int en)
{
#   pragma warning(push)
#   pragma warning(disable : 4996)

#   ifdef CLASP_USE_WIDE_STRINGS

    return _wcserror(en);
#   else /* ? CLASP_USE_WIDE_STRINGS */

    return strerror(en);
#   endif /* CLASP_USE_WIDE_STRINGS */
#   pragma warning(pop)
}
#   define clasp_main_internal_freeerror_(es)               ((void)0)
#  else

#   ifdef CLASP_USE_WIDE_STRINGS

#    define clasp_main_internal_strerror_(en)               wcserror((en))
#   else /* ? CLASP_USE_WIDE_STRINGS */

#    define clasp_main_internal_strerror_(en)               strerror((en))
#   endif /* CLASP_USE_WIDE_STRINGS */
#   define clasp_main_internal_freeerror_(es)               ((void)0)
#  endif
# endif /* CLASP_MAIN_USE_WINSTL_ERROR_FUNCTIONS */
#endif /* !CLASP_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * functions
 */

static
int
clasp_main_invoke(
    int                                 argc
,   clasp_char_t*                       argv[]
,   int (*                              pfnMain)(clasp_arguments_t const* args)
,   clasp_char_t const*                 programName
,   clasp_specification_t const         specifications[]
,   unsigned                            flags
,   clasp_diagnostic_context_t const*   ctxt
)
{
    clasp_arguments_t const* args;

    int r = clasp_parseArguments(flags, argc, argv, specifications, ctxt, &args);

    if (r != 0)
    {
        clasp_char_t const* const e = clasp_main_internal_strerror_(r);

        if (NULL == programName)
        {
            programName = CLASP_LITERAL_STRING("process");
        }

        /* Diagnostic logging */
#if defined(PANTHEIOS_INCL_PANTHEIOS_H_PANTHEIOS)
        pantheios_logprintf(PANTHEIOS_SEV_ALERT, PANTHEIOS_LITERAL_STRING("%s: could not start program: arguments parsing failed: "), programName, e);
#endif /* PANTHEIOS_INCL_PANTHEIOS_H_PANTHEIOS */

        /* Contingent report */
        fprintf(stderr, "%s: could not start program: arguments parsing failed: %s\n", programName, e);

        clasp_main_internal_freeerror_(e);

        return EXIT_FAILURE;
    }
    else
    {
        int const mr = (*pfnMain)(args);

        clasp_releaseArguments(args);

        return mr;
    }
}


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !CLASP_INCL_CLASP_H_MAIN */


/* ///////////////////////////// end of file //////////////////////////// */

