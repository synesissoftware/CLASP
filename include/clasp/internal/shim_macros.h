/* /////////////////////////////////////////////////////////////////////////
 * File:    clasp/internal/shim_macros.h
 *
 * Purpose: Definitions of macros used internally in the library
 *          components
 *
 * Created: 5th December 2014
 * Updated: 12th July 2024
 *
 * Home:    https://github.com/synesissoftware/CLASP/
 *
 * Copyright (c) 2019-2024, Matthew Wilson and Synesis Information Systems
 * Copyright (c) 2014-2019, Matthew Wilson and Synesis Software
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


/** \file clasp/internal/shim_macros.h
 *
 * [C, C++] Definitions of macros used internally in the library components
 */

#ifndef CLASP_INCL_CLASP_INTERNAL_H_SHIM_MACROS
#define CLASP_INCL_CLASP_INTERNAL_H_SHIM_MACROS


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#ifndef CLASP_DOCUMENTATION_SKIP_SECTION
# include <clasp/clasp.h>
#endif /* !CLASP_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * macros
 */


/* /////////////////////////////////////////////////////////////////////////
 * compiler compatibility
 */

/* The Digital Mars and GCC compilers both exhibit strange behaviour (bugs?)
 * with respect to the invocation of shims.
 *
 * - DMC++ requires explicit qualification, even in the presence of a
 *    (local) using declaration
 * - GCC requires a local using declaration and *must not* have explicit
 *    qualification.
 *
 * - all other compilers work fine without any using declaration and with
 *    explicit qualification.
 *
 * As currently defined, we follow the GCC way (which works for all other
 * compilers, except DMC++), and explicitly qualify for DMC++.
 *
 */

#ifndef CLASP_DOCUMENTATION_SKIP_SECTION

/* 1. String access shims
 * ----------------------
 */

# ifdef CLASP_INVOKE_c_str_data_
#  undef CLASP_INVOKE_c_str_data_
# endif /* CLASP_INVOKE_c_str_data_ */
# ifdef CLASP_INVOKE_c_str_len_
#  undef CLASP_INVOKE_c_str_len_
# endif /* CLASP_INVOKE_c_str_len_ */
# ifdef CLASP_INVOKE_c_str_ptr_
#  undef CLASP_INVOKE_c_str_ptr_
# endif /* CLASP_INVOKE_c_str_ptr_ */
# ifdef CLASP_INVOKE_c_str_ptr_null_
#  undef CLASP_INVOKE_c_str_ptr_null_
# endif /* CLASP_INVOKE_c_str_ptr_null_ */

# ifdef CLASP_INVOKE_SHIM_PAIR_
#  undef CLASP_INVOKE_SHIM_PAIR_
# endif /* CLASP_INVOKE_SHIM_PAIR_ */
# ifdef CLASP_c_str_data_name_
#  undef CLASP_c_str_data_name_
# endif /* CLASP_c_str_data_name_ */
# ifdef CLASP_c_str_ptr_name_
#  undef CLASP_c_str_ptr_name_
# endif /* CLASP_c_str_ptr_name_ */
# ifdef CLASP_c_str_ptr_null_name_
#  undef CLASP_c_str_ptr_null_name_
# endif /* CLASP_c_str_ptr_null_name_ */

# ifdef CLASP_USE_WIDE_STRINGS
#  define CLASP_c_str_data_name_                            c_str_data_w
#  define CLASP_c_str_len_name_                             c_str_len_w
#  define CLASP_c_str_ptr_name_                             c_str_ptr_w
#  define CLASP_c_str_ptr_null_name_                        c_str_ptr_null_w
# else /* ? CLASP_USE_WIDE_STRINGS */
#  define CLASP_c_str_data_name_                            c_str_data_a
#  define CLASP_c_str_len_name_                             c_str_len_a
#  define CLASP_c_str_ptr_name_                             c_str_ptr_a
#  define CLASP_c_str_ptr_null_name_                        c_str_ptr_null_a
# endif /* CLASP_USE_WIDE_STRINGS */

# if defined(STLSOFT_COMPILER_IS_DMC)
#  define CLASP_INVOKE_c_str_data_(x)                       stlsoft::CLASP_c_str_data_name_(x)
#  define CLASP_INVOKE_c_str_len_(x)                        stlsoft::CLASP_c_str_len_name_(x)
#  define CLASP_INVOKE_c_str_ptr_(x)                        stlsoft::CLASP_c_str_ptr_name_(x)
#  define CLASP_INVOKE_c_str_ptr_null_(x)                   stlsoft::CLASP_c_str_ptr_null_name_(x)
#  define CLASP_DECLARE_c_str_ptr_()                        stlsoft_static_cast(void, 0)
#  define CLASP_DECLARE_c_str_ptr_null_()                   stlsoft_static_cast(void, 0)
#  define CLASP_DECLARE_c_str_datalen_PAIR_()               stlsoft_static_cast(void, 0)
# elif 0 || \
       defined(STLSOFT_COMPILER_IS_CLANG) || \
       defined(STLSOFT_COMPILER_IS_GCC) || \
       0
#  define CLASP_INVOKE_c_str_data_(x)                       CLASP_c_str_data_name_(x)
#  define CLASP_INVOKE_c_str_len_(x)                        CLASP_c_str_len_name_(x)
#  define CLASP_INVOKE_c_str_ptr_(x)                        CLASP_c_str_ptr_name_(x)
#  define CLASP_INVOKE_c_str_ptr_null_(x)                   CLASP_c_str_ptr_null_name_(x)
#  define CLASP_DECLARE_c_str_ptr_()                        using ::stlsoft::CLASP_c_str_ptr_name_
#  define CLASP_DECLARE_c_str_ptr_null_()                   using ::stlsoft::CLASP_c_str_ptr_null_name_
#  define CLASP_DECLARE_c_str_datalen_PAIR_()               using ::stlsoft::CLASP_c_str_data_name_; using ::stlsoft::CLASP_c_str_len_name_
# else /* ? compiler */
#  define CLASP_INVOKE_c_str_data_(x)                       CLASP_c_str_data_name_(x)
#  define CLASP_INVOKE_c_str_len_(x)                        CLASP_c_str_len_name_(x)
#  define CLASP_INVOKE_c_str_ptr_(x)                        CLASP_c_str_ptr_name_(x)
#  define CLASP_INVOKE_c_str_ptr_null_(x)                   CLASP_c_str_ptr_null_name_(x)
#  define CLASP_DECLARE_c_str_ptr_()                        using ::stlsoft::CLASP_c_str_ptr_name_
#  define CLASP_DECLARE_c_str_ptr_null_()                   using ::stlsoft::CLASP_c_str_ptr_null_name_
#  define CLASP_DECLARE_c_str_datalen_PAIR_()               using ::stlsoft::CLASP_c_str_data_name_; using ::stlsoft::CLASP_c_str_len_name_
# endif /* compiler */
# define CLASP_INVOKE_SHIM_PAIR_(x)                         CLASP_INVOKE_c_str_data_(x), CLASP_INVOKE_c_str_len_(x)


/* 2. Conversion shims
 * -------------------
 */



/* 3. Action shims
 * ---------------
 */



/* 4. Internal helpers
 * -------------------
 */


#endif /* !CLASP_DOCUMENTATION_SKIP_SECTION */


/* /////////////////////////////////////////////////////////////////////////
 * inclusion control
 */

#ifdef STLSOFT_PPF_pragma_once_SUPPORT
# pragma once
#endif /* STLSOFT_PPF_pragma_once_SUPPORT */

#endif /* CLASP_INCL_CLASP_INTERNAL_H_SHIM_MACROS */


/* ///////////////////////////// end of file //////////////////////////// */

