/* /////////////////////////////////////////////////////////////////////////
 * File:    src/clasp.usage.FILE.c
 *
 * Purpose: CLASP usage (FILE) facilities.
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

#define CLASP_OBSOLETE

#include "clasp.internal.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 */

#if defined(_MSC_VER) && \
    _MSC_VER >= 1400

# pragma warning(push)
# pragma warning(disable : 4996)
static
clasp_char_t*
clasp_strcat_X_(clasp_char_t* s1, clasp_char_t const* s2)
{
    return clasp_strcat_(s1, s2);
}
# undef clasp_strcat_
# define clasp_strcat_(s1, s2)                              clasp_strcat_X_((s1), (s2))
# pragma warning(pop)
#endif /* _MSC_VER */


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

static
int
clasp_is_valid_specification_type_(clasp_argtype_t t)
{
    switch (t)
    {
    case CLASP_ARGTYPE_FLAG:
    case CLASP_ARGTYPE_OPTION:
    case CLASP_ARGTYPE_VALUE:

        return clasp_true_v;
    default:

        return clasp_false_v;
    }
}

static
size_t
clasp_longOptionName_strlen_(clasp_char_t const* s, unsigned flags)
{
    clasp_char_t const* equals = clasp_strchreq_(s, flags);

    return (NULL == equals) ? clasp_strlen_(s) : (size_t)(equals - s);
}

static size_t clasp_find_matching_primary_(
    clasp_alias_t const     specifications[]
,   size_t                  numSpecifications
,   clasp_alias_t const*    alias
,   unsigned                flags
)
{
    size_t  numberOfMatches     = 0;
    size_t  firstMatchingIndex  = 0;
    size_t  lastMatchingIndex   = 0;

    CLASP_ASSERT(clasp_is_valid_specification_type_(alias->type));

    /* Algorithm:
     *
     * 1. If only matching alias, then primary
     * 2. Use first (non-equal) matching alias with help text and NULL name
     * 3. Use first (non-equal) matching alias with help text
     * 4. Use first matching alias with help text and NULL name
     * 5. Use first matching alias with help text
     * 6. Use first matching alias
     */

    /* 1. If only matching alias, then primary */

    { size_t i; for (i = 0; i != numSpecifications; ++i)
    {
        clasp_alias_t const* alias2 = specifications + i;

        if (clasp_is_valid_specification_type_(alias2->type))
        {
            size_t  lenLong1    =   clasp_longOptionName_strlen_(alias->mappedArgument, flags);
            size_t  lenLong2    =   clasp_longOptionName_strlen_(alias2->mappedArgument, flags);

            if (lenLong1 == lenLong2 &&
                0 == clasp_strncmp_(alias->mappedArgument, alias2->mappedArgument, lenLong1))
            {
                if (1u == ++numberOfMatches)
                {
                    firstMatchingIndex = i;
                }
                lastMatchingIndex = i;
            }
        }
    }}

    CLASP_ASSERT(0u != numberOfMatches);

    if (1u == numberOfMatches)
    {
        return firstMatchingIndex;
    }

    /* 2. Use first (non-equal) matching alias with help text and NULL name */

    { size_t i; for (i = firstMatchingIndex; i <= lastMatchingIndex; ++i)
    {
        clasp_alias_t const* alias2 = specifications + i;

        if (clasp_is_valid_specification_type_(alias2->type))
        {
            size_t  lenLong1    =   clasp_longOptionName_strlen_(alias->mappedArgument, flags);
            size_t  lenLong2    =   clasp_longOptionName_strlen_(alias2->mappedArgument, flags);

            if (lenLong1 == lenLong2 &&
                0 == clasp_strncmp_(alias->mappedArgument, alias2->mappedArgument, lenLong1))
            {
                clasp_char_t const* const equal = clasp_strchreq_(alias2->mappedArgument, flags);

                if (NULL != equal)
                {
                    ;
                }
                else if (   NULL == alias2->help ||
                            '\0' == *alias2->help)
                {
                    ;
                }
                else if (   NULL != alias2->name &&
                            '\0' != *alias2->name)
                {
                    ;
                }
                else
                {
                    return i;
                }
            }
        }
    }}

    /* 3. Use first (non-equal) matching alias with help text */

    { size_t i; for (i = firstMatchingIndex; i <= lastMatchingIndex; ++i)
    {
        clasp_alias_t const* alias2 = specifications + i;

        if (clasp_is_valid_specification_type_(alias2->type))
        {
            size_t  lenLong1    =   clasp_longOptionName_strlen_(alias->mappedArgument, flags);
            size_t  lenLong2    =   clasp_longOptionName_strlen_(alias2->mappedArgument, flags);

            if (lenLong1 == lenLong2 &&
                0 == clasp_strncmp_(alias->mappedArgument, alias2->mappedArgument, lenLong1))
            {
                clasp_char_t const* const equal = clasp_strchreq_(alias2->mappedArgument, flags);

                if (NULL != equal)
                {
                    ;
                }
                else if (   NULL == alias2->help ||
                            '\0' == *alias2->help)
                {
                    ;
                }
                else
                {
                    return i;
                }
            }
        }
    }}

    /* 4. Use first matching alias with help text and NULL name */

    { size_t i; for (i = firstMatchingIndex; i <= lastMatchingIndex; ++i)
    {
        clasp_alias_t const* alias2 = specifications + i;

        if (clasp_is_valid_specification_type_(alias2->type))
        {
            size_t  lenLong1    =   clasp_longOptionName_strlen_(alias->mappedArgument, flags);
            size_t  lenLong2    =   clasp_longOptionName_strlen_(alias2->mappedArgument, flags);

            if (lenLong1 == lenLong2 &&
                0 == clasp_strncmp_(alias->mappedArgument, alias2->mappedArgument, lenLong1))
            {
                if (NULL == alias2->help ||
                    '\0' == *alias2->help)
                {
                    ;
                }
                else if (NULL != alias2->name &&
                        '\0' != *alias2->name)
                {
                    ;
                }
                else
                {
                    return i;
                }
            }
        }
    }}

    /* 5. Use first matching alias with help text */

    { size_t i; for (i = firstMatchingIndex; i <= lastMatchingIndex; ++i)
    {
        clasp_alias_t const* alias2 = specifications + i;

        if (clasp_is_valid_specification_type_(alias2->type))
        {
            size_t  lenLong1    =   clasp_longOptionName_strlen_(alias->mappedArgument, flags);
            size_t  lenLong2    =   clasp_longOptionName_strlen_(alias2->mappedArgument, flags);

            if (lenLong1 == lenLong2 &&
                0 == clasp_strncmp_(alias->mappedArgument, alias2->mappedArgument, lenLong1))
            {
                if (NULL == alias2->help ||
                    '\0' == *alias2->help)
                {
                    ;
                }
                else
                {
                    return i;
                }
            }
        }
    }}

    /* 6. Use first matching alias */

    return firstMatchingIndex;
}

static
void
clasp_show_split_option_help_limit_width_by_FILE_fitting_fragment_(
    FILE*                           stm
,   clasp_char_t const*             fragment
,   size_t                          len
,   int                             TabSize
)
{
    if (TabSize < 1)
    {
    clasp_fprintf_(stm, CLASP_LITERAL_("%*s%.*s\n"), -TabSize * 2, CLASP_LITERAL_(""), (int)len, fragment);
    }
    else
    {
    clasp_fprintf_(stm, CLASP_LITERAL_("\t\t%.*s\n"), (int)len, fragment);
    }
}

static void clasp_show_split_option_help_limit_width_by_FILE_(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_char_t const*                 help
,   FILE*                               stm
,   int                                 width
,   int                                 TabSize
)
{
    size_t const    len             =   clasp_strlen_(help);
    int const       absTabSize      =   abs(TabSize);
    int const       availableWidth  =   width - 2 * absTabSize;

    ((void)ctxt);

    if (width < 1 ||
        (int)len < availableWidth)
    {
        clasp_show_split_option_help_limit_width_by_FILE_fitting_fragment_(stm, help, len, TabSize);
    }
    else
    {
        clasp_char_t const* const   end =   help + len;
        clasp_char_t const*         p0;
        clasp_char_t const*         p1;

        p0 = p1 = help;

        for (; end != p1;)
        {
            if (end - p0 <= availableWidth)
            {
                clasp_show_split_option_help_limit_width_by_FILE_fitting_fragment_(stm, p0, end - p0, TabSize);

                break;
            }
            else
            {
                clasp_char_t const* p;
                clasp_char_t const* sl = end;

                /* find last space within length, or the first one after */
                for (p = p0; end != p; ++p)
                {
                    if (p - p0 >= availableWidth)
                    {
                        if (end != sl)
                        {
                            break;
                        }
                    }

                    if (isspace(*p))
                    {
                        sl = p;
                    }
                }

                p1 = sl;

                if (end == p1)
                {
                    clasp_show_split_option_help_limit_width_by_FILE_fitting_fragment_(stm, p0, end - p0, TabSize);

                    break;
                }
                else
                {
                    clasp_show_split_option_help_limit_width_by_FILE_fitting_fragment_(stm, p0, p1 - p0, TabSize);

                    for (; p1 != end; ++p1)
                    {
                        if (!isspace(*p1))
                        {
                            break;
                        }
                    }
                    p0 = p1;
                }
            }
        }
    }
}


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

CLASP_CALL(void)
clasp_showVersionByFILE(
    clasp_arguments_t const*    args
,   clasp_usageinfo_t const*    info
,   clasp_alias_t const         specifications[]
)
{
    clasp_show_version_by_FILE(
        (NULL != args) ? clasp_diagnostic_context_from_args_(args) : NULL
    ,   info
    ,   specifications
    );
}

CLASP_CALL(void)
clasp_show_version_by_FILE(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_usageinfo_t const*            info
,   clasp_alias_t const                 specifications[]
)
{
    FILE*                 stm         =   (FILE*)info->param;
    clasp_char_t          fmt[]       =   CLASP_LITERAL_("%s%s%d.%d.%d.%d\n");
    clasp_char_t const*   tool_name;
    clasp_char_t const*   v_prefix;

    if (NULL == info->toolName)
    {
        tool_name =   CLASP_LITERAL_("");
        v_prefix  =   CLASP_LITERAL_("");
    }
    else
    {
        tool_name =   info->toolName;
        v_prefix  =   CLASP_LITERAL_(" version ");
    }

    if (info->version.revision < 0)
    {
        CLASP_ASSERT('.' == fmt[6]);
        CLASP_ASSERT('.' == fmt[9]);

        fmt[ 9] = '\n';
        fmt[10] = '\0';
    }
    else
    if (info->version.build < 0)
    {
        CLASP_ASSERT('.' == fmt[ 9]);
        CLASP_ASSERT('.' == fmt[12]);

        fmt[12] = '\n';
        fmt[13] = '\0';
    }

    ((void)specifications);
    ((void)ctxt);

    clasp_fprintf_(stm, fmt, tool_name, v_prefix, info->version.major, info->version.minor, info->version.revision, info->version.build);
}


CLASP_CALL(void)
clasp_showHeaderByFILE(
    clasp_arguments_t const*    args
,   clasp_usageinfo_t const*    info
,   clasp_alias_t const         specifications[]
)
{
    clasp_show_header_by_FILE(
        (NULL != args) ? clasp_diagnostic_context_from_args_(args) : NULL
    ,   info
    ,   specifications
    );
}

CLASP_CALL(void)
clasp_show_header_by_FILE(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_usageinfo_t const*            info
,   clasp_alias_t const                 specifications[]
)
{
    FILE*                       stm     =   (FILE*)info->param;
    clasp_diagnostic_context_t  ctxt_;
    int                         r;

    CLASP_ASSERT(NULL != info->usage);

    ctxt = clasp_verify_context_(ctxt, &ctxt_, &r);
    if (NULL == ctxt)
    {
        return;
    }

    if (NULL != info->summary &&
        '\0' != info->summary[0])
    {
        clasp_fprintf_(stm, CLASP_LITERAL_("%s\n"), info->summary);
    }
    /* clasp_fprintf_(stm, CLASP_LITERAL_("\n")); */

    clasp_show_version_by_FILE(ctxt, info, specifications);

    if (NULL != info->copyright &&
        '\0' != info->copyright[0])
    {
        /* clasp_fprintf_(stm, CLASP_LITERAL_("\n")); */
    clasp_fprintf_(stm, CLASP_LITERAL_("%s\n"), info->copyright);
    }
    if (NULL != info->description &&
        '\0' != info->description[0])
    {
        /* clasp_fprintf_(stm, CLASP_LITERAL_("\n")); */
    clasp_fprintf_(stm, CLASP_LITERAL_("%s\n"), info->description);
    }

    clasp_fprintf_(stm, CLASP_LITERAL_("\n"));
    clasp_fprintf_(stm, CLASP_LITERAL_("%s\n"), info->usage);
    clasp_fprintf_(stm, CLASP_LITERAL_("\n"));
}

CLASP_CALL(void)
clasp_showBodyByFILE(
    clasp_arguments_t const*    args
,   clasp_usageinfo_t const*    info
,   clasp_alias_t const         specifications[]
)
{
    clasp_show_body_by_FILE(
        (NULL != args) ? clasp_diagnostic_context_from_args_(args) : NULL
    ,   info
    ,   specifications
    );
}

CLASP_CALL(void)
clasp_show_body_by_FILE(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_usageinfo_t const*            info
,   clasp_alias_t const                 specifications[]
)
{
    FILE*                       stm                 =   (FILE*)info->param;
    const size_t                numSpecifications   =   clasp_countSpecifications(specifications);
    clasp_diagnostic_context_t  ctxt_;
    int                         r;
    size_t                      numFlags            =   (size_t)~0;
    size_t                      numOptions          =   (size_t)~0;

    unsigned const              flags               =   0;

    /* Prefixing. Either:
     *
     * - single TAB:  equiv "\t"
     * - n-spaces:    equiv "%.*s", (int)n, ""
     */

    clasp_char_t const* const   prefixPtr   =   (info->assumedTabWidth < 1) ? CLASP_LITERAL_STRING("") : CLASP_LITERAL_STRING("\t");
    size_t const                prefixLen   =   (info->assumedTabWidth < 1) ? (size_t)(-info->assumedTabWidth) : 1u;


    ctxt = clasp_verify_context_(ctxt, &ctxt_, &r);
    if (NULL == ctxt)
    {
        return;
    }

    if (NULL != specifications)
    {
        clasp_count_flags_and_options_(specifications, &numFlags, &numOptions);
    }
    else
    {
        numFlags = 0;
        numOptions = 0;
    }

    if (0 == numFlags)
    {
        if (0 == numOptions)
        {
            return;
        }
        else
        {
            clasp_fprintf_(stm, CLASP_LITERAL_("Options:\n"));
        }
    }
    else
    {
        if (0 == numOptions)
        {
            clasp_fprintf_(stm, CLASP_LITERAL_("Flags:\n"));
        }
        else
        {
            clasp_fprintf_(stm, CLASP_LITERAL_("Flags and options:\n"));
        }
    }

    clasp_fprintf_(stm, CLASP_LITERAL_("\n"));

    { size_t i; for (i = 0; i != numSpecifications; ++i)
    {
        clasp_alias_t const* alias = specifications + i;

        if (CLASP_ARGTYPE_TACIT_ == alias->type)
        {
            break;
        }
        else
        if (CLASP_ARGTYPE_GAP_ == alias->type)
        {
            if (0 != i)
            {
    clasp_fprintf_(stm, CLASP_LITERAL_("\n"));
            }

            if (NULL != alias->help &&
                '\0' != alias->help[0])
            {
    clasp_fprintf_(stm, CLASP_LITERAL_("%*s%s\n"), (int)prefixLen, prefixPtr, alias->help);
    clasp_fprintf_(stm, CLASP_LITERAL_("\n"));
            }

            continue;
        }
        else
        {
            size_t const    primaryIndex    =   clasp_find_matching_primary_(specifications, numSpecifications, alias, flags);

            clasp_char_t const* const   equals      =   (NULL == alias->mappedArgument) ? NULL : clasp_strchreq_(alias->mappedArgument, flags);
            size_t const                maLen       =   (NULL == alias->mappedArgument) ? 0u : (NULL == equals) ? clasp_strlen_(alias->mappedArgument) : (size_t)(equals - alias->mappedArgument);
            clasp_char_t const* const   defValue    =   (NULL != equals) ? (equals + 1) : NULL;
            size_t const                defValLen   =   (NULL == defValue) ? 0u : clasp_strlen_(defValue);

            /* So as to avoid allocating memory, or maintaining
             * complex relationships between what is an alias and
             * what is the 'primary' argument, we process each
             * item by identifying its corresponding primary (which
             * may be itself).
             *
             * once the primary is identified, search all elements
             * including this one and display any matching specifications
             *
             * then display this primary
             */

            if (primaryIndex != i)
            {
                continue;
            }

            /* If we're here, then we've found the primary.
             *
             * We do two things:
             * - display any *other* specifications
             * - display the primary option details
             */
            { size_t j; for (j = 0; j != numSpecifications; ++j)
            {
                clasp_alias_t const* alias2 = specifications + j;

                if (j != i)
                {
                    if (NULL != alias->mappedArgument &&
                        NULL != alias2->mappedArgument)
                    {
                        size_t  lenLong1    =   clasp_longOptionName_strlen_(alias->mappedArgument, flags);
                        size_t  lenLong2    =   clasp_longOptionName_strlen_(alias2->mappedArgument, flags);

                        if (lenLong1 == lenLong2 &&
                            0 == clasp_strncmp_(alias->mappedArgument, alias2->mappedArgument, lenLong1))
                        {
                            if (NULL != alias2->name &&
                                '\0' != *alias2->name)
                            {
                                clasp_char_t const* const equal = clasp_strchreq_(alias2->mappedArgument, flags);

                                if (NULL != equal)
                                {
    clasp_fprintf_(stm, CLASP_LITERAL_("%*s%s => %s\n"), (int)prefixLen, prefixPtr, alias2->name, alias2->mappedArgument);
                                }
                                else
                                {
                                    if (CLASP_ARGTYPE_OPTION == alias->type)
                                    {
    clasp_fprintf_(stm, CLASP_LITERAL_("%*s%s <value>\n"), (int)prefixLen, prefixPtr, alias2->name);
                                    }
                                    else
                                    {
    clasp_fprintf_(stm, CLASP_LITERAL_("%*s%s\n"), (int)prefixLen, prefixPtr, alias2->name);
                                    }
                                }
                            }
                        }
                    }
                }
            }}

            if (NULL != alias->name &&
                '\0' != *alias->name)
            {
                size_t  lenShort    =   clasp_longOptionName_strlen_(alias->name, flags);
                size_t  lenLong     =   clasp_longOptionName_strlen_(alias->mappedArgument, flags);

                if (lenShort != lenLong ||
                    0 != clasp_strncmp_(alias->name, alias->mappedArgument, lenLong))
                {
    clasp_fprintf_(stm, CLASP_LITERAL_("%*s%s%s\n"), (int)prefixLen, prefixPtr, alias->name, (alias->type == CLASP_ARGTYPE_OPTION) ? CLASP_LITERAL_(" <value>") : CLASP_LITERAL_(""));
                }
            }
            if ((alias->type == CLASP_ARGTYPE_OPTION) &&
                NULL != alias->valueSet &&
                '\0' != *alias->valueSet)
            {
                clasp_char_t* valueSet = clasp_strdup_raw_(1 + alias->valueSet);

                if (NULL == valueSet)
                {
                    goto print_plain;
                }
                else
                {
                    const size_t    len     =   clasp_strlen_(valueSet);
                    clasp_char_t*   buff    =   (clasp_char_t*)malloc(sizeof(clasp_char_t) * (1 + len + 2));
                    if (NULL == buff)
                    {
                        free(valueSet);

                        goto print_plain;
                    }
                    else
                    {
                        static const clasp_char_t bracePairs[][3] =
                        {
                            /* "{}",   "[]",   "<>",   "()",   "  " */
                            { '{', '}', '\0' },
                            { '[', ']', '\0' },
                            { '<', '>', '\0' },
                            { '(', ')', '\0' },
                            { ' ', ' ', '\0' },
                        };

                        clasp_char_t        delim[2];
                        clasp_char_t        braces[3];
                        clasp_char_t*       tok;
                        struct
                        strtok_savectxt_t   sc;
                        const int           allowOthers =   (alias->valueSet[0] == valueSet[len - 1]);
                        size_t              braceIndex  =   0;

                        delim[0]    =   alias->valueSet[0];
                        delim[1]    =   '\0';

                        braces[0]   =   bracePairs[braceIndex][0];
                        braces[1]   =   bracePairs[braceIndex][1];
                        braces[2]   =   '\0';

                        buff[0] = ' ';
                        buff[1] = '\0';

                        for (tok = clasp_strtok_wblank_r_(valueSet, delim, &sc); NULL != tok; tok = clasp_strtok_wblank_r_(NULL, delim, &sc))
                        {
                            clasp_strcat_(buff, tok);
                            clasp_strcat_(buff, delim);

                            while ( NULL != clasp_strpbrk_(tok, braces) &&
                                    ++braceIndex < (sizeof(bracePairs) / sizeof(bracePairs[0])))
                            {
                                braces[0]   =   bracePairs[braceIndex][0];
                                braces[1]   =   bracePairs[braceIndex][1];
                            }
                        }
                        buff[0] = braces[0];
                        buff[len + 1] = braces[1];
                        buff[len + 2] = '\0';

    clasp_fprintf_(
      stm
                       /* PPPmmmmVV           bbOO                DD*/
    , CLASP_LITERAL_("%*s%.*s%s as one of %s%s%s%s\n")
    , (int)prefixLen, prefixPtr
    , (int)maLen, alias->mappedArgument
    , (alias->type == CLASP_ARGTYPE_OPTION)
        ? CLASP_LITERAL_("=<value>")
        : CLASP_LITERAL_("")
    , buff
    , allowOthers
        ? CLASP_LITERAL_(" or any other value")
        : CLASP_LITERAL_("")
    , (defValLen != 0)
        ? CLASP_LITERAL_("; default value=")
        : CLASP_LITERAL_("")
    , (defValLen != 0)
        ? defValue
        : CLASP_LITERAL_("")
    );

                        free(buff);
                        free(valueSet);
                    }
                }
            }
            else
            {
print_plain:
    clasp_fprintf_(stm, CLASP_LITERAL_("%*s%.*s%s\n"), (int)prefixLen, prefixPtr, (int)maLen, alias->mappedArgument, (alias->type == CLASP_ARGTYPE_OPTION) ? CLASP_LITERAL_("=<value>") : CLASP_LITERAL_(""));
            }
            if (NULL != alias->help)
            {
    clasp_show_split_option_help_limit_width_by_FILE_(ctxt, alias->help, stm, info->width, info->assumedTabWidth);
            }
            { int l; for (l = 0; l != info->blanksBetweenItems; ++l)
            {
    clasp_fprintf_(stm, CLASP_LITERAL_("\n"));
            }}
        }
    }}
}


/* ///////////////////////////// end of file //////////////////////////// */

