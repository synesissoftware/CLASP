/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.version/entry.c
 *
 * Purpose: Unit-test(s) for CLASP version macros.
 *
 * Created: 2nd September 2026
 * Updated: 2nd September 2026
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

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void test_CLASP_VER_components(void);
static void test_CLASP_VER_composite(void);


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.version", verbosity))
    {
        XTESTS_RUN_CASE(test_CLASP_VER_components);
        XTESTS_RUN_CASE(test_CLASP_VER_composite);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void test_CLASP_VER_components(void)
{
    XTESTS_TEST_INTEGER_EQUAL(0, CLASP_VER_MAJOR);
    XTESTS_TEST_INTEGER_EQUAL(15, CLASP_VER_MINOR);
    XTESTS_TEST_INTEGER_EQUAL(1, CLASP_VER_PATCH);
    XTESTS_TEST_INTEGER_EQUAL(0xFF, CLASP_VER_AB);

    XTESTS_TEST_INTEGER_EQUAL(CLASP_VER_PATCH, CLASP_VER_REVISION);
}

static void test_CLASP_VER_composite(void)
{
    /* Evaluating CLASP_VER as an expression catches composite-macro defects
     * (e.g. referencing a retired CLASP_VER_ALPHABETA symbol).
     */
    unsigned const ver = (unsigned)CLASP_VER;

    XTESTS_TEST_INTEGER_EQUAL(CLASP_VER_MAJOR, (ver >> 24) & 0xff);
    XTESTS_TEST_INTEGER_EQUAL(CLASP_VER_MINOR, (ver >> 16) & 0xff);
    XTESTS_TEST_INTEGER_EQUAL(CLASP_VER_PATCH, (ver >>  8) & 0xff);
    XTESTS_TEST_INTEGER_EQUAL(CLASP_VER_AB,    (ver >>  0) & 0xff);

    XTESTS_TEST_INTEGER_EQUAL(
        (unsigned)(0
            | (CLASP_VER_MAJOR << 24)
            | (CLASP_VER_MINOR << 16)
            | (CLASP_VER_PATCH <<  8)
            | (CLASP_VER_AB    <<  0)
        )
    ,   ver
    );
}


/* ///////////////////////////// end of file //////////////////////////// */
