/* /////////////////////////////////////////////////////////////////////////
 * File:    src/clasp.internal.h
 *
 * Purpose: CLASP internal common header.
 *
 * Created: 4th June 2008
 * Updated: 11th March 2025
 *
 * Home:    https://github.com/synesissoftware/CLASP/
 *
 * Copyright (c) 2008-2025, Matthew Wilson
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



/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <clasp/clasp.h>

#ifdef _MSC_VER
# include <crtdbg.h>
#else /* ? compiler */
# include <assert.h>
#endif /* compiler */
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * language agnosticism
 */

#ifndef stlsoft_static_cast
# ifdef __cplusplus
#  define stlsoft_static_cast(t, v)                         static_cast<t>((v))
# else /* ? __cplusplus */
#  define stlsoft_static_cast(t, v)                         ((t)(v))
# endif /* __cplusplus */
#endif /* !stlsoft_static_cast */

#ifndef stlsoft_const_cast
# ifdef __cplusplus
#  define stlsoft_const_cast(t, v)                          const_cast<t>((v))
# else /* ? __cplusplus */
#  define stlsoft_const_cast(t, v)                          ((t)(v))
# endif /* __cplusplus */
#endif /* !stlsoft_const_cast */

#ifdef __cplusplus

# define clasp_bool_t                                       bool
# define clasp_true_v                                       true
# define clasp_false_v                                      false
#else /* ? __cplusplus */

# define clasp_bool_t                                       int
# define clasp_true_v                                       (1)
# define clasp_false_v                                      (0)
#endif /* __cplusplus */


/* /////////////////////////////////////////////////////////////////////////
 * macros
 */

#define CLASP_NUM_ELEMENTS_(ar)                             (sizeof((ar)) / sizeof((ar)[0]))


/* /////////////////////////////////////////////////////////////////////////
 * diagnostics and contract enforcement
 */

#ifndef CLASP_ASSERT
# ifdef _MSC_VER
#  define CLASP_ASSERT(x)                                   _ASSERTE(x)
# else /* ? compiler */
#  define CLASP_ASSERT(x)                                   assert(x)
# endif /* compiler */
#endif /* !CLASP_ASSERT */

enum clasp_severity_index_t
{
        CLASP_SEVIX_DEBUG =   0
    ,   CLASP_SEVIX_WARN  =   1
    ,   CLASP_SEVIX_ERROR =   2
    ,   CLASP_SEVIX_FATAL =   3
    ,   CLASP_SEVIX_EMERG =   4
};

void
CLASP_LOG_PRINTF(
    clasp_diagnostic_context_t const*   ctxt
,   int                                 severityIndex
,   clasp_char_t const*                 fmt
,   ...
);

clasp_diagnostic_context_t const*
clasp_verify_context_(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_diagnostic_context_t*         local
,   int*                                r
);

clasp_diagnostic_context_t const*
clasp_diagnostic_context_from_args_(
    clasp_arguments_t const* args
);


/* /////////////////////////////////////////////////////////////////////////
 * memory
 */

void* clasp_malloc_(clasp_diagnostic_context_t const* ctxt, size_t cb);
void* clasp_realloc_(clasp_diagnostic_context_t const* ctxt, void* pv, size_t cb);
void clasp_free_(clasp_diagnostic_context_t const* ctxt, void* pv);

void* CLASP_CALLCONV clasp_stock_malloc_(void* context, size_t cb);
void* CLASP_CALLCONV clasp_stock_realloc_(void* context, void* pv, size_t cb);
void CLASP_CALLCONV clasp_stock_free_(void* context, void* pv);


/* /////////////////////////////////////////////////////////////////////////
 * argument-control
 */

/** Indicates whether the given argument is marked as used.
 *
 * \retval 0 The argument is not used
 * \retval !0 The argument is used
 *
 * \pre NULL != args
 * \pre NULL != arg
 */
int
clasp_argumentIsUsed_(
    clasp_arguments_t const*    args
,   clasp_argument_t const*     arg
);

/* Causes the given argument to be marked as used.
 *
 * \retval 0 The argument was previously unused
 * \retval !0 The argument was previously used
 *
 * \pre NULL != args
 * \pre NULL != arg
 */
int
clasp_useArgument_(
    clasp_arguments_t const*    args
,   clasp_argument_t const*     arg
);

void
clasp_count_flags_and_options_(
    clasp_specification_t const     specifications[]
,   size_t*                         numFlags
,   size_t*                         numOptions
);


/* /////////////////////////////////////////////////////////////////////////
 * character encoding abstraction
 */

#ifdef CLASP_USE_WIDE_STRINGS

# define clasp_fprintf_                                     fwprintf
# define clasp_strcat_                                      wcscat
# define clasp_strchr_                                      wcschr
# define clasp_strcmp_                                      wcscmp
# define clasp_strlen_                                      wcslen
# define clasp_strncmp_                                     wcsncmp
# define clasp_strpbrk_                                     wcspbrk
# define clasp_strrchr_                                     wcsrchr
# define clasp_strstr_                                      wcsstr
# define CLASP_LITERAL_(x)                                  L ## x
#else /* ? CLASP_USE_WIDE_STRINGS */

# define clasp_fprintf_                                     fprintf
# define clasp_strcat_                                      strcat
# define clasp_strchr_                                      strchr
# define clasp_strcmp_                                      strcmp
# define clasp_strlen_                                      strlen
# define clasp_strncmp_                                     strncmp
# define clasp_strpbrk_                                     strpbrk
# define clasp_strrchr_                                     strrchr
# define clasp_strstr_                                      strstr
# define CLASP_LITERAL_(x)                                  x
#endif


/* /////////////////////////////////////////////////////////////////////////
 * string
 */

/* Duplicates a string.
 *
 * \param ctxt The diagnostic context. May not be NULL;
 * param s The string to be duplicated;
 */
clasp_char_t* clasp_strdup_(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_char_t const*                 s
);

/* Duplicates a string.
 *
 * param s The string to be duplicated;
 */
clasp_char_t* clasp_strdup_raw_(
    clasp_char_t const* s
);

/* This function controls whether the library recognises just an equals
 * sign ('='), or both an equals sign '=' and a colon (':') as separating
 * an option name and value.
 *
 * \param s The string to be examined;
 * \param flags Flags that moderate the behaviour of the function;
 */
clasp_char_t*
clasp_strchreq_(
    clasp_char_t const* s
,   unsigned            flags
);

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
);

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
);

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
);

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
);

struct strtok_savectxt_t
{
    void*   p0;
    void*   p1;
};

/* string tokenisation a la strtok_r
 *
 * \pre (NULL != s)
 * \pre (NULL != delim)
 * \pre (NULL != saveptr)
 */
clasp_char_t*
clasp_strtok_r_(
    clasp_char_t*               s
,   clasp_char_t const*         delim
,   struct strtok_savectxt_t*   savectxt
);

/* string tokenisation a la strtok_r, except that the blanks are
 * preserved (and returned as empty, not null, strings)
 *
 * \pre (NULL != s)
 * \pre (NULL != delim)
 * \pre (NULL != savectxt)
 */
clasp_char_t*
clasp_strtok_wblank_r_(
    clasp_char_t*               s
,   clasp_char_t const*         delim
,   struct strtok_savectxt_t*   savectxt
);


/* ///////////////////////////// end of file //////////////////////////// */

