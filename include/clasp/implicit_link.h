/* /////////////////////////////////////////////////////////////////////////
 * File:    clasp/implicit_link.h
 *
 * Purpose: Implicit linking for CLASP
 *
 * Created: 31st July 2008
 * Updated: 2nd February 2024
 *
 * Home:    https://github.com/synesissoftware/CLASP/
 *
 * Copyright (c) 2019-2024, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 2008-2019, Matthew Wilson and Synesis Software
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


/** \file clasp/implicit_link.h
 *
 * \brief [C, C++] Implicit linking for CLASP.
 */

#ifndef CLASP_INCL_CLASP_H_IMPLICIT_LINK
#define CLASP_INCL_CLASP_H_IMPLICIT_LINK

/* /////////////////////////////////////////////////////////////////////////
 * version information
 */

#ifndef CLASP_DOCUMENTATION_SKIP_SECTION
# define CLASP_VER_CLASP_H_IMPLICIT_LINK_MAJOR      2
# define CLASP_VER_CLASP_H_IMPLICIT_LINK_MINOR      0
# define CLASP_VER_CLASP_H_IMPLICIT_LINK_REVISION   4
# define CLASP_VER_CLASP_H_IMPLICIT_LINK_EDIT       22
#endif /* !CLASP_DOCUMENTATION_SKIP_SECTION */

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef CLASP_INCL_CLASP_H_CLASP
# include <clasp/clasp.h>
#endif /* !CLASP_INCL_CLASP_H_CLASP */

/* /////////////////////////////////////////////////////////////////////////
 * macros and definitions
 */

#define CLASP_STRINGIZE_(x)     #x
#define CLASP_STRINGIZE(x)      CLASP_STRINGIZE_(x)

/* /////////////////////////////////////////////////////////////////////////
 * architecture discrimination
 */

#ifdef CLASP_ARCH_IS_X86_
# undef CLASP_ARCH_IS_X86_
#endif /* CLASP_ARCH_IS_X86_ */
#ifdef CLASP_ARCH_IS_X64_
# undef CLASP_ARCH_IS_X64_
#endif /* CLASP_ARCH_IS_X64_ */
#ifdef CLASP_ARCH_IS_IA64_
# undef CLASP_ARCH_IS_IA64_
#endif /* CLASP_ARCH_IS_IA64_ */


#if defined(CLASP_ARCH_IS_IA64) || \
    defined(_M_IA64)
# define CLASP_ARCH_IS_IA64_
#elif defined(CLASP_ARCH_IS_X64) || \
      defined(_M_X64) || \
      defined(_M_AMD64)
# define CLASP_ARCH_IS_X64_
#elif defined(CLASP_ARCH_IS_X86) || \
      defined(_M_IX86)
# define CLASP_ARCH_IS_X86_
#else /* ? _M_?? */
#endif /* _M_?? */

/* /////////////////////////////////////////////////////////////////////////
 * implicit linking
 */

#if defined(_WIN32) || \
    defined(_WIN64)

# if defined(__BORLANDC__) || \
     /* defined(__DMC__) || */ \
     defined(__INTEL_COMPILER) || \
     defined(__MWERKS__) || \
     defined(_MSC_VER)
#  if !defined(__COMO__)
#   define CLASP_IMPLICIT_LINK_SUPPORT
#  endif /* compiler */
# endif /* compiler */

# if defined(CLASP_IMPLICIT_LINK_SUPPORT) && \
     defined(CLASP_NO_IMPLICIT_LINK)
#  undef CLASP_IMPLICIT_LINK_SUPPORT
# endif /* CLASP_IMPLICIT_LINK_SUPPORT && CLASP_NO_IMPLICIT_LINK */

# if defined(CLASP_IMPLICIT_LINK_SUPPORT)

  /* prefix */

#  define CLASP_IMPL_LINK_PREFIX

  /* library basename */

#  define CLASP_IMPL_LINK_LIBRARY_BASENAME                  "systemtools.clasp"

  /* major version */

#  define CLASP_IMPL_LINK_MAJOR_VERSION                     "." CLASP_STRINGIZE(CLASP_VER_MAJOR)

  /* module name */

#  define CLASP_IMPL_LINK_MODULE_NAME                       ".core"

#  ifdef CLASP_CMDLINE_ARGS_NO_RECLS_ON_WINDOWS
#   define CLASP_IMPL_LINK_RECLS_VARIANT                    ".norecls"
#  else /* ? CLASP_CMDLINE_ARGS_NO_RECLS_ON_WINDOWS */
#   define CLASP_IMPL_LINK_RECLS_VARIANT                    ""
#  endif /* CLASP_CMDLINE_ARGS_NO_RECLS_ON_WINDOWS */

  /* compiler tag */

#  if defined(__BORLANDC__)
#   if __BORLANDC__ == 0x0550
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "bc55"
#   elif (__BORLANDC__ == 0x0551)
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "bc551"
#   elif (__BORLANDC__ == 0x0560)
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "bc56"
#   elif (__BORLANDC__ == 0x0564)
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "bc564"
#   elif (__BORLANDC__ == 0x0582)
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "bc582"
#   elif (0x0590 == (__BORLANDC__ & 0xfff0))
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "bc59x"
#   elif (0x0610 == (__BORLANDC__ & 0xfff0))
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "bc61x"
#   else /* ? __BORLANDC__ */
#    error Unrecognised value of __BORLANDC__
#   endif /* __BORLANDC__ */

/*
#  elif defined(__DMC__)
#   define CLASP_IMPL_LINK_COMPILER_NAME                    "dm"
 */

#  elif defined(__INTEL_COMPILER)
#   if __INTEL_COMPILER == 600
#    define   CLASP_IMPL_LINK_COMPILER_NAME                 "icl6"
#   elif __INTEL_COMPILER == 700
#    define   CLASP_IMPL_LINK_COMPILER_NAME                 "icl7"
#   elif __INTEL_COMPILER == 800
#    define   CLASP_IMPL_LINK_COMPILER_NAME                 "icl8"
#   elif __INTEL_COMPILER == 900
#    define   CLASP_IMPL_LINK_COMPILER_NAME                 "icl9"
#   elif __INTEL_COMPILER == 1000
#    define   CLASP_IMPL_LINK_COMPILER_NAME                 "icl10"
#   elif __INTEL_COMPILER == 1100
#    define   CLASP_IMPL_LINK_COMPILER_NAME                 "icl11"
#   elif __INTEL_COMPILER == 1200
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "icl12"
#   else /* ? __INTEL_COMPILER */
#    error Intel C/C++ version not supported
#   endif /* __INTEL_COMPILER */

#  elif defined(__MWERKS__)
#   if ((__MWERKS__ & 0xFF00) == 0x2400)
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "cw7"
#   elif ((__MWERKS__ & 0xFF00) == 0x3000)
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "cw8"
#   elif ((__MWERKS__ & 0xFF00) == 0x3200)
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "cw9"
#   else /* ? __MWERKS__ */
#    error CodeWarrior version not supported
#   endif /* __MWERKS__ */

#  elif defined(_MSC_VER)
#   if _MSC_VER == 1000
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "vc4"
#   elif _MSC_VER == 1020
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "vc42"
#   elif _MSC_VER == 1100
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "vc5"
#   elif _MSC_VER == 1200
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "vc6"
#   elif _MSC_VER == 1300
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "vc7"
#   elif _MSC_VER == 1310
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "vc71"
#   elif _MSC_VER == 1400
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "vc8"
#   elif _MSC_VER == 1500
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "vc9"
#   elif _MSC_VER == 1600
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "vc10"
#   elif _MSC_VER == 1700
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "vc11"
#   elif _MSC_VER == 1800
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "vc12"
#   elif _MSC_VER == 1900
#    define CLASP_IMPL_LINK_COMPILER_NAME                   "vc14"
#   elif _MSC_VER >= 1910
#    if 0
#    elif _MSC_VER < 1920
#     define CLASP_IMPL_LINK_COMPILER_NAME                  "vc15"
#    elif _MSC_VER <= 1929
#     define CLASP_IMPL_LINK_COMPILER_NAME                  "vc16"
#    else
#     error Visual C++ version that is >= vc16 is not recognised
#    endif
#   else /* ? _MSC_VER */
#    error Visual C++ version not supported
#   endif /* _MSC_VER */

#  else /* ? compiler */
#   error Unrecognised compiler
#  endif /* compiler */


  /* operating system tag */

#  if defined(_STLSOFT_FORCE_ANY_COMPILER) && \
      defined(CLASP_PLATFORM_IS_UNIX) && \
      defined(_WIN32)
#   define CLASP_IMPL_LINK_OS_TAG                           ".unix"
#  endif /* pseudo UNIX */

#  if !defined(CLASP_IMPL_LINK_OS_TAG)
#   define CLASP_IMPL_LINK_OS_TAG                           ""
#  endif /* !CLASP_IMPL_LINK_OS_TAG */


  /* architecture tag */

#  if defined(CLASP_ARCH_IS_X86_)
#   define CLASP_IMPL_LINK_ARCH_TAG                         ""
#  elif defined(CLASP_ARCH_IS_X64_)
#   define CLASP_IMPL_LINK_ARCH_TAG                         ".x64"
#  elif defined(CLASP_ARCH_IS_IA64_)
#   define CLASP_IMPL_LINK_ARCH_TAG                         ".ia64"
#  endif /* arch */

#  if !defined(CLASP_IMPL_LINK_ARCH_TAG)
#   define CLASP_IMPL_LINK_ARCH_TAG                         ""
#  endif /* !CLASP_IMPL_LINK_ARCH_TAG */


  /* encoding tag */

#  if defined(CLASP_USE_WIDE_STRINGS)
#   define CLASP_IMPL_LINK_ENCODING_TAG                     ".widestring"
#  else /* ? CLASP_USE_WIDE_STRINGS */
#   define CLASP_IMPL_LINK_ENCODING_TAG                     ""
#  endif /* CLASP_USE_WIDE_STRINGS */


  /* threading tag */

#  if defined(__MT__) || \
      defined(_REENTRANT) || \
      defined(_MT)
#   if defined(_DLL) || \
       defined(__DLL)
#    define CLASP_IMPL_LINK_THREADING_TAG                   ".dll"
#   else /* ? dll */
#    define CLASP_IMPL_LINK_THREADING_TAG                   ".mt"
#   endif /* dll */
#  else /* ? mt */
#    define CLASP_IMPL_LINK_THREADING_TAG                   ""
#  endif /* mt */


  /* NoX */

#  if defined(CLASP_CF_NOX) && 0 /* CLASP is written in C, so is always NoX */
#   define CLASP_IMPL_LINK_NOX_TYPE                         ".nox"
#  else /* ? CLASP_CF_NOX */
#   define CLASP_IMPL_LINK_NOX_TYPE                         ""
#  endif /* CLASP_CF_NOX */


  /* debug tag */

#  if defined(CLASP_VARIANT_TEST)
#   define CLASP_IMPL_LINK_DEBUG_TYPE                       ".test"
#  elif !defined(NDEBUG) && \
        defined(_DEBUG)
#   define CLASP_IMPL_LINK_DEBUG_TAG                        ".debug"
#  else /* ? debug */
#   define CLASP_IMPL_LINK_DEBUG_TAG                        ""
#  endif /* debug */


  /* suffix */

#  define CLASP_IMPL_LINK_SUFFIX                            ".lib"


   /* Library name is:
    *
    * [lib]<library-basename>.<major-version>.<module-name>.<compiler-name>[.<os-arch-tag>][.<char-encoding-tag>][.<threading-tag>][.<nox-tag>][.<debug-tag>].{a|lib}
    */

#  define CLASP_IMPL_LINK_LIBRARY_NAME              \
                                                    \
    CLASP_IMPL_LINK_PREFIX \
    CLASP_IMPL_LINK_LIBRARY_BASENAME \
    CLASP_IMPL_LINK_MAJOR_VERSION \
    CLASP_IMPL_LINK_MODULE_NAME \
    CLASP_IMPL_LINK_RECLS_VARIANT \
    "." CLASP_IMPL_LINK_COMPILER_NAME \
    CLASP_IMPL_LINK_OS_TAG \
    CLASP_IMPL_LINK_ARCH_TAG \
    CLASP_IMPL_LINK_ENCODING_TAG \
    CLASP_IMPL_LINK_THREADING_TAG \
    CLASP_IMPL_LINK_NOX_TYPE \
    CLASP_IMPL_LINK_DEBUG_TAG \
    CLASP_IMPL_LINK_SUFFIX


#  pragma message("lib: " CLASP_IMPL_LINK_LIBRARY_NAME)

#  pragma comment(lib, CLASP_IMPL_LINK_LIBRARY_NAME)

# endif /* CLASP_IMPLICIT_LINK_SUPPORT */

#endif /* Win-32 || Win-64 */

/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_CF_PRAGMA_ONCE_SUPPORT
# pragma once
#endif /* STLSOFT_CF_PRAGMA_ONCE_SUPPORT */

#endif /* !CLASP_INCL_CLASP_H_IMPLICIT_LINK */

/* ///////////////////////////// end of file //////////////////////////// */

