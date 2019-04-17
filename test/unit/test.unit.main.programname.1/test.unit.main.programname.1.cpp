/* /////////////////////////////////////////////////////////////////////////
 * File:        test.unit.main.programname.1.cpp
 *
 * Purpose:     Implementation file for the test.unit.main.programname.1 project.
 *
 * Created:     9th March 2013
 * Updated:     18th April 2019
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2013-2019, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * Test component header file include(s)
 */

static char const* Test_programName;
#define CLASP_MAIN_DEFAULT_PROGRAM_NAME     Test_programName

#include <stdio.h>
static FILE* Real_stderr = stderr;
static FILE* Test_stderr;
#ifdef stderr
# undef stderr
# define CLASP_Test_stderr_was_defined
#endif
#define stderr  Test_stderr

#include <systemtools/clasp/main.hpp>

#undef stderr
#ifdef CLASP_Test_stderr_was_defined
# define stderr Real_stderr
#endif
#undef CLASP_MAIN_DEFAULT_PROGRAM_NAME

#define Test_path                           "test.unit.main.programname.1-stderr.txt"

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>
#include <platformstl/filesystem/file_lines.hpp>

/* Standard C header files */
#include <stdlib.h>

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

} // anonymous namespace

/* /////////////////////////////////////////////////////////////////////////
 * Main
 */

namespace
{
    int setup(void* param)
    {
        ::unlink(static_cast<char const*>(param));

        return 0;
    }
    int teardown(void* param)
    {
        ::unlink(static_cast<char const*>(param));

        return 0;
    }
}

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if(XTESTS_START_RUNNER_WITH_SETUP_FNS("test.unit.main.programname.1", verbosity, setup, teardown, Test_path))
    {
        XTESTS_RUN_CASE(test_1_0);
        XTESTS_RUN_CASE(test_1_1);
        XTESTS_RUN_CASE(test_1_2);
        XTESTS_RUN_CASE(test_1_3);
        XTESTS_RUN_CASE(test_1_4);
        XTESTS_RUN_CASE(test_1_5);
        XTESTS_RUN_CASE(test_1_6);
        XTESTS_RUN_CASE(test_1_7);
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

#define RUN_TEST(argc, argv, pfnMain, png, pna, al, fl, el0)    \
                                                                \
        run_test_(__FILE__, __LINE__, (argc), (argv), (pfnMain), (png), (pna), (al), (fl), (el0))

static void run_test_(
    char const*                 file
,   int                         line
,   int                         argc
,   char const* const* const    argv
,   int (STLSOFT_CDECL*         pfnMain)(clasp::arguments_t const* args)
,   char const*                 programNameGlobal
,   char const*                 programNameArgument
,   clasp::alias_t const*       aliases
,   unsigned                    flags
,   char const*                 expectedLine0
)
{
    Test_programName    =   programNameGlobal;
    Test_stderr         =   ::fopen(Test_path, "w");

    if(NULL == Test_stderr)
    {
        int const e = errno;

        XTESTS_TEST_FAIL_WITH_QUALIFIER("could not create stderr mock file", stlsoft::error_desc(e));

        return;
    }

    int const r = clasp::main::invoke(
                        argc
                    ,   argv
                    ,   pfnMain
                    ,   programNameArgument
                    ,   aliases
                    ,   flags
                    );

    ::fflush(Test_stderr);
    ::fclose(Test_stderr);

    platformstl::file_lines     lines(Test_path);

    XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(1u, lines.size()));
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL(expectedLine0, lines[0]);
}

static void test_1_0()
{
    char const* const   args[] =
    {
        "test_1_0",

        NULL
    };

    struct main_
    {
        static
        int
        fn(
            clasp::arguments_t const* args
        )
        {
            int o;

            clasp::require_option(args, "--unknown", &o);

            return EXIT_FAILURE;
        }
    };

    RUN_TEST(
        int(STLSOFT_NUM_ELEMENTS(args) - 1), args
    ,   &main_::fn
    ,   "program-global-name-1.0", NULL
    ,   NULL
    ,   0
    ,   "program-global-name-1.0: invalid command-line: required option is not found: --unknown"
    );
}

static void test_1_1()
{
    char const* const   args[] =
    {
        "test_1_0",

        NULL
    };

    struct main_
    {
        static
        int
        fn(
            clasp::arguments_t const* args
        )
        {
            int o;

            clasp::require_option(args, "--unknown", &o);

            return EXIT_FAILURE;
        }
    };

    RUN_TEST(
        int(STLSOFT_NUM_ELEMENTS(args) - 1), args
    ,   &main_::fn
    ,   "program-name-1.1", "program-argument-name-1.1"
    ,   NULL
    ,   0
    ,   "program-argument-name-1.1: invalid command-line: required option is not found: --unknown"
    );
}

static void test_1_2()
{
    char const* const   args[] =
    {
        "test_1_0",

        NULL
    };

    struct main_
    {
        static
        int
        fn(
            clasp::arguments_t const* args
        )
        {
            int o;

            clasp::require_option(args, "--unknown", &o);

            return EXIT_FAILURE;
        }
    };

    RUN_TEST(
        int(STLSOFT_NUM_ELEMENTS(args) - 1), args
    ,   &main_::fn
    ,   NULL, "program-argument-name-1.2"
    ,   NULL
    ,   0
    ,   "program-argument-name-1.2: invalid command-line: required option is not found: --unknown"
    );
}

static void test_1_3()
{
    char const* const   args[] =
    {
        "test_1_0",

        NULL
    };

    struct main_
    {
        static
        int
        fn(
            clasp::arguments_t const* args
        )
        {
            int o;

            clasp::require_option(args, "--unknown", &o);

            return EXIT_FAILURE;
        }
    };

    RUN_TEST(
        int(STLSOFT_NUM_ELEMENTS(args) - 1), args
    ,   &main_::fn
    ,   NULL, NULL
    ,   NULL
    ,   0
    ,   "process: invalid command-line: required option is not found: --unknown"
    );
}

static void test_1_4()
{
}

static void test_1_5()
{
}

static void test_1_6()
{
}

static void test_1_7()
{
}

static void test_1_8()
{
}

static void test_1_9()
{
}

static void test_1_10()
{
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
}

static void test_1_15()
{
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


} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */

