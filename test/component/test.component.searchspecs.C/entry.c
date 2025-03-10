/* /////////////////////////////////////////////////////////////////////////
 * File:    test.component.searchspecs.C/entry.c
 *
 * Purpose: Component test for search-specs
 *
 * Created: 12th September 2014
 * Updated: 10th March 2025
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <clasp/util/searchspecs.h>


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* CLASP header files */
#include <clasp/clasp.h>

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
 * forward declarations
 */

static void test_1_0(void);
static void test_1_1(void);

static int setup(void* param);
static int teardown(void* param);
static void* setupParam = NULL;


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

static
int main_(int argc, char **argv);

int main(int argc, char **argv)
{
    int r;

#ifdef _MSC_VER
    _CrtMemState    memState;

    _CrtMemCheckpoint(&memState);

    STLSOFT_SUPPRESS_UNUSED(memState);
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

    if (XTESTS_START_RUNNER_WITH_SETUP_FNS("test.component.searchspecs.C", verbosity, setup, teardown, setupParam))
    {
        XTESTS_RUN_CASE(test_1_0);
        XTESTS_RUN_CASE(test_1_1);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
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
    char const* /* const */*            strings
,   int                                 flags
,   clasp_char_t const*                 defaultDirectory
,   clasp_char_t const*                 defaultPatterns
,   clasp_util_searchspecs_t const**    searchspecs
)
{
    size_t numValues = 0;

    STLSOFT_C_AUTO_BUFFER_DECLARE(clasp_argument_t, 10, values);


    { char const** s; for (s = strings; NULL != *s; ++s)
    {
        ++numValues;
    }}

    if (0 != STLSOFT_C_AUTO_BUFFER_RESIZE(values, numValues))
    {
        return ENOMEM;
    }
    else
    {
        static const clasp_slice_t emptySlice = { 0 };

        int r;

        { size_t i; for (i = 0; i != numValues; ++i)
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


static void test_1_0(void)
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

    if (ENOMEM == r)
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

static void test_1_1(void)
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

    if (ENOMEM == r)
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


/* /////////////////////////////////////////////////////////////////////////
 * test component source file include(s)
 */

#include <../src/searchspecs/searchspecs.c>


/* ///////////////////////////// end of file //////////////////////////// */

