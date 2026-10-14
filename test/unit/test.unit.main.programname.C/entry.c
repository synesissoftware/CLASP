/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.main.programname.C/entry.c
 *
 * Purpose: Unit-test program name in failure conditions for the C API.
 *
 * Created: 8th October 2026
 * Updated: 15th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */

/* CLASP header files */
#include <clasp/clasp.h>
#include <clasp/main.h>

/* woad header files */
#include <woad/woad.h>

/* xTests header files */
#include <xtests/terse-api.h>

/* STLSoft header files */
#include <stlsoft/api/internal/stdio.h>

/* Standard C header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * application callbacks
 */

static clasp_specification_t const Specifications[] =
{
    CLASP_OPTION("-o",  "--output-file",    "specify the output-file", ":one:two"),
    CLASP_SPECIFICATION_ARRAY_TERMINATOR,
};


/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void test_coloured_program_name_passes_through(void);

static int invoked_main(clasp_arguments_t const* args);

static void* failing_malloc(void* context, size_t cb);
static void* failing_realloc(void* context, void* pv, size_t cb);
static void noop_free(void* context, void* pv);

static int setup_teardown(void* pv);

static char const* tmpfile_path;


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER_WITH_SETUP_FNS("test.unit.main.programname.C", verbosity, setup_teardown, setup_teardown, &tmpfile_path))
    {
        XTESTS_RUN_CASE(test_coloured_program_name_passes_through);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}


/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static void
test_coloured_program_name_passes_through(void)
{
    tmpfile_path = "test.unit.main.programname.C-stderr.txt";

    FILE* const redirected_stderr = freopen(tmpfile_path, "w", stderr);

    if (NULL == redirected_stderr)
    {
        TEST_FAIL("could not create stderr mock file");

        return;
    }
    else
    {
        char const                  programName[] =
            WOAD_FG_RED
            "program-name-c"
            WOAD_RESET;

        char                        arg0[] = "test.unit.main.programname.C";
        char                        arg1[] = "--output-file=bogus";
        char*                       argv[] =
        {
            arg0,
            arg1,
            NULL,
        };
        clasp_diagnostic_context_t  ctxt;
        FILE*                       stm_contents = NULL;

        clasp_init_diagnostic_context(&ctxt, NULL, failing_malloc, failing_realloc, noop_free, NULL, NULL, NULL);

        {
            int const r = clasp_main_invoke(
                (int)(sizeof(argv) / sizeof(argv[0]) - 1u),
                argv,
                invoked_main,
                programName,
                Specifications,
                0,
                &ctxt);

            TEST_INT_NE(EXIT_SUCCESS, r);
        }

        fflush(stderr);
        fclose(redirected_stderr);

        if (0 != STLSOFT_API_INTERNAL_stdio_fopen_m(tmpfile_path, "r", &stm_contents))
        {
            TEST_FAIL("could not reopen stderr mock file");

            return;
        }
        else
        {
            char    ignored[1024];
            char    line[1024];
            size_t  prefixLen;

            if (NULL == fgets(ignored, (int)sizeof(ignored), stm_contents))
            {
                fclose(stm_contents);

                TEST_FAIL("could not read allocator diagnostic");

                return;
            }

            if (NULL == fgets(line, (int)sizeof(line), stm_contents))
            {
                fclose(stm_contents);

                TEST_FAIL("could not read contingent report");

                return;
            }

            fclose(stm_contents);

            prefixLen = strlen(programName);

            TEST_INT_EQ(0, strncmp(line, programName, prefixLen));
        }
    }
}

static int setup_teardown(void* pv)
{
    if (NULL != pv)
    {
        char const* path = *(char const**)pv;

        remove(path);

        path = NULL;
    }

    return 0;
}


static int
invoked_main(
    clasp_arguments_t const* args
)
{
    ((void)args);

    return EXIT_SUCCESS;
}

static void*
failing_malloc(
    void*   context,
    size_t  cb
)
{
    ((void)context);
    ((void)cb);

    return NULL;
}

static void*
failing_realloc(
    void*   context,
    void*   pv,
    size_t  cb
)
{
    ((void)context);
    ((void)pv);
    ((void)cb);

    return NULL;
}

static void
noop_free(
    void*   context,
    void*   pv
)
{
    ((void)context);
    ((void)pv);
}


/* ///////////////////////////// end of file //////////////////////////// */

