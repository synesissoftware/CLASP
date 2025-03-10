/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.parseapi.findflagoroption/entry.cpp
 *
 * Purpose: Unit-test(s) for `clasp_findFlagOrOption()`
 *
 * Created: 11th December 2011
 * Updated: 10th March 2025
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


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char **argv)
{
  int retCode = EXIT_SUCCESS;
  int verbosity = 2;

  XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

  if (XTESTS_START_RUNNER("test.unit.parseapi.findflagoroption", verbosity))
  {
    XTESTS_RUN_CASE(test_1_0);
    XTESTS_RUN_CASE(test_1_1);
    XTESTS_RUN_CASE(test_1_2);
    XTESTS_RUN_CASE(test_1_3);
    XTESTS_RUN_CASE(test_1_4);
    XTESTS_RUN_CASE(test_1_5);

    XTESTS_PRINT_RESULTS();

    XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
  }

  return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void test_1_0(void)
{
  char const* const         argv[] =
  {
    "program",

    NULL
  };
  int const                 argc = STLSOFT_NUM_ELEMENTS(argv) - 1;
  clasp_arguments_t const*  args;
  int const                 cr   = clasp_parseArguments(0, argc, (char**)argv, NULL, NULL, &args);

  if (0 != cr)
  {
    XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
  }
  else
  {
    clasp_argument_t const* arg = clasp_findFlagOrOption(args, "--verbosity", 0);

    XTESTS_TEST_POINTER_EQUAL(NULL, arg);

    clasp_releaseArguments(args);
  }
}

static void test_1_1(void)
{
  char const* const         argv[] =
  {
    "program",

    "--verbosity",

    NULL
  };
  int const                 argc = STLSOFT_NUM_ELEMENTS(argv) - 1;
  clasp_arguments_t const*  args;
  int const                 cr   = clasp_parseArguments(0, argc, (char**)argv, NULL, NULL, &args);

  if (0 != cr)
  {
    XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
  }
  else
  {
    clasp_argument_t const* arg = clasp_findFlagOrOption(args, "--verbosity", 0);

    XTESTS_TEST_POINTER_NOT_EQUAL(NULL, arg);
    XTESTS_TEST_ENUM_EQUAL(CLASP_ARGTYPE_FLAG, arg->type);
    XTESTS_TEST_INTEGER_EQUAL(-1, arg->aliasIndex);
    XTESTS_TEST_INTEGER_EQUAL(1, arg->cmdLineIndex);
    XTESTS_TEST_INTEGER_EQUAL(2, arg->numGivenHyphens);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--verbosity", arg->givenName.ptr);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--verbosity", arg->resolvedName.ptr);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", arg->value.ptr);

    clasp_releaseArguments(args);
  }
}

static void test_1_2(void)
{
  char const* const         argv[] =
  {
    "program",

    "--verbosity",
    "--verbosity",
    "--verbosity",

    NULL
  };
  int const                 argc = STLSOFT_NUM_ELEMENTS(argv) - 1;
  clasp_arguments_t const*  args;
  int const                 cr   = clasp_parseArguments(0, argc, (char**)argv, NULL, NULL, &args);

  if (0 != cr)
  {
    XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
  }
  else
  {
    clasp_argument_t const* arg = clasp_findFlagOrOption(args, "--verbosity", 3);

    XTESTS_TEST_POINTER_EQUAL(NULL, arg);

    clasp_releaseArguments(args);
  }
}

static void test_1_3(void)
{
  char const* const         argv[] =
  {
    "program",

    "--verbosity",
    "--verbosity",
    "--verbosity",

    NULL
  };
  int const                 argc = STLSOFT_NUM_ELEMENTS(argv) - 1;
  clasp_arguments_t const*  args;
  int const                 cr   = clasp_parseArguments(0, argc, (char**)argv, NULL, NULL, &args);

  if (0 != cr)
  {
    XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
  }
  else
  {
    clasp_argument_t const* arg = clasp_findFlagOrOption(args, "--verbosity", 2);

    XTESTS_TEST_POINTER_NOT_EQUAL(NULL, arg);
    XTESTS_TEST_ENUM_EQUAL(CLASP_ARGTYPE_FLAG, arg->type);
    XTESTS_TEST_INTEGER_EQUAL(-1, arg->aliasIndex);
    XTESTS_TEST_INTEGER_EQUAL(3, arg->cmdLineIndex);
    XTESTS_TEST_INTEGER_EQUAL(2, arg->numGivenHyphens);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--verbosity", arg->givenName.ptr);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--verbosity", arg->resolvedName.ptr);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", arg->value.ptr);

    clasp_releaseArguments(args);
  }
}

static void test_1_4(void)
{
  char const* const         argv[] =
  {
    "program",

    "--verbosity=abc",

    NULL
  };
  int const                 argc = STLSOFT_NUM_ELEMENTS(argv) - 1;
  clasp_arguments_t const*  args;
  int const                 cr   = clasp_parseArguments(0, argc, (char**)argv, NULL, NULL, &args);

  if (0 != cr)
  {
    XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
  }
  else
  {
    clasp_argument_t const* arg = clasp_findFlagOrOption(args, "--verbosity", 0);

    XTESTS_TEST_POINTER_NOT_EQUAL(NULL, arg);
    XTESTS_TEST_ENUM_EQUAL(CLASP_ARGTYPE_OPTION, arg->type);
    XTESTS_TEST_INTEGER_EQUAL(-1, arg->aliasIndex);
    XTESTS_TEST_INTEGER_EQUAL(1, arg->cmdLineIndex);
    XTESTS_TEST_INTEGER_EQUAL(2, arg->numGivenHyphens);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--verbosity", arg->givenName.ptr);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--verbosity", arg->resolvedName.ptr);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("abc", arg->value.ptr);

    clasp_releaseArguments(args);
  }
}

static void test_1_5(void)
{
  char const* const         argv[] =
  {
    "program",

    "--verbosity=abc",
    "--blank",
    "--verbosity=def",
    "--blank",
    "--verbosity=ghi",

    NULL
  };
  int const                 argc = STLSOFT_NUM_ELEMENTS(argv) - 1;
  clasp_arguments_t const*  args;
  int const                 cr   = clasp_parseArguments(0, argc, (char**)argv, NULL, NULL, &args);

  if (0 != cr)
  {
    XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
  }
  else
  {
    clasp_argument_t const* arg = clasp_findFlagOrOption(args, "--verbosity", 1);

    XTESTS_TEST_POINTER_NOT_EQUAL(NULL, arg);
    XTESTS_TEST_ENUM_EQUAL(CLASP_ARGTYPE_OPTION, arg->type);
    XTESTS_TEST_INTEGER_EQUAL(-1, arg->aliasIndex);
    XTESTS_TEST_INTEGER_EQUAL(3, arg->cmdLineIndex);
    XTESTS_TEST_INTEGER_EQUAL(2, arg->numGivenHyphens);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--verbosity", arg->givenName.ptr);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--verbosity", arg->resolvedName.ptr);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("def", arg->value.ptr);

    clasp_releaseArguments(args);
  }
}


/* ///////////////////////////// end of file //////////////////////////// */

