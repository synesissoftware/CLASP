/* /////////////////////////////////////////////////////////////////////////
 * File:    src/clasp.api.c
 *
 * Purpose: CLASP API.
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

#include "clasp.internal.h"

#if defined(_MSC_VER) && \
  defined(__STDC_SECURE_LIB__) && \
  defined(__STDC_WANT_SECURE_LIB__) && \
  __STDC_WANT_SECURE_LIB__ == 1

# pragma warning(disable : 4996)
#endif

#if (   defined(_WIN32) || \
        defined(_WIN64)) && \
    !defined(CLASP_CMDLINE_ARGS_NO_RECLS_ON_WINDOWS)

# define CLASP_CMDLINE_ARGS_USE_RECLS
#endif /* (_WIN32 || _WIN64) && !CLASP_CMDLINE_ARGS_NO_RECLS_ON_WINDOWS */

#ifdef CLASP_CMDLINE_ARGS_USE_RECLS

# include <recls/recls.h>
# if defined(CLASP_USE_WIDE_STRINGS) && \
     !defined(RECLS_CHAR_TYPE_IS_WCHAR)

#  error RECLS_CHAR_TYPE_IS_WCHAR is not defined when CLASP_USE_WIDE_STRINGS is defined!
# endif /* CLASP_USE_WIDE_STRINGS && !RECLS_CHAR_TYPE_IS_WCHAR */
#endif /* CLASP_CMDLINE_ARGS_USE_RECLS */

#include <errno.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * notes
 */

/*

For two reasons, we can only call recls *once* for each wildcard argument:
 - efficiency, because each expansion is expensive. This is a minor argument
   because this happens at the start of the process and would never
   eventuate to any noticeable performance degredation
 - the fs enumerations could give different results, possibly eventuating in
   a crash (due to insufficient space in the buffer) during a second pass.
   This is the major argument

 */


/* /////////////////////////////////////////////////////////////////////////
 * compiler warning suppression
 */

#if defined(_MSC_VER) && \
    defined(_DEBUG)

# pragma warning(disable : 4505)
#endif /* VC++ and _DEBUG */


/* /////////////////////////////////////////////////////////////////////////
 * constants and definitions
 */

#define CLASP_EXPANDEDARGS_ADDITIONAL                       (20)

#define CLASP_SECTION_MIN_                                  (1)
#define CLASP_SECTION_MAX_                                  (1000)


/* /////////////////////////////////////////////////////////////////////////
 * internal flags
 */

#define CLASP_ARG_F_USED_                                   (0x0002)


/* /////////////////////////////////////////////////////////////////////////
 * macros
 */

#define CLASP_STRING_NULL_OR_EMPTY_(s)                      (NULL == (s) || '\0' == 0[(s)])


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

void
clasp_count_flags_and_options_(
    clasp_specification_t const     specifications[]
,   size_t*                         numFlags
,   size_t*                         numOptions
)
{
    *numFlags = 0;
    *numOptions = 0;

    { clasp_specification_t const* p; for (p = specifications; CLASP_ARGTYPE_INVALID != p->type; ++p)
    {
        switch (p->type)
        {
        default:
            /* fall through */
        case CLASP_ARGTYPE_VALUE:

            break;
        case CLASP_ARGTYPE_FLAG:

            ++*numFlags;
            break;
        case CLASP_ARGTYPE_OPTION:

            ++*numOptions;
            break;
        }
    }}
}

static
int
clasp_evaluate_specification_index_(
    clasp_specification_t const     specifications[]
,   clasp_specification_t const*    alias
)
{
    int const r = stlsoft_static_cast(int, alias - specifications);

#if _DEBUG

    int                             r2;
    clasp_specification_t const*    a2;

    CLASP_ASSERT(NULL != specifications);
    CLASP_ASSERT(NULL != alias);
    CLASP_ASSERT(specifications <= alias);

    for (r2 = 0, a2 = specifications; a2 != alias; ++a2, ++r2)
    {}

    CLASP_ASSERT(r2 == r);
#endif /* _DEBUG */

    return r;
}

#ifdef CLASP_CMDLINE_ARGS_USE_RECLS

struct clasp_expanded_args_t
{
    clasp_diagnostic_context_t const*   ctxt;
    size_t                              size;       /*!< The current extent of (i.e. number of items in) args, the array of string pointers */
    size_t                              capacity;   /*!< Total capacity of array of pointers */
    clasp_char_t const**                args;       /*!< The array of string pointers */
    int                                 numFiles;
};
#endif /* CLASP_CMDLINE_ARGS_USE_RECLS */

#ifdef CLASP_CMDLINE_ARGS_USE_RECLS

static
int
RECLS_CALLCONV_DEFAULT clasp_recls_callback(
    recls_info_t                hEntry
,   recls_process_fn_param_t    param
)
{
    struct clasp_expanded_args_t* expandedArgs = (struct clasp_expanded_args_t*)param;

    if (expandedArgs->size == expandedArgs->capacity)
    {
        size_t                  newCapacity =   (expandedArgs->capacity + CLASP_EXPANDEDARGS_ADDITIONAL) * sizeof(clasp_char_t*);
        clasp_char_t const**    newArgs     =   (clasp_char_t const**)clasp_realloc_(expandedArgs->ctxt, (void*)expandedArgs->args, newCapacity);

        if (NULL == newArgs)
        {
            return 0; /* This cancels the search, which will be caught in the callee */
        }
        else
        {
            expandedArgs->args      =   newArgs;
            expandedArgs->capacity  =   newCapacity / sizeof(clasp_char_t*);
        }
    }

    /* Now we have enough space in the array, and we need to add the item */
    expandedArgs->args[expandedArgs->size] = clasp_strdup_(expandedArgs->ctxt, hEntry->searchRelativePath.begin);

    if (NULL == expandedArgs->args[expandedArgs->size])
    {
        return 0; /* This cancels the search, which will be handled by the callee */
    }
    else
    {
        ++expandedArgs->size;
    }

    ++expandedArgs->numFiles;

    return 1; /* This continues the search. */
}
#endif /* CLASP_CMDLINE_ARGS_USE_RECLS */

static
int
compare_clasp_argument_t_(
    clasp_argument_t const* lhs
,   clasp_argument_t const* rhs
)
{
    if (lhs->type == rhs->type)
    {
        int r = lhs->cmdLineIndex - rhs->cmdLineIndex;

        if (0 == r)
        {
            size_t n = (lhs->resolvedName.len < rhs->resolvedName.len) ? lhs->resolvedName.len : rhs->resolvedName.len;

            r = clasp_strncmp_(lhs->resolvedName.ptr, rhs->resolvedName.ptr, n);
        }

        return r;
    }
    else
    {
        switch (lhs->type)
        {
        default:
            CLASP_ASSERT(0);
        case CLASP_ARGTYPE_VALUE:
            switch (rhs->type)
            {
            default:
            case CLASP_ARGTYPE_VALUE:
                CLASP_ASSERT(0);
            case CLASP_ARGTYPE_OPTION:
            case CLASP_ARGTYPE_FLAG:
                return +1;
            }
        case CLASP_ARGTYPE_OPTION:
            switch (rhs->type)
            {
            default:
            case CLASP_ARGTYPE_OPTION:
                CLASP_ASSERT(0);
            case CLASP_ARGTYPE_VALUE:
                return -1;
            case CLASP_ARGTYPE_FLAG:
                return +1;
            }
            break;
        case CLASP_ARGTYPE_FLAG:
            switch (rhs->type)
            {
            default:
            case CLASP_ARGTYPE_FLAG:
                CLASP_ASSERT(0);
            case CLASP_ARGTYPE_VALUE:
            case CLASP_ARGTYPE_OPTION:
                return -1;
            }
            break;
        }
    }
}

static
int
compare_clasp_argument_t(
    void const* lhs
,   void const* rhs
)
{
    return compare_clasp_argument_t_(stlsoft_static_cast(clasp_argument_t const*, lhs), stlsoft_static_cast(clasp_argument_t const*, rhs));
}


struct clasp_arguments_x_t
{
    /* Memory:
     *
     * | clasp_arguments_t    |
     * |      mgmt info       |
     * |  arguments array(s)  |
     * |      strings         |
     */

    clasp_arguments_t           claspArgs;
    clasp_diagnostic_context_t  ctxt;
    size_t                      cb;
    clasp_char_t*               stringsBase;
    void*                       reserved0;
    size_t                      reserved1;
    void const*                 specifications;
    size_t                      reserved2;
    clasp_argument_t            args[1];
};
#ifndef __cplusplus
typedef struct clasp_arguments_x_t                          clasp_arguments_x_t;
#endif /* !__cplusplus */

clasp_arguments_x_t*
clasp_argsx_from_args_(
    clasp_arguments_t const* args
)
{
    CLASP_ASSERT(0 == offsetof(clasp_arguments_x_t, claspArgs));

    return (clasp_arguments_x_t*)stlsoft_const_cast(clasp_arguments_t*, args);
}

clasp_diagnostic_context_t const*
clasp_diagnostic_context_from_args_(
    clasp_arguments_t const* args
)
{
    clasp_arguments_x_t const* const argsx = clasp_argsx_from_args_(args);

    return &argsx->ctxt;
}

#if 0
static
clasp_specification_t const*
clasp_lookup_alias_len_(
    clasp_specification_t const specifications[]
,   clasp_char_t const*         arg
,   size_t                      cchArg
,   unsigned                    flags
);

static
clasp_specification_t const*
clasp_lookup_alias_(
    clasp_specification_t const specifications[]
,   clasp_char_t const*         arg
,   unsigned                    flags
)
{
    return clasp_lookup_alias_len_(specifications, arg, clasp_strlen_(arg), flags);
}
#endif

/* Looks up the given alias in the specifications vector, searching first for the
 * alias, then for non-defaulted mapped arguments, then for defaulted
 * mapped arguments.
 *
 * \param specifications The specifications array
 * \param arg Pointer to the argument
 * \param cchArg Length of the argument
 * \param flags
 */
static
clasp_specification_t const*
clasp_lookup_alias_len_(
    clasp_specification_t const specifications[]
,   clasp_char_t const*         arg
,   size_t                      cchArg
,   unsigned                    flags
)
{
    ((void)flags);

    if (NULL != specifications)
    {
        CLASP_ASSERT(NULL != arg);

        /* search in the specifications */

        { clasp_specification_t const* alias = specifications; for (; CLASP_ARGTYPE_INVALID != alias->type; ++alias)
        {
            if (NULL != alias->name)
            {
                if (0 == clasp_strncmp_(alias->name, arg, cchArg))
                {
                    return alias;
                }
            }
        }}

        /* search in the mappedArgument(s), but only those that don't have default values */

        { clasp_specification_t const* alias = specifications; for (; CLASP_ARGTYPE_INVALID != alias->type; ++alias)
        {
            if (NULL != alias->mappedArgument)
            {
                clasp_char_t const* const equal = clasp_strchreq_(alias->mappedArgument, flags);

                if (NULL == equal)
                {
                    const size_t len = clasp_strlen_(alias->mappedArgument);

                    if (len == cchArg)
                    {
                        if (0 == clasp_strncmp_(alias->mappedArgument, arg, cchArg))
                        {
                            return alias;
                        }
                    }
                }
            }
        }}

        /* search in the mappedArgument(s), but only those that do have default values */

        { clasp_specification_t const* alias = specifications; for (; CLASP_ARGTYPE_INVALID != alias->type; ++alias)
        {
            if (NULL != alias->mappedArgument)
            {
                clasp_char_t const* const equal = clasp_strchreq_(alias->mappedArgument, flags);

                if (NULL != equal)
                {
                    const size_t len = (size_t)(equal - alias->mappedArgument);

                    if (len == cchArg &&
                        0 == clasp_strncmp_(alias->mappedArgument, arg, cchArg))
                    {
                        return alias;
                    }
                }
            }
        }}
    }

    return NULL;
}

#if 0
static
clasp_bool_t
clasp_is_recognised_option_or_flag_(
    clasp_specification_t const specifications[]
,   clasp_char_t const*         arg
)
{
    if (NULL != specifications)
    {
        { for (specifications; CLASP_ARGTYPE_INVALID != specifications->type; ++specifications)
        {
            if (0 == clasp_strcmp_(specifications->name, arg) ||
                0 == clasp_strcmp_(specifications->mappedArgument, arg))
            {
                return clasp_true_v;
            }
        }}
    }

    return clasp_false_v;
}
#endif /* 0 */

static
clasp_bool_t
clasp_check_alias_duplicates_(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_specification_t const         specifications[]
)
{
    if (NULL != specifications)
    {
        clasp_specification_t const* from = specifications;

        { for (; CLASP_ARGTYPE_INVALID != from->type; ++from)
        {
            clasp_specification_t const* to = from;

            { for (++to; CLASP_ARGTYPE_INVALID != to->type; ++to)
            {
                if (NULL != from->name &&
                    NULL != to->name &&
                    0 != clasp_strlen_(from->name) &&
                    0 == clasp_strcmp_(from->name, to->name))
                {
                    CLASP_LOG_PRINTF(ctxt, CLASP_SEVIX_ERROR, CLASP_LITERAL_("programming error: duplicate argument alias: %s"), from->name);

                    return clasp_false_v;
                }
#if 0
                if (0 == clasp_strcmp_(from->mappedArgument, to->mappedArgument))
                {
                    CLASP_LOG_PRINTF(ctxt, CLASP_SEVIX_ERROR, CLASP_LITERAL_("programming error: duplicate argument name: %s"), from->mappedArgument);

                    return clasp_false_v;
                }
#endif /* 0 */
            }}
        }}
    }

    return clasp_true_v;
}

/* Parses the command-line for the program name (no directory, no extension)
 * and returns the result as a slice.
 *
 */
static
size_t
clasp_identify_programName_(
    unsigned                    flags
,   int                         argc
,   clasp_char_t*               argv[]
,   clasp_slice_t*              programName
)
{
    size_t const        argv0len        =   clasp_strlen_(argv[0]);
    clasp_char_t const* lastSlash       =   clasp_strrchr_(argv[0], '/');
#ifndef _WIN32

    clasp_char_t const* lastDot         =   argv[0] + argv0len;
#else

    clasp_char_t const* lastBackSlash   =   clasp_strrchr_(argv[0], '\\');
    clasp_char_t const* lastDot         =   clasp_strrchr_(argv[0], '.');

    if (NULL == lastSlash)
    {
        lastSlash = lastBackSlash;
    }
    else if (NULL != lastBackSlash)
    {
        if (lastSlash < lastBackSlash)
        {
            lastSlash = lastBackSlash;
        }
    }
#endif
    if (NULL != lastSlash)
    {
        ++lastSlash;
    }
    if (NULL == lastDot ||
        lastDot < lastSlash)
    {
        lastDot = argv[0] + argv0len;
    }
    if (NULL == lastSlash)
    {
        lastSlash = argv[0];
    }

    ((void)flags);
    ((void)argc);
    ((void)argv);
    CLASP_ASSERT(argc > 0);
    CLASP_ASSERT(NULL != programName);

    programName->len    =   stlsoft_static_cast(size_t, lastDot - lastSlash);
    programName->ptr    =   lastSlash;

    /* Post-conditions */

    CLASP_ASSERT(programName->len <= argv0len);
    CLASP_ASSERT(NULL == programName->ptr || (programName->ptr >= argv[0] && programName->ptr < argv[0] + argv0len));

    return programName->len;
}

/* Calculates the number of arguments, the amount of string memory, and the
 * total amount of memory required when the given arguments are parsed, with
 * respect to the given flags and specifications
 */
static
int
clasp_calculate_sizes_(
    unsigned                    flags
,   int                         argc
,   clasp_char_t*               argv[]
,   clasp_specification_t const specifications[]
,   size_t*                     numArgs
,   size_t*                     cbStrings
,   size_t*                     cbTotal
)
{
    clasp_bool_t    nextArgumentIsValue         =   clasp_false_v;
    clasp_bool_t    treatAllArgumentsAsValues   =   clasp_false_v;
    clasp_slice_t   programName;

    *numArgs    =   0;
    *cbStrings  =   0;
    *cbTotal    =   0;

    CLASP_ASSERT(argc > 0);

    /* Calculate the size of programName
     *
     */
    clasp_identify_programName_(flags, argc, argv, &programName);

    *cbStrings += 1 + programName.len;

    /* process all the arguments, incrementing, where
     * appropriate, *numArgs, and adding the required
     * string size (including nul-terminators) to
     * cbStrings
     */

    { int i; for (i = 1; i != argc; ++i)
    {
        clasp_char_t const* const   arg     =   argv[i];
        const size_t                argLen  =   clasp_strlen_(arg);

        if (nextArgumentIsValue)
        {
            ++*numArgs;

            *cbStrings += 1 + argLen;

            nextArgumentIsValue = clasp_false_v;
        }
        else if (   !treatAllArgumentsAsValues &&
                    '-' == arg[0])
        {
            CLASP_ASSERT(!nextArgumentIsValue);

            /* A hyphenated argument */

            if ('-' == arg[1])
            {
                /* double hyphen argument */

                if ('\0' == arg[2] &&
                    0 == (CLASP_F_DONT_RECOGNISE_DOUBLEHYPHEN_TO_START_VALUES & flags))
                {
                    /* The special "--" argument. Not added into array */

                    treatAllArgumentsAsValues = clasp_true_v;
                }
                else
                {
                    /* Need to work out whether it is an option, in order
                     * to work out whether to see whether the next argument
                     * is a value
                     *
                     * Also, we need to check whether it has an equal AND it
                     * has an alias, in which case we must translate the
                     * name before calculating
                     */

                    clasp_char_t const* const equal1 = clasp_strchreq_(arg + 2, flags);

                    if (NULL != equal1)
                    {
                        clasp_specification_t const* const alias = clasp_lookup_alias_len_(specifications, arg, (size_t)(equal1 - arg), flags);

                        if (NULL != alias)
                        {
                            if (!CLASP_STRING_NULL_OR_EMPTY_(alias->mappedArgument))
                            {
                                /* This will be an additional string, so add */

                                const size_t                longLen     =   clasp_strlen_(alias->mappedArgument);
                                clasp_char_t const* const   equal1_b    =   clasp_strchreq_(alias->mappedArgument, flags);

                                if (NULL != equal1_b)
                                {
                                    *cbStrings += 1u + (size_t)(equal1_b - alias->mappedArgument);
                                }
                                else
                                {
                                    *cbStrings += 1u + longLen;
                                }

                            }
                        }

                        ++*numArgs;
                    }
                    else
                    {
                        /* = sign not specified */

                        clasp_specification_t const* const alias = clasp_lookup_alias_len_(specifications, arg, argLen, flags);

                        if (NULL != alias)
                        {
                            const size_t longLen = (NULL == alias->mappedArgument) ? 0u : clasp_strlen_(alias->mappedArgument);

                            clasp_char_t const* const equal1_c = clasp_strchreq_(alias->mappedArgument, flags);

                            if (NULL != equal1_c)
                            {
                                /* has an '=' (or ':'), so interpret it as an option regardless of what the specifications says */

                                ++*numArgs;
                            }
                            else
                            {
                                /* not implicitly an option, so guided by the alias */

                                if (CLASP_ARGTYPE_OPTION == alias->type)
                                {
                                    clasp_char_t const* const   nextArg     =   (i < (argc - 1)) ? argv[i + 1] : NULL;
                                    size_t const                nextArgLen  =   (NULL != nextArg) ? clasp_strlen_(nextArg) : 0u;

                                    /* If it's an option
                                     *  AND
                                     * this argument has an alias
                                     *  AND
                                     * there's a subsequent argument
                                     *  AND
                                     * the next argument is not a recognised arguments
                                     */

                                    if (!CLASP_STRING_NULL_OR_EMPTY_(alias->name) &&
                                        0 != nextArgLen &&
                                        NULL == clasp_lookup_alias_len_(specifications, nextArg, nextArgLen, flags))
                                    {
                                        nextArgumentIsValue = clasp_true_v;
                                    }
                                    else
                                    {
                                        ++*numArgs;
                                    }
                                }
                                else
                                {
                                    ++*numArgs;
                                }
                            }

                            if (0u != longLen)
                            {
                                /* This will be an additional string, so add */

                                *cbStrings += 1u + longLen;
                            }
                        }
                        else
                        {
                            ++*numArgs;
                        }
                    }

                    /* The size is the same whether or not an equal is
                     * specified, because if it is the '=' will have to
                     * be replaced by a nul-terminator
                     */

                    *cbStrings += 1u + argLen;
                }
            }
            else
            {
                /* single hyphen argument */

                if ('\0' == arg[1])
                {
                    /* This is the special option with no name, which is
                     * usually used to indicate that the program should
                     * read from stdin; we don't ascribe any special meaning
                     * to it here
                     */

                    ++*numArgs;

                    *cbStrings += 1 + 1;
                }
                else
                {
                    clasp_char_t const* const equal2 = clasp_strchreq_(arg + 1, flags);

                    if (NULL != equal2)
                    {
                        clasp_specification_t const* const alias = clasp_lookup_alias_len_(specifications, arg, (size_t)(equal2 - arg), flags);

                        if (NULL != alias &&
                            !CLASP_STRING_NULL_OR_EMPTY_(alias->mappedArgument))
                        {
                            /* This will be an additional string, so add */

                            const size_t                longLen     =   clasp_strlen_(alias->mappedArgument);
                            clasp_char_t const* const   equal2_b    =   clasp_strchreq_(alias->mappedArgument, flags);

                            if (NULL != equal2_b)
                            {
                                *cbStrings += 1u + (size_t)(equal2_b - alias->mappedArgument);
                            }
                            else
                            {
                                *cbStrings += 1u + longLen;
                            }
                        }

                        ++*numArgs;

                        *cbStrings += 1 + argLen;
                    }
                    else if (NULL == specifications)
                    {
                        ++*numArgs;

                        *cbStrings += 1 + argLen;
                    }
                    else
                    {
                        /* work out whether option or flag */

                        clasp_specification_t const* const alias = clasp_lookup_alias_len_(specifications, arg, argLen, flags);

                        if (NULL != alias)
                        {
#if 0

                            clasp_char_t const* equal3;

                            if (NULL != alias->mappedArgument &&
                                '-' == alias->mappedArgument[0] &&
                                NULL != (equal3 = clasp_strchreq_(alias->mappedArgument, flags)))
                            {
                            }
                            else
                            {
                            }

                            if (NULL != alias->mappedArgument &&
                                '-' == alias->mappedArgument[0])
                            {
                                *cbStrings += 1 + clasp_strlen_(alias->mappedArgument);    /* Space for the resolved name */
                            }
                            *cbStrings += 1 + argLen;                               /* Space for the given name */

                            if (alias->type == CLASP_ARGTYPE_OPTION)
                            {
                                nextArgumentIsValue = clasp_true_v;
                            }
                            else
                            {
                                ++*numArgs;
                            }
#else /* ? 0 */

                            const size_t longLen = (NULL == alias->mappedArgument) ? 0u : clasp_strlen_(alias->mappedArgument);

                            if (CLASP_ARGTYPE_OPTION == alias->type)
                            {
                                clasp_char_t const* const equal1_c = (0u == longLen) ? NULL : clasp_strchreq_(alias->mappedArgument, flags);

                                if (NULL != equal1_c)
                                {
                                    ++*numArgs;
                                }
                                else
                                {
                                    nextArgumentIsValue = clasp_true_v;
                                }
                            }
                            else
                            {
                                ++*numArgs;
                            }

                            if (0u != longLen)
                            {
                                /* This will be an additional string, so add */

                                *cbStrings += 1u + longLen;
                            }

                            *cbStrings += 1 + argLen;                               /* Space for the given name */
#endif /* 0 */
                        }
                        else
                        {
                            /* It's one or more flags, any of which may also be
                             * specifications
                             */
                            const size_t n = argLen - 1;

                            CLASP_ASSERT(0 != n);
                            ((void)n);

                            { size_t j; for (j = 1; '\0' != arg[j]; ++j)
                            {
                                clasp_char_t                    flag[3] = { '-', '?', '\0' };
                                clasp_specification_t const*    flagAlias;

                                flag[1]     =   arg[j];
                                flagAlias   =   clasp_lookup_alias_len_(specifications, flag, 2u, flags);

                                if (NULL != flagAlias &&
                                    NULL != flagAlias->mappedArgument)
                                {
                                    clasp_char_t const* equal4;

                                    if ('-' == flagAlias->mappedArgument[0] &&
                                        NULL != (equal4 = clasp_strchreq_(flagAlias->mappedArgument, flags)))
                                    {
                                    }
                                    else
                                    {
                                    }

                                    *cbStrings += 1 + clasp_strlen_(flagAlias->mappedArgument);
                                }
                                else
                                {
                                    *cbStrings += 3; /* 3 === '-' + ? + '\0' */
                                }

                                ++*numArgs;
                            }}

                            *cbStrings += 1 + argLen;
                        }
                    }
                }
            }
        }
        else
        {
            CLASP_ASSERT(!nextArgumentIsValue);

            /* Append a value */
            ++*numArgs;

            *cbStrings += 1 + argLen;
        }
    }}

    if (nextArgumentIsValue)
    {
        /* A separate value argument is required, but not provided. We
         * will indicate this to the caller by having an empty value
         */

        ++*numArgs;
    }

    *cbTotal    =   0
                +   sizeof(clasp_arguments_x_t)
                +   (*numArgs ? (*numArgs - 1) : 0) * sizeof(clasp_argument_t)
                +   *cbStrings
                ;

    /* Round up to align on 16 */
    *cbTotal = (*cbTotal + 15) & ~15;

    return 0;
}

CLASP_CALL(int)
clasp_slice_t_cmp(
    clasp_slice_t const*    slice
,   clasp_char_t const*     str
)
{
    if (NULL == slice ||
        0 == slice->len)
    {
        if (!CLASP_STRING_NULL_OR_EMPTY_(str))
        {
            return +1;  /* null/empty lhs vs non-null/empty rhs */
        }
        else
        {
            return 0;   /* Both null/empty */
        }
    }
    else
    {
        if (CLASP_STRING_NULL_OR_EMPTY_(str))
        {
            return -1;  /* non-null/empty lhs vs null/empty rhs */
        }
        else
        {
            return clasp_strcmp_(slice->ptr, str);
        }
    }
}

CLASP_CALL(size_t)
clasp_slice_create(
    clasp_char_t const*     s
,   int                     n /* = -1 */
,   clasp_slice_t*          slice
)
{
    CLASP_ASSERT(NULL != slice);

    if (NULL == s)
    {
        slice->len  =   0;
        slice->ptr  =   NULL;

    }
    else
    {
        slice->len  =   (n < 0) ? clasp_strlen_(s) : stlsoft_static_cast(size_t, n);
        slice->ptr  =   s;
    }

    return slice->len;
}

static
clasp_char_t const*
clasp_add_string_to_area_(
    clasp_char_t**      current
,   clasp_char_t const* s
,   size_t              len
)
{
    clasp_char_t const* const original = *current;

    memcpy(*current, s, len);
    (*current)[len] = '\0';

    *current += (len + 1);

    return original;
}

static
clasp_char_t const*
clasp_add_flag_to_area_(
    clasp_char_t**  current
,   clasp_char_t    ch
)
{
    clasp_char_t const* const original = *current;

    *((*current)++) = '-';
    *((*current)++) = ch;
    *((*current)++) = '\0';

    return original;
}

static
int
clasp_is_valid_alias_section_range_(
    clasp_argtype_t t
)
{
    int const i = stlsoft_static_cast(int, t);

    return CLASP_SECTION_MIN_ <= i && CLASP_SECTION_MAX_ >= i;
}


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

CLASP_CALL(void)
clasp_init_diagnostic_context(
    clasp_diagnostic_context_t* dc
,   void*                       context
,   clasp_malloc_fn_t           pfnMalloc
,   clasp_realloc_fn_t          pfnRealloc
,   clasp_free_fn_t             pfnFree
,   clasp_log_fn_t              pfnLog
,   int const                   (*severities)[5]
,   void*                       param
)
{
    static int const severities_[5] = { 7, 4, 3, 1, 0 };

    CLASP_ASSERT(NULL != dc);
    CLASP_ASSERT((NULL == pfnMalloc && NULL == pfnRealloc && NULL == pfnFree) || (NULL != pfnMalloc && NULL != pfnRealloc && NULL != pfnFree));

    if (NULL == severities)
    {
        /* Null Object (Variable) pattern */
        severities = &severities_;
    }

    memset(dc, 0, sizeof(*dc));

    dc->context         =   context;

    dc->pfnMalloc       =   pfnMalloc;
    dc->pfnRealloc      =   pfnRealloc;
    dc->pfnFree         =   pfnFree;

    dc->pfnLog          =   pfnLog;
    dc->severities[0]   =   (*severities)[0];
    dc->severities[1]   =   (*severities)[1];
    dc->severities[2]   =   (*severities)[2];
    dc->severities[3]   =   (*severities)[3];
    dc->severities[4]   =   (*severities)[4];

    dc->param           =   param;
}

static
int
clasp_parseArguments_NoWild_(
    unsigned                            flags
,   int                                 argc
,   clasp_char_t*                       argv[]
,   int                                 originalArgc
,   clasp_char_t*                       originalArgv[]
,   clasp_specification_t const         specifications[]
,   clasp_diagnostic_context_t const*   ctxt
,   clasp_arguments_t const**           args
);

CLASP_CALL(int)
clasp_parseArguments(
    unsigned                            flags
,   int                                 argc
,   clasp_char_t*                       argv[]
,   clasp_specification_t const         specifications[]
,   clasp_diagnostic_context_t const*   ctxt
,   clasp_arguments_t const**           args
)
{
    clasp_diagnostic_context_t  ctxt_;
    int                         r;

    ctxt = clasp_verify_context_(ctxt, &ctxt_, &r);
    if (NULL == ctxt)
    {
        return r;
    }

    CLASP_LOG_PRINTF(ctxt, CLASP_SEVIX_DEBUG, CLASP_LITERAL_("clasp_parseArguments(): argc=%d"), argc);

    /* Validate the specifications. Must contain only:
     *
     * - flags
     * - options
     * - tacit section separator
     * - (in-range) section separators
     */
    if (NULL != specifications)
    {
        { clasp_specification_t const* specification = specifications; for (; CLASP_ARGTYPE_INVALID != specification->type; ++specification)
        {
            if (CLASP_ARGTYPE_FLAG == specification->type)
            {
                ; /* valid */
            }
            else
            if (CLASP_ARGTYPE_OPTION == specification->type)
            {
                ; /* valid */
            }
            else
            if (CLASP_ARGTYPE_TACIT_ == specification->type)
            {
                ; /* valid */
            }
            else
            if (CLASP_ARGTYPE_GAP_ == specification->type)
            {
                ; /* valid */
            }
            else
            if (clasp_is_valid_alias_section_range_(specification->type))
            {
                ; /* valid */
            }
            else
            if (CLASP_ARGTYPE_VALUE == specification->type)
            {
                CLASP_LOG_PRINTF(ctxt, CLASP_SEVIX_EMERG, CLASP_LITERAL_("value specified in specifications array"));

                return EINVAL;
            }
            else
            {
                /* Unknown argument type */
                CLASP_LOG_PRINTF(ctxt, CLASP_SEVIX_EMERG, CLASP_LITERAL_("unknown argument type (%d) specified in specifications array"), specification->type);

                return EINVAL;
            }

#if 0
            /* Requires the alias name to be a non-empty string */
            if (CLASP_STRING_NULL_OR_EMPTY_(specification->name))
            {
                CLASP_LOG_PRINTF(ctxt, CLASP_SEVIX_EMERG, CLASP_LITERAL_("alias name cannot be null or empty"));

                return EINVAL;
            }
#endif /* 0 */
        }}
    }

    if (!clasp_check_alias_duplicates_(ctxt, specifications))
    {
        return EINVAL;
    }

#ifdef CLASP_CMDLINE_ARGS_USE_RECLS

    {
        struct clasp_expanded_args_t    expandedArgs;

        expandedArgs.ctxt       =   ctxt;
        expandedArgs.size       =   0;
        expandedArgs.capacity   =   argc + CLASP_EXPANDEDARGS_ADDITIONAL;
        expandedArgs.args       =   (clasp_char_t const**)clasp_malloc_(ctxt, expandedArgs.capacity * sizeof(clasp_char_t*));

        if (NULL == expandedArgs.args)
        {
            CLASP_LOG_PRINTF(ctxt, CLASP_SEVIX_FATAL, CLASP_LITERAL_("could not allocate memory for wildcard expansion"));

            return ENOMEM;
        }
        else
        {
            int                     result          =   0;
            const recls_uint32_t    reclsFlags      =   RECLS_F_FILES | RECLS_F_DIRECTORIES | RECLS_F_LINKS | RECLS_F_DEVICES;
            clasp_char_t*           aposStrippedArg =   NULL;

            memset((void*)expandedArgs.args, 0, sizeof(clasp_char_t*) * expandedArgs.capacity);

            expandedArgs.args[0] = argv[0];
            ++expandedArgs.size;

            /* populate newArgv array using recls */
            { int i; for (i = 1; i != argc; ++i)
            {
                recls_rc_t          rc;
                clasp_char_t const* arg             =   argv[i];
                size_t              len             =   clasp_strlen_(arg);
                int                 isAposQuoted    =   0;

                expandedArgs.numFiles = 0;

                if (NULL != aposStrippedArg)
                {
                    clasp_free_(ctxt, aposStrippedArg);
                    aposStrippedArg = NULL;
                }

/* TODO: Need to process ranges , e.g. "[abc].txt" */

                if (len >= 2 &&
                    '\'' == arg[0] &&
                    '\'' == arg[len - 1])
                {
                    isAposQuoted = 1;

                    aposStrippedArg = clasp_strdup_(ctxt, arg + isAposQuoted);

                    if (NULL == aposStrippedArg)
                    {
                        goto cleanup;
                    }
                    else
                    {
                        aposStrippedArg[len - 2] = '\0';
                        --len;
                        arg = aposStrippedArg;
                    }
                }

                if (CLASP_F_DONT_EXPAND_WILDCARDS_ON_WINDOWS == (CLASP_F_DONT_EXPAND_WILDCARDS_ON_WINDOWS & flags) ||
                    NULL == clasp_strpbrk_(arg, CLASP_LITERAL_("*?")))
                {
                    rc = RECLS_RC_OK;
                }
                else
                {
                    if (0 == (CLASP_F_DO_EXPAND_WILDCARDS_IN_APOSQUOTES_ON_WINDOWS & flags) &&
                        isAposQuoted)
                    {
                        rc = RECLS_RC_OK;
                    }
                    else
                    {
                        rc = Recls_SearchProcess(CLASP_LITERAL_("."), arg, reclsFlags, clasp_recls_callback, &expandedArgs);
                    }
                }

                if (RECLS_SUCCEEDED(rc))
                {
                    if (0 == expandedArgs.numFiles)
                    {
                        CLASP_LOG_PRINTF(ctxt, CLASP_SEVIX_DEBUG, CLASP_LITERAL_("no expansion for argument [%.*s]"), (int)len, arg);

                        if (expandedArgs.size == expandedArgs.capacity)
                        {
                            size_t                  newCapacity =   (expandedArgs.capacity + CLASP_EXPANDEDARGS_ADDITIONAL) * sizeof(clasp_char_t*);
                            clasp_char_t const**    newArgs     =   (clasp_char_t const**)clasp_realloc_(ctxt, (void*)expandedArgs.args, newCapacity);

                            if (NULL == newArgs)
                            {
                                CLASP_LOG_PRINTF(ctxt, CLASP_SEVIX_FATAL, CLASP_LITERAL_("could not allocate memory for wildcard expansion"));

                                result = ENOMEM;

                                goto cleanup;
                            }
                            else
                            {
                                expandedArgs.args       =   newArgs;
                                expandedArgs.capacity   =   newCapacity / sizeof(clasp_char_t*);
                            }
                        }

                        expandedArgs.args[expandedArgs.size] = clasp_strdup_(ctxt, arg);

                        if (NULL == expandedArgs.args[1])
                        {
                            CLASP_LOG_PRINTF(ctxt, CLASP_SEVIX_FATAL, CLASP_LITERAL_("could not allocate memory for wildcard expansion"));

                            result = ENOMEM;

                            goto cleanup;
                        }

                        ++expandedArgs.size;
                    }
                    else
                    {
                        ; /* Nothing to do, because the callback has done it */

                        CLASP_LOG_PRINTF(ctxt, CLASP_SEVIX_DEBUG, CLASP_LITERAL_("%d matching files for wildcard [%.*s]"), (int)expandedArgs.numFiles, (int)len, arg);
                    }
                }
                else if (RECLS_RC_USER_CANCELLED_SEARCH == rc)
                {
                    CLASP_LOG_PRINTF(ctxt, CLASP_SEVIX_FATAL, CLASP_LITERAL_("could not allocate memory for wildcard expansion"));

                    result = ENOMEM;

                    goto cleanup;
                }
                else
                {
                    CLASP_LOG_PRINTF(ctxt, CLASP_SEVIX_FATAL, CLASP_LITERAL_("wildcard expansion failed"));

                    result = EIO;

                    goto cleanup;
                }
            }}

            /* now invoke on "new" args array */

            result = clasp_parseArguments_NoWild_(flags, (int)expandedArgs.size, expandedArgs.args, argc, argv, specifications, ctxt, args);


cleanup:
            clasp_free_(ctxt, aposStrippedArg);

            /* free newArgv array */
            { size_t i; for (i = 1; i != expandedArgs.size; ++i)
            {
                clasp_free_(ctxt, (void*)expandedArgs.args[i]);
            }}
            clasp_free_(ctxt, (void*)expandedArgs.args);

            return result;
        }
    }
#else /* ? CLASP_CMDLINE_ARGS_USE_RECLS */

    return clasp_parseArguments_NoWild_(flags, argc, argv, argc, argv, specifications, ctxt, args);
#endif /* CLASP_CMDLINE_ARGS_USE_RECLS */
}

static
int
clasp_parseArguments_NoWild_(
    unsigned                            flags
,   int                                 argc
,   clasp_char_t*                       argv[]
,   int                                 originalArgc
,   clasp_char_t*                       originalArgv[]
,   clasp_specification_t const         specifications[]
,   clasp_diagnostic_context_t const*   ctxt
,   clasp_arguments_t const**           args
)
{
    size_t                      cbTotal;
    size_t                      numArgs;
    size_t                      cbStrings;
    clasp_arguments_x_t*        argsx;

    CLASP_LOG_PRINTF(ctxt, CLASP_SEVIX_DEBUG, CLASP_LITERAL_("clasp_parseArguments_NoWild_(): argc=%d"), argc);

    CLASP_ASSERT(argc > 0);
    CLASP_ASSERT(NULL != ctxt);
    CLASP_ASSERT(NULL != args);

    *args = NULL;

    clasp_calculate_sizes_(flags, argc, argv, specifications, &numArgs, &cbStrings, &cbTotal);

    argsx = stlsoft_static_cast(clasp_arguments_x_t*, clasp_malloc_(ctxt, cbTotal));

    if (NULL == argsx)
    {
        CLASP_LOG_PRINTF(ctxt, CLASP_SEVIX_FATAL, CLASP_LITERAL_("could not allocate memory to store results"));

        return ENOMEM;
    }

    memcpy(&argsx->ctxt, ctxt, sizeof(argsx->ctxt));

    argsx->reserved0      = NULL;
    argsx->reserved1      = 0;
    argsx->specifications = specifications;
    argsx->reserved2      = 0;

    argsx->claspArgs.numArguments       =   numArgs;
    argsx->claspArgs.arguments          =   NULL;
    argsx->claspArgs.numFlagsAndOptions =   0;
    argsx->claspArgs.flagsAndOptions    =   NULL;
    argsx->claspArgs.numFlags           =   0;
    argsx->claspArgs.flags              =   NULL;
    argsx->claspArgs.numOptions         =   0;
    argsx->claspArgs.options            =   NULL;
    argsx->claspArgs.numValues          =   0;
    argsx->claspArgs.values             =   NULL;
    argsx->claspArgs.argc               =   originalArgc;
    argsx->claspArgs.argv               =   originalArgv;
#if 0
    argsx->claspArgs.programName;
#endif

    argsx->cb                           =   cbTotal;
    argsx->stringsBase                  =   stlsoft_static_cast(clasp_char_t*, stlsoft_static_cast(void*, argsx->args + numArgs));

#ifdef _DEBUG
    memset(&argsx->args[0], '~', numArgs * sizeof(clasp_argument_t));
    memset(argsx->stringsBase, '%', cbStrings);
#endif /* _DEBUG */

{
    clasp_slice_t       programName;

    clasp_bool_t        nextArgumentIsValue         =   clasp_false_v;
    clasp_bool_t        treatAllArgumentsAsValues   =   clasp_false_v;

    clasp_argument_t*   currentArg                  =   &argsx->args[0];
    clasp_char_t*       currentString               =   argsx->stringsBase;

    size_t              numValues                   =   0;
    size_t              numOptions                  =   0;
    size_t              numFlags                    =   0;

    { int i; for (i = 1; i != argc; ++i)
    {
        clasp_char_t const* const   arg     =   argv[i];
        const size_t                argLen  =   clasp_strlen_(arg);

        CLASP_LOG_PRINTF(&argsx->ctxt, CLASP_SEVIX_DEBUG, CLASP_LITERAL_("argv[%d]: [%.*s]"), i, (int)argLen, arg);

        if (nextArgumentIsValue)
        {
            /* Append an option */

            currentArg->value.len   =   argLen;
            currentArg->value.ptr   =   clasp_add_string_to_area_(&currentString, arg, argLen);

            CLASP_LOG_PRINTF(&argsx->ctxt, CLASP_SEVIX_DEBUG, CLASP_LITERAL_("found value [%.*s] for option [%.*s]"), (int)currentArg->value.len, currentArg->value.ptr, (int)currentArg->givenName.len, currentArg->givenName.ptr);

            ++currentArg;

            nextArgumentIsValue = clasp_false_v;
        }
        else if (   !treatAllArgumentsAsValues &&
                    '-' == arg[0])
        {
            CLASP_ASSERT(!nextArgumentIsValue);

            /* A hyphenated argument */

            if ('-' == arg[1])
            {
                /* double hyphen argument */

                if ('\0' == arg[2] &&
                    0 == (CLASP_F_DONT_RECOGNISE_DOUBLEHYPHEN_TO_START_VALUES & flags))
                {
                    /* The special "--" argument. Not added into array */

                    treatAllArgumentsAsValues = clasp_true_v;
                }
                else
                {
                    /* Now work out whether there's an associated value. If
                     * there is, we will need to allocate the length
                     */

                    clasp_char_t const* const equal5 = clasp_strchreq_(arg + 2, flags);

                    if (NULL != equal5)
                    {
                        const size_t nameLen = stlsoft_static_cast(size_t, equal5 - arg);

                        clasp_specification_t const* const alias = clasp_lookup_alias_len_(specifications, arg, (size_t)(equal5 - arg), flags);

                        if (NULL != alias &&
                            !CLASP_STRING_NULL_OR_EMPTY_(alias->mappedArgument))
                        {
                            const size_t                longLen     =   clasp_strlen_(alias->mappedArgument);
                            clasp_char_t const* const   equal5_c    =   clasp_strchreq_(alias->mappedArgument, flags);

                            currentArg->resolvedName.len    =   (NULL == equal5_c) ? longLen : (size_t)(equal5_c - alias->mappedArgument);
                            currentArg->resolvedName.ptr    =   clasp_add_string_to_area_(&currentString, alias->mappedArgument, currentArg->resolvedName.len);
                            currentArg->givenName.len       =   nameLen;
                            currentArg->givenName.ptr       =   clasp_add_string_to_area_(&currentString, arg, nameLen);
                        }
                        else
                        {
                            currentArg->resolvedName.len    =   nameLen;
                            currentArg->resolvedName.ptr    =   clasp_add_string_to_area_(&currentString, arg, nameLen);
                            currentArg->givenName.len       =   currentArg->resolvedName.len;
                            currentArg->givenName.ptr       =   currentArg->resolvedName.ptr;
                        }

                        currentArg->value.len           =   argLen - (nameLen + 1);
                        currentArg->value.ptr           =   clasp_add_string_to_area_(&currentString, equal5 + 1, currentArg->value.len);
                        currentArg->type                =   CLASP_ARGTYPE_OPTION;
                        ++numOptions;

                        if (NULL != alias)
                        {
                            currentArg->aliasIndex      =   clasp_evaluate_specification_index_(specifications, alias);
                        }
                        else
                        {
                            currentArg->aliasIndex      =   -1;
                        }
                    }
                    else
                    {
                        /* = sign not specified */

                        clasp_specification_t const* const alias = clasp_lookup_alias_len_(specifications, arg, argLen, flags);

                        if (NULL != alias &&
                            !CLASP_STRING_NULL_OR_EMPTY_(alias->mappedArgument))
                        {
                            clasp_char_t const* const equal5_b = clasp_strchreq_(alias->mappedArgument, flags);

                            if (NULL != equal5_b)
                            {
                                /* has an '=' (or ':'), so interpret it as an option regardless of what the specifications says */

                                currentArg->resolvedName.len    =   (size_t)(equal5_b - alias->mappedArgument);
                                currentArg->resolvedName.ptr    =   clasp_add_string_to_area_(&currentString, alias->mappedArgument, currentArg->resolvedName.len);
                                currentArg->givenName.len       =   argLen;
                                currentArg->givenName.ptr       =   clasp_add_string_to_area_(&currentString, arg, argLen);
                                currentArg->value.len           =   clasp_strlen_(alias->mappedArgument) - (1u + (size_t)(equal5_b - alias->mappedArgument));
                                currentArg->value.ptr           =   clasp_add_string_to_area_(&currentString, equal5_b + 1, currentArg->value.len);
                                currentArg->type                =   CLASP_ARGTYPE_OPTION;
                                ++numOptions;
                            }
                            else
                            {
                                /* not implicitly an option, so guided by the alias */

                                currentArg->resolvedName.len    =   clasp_strlen_(alias->mappedArgument);
                                currentArg->resolvedName.ptr    =   clasp_add_string_to_area_(&currentString, alias->mappedArgument, currentArg->resolvedName.len);
                                currentArg->givenName.len       =   argLen;
                                currentArg->givenName.ptr       =   clasp_add_string_to_area_(&currentString, arg, argLen);

                                if (alias->type == CLASP_ARGTYPE_OPTION)
                                {
                                    clasp_char_t const* const   nextArg     =   (i < (argc - 1)) ? argv[i + 1] : NULL;
                                    size_t const                nextArgLen  =   (NULL != nextArg) ? clasp_strlen_(nextArg) : 0u;

                                    /* If it's an option
                                     *  AND
                                     * this argument has an alias
                                     *  AND
                                     * there's a subsequent argument
                                     *  AND
                                     * the next argument is not a recognised arguments
                                     */

                                    if (!CLASP_STRING_NULL_OR_EMPTY_(alias->name) &&
                                        0 != nextArgLen &&
                                        NULL == clasp_lookup_alias_len_(specifications, nextArg, nextArgLen, flags))
                                    {
                                        nextArgumentIsValue = clasp_true_v;
                                    }
                                    else
                                    {
                                        currentArg->value.len   =   0;
                                        currentArg->value.ptr   =   NULL;
                                    }
                                    ++numOptions;
                                }
                                else
                                {
                                    currentArg->value.len       =   0;
                                    currentArg->value.ptr       =   NULL;
                                    ++numFlags;
                                }

                                currentArg->type                =   alias->type;
                            }
                        }
                        else
                        {
                            currentArg->resolvedName.len    =   argLen;
                            currentArg->resolvedName.ptr    =   clasp_add_string_to_area_(&currentString, arg, argLen);
                            currentArg->givenName.len       =   currentArg->resolvedName.len;
                            currentArg->givenName.ptr       =   currentArg->resolvedName.ptr;
                            currentArg->value.len           =   0;
                            currentArg->value.ptr           =   NULL;
                            if (NULL != alias &&
                                CLASP_ARGTYPE_OPTION == alias->type)
                            {
                                currentArg->type            =   CLASP_ARGTYPE_OPTION;
                                nextArgumentIsValue         =   clasp_true_v;
                                ++numOptions;
                            }
                            else
                            {
                                currentArg->type            =   CLASP_ARGTYPE_FLAG;
                                ++numFlags;
                            }
                        }

                        if (NULL != alias)
                        {
                            currentArg->aliasIndex      =   clasp_evaluate_specification_index_(specifications, alias);
                        }
                        else
                        {
                            currentArg->aliasIndex      =   -1;
                        }
                    }
                    currentArg->numGivenHyphens =   2;
                    currentArg->cmdLineIndex    =   i;
                    currentArg->flags           =   0;

                    if (!nextArgumentIsValue)
                    {
                        ++currentArg;
                    }
                }
            }
            else
            {
                /* single hyphen argument - work out whether option or flag */

                if ('\0' == arg[1])
                {
                    /* This is the special option with no name, which is
                     * usually used to indicate that the program should
                     * read from stdin
                     */

                    currentArg->resolvedName.len    =   1;
                    currentArg->resolvedName.ptr    =   clasp_add_string_to_area_(&currentString, CLASP_LITERAL_("-"), 1);
                    currentArg->givenName.len       =   currentArg->resolvedName.len;
                    currentArg->givenName.ptr       =   currentArg->resolvedName.ptr;
                    currentArg->value.len           =   0;
                    currentArg->value.ptr           =   NULL;
                    currentArg->numGivenHyphens     =   1;
                    currentArg->aliasIndex          =   -1;
                    currentArg->type                =   CLASP_ARGTYPE_FLAG;
                    currentArg->cmdLineIndex        =   i;
                    currentArg->flags               =   0;

                    if (flags & CLASP_F_TREAT_SINGLEHYPHEN_AS_VALUE)
                    {
                        currentArg->value.len       =   currentArg->resolvedName.len;
                        currentArg->value.ptr       =   currentArg->resolvedName.ptr;
                        currentArg->type            =   CLASP_ARGTYPE_VALUE;
                        ++numValues;
                    }
                    else
                    {
                        ++numFlags;
                    }

                    ++currentArg;
                }
                else
                {
                    clasp_char_t const* const equal6 = clasp_strchreq_(arg + 1, flags);

                    if (NULL != equal6)
                    {
                        const size_t nameLen = stlsoft_static_cast(size_t, equal6 - arg);

                        clasp_specification_t const* const alias = clasp_lookup_alias_len_(specifications, arg, (size_t)(equal6 - arg), flags);

                        if (NULL != alias &&
                            !CLASP_STRING_NULL_OR_EMPTY_(alias->mappedArgument))
                        {
                            const size_t                longLen     =   clasp_strlen_(alias->mappedArgument);
                            clasp_char_t const* const   equal6_b    =   clasp_strchreq_(alias->mappedArgument, flags);

                            currentArg->resolvedName.len    =   (NULL == equal6_b) ? longLen : (size_t)(equal6_b - alias->mappedArgument);
                            currentArg->resolvedName.ptr    =   clasp_add_string_to_area_(&currentString, alias->mappedArgument, currentArg->resolvedName.len);
                            currentArg->givenName.len       =   nameLen;
                            currentArg->givenName.ptr       =   clasp_add_string_to_area_(&currentString, arg, nameLen);
                        }
                        else
                        {
                            currentArg->resolvedName.len    =   nameLen;
                            currentArg->resolvedName.ptr    =   clasp_add_string_to_area_(&currentString, arg, nameLen);
                            currentArg->givenName.len       =   currentArg->resolvedName.len;
                            currentArg->givenName.ptr       =   currentArg->resolvedName.ptr;
                        }

                        currentArg->value.len           =   argLen - (nameLen + 1);
                        currentArg->value.ptr           =   clasp_add_string_to_area_(&currentString, equal6 + 1, currentArg->value.len);
                        currentArg->type                =   CLASP_ARGTYPE_OPTION;
                        currentArg->cmdLineIndex        =   i;
                        currentArg->numGivenHyphens     =   1;
                        if (NULL != alias)
                        {
                            currentArg->aliasIndex      =   clasp_evaluate_specification_index_(specifications, alias);
                        }
                        else
                        {
                            currentArg->aliasIndex      =   -1;
                        }
                        currentArg->flags               =   0;

                        ++currentArg;
                        ++numOptions;
                    }
                    else if (NULL == specifications)
                    {
                        /* Without any specifications, we must assume a flag */

                        currentArg->resolvedName.len    =   argLen;
                        currentArg->resolvedName.ptr    =   clasp_add_string_to_area_(&currentString, arg, argLen);
                        currentArg->givenName.len       =   argLen;
                        currentArg->givenName.ptr       =   currentArg->resolvedName.ptr;
                        currentArg->value.len           =   0;
                        currentArg->value.ptr           =   NULL;
                        currentArg->type                =   CLASP_ARGTYPE_FLAG;
                        currentArg->cmdLineIndex        =   i;
                        currentArg->numGivenHyphens     =   1;
                        currentArg->aliasIndex          =   -1;
                        currentArg->flags               =   0;

                        ++currentArg;
                        ++numFlags;
                    }
                    else
                    {
                        /* work out whether option or flag */

                        clasp_specification_t const* const alias = clasp_lookup_alias_len_(specifications, arg, argLen, flags);

                        if (NULL != alias)
                        {
                            clasp_char_t const* equal7;

                            if (NULL != alias->mappedArgument &&
                                '-' == alias->mappedArgument[0] &&
                                NULL != (equal7 = clasp_strchreq_(alias->mappedArgument, flags)))
                            {
                                const size_t nameLen = stlsoft_static_cast(size_t, equal7 - alias->mappedArgument);

                                currentArg->resolvedName.len    =   nameLen;
                                currentArg->resolvedName.ptr    =   clasp_add_string_to_area_(&currentString, alias->mappedArgument, nameLen);
                                currentArg->givenName.len       =   argLen;
                                currentArg->givenName.ptr       =   clasp_add_string_to_area_(&currentString, arg, argLen);
                                currentArg->value.len           =   clasp_strlen_(equal7 + 1);
                                currentArg->value.ptr           =   clasp_add_string_to_area_(&currentString, equal7 + 1, currentArg->value.len);
                                currentArg->type                =   CLASP_ARGTYPE_OPTION;
                                currentArg->flags               =   0;
                            }
                            else
                            {
                                if (NULL != alias->mappedArgument &&
                                    '-' == alias->mappedArgument[0])
                                {
                                    currentArg->resolvedName.len    =   clasp_strlen_(alias->mappedArgument);
                                    currentArg->resolvedName.ptr    =   clasp_add_string_to_area_(&currentString, alias->mappedArgument, currentArg->resolvedName.len);
                                    currentArg->givenName.len       =   argLen;
                                    currentArg->givenName.ptr       =   clasp_add_string_to_area_(&currentString, arg, argLen);
                                }
                                else
                                {
                                    currentArg->givenName.len       =   argLen;
                                    currentArg->givenName.ptr       =   clasp_add_string_to_area_(&currentString, arg, argLen);
                                    currentArg->resolvedName.len    =   currentArg->givenName.len;
                                    currentArg->resolvedName.ptr    =   currentArg->givenName.ptr;
                                }

                                if (alias->type == CLASP_ARGTYPE_OPTION)
                                {
                                    nextArgumentIsValue = clasp_true_v;
                                }
                                else
                                {
                                    currentArg->value.len       =   0;
                                    currentArg->value.ptr       =   NULL;
                                }

                                currentArg->type                =   alias->type;

                                if (nextArgumentIsValue)
                                {
                                    currentArg->type = CLASP_ARGTYPE_OPTION; /* Ignore the alias' type here */
                                }

                                currentArg->flags               =   0;
                            }

                            currentArg->cmdLineIndex    =   i;
                            currentArg->numGivenHyphens =   1;
                            currentArg->aliasIndex      =   clasp_evaluate_specification_index_(specifications, alias);

                            switch (currentArg->type)
                            {
                            default:
                                CLASP_ASSERT(0);
                            case CLASP_ARGTYPE_VALUE:
                                CLASP_ASSERT(0);
                            case CLASP_ARGTYPE_OPTION:
                                ++numOptions;
                                break;
                            case CLASP_ARGTYPE_FLAG:
                                ++numFlags;
                                break;
                            }

                            if (!nextArgumentIsValue)
                            {
                                ++currentArg;
                            }
                        }
                        else
                        {
                            /* It's one or more flags, any of which may also be
                             * specifications
                             */
                            const size_t                n           =   argLen - 1;
                            clasp_char_t const* const   givenName   =   clasp_add_string_to_area_(&currentString, arg, argLen);

                            CLASP_ASSERT(0 != n);
                            ((void)n);

                            { size_t j; for (j = 1; '\0' != arg[j]; ++j)
                            {
                                clasp_char_t                    flag[3] = { '-', '?', '\0' };
                                clasp_specification_t const*    flagAlias;

                                flag[1]     =   arg[j];
                                flagAlias   =   clasp_lookup_alias_len_(specifications, flag, 2u, flags);

                                if (NULL != flagAlias)
                                {
                                    /* This is similar to the above processing with the exception
                                     * that we do not account for following values
                                     */

                                    clasp_char_t const* equal8;

                                    if (NULL != flagAlias->mappedArgument &&
                                        '-' == flagAlias->mappedArgument[0] &&
                                        NULL != (equal8 = clasp_strchreq_(flagAlias->mappedArgument, flags)))
                                    {
                                        const size_t nameLen = stlsoft_static_cast(size_t, equal8 - flagAlias->mappedArgument);

                                        currentArg->resolvedName.len    =   nameLen;
                                        currentArg->resolvedName.ptr    =   clasp_add_string_to_area_(&currentString, flagAlias->mappedArgument, nameLen);
                                        currentArg->givenName.len       =   argLen;
                                        currentArg->givenName.ptr       =   givenName;
                                        currentArg->value.len           =   clasp_strlen_(equal8 + 1);
                                        currentArg->value.ptr           =   clasp_add_string_to_area_(&currentString, equal8 + 1, currentArg->value.len);
                                        currentArg->type                =   CLASP_ARGTYPE_OPTION;
                                    }
                                    else
                                    {
                                        if (NULL != flagAlias->mappedArgument)
                                        {
                                            currentArg->resolvedName.len    =   clasp_strlen_(flagAlias->mappedArgument);
                                            currentArg->resolvedName.ptr    =   clasp_add_string_to_area_(&currentString, flagAlias->mappedArgument, currentArg->resolvedName.len);
                                        }
                                        else
                                        {
                                            currentArg->resolvedName.len    =   2u;
                                            currentArg->resolvedName.ptr    =   clasp_add_string_to_area_(&currentString, flag, 2u);
                                        }
                                        currentArg->givenName.len       =   argLen;
                                        currentArg->givenName.ptr       =   givenName;
                                        currentArg->value.len           =   0;
                                        currentArg->value.ptr           =   NULL;
                                        currentArg->type                =   flagAlias->type;
                                    }
                                    currentArg->cmdLineIndex        =   i;
                                    currentArg->numGivenHyphens     =   1;
                                    currentArg->aliasIndex          =   clasp_evaluate_specification_index_(specifications, flagAlias);
                                    currentArg->flags               =   0;

                                    switch (currentArg->type)
                                    {
                                    default:
                                        CLASP_ASSERT(0);
                                    case CLASP_ARGTYPE_VALUE:
                                        CLASP_ASSERT(0);
                                    case CLASP_ARGTYPE_OPTION:
                                        ++numOptions;
                                        break;
                                    case CLASP_ARGTYPE_FLAG:
                                        ++numFlags;
                                        break;
                                    }

                                    ++currentArg;
                                }
                                else
                                {
                                    currentArg->resolvedName.len    =   2;
                                    currentArg->resolvedName.ptr    =   clasp_add_flag_to_area_(&currentString, arg[j]);
                                    currentArg->givenName.len       =   argLen;
                                    currentArg->givenName.ptr       =   givenName;
                                    currentArg->value.len           =   0;
                                    currentArg->value.ptr           =   NULL;
                                    currentArg->cmdLineIndex        =   i;
                                    currentArg->type                =   CLASP_ARGTYPE_FLAG;
                                    currentArg->numGivenHyphens     =   1;
                                    currentArg->aliasIndex          =   -1;
                                    currentArg->flags               =   0;

                                    ++currentArg;
                                    ++numFlags;
                                }
                            }}
                        }
                    }
                }
            }
        }
        else
        {
            /* Append a value */
            currentArg->resolvedName.len    =   0;
            currentArg->resolvedName.ptr    =   NULL;
            currentArg->givenName.len       =   0;
            currentArg->givenName.ptr       =   NULL;

            currentArg->value.len           =   argLen;
            currentArg->value.ptr           =   clasp_add_string_to_area_(&currentString, arg, currentArg->value.len);

            currentArg->cmdLineIndex        =   i;
            currentArg->type                =   CLASP_ARGTYPE_VALUE;
            currentArg->numGivenHyphens     =   0;
            currentArg->aliasIndex          =   -1;
            currentArg->flags               =   0;

            ++currentArg;
            ++numValues;
        }
    }}

    if (nextArgumentIsValue)
    {
        /* A separate value argument is required, but not provided. We
         * will indicate this to the caller by having an empty value
         */

        currentArg->value.len       =   0;
        currentArg->value.ptr       =   NULL;
    }

#ifdef _DEBUG
    if (NULL != specifications)
    {
        size_t const numSpecifications = clasp_countSpecifications(specifications);

        { size_t i; for (i = 0; i != argsx->claspArgs.numArguments; ++i)
        {
            CLASP_ASSERT(argsx->args[i].aliasIndex >= -1 && argsx->args[i].aliasIndex < (int)numSpecifications);
        }}
    }
#endif /* _DEBUG */

    /* Build in the program name */

    clasp_identify_programName_(flags, argc, argv, &programName);

    argsx->claspArgs.programName.len    =   programName.len;
    argsx->claspArgs.programName.ptr    =   clasp_add_string_to_area_(&currentString, programName.ptr, programName.len);

    if (0 == (flags & CLASP_F_PRESERVE_ORIGINAL_ARGUMENT_ORDER))
    {
        CLASP_LOG_PRINTF(ctxt, CLASP_SEVIX_DEBUG, CLASP_LITERAL_("sorting results"));

        /* Now we must sort them */
        qsort(&argsx->args[0], argsx->claspArgs.numArguments, sizeof(clasp_argument_t), compare_clasp_argument_t);

        argsx->claspArgs.arguments          =   &argsx->args[0];
        argsx->claspArgs.numFlagsAndOptions =   numFlags + numOptions;
        argsx->claspArgs.flagsAndOptions    =   &argsx->args[0];
        argsx->claspArgs.numFlags           =   numFlags;
        argsx->claspArgs.flags              =   &argsx->args[0];
        argsx->claspArgs.numOptions         =   numOptions;
        argsx->claspArgs.options            =   &argsx->args[0] + numFlags;
        argsx->claspArgs.numValues          =   numValues;
        argsx->claspArgs.values             =   &argsx->args[0] + numFlags + numOptions;

        CLASP_ASSERT(NULL != argsx);

        CLASP_ASSERT(numFlags + numOptions + numValues == numArgs);

        CLASP_ASSERT(argsx->claspArgs.numArguments == numArgs);
        CLASP_ASSERT(NULL != argsx->claspArgs.arguments);
        CLASP_ASSERT(argsx->claspArgs.numFlagsAndOptions <= argsx->claspArgs.numArguments);
        CLASP_ASSERT(NULL != argsx->claspArgs.flagsAndOptions);
        CLASP_ASSERT(argsx->claspArgs.numFlags <= argsx->claspArgs.numArguments);
        CLASP_ASSERT(NULL != argsx->claspArgs.flags);
        CLASP_ASSERT(argsx->claspArgs.numOptions <= argsx->claspArgs.numArguments);
        CLASP_ASSERT(NULL != argsx->claspArgs.options);
        CLASP_ASSERT(argsx->claspArgs.numValues <= argsx->claspArgs.numArguments);
        CLASP_ASSERT(NULL != argsx->claspArgs.values);
    }
    else
    {
        argsx->claspArgs.arguments          =   &argsx->args[0];

        CLASP_ASSERT(NULL != argsx);

        CLASP_ASSERT(argsx->claspArgs.numArguments == numArgs);
        CLASP_ASSERT(NULL != argsx->claspArgs.arguments);
        CLASP_ASSERT(0 == argsx->claspArgs.numFlagsAndOptions);
        CLASP_ASSERT(NULL == argsx->claspArgs.flagsAndOptions);
        CLASP_ASSERT(0 == argsx->claspArgs.numFlags);
        CLASP_ASSERT(NULL == argsx->claspArgs.flags);
        CLASP_ASSERT(0 == argsx->claspArgs.numOptions);
        CLASP_ASSERT(NULL == argsx->claspArgs.options);
        CLASP_ASSERT(0 == argsx->claspArgs.numValues);
        CLASP_ASSERT(NULL == argsx->claspArgs.values);
    }

    CLASP_ASSERT(originalArgc == argsx->claspArgs.argc);
    CLASP_ASSERT(originalArgv == argsx->claspArgs.argv);

    CLASP_ASSERT(argsx->cb == cbTotal);
    CLASP_ASSERT(currentString >= argsx->stringsBase);
    CLASP_ASSERT(stlsoft_static_cast(size_t, currentString - argsx->stringsBase) == cbStrings);

    *args = &argsx->claspArgs;

    return 0;
}}

CLASP_CALL(void)
clasp_releaseArguments(
    clasp_arguments_t const*    args
)
{
    clasp_arguments_x_t* argsx = clasp_argsx_from_args_(args);

    CLASP_LOG_PRINTF(&argsx->ctxt, CLASP_SEVIX_DEBUG, CLASP_LITERAL_("clasp_releaseArguments()"));

    clasp_free_(&argsx->ctxt, argsx);
}

CLASP_CALL(clasp_specification_t const*)
clasp_getSpecifications(
    clasp_arguments_t const*    args
)
{
    if (NULL != args)
    {
        return (clasp_specification_t const*)clasp_argsx_from_args_(args)->specifications;
    }

    return NULL;
}

CLASP_CALL(size_t)
clasp_reportUnrecognisedFlagsAndOptions(
    clasp_arguments_t const*    args
,   clasp_specification_t const specifications[]
,   clasp_argument_t const**    nextUnrecognisedArg
,   unsigned                    nSkip /* = 0 */
)
{
    size_t  i;
    size_t  n = 0;

    clasp_argument_t const* nextUnrecognisedArg_;

    unsigned flags = 0;

    if (NULL == specifications)
    {
        clasp_arguments_x_t* argsx = clasp_argsx_from_args_(args);

        specifications = (clasp_specification_t const*)argsx->specifications;
    }

    CLASP_ASSERT(NULL != args);
    CLASP_ASSERT(NULL != specifications);

    if (NULL == nextUnrecognisedArg)
    {
        nextUnrecognisedArg = &nextUnrecognisedArg_;
    }

    *nextUnrecognisedArg = NULL;

    for (i = 0; i != args->numFlagsAndOptions; ++i)
    {
        clasp_argument_t const* const       arg     =   &args->flagsAndOptions[i];
        clasp_specification_t const* const  alias   =   clasp_lookup_alias_len_(specifications, arg->resolvedName.ptr, arg->resolvedName.len, flags);

        if (NULL == alias)
        {
            if (0 == nSkip)
            {
                ++n;
                if (NULL == *nextUnrecognisedArg)
                {
                    *nextUnrecognisedArg = arg;
                }
            }
            else
            {
                --nSkip;
            }
        }
    }

    return n;
}

static
size_t clasp_report_unused_arguments_(
    clasp_arguments_t const*    args
,   clasp_argument_t const**    firstUnusedArg
,   unsigned                    nSkip /* = 0 */
,   size_t                      numArguments
,   clasp_argument_t const*     arguments
)
{
    clasp_arguments_x_t*    argsx   =   clasp_argsx_from_args_(args);
    size_t                  n       =   0;
    size_t                  i;
    clasp_argument_t const* firstUnusedArg_;

    CLASP_LOG_PRINTF(&argsx->ctxt, CLASP_SEVIX_DEBUG, CLASP_LITERAL_("clasp_report_unused_arguments_()"));

    if (NULL == firstUnusedArg)
    {
        firstUnusedArg = &firstUnusedArg_;
    }

    *firstUnusedArg = NULL;

    for (i = 0; i != numArguments; ++i)
    {
        if (0 == (CLASP_ARG_F_USED_ & arguments[i].flags))
        {
            if (0 == nSkip)
            {
                ++n;
                if (NULL == *firstUnusedArg)
                {
                    *firstUnusedArg = &arguments[i];
                }
            }
            else
            {
                --nSkip;
            }
        }
    }

    return n;
}

CLASP_CALL(size_t) clasp_reportUnusedFlags(
    clasp_arguments_t const*    args
,   clasp_argument_t const**    firstUnusedArg
,   unsigned                    nSkip /* = 0 */
)
{
    CLASP_ASSERT(NULL != args);

    return clasp_report_unused_arguments_(args, firstUnusedArg, nSkip, args->numFlags, args->flags);
}

CLASP_CALL(size_t) clasp_reportUnusedOptions(
    clasp_arguments_t const*    args
,   clasp_argument_t const**    firstUnusedArg
,   unsigned                    nSkip /* = 0 */
)
{
    CLASP_ASSERT(NULL != args);

    return clasp_report_unused_arguments_(args, firstUnusedArg, nSkip, args->numOptions, args->options);
}

CLASP_CALL(size_t) clasp_reportUnusedFlagsAndOptions(
    clasp_arguments_t const*    args
,   clasp_argument_t const**    firstUnusedArg
,   unsigned                    nSkip /* = 0 */
)
{
    CLASP_ASSERT(NULL != args);

    return clasp_report_unused_arguments_(args, firstUnusedArg, nSkip, args->numFlagsAndOptions, args->flagsAndOptions);
}

CLASP_CALL(size_t) clasp_reportUnusedValues(
    clasp_arguments_t const*    args
,   clasp_argument_t const**    firstUnusedArg
,   unsigned                    nSkip /* = 0 */
)
{
    CLASP_ASSERT(NULL != args);

    return clasp_report_unused_arguments_(args, firstUnusedArg, nSkip, args->numValues, args->values);
}

CLASP_CALL(size_t) clasp_reportUnusedArguments(
    clasp_arguments_t const*    args
,   clasp_argument_t const**    firstUnusedArg
,   unsigned                    nSkip /* = 0 */
)
{
    CLASP_ASSERT(NULL != args);

    return clasp_report_unused_arguments_(args, firstUnusedArg, nSkip, args->numArguments, args->arguments);
}

CLASP_CALL(void) clasp_useArgument(
    clasp_arguments_t const*    args
,   clasp_argument_t const*     usedArg
)
{
    clasp_useArgument_(args, usedArg);
}

int clasp_useArgument_(
    clasp_arguments_t const*    args
,   clasp_argument_t const*     usedArg
)
{
    clasp_arguments_x_t* const  argsx   =   clasp_argsx_from_args_(args);
    size_t                      n;
    clasp_argument_t*           arg;
    int                         wasUsed;

    CLASP_LOG_PRINTF(&argsx->ctxt, CLASP_SEVIX_DEBUG, CLASP_LITERAL_("clasp_useArgument()"));

    CLASP_ASSERT(NULL != args);
    CLASP_ASSERT(NULL != usedArg);

    n = usedArg - &args->arguments[0];

    CLASP_ASSERT(n < args->numArguments);

    if (0 != (CLASP_ARG_F_USED_ & args->arguments[n].flags))
    {
        CLASP_LOG_PRINTF(&argsx->ctxt, CLASP_SEVIX_WARN, CLASP_LITERAL_("argument already used"));
    }

    arg = (clasp_argument_t*)&args->arguments[n];

    wasUsed = 0 != (arg->flags & CLASP_ARG_F_USED_);

    arg->flags |= CLASP_ARG_F_USED_;

    return wasUsed;
}

CLASP_CALL(int)
clasp_argumentIsUsed(
    clasp_arguments_t const*    args
,   clasp_argument_t const*     arg
)
{
    return clasp_argumentIsUsed_(args, arg);
}

int clasp_argumentIsUsed_(
    clasp_arguments_t const*    args
,   clasp_argument_t const*     arg
)
{
    ((void)args);
    CLASP_ASSERT(NULL != args);
    CLASP_ASSERT(NULL != arg);

    return 0 != (arg->flags & CLASP_ARG_F_USED_);
}

CLASP_CALL(int)
clasp_flagIsSpecified(
    clasp_arguments_t const*    args
,   clasp_char_t const*         mappedArgumentName
)
{
    int dummyBitFlags = 0;

    CLASP_ASSERT(NULL != args);
    CLASP_ASSERT(NULL != mappedArgumentName);

    return clasp_checkFlag(args, mappedArgumentName, &dummyBitFlags, 1);
}

CLASP_CALL(int)
clasp_checkFlag(
    clasp_arguments_t const*    args
,   clasp_char_t const*         mappedArgumentName
,   int*                        bitFlags
,   int                         flag
)
{
    CLASP_ASSERT(NULL != args);
    CLASP_ASSERT(NULL != mappedArgumentName);
    CLASP_ASSERT(NULL != bitFlags);

    { size_t i; for (i = 0; i != args->numFlags; ++i)
    {
        clasp_argument_t const* const arg = &args->flags[i];

        if (0 == clasp_strcmp_(mappedArgumentName, arg->resolvedName.ptr))
        {
            *bitFlags |= flag;

            clasp_useArgument(args, arg);

            return 1;
        }
    }}

    return 0;
}

CLASP_CALL(int)
clasp_checkAllFlags(
    clasp_arguments_t const*    args
,   clasp_specification_t const specifications[]
,   int*                        flags
)
{
    int flags_ = 0;

    if (NULL == specifications)
    {
        clasp_arguments_x_t* argsx = clasp_argsx_from_args_(args);

        specifications = (clasp_specification_t const*)argsx->specifications;
    }

    CLASP_ASSERT(NULL != args);
    CLASP_ASSERT(NULL != specifications);

    if (NULL == flags)
    {
        flags = &flags_;
    }

    /* For every argument ... */

    { size_t i; for (i = 0; i != args->numFlags; ++i)
    {
        clasp_argument_t const* const arg = args->flags + i;

        /* ... that is not used ... */

        if (!clasp_argumentIsUsed_(args, arg))
        {
            { size_t j; for (j = 0; CLASP_ARGTYPE_INVALID != specifications[j].type; ++j)
            {
                /* ... see if there is a flag alias ... */

                if (CLASP_ARGTYPE_FLAG == specifications[j].type)
                {
                    /* ... with a corresponding name ... */

                    if (0 == clasp_strcmp_(arg->resolvedName.ptr, specifications[j].mappedArgument))
                    {
                        clasp_useArgument(args, arg);

                        /* ... and a non-0 bitFlags member. */

                        if (0 != specifications[j].bitFlags)
                        {
                            *flags |= specifications[j].bitFlags;

                            break;
                        }
                    }
                }
            }}
        }
    }}

    return *flags;
}

CLASP_CALL(int)
clasp_checkAllMatchingFlags(
    clasp_arguments_t const*    args
,   clasp_specification_t const specifications[]
,   int                         bitMask
,   int*                        flags
)
{
    int flags_ = 0;

    CLASP_ASSERT(NULL != args);
    CLASP_ASSERT(NULL != specifications);

    if (NULL == flags)
    {
        flags = &flags_;
    }

    { size_t i; for (i = 0; i != args->numFlags; ++i)
    {
        clasp_argument_t const* const arg = args->flags + i;

        if (!clasp_argumentIsUsed_(args, arg))
        {
            { size_t j; for (j = 0; CLASP_ARGTYPE_INVALID != specifications[j].type; ++j)
            {
                if (0 != (bitMask & specifications[j].bitFlags))
                {
                    if (0 == clasp_strcmp_(arg->resolvedName.ptr, specifications[j].mappedArgument))
                    {
                        *flags |= specifications[j].bitFlags;

                        clasp_useArgument(args, arg);

                        break;
                    }
                }
            }}
        }
    }}

    return *flags;
}

CLASP_CALL(clasp_argument_t const*)
clasp_findFlagOrOption(
    clasp_arguments_t const*    args
,   clasp_char_t const*         mappedArgumentName
,   unsigned                    nSkip /* = 0 */
)
{
    CLASP_ASSERT(NULL != args);
    CLASP_ASSERT(NULL != mappedArgumentName);

    { size_t i; for (i = 0; i != args->numFlagsAndOptions; ++i)
    {
        clasp_argument_t const* const arg =   args->flagsAndOptions + i;

        if (0 == clasp_strcmp_(arg->resolvedName.ptr, mappedArgumentName))
        {
            if (0 == nSkip--)
            {
                clasp_useArgument(args, arg);

                return arg;
            }
        }
    }}

    return NULL;
}

CLASP_CALL(int)
clasp_checkValue(
    clasp_arguments_t const*    args
,   size_t                      index
,   clasp_char_t const**        pptr
,   size_t*                     plen
,   clasp_argument_t const**    parg
)
{
    CLASP_ASSERT(NULL != args);

    if (index < args->numValues)
    {
        clasp_argument_t const* const arg = &args->values[index];

        if (NULL != pptr)
        {
            *pptr = arg->value.ptr;
        }

        if (NULL != plen)
        {
            *plen = arg->value.len;
        }

        if (NULL != parg)
        {
            *parg = arg;
        }


        /* This is superfluous wrt the current CLASP API functions, but is
         * utterly benign and will be necessary if/when checking of unused
         * values is provided.
         */
        clasp_useArgument(args, arg);

        return 1;
    }

    return 0;
}

/* /////////////////////////////////////////////////////////////////////////
 * output API
 */

CLASP_CALL(size_t)
clasp_countSpecifications(
    clasp_specification_t const specifications[]
)
{
    size_t n = 0;

    if (NULL != specifications)
    {
        for (; CLASP_ARGTYPE_INVALID != specifications->type; ++specifications, ++n)
        {}
    }

    return n;
}

CLASP_CALL(size_t)
clasp_countAliases(
    clasp_specification_t const specifications[]
)
{
    return clasp_countSpecifications(specifications);
}


/* ///////////////////////////// end of file //////////////////////////// */

