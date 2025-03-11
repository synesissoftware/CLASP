/* /////////////////////////////////////////////////////////////////////////
 * File:    src/clasp.usage.c
 *
 * Purpose: CLASP usage facilities.
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

#include <ctype.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

#define CLASP_MAX_SPECIFICATIONS_                           (511)

static clasp_char_t const               s_unknownIdentifier[] = { '@', 'u', 'n', 'k', 'n', 'o', 'w', 'n', '-', 'i', 'd', 'e', 'n', 't', 'i', 'f', 'i', 'e', 'r', '@', '\0' };


/* /////////////////////////////////////////////////////////////////////////
 * external declarations
 */

#if defined(WIN32) || \
    defined(WIN64)

# if 0 || \
     defined(__i386__) || \
     defined(__i386) || \
     defined(_X86_) || \
     defined(_M_IX86) || \
     0

#  define CLASP_INTERNAL_STDCALL                            __stdcall
# else

#  define CLASP_INTERNAL_STDCALL
# endif


extern
long
CLASP_INTERNAL_STDCALL
GetLastError(void);

extern
void
CLASP_INTERNAL_STDCALL
SetLastError(
    long e
);

extern
void*
CLASP_INTERNAL_STDCALL
GetModuleHandleA(
    char const* lpModuleName
);

extern
void*
CLASP_INTERNAL_STDCALL
GetModuleHandleW(
    wchar_t const* lpModuleName
);

# ifdef CLASP_USE_WIDE_STRINGS
extern
int
CLASP_INTERNAL_STDCALL
LoadStringW(
    void*           hInstance
,   unsigned int    uID
,   wchar_t*        lpBuffer
,   int             cchBufferMax
);
#  define clasp_ext_LoadString                              LoadStringW
# else /* ? CLASP_USE_WIDE_STRINGS */
extern
int
CLASP_INTERNAL_STDCALL
LoadStringA(
    void*           hInstance
,   unsigned int    uID
,   char*           lpBuffer
,   int             cchBufferMax
);
#  define clasp_ext_LoadString                              LoadStringA
# endif /* CLASP_USE_WIDE_STRINGS */
#endif /* WIN32 || WIN64 */


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

/* Obtains the file basename from the given path, taking into account the
 * rightmost path-name separator character.
 *
 * \note: On UNIX, this just searches for the rightmost '/'; on Windows the
 *  rightmost '\\' is also considered.
 */
static
clasp_char_t const*
clasp_executable_name_from_path_(
    clasp_char_t const* path
)
{
    clasp_char_t const* last_slash = clasp_strrchr_(path, '/');
#ifdef _WIN32
    clasp_char_t const* last_bslash = clasp_strrchr_(path, '\\');

    if (NULL == last_slash || (NULL != last_bslash && last_slash < last_bslash))
    {
        last_slash = last_bslash;
    }
#endif
    if (NULL == last_slash)
    {
        return path;
    }
    else
    {
        return last_slash + 1;
    }
}

static
long
clasp_find_id_(
    clasp_char_t const* p
)
{
    clasp_char_t*   endptr = NULL;
    long            r;

#ifdef CLASP_USE_WIDE_STRINGS

    r =  wcstol(p, &endptr, 0);
#else /* ? CLASP_USE_WIDE_STRINGS */

    r =  strtol(p, &endptr, 0);
#endif /* CLASP_USE_WIDE_STRINGS */

    CLASP_ASSERT(NULL != endptr);

    if ('@' != *endptr)
    {
        return 0;
    }
    else
    {
        return r;
    }
}

static
int
clasp_find_replacement_usage_field_(
    clasp_usageinfo_t*      usageinfo
,   clasp_char_t const***   ppp
,   int*                    isNumber
)
{
    clasp_char_t const**    fields[5];
    size_t const            n = CLASP_NUM_ELEMENTS_(fields);
    size_t                  i;

    fields[0] = &usageinfo->toolName;
    fields[1] = &usageinfo->summary;
    fields[2] = &usageinfo->copyright;
    fields[3] = &usageinfo->description;
    fields[4] = &usageinfo->usage;

    CLASP_ASSERT(NULL != ppp);
    CLASP_ASSERT(NULL != isNumber);

    *isNumber = 0;

    for (i = 0; i != n; ++i)
    {
        if (NULL == *fields[i])
        {
            continue;
        }
        else
        if (s_unknownIdentifier == *fields[i])
        {
            continue;
        }
        else
        {
            size_t const len = clasp_strlen_(*fields[i]);

            if (len > 2 &&
                '@' == (*fields[i])[0] &&
                '@' == (*fields[i])[len - 1])
            {
                *ppp = fields[i];

                switch ((*fields[i])[1])
                {
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    *isNumber = 0 != clasp_find_id_((*fields[i]) + 1);

                /* fall through */
                default:
                    return 1;
                }
            }
        }
    }

    return 0;
}

static
int
clasp_replace_field_from_resource_(
    clasp_char_t const*     argv0
,   clasp_char_t const**    pp
,   clasp_char_t*           buff
,   size_t                  cchBuff
)
{
#if defined(WIN32) || \
    defined(WIN64)

# ifdef CLASP_USE_WIDE_STRINGS

    void* const     hinst   =   GetModuleHandleW(argv0);
# else /* ? CLASP_USE_WIDE_STRINGS */

    void* const     hinst   =   GetModuleHandleA(argv0);
# endif /* CLASP_USE_WIDE_STRINGS */
    long const      id      =   clasp_find_id_(*pp + 1);
    size_t const    n       =   (SetLastError(0), clasp_ext_LoadString(hinst, id, buff, (int)cchBuff));
    long const      e       =   GetLastError();

    if (0 == e &&
        0 != n)
    {
        buff[n] = '\0';

        *pp = buff;

        return 1;
    }
#else

    ((void)argv0);
    ((void)pp);
    ((void)buff);
    ((void)cchBuff);
#endif

    return 0;
}

static
int
clasp_find_replacement_mappedArgument_(
    clasp_alias_t*          specifications
,   clasp_char_t const***   ppp
,   int*                    isNumber
)
{
    CLASP_ASSERT(NULL != ppp);
    CLASP_ASSERT(NULL != isNumber);

    *isNumber = 0;

    for (; CLASP_ARGTYPE_INVALID != specifications->type; ++specifications)
    {
        if (CLASP_ARGTYPE_FLAG != specifications->type &&
            CLASP_ARGTYPE_OPTION != specifications->type)
        {
            continue;
        }
        else
        if (NULL == specifications->help)
        {
            continue;
        }
        else
        if (s_unknownIdentifier == specifications->help)
        {
            continue;
        }
        else
        {
            size_t const len = clasp_strlen_(specifications->help);

            if (len > 2 &&
                '@' == specifications->help[0] &&
                '@' == specifications->help[len - 1])
            {
                *ppp = &specifications->help;

                switch (specifications->help[1])
                {
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    *isNumber = 0 != clasp_find_id_(specifications->help + 1);

                /* fall through */
                default:
                    return 1;
                }
            }
        }
    }

    return 0;
}

/* Examines the usage string as to whether it contains a tool-name
 * replacement - such as ':toolName:', ':program_name:', ... - and, if so,
 * writes the index and length into the variables provided in the given
 * pointers.
 *
 * \param usage The usage string. May not be NULL;
 * \param ix_start Pointer of a variable into which to write the index, if
 *  a replacement is found. 0 is written if not found. May not be NULL;
 * \param len Pointer of a variable into which to write the length, if a
 *  replacement is found. 0 is written if not found. May not be NULL;
 */
static
int
clasp_usage_has_replacement_toolName_(
    clasp_char_t const*     usage
,   size_t*                 ix_start
,   size_t*                 len
)
{
    CLASP_ASSERT(usage);
    CLASP_ASSERT(ix_start);
    CLASP_ASSERT(len);

    *ix_start = 0;
    *len = 0;

    {
        clasp_char_t const* const s_tags[] =
        {
            ":toolName:",
            ":toolname:",
            ":program_name:",
            ":program:",
            NULL
        };

        clasp_char_t* p = NULL;

        { size_t i; for (i = 0; NULL == p && NULL != s_tags[i]; ++i)
        {
            clasp_char_t const* const   tag     =   s_tags[i];
            size_t const                tag_len =   clasp_strlen_(tag);

            if (NULL != (p = clasp_strstr_(usage, tag)))
            {
                *ix_start = (size_t)(p - usage);
                *len = tag_len;
            }
        }}

        return NULL != p;
    }
}

static
int
clasp_invoke_header_expand_usage_(
    void                      (*pfnHeader)(clasp_arguments_t const*, clasp_usageinfo_t const* , clasp_alias_t const* )
,   clasp_arguments_t const*    args
,   clasp_usageinfo_t const*    usageinfo
,   clasp_alias_t const*        specifications
)
{
    clasp_char_t        usage1_[2000];
    clasp_char_t        usage2_[CLASP_NUM_ELEMENTS_(usage1_)];

    size_t const        CCH_USAGE   =   CLASP_NUM_ELEMENTS_(usage1_);

    clasp_char_t const  prefixChar  =   (usageinfo->assumedTabWidth < 1) ? ' ' : '\t';
    size_t const        prefixLen   =   (usageinfo->assumedTabWidth < 1) ? (size_t)(-usageinfo->assumedTabWidth) : 1u;

    clasp_usageinfo_t   usageinfo_  =   *usageinfo;
    clasp_char_t const* usage       =   usageinfo_.usage;

    if (NULL != usage &&
        '\0' != usage[0] &&
        ispunct(usage[0]) &&
        '@' != usage[0] &&
        '\0' != usage[1])
    {
        /* usage is specified, begins with a punctuation character, and has length >= 2 */

        clasp_char_t const          sep =   usage++[0]; /* NOTE: moved past usage[0] */
        size_t const                le_ =   clasp_strlen_(usage);
        clasp_char_t const* const   l_s =   clasp_strnexrchr_(usage, le_, sep);

        if (NULL == l_s)
        {
            /* no other (non-separator) characters present, so print as is */

            goto invoke;
        }
        else
        {
            size_t const    len =   (NULL != l_s) ? (size_t)((l_s + 1) - usage) : le_;
            size_t const    n_x =   clasp_strncount_(usage, len, sep);

            if (len >= CCH_USAGE)
            {
                /* input too large */

                goto invoke;
            }

            /* prepare tokenisable buffer (and strip any trailing separators) */

            memcpy(usage2_, usage, len * sizeof(clasp_char_t));
            usage2_[len] = '\0';
            usage = usage2_;

            if (0 == n_x)
            {
                /* no embedded separators, so as is */

                goto invoke;
            }
            else
            {
                /* calculate whether we have space for string when replacing separators with LF + WS*N */

                size_t const    req =   len + (n_x * prefixLen);
                size_t const    s_w =   (req < CCH_USAGE) ? prefixLen : 0;

                /* now process the usage as a sequence of tokens */
                clasp_char_t        seps[2];
                struct
                strtok_savectxt_t   sc;
                clasp_char_t*       tok =   (seps[0] = sep, seps[1] = '\0', clasp_strtok_wblank_r_(usage2_, seps, &sc));
                clasp_char_t*       p0  =   usage1_;

                for (; NULL != tok; )
                {
                    size_t const tl = clasp_strlen_(tok);

                    if (0 != tl)
                    {
                        if (usage2_ != tok)
                        {
                            memset(p0, prefixChar, s_w);
                            p0 += s_w;
                        }

                        memcpy(p0, tok, tl * sizeof(clasp_char_t));
                        p0 += tl;
                    }

                    tok = clasp_strtok_wblank_r_(NULL, seps, &sc);

                    if (NULL != tok)
                    {
                        *p0++ = '\n';
                    }
                }
                CLASP_ASSERT(p0 < &usage1_[CCH_USAGE]);
                *p0 = 0;

                usageinfo_.usage    =   usage1_;
                usageinfo           =   &usageinfo_;

                goto invoke;
            }
        }
    }

invoke:

    (*pfnHeader)(args, usageinfo, specifications);

    return 0;
}

static
int
clasp_invoke_header_new_(
    void                      (*pfnHeader)(clasp_arguments_t const*, clasp_usageinfo_t const* , clasp_alias_t const* )
,   clasp_arguments_t const*    args
,   clasp_usageinfo_t const*    usageinfo
,   clasp_alias_t const*        specifications
)
{
    size_t  ix_start;
    size_t  len;

    if (NULL == specifications)
    {
        specifications = clasp_getSpecifications(args);
    }

    if (NULL == usageinfo->toolName)
    {
        clasp_usageinfo_t usageinfo_ = *usageinfo;

        if (args->argc > 0)
        {
            usageinfo_.toolName = clasp_executable_name_from_path_(args->argv[0]);

            return clasp_invoke_header_new_(pfnHeader, args, &usageinfo_, specifications);
        }
    }

    if (NULL == usageinfo->usage)
    {
        clasp_char_t const* const   s_usages[4] =
        {
                ":program: <arg1> [ ... <argN> ]"
            ,   ":program: [ ... flags ... ] <arg1> [ ... <argN> ]"
            ,   ":program: [ ... options ... ] <arg1> [ ... <argN> ]"
            ,   ":program: [ ... flags/options ... ] <arg1> [ ... <argN> ]"
        };
        clasp_char_t const* usage;
        size_t              index;

        clasp_usageinfo_t   usageinfo_ = *usageinfo;

        size_t  numFlags    =   (size_t)~0;
        size_t  numOptions  =   (size_t)~0;

        if (NULL != specifications)
        {
            clasp_count_flags_and_options_(specifications, &numFlags, &numOptions);
        }

        index = 1 * (0 != numFlags) + 2 * (0 != numOptions);

        usage = s_usages[index];

        usageinfo_.usage = usage;

        return clasp_invoke_header_new_(pfnHeader, args, &usageinfo_, specifications);
    }

    if (0 != clasp_usage_has_replacement_toolName_(usageinfo->usage, &ix_start, &len))
    {
        clasp_char_t    buff_[1001] = "";

        size_t const    usage_len_0     =   clasp_strlen_(usageinfo->usage);
        size_t const    toolName_len    =   clasp_strlen_(usageinfo->toolName);

        size_t const    n_lhs           =   ix_start;
        size_t const    n_mid           =   toolName_len;
        size_t const    n_rhs           =   usage_len_0 - (ix_start + len);

        size_t const    CCH_REQUIRED    =   (usage_len_0 - len) + toolName_len;

        clasp_usageinfo_t usageinfo_ = *usageinfo;

        if (CCH_REQUIRED > CLASP_NUM_ELEMENTS_(buff_))
        {
            usageinfo_.usage = CLASP_LITERAL_STRING("INVALID USAGE: TOO MANY RESULTING CHARACTERS!");
        }
        else
        {
            memcpy(&buff_[0] + 0                        , usageinfo->usage                  , sizeof(clasp_char_t) * n_lhs);
            memcpy(&buff_[0] + ix_start                 , usageinfo->toolName               , sizeof(clasp_char_t) * n_mid);
            memcpy(&buff_[0] + ix_start + toolName_len  , usageinfo->usage + ix_start + len , sizeof(clasp_char_t) * n_rhs);

            usageinfo_.usage = buff_;
        }

        return clasp_invoke_header_new_(pfnHeader, args, &usageinfo_, specifications);
    }

    {
        clasp_usageinfo_t       usageInfo_  =   *usageinfo;
        int                     isNumber;
        clasp_char_t const**    pp;

        if (clasp_find_replacement_usage_field_(&usageInfo_, &pp, &isNumber))
        {
            clasp_char_t buff[4096];

            CLASP_ASSERT(NULL != pp);

            if (!isNumber)
            {
                *pp = s_unknownIdentifier;
            }
            else
            if (!clasp_replace_field_from_resource_(args->argv[0], pp, buff, CLASP_NUM_ELEMENTS_(buff)))
            {
                *pp = s_unknownIdentifier;
            }

            return clasp_invoke_header_new_(pfnHeader, args, &usageInfo_, specifications);
        }

        return clasp_invoke_header_expand_usage_(pfnHeader, args, usageinfo, specifications);
    }
}

static
int
clasp_invoke_body_new_(
    void                      (*pfnBody)(clasp_arguments_t const*, clasp_usageinfo_t const* , clasp_alias_t const* )
,   clasp_arguments_t const*    args
,   clasp_usageinfo_t const*    usageinfo
,   clasp_alias_t const*        specifications
)
{
    CLASP_ASSERT(NULL != pfnBody);
    CLASP_ASSERT(NULL != args);
    CLASP_ASSERT(NULL != usageinfo);


    if (NULL == specifications)
    {
        specifications = clasp_getSpecifications(args);
    }

    {
        clasp_alias_t   specifications_[CLASP_MAX_SPECIFICATIONS_ + 1];
        size_t const    n = clasp_countSpecifications(specifications);

        if (0 != n &&
            n <= CLASP_MAX_SPECIFICATIONS_)
        {
            int                     isNumber;
            clasp_char_t const**    pp;

            CLASP_ASSERT(NULL != specifications);

            memcpy(specifications_, specifications, sizeof(clasp_alias_t) * (1 + n));

            if (clasp_find_replacement_mappedArgument_(&specifications_[0], &pp, &isNumber))
            {
                clasp_char_t buff[4096];

                CLASP_ASSERT(NULL != pp);

                if (!isNumber)
                {
                    *pp = s_unknownIdentifier;
                }
                else
                if (!clasp_replace_field_from_resource_(args->argv[0], pp, buff, CLASP_NUM_ELEMENTS_(buff)))
                {
                    *pp = s_unknownIdentifier;
                }

                return clasp_invoke_body_new_(pfnBody, args, usageinfo, &specifications_[0]);
            }
        }

        (*pfnBody)(args, usageinfo, specifications);

        return 0;
    }
}

static
int
clasp_invoke_version_new_(
    void                      (*pfnVersion)(clasp_arguments_t const*, clasp_usageinfo_t const* , clasp_alias_t const* )
,   clasp_arguments_t const*    args
,   clasp_usageinfo_t const*    usageinfo
,   clasp_alias_t const*        specifications
)
{
    CLASP_ASSERT(NULL != pfnVersion);
    CLASP_ASSERT(NULL != args);

    if (NULL == usageinfo->toolName)
    {
        clasp_usageinfo_t usageinfo_ = *usageinfo;

        if (args->argc > 0)
        {
            usageinfo_.toolName = clasp_executable_name_from_path_(args->argv[0]);

            return clasp_invoke_version_new_(pfnVersion, args, &usageinfo_, specifications);
        }
    }

    {
        clasp_usageinfo_t       usageInfo_  =   *usageinfo;
        int                     isNumber;
        clasp_char_t const**    pp;

        if (clasp_find_replacement_usage_field_(&usageInfo_, &pp, &isNumber))
        {
            clasp_char_t buff[4096];

            CLASP_ASSERT(NULL != pp);

            if (!isNumber)
            {
                *pp = s_unknownIdentifier;
            }
            else
            if (!clasp_replace_field_from_resource_(args->argv[0], pp, buff, CLASP_NUM_ELEMENTS_(buff)))
            {
                *pp = s_unknownIdentifier;
            }

            return clasp_invoke_version_new_(pfnVersion, args, &usageInfo_, specifications);
        }

        (*pfnVersion)(args, usageinfo, specifications);

        return 0;
    }
}

static
int
clasp_invoke_usage_new_(
    void                      (*pfnHeader)(clasp_arguments_t const*, clasp_usageinfo_t const* , clasp_alias_t const* )
,   void                      (*pfnBody)(clasp_arguments_t const*, clasp_usageinfo_t const* , clasp_alias_t const* )
,   clasp_arguments_t const*    args
,   clasp_usageinfo_t const*    usageinfo
,   clasp_alias_t const*        specifications
)
{

    {
        clasp_invoke_header_new_(pfnHeader, args, usageinfo, specifications);

        clasp_invoke_body_new_(pfnBody, args, usageinfo, specifications);

        return 0;
    }
}


/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

CLASP_CALL(int)
clasp_showUsage(
    clasp_arguments_t const*    args
,   clasp_alias_t const*        specifications
,   clasp_char_t const*         toolName    /* "rcp" */
,   clasp_char_t const*         summary     /* "SystemTools (http://systemtools.sourceforge.net/)" */
,   clasp_char_t const*         copyright   /* "Copyright (c) XXXX. All rights reserved" */
,   clasp_char_t const*         description /* "Recursively copies files" */
,   clasp_char_t const*         usage       /* ":program: [ ... options ... ] <src-spec> <dest-spec>" */
,   int                         major
,   int                         minor
,   int                         revision
,   void                      (*pfnHeader)(clasp_arguments_t const*, clasp_usageinfo_t const* , clasp_alias_t const* )
,   void                      (*pfnBody)(clasp_arguments_t const*, clasp_usageinfo_t const* , clasp_alias_t const* )
,   void*                       param
,   int                         flags
,   int                         consoleWidth
,   int                         tabSize
,   int                         blanksBetweenItems
)
{
    clasp_usageinfo_t usageinfo;


    CLASP_ASSERT(NULL != args);
    CLASP_ASSERT(NULL != pfnHeader);
    CLASP_ASSERT(NULL != pfnBody);

    usageinfo.version.major         =   major;
    usageinfo.version.minor         =   minor;
    usageinfo.version.revision      =   revision;
    usageinfo.version.build         =   0;
    usageinfo.toolName              =   toolName;
    usageinfo.summary               =   summary;
    usageinfo.copyright             =   copyright;
    usageinfo.description           =   description;
    usageinfo.usage                 =   usage;
    usageinfo.flags                 =   flags;
    usageinfo.param                 =   param;
    usageinfo.width                 =   consoleWidth;
    usageinfo.assumedTabWidth       =   tabSize;
    usageinfo.blanksBetweenItems    =   blanksBetweenItems;

    return clasp_invoke_usage_new_(
        pfnHeader
    ,   pfnBody
    ,   args
    ,   &usageinfo
    ,   specifications
    );
}

CLASP_CALL(int)
clasp_show_usage(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_alias_t const*                specifications
,   clasp_char_t const*                 toolName    /* "rcp" */
,   clasp_char_t const*                 summary     /* "SystemTools (http://systemtools.sourceforge.net/)" */
,   clasp_char_t const*                 copyright   /* "Copyright (c) XXXX. All rights reserved" */
,   clasp_char_t const*                 description /* "Recursively copies files" */
,   clasp_char_t const*                 usage       /* "rcp [ ... options ... ] <src-spec> <dest-spec>" */
,   int                                 major
,   int                                 minor
,   int                                 revision
,   void                              (*pfnHeader)(clasp_diagnostic_context_t const*, clasp_usageinfo_t const* , clasp_alias_t const* )
,   void                              (*pfnBody)(clasp_diagnostic_context_t const*, clasp_usageinfo_t const* , clasp_alias_t const* )
,   void*                               param
,   int                                 flags
,   int                                 consoleWidth
,   int                                 tabSize
,   int                                 blanksBetweenItems
)
{
    clasp_usageinfo_t           usageinfo;
    clasp_diagnostic_context_t  ctxt_;
    int                         r;

    CLASP_ASSERT(NULL != pfnHeader);
    CLASP_ASSERT(NULL != pfnBody);

    ctxt = clasp_verify_context_(ctxt, &ctxt_, &r);
    if (NULL == ctxt)
    {
        return r;
    }

    usageinfo.version.major         =   major;
    usageinfo.version.minor         =   minor;
    usageinfo.version.revision      =   revision;
    usageinfo.version.build         =   0;
    usageinfo.toolName              =   toolName;
    usageinfo.summary               =   summary;
    usageinfo.copyright             =   copyright;
    usageinfo.description           =   description;
    usageinfo.usage                 =   usage;
    usageinfo.flags                 =   flags;
    usageinfo.param                 =   param;
    usageinfo.width                 =   consoleWidth;
    usageinfo.assumedTabWidth       =   tabSize;
    usageinfo.blanksBetweenItems    =   blanksBetweenItems;

    (*pfnHeader)(ctxt, &usageinfo, specifications);
    (*pfnBody)(ctxt, &usageinfo, specifications);

    return 0;
}

CLASP_CALL(int)
clasp_showHeader(
    clasp_arguments_t const*    args
,   clasp_alias_t const*        specifications
,   clasp_char_t const*         toolName
,   clasp_char_t const*         summary
,   clasp_char_t const*         copyright
,   clasp_char_t const*         description
,   clasp_char_t const*         usage
,   int                         major
,   int                         minor
,   int                         revision
,   void                      (*pfnHeader)(clasp_arguments_t const*, clasp_usageinfo_t const* , clasp_alias_t const* )
,   void*                       param
,   int                         flags
,   int                         consoleWidth
,   int                         tabSize
,   int                         blanksBetweenItems
)
{
    clasp_usageinfo_t usageinfo;

    CLASP_ASSERT(NULL != args);
    CLASP_ASSERT(NULL != pfnHeader);


    usageinfo.version.major         =   major;
    usageinfo.version.minor         =   minor;
    usageinfo.version.revision      =   revision;
    usageinfo.version.build         =   0;
    usageinfo.toolName              =   toolName;
    usageinfo.summary               =   summary;
    usageinfo.copyright             =   copyright;
    usageinfo.description           =   description;
    usageinfo.usage                 =   usage;
    usageinfo.flags                 =   flags;
    usageinfo.param                 =   param;
    usageinfo.width                 =   consoleWidth;
    usageinfo.assumedTabWidth       =   tabSize;
    usageinfo.blanksBetweenItems    =   blanksBetweenItems;

    return clasp_invoke_header_new_(pfnHeader, args, &usageinfo, specifications);
}

CLASP_CALL(int)
clasp_show_header(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_alias_t const*                specifications
,   clasp_char_t const*                 toolName
,   clasp_char_t const*                 summary
,   clasp_char_t const*                 copyright
,   clasp_char_t const*                 description
,   clasp_char_t const*                 usage
,   int                                 major
,   int                                 minor
,   int                                 revision
,   void                              (*pfnHeader)(clasp_diagnostic_context_t const*, clasp_usageinfo_t const* , clasp_alias_t const* )
,   void*                               param
,   int                                 flags
)
{
    clasp_usageinfo_t           usageinfo;
    clasp_diagnostic_context_t  ctxt_;
    int                         r;

    CLASP_ASSERT(NULL != pfnHeader);

    ctxt = clasp_verify_context_(ctxt, &ctxt_, &r);
    if (NULL == ctxt)
    {
        return r;
    }

    usageinfo.version.major     =   major;
    usageinfo.version.minor     =   minor;
    usageinfo.version.revision  =   revision;
    usageinfo.version.build     =   0;
    usageinfo.toolName          =   toolName;
    usageinfo.summary           =   summary;
    usageinfo.copyright         =   copyright;
    usageinfo.description       =   description;
    usageinfo.usage             =   usage;
    usageinfo.flags             =   flags;
    usageinfo.param             =   param;
    usageinfo.width             =   -1;
    usageinfo.assumedTabWidth   =   -1;

    (*pfnHeader)(ctxt, &usageinfo, specifications);

    return 0;
}

CLASP_CALL(int)
clasp_showBody(
    clasp_arguments_t const*    args
,   clasp_alias_t const*        specifications
,   void                      (*pfnBody)(clasp_arguments_t const*, clasp_usageinfo_t const* , clasp_alias_t const* )
,   void*                       param
,   int                         flags
,   int                         consoleWidth
,   int                         tabSize
,   int                         blanksBetweenItems
)
{
    clasp_usageinfo_t usageinfo;

    CLASP_ASSERT(NULL != args);
    CLASP_ASSERT(NULL != pfnBody);

    usageinfo.version.major         =   -1;
    usageinfo.version.minor         =   -1;
    usageinfo.version.revision      =   -1;
    usageinfo.version.build         =   -1;
    usageinfo.toolName              =   NULL;
    usageinfo.summary               =   NULL;
    usageinfo.copyright             =   NULL;
    usageinfo.description           =   NULL;
    usageinfo.usage                 =   NULL;
    usageinfo.flags                 =   flags;
    usageinfo.param                 =   param;
    usageinfo.width                 =   consoleWidth;
    usageinfo.assumedTabWidth       =   tabSize;
    usageinfo.blanksBetweenItems    =   blanksBetweenItems;

    return clasp_invoke_body_new_(pfnBody, args, &usageinfo, specifications);
}

CLASP_CALL(int)
clasp_show_body(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_alias_t const*                specifications
,   void                              (*pfnBody)(clasp_diagnostic_context_t const*, clasp_usageinfo_t const* , clasp_alias_t const* )
,   void*                               param
,   int                                 flags
,   int                                 consoleWidth
,   int                                 tabSize
,   int                                 blanksBetweenItems
)
{
    clasp_usageinfo_t           usageinfo;
    clasp_diagnostic_context_t  ctxt_;
    int                         r;

    CLASP_ASSERT(NULL != pfnBody);

    ctxt = clasp_verify_context_(ctxt, &ctxt_, &r);
    if (NULL == ctxt)
    {
        return r;
    }

    usageinfo.version.major         =   -1;
    usageinfo.version.minor         =   -1;
    usageinfo.version.revision      =   -1;
    usageinfo.version.build         =   -1;
    usageinfo.toolName              =   NULL;
    usageinfo.summary               =   NULL;
    usageinfo.copyright             =   NULL;
    usageinfo.description           =   NULL;
    usageinfo.usage                 =   NULL;
    usageinfo.flags                 =   flags;
    usageinfo.param                 =   param;
    usageinfo.width                 =   consoleWidth;
    usageinfo.assumedTabWidth       =   tabSize;
    usageinfo.blanksBetweenItems    =   blanksBetweenItems;

    (*pfnBody)(ctxt, &usageinfo, specifications);

    return 0;
}

CLASP_CALL(int)
clasp_showVersion(
    clasp_arguments_t const*    args
,   clasp_char_t const*         toolName
,   int                         major
,   int                         minor
,   int                         revision
,   void                      (*pfnVersion)(clasp_arguments_t const*, clasp_usageinfo_t const* , clasp_alias_t const* )
,   void*                       param
,   int                         flags
)
{
    clasp_usageinfo_t usageinfo;

    CLASP_ASSERT(NULL != args);
    CLASP_ASSERT(NULL != pfnVersion);

    usageinfo.version.major         =   major;
    usageinfo.version.minor         =   minor;
    usageinfo.version.revision      =   revision;
    usageinfo.version.build         =   0;
    usageinfo.toolName              =   toolName;
    usageinfo.summary               =   NULL;
    usageinfo.copyright             =   NULL;
    usageinfo.description           =   NULL;
    usageinfo.usage                 =   NULL;
    usageinfo.flags                 =   flags;
    usageinfo.param                 =   param;
    usageinfo.width                 =   -1;
    usageinfo.assumedTabWidth       =   -1;
    usageinfo.blanksBetweenItems    =   0;

    return clasp_invoke_version_new_(pfnVersion, args, &usageinfo, NULL);
}

CLASP_CALL(int)
clasp_show_version(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_char_t const*                 toolName
,   int                                 major
,   int                                 minor
,   int                                 revision
,   void                              (*pfnVersion)(clasp_diagnostic_context_t const*, clasp_usageinfo_t const* , clasp_alias_t const* )
,   void*                               param
,   int                                 flags
)
{
    clasp_usageinfo_t           usageinfo;
    clasp_diagnostic_context_t  ctxt_;
    int                         r;

    CLASP_ASSERT(NULL != pfnVersion);

    ctxt = clasp_verify_context_(ctxt, &ctxt_, &r);
    if (NULL == ctxt)
    {
        return r;
    }

    usageinfo.version.major     =   major;
    usageinfo.version.minor     =   minor;
    usageinfo.version.revision  =   revision;
    usageinfo.version.build     =   0;
    usageinfo.toolName          =   toolName;
    usageinfo.summary           =   NULL;
    usageinfo.copyright         =   NULL;
    usageinfo.description       =   NULL;
    usageinfo.usage             =   NULL;
    usageinfo.flags             =   flags;
    usageinfo.param             =   param;
    usageinfo.width             =   -1;
    usageinfo.assumedTabWidth   =   -1;

    (*pfnVersion)(ctxt, &usageinfo, NULL);

    return 0;
}


/* ///////////////////////////// end of file //////////////////////////// */

