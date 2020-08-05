/* /////////////////////////////////////////////////////////////////////////
 * File:        src/searchspecs/searchspecs.c
 *
 * Purpose:     The CLASP::Util::SearchSpecs library API.
 *
 * Created:     8th March 2012
 * Updated:     5th August 2020
 *
 * Home:        https://github.com/synesissoftware/CLASP/
 *
 * Copyright (c) 2012-2020, Matthew Wilson
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
 * - Neither the names of Matthew Wilson and Synesis Information Systems nor
 *   the names of any contributors may be used to endorse or promote
 *   products derived from this software without specific prior written
 *   permission.
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


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <clasp/util/searchspecs.h>

#include <assert.h>
#include <errno.h>
#include <stdlib.h>

/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

/* /////////////////////////////////////////////////////////////////////////
 * API
 */

CLASP_CALL(int)
clasp_util_searchSpecs_load(
    int                                 flags
,   size_t                              numValues
,   clasp_argument_t const*             values
,   clasp_char_t const*                 defaultDirectory
,   clasp_char_t const*                 defaultPatterns
,   clasp_util_searchspecs_t const**    searchspecs
)
{
    clasp_util_searchspecs_t* ss;

    assert(NULL != searchspecs);

    ss = (clasp_util_searchspecs_t*)malloc(sizeof(clasp_util_searchspecs_t));

    if (NULL == ss)
    {
        *searchspecs = NULL;

        return ENOMEM;
    }
    else
    {
        ss->flags       =   0;
        ss->numSpecs    =   0;
        ss->specs       =   NULL;

        *searchspecs    =   ss;

        return 0;
    }
}

/* ///////////////////////////// end of file //////////////////////////// */

