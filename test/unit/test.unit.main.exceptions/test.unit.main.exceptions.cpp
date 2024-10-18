/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.main.exceptions.cpp
 *
 * Purpose: Unit-tests exceptional inputs
 *
 * Created: 7th March 2013
 * Updated: 12th July 2024
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

static char const* Test_programName;
#define CLASP_MAIN_DEFAULT_PROGRAM_NAME                     Test_programName

#include <stdio.h>
#ifdef stderr
static FILE* Real_stderr = stderr;
static FILE* Test_stderr = Real_stderr; /* NOTE: this assignment here is solely to placate the compiler when it thinks `Real_stderr` not used */
# undef stderr
# define CLASP_Test_stderr_was_defined
#endif
#define stderr                                              Test_stderr

#include <clasp/main.hpp>

#undef stderr
#ifdef CLASP_Test_stderr_was_defined
# define stderr                                             Real_stderr
#endif
#undef CLASP_MAIN_DEFAULT_PROGRAM_NAME

#define Test_path                                           "test.unit.main.exceptions-stderr.txt"


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
 * compatibility
 */

#if 0 ||\
    defined(_MSC_VER) ||\
    0
# define unlink                                             _unlink
#endif


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    static void test_1_0(void);
    static void test_1_1(void);
    static void test_1_1_unrecognised(void);
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
 * main
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

    if (XTESTS_START_RUNNER_WITH_SETUP_FNS("test.unit.main.exceptions", verbosity, setup, teardown, const_cast<char*>(Test_path)))
    {
        XTESTS_RUN_CASE(test_1_0);
        XTESTS_RUN_CASE(test_1_1);
        XTESTS_RUN_CASE(test_1_1_unrecognised);
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
 * test function implementations
 */

namespace
{

#define RUN_TEST(argc, argv, pfnMain, png, pna, al, fl, el0)    \
                                                                \
        run_test_(__FILE__, __LINE__, XTESTS_GET_FUNCTION_(), (argc), (argv), (pfnMain), (png), (pna), (al), (fl), (el0))

static void run_test_(
    char const*                     file
,   int                             line
,   char const*                     function
,   int                             argc
,   char const* const* const        argv
,   int (STLSOFT_CDECL*             pfnMain)(clasp::arguments_t const* args)
,   char const*                     programNameGlobal
,   char const*                     programNameArgument
,   clasp::specification_t const    specifications[]
,   unsigned                        flags
,   char const*                     expectedLine0
)
{
    Test_programName    =   programNameGlobal;
    Test_stderr         =   ::fopen(Test_path, "w");

    if (NULL == Test_stderr)
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
                    ,   specifications
                    ,   flags
                    );

    XTESTS_REQUIRE(XTESTS_TEST_INTEGER_NOT_EQUAL(0, r));

    ::fflush(Test_stderr);
    ::fclose(Test_stderr);

    platformstl::file_lines     lines(Test_path);

    if (!XTESTS_NS_C_QUAL(xTests_hasRequiredConditionFailed()))
    {
        XTESTS_REQUIRE(XTESTS_NS_CPP_QUAL(xtests_test_integer(file, line, function, "", 1u, lines.size(), XTESTS_NS_C_QUAL(xtestsComparisonEqual))));
    }

    if (!XTESTS_NS_C_QUAL(xTests_hasRequiredConditionFailed()))
    {
        XTESTS_NS_C_QUAL(xtests_testMultibyteStrings)(file, line, function, "", expectedLine0, lines[0], XTESTS_NS_C_QUAL(xtestsComparisonEqual));
    }
}

static void test_1_0()
{
    static char const* const args[] =
    {
        "program-path-1.0",

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

            try
            {
                clasp::require_option(args, "--unknown", &o);
                XTESTS_TEST_FAIL("should not get here");
            }
            catch(std::bad_alloc&)
            {
                throw;
            }
            catch(clasp::missing_option_exception&)
            {
                XTESTS_TEST_PASSED();
                throw;
            }
            catch(std::exception&)
            {
                XTESTS_TEST_FAIL("should not get here");
                throw;
            }

            return EXIT_FAILURE;
        }
    };

    RUN_TEST(
        int(STLSOFT_NUM_ELEMENTS(args) - 1), args
    ,   &main_::fn
    ,   NULL, NULL
    ,   NULL
    ,   0
    ,   "program-path-1.0: invalid command-line: required option is not found: --unknown"
    );
}

static void test_1_1()
{
    static char const* const args[] =
    {
        "program-path-1.1",

        "--x",

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
            try
            {
                clasp::verify_all_options_used(args);
                XTESTS_TEST_FAIL("should not get here");
            }
            catch(std::bad_alloc&)
            {
                throw;
            }
            catch(clasp::unused_argument_exception&)
            {
                XTESTS_TEST_PASSED();
                throw;
            }
            catch(std::exception&)
            {
                XTESTS_TEST_FAIL("should not get here");
                throw;
            }

            return EXIT_FAILURE;
        }
    };

    RUN_TEST(
        int(STLSOFT_NUM_ELEMENTS(args) - 1), args
    ,   &main_::fn
    ,   NULL, NULL
    ,   NULL
    ,   0
    ,   "program-path-1.1: invalid command-line: unused argument: --x"
    );
}

static void test_1_1_unrecognised()
{
    static char const* const args[] =
    {
        "program-path-1.1",

        "--x",

        NULL
    };

    static clasp::specification_t const s_specifications[] =
    {
      CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };

    struct main_
    {
        static
        int
        fn(
            clasp::arguments_t const* args
        )
        {
            try
            {
                clasp::verify_all_flags_and_options_are_recognised(args, s_specifications);
                XTESTS_TEST_FAIL("should not get here");
            }
            catch(std::bad_alloc&)
            {
                throw;
            }
            catch(clasp::unrecognised_argument_exception&)
            {
                XTESTS_TEST_PASSED();
                throw;
            }
            catch(std::exception&)
            {
                XTESTS_TEST_FAIL("should not get here");
                throw;
            }

            return EXIT_FAILURE;
        }
    };

    RUN_TEST(
        int(STLSOFT_NUM_ELEMENTS(args) - 1), args
    ,   &main_::fn
    ,   NULL, NULL
    ,   s_specifications
    ,   0
    ,   "program-path-1.1: invalid command-line: unrecognised argument: --x"
    );
}

static void test_1_2()
{
    static char const* const args[] =
    {
        "program-path-1.2",

        "--opt=",

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
            int opt;

            try
            {
                clasp::require_option(args, "--opt", &opt);
                XTESTS_TEST_FAIL("should not get here");
            }
            catch(std::bad_alloc&)
            {
                throw;
            }
            catch(clasp::missing_option_value_exception&)
            {
                XTESTS_TEST_PASSED();
                throw;
            }
            catch(std::exception&)
            {
                XTESTS_TEST_FAIL("should not get here");
                throw;
            }

            return EXIT_FAILURE;
        }
    };

    RUN_TEST(
        int(STLSOFT_NUM_ELEMENTS(args) - 1), args
    ,   &main_::fn
    ,   NULL, NULL
    ,   NULL
    ,   0
    ,   "program-path-1.2: invalid command-line: value is missing for option: --opt"
    );
}

static void test_1_3()
{
    static char const* const args[] =
    {
        "program-path-1.3",

        "--opt=abc",

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
            int opt;

            try
            {
                clasp::require_option(args, "--opt", &opt);
                XTESTS_TEST_FAIL("should not get here");
            }
            catch(std::bad_alloc&)
            {
                throw;
            }
            catch(clasp::invalid_option_value_exception&)
            {
                XTESTS_TEST_PASSED();
                throw;
            }
            catch(std::exception&)
            {
                XTESTS_TEST_FAIL("should not get here");
                throw;
            }

            return EXIT_FAILURE;
        }
    };

    RUN_TEST(
        int(STLSOFT_NUM_ELEMENTS(args) - 1), args
    ,   &main_::fn
    ,   NULL, NULL
    ,   NULL
    ,   0
    ,   "program-path-1.3: invalid command-line: value is not an integer for option: --opt"
    );
}

static void test_1_4()
{
    static char const* const args[] =
    {
        "program-path-1.4",

        "--opt=-1",

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
            unsigned opt;

            clasp::require_option(args, "--opt", &opt);

            return EXIT_FAILURE;
        }
    };

    RUN_TEST(
        int(STLSOFT_NUM_ELEMENTS(args) - 1), args
    ,   &main_::fn
    ,   NULL, NULL
    ,   NULL
    ,   0
    ,   "program-path-1.4: invalid command-line: value may not be negative for option: --opt"
    );
}

static void test_1_5()
{
}

static void test_1_6()
{
    static char const* const args[] =
    {
        "program-path-1.6",

        "--opt-real-1=-1.1",
        "--opt-real-2=-2.2abc",

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
            double or1;
            double or2;

            try
            {
                clasp::require_option(args, "--opt-real-1", &or1);
                XTESTS_TEST_FLOATINGPOINT_EQUAL(-1.1, or1);
            }
            catch(std::bad_alloc&)
            {
                throw;
            }
            catch(std::exception&)
            {
                XTESTS_TEST_FAIL("should not get here");
            }

            try
            {
                clasp::require_option(args, "--opt-real-2", &or2);
                XTESTS_TEST_FAIL("should not get here");
            }
            catch(std::bad_alloc&)
            {
                throw;
            }
            catch(clasp::invalid_option_value_exception&)
            {
                XTESTS_TEST_PASSED();
                throw;
            }
            catch(std::exception&)
            {
                XTESTS_TEST_FAIL("should not get here");
                throw;
            }

            return EXIT_FAILURE;
        }
    };

    RUN_TEST(
        int(STLSOFT_NUM_ELEMENTS(args) - 1), args
    ,   &main_::fn
    ,   NULL, NULL
    ,   NULL
    ,   0
    ,   "program-path-1.6: invalid command-line: value is not a real number for option: --opt-real-2"
    );
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

