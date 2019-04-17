/* /////////////////////////////////////////////////////////////////////////
 * File:        systemtools/clasp/util/searchspecs.h
 *
 * Purpose:     The CLASP::Util::SearchSpecs library API.
 *
 * Created:     7th March 2012
 * Updated:     18th April 2019
 *
 * Home:        https://github.com/synesissoftware/CLASP/
 *
 * Copyright (c) 2012-2019, Matthew Wilson
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - Neither the names of Matthew Wilson and Synesis Software nor the names
 *   of any contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/** \file systemtools/clasp/util/searchspecs.h
 *
 * \brief [C, C++] The CLASP::Util::SearchSpecs library API.
 */

#ifndef SYSTEMTOOLS_INCL_SYSTEMTOOLS_CLASP_UTIL_H_SEARCHSPECS
#define SYSTEMTOOLS_INCL_SYSTEMTOOLS_CLASP_UTIL_H_SEARCHSPECS

/* /////////////////////////////////////////////////////////////////////////
 * version information
 */

#ifndef SYSTEMTOOLS_DOCUMENTATION_SKIP_SECTION
# define SYSTEMTOOLS_VER_SYSTEMTOOLS_CLASP_UTIL_H_SEARCHSPECS_MAJOR     1
# define SYSTEMTOOLS_VER_SYSTEMTOOLS_CLASP_UTIL_H_SEARCHSPECS_MINOR     0
# define SYSTEMTOOLS_VER_SYSTEMTOOLS_CLASP_UTIL_H_SEARCHSPECS_REVISION  1
# define SYSTEMTOOLS_VER_SYSTEMTOOLS_CLASP_UTIL_H_SEARCHSPECS_EDIT      3
#endif /* !SYSTEMTOOLS_DOCUMENTATION_SKIP_SECTION */

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <systemtools/clasp/clasp.h>


struct clasp_util_searchspec_t
{
    clasp_slice_t           directory;
    clasp_slice_t           patterns;
};
#ifndef __cplusplus
typedef struct clasp_util_searchspec_t  clasp_util_searchspec_t;
#endif /* !__cplusplus */


struct clasp_util_searchspecs_t
{
    int                             flags;
    size_t                          numSpecs;
    clasp_util_searchspec_t const*  specs;

#ifndef SYSTEMTOOLS_DOCUMENTATION_SKIP_SECTION
    size_t                  reserved0;
    void*                   reserved1;
#endif /* !SYSTEMTOOLS_DOCUMENTATION_SKIP_SECTION */
};
#ifndef __cplusplus
typedef struct clasp_util_searchspecs_t clasp_util_searchspecs_t;
#endif /* !__cplusplus */


/**
 *
 * \retval 0 The operation succeeded
 * \retval !0 The operation succeeded. The value is an errno value indicating
 *   the cause for failure.
 *
 * \pre (NULL != searchspecs)
 * \pre (0 == numValues || NULL != values)
 */
CLASP_CALL(int)
clasp_util_searchSpecs_load(
    int                                 flags
,   size_t                              numValues
,   clasp_argument_t const*             values
,   clasp_char_t const*                 defaultDirectory
,   clasp_char_t const*                 defaultPatterns
,   clasp_util_searchspecs_t const**    searchspecs
);

CLASP_CALL(void)
clasp_util_searchSpecs_release(
    clasp_util_searchspecs_t const*     searchspecs
);

/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !SYSTEMTOOLS_INCL_SYSTEMTOOLS_CLASP_UTIL_H_SEARCHSPECS */

/* ///////////////////////////// end of file //////////////////////////// */

