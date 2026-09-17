/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.clasp++/entry.cpp
 *
 * Purpose: Unit-tests for CLASP C++ API
 *
 * Created: 16th July 2009
 * Updated: 17th September 2026
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
#include <stlsoft/error/error_desc.hpp> // required for GCC template lookup
#include <xtests/terse-api.h>

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


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    static void test_1_0();
    static void test_1_1();
    static void test_1_2();
    static void test_1_3();
    static void test_1_4();
    static void test_1_5();
    static void test_1_6();
    static void test_1_7();
    static void test_1_10();
    static void test_1_14();
    static void test_1_15();

    static void test_2_01();
    static void test_2_01_c();
    static void test_2_02();
    static void test_2_03();
    static void test_2_04();
    static void test_2_05();
    static void test_2_07();
    static void test_2_08();
    static void test_2_09();
    static void test_2_10();
    static void test_2_11();
    static void test_2_12();
    static void test_2_13();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * globals
 */

clasp_diagnostic_context_t const*   s_ctxt;


/* /////////////////////////////////////////////////////////////////////////
 * main()
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
        XTESTS_RUN_CASE(test_2_04);
#endif /* 0 */

        XTESTS_RUN_CASE(test_1_0);
        XTESTS_RUN_CASE(test_1_1);
        XTESTS_RUN_CASE(test_1_2);
        XTESTS_RUN_CASE(test_1_3);
        XTESTS_RUN_CASE(test_1_4);
        XTESTS_RUN_CASE(test_1_5);
        XTESTS_RUN_CASE(test_1_6);
        XTESTS_RUN_CASE_THAT_THROWS(test_1_7, clasp::invalid_option_value_exception);
        XTESTS_RUN_CASE(test_1_10);
        XTESTS_RUN_CASE(test_1_14);
        XTESTS_RUN_CASE(test_1_15);

        XTESTS_RUN_CASE(test_2_01);
        XTESTS_RUN_CASE(test_2_01_c);
        XTESTS_RUN_CASE(test_2_02);
        XTESTS_RUN_CASE(test_2_03);
        XTESTS_RUN_CASE(test_2_04);
        XTESTS_RUN_CASE(test_2_05);
        XTESTS_RUN_CASE(test_2_07);
        XTESTS_RUN_CASE(test_2_08);
        XTESTS_RUN_CASE(test_2_09);
        XTESTS_RUN_CASE(test_2_10);
        XTESTS_RUN_CASE(test_2_11);
        XTESTS_RUN_CASE(test_2_12);
        XTESTS_RUN_CASE(test_2_13);

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

static void test_1_0()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        TEST_INT_EQ(0u, args->numArguments);
        TEST_INT_EQ(0u, args->numFlagsAndOptions);
        TEST_INT_EQ(0u, args->numFlags);
        TEST_INT_EQ(0u, args->numOptions);
        TEST_INT_EQ(0u, args->numValues);
        TEST_INT_EQ(1, args->argc);
        TEST_MS_EQ("arg0", args->programName);


        clasp::releaseArguments(args);
    }
}

static void test_1_1()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        TEST_INT_EQ(1u, args->numArguments);
        TEST_INT_EQ(0u, args->numFlagsAndOptions);
        TEST_INT_EQ(0u, args->numFlags);
        TEST_INT_EQ(0u, args->numOptions);
        TEST_INT_EQ(1u, args->numValues);
        TEST_INT_EQ(2, args->argc);
        TEST_MS_EQ("arg0", args->programName);


        clasp::releaseArguments(args);
    }
}

static void test_1_2()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        TEST_INT_EQ(2u, args->numArguments);
        TEST_INT_EQ(1u, args->numFlagsAndOptions);
        TEST_INT_EQ(1u, args->numFlags);
        TEST_INT_EQ(0u, args->numOptions);
        TEST_INT_EQ(1u, args->numValues);
        TEST_INT_EQ(3, args->argc);
        TEST_MS_EQ("arg0", args->programName);


        clasp::releaseArguments(args);
    }
}

static void test_1_3()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        TEST_INT_EQ(2u, args->numArguments);
        TEST_INT_EQ(1u, args->numFlagsAndOptions);
        TEST_INT_EQ(1u, args->numFlags);
        TEST_INT_EQ(0u, args->numOptions);
        TEST_INT_EQ(1u, args->numValues);
        TEST_INT_EQ(3, args->argc);
        TEST_MS_EQ("arg0", args->programName);


        clasp::releaseArguments(args);
    }
}

static void test_1_4()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        TEST_INT_EQ(2u, args->numArguments);
        TEST_INT_EQ(0u, args->numFlagsAndOptions);
        TEST_INT_EQ(0u, args->numFlags);
        TEST_INT_EQ(0u, args->numOptions);
        TEST_INT_EQ(2u, args->numValues);
        TEST_INT_EQ(4, args->argc);
        TEST_MS_EQ("arg0", args->programName);


        clasp::releaseArguments(args);
    }
}

static void test_1_5()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        TEST_INT_EQ(5u, args->numArguments);
        TEST_INT_EQ(4u, args->numFlagsAndOptions);
        TEST_INT_EQ(2u, args->numFlags);
        TEST_INT_EQ(2u, args->numOptions);
        TEST_INT_EQ(1u, args->numValues);
        TEST_INT_EQ(6, args->argc);
        TEST_MS_EQ("arg0", args->programName);


        clasp::releaseArguments(args);
    }
}

static void test_1_6()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        TEST_INT_EQ(5u, args->numArguments);
        TEST_INT_EQ(4u, args->numFlagsAndOptions);
        TEST_INT_EQ(2u, args->numFlags);
        TEST_INT_EQ(2u, args->numOptions);
        TEST_INT_EQ(1u, args->numValues);
        TEST_INT_EQ(6, args->argc);
        TEST_MS_EQ("arg0", args->programName);

        int flags = 0;

        clasp::check_flag(args, "-x", &flags, TEST_1_6_SINGLE_X, 0);
        clasp::check_flag(args, "-y", &flags, TEST_1_6_SINGLE_Y, 0);
        clasp::check_flag(args, "-z", &flags, 0, 0);
        clasp::check_flag(args, "--x-argument", &flags, TEST_1_6_DOUBLE_X, 0);
        clasp::check_flag(args, "--y-argument", &flags, TEST_1_6_DOUBLE_Y, 0);

        TEST_INT_EQ(TEST_1_6_SINGLE_X | TEST_1_6_SINGLE_Y | TEST_1_6_DOUBLE_X, flags);


        clasp::releaseArguments(args);
    }
}

static void test_1_7()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        TEST_INT_EQ(5u, args->numArguments);
        TEST_INT_EQ(4u, args->numFlagsAndOptions);
        TEST_INT_EQ(2u, args->numFlags);
        TEST_INT_EQ(2u, args->numOptions);
        TEST_INT_EQ(1u, args->numValues);
        TEST_INT_EQ(6, args->argc);
        TEST_MS_EQ("arg0", args->programName);

        int flags = 0;

        clasp::check_flag(args, "-x", &flags, TEST_1_6_SINGLE_X, 0);
        clasp::check_flag(args, "-y", &flags, TEST_1_6_SINGLE_Y, 0);
        clasp::check_flag(args, "-z", &flags, 0, 0);
        clasp::check_flag(args, "--x-argument", &flags, TEST_1_6_DOUBLE_X, 0);
        clasp::check_flag(args, "--y-argument", &flags, TEST_1_6_DOUBLE_Y, 0);

        TEST_FAIL("should never get here!");
    }
}

static void test_1_10()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        TEST_INT_EQ(5u, args->numArguments);
        TEST_INT_EQ(4u, args->numFlagsAndOptions);
        TEST_INT_EQ(2u, args->numFlags);
        TEST_INT_EQ(2u, args->numOptions);
        TEST_INT_EQ(1u, args->numValues);
        TEST_INT_EQ(6, args->argc);
        TEST_MS_EQ("arg0", args->programName);


        clasp::releaseArguments(args);
    }
}

static void test_1_14()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        stlsoft::scoped_handle<arguments_t const*> scoper(args, clasp::releaseArguments);

        TEST_INT_EQ(2u, args->numArguments);
        TEST_INT_EQ(2u, args->numFlagsAndOptions);
        TEST_INT_EQ(0u, args->numFlags);
        TEST_INT_EQ(2u, args->numOptions);
        TEST_INT_EQ(0u, args->numValues);
        TEST_INT_EQ(3, args->argc);
        TEST_MS_EQ("arg0", args->programName);

        int flags = 0;

        clasp::check_flags_option(args, "--option-1", &flags, TEST_1_14_OPTION_1);
        TEST_INT_EQ(0x0001, flags);
        clasp::check_flags_option(args, "--option-2", &flags, TEST_1_14_OPTION_2);
        TEST_INT_EQ(0x0001, flags);
        clasp::check_flags_option(args, "--option-3", &flags, TEST_1_14_OPTION_3, TEST_1_14_OPTION_3);
        TEST_INT_EQ(0x0005, flags);
        clasp::check_flags_option(args, "--option-4", &flags, TEST_1_14_OPTION_4);
        TEST_INT_EQ(0x0005, flags);

        TEST_PASSED();
    }
}

static void test_1_15()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        TEST_INT_EQ(2u, args->numArguments);
        TEST_INT_EQ(1u, args->numFlagsAndOptions);
        TEST_INT_EQ(1u, args->numFlags);
        TEST_INT_EQ(0u, args->numOptions);
        TEST_INT_EQ(1u, args->numValues);
        TEST_INT_EQ(3, args->argc);
        TEST_MS_EQ("arg0", args->programName);


        clasp::releaseArguments(args);
    }
}


static void test_2_01()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        bool    v;

        TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--nonexistant"));
        TEST_BOOLEAN_FALSE(clasp::check_flag(args, "--nonexistant", &v));
        TEST_BOOLEAN_FALSE(v);

        TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--version"));
        TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--version", &v));
        TEST_BOOLEAN_TRUE(v);

        TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt1"));
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt1", &v, false));
        TEST_BOOLEAN_TRUE(v);
        TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt1", &v));
        TEST_BOOLEAN_TRUE(v);

        TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt2"));
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, true));
        TEST_BOOLEAN_FALSE(v);
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, false));
        TEST_BOOLEAN_FALSE(v);
        TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt2", &v));
        TEST_BOOLEAN_FALSE(v);

        TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--boolopt3"));

        TEST_MS_EQ("arg0", args->programName);


        clasp::releaseArguments(args);
    }
}

static void test_2_01_c()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        bool    v;

        TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--nonexistant"));
        TEST_BOOLEAN_FALSE(clasp::check_flag(args, "--nonexistant", &v));
        TEST_BOOLEAN_FALSE(v);

        TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--version"));
        TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--version", &v));
        TEST_BOOLEAN_TRUE(v);

        TEST_BOOLEAN_TRUE(clasp::flag_specified(args, Alias_Flag_Version));
        TEST_BOOLEAN_TRUE(clasp::check_flag(args, Alias_Flag_Version, &v));
        TEST_BOOLEAN_TRUE(v);

        TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt1"));
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt1", &v, false));
        TEST_BOOLEAN_TRUE(v);
        TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt1", &v));
        TEST_BOOLEAN_TRUE(v);

        TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt2"));
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, true));
        TEST_BOOLEAN_FALSE(v);
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, false));
        TEST_BOOLEAN_FALSE(v);
        TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt2", &v));
        TEST_BOOLEAN_FALSE(v);

        TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--boolopt3"));

        TEST_MS_EQ("arg0", args->programName);


        clasp::releaseArguments(args);
    }
}

static void test_2_02()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        bool    v;

        TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--nonexistant"));
        TEST_BOOLEAN_FALSE(clasp::check_flag(args, "--nonexistant", &v));
        TEST_BOOLEAN_FALSE(v);

        TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--version"));
        TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--version", &v));
        TEST_BOOLEAN_TRUE(v);

        TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt1"));
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt1", &v, false));
        TEST_BOOLEAN_TRUE(v);
        TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt1", &v));
        TEST_BOOLEAN_TRUE(v);

        TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt2"));
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, true));
        TEST_BOOLEAN_FALSE(v);
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, false));
        TEST_BOOLEAN_FALSE(v);
        TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt2", &v));
        TEST_BOOLEAN_FALSE(v);

        TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--boolopt3"));

        TEST_MS_EQ("arg0", args->programName);


        clasp::releaseArguments(args);
    }
}

static void test_2_03()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        bool    v;

        TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--nonexistant"));
        TEST_BOOLEAN_FALSE(clasp::check_flag(args, "--nonexistant", &v));
        TEST_BOOLEAN_FALSE(v);

        TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--version"));
        TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--version", &v));
        TEST_BOOLEAN_TRUE(v);

        TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt1"));
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt1", &v, false));
        TEST_BOOLEAN_TRUE(v);
        TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt1", &v));
        TEST_BOOLEAN_TRUE(v);

        TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt2"));
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, true));
        TEST_BOOLEAN_TRUE(v);
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, false));
        TEST_BOOLEAN_TRUE(v);
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, false, false));
        TEST_BOOLEAN_FALSE(v);

        TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--boolopt3"));

        TEST_MS_EQ("arg0", args->programName);


        clasp::releaseArguments(args);
    }
}

static void test_2_04()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        bool    v;

        TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--nonexistant"));
        TEST_BOOLEAN_FALSE(clasp::check_flag(args, "--nonexistant", &v));
        TEST_BOOLEAN_FALSE(v);

        TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--version"));
        TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--version", &v));
        TEST_BOOLEAN_TRUE(v);

        TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt1"));
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt1", &v, false));
        TEST_BOOLEAN_TRUE(v);
        TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt1", &v));
        TEST_BOOLEAN_TRUE(v);

        TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt2"));
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, true));
        TEST_BOOLEAN_TRUE(v);
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, false));
        TEST_BOOLEAN_TRUE(v);
        TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt2", &v));
        TEST_BOOLEAN_TRUE(v);

        TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--boolopt3"));

        TEST_MS_EQ("arg0", args->programName);


        clasp::releaseArguments(args);
    }
}

static void test_2_05()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        bool    v;

        TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--nonexistant"));
        TEST_BOOLEAN_FALSE(clasp::check_flag(args, "--nonexistant", &v));
        TEST_BOOLEAN_FALSE(v);

        TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--version"));
        TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--version", &v));
        TEST_BOOLEAN_TRUE(v);

        TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt1"));
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt1", &v, false));
        TEST_BOOLEAN_TRUE(v);
        TEST_BOOLEAN_TRUE(clasp::check_flag(args, "--boolopt1", &v));
        TEST_BOOLEAN_TRUE(v);

        TEST_BOOLEAN_FALSE(clasp::flag_specified(args, "--boolopt2"));
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, true));
        TEST_BOOLEAN_TRUE(v);
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, false));
        TEST_BOOLEAN_TRUE(v);
        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--boolopt2", &v, false, false));
        TEST_BOOLEAN_FALSE(v);

        TEST_BOOLEAN_TRUE(clasp::flag_specified(args, "--boolopt3"));

        TEST_MS_EQ("arg0", args->programName);


        clasp::releaseArguments(args);
    }
}

static void test_2_07()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        char const* v1 = ss_nullptr_k;

        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--multi-opt", &v1, NULL));
        TEST_MS_EQ("v1", v1);

        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--multi-opt", &v1, NULL));
        TEST_MS_EQ("v1", v1);

        char const* v2 = ss_nullptr_k;

        TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--multi-opt", &v2, NULL));
        TEST_MS_EQ("v2", v2);

        char const* v3 = ss_nullptr_k;

        TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--multi-opt", &v3, NULL));
        TEST_MS_EQ("v3", v3);

        char const* v_ = ss_nullptr_k;

        TEST_BOOLEAN_FALSE(clasp::check_next_option(args, "--multi-opt", &v_, NULL));


        TEST_MS_EQ("arg0", args->programName);


        clasp::releaseArguments(args);
    }
}

static void test_2_08()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        int         length_i = 0;

        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--length", &length_i, 0));
        TEST_INT_EQ(1, length_i);

        unsigned    length_u = 0;

        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--length", &length_u, 0));
        TEST_INT_EQ(1u, length_u);

        size_t      length_s = 0;

        TEST_BOOLEAN_TRUE(clasp::check_option(args, "--length", &length_s, 0));
        TEST_INT_EQ(1u, length_s);


        clasp::releaseArguments(args);
    }
}

static void test_2_09()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        int         length_1;

        TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_1, 0));
        TEST_INT_EQ(1, length_1);

        int         length_2;

        TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_2, 0));
        TEST_INT_EQ(2, length_2);

        int         length_3;

        TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_3, 0));
        TEST_INT_EQ(3, length_3);

        int         v_;

        TEST_BOOLEAN_FALSE(clasp::check_next_option(args, "--length", &v_, 0));


        clasp::releaseArguments(args);
    }
}

static void test_2_10()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        unsigned    length_1;

        TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_1, 0));
        TEST_INT_EQ(1u, length_1);

        unsigned    length_2;

        TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_2, 0));
        TEST_INT_EQ(2u, length_2);

        unsigned    length_3;

        TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_3, 0));
        TEST_INT_EQ(3u, length_3);

        unsigned    v_;

        TEST_BOOLEAN_FALSE(clasp::check_next_option(args, "--length", &v_, 0));


        clasp::releaseArguments(args);
    }
}

static void test_2_11()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        double  length_1;

        TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_1, 0.0));
        TEST_FP_EQ(1.1, length_1);

        double  length_2;

        TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_2, 0.0));
        TEST_FP_EQ(2.2, length_2);

        double  length_3;

        TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_3, 0.0));
        TEST_FP_EQ(3.3, length_3);

        double  v_;

        TEST_BOOLEAN_FALSE(clasp::check_next_option(args, "--length", &v_, 0.0));


        clasp::releaseArguments(args);
    }
}

static void test_2_12()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        size_t  length_1;

        TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_1, 0));
        TEST_INT_EQ(1u, length_1);

        size_t  length_2;

        TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_2, 0));
        TEST_INT_EQ(2u, length_2);

        size_t  length_3;

        TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_3, 0));
        TEST_INT_EQ(3u, length_3);

        size_t  v_;

        TEST_BOOLEAN_FALSE(clasp::check_next_option(args, "--length", &v_, 0));


        clasp::releaseArguments(args);
    }
}

static void test_2_13()
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
        TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        long        length_1;

        TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_1, 0));
        TEST_INT_EQ(1, length_1);

        long        length_2;

        TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_2, 0));
        TEST_INT_EQ(2, length_2);

        long        length_3;

        TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_3, 0));
        TEST_INT_EQ(3, length_3);

        long        v_;

        TEST_BOOLEAN_FALSE(clasp::check_next_option(args, "--length", &v_, 0));


        clasp::releaseArguments(args);
    }
}

} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

