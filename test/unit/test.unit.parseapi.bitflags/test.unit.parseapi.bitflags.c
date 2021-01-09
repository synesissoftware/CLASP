/* /////////////////////////////////////////////////////////////////////////
 * File:        test.unit.parseapi.bitflags.cpp
 *
 * Purpose:     Implementation file for the test.unit.parseapi.bitflags project.
 *
 * Created:     11th December 2011
 * Updated:     10th January 2021
 *
 * Status:      Wizard-generated
 *
 * License:     BSD (3-clause)
 *
 *              Copyright (c) 2019-2021, Synesis Information Systems Pty Ltd.
 *              Copyright (c) 2011-2019, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://github.com/synesissoftware/CLASP
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <clasp/clasp.h>

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>

/* Standard C header files */
#include <stdlib.h>
#include <string.h>

/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 */

#if defined(_MSC_VER) && \
    _MSC_VER >= 1400
# pragma warning(push)
# pragma warning(disable : 4996)
#endif

/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

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

/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char **argv)
{
  int retCode = EXIT_SUCCESS;
  int verbosity = 2;

  XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

  if (XTESTS_START_RUNNER("test.unit.parseapi.bitflags", verbosity))
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
 * test function implementations
 */

static void test_1_0()
{
    clasp_specification_t Specifications[] =
    {

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };
    char*     argv[] =
    {
        "arg0",

        NULL
    };
    int const                 argc = STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*  args;
    int const                 cr   = clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if (0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        int const flagsAll  =   clasp_checkAllFlags(args, Specifications, NULL);
        int const flagsAny  =   clasp_checkAllMatchingFlags(args, Specifications, ~(int)0, NULL);
        int const flags0001 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0001, NULL);
        int const flags0002 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0002, NULL);
        int const flags0003 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0003, NULL);
        int const flags0004 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0004, NULL);
        int const flags0005 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0005, NULL);
        int const flags0006 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0006, NULL);
        int const flags0007 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0007, NULL);
        int const flags0008 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0008, NULL);

        XTESTS_TEST_INTEGER_EQUAL(0x0000, flagsAll);
        XTESTS_TEST_INTEGER_EQUAL(0x0000, flagsAny);
        XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0001);
        XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0002);
        XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0003);
        XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0004);
        XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0005);
        XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0006);
        XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0007);
        XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0008);

        clasp_releaseArguments(args);
    }
}

static void test_1_1()
{
    clasp_specification_t Specifications[] =
    {
        CLASP_BIT_FLAG(NULL, "-f", 0x0001, ""),
        CLASP_BIT_FLAG(NULL, "-g", 0x0002, ""),
        CLASP_BIT_FLAG(NULL, "-h", 0x0004, ""),
        CLASP_BIT_FLAG(NULL, "-i", 0x0006, ""),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };
    char*     argv[] =
    {
        "arg0",

        NULL
    };
    int const                 argc = STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*  args;
    int const                 cr   = clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if (0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        int const flagsAll  =   clasp_checkAllFlags(args, Specifications, NULL);
        int const flagsAny  =   clasp_checkAllMatchingFlags(args, Specifications, ~(int)0, NULL);
        int const flags0001 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0001, NULL);
        int const flags0002 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0002, NULL);
        int const flags0003 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0003, NULL);
        int const flags0004 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0004, NULL);
        int const flags0005 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0005, NULL);
        int const flags0006 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0006, NULL);
        int const flags0007 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0007, NULL);
        int const flags0008 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0008, NULL);

        XTESTS_TEST_INTEGER_EQUAL(0x0000, flagsAll);
        XTESTS_TEST_INTEGER_EQUAL(0x0000, flagsAny);
        XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0001);
        XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0002);
        XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0003);
        XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0004);
        XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0005);
        XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0006);
        XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0007);
        XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0008);

        clasp_releaseArguments(args);
    }
}

static void test_1_2()
{
    clasp_specification_t Specifications[] =
    {
        CLASP_BIT_FLAG(NULL, "-f", 0x0001, ""),
        CLASP_BIT_FLAG(NULL, "-g", 0x0002, ""),
        CLASP_BIT_FLAG(NULL, "-h", 0x0004, ""),
        CLASP_BIT_FLAG(NULL, "-i", 0x0006, ""),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };
    char*       argv[] =
    {
        "arg0",

        "-f",

        NULL
    };
    int const   argc = STLSOFT_NUM_ELEMENTS(argv) - 1;

    {
        clasp_arguments_t const*  args;
        int const                 cr   = clasp_parseArguments(0, argc, argv, Specifications, NULL, &args);

        if (0 != cr)
        {
            XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
        }
        else
        {
            int const flagsAll  =   clasp_checkAllFlags(args, Specifications, NULL);

            XTESTS_TEST_INTEGER_EQUAL(0x0001, flagsAll);

            clasp_releaseArguments(args);
        }
    }

    {
        clasp_arguments_t const*  args;
        int const                 cr   = clasp_parseArguments(0, argc, argv, Specifications, NULL, &args);

        if (0 != cr)
        {
            XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
        }
        else
        {
            int const flagsAny  =   clasp_checkAllMatchingFlags(args, Specifications, ~(int)0, NULL);

            XTESTS_TEST_INTEGER_EQUAL(0x0001, flagsAny);

            clasp_releaseArguments(args);
        }
    }

    {
        clasp_arguments_t const*  args;
        int const                 cr   = clasp_parseArguments(0, argc, argv, Specifications, NULL, &args);

        if (0 != cr)
        {
            XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
        }
        else
        {
            int const flags0001 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0001, NULL);

            XTESTS_TEST_INTEGER_EQUAL(0x0001, flags0001);

            clasp_releaseArguments(args);
        }
    }

    {
        clasp_arguments_t const*  args;
        int const                 cr   = clasp_parseArguments(0, argc, argv, Specifications, NULL, &args);

        if (0 != cr)
        {
            XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
        }
        else
        {
            int const flags0002 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0002, NULL);

            XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0002);

            clasp_releaseArguments(args);
        }
    }

    {
        clasp_arguments_t const*  args;
        int const                 cr   = clasp_parseArguments(0, argc, argv, Specifications, NULL, &args);

        if (0 != cr)
        {
            XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
        }
        else
        {
            int const flags0003 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0003, NULL);

            XTESTS_TEST_INTEGER_EQUAL(0x0001, flags0003);

            clasp_releaseArguments(args);
        }
    }

    {
        clasp_arguments_t const*  args;
        int const                 cr   = clasp_parseArguments(0, argc, argv, Specifications, NULL, &args);

        if (0 != cr)
        {
            XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
        }
        else
        {
            int const flags0004 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0004, NULL);

            XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0004);

            clasp_releaseArguments(args);
        }
    }

    {
        clasp_arguments_t const*  args;
        int const                 cr   = clasp_parseArguments(0, argc, argv, Specifications, NULL, &args);

        if (0 != cr)
        {
            XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
        }
        else
        {
            int const flags0005 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0005, NULL);

            XTESTS_TEST_INTEGER_EQUAL(0x0001, flags0005);

            clasp_releaseArguments(args);
        }
    }

    {
        clasp_arguments_t const*  args;
        int const                 cr   = clasp_parseArguments(0, argc, argv, Specifications, NULL, &args);

        if (0 != cr)
        {
            XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
        }
        else
        {
            int const flags0006 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0006, NULL);

            XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0006);

            clasp_releaseArguments(args);
        }
    }

    {
        clasp_arguments_t const*  args;
        int const                 cr   = clasp_parseArguments(0, argc, argv, Specifications, NULL, &args);

        if (0 != cr)
        {
            XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
        }
        else
        {
            int const flags0007 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0007, NULL);

            XTESTS_TEST_INTEGER_EQUAL(0x0001, flags0007);

            clasp_releaseArguments(args);
        }
    }

    {
        clasp_arguments_t const*  args;
        int const                 cr   = clasp_parseArguments(0, argc, argv, Specifications, NULL, &args);

        if (0 != cr)
        {
            XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
        }
        else
        {
            int const flags0008 =   clasp_checkAllMatchingFlags(args, Specifications, 0x0008, NULL);

            XTESTS_TEST_INTEGER_EQUAL(0x0000, flags0008);

            clasp_releaseArguments(args);
        }
    }
}

static void test_1_3()
{
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

/* ///////////////////////////// end of file //////////////////////////// */

