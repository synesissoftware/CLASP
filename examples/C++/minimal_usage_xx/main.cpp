/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/C++/minimal_usage_xx/main.cpp
 *
 * Purpose: Illustrates a minimal use of CLASP in a C++ program.
 *
 * Created: 9th March 2025
 * Updated: 9th March 2025
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */


#include <clasp/main.hpp>

#include <cstdio>
#include <cstdlib>
#include <iostream>


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

    CLASP_FLAG(NULL,    "--help",           "show this help and terminate"),
    CLASP_FLAG(NULL,    "--version",        "show version and terminate"),


    CLASP_SPECIFICATION_ARRAY_TERMINATOR
};


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

static
int main1(clasp_arguments_t const* args)
{
    if (clasp::flag_specified(args, "--help"))
    {
        clasp_showUsage(
            args
        ,   Specifications
        ,   NULL /* toolName inferred from process */
        ,   "CLASP (http://github.com/synesissoftware/CLASP)"
        ,   "Copyright Matthew Wilson and Synesis Information Systems"
        ,   "illustrates minimal usage functionality"
        ,   ":program: [... flags/options ...]"
        ,   PROGRAM_VER_ARGLIST
        ,   clasp_showHeaderByFILE, clasp_showBodyByFILE, stdout
        ,   0  /* flags */
        ,   76 /* console width */
        ,   -2 /* indent size */
        ,   1  /* blank line between args */
        );

        return EXIT_SUCCESS;
    }

    if (clasp::flag_specified(args, "--version"))
    {
        clasp_showVersion(
            args
        ,   NULL /* toolName inferred from process */
        ,   PROGRAM_VER_ARGLIST
        ,   clasp_showVersionByFILE, stdout
        ,   0 /* flags */
        );

        return EXIT_SUCCESS;
    }


    std::cout
        << "args={ numArguments="
        << args->numArguments
        << ", numFlagsAndOptions="
        << args->numFlagsAndOptions
        << ", numFlags="
        << args->numFlags
        << ", numOptions="
        << args->numOptions
        << ", numValues="
        << args->numValues
        << ", }"
        << std::endl;


    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    unsigned const cflags = 0;

    return clasp::main::invoke(argc, argv, main1, NULL, Specifications, cflags);
}


 /* ///////////////////////////// end of file //////////////////////////// */

