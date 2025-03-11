/* /////////////////////////////////////////////////////////////////////////
 * File:    clasp/main.hpp
 *
 * Purpose: main() entry-point helper functions.
 *
 * Created: 29th December 2010
 * Updated: 12th July 2024
 *
 * Home:    https://github.com/synesissoftware/CLASP/
 *
 * Copyright (c) 2010-2024, Matthew Wilson
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


/** \file clasp/clasp.hpp
 *
 * \brief [C++-only] main() entry-point helper functions.
 */

#ifndef CLASP_INCL_CLASP_HPP_MAIN
#define CLASP_INCL_CLASP_HPP_MAIN


/* /////////////////////////////////////////////////////////////////////////
 * version information
 */

#ifndef CLASP_DOCUMENTATION_SKIP_SECTION
# define CLASP_VER_CLASP_HPP_MAIN_MAJOR     2
# define CLASP_VER_CLASP_HPP_MAIN_MINOR     0
# define CLASP_VER_CLASP_HPP_MAIN_REVISION  2
# define CLASP_VER_CLASP_HPP_MAIN_EDIT      43
#endif /* !CLASP_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef __cplusplus
# error This file is only compatible with C++ compilation
#endif /* !__cplusplus */

/* CLASP header files */
#if 1
# include <clasp/clasp.hpp>
# else
  /* TODO: separate out CLASP C++ */
# include <clasp/clasp.h>
# include <clasp/clasp/exceptions.hpp>
#endif

/* Pantheios header files */
#ifdef PANTHEIOS_INCL_PANTHEIOS_HPP_PANTHEIOS
 /* Pantheios C++ API is used in this compilation unit, so we can further
  * include
  */
# include <pantheios/inserters/args.hpp>
#endif

/* STLSoft header files */
#include <stlsoft/stlsoft.h>
#if STLSOFT_LEAD_VER >= 0x010a0000
# include <platformstl/filesystem/path_functions.h>
#endif
#if defined(STLSOFT_VER) && \
    STLSOFT_VER >= 0x010c0000
# include <stlsoft/diagnostics/error_desc.hpp>
#else /* ? PANTHEIOS_STLSOFT_1_12_OR_LATER */
# include <stlsoft/error/error_desc.hpp>
#endif /* PANTHEIOS_STLSOFT_1_12_OR_LATER */
#include <stlsoft/smartptr/scoped_handle.hpp>

/* Standard C++ header files */
#include <stdexcept>
#include <string>

/* Standard C header files */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

namespace clasp
{
namespace main
{


/* /////////////////////////////////////////////////////////////////////////
 * typedefs
 */

#ifdef CLASP_DOCUMENTATION_SKIP_SECTION

/** \def CLASP_MAIN_DEFAULT_PROGRAM_NAME
 *
 * If defined, specifies, at compile-time, the program name to be assumed if
 * none is specified to clasp::main::invoke(), which is otherwise inferred
 * heuristically.
 *
 * \see clasp::main::invoke()
 */
# define CLASP_MAIN_DEFAULT_PROGRAM_NAME                    "MyExampleProgramName"
#endif /* CLASP_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * typedefs
 */


/* /////////////////////////////////////////////////////////////////////////
 * implementation functions
 */

#ifndef CLASP_DOCUMENTATION_SKIP_SECTION

namespace ximpl
{

inline
int
invoke_(
    int                                 argc
,   clasp_char_t const* const*          argv
,   int (STLSOFT_CDECL*                 pfnMain)(clasp::arguments_t const* args)
,   clasp_char_t const*                 programName
,   clasp::specification_t const        specifications[]
,   unsigned                            flags
,   clasp::diagnostic_context_t const*  ctxt
,   clasp_char_t const*                 usageHelpSuffix
)
{
    /* Using declarations */

#ifdef PANTHEIOS_INCL_PANTHEIOS_H_PANTHEIOS
# ifndef PANTHEIOS_NO_NAMESPACE
    using pantheios::pantheios_logprintf;
# endif /* !PANTHEIOS_NO_NAMESPACE */
#endif /* PANTHEIOS_INCL_PANTHEIOS_H_PANTHEIOS */
#ifdef PANTHEIOS_INCL_PANTHEIOS_HPP_PANTHEIOS
# ifndef PANTHEIOS_NO_NAMESPACE
    using pantheios::log_DEBUG;
    using pantheios::args;
# endif /* !PANTHEIOS_NO_NAMESPACE */
#endif /* Pantheios C++ API */

    /* Preconditions */

    assert(argc > 0);
    assert(NULL != argv);
    assert(NULL != pfnMain);
    assert(NULL != programName);

    clasp::arguments_t const* clargs;

    int r = clasp::parseArguments(flags, argc, argv, specifications, ctxt, &clargs);

    if (r != 0)
    {
        stlsoft::error_desc e(r);

        /* Diagnostic log statement */
#ifdef PANTHEIOS_INCL_PANTHEIOS_H_PANTHEIOS
        pantheios_logprintf(PANTHEIOS_SEV_ALERT, PANTHEIOS_LITERAL_STRING("%s: could not start program: arguments parsing failed: %s"), programName, e.c_str());
#endif /* PANTHEIOS_INCL_PANTHEIOS_H_PANTHEIOS */

        /* Contingent report */
        fprintf(stderr, "%s: could not start program: arguments parsing failed: %.*s\n", programName, int(e.size()), e.c_str());

        return EXIT_FAILURE;
    }
    else
    {
        stlsoft::scoped_handle<clasp::arguments_t const*> scoper(clargs, clasp::releaseArguments);

        try
        {
#ifdef PANTHEIOS_INCL_PANTHEIOS_HPP_PANTHEIOS

            log_DEBUG(PANTHEIOS_LITERAL_STRING("entering main("), args(argc, argv, args::arg0FileOnly), PANTHEIOS_LITERAL_STRING(")"));

#endif /* Pantheios C++ API */

            return pfnMain(clargs);
        }
        catch(clasp::clasp_exception &x)
        {
            /* Diagnostic log statement */
#ifdef PANTHEIOS_INCL_PANTHEIOS_H_PANTHEIOS
# ifdef STLSOFT_CF_RTTI_SUPPORT
            pantheios_logprintf(PANTHEIOS_SEV_DEBUG, PANTHEIOS_LITERAL_STRING("%s: invalid-command-line (%s): %s"), programName, typeid(x).name(), x.what());
# else /* ? STLSOFT_CF_RTTI_SUPPORT */
            pantheios_logprintf(PANTHEIOS_SEV_DEBUG, PANTHEIOS_LITERAL_STRING("%s: invalid-command-line: %s"), programName, x.what());
# endif /* STLSOFT_CF_RTTI_SUPPORT */
#endif /* PANTHEIOS_INCL_PANTHEIOS_H_PANTHEIOS */

            /* Contingent report */
            if (NULL != usageHelpSuffix &&
                '\0' != usageHelpSuffix[0])
            {
                ::fprintf(stderr, "%s: invalid command-line: %s; %s\n", programName, x.what(), usageHelpSuffix);
            }
            else
            {
                ::fprintf(stderr, "%s: invalid command-line: %s\n", programName, x.what());
            }
        }

        return EXIT_FAILURE;
    }
}

} /* namespace ximpl */
#endif /* !CLASP_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * functions
 */

/** Parses the command-line (specified in \c argc and \c argv) and invokes
 * caller-supplied CLASP main function (\c pfnMain) according to the given
 * arguments.
 *
 * \param argc \c argc passed to <code>main()</code>
 * \param argv \c argv passed to <code>main()</code>
 * \param pfnMain Caller-supplied CLASP main function that will be invoked
 * \param programName Specifies the name of the program, which will be
 *   inferred heuristically if NULL or empty
 * \param specifications Pointer to an specifications array that will be passed to
 *   clasp::parseArguments()
 * \param flags Flags that will be passed to clasp::parseArguments()
 * \param usageHelpSuffix Suffix such as "use --help for usage" that will be
 *   semicolon-space appended after the exception information, or NULL for
 *   no suffix
 * \param ctxt
 *
 * \note If use of the Pantheios diagnostic logging API library is detected,
 *   via Pantheios C and/or C++ API main headers - pantheios/pantheios.h and
 *   pantheios/pantheios.hpp, respectively - then diagnostic logging
 *   statements are issued to Pantheios in addition to the contingent
 *   reports issued to the standard error stream in conditions of failure.
 * \note If no program name is specified (\c programName \c NULL or empty)
 *   then one will be assumed according to the following algorithm: 1. If
 *   the preprocessor symbol \c CLASP_MAIN_DEFAULT_PROGRAM_NAME is defined
 *   (and it is not-<code>NULL</code>), then it is user; otherwise, 2. If
 *   Pantheios 1.0.1 beta 214 or later is detected (see other note), then
 *   the diagnostic logging process identity is used (elicited via
 *   <code>pantheios_getProcessIdentity</code>); otherwise 3. The name
 *   "process" is used.
 *
 * \exceptions * All exceptions not derived from clasp::clasp_exception are
 *   passed through to the caller uncaught.
 *
 * \pre argc > 0
 * \pre NULL != argv
 * \pre NULL != pfnMain
 */
inline
int
invoke(
    int                                 argc
,   clasp_char_t const* const*          argv
,   int                 (STLSOFT_CDECL *pfnMain)(clasp::arguments_t const* args)
,   clasp_char_t const*                 programName
,   clasp::specification_t const        specifications[]
,   unsigned                            flags
,   clasp::diagnostic_context_t const*  ctxt            =   NULL
,   clasp_char_t const*                 usageHelpSuffix =   NULL
)
{
    if (NULL != programName &&
        '\0' == programName[0])
    {
        programName = NULL;
    }

#ifdef CLASP_MAIN_DEFAULT_PROGRAM_NAME
    if (NULL == programName)
    {
        programName = CLASP_MAIN_DEFAULT_PROGRAM_NAME;
    }
#endif /* CLASP_MAIN_DEFAULT_PROGRAM_NAME */

#if !defined(PANTHEIOS_USE_WIDE_STRINGS) && \
    defined(PANTHEIOS_INCL_PANTHEIOS_H_PANTHEIOS) && \
    PANTHEIOS_VER >= 0x010001d6
    if (NULL == programName)
    {
# ifndef PANTHEIOS_NO_NAMESPACE
        using pantheios::pantheios_getProcessIdentity;
# endif /* !PANTHEIOS_NO_NAMESPACE */

        programName = pantheios_getProcessIdentity();
    }
#endif

    if (NULL == programName)
    {
#if (STLSOFT_LEAD_VER >= 0x010a0000) && \
    (   !defined(CLASP_USE_WIDE_STRINGS) || \
        STLSOFT_LEAD_VER >= 0x010a0113)
        programName = platformstl_ns_qual(get_executable_name_from_path)(argv[0]).ptr;
# else
        programName = argv[0];
# endif
    }

    if (NULL == programName)
    {
        programName = argv[0];
    }

    return ximpl::invoke_(argc, argv, pfnMain, programName, specifications, flags, ctxt, usageHelpSuffix);
}

inline
int
invoke(
    int                                 argc
,   clasp_char_t const* const*          argv
,   clasp::specification_t const        specifications[]
,   int                 (STLSOFT_CDECL *pfnMain)(clasp::arguments_t const* args)
,   clasp_char_t const*                 programName     =   NULL
,   unsigned                            flags           =   0
,   clasp::diagnostic_context_t const*  ctxt            =   NULL
,   clasp_char_t const*                 usageHelpSuffix =   NULL
)
{
    return invoke(
        argc
    ,   argv
    ,   pfnMain
    ,   programName
    ,   specifications
    ,   flags
    ,   ctxt
    ,   usageHelpSuffix
    );
}

/* /////////////////////////////////////////////////////////////////////////
 * namespace
 */

} /* namespace main */
} /* namespace clasp */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !CLASP_INCL_CLASP_HPP_MAIN */

/* ///////////////////////////// end of file //////////////////////////// */

