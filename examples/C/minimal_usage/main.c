/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/C/minimal_usage/main.c
 *
 * Purpose: Illustrates a minimal use of CLASP in a C program.
 *
 * Created: 9th March 2025
 * Updated: 11th March 2025
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <clasp/main.h>

#include <stdio.h>
#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * constants
 */

#define PROGRAM_VER_MAJOR                                   0
#define PROGRAM_VER_MINOR                                   0
#define PROGRAM_VER_PATCH                                   0
#define PROGRAM_VER_ARGLIST                                 PROGRAM_VER_MAJOR, PROGRAM_VER_MINOR, PROGRAM_VER_PATCH


/* /////////////////////////////////////////////////////////////////////////
 * globals
 */

static clasp_specification_t const Specifications[] =
{
    /* Standard flags */

    CLASP_GAP_SECTION("standard flags:"),
    CLASP_STOCK_FLAG_HELP,
    CLASP_STOCK_FLAG_VERSION,

    CLASP_SPECIFICATION_ARRAY_TERMINATOR
};


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

static
int main1(clasp_arguments_t const* args)
{
    if (clasp_flagIsSpecified(args, "--help"))
    {
        return clasp_showUsage(
            args
        ,   Specifications
        ,   NULL /* toolName inferred from process */
        ,   "CLASP (http://github.com/synesissoftware/CLASP)"
        ,   "Copyright Matthew Wilson and Synesis Information Systems"
        ,   "illustrates minimal usage functionality"
        ,   NULL /* toolName inferred from process/specifications */
        ,   PROGRAM_VER_ARGLIST
        ,   clasp_showHeaderByFILE, clasp_showBodyByFILE, stdout
        ,   0  /* flags */
        ,   0  /* console width */
        ,   -2 /* indent size */
        ,   1  /* blank line between args */
        );
    }

    if (clasp_flagIsSpecified(args, "--version"))
    {
        return clasp_showVersion(
            args
        ,   NULL /* toolName inferred from process */
        ,   PROGRAM_VER_ARGLIST
        ,   clasp_showVersionByFILE, stdout
        ,   0 /* flags */
        );
    }


    printf("args={ .numArguments=%zu, .numFlagsAndOptions=%zu, .numFlags=%zu, .numOptions=%zu, .numValues=%zu, }\n"
    ,   args->numArguments
    ,   args->numFlagsAndOptions
    ,   args->numFlags
    ,   args->numOptions
    ,   args->numValues
    );


    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    unsigned const clasp_flags = 0;

    return clasp_main_invoke(argc, argv, main1, NULL, Specifications, clasp_flags, NULL);
}


/* ///////////////////////////// end of file //////////////////////////// */

