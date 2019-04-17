/* /////////////////////////////////////////////////////////////////////////
 * File:        test.unit.clasp++.cpp
 *
 * Purpose:     Implementation file for the test.unit.clasp++ project.
 *
 * Created:     16th July 2009
 * Updated:     18th April 2019
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2009-2019, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * Test component header file include(s)
 */

#include <systemtools/clasp/clasp.hpp>

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
 * Compatibility
 */

#if defined(_MSC_VER) && \
    _MSC_VER >= 1400
# pragma warning(push)
# pragma warning(disable : 4702)
# pragma warning(disable : 4996)
#endif

/* /////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

namespace
{

    static void test_1_0(void);
    static void test_1_1(void);
    static void test_1_2(void);
    static void test_1_3(void);
    static void test_1_4(void);
    static void test_1_5(void);
    static void test_1_6(void);
    static void test_1_7(void);
    static void test_1_8(void);
    static void test_1_9(void);
    static void test_1_10(void);
    static void test_1_11(void);
    static void test_1_12(void);
    static void test_1_13(void);
    static void test_1_14(void);
    static void test_1_15(void);
    static void test_1_16(void);
    static void test_1_17(void);
    static void test_1_18(void);
    static void test_1_19(void);


    static void test_2_01(void);
    static void test_2_02(void);
    static void test_2_03(void);
    static void test_2_04(void);
    static void test_2_05(void);
    static void test_2_06(void);
    static void test_2_07(void);
    static void test_2_08(void);
    static void test_2_09(void);
    static void test_2_10(void);
    static void test_2_11(void);
    static void test_2_12(void);
    static void test_2_13(void);
    static void test_2_14(void);
    static void test_2_15(void);
    static void test_2_16(void);
    static void test_2_17(void);
    static void test_2_18(void);
    static void test_2_19(void);

} // anonymous namespace

/* /////////////////////////////////////////////////////////////////////////
 * Main
 */

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if(XTESTS_START_RUNNER("test.unit.clasp++", verbosity))
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
        XTESTS_RUN_CASE(test_1_8);
        XTESTS_RUN_CASE(test_1_9);
        XTESTS_RUN_CASE(test_1_10);
        XTESTS_RUN_CASE(test_1_11);
        XTESTS_RUN_CASE(test_1_12);
        XTESTS_RUN_CASE(test_1_13);
        XTESTS_RUN_CASE(test_1_14);
        XTESTS_RUN_CASE(test_1_15);
        XTESTS_RUN_CASE(test_1_16);
        XTESTS_RUN_CASE(test_1_17);
        XTESTS_RUN_CASE(test_1_18);
        XTESTS_RUN_CASE(test_1_19);

        XTESTS_RUN_CASE(test_2_01);
        XTESTS_RUN_CASE(test_2_02);
        XTESTS_RUN_CASE(test_2_03);
        XTESTS_RUN_CASE(test_2_04);
        XTESTS_RUN_CASE(test_2_05);
        XTESTS_RUN_CASE(test_2_06);
        XTESTS_RUN_CASE(test_2_07);
        XTESTS_RUN_CASE(test_2_08);
        XTESTS_RUN_CASE(test_2_09);
        XTESTS_RUN_CASE(test_2_10);
        XTESTS_RUN_CASE(test_2_11);
        XTESTS_RUN_CASE(test_2_12);
        XTESTS_RUN_CASE(test_2_13);
        XTESTS_RUN_CASE(test_2_14);
        XTESTS_RUN_CASE(test_2_15);
        XTESTS_RUN_CASE(test_2_16);
        XTESTS_RUN_CASE(test_2_17);
        XTESTS_RUN_CASE(test_2_18);
        XTESTS_RUN_CASE(test_2_19);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

/* /////////////////////////////////////////////////////////////////////////
 * Test function implementations
 */

namespace
{
    using clasp::argument_t;
    using clasp::arguments_t;

static void test_1_0()
{
    char* argv[] =
    {
        "arg0",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(1, args->argc);


        clasp::releaseArguments(args);
    }
}

static void test_1_1()
{
    char* argv[] =
    {
        "arg0",
        "abc",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(2, args->argc);


        clasp::releaseArguments(args);
    }
}

static void test_1_2()
{
    char* argv[] =
    {
        "arg0",
        "abc",
        "-x",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(3, args->argc);


        clasp::releaseArguments(args);
    }
}

static void test_1_3()
{
    char* argv[] =
    {
        "arg0",
        "abc",
        "-",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(3, args->argc);


        clasp::releaseArguments(args);
    }
}

static void test_1_4()
{
    char* argv[] =
    {
        "arg0",
        "abc",
        "--",
        "-",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(4, args->argc);


        clasp::releaseArguments(args);
    }
}

static void test_1_5()
{
    char* argv[] =
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

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        XTESTS_TEST_INTEGER_EQUAL(5u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(4u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(6, args->argc);


        clasp::releaseArguments(args);
    }
}

static void test_1_6()
{
    char* argv[] =
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
        TEST_1_6_SINGLE_X   =   0x0001,
        TEST_1_6_SINGLE_Y   =   0x0002,
        TEST_1_6_DOUBLE_X   =   0x0004,
        TEST_1_6_DOUBLE_Y   =   0x0008,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        XTESTS_TEST_INTEGER_EQUAL(5u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(4u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(6, args->argc);

        int flags = 0;

        clasp::check_flag(args, "-x", &flags, TEST_1_6_SINGLE_X, 0);
        clasp::check_flag(args, "-y", &flags, TEST_1_6_SINGLE_Y, 0);
        clasp::check_flag(args, "-z", &flags, 0, 0);
        clasp::check_flag(args, "--x-argument", &flags, TEST_1_6_DOUBLE_X, 0);
        clasp::check_flag(args, "--y-argument", &flags, TEST_1_6_DOUBLE_Y, 0);

        XTESTS_TEST_INTEGER_EQUAL(TEST_1_6_SINGLE_X | TEST_1_6_SINGLE_Y | TEST_1_6_DOUBLE_X, flags);


        clasp::releaseArguments(args);
    }
}

static void test_1_7()
{
    char* argv[] =
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
        TEST_1_6_SINGLE_X   =   0x0001,
        TEST_1_6_SINGLE_Y   =   0x0002,
        TEST_1_6_DOUBLE_X   =   0x0004,
        TEST_1_6_DOUBLE_Y   =   0x0008,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
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

        int flags = 0;

        clasp::check_flag(args, "-x", &flags, TEST_1_6_SINGLE_X, 0);
        clasp::check_flag(args, "-y", &flags, TEST_1_6_SINGLE_Y, 0);
        clasp::check_flag(args, "-z", &flags, 0, 0);
        clasp::check_flag(args, "--x-argument", &flags, TEST_1_6_DOUBLE_X, 0);
        clasp::check_flag(args, "--y-argument", &flags, TEST_1_6_DOUBLE_Y, 0);

        XTESTS_TEST_FAIL("should never get here!");
    }
}

static void test_1_8()
{
}

static void test_1_9()
{
}

static void test_1_10()
{
    char* argv[] =
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

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        XTESTS_TEST_INTEGER_EQUAL(5u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(4u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(6, args->argc);


        clasp::releaseArguments(args);
    }
}

static void test_1_11()
{
}

static void test_1_12()
{
}

static void test_1_13()
{
}

static void test_1_14()
{
    char* argv[] =
    {
            "arg0"
        ,   "--option-1=true"
        ,   "--option-2=false"
        //  "--option-3=true"
        ,   NULL
    };

    enum
    {
        TEST_1_14_OPTION_1  =   0x0001,
        TEST_1_14_OPTION_2  =   0x0002,
        TEST_1_14_OPTION_3  =   0x0004,
        TEST_1_14_OPTION_4  =   0x0008,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
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

static void test_1_15()
{
    char* argv[] =
    {
        "arg0",
        "--clipboard",
        "H:\\dev\\srctools\\number_lines\\implicit_link.cpp",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, NULL, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        XTESTS_TEST_INTEGER_EQUAL(2u, args->numArguments);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numFlagsAndOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numFlags);
        XTESTS_TEST_INTEGER_EQUAL(0u, args->numOptions);
        XTESTS_TEST_INTEGER_EQUAL(1u, args->numValues);
        XTESTS_TEST_INTEGER_EQUAL(3, args->argc);


        clasp::releaseArguments(args);
    }
}

static void test_1_16()
{
}

static void test_1_17()
{
}

static void test_1_18()
{
}

static void test_1_19()
{
}


static void test_2_01()
{
    static clasp::alias_t const Aliases[] =
    {
        CLASP_FLAG("-v", "--version", NULL),

        CLASP_ALIAS_ARRAY_TERMINATOR
    };

    char* argv[] =
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

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Aliases, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
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


        clasp::releaseArguments(args);
    }
}

static void test_2_02(void)
{
    static clasp::alias_t const Aliases[] =
    {
        CLASP_FLAG("-v", "--version", NULL),

        CLASP_OPTION("-b", "--boolopt2", NULL, "|true|false"),

        CLASP_ALIAS_ARRAY_TERMINATOR
    };

    char* argv[] =
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

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Aliases, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
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


        clasp::releaseArguments(args);
    }
}

static void test_2_03(void)
{
    static clasp::alias_t const Aliases[] =
    {
        CLASP_FLAG("-v", "--version", NULL),

        CLASP_OPTION(NULL, "--boolopt2", NULL, "|true|false"),

        CLASP_ALIAS_ARRAY_TERMINATOR
    };

    char* argv[] =
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

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Aliases, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
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


        clasp::releaseArguments(args);
    }
}

static void test_2_04(void)
{
    static clasp::alias_t const Aliases[] =
    {
        CLASP_FLAG("-v", "--version", NULL),

        CLASP_OPTION(NULL, "--boolopt2", NULL, "|true|false"),

        CLASP_ALIAS_ARRAY_TERMINATOR
    };

    char* argv[] =
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

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Aliases, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
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


        clasp::releaseArguments(args);
    }
}

static void test_2_05(void)
{
    static clasp::alias_t const Aliases[] =
    {
        CLASP_FLAG("-v", "--version", NULL),

        CLASP_OPTION(NULL, "--boolopt2", NULL, "|true|false"),

        CLASP_ALIAS_ARRAY_TERMINATOR
    };

    char* argv[] =
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

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Aliases, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
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


        clasp::releaseArguments(args);
    }
}

static void test_2_06(void)
{
}

static void test_2_07(void)
{
    static clasp::alias_t const Aliases[] =
    {
        CLASP_OPTION("-m", "--multi-opt", NULL, NULL),

        CLASP_ALIAS_ARRAY_TERMINATOR
    };

    char* argv[] =
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

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Aliases, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        char const* v1;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--multi-opt", &v1, NULL));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("v1", v1);

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--multi-opt", &v1, NULL));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("v1", v1);

        char const* v2;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--multi-opt", &v2, NULL));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("v2", v2);

        char const* v3;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--multi-opt", &v3, NULL));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("v3", v3);

        char const* v_;

        XTESTS_TEST_BOOLEAN_FALSE(clasp::check_next_option(args, "--multi-opt", &v_, NULL));


        clasp::releaseArguments(args);
    }
}

static void test_2_08(void)
{
    static clasp::alias_t const Aliases[] =
    {
        CLASP_OPTION("-l", "--length", NULL, NULL),

        CLASP_ALIAS_ARRAY_TERMINATOR
    };

    char* argv[] =
    {
        "arg0",
        "--length=1",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Aliases, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        int         length_i;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--length", &length_i, NULL));
        XTESTS_TEST_INTEGER_EQUAL(1, length_i);

        unsigned    length_u;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--length", &length_u, NULL));
        XTESTS_TEST_INTEGER_EQUAL(1u, length_u);

        size_t      length_s;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--length", &length_s, NULL));
        XTESTS_TEST_INTEGER_EQUAL(1u, length_s);


        clasp::releaseArguments(args);
    }
}

static void test_2_09(void)
{
    static clasp::alias_t const Aliases[] =
    {
        CLASP_OPTION("-l", "--length", NULL, NULL),

        CLASP_ALIAS_ARRAY_TERMINATOR
    };

    char* argv[] =
    {
        "arg0",
        "--length=1",
        "--length=2",
        "--length=3",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Aliases, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        int         length_1;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_1, NULL));
        XTESTS_TEST_INTEGER_EQUAL(1, length_1);

        int         length_2;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_2, NULL));
        XTESTS_TEST_INTEGER_EQUAL(2, length_2);

        int         length_3;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_3, NULL));
        XTESTS_TEST_INTEGER_EQUAL(3, length_3);

        int         v_;

        XTESTS_TEST_BOOLEAN_FALSE(clasp::check_next_option(args, "--length", &v_, NULL));


        clasp::releaseArguments(args);
    }
}

static void test_2_10(void)
{
    static clasp::alias_t const Aliases[] =
    {
        CLASP_OPTION("-l", "--length", NULL, NULL),

        CLASP_ALIAS_ARRAY_TERMINATOR
    };

    char* argv[] =
    {
        "arg0",
        "--length=1",
        "--length=2",
        "--length=3",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Aliases, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        unsigned    length_1;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_1, NULL));
        XTESTS_TEST_INTEGER_EQUAL(1u, length_1);

        unsigned    length_2;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_2, NULL));
        XTESTS_TEST_INTEGER_EQUAL(2u, length_2);

        unsigned    length_3;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_3, NULL));
        XTESTS_TEST_INTEGER_EQUAL(3u, length_3);

        unsigned    v_;

        XTESTS_TEST_BOOLEAN_FALSE(clasp::check_next_option(args, "--length", &v_, NULL));


        clasp::releaseArguments(args);
    }
}

static void test_2_11(void)
{
    static clasp::alias_t const Aliases[] =
    {
        CLASP_OPTION("-l", "--length", NULL, NULL),

        CLASP_ALIAS_ARRAY_TERMINATOR
    };

    char* argv[] =
    {
        "arg0",
        "--length=1.1",
        "--length=2.2",
        "--length=3.3",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Aliases, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        double  length_1;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_1, NULL));
        XTESTS_TEST_FLOATINGPOINT_EQUAL(1.1, length_1);

        double  length_2;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_2, NULL));
        XTESTS_TEST_FLOATINGPOINT_EQUAL(2.2, length_2);

        double  length_3;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_3, NULL));
        XTESTS_TEST_FLOATINGPOINT_EQUAL(3.3, length_3);

        double  v_;

        XTESTS_TEST_BOOLEAN_FALSE(clasp::check_next_option(args, "--length", &v_, NULL));


        clasp::releaseArguments(args);
    }
}

static void test_2_12(void)
{
    static clasp::alias_t const Aliases[] =
    {
        CLASP_OPTION("-l", "--length", NULL, NULL),

        CLASP_ALIAS_ARRAY_TERMINATOR
    };

    char* argv[] =
    {
        "arg0",
        "--length=1",
        "--length=2",
        "--length=3",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Aliases, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        size_t  length_1;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_1, NULL));
        XTESTS_TEST_INTEGER_EQUAL(1u, length_1);

        size_t  length_2;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_2, NULL));
        XTESTS_TEST_INTEGER_EQUAL(2u, length_2);

        size_t  length_3;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_3, NULL));
        XTESTS_TEST_INTEGER_EQUAL(3u, length_3);

        size_t  v_;

        XTESTS_TEST_BOOLEAN_FALSE(clasp::check_next_option(args, "--length", &v_, NULL));


        clasp::releaseArguments(args);
    }
}

static void test_2_13(void)
{
    static clasp::alias_t const Aliases[] =
    {
        CLASP_OPTION("-l", "--length", NULL, NULL),

        CLASP_ALIAS_ARRAY_TERMINATOR
    };

    char* argv[] =
    {
        "arg0",
        "--length=1",
        "--length=2",
        "--length=3",
        NULL,
    };

    arguments_t const*  args;
    int r;

    r = clasp::parseArguments(0, STLSOFT_NUM_ELEMENTS(argv) - 1, argv, Aliases, NULL, &args);

    if(0 != r)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not parse arguments", stlsoft::error_desc(r));
    }
    else
    {
        long        length_1;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_1, NULL));
        XTESTS_TEST_INTEGER_EQUAL(1, length_1);

        long        length_2;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_2, NULL));
        XTESTS_TEST_INTEGER_EQUAL(2, length_2);

        long        length_3;

        XTESTS_TEST_BOOLEAN_TRUE(clasp::check_next_option(args, "--length", &length_3, NULL));
        XTESTS_TEST_INTEGER_EQUAL(3, length_3);

        long        v_;

        XTESTS_TEST_BOOLEAN_FALSE(clasp::check_next_option(args, "--length", &v_, NULL));


        clasp::releaseArguments(args);
    }
}

static void test_2_14(void)
{
}

static void test_2_15(void)
{
}

static void test_2_16(void)
{
}

static void test_2_17(void)
{
}

static void test_2_18(void)
{
}

static void test_2_19(void)
{
}


} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */

