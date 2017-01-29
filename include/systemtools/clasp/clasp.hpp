/* /////////////////////////////////////////////////////////////////////////
 * File:        systemtools/clasp/clasp.hpp
 *
 * Purpose:     C++ layer for the CLASP library.
 *
 * Created:     31st July 2008
 * Updated:     27th January 2017
 *
 * Home:        http://synesis.com.au/software
 *
 * Copyright (c) 2008-2017, Matthew Wilson
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


/** \file systemtools/clasp/clasp.hpp
 *
 * \brief [C++-only] C++ layer for the CLASP library.
 */

#ifndef SYSTEMTOOLS_INCL_SYSTEMTOOLS_CLASP_HPP_CLASP
#define SYSTEMTOOLS_INCL_SYSTEMTOOLS_CLASP_HPP_CLASP

/* /////////////////////////////////////////////////////////////////////////
 * Version information
 */

#ifndef SYSTEMTOOLS_DOCUMENTATION_SKIP_SECTION
# define SYSTEMTOOLS_VER_SYSTEMTOOLS_CLASP_HPP_CLASP_MAJOR    2
# define SYSTEMTOOLS_VER_SYSTEMTOOLS_CLASP_HPP_CLASP_MINOR    9
# define SYSTEMTOOLS_VER_SYSTEMTOOLS_CLASP_HPP_CLASP_REVISION 2
# define SYSTEMTOOLS_VER_SYSTEMTOOLS_CLASP_HPP_CLASP_EDIT     55
#endif /* !SYSTEMTOOLS_DOCUMENTATION_SKIP_SECTION */

/* /////////////////////////////////////////////////////////////////////////
 * Includes
 */

/* CLASP header files */
#include <systemtools/clasp/clasp.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>
#if _STLSOFT_VER < 0x010982ff
# error This requires STLSoft 1.9.130 or later
#endif
#ifdef CLASP_USE_WIDE_STRINGS
# include <stlsoft/conversion/char_conversions.hpp>
#endif /* CLASP_USE_WIDE_STRINGS */
#include <stlsoft/conversion/integer_to_string.hpp>
#include <stlsoft/meta/is_integral_type.hpp>
#include <stlsoft/meta/is_numeric_type.hpp>
#include <stlsoft/meta/is_pointer_type.hpp>
#include <stlsoft/shims/access/string/std/c_string.h>
#if 0
#elif 0 ||\
      defined(STLSOFT_COMPILER_IS_GCC) || \
      0
# include <stlsoft/shims/access/string.hpp>
#endif

#include <stdexcept>
#include <string>

/* /////////////////////////////////////////////////////////////////////////
 * Namespace
 */

namespace clasp
{

/* /////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

typedef std::basic_string<clasp_char_t>     clasp_string_t;

/* /////////////////////////////////////////////////////////////////////////
 * Exception classes
 */

/// Root class for all CLASP exceptions
class clasp_exception
    : public std::runtime_error
{
public: // Member Types
    typedef std::runtime_error  parent_class_type;
    typedef std::string         message_string_type;
    typedef clasp_string_t      string_type;

public: // Construction
    explicit clasp_exception(message_string_type const& message)
        : parent_class_type(message)
    {}
    virtual ~clasp_exception() stlsoft_throw_0() = 0;
};

/// Root class for all CLASP argument exceptions
class argument_exception
    : public clasp_exception
{
public: // Member Types
    typedef clasp_exception     parent_class_type;
    typedef argument_exception  class_type;

public: // Construction
    explicit argument_exception(message_string_type const& message, string_type const& optionName)
        : parent_class_type(calc_message_(message, optionName))
        , optionName(optionName)
    {}
    virtual ~argument_exception() stlsoft_throw_0() = 0;
private:
    class_type& operator =(class_type const&);

public:
    const string_type optionName;

private:
    static
    message_string_type
    calc_message_(
        message_string_type const&  message
    ,   string_type const&          optionName
    )
    {
        if(optionName.empty())
        {
            return message;
        }
        else
        {

            message_string_type m;

            m.reserve(2 + message.size() + optionName.size());

            m.append(message);
            m.append(1u, ':');
            m.append(1u, ' ');
#ifdef CLASP_USE_WIDE_STRINGS
            m.append(stlsoft::w2m(optionName));
#else /* ? CLASP_USE_WIDE_STRINGS */
            m.append(optionName);
#endif /* CLASP_USE_WIDE_STRINGS */

            return m;
        }
    }
};

/// Thrown if a required option is not specified
class missing_option_exception
    : public argument_exception
{
public: // Member Types
    typedef argument_exception          parent_class_type;
    typedef missing_option_exception    class_type;

public: // Construction
    explicit missing_option_exception(message_string_type const& message, string_type const& optionName)
        : parent_class_type(message, optionName)
    {}
private:
    class_type& operator =(class_type const&);
};

/// Thrown if an option is missing its value
class missing_option_value_exception
    : public argument_exception
{
public: // Member Types
    typedef argument_exception  parent_class_type;

public: // Construction
    explicit missing_option_value_exception(message_string_type const& message, string_type const& optionName)
        : parent_class_type(message, optionName)
    {}
};

/// Thrown if any arguments have an invalid value
class invalid_option_value_exception
    : public argument_exception
{
public: // Member Types
    typedef argument_exception  parent_class_type;

public: // Construction
    explicit invalid_option_value_exception(message_string_type const& message, string_type const& optionName)
        : parent_class_type(message, optionName)
    {}
};

/// Thrown if any unused arguments remain
class unused_argument_exception
    : public argument_exception
{
public: // Member Types
    typedef argument_exception          parent_class_type;
    typedef unused_argument_exception   class_type;

public: // Construction
    explicit unused_argument_exception(message_string_type const& message, string_type const& optionName)
        : parent_class_type(message, optionName)
    {}
};

/// Thrown if any arguments are unknown
class unrecognised_argument_exception
    : public argument_exception
{
public: // Member Types
    typedef argument_exception              parent_class_type;
    typedef unrecognised_argument_exception class_type;

public: // Construction
    explicit unrecognised_argument_exception(message_string_type const& message, string_type const& optionName)
        : parent_class_type(message, optionName)
    {}
};

/* /////////////////////////////////////////////////////////////////////////
 * Exceptions implementation
 */

inline /* virtual */ clasp_exception::~clasp_exception() stlsoft_throw_0() /* = 0 */
{}

inline /* virtual */ argument_exception::~argument_exception() stlsoft_throw_0() /* = 0 */
{}

/* /////////////////////////////////////////////////////////////////////////
 * Implementation
 */

#ifndef SYSTEMTOOLS_DOCUMENTATION_SKIP_SECTION

namespace ximpl
{
    /* The atoi_helper and atol_helper classes were removed from
     * STLSoft 1.12+, as they are superceded by the flecxx project's
     * facilities; but rather than introduce another dependency the
     * original classes are borrowed into CLASP here with permission
     * (which was easy to get, since I am the author of both).
     */

    struct atoi_helper
    {
        static int call(char const* s)
        {
            return ::atoi(s);
        }
        static int call(wchar_t const* s)
        {
#ifdef STLSOFT_STD_CSTDLIB_WTOI_SUPPORTED
            return ::_wtoi(s);
#else /* ? STLSOFT_STD_CSTDLIB_WTOI_SUPPORTED */
            return static_cast<int>(::wcstol(s, NULL, 0));
#endif /* STLSOFT_STD_CSTDLIB_WTOI_SUPPORTED */
        }
    };

    struct atol_helper
    {
        static long call(char const* s)
        {
            return ::atol(s);
        }
        static long call(wchar_t const* s)
        {
#ifdef STLSOFT_STD_CSTDLIB_WTOL_SUPPORTED
            return ::_wtol(s);
#else /* ? STLSOFT_STD_CSTDLIB_WTOL_SUPPORTED */
            return ::wcstol(s, NULL, 0);
#endif /* STLSOFT_STD_CSTDLIB_WTOL_SUPPORTED */
        }
    };

    struct atoul_helper
    {
        static unsigned long call(char const* s)
        {
            return ::strtoul(s, NULL, 0);
        }
        static long call(wchar_t const* s)
        {
            return ::wcstoul(s, NULL, 0);
        }
    };

    struct strtod_helper
    {
        static double call(char const* s, char** endptr)
        {
            return ::strtod(s, endptr);
        }
        static double call(wchar_t const* s, wchar_t** endptr)
        {
            return ::wcstod(s, endptr);
        }
    };




    template <typename I>
    struct integer_conversion_traits_;

    STLSOFT_TEMPLATE_SPECIALISATION
    struct integer_conversion_traits_<int>
    {
    public:
        enum { allowNegatives = 1 };

        static int convert(clasp_char_t const* str)
        {
            return atoi_helper::call(str);
        }
    };

#ifdef _WIN64
    STLSOFT_TEMPLATE_SPECIALISATION
    struct integer_conversion_traits_<unsigned>
    {
    public:
        enum { allowNegatives = 1 };

        static unsigned convert(clasp_char_t const* str)
        {
            return atol_helper::call(str);
        }
    };
#endif

    STLSOFT_TEMPLATE_SPECIALISATION
    struct integer_conversion_traits_<long>
    {
    public:
        enum { allowNegatives = 1 };

        static int convert(clasp_char_t const* str)
        {
            return atol_helper::call(str);
        }
    };

    STLSOFT_TEMPLATE_SPECIALISATION
    struct integer_conversion_traits_<size_t>
    {
    public:
        enum { allowNegatives = 0 };

        static size_t convert(clasp_char_t const* str)
        {
            return atoul_helper::call(str);
        }
    };

    struct boolean_conversion_traits_
    {
        static bool convert(clasp_slice_t const& str, bool* wasStrictlyCorrect = NULL)
        {
            bool  wasStrictlyCorrect_;

            if(NULL == wasStrictlyCorrect)
            {
              wasStrictlyCorrect = &wasStrictlyCorrect_;
            }

            *wasStrictlyCorrect = false;

            if(0 == str.len)
            {
              return true;
            }

            *wasStrictlyCorrect = true;

            switch(str.ptr[0])
            {
                /* Affirmative */
                case    'Y':
                case    'y':
                    switch(str.ptr[1])
                    {
                        case    '\0':
                            return true;
                        case    'E':
                        case    'e':
                            switch(str.ptr[2])
                            {
                                case    'S':
                                case    's':
                                    if('\0' == str.ptr[3])
                                    {
                                        return true;
                                    }
                                    break;
                            }
                            break;
                    }
                    break;
                case    'T':
                case    't':
                    switch(str.ptr[1])
                    {
                        case    '\0':
                            return true;
                        case    'R':
                        case    'r':
                            switch(str.ptr[2])
                            {
                                case    'U':
                                case    'u':
                                    switch(str.ptr[3])
                                    {
                                        case    'E':
                                        case    'e':
                                            if('\0' == str.ptr[4])
                                            {
                                                return true;
                                            }
                                            break;
                                    }
                                    break;
                            }
                            break;
                    }
                    break;

                /* Negative */
                case    'N':
                case    'n':
                    switch(str.ptr[1])
                    {
                        case    '\0':
                            return false;
                        case    'O':
                        case    'o':
                            if('\0' == str.ptr[2])
                            {
                                return false;
                            }
                            break;
                    }
                    break;
                case    'F':
                case    'f':
                    switch(str.ptr[1])
                    {
                        case    '\0':
                            return false;
                        case    'A':
                        case    'a':
                            switch(str.ptr[2])
                            {
                                case    'L':
                                case    'l':
                                    switch(str.ptr[3])
                                    {
                                        case    'S':
                                        case    's':
                                            switch(str.ptr[4])
                                            {
                                                case    'E':
                                                case    'e':
                                                    if('\0' == str.ptr[5])
                                                    {
                                                        return false;
                                                    }
                                                    break;
                                            }
                                    }
                            }
                    }
                    break;

                default:
                    break;
            }

            *wasStrictlyCorrect = false;

            return false;
        }
    };

    inline
    clasp_char_t const*
    empty_string_()
    {
        static clasp_char_t const s_empty[1] = { '\0' };

        return s_empty;
    }

    inline
    void
    throw_missing_option_exception_(
        clasp_char_t const* optionName
    ,   char const*         missingMessage
    )
    {
        char const* defaultMessage = "required option is not found";

        if( NULL != missingMessage &&
            '\0' != missingMessage[0])
        {
            defaultMessage  =   missingMessage;
            optionName      =   empty_string_();
        }

        throw missing_option_exception(defaultMessage, optionName);
    }

    inline
    void
    throw_missing_option_value_exception_(
        clasp_char_t const* optionName
    ,   char const*         missingMessage
    )
    {
        char const* defaultMessage = "value is missing for option";

        if( NULL != missingMessage &&
            '\0' != missingMessage[0])
        {
            defaultMessage  =   missingMessage;
            optionName      =   empty_string_();
        }

        throw missing_option_value_exception(defaultMessage, optionName);
    }

    inline
    void
    throw_invalid_option_value_exception_(
        char const*         message
    ,   clasp_char_t const* optionName
    )
    {
        throw invalid_option_value_exception(message, optionName);
    }

    template <int N_allowNegatives>
    inline
    void
    throw_invalid_option_value_exception_if_(
        char const*         message
    ,   clasp_char_t const* optionName
    )
    {
        throw_invalid_option_value_exception_(message, optionName);
    }

    template <>
    inline
    void
    throw_invalid_option_value_exception_if_<0>(
        char const*         /*message*/
    ,   clasp_char_t const* /*optionName*/
    )
    {}

    template <typename I>
    bool check_option_integer_(
        clasp_arguments_t const*    args
    ,   bool                        ignoreUsed
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   I*                          result
    ,   I const&                    defaultValue
    )
    {
        { for(size_t i = 0; i != args->numOptions; ++i)
        {
            clasp_argument_t const& arg = args->options[i];

            if( ignoreUsed &&
                clasp_argumentIsUsed(args, &arg))
            {
                continue;
            }

            if( arg.resolvedName.len == optionNameLen &&
                0 == ::memcmp(arg.resolvedName.ptr, optionName, optionNameLen * sizeof(clasp_char_t)))
            {
                clasp_useArgument(args, &arg);

                switch(arg.value.ptr[0])
                {
                    case    '-':
                        throw_invalid_option_value_exception_if_<0 != integer_conversion_traits_<I>::allowNegatives>("value may not be negative for option", optionName);
                        break;
                    case    '0':
                    case    '1':
                    case    '2':
                    case    '3':
                    case    '4':
                    case    '5':
                    case    '6':
                    case    '7':
                    case    '8':
                    case    '9':
                    case    '+':
                        *result = integer_conversion_traits_<I>::convert(arg.value.ptr);
                        return true;
                    default:
                        throw_invalid_option_value_exception_("value is not an integer for option", optionName);
                        break;
                }
            }
        }}

        *result = defaultValue;

        return false;
    }

    template <typename I>
    void
    require_option_integer_(
        clasp_arguments_t const*    args
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   I*                          result
    ,   char const*                 missingMessage
    )
    {
        { for(size_t i = 0; i != args->numOptions; ++i)
        {
            clasp_argument_t const& arg = args->options[i];

            if( arg.resolvedName.len == optionNameLen &&
                0 == ::memcmp(arg.resolvedName.ptr, optionName, optionNameLen * sizeof(clasp_char_t)))
            {
                clasp_useArgument(args, &arg);

                if(0 == arg.value.len)
                {
                    throw_missing_option_value_exception_(optionName, missingMessage);
                }
                else
                {
                    switch(arg.value.ptr[0])
                    {
                        case    '-':
                            throw_invalid_option_value_exception_if_<0 != integer_conversion_traits_<I>::allowNegatives>("value may not be negative for option", optionName);
                            break;
                        case    '0':
                        case    '1':
                        case    '2':
                        case    '3':
                        case    '4':
                        case    '5':
                        case    '6':
                        case    '7':
                        case    '8':
                        case    '9':
                        case    '+':
                            *result = integer_conversion_traits_<I>::convert(arg.value.ptr);
                            return;
                        default:
                            throw_invalid_option_value_exception_("value is not an integer for option", optionName);
                            break;
                    }
                }
            }
        }}

        throw_missing_option_exception_(optionName, missingMessage);
    }

    inline
    bool
    check_option_real_(
        clasp_arguments_t const*    args
    ,   bool                        ignoreUsed
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   double*                     result
    ,   double const&               defaultValue
    )
    {
        { for(size_t i = 0; i != args->numOptions; ++i)
        {
            clasp_argument_t const& arg = args->options[i];

            if( ignoreUsed &&
                clasp_argumentIsUsed(args, &arg))
            {
                continue;
            }

            if( arg.resolvedName.len == optionNameLen &&
                0 == ::memcmp(arg.resolvedName.ptr, optionName, optionNameLen * sizeof(clasp_char_t)))
            {
                clasp_useArgument(args, &arg);

                if(0 == arg.value.len)
                {
                    break;
                }
                else
                {
                    clasp_char_t*   endptr;
                    double          res = strtod_helper::call(arg.value.ptr, &endptr);

                    if( NULL != endptr &&
                        endptr != arg.value.ptr + arg.value.len)
                    {
                        throw_invalid_option_value_exception_("value is not a real number for option", optionName);
                    }

                    *result = res;

                    return true;
                }
            }
        }}

        *result = defaultValue;

        return false;
    }

    inline
    void
    require_option_real_(
        clasp_arguments_t const*    args
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   double*                     result
    ,   char const*                 missingMessage
    )
    {
        { for(size_t i = 0; i != args->numOptions; ++i)
        {
            clasp_argument_t const& arg = args->options[i];

            if( arg.resolvedName.len == optionNameLen &&
                0 == ::memcmp(arg.resolvedName.ptr, optionName, optionNameLen * sizeof(clasp_char_t)))
            {
                clasp_useArgument(args, &arg);

                if(0 == arg.value.len)
                {
                    throw_missing_option_value_exception_(optionName, missingMessage);
                }
                else
                {
                    clasp_char_t*   endptr;
                    double          res = strtod_helper::call(arg.value.ptr, &endptr);

                    if( NULL != endptr &&
                        endptr != arg.value.ptr + arg.value.len)
                    {
                        throw_invalid_option_value_exception_("value is not a real number for option", optionName);
                    }

                    *result = res;

                    return;
                }
            }
        }}

        throw_missing_option_exception_(optionName, missingMessage);
    }

    inline
    void
    require_option_cstring_(
        clasp_arguments_t const*    args
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   clasp_char_t const**        result
    ,   char const*                 missingMessage
    )
    {
        { for(size_t i = 0; i != args->numOptions; ++i)
        {
            clasp_argument_t const& arg = args->options[i];

            if( arg.resolvedName.len == optionNameLen &&
                0 == ::memcmp(arg.resolvedName.ptr, optionName, optionNameLen * sizeof(clasp_char_t)))
            {
                clasp_useArgument(args, &arg);

                if(0 == arg.value.len)
                {
                    throw_missing_option_value_exception_(optionName, missingMessage);
                }
                else
                {
                    *result = arg.value.ptr;

                    return;
                }
            }
        }}

        throw_missing_option_exception_(optionName, missingMessage);
    }

    inline
    bool
    check_option_boolean_(
        clasp_arguments_t const*    args
    ,   bool                        ignoreUsed
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   bool*                       result
    ,   bool                        optionNotSpecifiedDefaultValue
    ,   bool const*                 valueNotSpecifiedDefaultValue
    )
    {
        { for(size_t i = 0; i != args->numOptions; ++i)
        {
            clasp_argument_t const& arg = args->options[i];

            if( ignoreUsed &&
                clasp_argumentIsUsed(args, &arg))
            {
                continue;
            }

            if( arg.resolvedName.len == optionNameLen &&
                0 == ::memcmp(arg.resolvedName.ptr, optionName, optionNameLen * sizeof(clasp_char_t)))
            {
                clasp_useArgument(args, &arg);

                bool wasStrictlyCorrect;

                *result = boolean_conversion_traits_::convert(arg.value, &wasStrictlyCorrect);

                if( *result &&
                    !wasStrictlyCorrect)
                {
                    // This means that no value was specified

                    if(NULL != valueNotSpecifiedDefaultValue)
                    {
                        *result = *valueNotSpecifiedDefaultValue;
                    }
                }

                return true;
            }
        }}

        *result = optionNotSpecifiedDefaultValue;

        return false;
    }

    inline
    bool
    check_option_cstring_(
        clasp_arguments_t const*    args
    ,   bool                        ignoreUsed
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   clasp_char_t const**        result
    ,   clasp_char_t const*         defaultValue
    )
    {
        { for(size_t i = 0; i != args->numOptions; ++i)
        {
            clasp_argument_t const& arg = args->options[i];

            if( ignoreUsed &&
                clasp_argumentIsUsed(args, &arg))
            {
                continue;
            }

            if( arg.resolvedName.len == optionNameLen &&
                0 == ::memcmp(arg.resolvedName.ptr, optionName, optionNameLen * sizeof(clasp_char_t)))
            {
                clasp_useArgument(args, &arg);

                *result = arg.value.ptr;
                return true;
            }
        }}

        *result = defaultValue;

        return false;
    }

    inline
    bool
    check_option_string_t_(
        clasp_arguments_t const*    args
    ,   bool                        ignoreUsed
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   clasp_string_t&             result
    ,   clasp_char_t const*         defaultValue
    ,   size_t                      defaultValueLen
    )
    {
        SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

        clasp_char_t const* p;
        bool const          r = check_option_cstring_(args, ignoreUsed, optionName, optionNameLen, &p, defaultValue);

        if(r)
        {
            clasp_string_t(SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(p), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(p)).swap(result);
        }
        else
        {
            clasp_string_t(defaultValue, defaultValueLen).swap(result);
        }

        return r;
    }

    template <typename R>
    inline
    bool
    check_option_fn_defaultIsString_(
        clasp_arguments_t const*    args
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   bool                      (*pfn)(
                                        void*               param
                                    ,   clasp_char_t const* parsedValue
                                    ,   R*                  result
                                    )
    ,   void*                       param
    ,   R*                          result
    ,   clasp_char_t const*         defaultValue
    )
    {
        { for(size_t i = 0; i != args->numOptions; ++i)
        {
            clasp_argument_t const& arg = args->options[i];

            if( arg.resolvedName.len == optionNameLen &&
                0 == ::memcmp(arg.resolvedName.ptr, optionName, optionNameLen * sizeof(clasp_char_t)))
            {
                clasp_useArgument(args, &arg);

                defaultValue = arg.value.ptr;

                break;
            }
        }}

        if(NULL != defaultValue)
        {
            return
            (*pfn)(
                param
            ,   defaultValue
            ,   result
            );
        }

        return false;
    }

    inline
    void
    require_option_boolean_(
        clasp_arguments_t const*  args
    ,   clasp_char_t const*       optionName
    ,   size_t                    optionNameLen
    ,   bool*                     result
    ,   char const*               missingMessage
    )
    {
        { for(size_t i = 0; i != args->numOptions; ++i)
        {
            clasp_argument_t const& arg = args->options[i];

            if( arg.resolvedName.len == optionNameLen &&
                0 == ::memcmp(arg.resolvedName.ptr, optionName, optionNameLen * sizeof(clasp_char_t)))
            {
                clasp_useArgument(args, &arg);

                bool wasStrictlyCorrect;

                *result = boolean_conversion_traits_::convert(arg.value, &wasStrictlyCorrect);

                return;
            }
        }}

        throw_missing_option_exception_(optionName, missingMessage);
    }

    template <typename S2>
    inline
    void
    require_option_string_(
        clasp_arguments_t const*    args
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   S2*                         result
    ,   char const*                 missingMessage
    )
    {
        { for(size_t i = 0; i != args->numOptions; ++i)
        {
            clasp_argument_t const& arg = args->options[i];

            if( arg.resolvedName.len == optionNameLen &&
                0 == ::memcmp(arg.resolvedName.ptr, optionName, optionNameLen * sizeof(clasp_char_t)))
            {
                clasp_useArgument(args, &arg);

                if(0 == arg.value.len)
                {
                    throw_missing_option_value_exception_(optionName, missingMessage);
                }
                else
                {
                    *result = S2(arg.value.ptr, arg.value.len);

                    return;
                }
            }
        }}

        throw_missing_option_exception_(optionName, missingMessage);
    }

    inline
    void
    require_option_dispatch_(
        ::stlsoft::yes_type
    ,   clasp_arguments_t const*    args
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   int*                        result
    ,   char const*                 missingMessage
    )
    {
        ::clasp::ximpl::require_option_integer_(args, optionName, optionNameLen, result, missingMessage);
    }

#ifdef _WIN64
    inline
    void
    require_option_dispatch_(
        ::stlsoft::yes_type
    ,   clasp_arguments_t const*    args
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   unsigned*                   result
    ,   char const*                 missingMessage
    )
    {
        ::clasp::ximpl::require_option_integer_(args, optionName, optionNameLen, result, missingMessage);
    }
#endif

    inline
    void
        require_option_dispatch_(
        ::stlsoft::yes_type
    ,   clasp_arguments_t const*    args
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   long*                       result
    ,   char const*                 missingMessage
    )
    {
        ::clasp::ximpl::require_option_integer_(args, optionName, optionNameLen, result, missingMessage);
    }

    inline
    void
    require_option_dispatch_(
        ::stlsoft::yes_type
    ,   clasp_arguments_t const*    args
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   size_t*                     result
    ,   char const*                 missingMessage
    )
    {
        ::clasp::ximpl::require_option_integer_(args, optionName, optionNameLen, result, missingMessage);
    }

    inline
    void
    require_option_dispatch_(
        ::stlsoft::yes_type
    ,   clasp_arguments_t const*    args
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   double*                     result
    ,   char const*                 missingMessage
    )
    {
        ::clasp::ximpl::require_option_real_(args, optionName, optionNameLen, result, missingMessage);
    }

    inline
    void
    require_option_dispatch_(
        ::stlsoft::no_type
    ,   clasp_arguments_t const*    args
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   clasp_char_t const**        result
    ,   char const*                 missingMessage
    )
    {
        ::clasp::ximpl::require_option_cstring_(args, optionName, optionNameLen, result, missingMessage);
    }

    template <typename R>
    inline
    void
    require_option_dispatch_(
        ::stlsoft::no_type
    ,   clasp_arguments_t const*    args
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   R*                          result
    ,   char const*                 missingMessage
    )
    {
        ::clasp::ximpl::require_option_string_(args, optionName, optionNameLen, result, missingMessage);
    }

    inline
    bool
    check_flag_(
        clasp_arguments_t const*    args
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   int*                        bitmask
    ,   int                         onValue
    ,   int                         offValue
    )
    {
        // A boolean value may be had either from a flag, or from an option
        // that has strictly boolean values
        //
        // Hence, the policy is to:
        //
        // 1. check flags first
        // 2. check options, but be strict about the values


        // 1. check flags first
        { for(size_t i = 0; i != args->numFlags; ++i)
        {
            clasp_argument_t const& arg = args->flags[i];

            if( arg.resolvedName.len == optionNameLen &&
                0 == ::memcmp(arg.resolvedName.ptr, optionName, optionNameLen * sizeof(clasp_char_t)))
            {
                clasp_useArgument(args, &arg);

                *bitmask |= onValue;

                return true;
            }
        }}

        // 2. check options, but be strict about the values
        { for(size_t i = 0; i != args->numOptions; ++i)
        {
            clasp_argument_t const& arg = args->options[i];

            if( arg.resolvedName.len == optionNameLen &&
                0 == ::memcmp(arg.resolvedName.ptr, optionName, optionNameLen * sizeof(clasp_char_t)))
            {
                clasp_useArgument(args, &arg);

                bool wasStrictlyCorrect;
                bool result = boolean_conversion_traits_::convert(arg.value, &wasStrictlyCorrect);

                if( !result &&
                    !wasStrictlyCorrect)
                {
                    throw_invalid_option_value_exception_("option value must be a boolean", optionName);
                }

                if(result)
                {
                    *bitmask |= onValue;
                }
                else
                {
                    *bitmask &= ~offValue;
                }

                return true;
            }
        }}

        *bitmask &= ~offValue;

        return false;
    }

    inline
    bool
    flag_specified_(
        clasp_arguments_t const*    args
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   bool                        markUsedIfFound
    )
    {
        { for(size_t i = 0; i != args->numFlags; ++i)
        {
            clasp_argument_t const& arg = args->flags[i];

            if( arg.resolvedName.len == optionNameLen &&
                0 == ::memcmp(arg.resolvedName.ptr, optionName, optionNameLen * sizeof(clasp_char_t)))
            {
                if(markUsedIfFound)
                {
                    clasp_useArgument(args, &arg);
                }

                return true;
            }
        }}

        return false;
    }

    inline
    clasp_argument_t const*
    find_flag_or_option_(
        clasp_arguments_t const*  args
    ,   clasp_char_t const*       optionName
    ,   size_t                    optionNameLen
    ,   clasp_argument_t const*   after
    )
    {
        STLSOFT_ASSERT(NULL == after || (after >= &args->flagsAndOptions[0] && after < &args->flagsAndOptions[0] + args->numFlagsAndOptions));

        { for(size_t i = (NULL == after) ? 0u : (after - &args->flagsAndOptions[0]); i != args->numFlagsAndOptions; ++i)
        {
            clasp_argument_t const& arg = args->flagsAndOptions[i];

            if( arg.resolvedName.len == optionNameLen &&
                0 == ::memcmp(arg.resolvedName.ptr, optionName, optionNameLen * sizeof(clasp_char_t)))
            {
                clasp_useArgument(args, &arg);

                return &arg;
            }
        }}

        return NULL;
    }



#if 0
    inline
    bool
    check_flags_option_(
        clasp_arguments_t const*    args
    ,   clasp_char_t const*         optionName
    ,   size_t                      optionNameLen
    ,   int*                        result
    ,   int                         flagValue
    ,   int                         defaultValue
    )
    {
    }
#endif /* 0 */

} /* namespace ximpl */

#endif /* !SYSTEMTOOLS_DOCUMENTATION_SKIP_SECTION */

/* /////////////////////////////////////////////////////////////////////////
 * API functions
 */

/** Checks whether the given option exists, and elicits its value if so; if
 * not, sets the result to be the given default value
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Pointer to a variable into which to write the result, if
 *   found, or the default value, if not. May not be NULL
 * \param defaultValue The default value to be written into
 *   <code>*result</code> if the named option does not exist
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 */
template <typename S>
bool
check_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   int*                        result
,   int                         defaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::check_option_integer_(args, false, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, defaultValue);
}

/** Checks whether the given option exists in one of the as-yet unused
 * arguments, and elicits its value if so; if not, sets the result to be the
 * given default value
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Pointer to a variable into which to write the result, if
 *   found, or the default value, if not. May not be NULL
 * \param defaultValue The default value to be written into
 *   <code>*result</code> if the named option does not exist
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 */
template <typename S>
bool
check_next_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   int*                        result
,   int                         defaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::check_option_integer_(args, true, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, defaultValue);
}

#ifdef _WIN64
/** Checks whether the given option exists, and elicits its value if so; if
 * not, sets the result to be the given default value
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Pointer to a variable into which to write the result, if
 *   found, or the default value, if not. May not be NULL
 * \param defaultValue The default value to be written into
 *   <code>*result</code> if the named option does not exist
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 */
template <typename S>
bool
check_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   unsigned*                   result
,   unsigned                    defaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::check_option_integer_(args, false, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, defaultValue);
}

/** Checks whether the given option exists in one of the as-yet unused
 * arguments, and elicits its value if so; if not, sets the result to be the
 * given default value
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Pointer to a variable into which to write the result, if
 *   found, or the default value, if not. May not be NULL
 * \param defaultValue The default value to be written into
 *   <code>*result</code> if the named option does not exist
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 */
template <typename S>
bool
check_next_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   unsigned*                   result
,   unsigned                    defaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::check_option_integer_(args, true, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, defaultValue);
}
#endif

/** Checks whether the given option exists, and elicits its value if so; if
 * not, sets the result to be the given default value
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Pointer to a variable into which to write the result, if
 *   found, or the default value, if not. May not be NULL
 * \param defaultValue The default value to be written into
 *   <code>*result</code> if the named option does not exist
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 */
template <typename S>
bool
check_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   long*                       result
,   long                        defaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::check_option_integer_(args, false, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, defaultValue);
}

/** Checks whether the given option exists in one of the as-yet unused
 * arguments, and elicits its value if so; if not, sets the result to be the
 * given default value
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Pointer to a variable into which to write the result, if
 *   found, or the default value, if not. May not be NULL
 * \param defaultValue The default value to be written into
 *   <code>*result</code> if the named option does not exist
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 */
template <typename S>
bool
check_next_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   long*                       result
,   long                        defaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::check_option_integer_(args, true, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, defaultValue);
}

/** Checks whether the given option exists, and elicits its value if so; if
 * not, sets the result to be the given default value
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Pointer to a variable into which to write the result, if
 *   found, or the default value, if not. May not be NULL
 * \param defaultValue The default value to be written into
 *   <code>*result</code> if the named option does not exist
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 */
template <typename S>
bool
check_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   size_t*                     result
,   size_t                      defaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::check_option_integer_(args, false, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, defaultValue);
}

/** Checks whether the given option exists in one of the as-yet unused
 * arguments, and elicits its value if so; if not, sets the result to be the
 * given default value
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Pointer to a variable into which to write the result, if
 *   found, or the default value, if not. May not be NULL
 * \param defaultValue The default value to be written into
 *   <code>*result</code> if the named option does not exist
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 */
template <typename S>
bool
check_next_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   size_t*                     result
,   size_t                      defaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::check_option_integer_(args, true, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, defaultValue);
}

/** Checks whether the given option exists, and elicits its value if so; if
 * not, sets the result to be the given default value
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Pointer to a variable into which to write the result, if
 *   found, or the default value, if not. May not be NULL
 * \param defaultValue The default value to be written into
 *   <code>*result</code> if the named option does not exist
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 */
template <typename S>
bool
check_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   double*                     result
,   double                      defaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::check_option_real_(args, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, defaultValue);
}

/** Checks whether the given option exists in one of the as-yet unused
 * arguments, and elicits its value if so; if not, sets the result to be the
 * given default value
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Pointer to a variable into which to write the result, if
 *   found, or the default value, if not. May not be NULL
 * \param defaultValue The default value to be written into
 *   <code>*result</code> if the named option does not exist
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 */
template <typename S>
bool
check_next_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   double*                     result
,   double                      defaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::check_option_real_(args, true, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, defaultValue);
}

/** Checks whether the given option exists, and elicits its value if so; if
 * not, sets the result to be the given default value
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Pointer to a variable into which to write the result, if
 *   found, or the default value, if not. May not be NULL
 * \param defaultValue The default value to be written into
 *   <code>*result</code> if the named option does not exist
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 */
template <typename S>
bool
check_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   bool*                       result
,   bool                        defaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::check_option_boolean_(args, false, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, defaultValue, NULL);
}

template <typename S>
bool
check_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   bool*                       result
,   bool                        optionNotSpecifiedDefaultValue
,   bool                        valueNotSpecifiedDefaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::check_option_boolean_(args, false, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, optionNotSpecifiedDefaultValue, &valueNotSpecifiedDefaultValue);
}


/**
 *
 * If the
 */
template <typename S>
bool
check_flags_option(
    clasp_arguments_t const*  args
,   S const&                  optionName
,   int*                      result
,   int                       flagValue
,   int                       defaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    bool givenValue;

    if(!::clasp::ximpl::check_option_boolean_(args, false, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), &givenValue, false, NULL))
    {
        *result = (~flagValue & *result) | defaultValue;

        return false;
    }
    else
    {
        if(givenValue)
        {
            *result = *result | flagValue;
        }
        else
        {
            *result = *result & ~flagValue;
        }

        return true;
    }
}

template <typename S>
bool
check_flags_option(
    clasp_arguments_t const*  args
,   S const&                  optionName
,   int*                      result
,   int                       flagValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    bool givenValue;

    if(!::clasp::ximpl::check_option_boolean_(args, false, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), &givenValue, false, NULL))
    {
        return false;
    }
    else
    {
        if(givenValue)
        {
            *result = *result | flagValue;
        }
        else
        {
            *result = *result & ~flagValue;
        }

        return true;
    }
}

/** Checks whether the given option exists, and elicits its value if so; if
 * not, sets the result to be the given default value
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Pointer to a variable into which to write the result, if
 *   found, or the default value, if not. May not be NULL
 * \param defaultValue The default value to be written into
 *   <code>*result</code> if the named option does not exist
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 */
template <typename S>
bool
check_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   clasp_char_t const**        result
,   clasp_char_t const*         defaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::check_option_cstring_(args, false, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, defaultValue);
}

/** Checks whether the given option exists in one of the as-yet unused
 * arguments, and elicits its value if so; if not, sets the result to be the
 * given default value
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Pointer to a variable into which to write the result, if
 *   found, or the default value, if not. May not be NULL
 * \param defaultValue The default value to be written into
 *   <code>*result</code> if the named option does not exist
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 */
template <typename S>
bool
check_next_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   clasp_char_t const**        result
,   clasp_char_t const*         defaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::check_option_cstring_(args, true, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, defaultValue);
}


/** Checks whether the given option exists, and elicits its value if so
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Mutating reference to a string class instance into which to
 *   write the result
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 */
template <typename S>
bool
check_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   clasp_string_t&             result
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    static clasp_char_t const defaultValue[1] = { '\0' };

    return ::clasp::ximpl::check_option_string_t_(args, false, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(defaultValue), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(defaultValue));
}

/** Checks whether the given option exists in one of the as-yet unused
 * arguments, and elicits its value if so
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Mutating reference to a string class instance into which to
 *   write the result
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 */
template <typename S>
bool
check_next_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   clasp_string_t&             result
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    static clasp_char_t const defaultValue[1] = { '\0' };

    return ::clasp::ximpl::check_option_string_t_(args, true, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(defaultValue), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(defaultValue));
}

/** Checks whether the given option exists, and elicits its value if so; if
 * not, sets the result to be the given default value
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Mutating reference to a string class instance into which to
 *   write the result, if found, or the default value, if not
 * \param defaultValue The default value to be written into
 *   <code>result</code> if the named option does not exist
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 */
template <typename S>
bool
check_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   clasp_string_t&             result
,   clasp_string_t const&       defaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::check_option_string_t_(args, false, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(defaultValue), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(defaultValue));
}

/** Checks whether the given option exists in one of the as-yet unused
 * arguments, and elicits its value if so; if not, sets the result to be the
 * given default value
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Mutating reference to a string class instance into which to
 *   write the result, if found, or the default value, if not
 * \param defaultValue The default value to be written into
 *   <code>result</code> if the named option does not exist
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 */
template <typename S>
bool
check_next_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   clasp_string_t&             result
,   clasp_string_t const&       defaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::check_option_string_t_(args, true, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(defaultValue), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(defaultValue));
}

/** Checks whether the given option exists, and elicits its value if so; if
 * not, sets the result to be the given default value
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Mutating reference to a string class instance into which to
 *   write the result, if found, or the default value, if not
 * \param defaultValue The default value to be written into
 *   <code>result</code> if the named option does not exist
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 */
template <typename S>
bool
check_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   clasp_string_t&             result
,   clasp_char_t const*         defaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::check_option_string_t_(args, false, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(defaultValue), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(defaultValue));
}

/** Checks whether the given option exists in one of the as-yet unused
 * arguments, and elicits its value if so; if not, sets the result to be the
 * given default value
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Mutating reference to a string class instance into which to
 *   write the result, if found, or the default value, if not
 * \param defaultValue The default value to be written into
 *   <code>result</code> if the named option does not exist
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 */
template <typename S>
bool
check_next_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   clasp_string_t&             result
,   clasp_char_t const*         defaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::check_option_string_t_(args, true, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(defaultValue), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(defaultValue));
}

/** Evaluates whether a flag (or a boolean option) is specified, and
 *   adjusts the given bitmask accordingly
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param S name Name of the flag or option to search for
 * \param bitmask Pointer to a variable whose value will be adjusted
 *   according to the presence/absence of the flag/option
 * \param offValue The value to be included into <code>*bitmask</code> if the
 *   flag/option is present (and specified to be on/true/1)
 * \param offValue The value to be removed from <code>*bitmask</code> if the
 *   flag/option is missing, or specified to be off/false/0
 *
 * \pre (NULL != args)
 * \pre (NULL != bitmask)
 */
template <typename S>
bool
check_flag(
    clasp_arguments_t const*    args
,   S const&                    name
,   int*                        bitmask
,   int                         onValue
,   int                         offValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::check_flag_(args, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(name), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(name), bitmask, onValue, offValue);
}

/** Evaluates whether a flag (or a boolean option) is specified, and
 *   adjusts the given bitmask accordingly
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param S name Name of the flag or option to search for
 * \param bitmask Pointer to a variable whose value will be adjusted
 *   according to the presence/absence of the flag/option
 * \param offValue The value to be included into <code>*bitmask</code> if the
 *   flag/option is present (and specified to be on/true/1)
 *
 * \pre (NULL != args)
 * \pre (NULL != bitmask)
 */
template <typename S>
bool
check_flag(
    clasp_arguments_t const*    args
,   S const&                    name
,   int*                        bitmask
,   int                         onValue
)
{
    return check_flag(args, name, bitmask, onValue, onValue);
}

/** Evaluates whether a flag (or a boolean option) is specified, and
 *   sets the given boolean flag variable accordingly.
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param S name Name of the flag or option to search for
 * \param flagVar <strong>true</strong> if the flag/option is present (and
 *  specified to be on/true/1); <strong>false</strong> otherwise.
 *
 * \pre (NULL != args)
 * \pre (NULL != flagVar)
 */
template <typename S>
bool
check_flag(
    clasp_arguments_t const*    args
,   S const&                    name
,   bool*                       flagVar
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    bool    dummy_;
    int     bitmask =   0;
    bool    b       =   ::clasp::ximpl::check_flag_(args, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(name), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(name), &bitmask, 1, 0);

    if(NULL == flagVar)
    {
        flagVar = &dummy_;
    }

    *flagVar = (0 != bitmask) ? true : false;

    return b;
}

/** Evaluates whether the named flag (or option) is specified, and
 * (optionally) marks it as used if so
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param name Name of the flag (or option). May not be NULL or empty
 * \param markUsedIfFound If true, the flag (or option) is mark used if
 *   found
 *
 * \pre (NULL != args)
 */
template <typename S>
bool
flag_specified(
    clasp_arguments_t const*    args
,   S const&                    name
,   bool                        markUsedIfFound = true
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::flag_specified_(args, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(name), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(name), markUsedIfFound);
}

/** Obtains a pointer to the flag or option with the given name, if it
 * exists
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param name Name of the flag or option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param after Point after which to start search. May be NULL, in which
 *   case search starts at beginning of <code>flagsAndOptions</code> field
 *
 * \pre (NULL != args)
 */
template <typename S>
clasp_argument_t const*
find_flag_or_option(
    clasp_arguments_t const*  args
,   S const&                  name
,   clasp_argument_t const*   after
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    return ::clasp::ximpl::find_flag_or_option_(args, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(name), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(name), after);
}

// The following functions allow for optional (check) retrieval of an option
// value of a custom type, via a caller-supplied parsing function. The
// caller-supplied function takes the forms:
//
//   (ctxt : void*, parsedValue : cc*, result T*) : bool
//
// The relationship between the default value type (D) and the result type
// (R) involves the following supported permutations:
//
// 1. Same type - D == R
// 2. D is character string literal
// 3. Integers - D is an integer type, R is an integer type
// 4. D is an instance of a type that can be interpreted as a string

/** Checks whether the given option exists, and elicits its value via the
 * given callback function if so; if not, sets the result to be the given
 * default value
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Pointer to a variable into which to write the result, if
 *   found, or the default value, if not. May not be NULL
 * \param pfn Caller-supplied that can convert the found option's value to
 *   the required type, returning true if so; returning false or throwing
 *   a caller-defined exception otherwise. May not be NULL
 * \param param Caller-supplied parameter that is passed back to the
 *   caller-supplied function. May be any value, including NULL, and is
 *   not examined in any way by CLASP
 * \param defaultValue The default value to be written into
 *   <code>*result</code> if the named option does not exist
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 * \pre (NULL != pfn)
 *
 * \note The default value must be of a type which may be interpreted as a
 *   string
 */
template<
    typename S
,   typename R
,   typename D
>
bool
check_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   R*                          result
,   bool                      (*pfn)(
                                    void*               param
                                ,   clasp_char_t const* parsedValue
                                ,   R*                  result
                                )
,   void*                       param
,   D const&                    defaultValue
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();
    SYSTEMTOOLS_CLASP_DECLARE_c_str_ptr_null_();

    return ::clasp::ximpl::check_option_fn_defaultIsString_(
                args
            ,   SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName)
            ,   SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName)
            ,   pfn
            ,   param
            ,   result
            ,   SYSTEMTOOLS_CLASP_INVOKE_c_str_ptr_null_(defaultValue)
            );
}


// The require_option() function overloads are similar in intent to the
// check_option() semantics, but if the option is not found an exception
// (of argument_exception or a derived type) is thrown.
//

/** Searches for the required option and provides its value, or throws an
 * exception if it cannot be found
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Pointer to a variable into which to write the result, if
 *   found, or the default value, if not. May not be NULL
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 *
 * \exception missing_option_exception Thrown if the option does not exist
 * \exception missing_option_value_exception Thrown if the option does not
 *   have a (non-empty) value
 * \exception invalid_option_value_exception Thrown if the option value
 *   cannot be converted to the type of <code>*result</code>
 */
template <typename S, typename R>
void
require_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   R*                          result
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    typedef ss_typename_type_k ::stlsoft::is_numeric_type<R>::type      numeric_t_;

    ::clasp::ximpl::require_option_dispatch_(numeric_t_(), args, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, NULL);
}

/** Searches for the required option and provides its value, or throws an
 * exception if it cannot be found
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param optionName Name of the option. Must be of a type which may be
 *   interpreted as a string. May not be NULL or empty
 * \param result Pointer to a variable into which to write the result, if
 *   found, or the default value, if not. May not be NULL
 * \param missingMessage Optional message to use in exception thrown when
 *   the named option cannot be found. May be NULL, in which case a default
 *   message is used
 *
 * \pre (NULL != args)
 * \pre (NULL != result)
 *
 * \exception missing_option_exception Thrown if the option does not exist
 * \exception missing_option_value_exception Thrown if the option does not
 *   have a (non-empty) value
 * \exception invalid_option_value_exception Thrown if the option value
 *   cannot be converted to the type of <code>*result</code>
 */
template <typename S, typename R>
void
require_option(
    clasp_arguments_t const*    args
,   S const&                    optionName
,   R*                          result
,   char const*                 missingMessage
)
{
    SYSTEMTOOLS_CLASP_DECLARE_c_str_datalen_PAIR_();

    typedef ss_typename_type_k ::stlsoft::is_numeric_type<R>::type      numeric_t_;

    ::clasp::ximpl::require_option_dispatch_(numeric_t_(), args, SYSTEMTOOLS_CLASP_INVOKE_c_str_data_(optionName), SYSTEMTOOLS_CLASP_INVOKE_c_str_len_(optionName), result, missingMessage);
}


/** Checks for the presence of a value with the given index
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param index The index of the putative value to be obtained
 * \param pslice Pointer to a slice variable to be assigned the value's
 *   value, if found
 *
 * \pre (NULL != args)
 * \pre (NULL != pslice)
 */
inline
bool
check_value(
    clasp_arguments_t const*    args
,   size_t                      index
,   clasp_slice_t*              pslice
)
{
    STLSOFT_ASSERT(NULL != args);
    STLSOFT_ASSERT(NULL != pslice);

    if(index < args->numValues)
    {
        pslice->ptr =   args->values[index].value.ptr;
        pslice->len =   args->values[index].value.len;

        return true;
    }
    else
    {
        pslice->ptr =   NULL;
        pslice->len =   0;

        return false;
    }
}

/** Checks for the presence of a value with the given index
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param index The index of the putative value to be obtained
 * \param pslice Pointer to a variable to receive the value's value's
 *   pointer (if found). May not be NULL
 * \param plen Pointer to a variable to receive the value's value's
 *   length (if found). May be NULL
 *
 * \pre (NULL != args)
 * \pre (NULL != pptr)
 */
inline
bool
check_value(
    clasp_arguments_t const*    args
,   size_t                      index
,   clasp_char_t const**        pptr
,   size_t*                     plen
)
{
    STLSOFT_ASSERT(NULL != args);

    size_t dummy_;

    if(NULL == plen)
    {
        plen = &dummy_;
    }

    clasp_slice_t   slice;
    bool            r = check_value(args, index, &slice);

    *pptr   =   slice.ptr;
    *plen   =   slice.len;

    return r;
}

/** Mark flag/option as used
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param usedArg Argument to be marked as used
 *
 * \note This is necessary only when manual processing of the \c args
 *   parameter's fields is conducted by the user
 */
inline
void
use_flag_or_option(
    clasp_arguments_t const*  args
,   clasp_argument_t const*   usedArg
)
{
    clasp_useArgument(args, usedArg);
}

/** Mark flag/option as used
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param usedArg Argument to be marked as used
 *
 * \note This is necessary only when manual processing of the \c args
 *   parameter's fields is conducted by the user
 */
inline
void
use_flag_or_option(
    clasp_arguments_t const*  args
,   clasp_argument_t const&   usedArg
)
{
    clasp_useArgument(args, &usedArg);
}

/** Verifies that all flags and options are known, by reference to the given
 * \c aliases parameter
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 * \param aliases A pointer to a properly-formed alias array. May not be
 *   NULL.
 *
 * \exception clasp::unrecognised_argument_exception Thrown if an argument is
 *   unrecognised
 */
inline
void
verify_all_flags_and_options_are_recognised(
    clasp_arguments_t const*    args
,   clasp_alias_t const*        aliases
)
{
    clasp_argument_t const* firstUnrecognisedArg;
    size_t const            n = clasp_reportUnrecognisedFlagsAndOptions(args, aliases, &firstUnrecognisedArg, 0);

    if(0u != n)
    {
        static char const s_prefix[] = "unrecognised argument(s)";

        throw unrecognised_argument_exception(
                  unrecognised_argument_exception::message_string_type(s_prefix, STLSOFT_NUM_ELEMENTS(s_prefix) - (1 + 3 * (1u == n)))
              ,   unrecognised_argument_exception::string_type(firstUnrecognisedArg->givenName.ptr, firstUnrecognisedArg->givenName.len)
              );
    }
}


/** Verifies that all flags and options have been used, throwing an instance of
 * clasp::unused_argument_exception if one or more have not been used (and
 * are therefore unrecognised).
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 *
 * \exception clasp::unused_argument_exception Thrown if an argument is
 *   unused
 */
inline
void
verify_all_flags_and_options_used(
    clasp_arguments_t const* args
)
{
    clasp_argument_t const* firstUnusedArg;
    size_t const            n = clasp_reportUnusedFlagsAndOptions(args, &firstUnusedArg, 0);

    if(0u != n)
    {
        static char const s_prefix[] = "unused argument(s)";

        throw unused_argument_exception(
                  unused_argument_exception::message_string_type(s_prefix, STLSOFT_NUM_ELEMENTS(s_prefix) - (1 + 3 * (1u == n)))
              ,   unused_argument_exception::string_type(firstUnusedArg->givenName.ptr, firstUnusedArg->givenName.len)
              );
    }
}

/** [DEPRECATED]
 *
 * \param args Non-mutating pointer to the arguments structure, obtained
 *   from call to parseArguments() / clasp_parseArguments(). May not be NULL
 *
 * \deprecated This function is now obsolete, and will be removed from a future
 *   version of CLASP; instead
 *   use \link clasp::verify_all_flags_and_options_used verify_all_flags_and_options_used()\endlink.
 */
inline
void
verify_all_options_used(
    clasp_arguments_t const* args
)
{
    verify_all_flags_and_options_used(args);
}

/* /////////////////////////////////////////////////////////////////////////
 * Namespace
 */

} /* namespace clasp */

/* ////////////////////////////////////////////////////////////////////// */

#endif /* !SYSTEMTOOLS_INCL_SYSTEMTOOLS_CLASP_HPP_CLASP */

/* ///////////////////////////// end of file //////////////////////////// */

