/* /////////////////////////////////////////////////////////////////////////
 * File:        src/clasp.string.c
 *
 * Purpose:     CLASP string facilities.
 *
 * Created:     4th June 2008
 * Updated:     21st August 2015
 *
 * Home:        http://stlsoft.org/
 *
 * Copyright (c) 2008-2015, Matthew Wilson
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


/* /////////////////////////////////////////////////////////////////////////
 * compatibility control
 */

#define _CRT_NON_CONFORMING_WCSTOK

/* /////////////////////////////////////////////////////////////////////////
 * Includes
 */

#include "clasp.internal.h"

#include <stdlib.h>
#include <string.h>

/* /////////////////////////////////////////////////////////////////////////
 * Compatibility
 */

#ifdef CLASP_USE_WIDE_STRINGS
# define clasp_strtok_      wcstok
#else
# define clasp_strtok_      strtok
#endif

/* /////////////////////////////////////////////////////////////////////////
 * Helper functions
 */

clasp_char_t*
clasp_strdup_(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_char_t const*                 s
)
{
    size_t          len     =   clasp_strlen_(s);
    clasp_char_t*   newS    =   (clasp_char_t*)clasp_malloc_(ctxt, (1 + len) * sizeof(clasp_char_t));

    if(NULL != newS)
    {
        memcpy(newS, s, (1 + len) * sizeof(clasp_char_t));
    }

    return newS;
}

clasp_char_t*
clasp_strdup_raw_(
    clasp_char_t const* s
)
{
    size_t          len     =   clasp_strlen_(s);
    clasp_char_t*   newS    =   (clasp_char_t*)malloc((1 + len) * sizeof(clasp_char_t));

    if(NULL != newS)
    {
        memcpy(newS, s, (1 + len) * sizeof(clasp_char_t));
    }

    return newS;
}

/* This function controls whether the library recognises just an equals
 * sign ('='), or both an equals sign '=' and a colon (':') as separating
 * an option name and value.
 */
clasp_char_t* clasp_strchreq_(clasp_char_t const* s, unsigned flags)
{
    ((void)flags);

#if 0
    return clasp_strchr_(s, '=');
#else /* ? 0 */
    return clasp_strpbrk_(s, CLASP_LITERAL_STRING("=:"));
#endif /* 0 */
}

/* Counts the number of instances of c in s
 *
 * \param s String to search
 * \param c Character for which to search
 *
 * \pre (NULL != s)
 * \pre ('\0' != c)
 */
size_t
clasp_strcount_(
    clasp_char_t const* s
,   clasp_char_t        c
)
{
    size_t count = 0;

    CLASP_ASSERT(NULL != s);

    for(; '\0' != *s; ++s)
    {
        if(c == *s)
        {
            ++count;
        }
    }

    return count;
}

/* Counts the number of instances of c in s to length n
 *
 * \param s String to search
 * \param n Maximum number of characters to search
 * \param c Character for which to search
 *
 * \pre (NULL != s)
 * \pre ('\0' != c)
 */
size_t
clasp_strncount_(
    clasp_char_t const* s
,   size_t              n
,   clasp_char_t        c
)
{
    size_t count = 0;

    CLASP_ASSERT(NULL != s);

    for(; 0 != n && '\0' != *s; --n, ++s)
    {
        if(c == *s)
        {
            ++count;
        }
    }

    return count;
}

/* Searches for the last occurence of n in a section of a
 * string - s[0, n) - and returns a pointer to it, or NULL if it could not
 * be found
 *
 * \pre (NULL != s || 0 == n)
 * \pre ('\0' != c)
 */
clasp_char_t*
clasp_strnrchr_(
    clasp_char_t const* s
,   size_t              n
,   clasp_char_t        c
)
{
    CLASP_ASSERT(NULL != s || 0 == n);

    if(0 != n)
    {
        clasp_char_t const* p = &s[n - 1];

        for(;; --p)
        {
            if(c == *p)
            {
                return (clasp_char_t*)p;
            }
        }
    }

    return NULL;
}

/* Searches for the last occurence of a character that is not c in a section
 * of a string - s[0, n) - and returns a pointer to it, or NULL if it could
 * not be found
 *
 * \pre (NULL != s || 0 == n)
 * \pre ('\0' != c)
 */
clasp_char_t*
clasp_strnexrchr_(
    clasp_char_t const* s
,   size_t              n
,   clasp_char_t        c
)
{
    CLASP_ASSERT(NULL != s || 0 == n);

    if(0 != n)
    {
        clasp_char_t const* p = &s[n - 1];

        for(;; --p)
        {
            if(c != *p)
            {
                return (clasp_char_t*)p;
            }
        }
    }

    return NULL;
}

/* string tokenisation a la strtok_r
 */
clasp_char_t*
clasp_strtok_r_(
    clasp_char_t*               s
,   clasp_char_t const*         delim
,   struct strtok_savectxt_t*   savectxt
)
{
    clasp_char_t* tok;

    CLASP_ASSERT(NULL != delim);
    CLASP_ASSERT(NULL != savectxt);

#if defined(_MSC_VER) && \
    _MSC_VER >= 1400

    do
    {
        tok = clasp_strtok_wblank_r_(s, delim, savectxt);
    }
    while(NULL != tok && '\0' == *tok);

#else
    tok = clasp_strtok_(s, delim);
#endif

    return tok;
}

/* string tokenisation a la strtok_r, except that the blanks are
 * preserved (and returned as empty, not null, strings)
 *
 * \pre (NULL != s)
 * \pre (NULL != delim)
 * \pre (NULL != saveptr)
 */
clasp_char_t*
clasp_strtok_wblank_r_(
    clasp_char_t*               s
,   clasp_char_t const*         delim
,   struct strtok_savectxt_t*   savectxt
)
{
    clasp_char_t*   tok;
    clasp_char_t*   p;

    CLASP_ASSERT(NULL != delim);
    CLASP_ASSERT(NULL != savectxt);

    if(NULL != s)
    {
        size_t const    len =   clasp_strlen_(s);
        clasp_char_t*   end =   s + len + 1;

        savectxt->p0 = s;
        savectxt->p1 = end;

        tok = s;
    }
    else
    {
        CLASP_ASSERT(savectxt->p0 <= savectxt->p1);

        tok = (clasp_char_t*)savectxt->p0;
    }

    for(p = tok; savectxt->p1 != p; ++p)
    {
        if(NULL != clasp_strchr_(delim, *p))
        {
            savectxt->p0 = p + 1;
            *p = '\0';
            return tok;
        }
    }

    return NULL;
}

/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

/* ///////////////////////////// end of file //////////////////////////// */
