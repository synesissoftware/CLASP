/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/C++/minimal_usage_xx/main.cpp
 *
 * Purpose: Illustrates a minimal use of CLASP in a C++ program.
 *
 * Created: 9th March 2025
 * Updated: 11th March 2025
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <clasp/main.hpp>

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
    CLASP_STOCK_FLAG_HELP,
    CLASP_STOCK_FLAG_VERSION,

    CLASP_SPECIFICATION_ARRAY_TERMINATOR
};


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char* argv[])
{
    return clasp::main::invoke(argc, argv, Specifications, [](clasp_arguments_t const* args) {

        if (clasp::flag_specified(args, "--help"))
        {
            return clasp::showUsage(
                args
            ,   NULL /* toolName inferred from process */
            ,   "CLASP (http://github.com/synesissoftware/CLASP)"
            ,   "Copyright Matthew Wilson and Synesis Information Systems"
            ,   "illustrates minimal usage functionality"
            ,   NULL /* toolName inferred from process/specifications */
            ,   PROGRAM_VER_ARGLIST
            );
        }

        if (clasp::flag_specified(args, "--version"))
        {
            return clasp::showVersion(args, PROGRAM_VER_ARGLIST);
        }


        std::cout << "args=" << args << std::endl;


        return EXIT_SUCCESS;
    });
}


 /* ///////////////////////////// end of file //////////////////////////// */

