/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.version/entry.c
 *
 * Purpose: Unit-test(s) for CLASP version macros.
 *
 * Created: 2nd September 2026
 * Updated: 20th September 2026
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
#include <xtests/terse-api.h>

/* Standard C header files */
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void test_CLASP_VER_components(void);
static void test_CLASP_VER_composite(void);


/* /////////////////////////////////////////////////////////////////////////
 * main()
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
    TEST_INT_EQ(0, CLASP_VER_MAJOR);
    TEST_INT_EQ(15, CLASP_VER_MINOR);
    TEST_INT_EQ(4, CLASP_VER_PATCH);
    TEST_INT_EQ(0xFF, CLASP_VER_ALPHABETA);
    TEST_INT_EQ(0xFF, CLASP_VER_AB);

    TEST_INT_EQ(CLASP_VER_PATCH, CLASP_VER_REVISION);
    TEST_INT_EQ(CLASP_VER_ALPHABETA, CLASP_VER_AB);
}

static void test_CLASP_VER_composite(void)
{
    /* Evaluating CLASP_VER as an expression catches composite-macro defects
     * (e.g. referencing an undefined discriminator symbol).
     */
    unsigned const ver = (unsigned)CLASP_VER;

    TEST_INT_EQ(CLASP_VER_MAJOR, (ver >> 24) & 0xff);
    TEST_INT_EQ(CLASP_VER_MINOR, (ver >> 16) & 0xff);
    TEST_INT_EQ(CLASP_VER_PATCH, (ver >>  8) & 0xff);
    TEST_INT_EQ(CLASP_VER_ALPHABETA, (ver >>  0) & 0xff);
    TEST_INT_EQ(CLASP_VER_AB,        (ver >>  0) & 0xff);

    TEST_INT_EQ(
        (unsigned)(0
            | (CLASP_VER_MAJOR     << 24)
            | (CLASP_VER_MINOR     << 16)
            | (CLASP_VER_PATCH     <<  8)
            | (CLASP_VER_ALPHABETA <<  0)
        )
    ,   ver
    );
}


/* ///////////////////////////// end of file //////////////////////////// */
