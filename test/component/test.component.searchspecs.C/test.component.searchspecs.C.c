/* /////////////////////////////////////////////////////////////////////////
 * File:        test.component.searchspecs.C.c
 *
 * Purpose:     Implementation file for the test.component.searchspecs.C project.
 *
 * Created:     12th September 2014
 * Updated:     18th April 2019
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2014-2019, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * Test component header file include(s)
 */

#include <systemtools/clasp/util/searchspecs.h>

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* SystemTools::CLASP header files */
#include <systemtools/clasp/clasp.h>

/* xTests header files */
#include <xtests/xtests.h>

/* STLSoft header files */
#include <stlsoft/stlsoft.h>
#include <stlsoft/memory/auto_buffer.h>

/* Standard C header files */
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
# include <crtdbg.h>
#endif /* _MSC_VER */

/* /////////////////////////////////////////////////////////////////////////
 * Forward declarations
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
static void test_1_20(void);
static void test_1_21(void);
static void test_1_22(void);
static void test_1_23(void);
static void test_1_24(void);
static void test_1_25(void);
static void test_1_26(void);
static void test_1_27(void);
static void test_1_28(void);
static void test_1_29(void);
static void test_1_30(void);
static void test_1_31(void);
static void test_1_32(void);
static void test_1_33(void);
static void test_1_34(void);
static void test_1_35(void);
static void test_1_36(void);
static void test_1_37(void);
static void test_1_38(void);
static void test_1_39(void);
static void test_1_40(void);
static void test_1_41(void);
static void test_1_42(void);
static void test_1_43(void);
static void test_1_44(void);
static void test_1_45(void);
static void test_1_46(void);
static void test_1_47(void);
static void test_1_48(void);
static void test_1_49(void);

static int setup(void* param);
static int teardown(void* param);
static void* setupParam = NULL;

/* /////////////////////////////////////////////////////////////////////////
 * Main
 */

static
int main_(int argc, char **argv);

int main(int argc, char **argv)
{
    int r;

#ifdef _MSC_VER
    _CrtMemState    memState;

    _CrtMemCheckpoint(&memState);
#endif /* _MSC_VER */

    r = main_(argc, argv);

#ifdef _MSC_VER
    _CrtMemDumpAllObjectsSince(&memState);
#endif /* _MSC_VER */

    return r;
}

int main_(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if(XTESTS_START_RUNNER_WITH_SETUP_FNS("test.component.searchspecs.C", verbosity, setup, teardown, setupParam))
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
        XTESTS_RUN_CASE(test_1_20);
        XTESTS_RUN_CASE(test_1_21);
        XTESTS_RUN_CASE(test_1_22);
        XTESTS_RUN_CASE(test_1_23);
        XTESTS_RUN_CASE(test_1_24);
        XTESTS_RUN_CASE(test_1_25);
        XTESTS_RUN_CASE(test_1_26);
        XTESTS_RUN_CASE(test_1_27);
        XTESTS_RUN_CASE(test_1_28);
        XTESTS_RUN_CASE(test_1_29);
        XTESTS_RUN_CASE(test_1_30);
        XTESTS_RUN_CASE(test_1_31);
        XTESTS_RUN_CASE(test_1_32);
        XTESTS_RUN_CASE(test_1_33);
        XTESTS_RUN_CASE(test_1_34);
        XTESTS_RUN_CASE(test_1_35);
        XTESTS_RUN_CASE(test_1_36);
        XTESTS_RUN_CASE(test_1_37);
        XTESTS_RUN_CASE(test_1_38);
        XTESTS_RUN_CASE(test_1_39);
        XTESTS_RUN_CASE(test_1_40);
        XTESTS_RUN_CASE(test_1_41);
        XTESTS_RUN_CASE(test_1_42);
        XTESTS_RUN_CASE(test_1_43);
        XTESTS_RUN_CASE(test_1_44);
        XTESTS_RUN_CASE(test_1_45);
        XTESTS_RUN_CASE(test_1_46);
        XTESTS_RUN_CASE(test_1_47);
        XTESTS_RUN_CASE(test_1_48);
        XTESTS_RUN_CASE(test_1_49);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

/* /////////////////////////////////////////////////////////////////////////
 * Test function implementations
 */

static int setup(void* param)
{
    ((void)param); /* TODO: Use the parameter, if you need to */

    return 0; /* Change to !0 to fail initialisation */
}

static int teardown(void* param)
{
    ((void)param); /* TODO: Use the parameter, if you need to */

    return 0; /* Currently ignored by xTests */
}

static
int
load_helper_(
    char const* /* const */*                    strings
,   int                                 flags
,   clasp_char_t const*                 defaultDirectory
,   clasp_char_t const*                 defaultPatterns
,   clasp_util_searchspecs_t const**    searchspecs
)
{
    size_t numValues = 0;

    STLSOFT_C_AUTO_BUFFER_DECLARE(clasp_argument_t, 10, values);


    { char const** s; for(s = strings; NULL != *s; ++s)
    {
        ++numValues;
    }}

    if(0 != STLSOFT_C_AUTO_BUFFER_ALLOCATE(values, numValues))
    {
        return ENOMEM;
    }
    else
    {
        static const clasp_slice_t emptySlice;

        int r;

        { size_t i; for(i = 0; i != numValues; ++i)
        {
            clasp_argument_t* const value   =   &values.ptr[i];
            char const* const       string  =   strings[i];
            size_t const            len     =   strlen(string);

            value->resolvedName     =   emptySlice;
            value->givenName        =   emptySlice;
            value->value.len        =   len;
            value->value.ptr        =   string;
            value->cmdLineIndex     =   1 + (int)i;
            value->numGivenHyphens  =   0;
            value->aliasIndex       =   -1;
            value->flags            =   0;
        }}

        r = clasp_util_searchSpecs_load(flags, numValues, values.ptr, defaultDirectory, defaultPatterns, searchspecs);

        STLSOFT_C_AUTO_BUFFER_FREE(values);

        return r;
    }
}


static void test_1_0()
{
    clasp_util_searchspecs_t const* searchspecs;

    int r = clasp_util_searchSpecs_load(
                0
            ,   0
            ,   NULL
            ,   NULL
            ,   NULL
            ,   &searchspecs
            );

    if(ENOMEM == r)
    {
        XTESTS_TEST_FAIL("out of memory");
    }
    else
    {
        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(0, r));
        XTESTS_TEST_INTEGER_EQUAL( 0, searchspecs->flags);
        XTESTS_TEST_INTEGER_EQUAL(0u, searchspecs->numSpecs);
    }
}

static void test_1_1()
{
    static char const* values[] =
    {
        ".",

        NULL
    };

    clasp_util_searchspecs_t const* searchspecs;

    int r = load_helper_(
                values
            ,   0
            ,   NULL
            ,   NULL
            ,   &searchspecs
            );

    if(ENOMEM == r)
    {
        XTESTS_TEST_FAIL("out of memory");
    }
    else
    {
        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(0, r));
        XTESTS_TEST_INTEGER_EQUAL( 0, searchspecs->flags);
        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(1u, searchspecs->numSpecs));

        XTESTS_TEST_INTEGER_EQUAL(1u, searchspecs->specs[0].directory.len);
    }
}

static void test_1_2()
{
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

static void test_1_20()
{
}

static void test_1_21()
{
}

static void test_1_22()
{
}

static void test_1_23()
{
}

static void test_1_24()
{
}

static void test_1_25()
{
}

static void test_1_26()
{
}

static void test_1_27()
{
}

static void test_1_28()
{
}

static void test_1_29()
{
}

static void test_1_30()
{
}

static void test_1_31()
{
}

static void test_1_32()
{
}

static void test_1_33()
{
}

static void test_1_34()
{
}

static void test_1_35()
{
}

static void test_1_36()
{
}

static void test_1_37()
{
}

static void test_1_38()
{
}

static void test_1_39()
{
}

static void test_1_40()
{
}

static void test_1_41()
{
}

static void test_1_42()
{
}

static void test_1_43()
{
}

static void test_1_44()
{
}

static void test_1_45()
{
}

static void test_1_46()
{
}

static void test_1_47()
{
}

static void test_1_48()
{
}

static void test_1_49()
{
}

/* /////////////////////////////////////////////////////////////////////////
 * Test component source file include(s)
 */

#include <../src/searchspecs/searchspecs.c>

/* ///////////////////////////// end of file //////////////////////////// */

