/* /////////////////////////////////////////////////////////////////////////
 * File:    test/scratch/versions/main.cpp
 *
 * Purpose: Scratch-test program for CLASP showing version(s).
 *
 * Created: 19th September 2026
 * Updated: 14th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <clasp/clasp.h>

#include <iomanip>
#include <iostream>

#include <stdlib.h>


/* /////////////////////////////////////////////////////////////////////////
 * helpers
 */

template<
    typename T_stream
,   typename T_integer
>
void
version(
    T_stream&   stm
,   char const* prefix
,   char const* libname
,   char const* macroname
,   T_integer   libver
)
{
    stm
        << prefix
        << libname
        << ": v"
        << ((libver >> 24) & 0xff)
        << '.'
        << ((libver >> 16) & 0xff)
        << '.'
        << ((libver >> 8) & 0xff)
        << '.'
        << ((libver >> 0) & 0xff)
        << " ("
        << macroname
        << " = 0x"
        << std::hex << std::setfill('0') << std::setw(8)
        << static_cast<unsigned>(libver)
        << std::dec
        << ")"
        << std::endl
        ;
}


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int /* argc */, char* /* argv */[])
{
    {
        unsigned const libver = CLASP_VER;

        version(std::cout, "", "CLASP", "CLASP_VER", libver);
    }

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

