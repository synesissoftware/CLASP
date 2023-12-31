/* /////////////////////////////////////////////////////////////////////////
 * File:        test.unit.custom_types.cpp
 *
 * Purpose:     Implementation file for the test.unit.custom_types project.
 *
 * Created:     12th September 2014
 * Updated:     31st December 2023
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <systemtools/clasp/clasp.hpp>

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

static void test_parse_Colour();
static void test_1_1();
static void test_1_2();
static void test_1_3();
static void test_1_4();
static void test_1_5();
static void test_1_6();
static void test_1_7();
static void test_1_8();
static void test_1_9();
static void test_1_10();
static void test_1_11();
static void test_1_12();
static void test_1_13();
static void test_1_14();
static void test_1_15();
static void test_1_16();
static void test_1_17();
static void test_1_18();
static void test_1_19();

/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char **argv)
{
  int retCode = EXIT_SUCCESS;
  int verbosity = 2;

  XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

  if(XTESTS_START_RUNNER("test.unit.custom_types", verbosity))
  {
    XTESTS_RUN_CASE(test_parse_Colour);
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
 * custom types
 */

enum Colour
{
        Black
    ,   Blue
    ,   Green
    ,   Red
    ,   Yellow
};

bool
parse_Colour(
    void*        /* param */
,   char const*     parsedValue
,   Colour*         result
)
{
#define PARSE_ENTRY_(s, v)                                  else if(0 == ::strcmp(s, parsedValue)) { *result = v; return true; }

    if(0) {}
    PARSE_ENTRY_("black", Black)
    PARSE_ENTRY_("blue", Blue)
    PARSE_ENTRY_("green", Green)
    PARSE_ENTRY_("red", Red)
    PARSE_ENTRY_("yellow", Yellow)

    return false;
}

/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

using ::clasp::arguments_t;

static void test_parse_Colour()
{
    int const           flags   =   0;
    char* const         argv[]  =
    {
            "programName"

        ,   NULL
    };
    int const           argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    arguments_t const*  args;
    int const           cr = clasp::parseArguments(flags, argc, argv, NULL, NULL, &args);

    XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(0, cr));

    Colour              clr;

    XTESTS_TEST_BOOLEAN_FALSE(clasp::check_option(args, "--colour", &clr, &parse_Colour, NULL, ""));
}

static void test_1_1()
{
    int const           flags   =   0;
    char* const         argv[]  =
    {
            "programName"

        ,   "--colour=yellow"

        ,   NULL
    };
    int const           argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    arguments_t const*  args;
    int const           cr = clasp::parseArguments(flags, argc, argv, NULL, NULL, &args);

    XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(0, cr));

    Colour              clr = Colour(0);

    XTESTS_TEST_BOOLEAN_TRUE(clasp::check_option(args, "--colour", &clr, &parse_Colour, NULL, ""));
    XTESTS_TEST_ENUM_EQUAL(Yellow, clr);
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

/* ///////////////////////////// end of file //////////////////////////// */

