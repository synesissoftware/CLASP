/* /////////////////////////////////////////////////////////////////////////
 * File:    clasp/clasp.h
 *
 * Purpose: The CLASP library API.
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


/** \file clasp/clasp.h
 *
 * \brief [C, C++] The CLASP library API.
 */

#ifndef CLASP_INCL_CLASP_H_CLASP
#define CLASP_INCL_CLASP_H_CLASP

/* /////////////////////////////////////////////////////////////////////////
 * version information
 */

#ifndef CLASP_DOCUMENTATION_SKIP_SECTION
# define CLASP_VER_CLASP_H_CLASP_MAJOR      3
# define CLASP_VER_CLASP_H_CLASP_MINOR      3
# define CLASP_VER_CLASP_H_CLASP_REVISION   3
# define CLASP_VER_CLASP_H_CLASP_EDIT       109
#endif /* !CLASP_DOCUMENTATION_SKIP_SECTION */

/**
 * \def CLASP_VER_MAJOR
 * The Major version number of the clasp library
 *
 * \def CLASP_VER_MINOR
 * Minor version number of the clasp library
 *
 * \def CLASP_VER_REVISION
 * The revision number of the clasp library
 *
 * \def CLASP_VER
 * The composite version of the clasp library
 */

#define CLASP_VER_MAJOR     0
#define CLASP_VER_MINOR     15
#define CLASP_VER_PATCH     0
#define CLASP_VER_REVISION  CLASP_VER_PATCH
#define CLASP_VER_AB        0x46

#define CLASP_VER           0x000f0046


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <stddef.h> /* size_t */
#include <stdarg.h> /* for logging function pointer */
#ifdef __cplusplus
# include <string.h>
#endif


/* /////////////////////////////////////////////////////////////////////////
 * documentation
 */

/** \defgroup group__clasp__common CLASP Common
 *
 *
 */

/** \defgroup group__clasp__api_parsing CLASP Parsing API
 *
 *
 */

/** \defgroup group__clasp__api_usage CLASP Usage API
 */


/* /////////////////////////////////////////////////////////////////////////
 * macros
 */

/** \def CLASP_DECLSPEC
 *
 * Storage class specifier to be applied to all System Tool Args API
 * functions
 *
 * \ingroup group__utility
 *
 * Defaults to no symbol. Can be defined to a symbol appropriate to the
 * operating system and linkage model. e.g. on Windows you might choose to
 * define it to <code>__declspec(dllexport)</code> when building System Tool
 * Args and to <code>__declspec(dllimport)</code> in client code using System
 * Tool Args.
 *
 * Used in the CLASP_CALL() macro.
 */

/** \def CLASP_EXTERN_C
 *
 * Resolves to <code>extern</code> when compiling in C, and
 * <code>extern "C"</code> when compiling in C++.
 *
 * \ingroup group__utility
 *
 * Used in the CLASP_CALL() macro.
 */

/** \def CLASP_CALLCONV
 *
 * Calling convention specifier to be applied to all System Tool Args API
 * functions
 *
 * Used in the CLASP_CALL() macro.
 *
 * \ingroup group__utility
 */

/** \def CLASP_CALL
 *
 * Used to declare and define System Tool Args API functions.
 *
 * \ingroup group__utility
 */

#if !defined(CLASP_DECLSPEC)
# define CLASP_DECLSPEC
#endif /* !CLASP_DECLSPEC */

#if defined(__cplusplus) || \
    defined(CLASP_DOCUMENTATION_SKIP_SECTION)

# define CLASP_EXTERN_C                                     extern "C"
#else /* ? __cplusplus */

# define CLASP_EXTERN_C                                     extern
#endif /* !__cplusplus */

#if !defined(CLASP_CALLCONV)
# define CLASP_CALLCONV
#endif /* !CLASP_CALLCONV */

#define CLASP_CALL(rt)                                      CLASP_EXTERN_C CLASP_DECLSPEC rt CLASP_CALLCONV

#ifndef CLASP_DOCUMENTATION_SKIP_SECTION
# define CLASP_CPP_CALL(rt)                                 extern "C++" CLASP_DECLSPEC rt CLASP_CALLCONV
#endif /* !CLASP_DOCUMENTATION_SKIP_SECTION */


#ifndef CLASP_OBSOLETE

# if 0
# elif defined(__cplusplus) && \
       __cplusplus >= 201402L

#  define CLASP_DEPRECATED_(msg)                            [[deprecated(msg)]]
# elif 0 || \
       defined(__GNUC__) || \
       defined(__clang__) || \
       0

#  define CLASP_DEPRECATED_(msg)                            __attribute__((deprecated))
# elif defined(_MSC_VER) && \
     (   _MSC_VER >= 1500 || \
         (   _MSC_VER >= 1400 && \
             defined(_MSC_FULL_VER) && \
             _MSC_FULL_VER >= 140050320))

#  define CLASP_DEPRECATED_(msg)                            __declspec(deprecated(msg))
# else

#  define CLASP_DEPRECATED_(msg)                            /* */
# endif
#else

# define CLASP_DEPRECATED_(msg)                             /* */
#endif /* CLASP_OBSOLETE */

#define CLASP_CALL_DEPRECATED(rt, msg)  \
                                        \
    CLASP_EXTERN_C                      \
    CLASP_DECLSPEC                      \
    CLASP_DEPRECATED_(msg)              \
    rt \
    CLASP_CALLCONV


/* /////////////////////////////////////////////////////////////////////////
 * platform recognition
 *
 * Define the symbol CLASP_OVERRIDE_PLATFORM to provide your own platform
 * discrimination
 */

#if defined(_WIN64)

# if defined(EMULATE_UNIX_ON_WIN64) && \
     !defined(EMULATE_UNIX_ON_WINDOWS)

#  define EMULATE_UNIX_ON_WINDOWS
# endif /* EMULATE_UNIX_ON_WIN64 && !EMULATE_UNIX_ON_WINDOWS */
# if !defined(EMULATE_UNIX_ON_WIN64) && \
     defined(EMULATE_UNIX_ON_WINDOWS)

#  define EMULATE_UNIX_ON_WIN64
# endif /* !EMULATE_UNIX_ON_WIN64 && EMULATE_UNIX_ON_WINDOWS */
#elif defined(_WIN32)

# if defined(EMULATE_UNIX_ON_WIN32) && \
     !defined(EMULATE_UNIX_ON_WINDOWS)

#  define EMULATE_UNIX_ON_WINDOWS
# endif /* EMULATE_UNIX_ON_WIN32 && !EMULATE_UNIX_ON_WINDOWS */
# if !defined(EMULATE_UNIX_ON_WIN32) && \
     defined(EMULATE_UNIX_ON_WINDOWS)

#  define EMULATE_UNIX_ON_WIN32
# endif /* !EMULATE_UNIX_ON_WIN32 && EMULATE_UNIX_ON_WINDOWS */
#endif /* _WIN32 || _WIN64 */


#ifndef CLASP_OVERRIDE_PLATFORM

# if defined(unix) || \
     defined(UNIX) || \
     defined(__unix) || \
     defined(__unix__) || \
     (   defined(__xlC__) && \
         defined(_POWER) && \
         defined(_AIX))

   /* Platform is UNIX */
#  define CLASP_PLATFORM_IS_UNIX
   /* Now determine whether this is being emulated on Windows */
#  if defined(_WIN64) && \
      ( defined(EMULATE_UNIX_ON_WIN64) || \
        defined(EMULATE_UNIX_ON_WINDOWS))

#   define CLASP_PLATFORM_IS_UNIX_EMULATED_ON_WIN64
#   define CLASP_PLATFORM_IS_UNIX_EMULATED_ON_WINDOWS
#  elif defined(_WIN32) && \
      ( defined(EMULATE_UNIX_ON_WIN32) || \
        defined(EMULATE_UNIX_ON_WINDOWS))

#   define CLASP_PLATFORM_IS_UNIX_EMULATED_ON_WIN32
#   define CLASP_PLATFORM_IS_UNIX_EMULATED_ON_WINDOWS
#  endif /* Windows */
# elif defined(WIN64)

   /* Platform is Win64 */
#  define CLASP_PLATFORM_IS_WIN64
#  define CLASP_PLATFORM_IS_WINDOWS
# elif defined(WIN32)

   /* Platform is Win32 */
#  define CLASP_PLATFORM_IS_WIN32
#  define CLASP_PLATFORM_IS_WINDOWS
# else /* ? platform */

/* We do not enforce that a neutral / non-recognised platform is a problem,
 * because the CLASP library does not rely on any platform-specific
 * features
 */
# endif /* platform */
#endif /* !CLASP_OVERRIDE_PLATFORM */

#if defined(CLASP_PLATFORM_IS_UNIX)
# if defined(__amd64__) || \
     defined(__amd64) || \
     defined(_AMD64_) || \
     defined(_M_AMD64) || \
     defined(_M_X64)
#  define CLASP_ARCH_IS_X64
# elif defined(__ia64__) || \
       defined(__ia64) || \
       defined(_IA64_) || \
       defined(_M_IA64)
#  define CLASP_ARCH_IS_IA64
# elif defined(__i386__) || \
       defined(__i386) || \
       defined(_X86_) || \
       defined(_M_IX86)
#  define CLASP_ARCH_IS_X86
# endif /* _M_?? */
#elif defined(CLASP_PLATFORM_IS_WINDOWS)
# if defined(_M_IA64)
#  define CLASP_ARCH_IS_IA64
# elif defined(_M_X64) || \
       defined(_M_AMD64)
#  define CLASP_ARCH_IS_X64
# elif defined(_M_IX86)
#  define CLASP_ARCH_IS_X86
# endif /* _M_?? */
#endif


/* /////////////////////////////////////////////////////////////////////////
 * basic types
 */


/* /////////////////////////////////////
 * wide strings
 *
 * NOTE: as of 0.11, the automatic discrimination of wide-string builds on
 * Windows is removed, because it is more common (and standards-conforming)
 * to use a multibyte main - int main(int argc, char* argv[]) - than the wide
 * main - int _wmain(int argc, wchar_t* argv[]). If you wish to use a wide
 * main, and therefore wide CLASP, you must define CLASP_USE_WIDE_STRINGS.
 */

#ifdef CLASP_USE_WIDE_STRINGS

# if defined(_WIN32) && \
     (  defined(UNICODE) || \
        defined(_UNICODE))

#  if defined(_UNICODE) && \
      !defined(UNICODE)

#   error (Windows:) _UNICODE defined and UNICODE not defined is not supported: define CLASP_USE_WIDE_STRINGS for special circumstances
#  endif /* _UNICODE && !UNICODE */
#  if defined(UNICODE) && \
      !defined(_UNICODE)

#   error (Windows:) UNICODE defined and _UNICODE not defined is not supported: define CLASP_USE_WIDE_STRINGS for special circumstances
#  endif /* UNICODE && !_UNICODE */
# endif /* _WIN32 && UNICODE && _UNICODE */

# ifndef _WCHAR_T_DEFINED
#  include <wchar.h>    /* for wchar_t (if not built-in) */
# endif /* !_WCHAR_T_DEFINED */
#endif /* CLASP_USE_WIDE_STRINGS */

#ifdef CLASP_USE_WIDE_STRINGS

typedef wchar_t                                             clasp_char_t;
#else /* ? CLASP_USE_WIDE_STRINGS */

typedef char                                                clasp_char_t;
#endif /* CLASP_USE_WIDE_STRINGS */

#ifdef CLASP_USE_WIDE_STRINGS

# define CLASP_LITERAL_STRING_(x)                           L ## #x
# define CLASP_LITERAL_STRING(x)                            CLASP_LITERAL_STRING_(x)
#else /* ? CLASP_USE_WIDE_STRINGS */

# define CLASP_LITERAL_STRING(x)                            x
#endif /* CLASP_USE_WIDE_STRINGS */

/* /////////////////////////////////////
 * clasp_slice_t
 */

#ifdef __cplusplus

struct clasp_slice_t;
#else /* ? __cplusplus */

typedef struct clasp_slice_t                                clasp_slice_t;
#endif /* __cplusplus */

CLASP_CALL(int)
clasp_slice_t_cmp(
    clasp_slice_t const*  slice
,   clasp_char_t const*   str
);

CLASP_CALL(size_t)
clasp_slice_create(
    clasp_char_t const* s
,   int                 n /* = -1 */
,   clasp_slice_t*      slice
);

/** Represents a string slice. */
struct clasp_slice_t
{
    /** The length of the slice. */
    size_t              len;
    /** Pointer to the first element in the slice. */
    clasp_char_t const* ptr;

#ifdef __cplusplus

public:
    static
    clasp_slice_t
    create(
        size_t              n
    ,   clasp_char_t const* s
    )
    {
        clasp_slice_t slice;

        clasp_slice_create(s, (int)n, &slice);

        return slice;
    }
    static
    clasp_slice_t
    create(
        clasp_char_t const* s
    )
    {
        clasp_slice_t slice;

        clasp_slice_create(s, -1, &slice);

        return slice;
    }

    bool
    equal(
        clasp_char_t const* s
    ) const
    {
        return 0 == clasp_slice_t_cmp(this, s);
    }
#endif /* __cplusplus */
};

#ifdef __cplusplus

inline
bool
operator ==(
    clasp_slice_t const&    lhs
,   clasp_char_t const*     rhs
)
{
    return lhs.equal(rhs);
}
inline
bool
operator ==(
    clasp_char_t const*     lhs
,   clasp_slice_t const&    rhs
)
{
    return rhs.equal(lhs);
}

inline
bool
operator !=(
    clasp_slice_t const&    lhs
,   clasp_char_t const*     rhs
)
{
    return !lhs.equal(rhs);
}
inline
bool
operator !=(
    clasp_char_t const*     lhs
,   clasp_slice_t const&    rhs
)
{
    return !rhs.equal(lhs);
}

inline
bool
operator <(
    clasp_slice_t const&    lhs
,   clasp_char_t const*     rhs
)
{
    return 0 < clasp_slice_t_cmp(&lhs, rhs);
}

inline
bool
operator <=(
    clasp_slice_t const&    lhs
,   clasp_char_t const*     rhs
)
{
    return 0 <= clasp_slice_t_cmp(&lhs, rhs);
}

inline
bool
operator >(
    clasp_slice_t const&    lhs
,   clasp_char_t const*     rhs
)
{
    return 0 > clasp_slice_t_cmp(&lhs, rhs);
}

inline
bool
operator >=(
    clasp_slice_t const&    lhs
,   clasp_char_t const*     rhs
)
{
    return 0 >= clasp_slice_t_cmp(&lhs, rhs);
}

/** A generic inserter function for clasp_slice_t into output streams
 *
 */
template <typename T_stm>
T_stm&
operator <<(
    T_stm&                  stm
,   clasp_slice_t const&    sl
)
{
    stm.write(sl.ptr, sl.len);

    return stm;
}
#endif /* __cplusplus */


/* /////////////////////////////////////////////////////////////////////////
 * main API types
 */

/** The possible types of the arguments
 *
 * Arguments may be of three types: <b>values</b>, <b>options</b> and
 * <b>flags</b>.
 *
 * - A <b>value</b> is a standalone argument, such as a file name argument.
 * Values do not begin with a hyphen, except in the case where they follow
 * the double-hyphen argument that is interpreted to mean "treat all
 * subsequent arguments as value". This interpretation is the default
 * behaviour of <b>clasp</b>, but may be suspended by specification of the
 * <code>CLASP_F_DONT_RECOGNISE_DOUBLEHYPHEN_TO_START_VALUES</code> flag to
 * clasp_parseArguments()
 * - An <b>option</b> is an argument comprised of a name/value pair. Two
 * forms of options are recognised by <b>clasp</b>, either
 * "<code>-name value</code>" (short-form option) or
 * "<code>--name=value</code>" (long-form option). <b>clasp</b> supports the
 * use of both forms simultaneously, by aliasing the short-form to the
 * long-form.
 * - A <b>flag</b> is an argument comprised of a hyphen and a single letter,
 * whose presence in the command-line usually indicates that a given program
 * characteristic be turned on or off, e.g. "<code>-c -R -d</code>". Flags
 * may be specified in combination, e.g. "<code>-cRd</code>", although the
 * combined string must not clash with an option. Flags may be used as
 * aliases for options with a given value, e.g. the flag "<code>-R</code>"
 * could be aliased to "<code>--recursive=no</code>".
 *
 * \see clasp_argument_t
 * \see clasp_parseArguments
 * \see CLASP_F_DONT_RECOGNISE_DOUBLEHYPHEN_TO_START_VALUES
 */
enum clasp_argtype_t
{
#ifndef CLASP_DOCUMENTATION_SKIP_SECTION
        CLASP_ARGTYPE_INVALID   =   0   /*!< An invalid value, not to be used */
#endif /* !CLASP_DOCUMENTATION_SKIP_SECTION */
    ,   CLASP_ARGTYPE_FLAG      =   -13 /*!< A <b>flag</b> */
    ,   CLASP_ARGTYPE_OPTION    =   -12 /*!< An <b>option</b> */
    ,   CLASP_ARGTYPE_VALUE     =   -11 /*!< A <b>value</b> */
#ifndef CLASP_DOCUMENTATION_SKIP_SECTION
    ,   CLASP_ARGTYPE_GAP_      =   -98 /*!< An invalid value, not to be used */
    ,   CLASP_ARGTYPE_TACIT_    =   -99 /*!< An invalid value, not to be used */
#endif /* !CLASP_DOCUMENTATION_SKIP_SECTION */
};
#ifndef __cplusplus
typedef enum clasp_argtype_t clasp_argtype_t;
#endif /* !__cplusplus */

/** A parsed argument, consisting of the type, given name, resolved name,
 * value (if any), flags, and command-line index and number of hyphens of
 * the underlying argument as it appears in the original command-line.
 */
struct clasp_argument_t
{
    clasp_slice_t               resolvedName;       /*!< The resolved name of the argument, based on the specifications, or the given name if no matching alias */
    clasp_slice_t               givenName;          /*!< The actual name of the argument given */
    clasp_slice_t               value;              /*!< The value, if any */
    clasp_argtype_t             type;               /*!< The type: CLASP_ARGTYPE_VALUE, CLASP_ARGTYPE_OPTION, or CLASP_ARGTYPE_FLAG */
    int                         cmdLineIndex;       /*!< The index of the argument with the original command-line */
    int                         numGivenHyphens;    /*!< The number of hyphens present in the original argument */
    int                         aliasIndex;         /*!< The index of the matching specification, if any; otherwise -1 */
    int                         flags;              /*!< Internal use only */
};
#ifndef __cplusplus
typedef struct clasp_argument_t                             clasp_argument_t;
#endif /* !__cplusplus */

/** Structure returned to the caller of clasp_parseArguments(), providing
 *   access to all the arguments - flags, options and values - after
 *   pre-processing and sorting.
 */
struct clasp_arguments_t
{
    size_t                      numArguments;       /*!< The total number of arguments */
    clasp_argument_t const*     arguments;          /*!< Pointer to an array of arguments */
    size_t                      numFlagsAndOptions; /*!< The number of flags and options */
    clasp_argument_t const*     flagsAndOptions;    /*!< Pointer to an array of flags and options */
    size_t                      numFlags;           /*!< The number of flags */
    clasp_argument_t const*     flags;              /*!< Pointer to an array of flags */
    size_t                      numOptions;         /*!< The number of options */
    clasp_argument_t const*     options;            /*!< Pointer to an array of options */
    size_t                      numValues;          /*!< The number of values */
    clasp_argument_t const*     values;             /*!< Pointer to an array of values */
    int                         argc;               /*!< Pointer to the <code>argc</code> argument passed to clasp_parseArguments() */
    clasp_char_t**              argv;               /*!< Pointer to the <code>argv</code> argument passed to clasp_parseArguments() */
    clasp_slice_t               programName;        /*!< The program name, deduced from argv[0] */
};
#ifndef __cplusplus
typedef struct clasp_arguments_t                            clasp_arguments_t;
#endif /* !__cplusplus */

/** Structure that defines a specification for a short option or flag; also
 *   used to define help information for all flags and options
 *
 * \note Specifying an entry whose <code>type</code> field has the
 *   value <code>-1</code> terminates the array
 */
struct clasp_specification_t
{
    clasp_argtype_t     type;             /*!< The type of the argument */
    clasp_char_t const* name;             /*!< The name of the alias, if an alias, or the name of the actual flag/option. May be NULL or empty */
    clasp_char_t const* mappedArgument;   /*!< The long option name. May contain a value, e.g. "--width=10", which will be used as a default */
    clasp_char_t const* help;             /*!< Help information for the argument */
    clasp_char_t const* valueSet;         /*!< char-separated list of options; first char is separator; if separator is trailing, indicates value may also be any-other-value */
    int                 bitFlags;         /*!< The bit flags associated with the specification (if it is a flag) */
};
#ifndef __cplusplus

typedef struct clasp_specification_t                        clasp_specification_t;
typedef struct clasp_specification_t                        clasp_alias_t;
#else

typedef clasp_specification_t                               clasp_alias_t;
#endif /* !__cplusplus */

/** \def CLASP_FLAG(alias, mappedArgument, help)
 *
 * Defines a flag specification in the specification array.
 *
 * \param alias The flag alias, e.g. "-i"
 * \param mappedArgument The flag mapped argument / full name, e.g. "--ignore-case"
 * \param help The help assocated with the flag, e.g. "Causes items to be compared in a case-insensitive fashion"
 *
 */
# define CLASP_FLAG(alias, mappedArgument, help)            { CLASP_ARGTYPE_FLAG, alias, mappedArgument, help, NULL, 0 }

/** \def CLASP_BIT_FLAG(alias, mappedArgument, bitFlags, help)
 *
 * Defines a bit-flag specification in the specification array.
 *
 * \param alias The flag alias, e.g. "-i"
 * \param mappedArgument The flag mapped argument / full name, e.g. "--ignore-case"
 * \param bitFlags The bit-flag(s) associated with the flag, e.g. MYTOOL_F_IGNORE_CASE
 * \param help The help assocated with the flag, e.g. "Causes items to be compared in a case-insensitive fashion"
 *
 */
# define CLASP_BIT_FLAG(alias, mappedArgument, bitFlags, help)  { CLASP_ARGTYPE_FLAG, alias, mappedArgument, help, NULL, bitFlags }

/** \def CLASP_FLAG_ALIAS(alias, mappedArgument)
 *
 * Equivalent to CLASP_FLAG(), but omits the need to specify an
 * empty/NULL help argument
 */
# define CLASP_FLAG_ALIAS(alias, mappedArgument)            CLASP_FLAG((alias), (mappedArgument), NULL)

/** \def CLASP_OPTION(alias, mappedArgument, help, valueSet)
 *
 * Defines a option specification in the specification array.
 *
 * \param alias The option alias, e.g. "-i"
 * \param mappedArgument The option mapped argument / full name, e.g. "--verbosity"
 * \param help The help assocated with the option, e.g. "The extent of user output"
 * \param valueSet The char-separated list of options; first char is separator; if separator is trailing, indicates value may also be any-other-value
 *
 */
# define CLASP_OPTION(alias, mappedArgument, help, valueSet)    { CLASP_ARGTYPE_OPTION, alias, mappedArgument, help, valueSet, 0 }

/** \def CLASP_OPTION_ALIAS(alias, mappedArgument)
 *
 * Equivalent to CLASP_OPTION(), but omits the need to specify an
 * empty/NULL help argument
 */
# define CLASP_OPTION_ALIAS(alias, mappedArgument)          CLASP_OPTION((alias), (mappedArgument), NULL, NULL)


#ifdef __cplusplus

# define CLASP_ARGTYPE_CAST_(N)                             (clasp_argtype_t(N))
#else /* ? __cplusplus */

# define CLASP_ARGTYPE_CAST_(N)                             ((clasp_argtype_t)(N))
#endif /* __cplusplus */

/** \def CLASP_SECTION(N)
 *
 * Defines a group section
 *
 * \param N any positive number in the range +1 - +1000
 *
 * \note Items in sections with -ve numbers will not be listed in usage.
 */
# define CLASP_SECTION(N)                                   { CLASP_ARGTYPE_CAST_(N), NULL, NULL, NULL, NULL, 0 }

/** \def CLASP_TACIT_SECTION()
 *
 * Defines all following items as being tacit - they are not displayed by
 * the functions in the \ref group__clasp__api_usage.
 *
 */
# define CLASP_TACIT_SECTION()                              CLASP_SECTION(CLASP_ARGTYPE_TACIT_)

/** \def CLASP_GAP_SECTION(sectionLabel)
 *
 * Defines a section label, that will be displayed by
 * the functions in the \ref group__clasp__api_usage.
 *
 * \param sectionLabel A literal character C-style string that serves as a
 *   section label. May be the empty string.
 */
# define CLASP_GAP_SECTION(sectionLabel)                    { CLASP_ARGTYPE_CAST_(CLASP_ARGTYPE_GAP_), NULL, NULL, sectionLabel, NULL, 0 }

/** \def CLASP_SPECIFICATION_ARRAY_TERMINATOR
 *
 * Terminates an array of specifications
 */
# define CLASP_SPECIFICATION_ARRAY_TERMINATOR               { CLASP_ARGTYPE_INVALID, NULL, NULL, NULL, NULL, 0 }

/** \def CLASP_ALIAS_ARRAY_TERMINATOR
 *
 * [DEPRECATED] Instead use CLASP_SPECIFICATION_ARRAY_TERMINATOR
 */
# define CLASP_ALIAS_ARRAY_TERMINATOR                       CLASP_SPECIFICATION_ARRAY_TERMINATOR

/** Log function prototype. */
typedef void (CLASP_CALLCONV *clasp_log_fn_t)(
    void*               context
,   int                 severity
,   clasp_char_t const* fmt
,   va_list             args
);

/** Memory allocation function prototype. */
typedef void* (CLASP_CALLCONV *clasp_malloc_fn_t)(
    void*       context
,   size_t      cb
);
/** Memory reallocation function prototype. */
typedef void* (CLASP_CALLCONV *clasp_realloc_fn_t)(
    void*       context
,   void*       pv
,   size_t      cb
);
/** Memory free function prototype. */
typedef void (CLASP_CALLCONV *clasp_free_fn_t)(
    void*       context
,   void*       pv
);

struct clasp_diagnostic_context_t;
#ifndef __cplusplus
typedef struct clasp_diagnostic_context_t                   clasp_diagnostic_context_t;
#endif /* !__cplusplus */

/** Initialises a diagnostic context */
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
);

struct clasp_diagnostic_context_t
{
    void*               context;

    clasp_malloc_fn_t   pfnMalloc;
    clasp_realloc_fn_t  pfnRealloc;
    clasp_free_fn_t     pfnFree;

    clasp_log_fn_t      pfnLog;
    int                 severities[5]; /*!< [0] => DEBUG, WARN, ERROR, FATAL, [4] => EMERG */

    void*               param;  /*!< user-specified parameter */

#ifdef __cplusplus

public: /** Construction */
    clasp_diagnostic_context_t()
    {
        clasp_init_diagnostic_context(this, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    }

    clasp_diagnostic_context_t(
        void*               context
    ,   clasp_malloc_fn_t   pfnMalloc
    ,   clasp_realloc_fn_t  pfnRealloc
    ,   clasp_free_fn_t     pfnFree
    )
    {
        clasp_init_diagnostic_context(this, context, pfnMalloc, pfnRealloc, pfnFree, NULL, NULL, NULL);
    }

    clasp_diagnostic_context_t(
        void*               context
    ,   clasp_log_fn_t      pfnLog
    ,   int const           (*severities)[5]
    )
    {
        clasp_init_diagnostic_context(this, context, NULL, NULL, NULL, pfnLog, severities, NULL);
    }
    clasp_diagnostic_context_t(
        void*               context
    ,   clasp_malloc_fn_t   pfnMalloc
    ,   clasp_realloc_fn_t  pfnRealloc
    ,   clasp_free_fn_t     pfnFree
    ,   clasp_log_fn_t      pfnLog
    ,   int const           (*severities)[5]
    )
    {
        clasp_init_diagnostic_context(this, context, pfnMalloc, pfnRealloc, pfnFree, pfnLog, severities, NULL);
    }
    clasp_diagnostic_context_t(
        void*               context
    ,   clasp_malloc_fn_t   pfnMalloc
    ,   clasp_realloc_fn_t  pfnRealloc
    ,   clasp_free_fn_t     pfnFree
    ,   clasp_log_fn_t      pfnLog
    ,   int const           (*severities)[5]
    ,   void*               param
    )
    {
        clasp_init_diagnostic_context(this, context, pfnMalloc, pfnRealloc, pfnFree, pfnLog, severities, param);
    }
#endif /* __cplusplus */
};


/* /////////////////////////////////////////////////////////////////////////
 * parsing API
 */

/** Pre-processors and sorts the command-line arguments
 *
 * \ingroup group__clasp__api_parsing
 *
 * \param flags Flags that control the parsing behaviour
 * \param argc The <code>argc</code> argument passed to main(). Must be 1 or
 *   more; undefined behaviour otherwise
 * \param argv The <code>argv</code>
 * \param specifications Variable-length array of clasp_specification_t
 *   entries that define the specifications used in parsing. May be \c NULL
 * \param args Receives a pointer to the parsed results structure
 *
 * \return An error code indicating the status of the function
 * \retval 0 The function succeeded
 * \retval !0 Any other standard error code, indicating the reason that the
 *   function failed, e.g. <code>ENOMEM</code>
 *
 * \note The behaviour of this function is undefined if argc is less than 1
 */
CLASP_CALL(int)
clasp_parseArguments(
    unsigned                            flags
,   int                                 argc
,   clasp_char_t*                       argv[]
,   clasp_specification_t const         specifications[]
,   clasp_diagnostic_context_t const*   ctxt
,   clasp_arguments_t const**           args
);

/** Releases all resources associated with the command-line
 *
 * \ingroup group__clasp__api_parsing
 *
 * \param args The clasp-arguments structure pointer allocated by a previous
 *   call to clasp_parseArguments()
 */
CLASP_CALL(void)
clasp_releaseArguments(
    clasp_arguments_t const*            args
);

/** Obtains the specifications given in the call to clasp_parseArguments(),
 *   which may be NULL.
 *
 * \pre NULL != args
 */
CLASP_CALL(clasp_specification_t const*)
clasp_getSpecifications(
    clasp_arguments_t const*            args
);

/** Reports how many flags/options are not recognised relative to the
 * given \c specifications array, and returns a pointer to the \c nSkip'th
 * unrecognised instance.
 *
 * \pre NULL != args
 * \pre NULL != specifications
 */
CLASP_CALL(size_t)
clasp_reportUnrecognisedFlagsAndOptions(
    clasp_arguments_t const*    args
,   clasp_specification_t const specifications[]
,   clasp_argument_t const**    nextUnrecognisedArg
,   unsigned                    nSkip /* = 0 */
);

/** Reports how many flags arguments were not used by the
 * application, and returns a pointer to the first unused flag
 * argument.
 *
 * \ingroup group__clasp__api_parsing
 *
 * \param args The clasp-arguments structure pointer allocated by a previous
 *   call to clasp_parseArguments()
 * \param nextUnusedArg Pointer to a variable to receive a pointer to the
 *   next unused argument (after the first \c nSkip have been skipped)
 * \param nSkip Number of unused flag arguments to skip before
 *   writing into <code>*nextUnusedArg</code>.
 *
 * \return The number of remaining unused flagss (after skipping the
 *   first \c nSkip instances).
 *
 * \pre NULL != args
 */
CLASP_CALL(size_t)
clasp_reportUnusedFlags(
    clasp_arguments_t const*    args
,   clasp_argument_t const**    firstUnusedArg
,   unsigned                    nSkip /* = 0 */
);

/** Reports how many option arguments were not used by the
 * application, and returns a pointer to the first unused option
 * argument.
 *
 * \ingroup group__clasp__api_parsing
 *
 * \param args The clasp-arguments structure pointer allocated by a previous
 *   call to clasp_parseArguments()
 * \param nextUnusedArg Pointer to a variable to receive a pointer to the
 *   next unused argument (after the first \c nSkip have been skipped)
 * \param nSkip Number of unused option arguments to skip before
 *   writing into <code>*nextUnusedArg</code>.
 *
 * \return The number of remaining unused options (after skipping the
 *   first \c nSkip instances).
 *
 * \pre NULL != args
 */
CLASP_CALL(size_t)
clasp_reportUnusedOptions(
    clasp_arguments_t const*    args
,   clasp_argument_t const**    firstUnusedArg
,   unsigned                    nSkip /* = 0 */
);

/** Reports how many flag/option arguments were not used by the
 * application, and returns a pointer to the first unused flag/option
 * argument.
 *
 * \ingroup group__clasp__api_parsing
 *
 * \param args The clasp-arguments structure pointer allocated by a previous
 *   call to clasp_parseArguments()
 * \param nextUnusedArg Pointer to a variable to receive a pointer to the
 *   next unused argument (after the first \c nSkip have been skipped)
 * \param nSkip Number of unused flag/option arguments to skip before
 *   writing into <code>*nextUnusedArg</code>.
 *
 * \return The number of remaining unused flags/options (after skipping the
 *   first \c nSkip instances).
 *
 * \pre NULL != args
 */
CLASP_CALL(size_t)
clasp_reportUnusedFlagsAndOptions(
    clasp_arguments_t const*  args
,   clasp_argument_t const**  nextUnusedArg
,   unsigned                  nSkip /* = 0 */
);

/** Reports how many value arguments were not used by the
 * application, and returns a pointer to the first unused value
 * argument.
 *
 * \ingroup group__clasp__api_parsing
 *
 * \param args The clasp-arguments structure pointer allocated by a previous
 *   call to clasp_parseArguments()
 * \param nextUnusedArg Pointer to a variable to receive a pointer to the
 *   next unused argument (after the first \c nSkip have been skipped)
 * \param nSkip Number of unused value arguments to skip before
 *   writing into <code>*nextUnusedArg</code>.
 *
 * \return The number of remaining unused values (after skipping the
 *   first \c nSkip instances).
 *
 * \pre NULL != args
 */
CLASP_CALL(size_t)
clasp_reportUnusedValues(
    clasp_arguments_t const*    args
,   clasp_argument_t const**    firstUnusedArg
,   unsigned                    nSkip /* = 0 */
);

/** Reports how many arguments were not used by the
 * application, and returns a pointer to the first unused
 * argument.
 *
 * \ingroup group__clasp__api_parsing
 *
 * \param args The clasp-arguments structure pointer allocated by a previous
 *   call to clasp_parseArguments()
 * \param nextUnusedArg Pointer to a variable to receive a pointer to the
 *   next unused argument (after the first \c nSkip have been skipped)
 * \param nSkip Number of unused arguments to skip before
 *   writing into <code>*nextUnusedArg</code>.
 *
 * \return The number of remaining unused arguments (after skipping the
 *   first \c nSkip instances).
 *
 * \pre NULL != args
 */
CLASP_CALL(size_t)
clasp_reportUnusedArguments(
    clasp_arguments_t const*    args
,   clasp_argument_t const**    firstUnusedArg
,   unsigned                    nSkip /* = 0 */
);

/** Causes the given argument to be marked as used.
 *
 *
 * \pre NULL != args
 * \pre NULL != usedArg
 */
CLASP_CALL(void)
clasp_useArgument(
    clasp_arguments_t const*  args
,   clasp_argument_t const*   usedArg
);

/** Indicates whether the given argument is marked as used.
 *
 * \retval 0 The argument is not marked as used
 * \retval !0 The argument is marked as used
 *
 * \pre NULL != args
 * \pre NULL != usedArg
 */
CLASP_CALL(int)
clasp_argumentIsUsed(
    clasp_arguments_t const*    args
,   clasp_argument_t const*     arg
);

/** Indicates whether a given set of command-line arguments contains the
 * given flag.
 *
 * \param args Pointer to the clasp_arguments_t instance.
 *
 * \retval 0 if the flag is not specified
 * \retval !0 if the flag is specified
 *
 * \note If the given flag is found, it will be marked as used.
 *
 * \pre NULL != args
 * \pre NULL != mappedArgumentName
 */
CLASP_CALL(int)
clasp_flagIsSpecified(
    clasp_arguments_t const*    args
,   clasp_char_t const*         mappedArgumentName
);

/** Determines whether the flag is specified (or an option is specified with
 * the value 'yes' or 'true') and, if so, sets the given \c flag into the
 * given \c bitFlags variable.
 *
 * \retval 0 if the flag is not specified (or the option is specified
 *   negatively)
 * \retval !0 if the flag is specified (or the option is specified
 *   positively)
 *
 * \note If the given flag is found, it will be marked as used.
 *
 * \pre NULL != args
 * \pre NULL != mappedArgumentName
 * \pre NULL != bitFlags
 */
CLASP_CALL(int)
clasp_checkFlag(
    clasp_arguments_t const*    args
,   clasp_char_t const*         mappedArgumentName
,   int*                        bitFlags
,   int                         flag
);

/** Checks arguments for all declared flags, combining their \c bitFlags
 * value into the given \c bitFlags variable.
 *
 * \param args Pointer to the clasp_arguments_t instance.
 * \param specifications Pointer to the specification array
 * \param bitFlags Optional pointer to a bit-flags variable. May be NULL. If
 *   not NULL, it is assumed to be initialised.
 *
 * \return The OR-combination of <code>*bitFlags</code> (if given) and the
 *   flag values of all declared flags in \c args
 *
 * \note If \c bitFlags is not \c NULL, it is assumed to be initialised (to
 *   0, or a mask representing previous calculation), and bit-flags from any
 *   found flag arguments will be OR'd into it.
 *
 * \note All flags found will be marked as used.
 *
 * \pre NULL != args
 * \pre NULL != specifications
 */
CLASP_CALL(int)
clasp_checkAllFlags(
    clasp_arguments_t const*    args
,   clasp_specification_t const specifications[]
,   int*                        bitFlags
);

/** Checks arguments for all flags matching the \c bitMask, combining their
 * \c bitFlags value into the given \c bitFlags variable.
 *
 * \param args Pointer to the clasp_arguments_t instance.
 * \param specifications Pointer to the specification array
 * \param bitFlags Optional pointer to a bit-flags variable. May be NULL. If
 *   not NULL, it is assumed to be initialised.
 *
 * \note If \c bitFlags is not NULL, it is assumed to be initialised (whether
 *   to 0, or a mask representing previous calculation), and bit-flags from
 *   any found flag arguments will be OR'd into it.
 *
 * \note All flags found will be marked as used.
 *
 * \pre NULL != args
 * \pre NULL != specifications
 */
CLASP_CALL(int)
clasp_checkAllMatchingFlags(
    clasp_arguments_t const*    args
,   clasp_specification_t const specifications[]
,   int                         bitMask
,   int*                        bitFlags
);

/** Finds the nth flag/option argument matching the given mapped name.
 *
 * \param args Pointer to the clasp_arguments_t instance.
 * \param mappedArgumentName The argument mapped name.
 * \param nSkip Number of instances of the given name to skip before
 *   returning found instance.
 */
CLASP_CALL(clasp_argument_t const*)
clasp_findFlagOrOption(
    clasp_arguments_t const*    args
,   clasp_char_t const*         mappedArgumentName
,   unsigned                    nSkip /* = 0 */
);


/** Checks for the existence of a value at a given index, optionally
 * providing to the caller the value pointer and/or the value length and/or
 * the argument.
 *
 * \param args Pointer to the clasp_arguments_t instance. May not be NULL.
 * \param index Index of the argument.
 * \param pptr Optional pointer to a variable to receive the value pointer.
 * \param plen Optional pointer to a variable that receives the value length.
 * \param parg Optional pointer to a variable to receive the argument pointer.
 *
 * \retval 0 if a value at the given index exists
 * \retval !0 if a value at the given index does not exist
 *
 * \pre (NULL != args)
 */

CLASP_CALL(int)
clasp_checkValue(
    clasp_arguments_t const*    args
,   size_t                      index
,   clasp_char_t const**        pptr
,   size_t*                     plen
,   clasp_argument_t const**    parg
);


#ifdef CLASP_DOCUMENTATION_SKIP_SECTION

/** Indicates whether the given variable points to an argument that
 * represents a treated hyphen.
 *
 * \param arg
 *
 * \pre (NULL != arg)
 *
 * \see CLASP_F_TREAT_SINGLEHYPHEN_AS_VALUE
 *
 * \note This is currently implemented as a macro, so you should not use it
 * with any expression that should not be exercised multiply.
 */
CLASP_CALL_(int)
clasp_valueIsTreatedHyphen(
    clasp_argument_t const*     arg
);
#else /* ? CLASP_DOCUMENTATION_SKIP_SECTION */

# define clasp_valueIsTreatedHyphen(a)                      (0 != (a)->givenName.len)
#endif /* !CLASP_DOCUMENTATION_SKIP_SECTION */


/** \def CLASP_F_DONT_RECOGNISE_DOUBLEHYPHEN_TO_START_VALUES
 *
 * \ingroup group__clasp__api_parsing
 *
 * clasp_parseArguments() flag used to prevent the double-hyphen argument \c "--"
 * from being recognised as a special modifier.
 *
 * Normally the \c "--" argument is interpreted to mean that all subsequent
 * arguments are treated as values, regardless of whether they're prefixed
 * with hyphens or not, in order to allow filenames (or other values) that
 * contain leading hyphens to be interpreted correctly.
 */
#define CLASP_F_DONT_RECOGNISE_DOUBLEHYPHEN_TO_START_VALUES (0x00000001)

/** \def CLASP_F_TREAT_SINGLEHYPHEN_AS_VALUE
 *
 * \ingroup group__clasp__api_parsing
 *
 * clasp_parseArguments() flag used to cause the single-hyphen argument \c "-"
 * to be recognised as a value.
 *
 * Normally the \c "-" argument is interpreted as a flag/option, requiring
 * that client code examine the flags and options in addition to the
 * values, in order to process a sequence of files including stdin (as
 * represented by \c "-"). Specifying this flag causes it to appear in
 * the values, so all values can be processed together.
 *
 * \note To avoid ambiguity, a \c "-" transformed in this way will have
 *   non-empty \c resolvedName and \c givenName fields
 */
#define CLASP_F_TREAT_SINGLEHYPHEN_AS_VALUE                 (0x00000002)

/** \def CLASP_F_DONT_EXPAND_WILDCARDS_ON_WINDOWS
 *
 * \ingroup group__clasp__api_parsing
 *
 * [Windows-only] clasp_parseArguments() flag that prevents the expansion of
 * wildcards on Windows.
 *
 * Because the Windows shell does not automatically expand wildcards,
 * clasp_parseArguments() performs this function on any values containing '?'
 * or '*' before returning the arguments. If that is not required, it can
 * be suppressed.
 *
 * \note Specifying this flag does not remove the requirement to link the
 *   <a href="http://recls.org/">recls</a> library along with clasp to
 *   Windows executables. To do that, define the pre-processor symbol
 *   CLASP_CMDLINE_ARGS_NO_RECLS_ON_WINDOWS during compilation clasp.
 */
#define CLASP_F_DONT_EXPAND_WILDCARDS_ON_WINDOWS            (0x00000100)

/** \def CLASP_F_DO_EXPAND_WILDCARDS_IN_APOSQUOTES_ON_WINDOWS
 *
 * \ingroup group__clasp__api_parsing
 *
 * [Windows-only] clasp_parseArguments() flag that causes the expansion of
 * wildcards in apostrophe-quoted values on Windows.
 *
 * Ordinarily, wildcards that are quoted by apostrophes (single quotes) are
 * not expanded. Specifying this flag causes such values to be expanded on
 * Windows.
 */
#define CLASP_F_DO_EXPAND_WILDCARDS_IN_APOSQUOTES_ON_WINDOWS    (0x00000200)

/** \def CLASP_F_PRESERVE_ORIGINAL_ARGUMENT_ORDER
 *
 * \ingroup group__clasp__api_parsing
 *
 * Prevents clasp_parseArguments() from sorting the results into groups of
 * flags, options and values.
 *
 * \note The structure members <code>numFlagsAndOptions</code>,
 *   <code>flagsAndOptions</code>, <code>numFlags</code>,
 *   <code>flags</code>, <code>numOptions</code>, <code>options</code>,
 *   <code>numValues</code> and <code>values</code> are not valid when this
 *   flag is used. Client code should only use <code>numArguments</code> and
 *   <code>arguments</code>.
 */
#define CLASP_F_PRESERVE_ORIGINAL_ARGUMENT_ORDER            (0x00000400)


/* /////////////////////////////////////////////////////////////////////////
 * usage API
 */

/** \def CLASP_STOCK_FLAG_HELP
 *
 * Defines a CLASP_FLAG() specification for the "--help" de-facto
 * standard flag.
 */
#define CLASP_STOCK_FLAG_HELP                               CLASP_FLAG(NULL, "--help", "Show this help and terminate.")
/** \def CLASP_STOCK_FLAG_VERSION
 *
 * Defines a CLASP_FLAG() specification for the "--version" de-facto
 * standard flag.
 */
#define CLASP_STOCK_FLAG_VERSION                            CLASP_FLAG(NULL, "--version", "Show version and terminate.")

/** Aggregate of version
 */
struct clasp_versioninfo_t
{
    int major;      /*!< The major version. */
    int minor;      /*!< The minor version. */
    int revision;   /*!< The revision number. */
    int build;      /*!< The build number. */
};
#ifndef __cplusplus
typedef struct clasp_versioninfo_t                          clasp_versioninfo_t;
#endif /* !__cplusplus */

struct clasp_tool_t
{
    clasp_char_t const*     toolName;
    clasp_char_t const*     toolDescription;
    clasp_char_t const*     toolUsage;
    clasp_char_t const*     suiteSummary;
    clasp_versioninfo_t     version;
    int                     consoleWidth;
    int                     assumedTabWidth;
    clasp_char_t const*     examples;
    clasp_char_t const*     defectReports;
    clasp_char_t const*     copyright;
    clasp_char_t const*     license;
    clasp_char_t const*     warranty;
    clasp_char_t const*     authors;
};
#ifndef __cplusplus
typedef struct clasp_tool_t                                 clasp_tool_t;
#endif /* !__cplusplus */

/**
 */
struct clasp_usageinfo_t
{
    /** The version information. */
    clasp_versioninfo_t     version;
    /** The tool name / program name. */
    clasp_char_t const*     toolName;
    clasp_char_t const*     summary;
    clasp_char_t const*     copyright;
    clasp_char_t const*     description;
    clasp_char_t const*     usage;
    int                     flags;
    void*                   param;
    /** If <0, infinite width is assumed */
    int                     width;
    /** The TAB width to be assumed.
     *
     * \note If this value is >0, then TABs are used for indentation, and
     *   the given value is used in the line-wrapping calculation. If this
     *   value is <0, then exactly this number of SPACEs are used for each
     *   indentation level (and the line-wrapping calculation is exact). If
     *   this value is 0, then line-wrapping is not performed.
     */
    int                     assumedTabWidth;
    /** This value specifies the number of blank lines to be inserted
     * between the alias list and description of each flag/option.
     */
    int                     blanksBetweenItems;
};
#ifndef __cplusplus
typedef struct clasp_usageinfo_t                            clasp_usageinfo_t;
#endif /* !__cplusplus */


/** Displays usage (aka help) information for the program, according to the
 * given parameters.
 *
 * \param args The arguments obtained from parsing the command-line. May not
 *  be NULL;
 * \param specifications The specifications used in parsing the
 *  command-line. May be NULL, in which case it will be inferred from args;
 * \param toolName The program name. May be NULL, in which case it will be
 *  inferred from the process-name (via args);
 * \param summary A string to stand as a summary line. May be NULL as long
 *  as pfnHeader is compatible with that;
 * \param copyright A string to stand as a copyright line. May be NULL as
 *  long as pfnHeader is compatible with that;
 * \param description A string to stand as a description line. May be NULL
 *  as long as pfnHeader is compatible with that;
 * \param usage A string to stand as a usage line. May be NULL, in which
 *  case the CLASP API will supply a pro-forma string (taking into account
 *  whether specifications contains any flags and/or options). May also
 *  contain the string ":program:", in which case the value of toolName
 *  (including if it was inferred) will be used as replacement;
 * \param major The major version number;
 * \param minor The minor version number;
 * \param revision The patch/revision version number;
 * \param pfnHeader The callback function to write the header structure. The
 *  stock function clasp_showHeaderByFILE() is provided, in which case the
 *  value stdout should be passed for param;
 * \param pfnBody The callback function to write the body structure. The
 *  stock function clasp_showBodyByFILE() is provided, in which case the
 *  value stdout should be passed for param;
 * \param param User-defined parameter to be passed to \c pfnHeader and \c pfnBody;
 * \param flags Flags that moderate the behaviour of the function;
 * \param consoleWidth The width, in characters, of the console. STLSoft users may use the return value of <code>platformstl_C_get_console_width()</code> (part of the <a href="http://stlsoft.org/">STLSoft</a> libraries);
 * \param tabSize The size of tabs on the console. If less than 1 then <code>-tabSize</code> spaces are used instead of a tab character;
 * \param blanksBetweenItems The number of blank lines to insert between each item;
 *
 * \retval 0 The operation completed successfully;
 */
CLASP_CALL(int)
clasp_showUsage(
    clasp_arguments_t const*        args
,   clasp_specification_t const     specifications[]
,   clasp_char_t const*             toolName    /* "rcp" */
,   clasp_char_t const*             summary     /* "SystemTools (http://systemtools.sourceforge.net/)" */
,   clasp_char_t const*             copyright   /* "Copyright (c) XXXX. All rights reserved" */
,   clasp_char_t const*             description /* "Recursively copies files" */
,   clasp_char_t const*             usage       /* ":program: [ ... options ... ] <src-spec> <dest-spec>" */
,   int                             major
,   int                             minor
,   int                             revision
,   void                          (*pfnHeader)(clasp_arguments_t const*, clasp_usageinfo_t const* , clasp_specification_t const[] )
,   void                          (*pfnBody)(clasp_arguments_t const*, clasp_usageinfo_t const* , clasp_specification_t const[] )
,   void*                           param
,   int                             flags
,   int                             consoleWidth
,   int                             tabSize
,   int                             blanksBetweenItems
);

/** Displays header part of the usage (aka help) information for the
 * program, according to the given parameters.
 *
 * \param args The arguments obtained from parsing the command-line. May not
 *  be NULL;
 * \param specifications The specifications used in parsing the
 *  command-line. May be NULL, in which case it will be inferred from args;
 * \param toolName The program name. May be NULL, in which case it will be
 *  inferred from the process-name (via args);
 * \param summary A string to stand as a summary line. May be NULL as long
 *  as pfnHeader is compatible with that;
 * \param copyright A string to stand as a copyright line. May be NULL as
 *  long as pfnHeader is compatible with that;
 * \param description A string to stand as a description line. May be NULL
 *  as long as pfnHeader is compatible with that;
 * \param usage A string to stand as a usage line. May be NULL, in which
 *  case the CLASP API will supply a pro-forma string (taking into account
 *  whether specifications contains any flags and/or options). May also
 *  contain the string ":program:", in which case the value of toolName
 *  (including if it was inferred) will be used as replacement;
 * \param major The major version number;
 * \param minor The minor version number;
 * \param revision The patch/revision version number;
 * \param pfnHeader The callback function to write the header structure. The
 *  stock function clasp_showHeaderByFILE() is provided, in which case the
 *  value stdout should be passed for param;
 * \param param User-defined parameter to be passed to \c pfnHeader;
 * \param flags Flags that moderate the behaviour of the function;
 * \param consoleWidth The width, in characters, of the console. STLSoft users may use the return value of <code>platformstl_C_get_console_width()</code> (part of the <a href="http://stlsoft.org/">STLSoft</a> libraries);
 * \param tabSize The size of tabs on the console. If less than 1 then <code>-tabSize</code> spaces are used instead of a tab character;
 * \param blanksBetweenItems The number of blank lines to insert between each item;
 *
 * \retval 0 The operation completed successfully;
 */
CLASP_CALL(int)
clasp_showHeader(
    clasp_arguments_t const*        args
,   clasp_specification_t const     specifications[]
,   clasp_char_t const*             toolName    /* "rcp" */
,   clasp_char_t const*             summary     /* "SystemTools (http://systemtools.sourceforge.net/)" */
,   clasp_char_t const*             copyright   /* "Copyright (c) XXXX. All rights reserved" */
,   clasp_char_t const*             description /* "Recursively copies files" */
,   clasp_char_t const*             usage       /* ":program: [ ... options ... ] <src-spec> <dest-spec>" */
,   int                             major
,   int                             minor
,   int                             revision
,   void                          (*pfnHeader)(clasp_arguments_t const*, clasp_usageinfo_t const* , clasp_specification_t const[] )
,   void*                           param
,   int                             flags
,   int                             consoleWidth
,   int                             tabSize
,   int                             blanksBetweenItems
);

/** Displays body part of the usage (aka help) information for the
 * program, according to the given parameters.
 *
 * \param args The arguments obtained from parsing the command-line. May not
 *  be NULL;
 * \param specifications The specifications used in parsing the
 *  command-line. May be NULL, in which case it will be inferred from args;
 * \param pfnBody The callback function to write the body structure. The
 *  stock function clasp_showBodyByFILE() is provided, in which case the
 *  value stdout should be passed for param;
 * \param param User-defined parameter to be passed to \c pfnBody;
 * \param flags Flags that moderate the behaviour of the function;
 * \param consoleWidth The width, in characters, of the console. STLSoft users may use the return value of <code>platformstl_C_get_console_width()</code> (part of the <a href="http://stlsoft.org/">STLSoft</a> libraries);
 * \param tabSize The size of tabs on the console. If less than 1 then <code>-tabSize</code> spaces are used instead of a tab character;
 * \param blanksBetweenItems The number of blank lines to insert between each item;
 *
 * \retval 0 The operation completed successfully;
 */
CLASP_CALL(int)
clasp_showBody(
    clasp_arguments_t const*        args
,   clasp_specification_t const     specifications[]
,   void                          (*pfnBody)(clasp_arguments_t const*, clasp_usageinfo_t const* , clasp_specification_t const[] )
,   void*                           param
,   int                             flags
,   int                             consoleWidth
,   int                             tabSize
,   int                             blanksBetweenItems
);

/** Displays version information for the program, according to the given
 * parameters.
 *
 * \param args The arguments obtained from parsing the command-line. May not
 *  be NULL;
 * \param toolName The program name. May be NULL, in which case it will be
 *  inferred from the process-name (via args);
 * \param major The major version number;
 * \param minor The minor version number;
 * \param revision The patch/revision version number;
 * \param pfnVersion The callback function to write the version structure.
 *  The stock function clasp_showVersionByFILE() is provided, in which case
 *  the value stdout should be passed for param;
 * \param param User-defined parameter to be passed to \c pfnVersion;
 * \param flags Flags that moderate the behaviour of the function;
 *
 * \retval 0 The operation completed successfully;
 */
CLASP_CALL(int)
clasp_showVersion(
    clasp_arguments_t const*    args
,   clasp_char_t const*         toolName
,   int                         major
,   int                         minor
,   int                         revision
,   void                      (*pfnVersion)(clasp_arguments_t const*, clasp_usageinfo_t const* , clasp_specification_t const[] )
,   void*                       param
,   int                         flags
);


/** Evaluates the number of specifications in the array
 *
 * \ingroup group__clasp__api_usage
 *
 * \param specifications Pointer to the specification array
 */
CLASP_CALL(size_t)
clasp_countSpecifications(
    clasp_specification_t const specifications[]
);

#ifndef CLASP_DOCUMENTATION_SKIP_SECTION

/** [DEPRECATED]
 *
 * \deprecated Instead use clasp_countSpecifications()
 */
CLASP_CALL_DEPRECATED(size_t, "clasp_countAliases() is deprecated and will be removed in a future release; use clasp_countSpecifications() instead")
clasp_countAliases(
    clasp_specification_t const specifications[]
);
#endif /* !CLASP_DOCUMENTATION_SKIP_SECTION */


/**  Stock function that shows version to a <code>FILE*</code>
 */
CLASP_CALL(void)
clasp_showVersionByFILE(
    clasp_arguments_t const*    args
,   clasp_usageinfo_t const*    info
,   clasp_specification_t const specifications[]
);

/**  Stock function that shows header to a <code>FILE*</code>
 */
CLASP_CALL(void)
clasp_showHeaderByFILE(
    clasp_arguments_t const*    args
,   clasp_usageinfo_t const*    info
,   clasp_specification_t const specifications[]
);

/**  Stock function that shows body to a <code>FILE*</code>
 */
CLASP_CALL(void)
clasp_showBodyByFILE(
    clasp_arguments_t const*    args
,   clasp_usageinfo_t const*    info
,   clasp_specification_t const specifications[]
);


#ifndef CLASP_DOCUMENTATION_SKIP_SECTION

/** [DEPRECATED]
 *
 * \deprecated Instead use clasp_showUsage()
 */
CLASP_CALL_DEPRECATED(int, "clasp_show_usage() is deprecated and will be removed in a future release; use clasp_showUsage() instead")
clasp_show_usage(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_specification_t const         specifications[]
,   clasp_char_t const*                 toolName    /* "rcp" */
,   clasp_char_t const*                 summary     /* "SystemTools (http://systemtools.sourceforge.net/)" */
,   clasp_char_t const*                 copyright   /* "Copyright (c) XXXX. All rights reserved" */
,   clasp_char_t const*                 description /* "Recursively copies files" */
,   clasp_char_t const*                 usage       /* ":program: [ ... options ... ] <src-spec> <dest-spec>" */
,   int                                 major
,   int                                 minor
,   int                                 revision
,   void                              (*pfnHeader)(clasp_diagnostic_context_t const*, clasp_usageinfo_t const* , clasp_specification_t const[] )
,   void                              (*pfnBody)(clasp_diagnostic_context_t const*, clasp_usageinfo_t const* , clasp_specification_t const[] )
,   void*                               param
,   int                                 flags
,   int                                 consoleWidth
,   int                                 tabSize
,   int                                 blanksBetweenItems
);

/** [DEPRECATED]
 *
 * \deprecated Instead use clasp_showHeader()
 */
CLASP_CALL_DEPRECATED(int, "clasp_show_header() is deprecated and will be removed in a future release; use clasp_showHeader() instead")
clasp_show_header(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_specification_t const         specifications[]
,   clasp_char_t const*                 toolName
,   clasp_char_t const*                 summary
,   clasp_char_t const*                 copyright
,   clasp_char_t const*                 description
,   clasp_char_t const*                 usage
,   int                                 major
,   int                                 minor
,   int                                 revision
,   void                              (*pfnHeader)(clasp_diagnostic_context_t const*, clasp_usageinfo_t const* , clasp_specification_t const[] )
,   void*                               param
,   int                                 flags
);

/** [DEPRECATED]
 *
 * \deprecated Instead use clasp_showBody()
 */
CLASP_CALL_DEPRECATED(int, "clasp_show_body() is deprecated and will be removed in a future release; use clasp_showBody() instead")
clasp_show_body(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_specification_t const         specifications[]
,   void                              (*pfnBody)(clasp_diagnostic_context_t const*, clasp_usageinfo_t const* , clasp_specification_t const[] )
,   void*                               param
,   int                                 flags
,   int                                 consoleWidth
,   int                                 tabSize
,   int                                 blanksBetweenItems
);

/** [DEPRECATED]
 *
 * \deprecated Instead use clasp_showVersion()
 */
CLASP_CALL_DEPRECATED(int, "clasp_show_version() is deprecated and will be removed in a future release; use clasp_showVersion() instead")
clasp_show_version(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_char_t const*                 toolName
,   int                                 major
,   int                                 minor
,   int                                 revision
,   void                              (*pfnVersion)(clasp_diagnostic_context_t const*, clasp_usageinfo_t const* , clasp_specification_t const[] )
,   void*                               param
,   int                                 flags
);


/** [DEPRECATED] Stock function that shows version to a <code>FILE*</code>
 *
 * \deprecated Instead use clasp_showVersionByFILE()
 */
CLASP_CALL_DEPRECATED(void, "clasp_show_version_by_FILE() is deprecated and will be removed in a future release; use clasp_showVersionByFILE() instead")
clasp_show_version_by_FILE(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_usageinfo_t const*            info
,   clasp_specification_t const         specifications[]
);

/** [DEPRECATED] Stock function that shows header to a <code>FILE*</code>
 *
 * \deprecated Instead use clasp_showHeaderByFILE()
 */
CLASP_CALL_DEPRECATED(void, "clasp_show_header_by_FILE() is deprecated and will be removed in a future release; use clasp_showHeaderByFILE() instead")
clasp_show_header_by_FILE(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_usageinfo_t const*            info
,   clasp_specification_t const         specifications[]
);

/** [DEPRECATED] Stock function that shows body to a <code>FILE*</code>
 *
 * \deprecated Instead use clasp_showBodyByFILE()
 */
CLASP_CALL_DEPRECATED(void, "clasp_show_body_by_FILE() is deprecated and will be removed in a future release; use clasp_showBodyByFILE() instead")
clasp_show_body_by_FILE(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_usageinfo_t const*            info
,   clasp_specification_t const         specifications[]
);
#endif /* !CLASP_DOCUMENTATION_SKIP_SECTION */


/* ////////////////////////////////////////////////////////////////////// */

#ifdef __cplusplus

namespace clasp
{

# ifdef CLASP_DOCUMENTATION_SKIP_SECTION

#  include "./internal/shim_macros.h"
# else /* ? CLASP_DOCUMENTATION_SKIP_SECTION */

#  include <clasp/internal/shim_macros.h>
# endif /* CLASP_DOCUMENTATION_SKIP_SECTION */

    typedef ::clasp_alias_t                 alias_t;
    typedef ::clasp_argtype_t               argtype_t;
    typedef ::clasp_argument_t              argument_t;
    typedef ::clasp_arguments_t             arguments_t;
    typedef ::clasp_diagnostic_context_t    diagnostic_context_t;
    typedef ::clasp_slice_t                 slice_t;
    typedef ::clasp_specification_t         specification_t;

    inline
    int
    parseArguments(
        unsigned                            flags
    ,   int                                 argc
    ,   clasp_char_t*                       argv[]
    ,   specification_t const               specifications[]
    ,   clasp_diagnostic_context_t const*   ctxt
    ,   arguments_t const**                 args
    )
    {
        return clasp_parseArguments(flags, argc, argv, specifications, ctxt, args);
    }

    inline
    int
    parseArguments(
        unsigned                            flags
    ,   int                                 argc
    ,   clasp_char_t const* const           argv[]
    ,   specification_t const               specifications[]
    ,   clasp_diagnostic_context_t const*   ctxt
    ,   arguments_t const**                 args
    )
    {
        return clasp_parseArguments(flags, argc, const_cast<clasp_char_t**>(argv), specifications, ctxt, args);
    }

    inline
    void
    releaseArguments(
        arguments_t const* args
    )
    {
        clasp_releaseArguments(args);
    }

} /* namespace clasp */


/** A generic inserter function for clasp_argument_t into output streams
 *
 */
template <typename T_stm>
T_stm&
operator <<(
    T_stm&                  stm
,   clasp_argument_t const& arg
)
{
    switch (arg.type)
    {
    case CLASP_ARGTYPE_FLAG:

        stm << arg.resolvedName;
        break;
    case CLASP_ARGTYPE_OPTION:

        stm << arg.resolvedName << clasp_char_t('=') << arg.value;
        break;
    case CLASP_ARGTYPE_VALUE:

        stm << arg.value;
        break;
    default:

        break;
    }

    return stm;
}


# ifndef CLASP_DOCUMENTATION_SKIP_SECTION

namespace stlsoft
{
#ifdef CLASP_USE_WIDE_STRINGS

    inline size_t c_str_len_w(clasp_specification_t const& s)
    {
        return NULL == s.mappedArgument ? 0 : ::wcslen(s.mappedArgument);
    }
#else /* ? CLASP_USE_WIDE_STRINGS */

    inline size_t c_str_len_a(clasp_specification_t const& s)
    {
        return NULL == s.mappedArgument ? 0 : ::strlen(s.mappedArgument);
    }
#endif /* CLASP_USE_WIDE_STRINGS */

#ifdef CLASP_USE_WIDE_STRINGS

    inline wchar_t const* c_str_data_w(clasp_specification_t const& s)
#else /* ? CLASP_USE_WIDE_STRINGS */

    inline char const* c_str_data_a(clasp_specification_t const& s)
#endif /* CLASP_USE_WIDE_STRINGS */
    {
        return s.mappedArgument;
    }




#ifdef CLASP_USE_WIDE_STRINGS

    inline size_t c_str_len_w(clasp_slice_t const& s)
#else /* ? CLASP_USE_WIDE_STRINGS */

    inline size_t c_str_len_a(clasp_slice_t const& s)
#endif /* CLASP_USE_WIDE_STRINGS */
    {
        return s.len;
    }

#ifdef CLASP_USE_WIDE_STRINGS

    inline wchar_t const* c_str_data_w(clasp_slice_t const& s)
#else /* ? CLASP_USE_WIDE_STRINGS */

    inline char const* c_str_data_a(clasp_slice_t const& s)
#endif /* CLASP_USE_WIDE_STRINGS */
    {
        return s.ptr;
    }

#ifdef CLASP_USE_WIDE_STRINGS

    inline wchar_t const* c_str_ptr_w(clasp_slice_t const& s)
#else /* ? CLASP_USE_WIDE_STRINGS */

    inline char const* c_str_ptr_a(clasp_slice_t const& s)
#endif /* CLASP_USE_WIDE_STRINGS */
    {
        return s.ptr;
    }

    inline size_t c_str_len(clasp_slice_t const& s)
    {
#ifdef CLASP_USE_WIDE_STRINGS

        return c_str_len_w(s);
#else /* ? CLASP_USE_WIDE_STRINGS */

        return c_str_len_a(s);
#endif /* CLASP_USE_WIDE_STRINGS */
    }

#ifdef CLASP_USE_WIDE_STRINGS

    inline wchar_t const* c_str_ptr(clasp_slice_t const& s)
#else /* ? CLASP_USE_WIDE_STRINGS */

    inline char const* c_str_ptr(clasp_slice_t const& s)
#endif /* CLASP_USE_WIDE_STRINGS */
    {
#ifdef CLASP_USE_WIDE_STRINGS

        return c_str_ptr_w(s);
#else /* ? CLASP_USE_WIDE_STRINGS */

        return c_str_ptr_a(s);
#endif /* CLASP_USE_WIDE_STRINGS */
    }

#ifdef CLASP_USE_WIDE_STRINGS

    inline wchar_t const* c_str_data(clasp_slice_t const& s)
#else /* ? CLASP_USE_WIDE_STRINGS */

    inline char const* c_str_data(clasp_slice_t const& s)
#endif /* CLASP_USE_WIDE_STRINGS */
    {
#ifdef CLASP_USE_WIDE_STRINGS

        return c_str_data_w(s);
#else /* ? CLASP_USE_WIDE_STRINGS */

        return c_str_data_a(s);
#endif /* CLASP_USE_WIDE_STRINGS */
    }

} /* namespace stlsoft */
# endif /* !CLASP_DOCUMENTATION_SKIP_SECTION */
#endif /* __cplusplus */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !CLASP_INCL_CLASP_H_CLASP */

/* ///////////////////////////// end of file //////////////////////////// */

