/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.clasp++/entry.cpp
 *
 * Purpose: Unit-tests for CLASP C++ API
 *
 * Created: 16th July 2009
 * Updated: 9th May 2025
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <clasp/clasp.hpp>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/error/error_desc.hpp>
#include <stlsoft/smartptr/scoped_handle.hpp>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 */

#if defined(_MSC_VER) && \
    _MSC_VER >= 1400

# pragma warning(push)
# pragma warning(disable : 4702)
# pragma warning(disable : 4996)
#endif

#ifndef XTESTS_TEST_FAIL_WITH_ERRNO

# define XTESTS_TEST_FAIL_WITH_ERRNO(msg, e)                \
                                                            \
    XTESTS_TEST_FAIL_WITH_QUALIFIER(msg, stlsoft::error_desc(r).c_str())
#endif // XTESTS_TEST_FAIL_WITH_ERRNO


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    static void TEST_NO_ARGUMENTS();
    static void TEST_1_VALUE();
    static void TEST_1_VALUE_1_FLAG();
    static void TEST_1_VALUE_AND_SINGLEHYPHEN();
    static void TEST_1_VALUE_AND_DOUBLEHYPHEN_AND_SINGLEHYPHEN();
    static void TEST_1_VALUE_2_LONGOPTIONS_2_FLAGS();
    static void TEST_1_VALUE_2_LONGOPTIONS_2_FLAGS_ALSO_CALLING_clasp_check_flag();
    static void TEST_1_VALUE_2_LONGOPTIONS_2_FLAGS_ALSO_CALLING_clasp_check_flag_2();
    static void TEST_1_VALUE_2_LONGOPTIONS_2_FLAGS_ALSO_CALLING_clasp_check_flag_3();
    static void TEST_2_LONGOPTIONS();
    static void TEST_1_FLAG_1_VALUE();

    static void TEST_1_FLAG_2_OPTIONS_1_FLAG();
    static void TEST_1_FLAG_2_OPTIONS_1_FLAG_2();
    static void TEST_1_FLAG_2_OPTIONS_1_FLAG_3();
    static void TEST_1_FLAG_2_OPTIONS_1_FLAG_4();
    static void TEST_1_FLAG_2_OPTIONS_1_FLAG_5();
    static void TEST_1_FLAG_2_OPTIONS_1_FLAG_6();
    static void TEST_1_FLAG_1_VALUE_1_OPTION_1_FLAG_1_VALUE();
    static void TEST_1_OPTION();
    static void TEST_3_OPTIONS();
    static void TEST_3_OPTIONS_2();
    static void TEST_3_OPTIONS_3();
    static void TEST_3_OPTIONS_4();
    static void TEST_3_OPTIONS_5();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * globals
 */

clasp_diagnostic_context_t const*   s_ctxt;


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    struct stub
    {
        static void CLASP_CALLCONV function(
            void*                /* context */
        ,   int                  /* severity */
        ,   clasp_char_t const*  /* fmt */
        ,   va_list              /* args */
        )
        {}
    };

    clasp_diagnostic_context_t  ctxt;

    ctxt.pfnLog = &stub::function;

    s_ctxt = &ctxt;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.clasp++", verbosity))
    {
#if 0
        XTESTS_RUN_CASE(TEST_1_FLAG_2_OPTIONS_1_FLAG_5);
#endif /* 0 */

        XTESTS_RUN_CASE(TEST_NO_ARGUMENTS);
        XTESTS_RUN_CASE(TEST_1_VALUE);
        XTESTS_RUN_CASE(TEST_1_VALUE_1_FLAG);
        XTESTS_RUN_CASE(TEST_1_VALUE_AND_SINGLEHYPHEN);
        XTESTS_RUN_CASE(TEST_1_VALUE_AND_DOUBLEHYPHEN_AND_SINGLEHYPHEN);
        XTESTS_RUN_CASE(TEST_1_VALUE_2_LONGOPTIONS_2_FLAGS);
        XTESTS_RUN_CASE(TEST_1_VALUE_2_LONGOPTIONS_2_FLAGS_ALSO_CALLING_clasp_check_flag);
        XTESTS_RUN_CASE_THAT_THROWS(TEST_1_VALUE_2_LONGOPTIONS_2_FLAGS_ALSO_CALLING_clasp_check_flag_2, clasp::invalid_option_value_exception);
        XTESTS_RUN_CASE(TEST_1_VALUE_2_LONGOPTIONS_2_FLAGS_ALSO_CALLING_clasp_check_flag_3);
        XTESTS_RUN_CASE(TEST_2_LONGOPTIONS);
        XTESTS_RUN_CASE(TEST_1_FLAG_1_VALUE);

        XTESTS_RUN_CASE(TEST_1_FLAG_2_OPTIONS_1_FLAG);
        XTESTS_RUN_CASE(TEST_1_FLAG_2_OPTIONS_1_FLAG_2);
        XTESTS_RUN_CASE(TEST_1_FLAG_2_OPTIONS_1_FLAG_3);
        XTESTS_RUN_CASE(TEST_1_FLAG_2_OPTIONS_1_FLAG_4);
        XTESTS_RUN_CASE(TEST_1_FLAG_2_OPTIONS_1_FLAG_5);
        XTESTS_RUN_CASE(TEST_1_FLAG_2_OPTIONS_1_FLAG_6);
        XTESTS_RUN_CASE(TEST_1_FLAG_1_VALUE_1_OPTION_1_FLAG_1_VALUE);
        XTESTS_RUN_CASE(TEST_1_OPTION);
        XTESTS_RUN_CASE(TEST_3_OPTIONS);
        XTESTS_RUN_CASE(TEST_3_OPTIONS_2);
        XTESTS_RUN_CASE(TEST_3_OPTIONS_3);
        XTESTS_RUN_CASE(TEST_3_OPTIONS_4);
        XTESTS_RUN_CASE(TEST_3_OPTIONS_5);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace
{
    using clasp::argument_t;
    using clasp::arguments_t;


static void TEST_NO_ARGUMENTS()
{
    char const* argv[] =
    {
        "arg0",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        XTESTS_TEST_INTEGER_EQUAL(0u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(1, args->argc);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("arg0", args->programName);
    }
}

static void TEST_1_VALUE()
{
    char const* argv[] =
    {
        "/dir0/arg0",
        "abc",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        XTESTS_TEST_INTEGER_EQUAL(1u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(2, args->argc);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("arg0", args->programName);

#if __cplusplus >= 201103L

        for (auto const& value : clasp::values(args))
        {
            XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abc", value);
        }
#endif
    }
}

static void TEST_1_VALUE_1_FLAG()
{
    char const* argv[] =
    {
#ifdef _WIN32

        "C:\\dir0\\arg0.exe",
#else

        "/dir0/arg0",
#endif
        "abc",
        "-x",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        XTESTS_TEST_INTEGER_EQUAL(2u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(3, args->argc);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("arg0", args->programName);

#if __cplusplus >= 201103L

        for (auto const& flag : clasp::flags(args))
        {
            XTESTS_TEST_MULTIBYTE_STRING_EQUAL("-x", flag.resolvedName);
        }

        for (auto const& value : clasp::values(args))
        {
            XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abc", value);
        }
#endif
    }
}

static void TEST_1_VALUE_AND_SINGLEHYPHEN()
{
    char const* argv[] =
    {
        "arg0",
        "abc",
        "-",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        XTESTS_TEST_INTEGER_EQUAL(2u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(3, args->argc);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("arg0", args->programName);

#if __cplusplus >= 201103L

        for (auto const& flag : clasp::flags(args))
        {
            XTESTS_TEST_MULTIBYTE_STRING_EQUAL("-", flag.resolvedName);
        }

        for (auto const& value : clasp::values(args))
        {
            XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abc", value);
        }
#endif
    }
}

static void TEST_1_VALUE_AND_DOUBLEHYPHEN_AND_SINGLEHYPHEN()
{
    char const* argv[] =
    {
        "arg0",
        "abc",
        "--",
        "-",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        XTESTS_TEST_INTEGER_EQUAL(2u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(4, args->argc);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("arg0", args->programName);

#if __cplusplus >= 201103L

        for (auto const& value : clasp::values(args))
        {
            ((void)&value);

            // XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abc", value);
            // XTESTS_TEST_MULTIBYTE_STRING_EQUAL("-", value);
        }
#endif
    }
}

static void TEST_1_VALUE_2_LONGOPTIONS_2_FLAGS()
{
    char const* argv[] =
    {
        "arg0",
        "abc",
        "--x-argument=true",
        "--y-argument=false",
        "-x",
        "-y",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        XTESTS_TEST_INTEGER_EQUAL(5u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(4u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(6, args->argc);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("arg0", args->programName);

#if __cplusplus >= 201103L

        for (auto const& flag : clasp::flags(args))
        {
            switch (flag.cmdLineIndex)
            {
            case 4:

                XTESTS_TEST_MULTIBYTE_STRING_EQUAL("-x", flag.resolvedName);
                break;
            case 5:

                XTESTS_TEST_MULTIBYTE_STRING_EQUAL("-y", flag.resolvedName);
                break;
            }
        }

        for (auto const& value : clasp::values(args))
        {
            XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abc", value);
        }
#endif
    }
}

static void TEST_1_VALUE_2_LONGOPTIONS_2_FLAGS_ALSO_CALLING_clasp_check_flag()
{
    char const* argv[] =
    {
        "arg0",
        "abc",
        "--x-argument=true",
        "--y-argument=false",
        "-x",
        "-y",
        NULL,
    };

    enum
    {
            TEST_1_6_SINGLE_X   =   0x0001
        ,   TEST_1_6_SINGLE_Y   =   0x0002
        ,   TEST_1_6_DOUBLE_X   =   0x0004
        ,   TEST_1_6_DOUBLE_Y   =   0x0008
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        XTESTS_TEST_INTEGER_EQUAL(5u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(4u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(6, args->argc);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("arg0", args->programName);

#if __cplusplus >= 201103L

        for (auto const& flag : clasp::flags(args))
        {
            switch (flag.cmdLineIndex)
            {
            case 4:

                XTESTS_TEST_MULTIBYTE_STRING_EQUAL("-x", flag.resolvedName);
                break;
            case 5:

                XTESTS_TEST_MULTIBYTE_STRING_EQUAL("-y", flag.resolvedName);
                break;
            }
        }

        for (auto const& value : clasp::values(args))
        {
            XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abc", value);
        }
#endif

        int flags = 0;

        clasp::check_flag(args, "-x", &flags, TEST_1_6_SINGLE_X, 0);
        clasp::check_flag(args, "-y", &flags, TEST_1_6_SINGLE_Y, 0);
        clasp::check_flag(args, "-z", &flags, 0, 0);
        clasp::check_flag(args, "--x-argument", &flags, TEST_1_6_DOUBLE_X, 0);
        clasp::check_flag(args, "--y-argument", &flags, TEST_1_6_DOUBLE_Y, 0);

        XTESTS_TEST_INTEGER_EQUAL(TEST_1_6_SINGLE_X | TEST_1_6_SINGLE_Y | TEST_1_6_DOUBLE_X, flags);
    }
}

static void TEST_1_VALUE_2_LONGOPTIONS_2_FLAGS_ALSO_CALLING_clasp_check_flag_2()
{
    char const* argv[] =
    {
        "arg0",
        "abc",
        "--x-argument=true",
        "--y-argument=nope",
        "-x",
        "-y",
        NULL,
    };

    enum
    {
            TEST_1_6_SINGLE_X   =   0x0001
        ,   TEST_1_6_SINGLE_Y   =   0x0002
        ,   TEST_1_6_DOUBLE_X   =   0x0004
        ,   TEST_1_6_DOUBLE_Y   =   0x0008
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        XTESTS_TEST_INTEGER_EQUAL(5u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(4u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(6, args->argc);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("arg0", args->programName);

#if __cplusplus >= 201103L

        for (auto const& value : clasp::values(args))
        {
            XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abc", value);
        }
#endif

        int flags = 0;

        clasp::check_flag(args, "-x", &flags, TEST_1_6_SINGLE_X, 0);
        clasp::check_flag(args, "-y", &flags, TEST_1_6_SINGLE_Y, 0);
        clasp::check_flag(args, "-z", &flags, 0, 0);
        clasp::check_flag(args, "--x-argument", &flags, TEST_1_6_DOUBLE_X, 0);
        clasp::check_flag(args, "--y-argument", &flags, TEST_1_6_DOUBLE_Y, 0);

        XTESTS_TEST_FAIL("should never get here!");
    }
}

static void TEST_1_VALUE_2_LONGOPTIONS_2_FLAGS_ALSO_CALLING_clasp_check_flag_3()
{
    char const* argv[] =
    {
        "arg0",
        "abc",
        "-X-argument=true",
        "-Y-argument=false",
        "-x",
        "-y",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        XTESTS_TEST_INTEGER_EQUAL(5u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(4u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(6, args->argc);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("arg0", args->programName);

#if __cplusplus >= 201103L

        for (auto const& value : clasp::values(args))
        {
            XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abc", value);
        }
#endif
    }
}

static void TEST_2_LONGOPTIONS()
{
    char const* argv[] =
    {
            "arg0"
        ,   "--option-1=true"
        ,   "--option-2=false"
        //  "--option-3=true"
        ,   NULL
    };

    enum
    {
            TEST_1_14_OPTION_1  =   0x0001
        ,   TEST_1_14_OPTION_2  =   0x0002
        ,   TEST_1_14_OPTION_3  =   0x0004
        ,   TEST_1_14_OPTION_4  =   0x0008
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        XTESTS_TEST_INTEGER_EQUAL(2u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(3, args->argc);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("arg0", args->programName);

        int flags = 0;

        clasp::check_flags_option(args, "--option-1", &flags, TEST_1_14_OPTION_1);
        XTESTS_TEST_INTEGER_EQUAL(0x0001, flags);
        clasp::check_flags_option(args, "--option-2", &flags, TEST_1_14_OPTION_2);
        XTESTS_TEST_INTEGER_EQUAL(0x0001, flags);
        clasp::check_flags_option(args, "--option-3", &flags, TEST_1_14_OPTION_3, TEST_1_14_OPTION_3);
        XTESTS_TEST_INTEGER_EQUAL(0x0005, flags);
        clasp::check_flags_option(args, "--option-4", &flags, TEST_1_14_OPTION_4);
        XTESTS_TEST_INTEGER_EQUAL(0x0005, flags);

        XTESTS_TEST_PASSED();
    }
}

static void TEST_1_FLAG_1_VALUE()
{
    char const* argv[] =
    {
        "arg0",
        "--clipboard",
        "H:\\dev\\srctools\\number_lines\\implicit_link.cpp",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        XTESTS_TEST_INTEGER_EQUAL(2u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(3, args->argc);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("arg0", args->programName);

#if __cplusplus >= 201103L

        for (auto const& flag : clasp::flags(args))
        {
            switch (flag.cmdLineIndex)
            {
            case 1:

                XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--clipboard", flag.resolvedName);
                break;
            }
        }

        for (auto const& value : clasp::values(args))
        {
            XTESTS_TEST_MULTIBYTE_STRING_EQUAL("H:\\dev\\srctools\\number_lines\\implicit_link.cpp", value);
        }
#endif
    }
}

static void TEST_1_FLAG_2_OPTIONS_1_FLAG()
{
    static clasp::specification_t const Specifications[] =
    {
        CLASP_FLAG("-v", "--version", NULL),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };

    char const* argv[] =
    {
        "arg0",
        "-v",
        "--boolopt1=true",
        "--boolopt2=false",
        "--boolopt3",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Specifications, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        bool    v;

        XTESTS_TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--nonexistant"));
        XTESTS_TEST_BOOLEAN_FALSE(clasp::check_flag(args, "--nonexistant", &v));
        XTESTS_TEST_BOOLEAN_FALSE(v);

        XTESTS_TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--version"));
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--version", &v));
        XTESTS_TEST_BOOLEAN_TRUE(v);

        XTESTS_TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt1"));
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt1", &v, false));
        XTESTS_TEST_BOOLEAN_TRUE(v);
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt1", &v));
        XTESTS_TEST_BOOLEAN_TRUE(v);

        XTESTS_TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt2"));
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, true));
        XTESTS_TEST_BOOLEAN_FALSE(v);
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, false));
        XTESTS_TEST_BOOLEAN_FALSE(v);
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt2", &v));
        XTESTS_TEST_BOOLEAN_FALSE(v);

        XTESTS_TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--boolopt3"));

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("arg0", args->programName);
    }
}

static void TEST_1_FLAG_2_OPTIONS_1_FLAG_2()
{
    clasp::specification_t const    Alias_Flag_Version  =   CLASP_FLAG("-v", "--version", NULL);

    static clasp::specification_t Specifications[] =
    {
        CLASP_SPECIFICATION_ARRAY_TERMINATOR, // Some older compilers can't pass in the specification_t instance here, so ...

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };

    Specifications[0] = Alias_Flag_Version; // ... it is assigned here

    char const* argv[] =
    {
        "arg0",
        "-v",
        "--boolopt1=true",
        "--boolopt2=false",
        "--boolopt3",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Specifications, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        bool    v;

        XTESTS_TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--nonexistant"));
        XTESTS_TEST_BOOLEAN_FALSE(clasp::check_flag(args, "--nonexistant", &v));
        XTESTS_TEST_BOOLEAN_FALSE(v);

        XTESTS_TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--version"));
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--version", &v));
        XTESTS_TEST_BOOLEAN_TRUE(v);

        XTESTS_TEST_BOOLEAN_TRUE(clasp::flag_specified(args, Alias_Flag_Version));
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_flag(args, Alias_Flag_Version, &v));
        XTESTS_TEST_BOOLEAN_TRUE(v);

        XTESTS_TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt1"));
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt1", &v, false));
        XTESTS_TEST_BOOLEAN_TRUE(v);
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt1", &v));
        XTESTS_TEST_BOOLEAN_TRUE(v);

        XTESTS_TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt2"));
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, true));
        XTESTS_TEST_BOOLEAN_FALSE(v);
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, false));
        XTESTS_TEST_BOOLEAN_FALSE(v);
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt2", &v));
        XTESTS_TEST_BOOLEAN_FALSE(v);

        XTESTS_TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--boolopt3"));

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("arg0", args->programName);
    }
}

static void TEST_1_FLAG_2_OPTIONS_1_FLAG_3()
{
    static clasp::specification_t const Specifications[] =
    {
        CLASP_FLAG("-v", "--version", NULL),

        CLASP_OPTION("-b", "--boolopt2", NULL, "|true|false"),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };

    char const* argv[] =
    {
        "arg0",
        "-v",
        "--boolopt1=true",
        "--boolopt2",
        "false",
        "--boolopt3",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Specifications, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        bool    v;

        XTESTS_TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--nonexistant"));
        XTESTS_TEST_BOOLEAN_FALSE(clasp::check_flag(args, "--nonexistant", &v));
        XTESTS_TEST_BOOLEAN_FALSE(v);

        XTESTS_TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--version"));
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--version", &v));
        XTESTS_TEST_BOOLEAN_TRUE(v);

        XTESTS_TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt1"));
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt1", &v, false));
        XTESTS_TEST_BOOLEAN_TRUE(v);
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt1", &v));
        XTESTS_TEST_BOOLEAN_TRUE(v);

        XTESTS_TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt2"));
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, true));
        XTESTS_TEST_BOOLEAN_FALSE(v);
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, false));
        XTESTS_TEST_BOOLEAN_FALSE(v);
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt2", &v));
        XTESTS_TEST_BOOLEAN_FALSE(v);

        XTESTS_TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--boolopt3"));

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("arg0", args->programName);
    }
}

static void TEST_1_FLAG_2_OPTIONS_1_FLAG_4()
{
    static clasp::specification_t const Specifications[] =
    {
        CLASP_FLAG("-v", "--version", NULL),

        CLASP_OPTION(NULL, "--boolopt2", NULL, "|true|false"),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };

    char const* argv[] =
    {
        "arg0",
        "-v",
        "--boolopt1=true",
        "--boolopt2=",
        "--boolopt3",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Specifications, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        bool    v;

        XTESTS_TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--nonexistant"));
        XTESTS_TEST_BOOLEAN_FALSE(clasp::check_flag(args, "--nonexistant", &v));
        XTESTS_TEST_BOOLEAN_FALSE(v);

        XTESTS_TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--version"));
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--version", &v));
        XTESTS_TEST_BOOLEAN_TRUE(v);

        XTESTS_TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt1"));
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt1", &v, false));
        XTESTS_TEST_BOOLEAN_TRUE(v);
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt1", &v));
        XTESTS_TEST_BOOLEAN_TRUE(v);

        XTESTS_TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt2"));
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, true));
        XTESTS_TEST_BOOLEAN_TRUE(v);
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, false));
        XTESTS_TEST_BOOLEAN_TRUE(v);
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, false, false));
        XTESTS_TEST_BOOLEAN_FALSE(v);

        XTESTS_TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--boolopt3"));

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("arg0", args->programName);
    }
}

static void TEST_1_FLAG_2_OPTIONS_1_FLAG_5()
{
    static clasp::specification_t const Specifications[] =
    {
        CLASP_FLAG("-v", "--version", NULL),

        CLASP_OPTION(NULL, "--boolopt2", NULL, "|true|false"),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };

    char const* argv[] =
    {
        "arg0",
        "-v",
        "--boolopt1=true",
        "--boolopt2",
        "false",
        "--boolopt3",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Specifications, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        bool    v;

        XTESTS_TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--nonexistant"));
        XTESTS_TEST_BOOLEAN_FALSE(clasp::check_flag(args, "--nonexistant", &v));
        XTESTS_TEST_BOOLEAN_FALSE(v);

        XTESTS_TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--version"));
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--version", &v));
        XTESTS_TEST_BOOLEAN_TRUE(v);

        XTESTS_TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt1"));
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt1", &v, false));
        XTESTS_TEST_BOOLEAN_TRUE(v);
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt1", &v));
        XTESTS_TEST_BOOLEAN_TRUE(v);

        XTESTS_TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt2"));
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, true));
        XTESTS_TEST_BOOLEAN_TRUE(v);
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, false));
        XTESTS_TEST_BOOLEAN_TRUE(v);
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt2", &v));
        XTESTS_TEST_BOOLEAN_TRUE(v);

        XTESTS_TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--boolopt3"));

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("arg0", args->programName);
    }
}

static void TEST_1_FLAG_2_OPTIONS_1_FLAG_6()
{
    static clasp::specification_t const Specifications[] =
    {
        CLASP_FLAG("-v", "--version", NULL),

        CLASP_OPTION(NULL, "--boolopt2", NULL, "|true|false"),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };

    char const* argv[] =
    {
        "arg0",
        "-v",
        "--boolopt1=true",
        "--boolopt2",
        "--boolopt3",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Specifications, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        bool    v;

        XTESTS_TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--nonexistant"));
        XTESTS_TEST_BOOLEAN_FALSE(clasp::check_flag(args, "--nonexistant", &v));
        XTESTS_TEST_BOOLEAN_FALSE(v);

        XTESTS_TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--version"));
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--version", &v));
        XTESTS_TEST_BOOLEAN_TRUE(v);

        XTESTS_TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt1"));
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt1", &v, false));
        XTESTS_TEST_BOOLEAN_TRUE(v);
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt1", &v));
        XTESTS_TEST_BOOLEAN_TRUE(v);

        XTESTS_TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt2"));
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, true));
        XTESTS_TEST_BOOLEAN_TRUE(v);
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, false));
        XTESTS_TEST_BOOLEAN_TRUE(v);
        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, false, false));
        XTESTS_TEST_BOOLEAN_FALSE(v);

        XTESTS_TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--boolopt3"));

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("arg0", args->programName);
    }
}

static void TEST_1_FLAG_1_VALUE_1_OPTION_1_FLAG_1_VALUE()
{
    static clasp::specification_t const Specifications[] =
    {
        CLASP_OPTION("-m", "--multi-opt", NULL, NULL),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };

    char const* argv[] =
    {
        "arg0",
        "-m",
        "v1",
        "--multi-opt=v2",
        "-m",
        "v3",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Specifications, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        char const* v1 = ss_nullptr_k;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--multi-opt", &v1, NULL));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("v1", v1);

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--multi-opt", &v1, NULL));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("v1", v1);

        char const* v2 = ss_nullptr_k;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--multi-opt", &v2, NULL));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("v2", v2);

        char const* v3 = ss_nullptr_k;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--multi-opt", &v3, NULL));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("v3", v3);

        char const* v_ = ss_nullptr_k;

        XTESTS_TEST_BOOLEAN_FALSE(clasp::check_next_option(args, "--multi-opt", &v_, NULL));


        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("arg0", args->programName);


#if __cplusplus >= 201103L

        for (auto const& value : clasp::values(args))
        {
            ((void)&value);

            // XTESTS_TEST_MULTIBYTE_STRING_EQUAL("v1", value);
            // XTESTS_TEST_MULTIBYTE_STRING_EQUAL("v3", value);
        }
#endif
    }
}

static void TEST_1_OPTION()
{
    static clasp::specification_t const Specifications[] =
    {
        CLASP_OPTION("-l", "--length", NULL, NULL),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };

    char const* argv[] =
    {
        "arg0",
        "--length=1",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Specifications, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        int         length_i = 0;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--length", &length_i, 0));
        XTESTS_TEST_INTEGER_EQUAL(1, length_i);

        unsigned    length_u = 0;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--length", &length_u, 0));
        XTESTS_TEST_INTEGER_EQUAL(1u, length_u);

        size_t      length_s = 0;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--length", &length_s, 0));
        XTESTS_TEST_INTEGER_EQUAL(1u, length_s);
    }
}

static void TEST_3_OPTIONS()
{
    static clasp::specification_t const Specifications[] =
    {
        CLASP_OPTION("-l", "--length", NULL, NULL),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };

    char const* argv[] =
    {
        "arg0",
        "--length=1",
        "--length=2",
        "--length=3",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Specifications, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        int         length_1;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_1, 0));
        XTESTS_TEST_INTEGER_EQUAL(1, length_1);

        int         length_2;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_2, 0));
        XTESTS_TEST_INTEGER_EQUAL(2, length_2);

        int         length_3;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_3, 0));
        XTESTS_TEST_INTEGER_EQUAL(3, length_3);

        int         v_;

        XTESTS_TEST_BOOLEAN_FALSE(clasp::check_next_option(args, "--length", &v_, 0));
    }
}

static void TEST_3_OPTIONS_2()
{
    static clasp::specification_t const Specifications[] =
    {
        CLASP_OPTION("-l", "--length", NULL, NULL),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };

    char const* argv[] =
    {
        "arg0",
        "--length=1",
        "--length=2",
        "--length=3",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Specifications, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        unsigned    length_1;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_1, 0));
        XTESTS_TEST_INTEGER_EQUAL(1u, length_1);

        unsigned    length_2;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_2, 0));
        XTESTS_TEST_INTEGER_EQUAL(2u, length_2);

        unsigned    length_3;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_3, 0));
        XTESTS_TEST_INTEGER_EQUAL(3u, length_3);

        unsigned    v_;

        XTESTS_TEST_BOOLEAN_FALSE(clasp::check_next_option(args, "--length", &v_, 0));
    }
}

static void TEST_3_OPTIONS_3()
{
    static clasp::specification_t const Specifications[] =
    {
        CLASP_OPTION("-l", "--length", NULL, NULL),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };

    char const* argv[] =
    {
        "arg0",
        "--length=1.1",
        "--length=2.2",
        "--length=3.3",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Specifications, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        double  length_1;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_1, 0.0));
        XTESTS_TEST_FLOATINGPOINT_EQUAL(1.1, length_1);

        double  length_2;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_2, 0.0));
        XTESTS_TEST_FLOATINGPOINT_EQUAL(2.2, length_2);

        double  length_3;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_3, 0.0));
        XTESTS_TEST_FLOATINGPOINT_EQUAL(3.3, length_3);

        double  v_;

        XTESTS_TEST_BOOLEAN_FALSE(clasp::check_next_option(args, "--length", &v_, 0.0));
    }
}

static void TEST_3_OPTIONS_4()
{
    static clasp::specification_t const Specifications[] =
    {
        CLASP_OPTION("-l", "--length", NULL, NULL),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };

    char const* argv[] =
    {
        "arg0",
        "--length=1",
        "--length=2",
        "--length=3",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Specifications, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        size_t  length_1;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_1, 0));
        XTESTS_TEST_INTEGER_EQUAL(1u, length_1);

        size_t  length_2;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_2, 0));
        XTESTS_TEST_INTEGER_EQUAL(2u, length_2);

        size_t  length_3;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_3, 0));
        XTESTS_TEST_INTEGER_EQUAL(3u, length_3);

        size_t  v_;

        XTESTS_TEST_BOOLEAN_FALSE(clasp::check_next_option(args, "--length", &v_, 0));
    }
}

static void TEST_3_OPTIONS_5()
{
    static clasp::specification_t const Specifications[] =
    {
        CLASP_OPTION("-l", "--length", NULL, NULL),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };

    char const* argv[] =
    {
        "arg0",
        "--length=1",
        "--length=2",
        "--length=3",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Specifications, s_ctxt, &args);

    if (0 != r)
    {
        XTESTS_TEST_FAIL_WITH_ERRNO("could not parse arguments", r);
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        long        length_1;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_1, 0));
        XTESTS_TEST_INTEGER_EQUAL(1, length_1);

        long        length_2;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_2, 0));
        XTESTS_TEST_INTEGER_EQUAL(2, length_2);

        long        length_3;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_3, 0));
        XTESTS_TEST_INTEGER_EQUAL(3, length_3);

        long        v_;

        XTESTS_TEST_BOOLEAN_FALSE(clasp::check_next_option(args, "--length", &v_, 0));
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

