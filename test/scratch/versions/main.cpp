/* /////////////////////////////////////////////////////////////////////////
 * File:    test/scratch/versions/main.cpp
 *
 * Purpose: Scratch-test program for CLASP showing version(s).
 *
 * Created: 19th September 2026
 * Updated: 23rd October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <clasp/clasp.h>

#ifdef STLSoft_FOUND
# include <stlsoft/stlsoft.h>
#endif /* STLSoft_FOUND */
#ifdef shwild_FOUND
# include <shwild/shwild.h>
#endif /* shwild_FOUND */
#include <woad/iostreams.hpp>

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
        << woad::blue(libname)
        << ": "
        << woad::green
        << "v"
        << ((libver >> 24) & 0xff)
        << '.'
        << ((libver >> 16) & 0xff)
        << '.'
        << ((libver >> 8) & 0xff)
        << '.'
        << ((libver >> 0) & 0xff)
        << woad::reset
        << " ("
        << woad::cyan(macroname)
        << " = "
        << woad::green
        << "0x"
        << std::hex << std::setfill('0') << std::setw(8)
        << static_cast<unsigned>(libver)
        << std::dec
        << woad::reset
        << ")"
        << std::endl
        ;
}


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int /* argc */, char* /* argv */[])
{
    int efferents_count = 0;

    {
        unsigned const libver = CLASP_VER;

        version(std::cout, "", "CLASP", "CLASP_VER", libver);
    }

#ifdef STLSoft_FOUND

    if (0 == efferents_count++)
    {
        std::cout << "\n" << "efferent dependencies:" << std::endl;
    }

    {
        unsigned const libver = _STLSOFT_VER;

        version(std::cout, "\t", "STLSoft", "_STLSOFT_VER", libver);
    }
#endif

#ifdef shwild_FOUND

    if (0 == efferents_count++)
    {
        std::cout << "\n" << "efferent dependencies:" << std::endl;
    }

    {
        unsigned const libver = SHWILD_VER;

        version(std::cout, "\t", "shwild", "SHWILD_VER", libver);
    }
#endif

#ifdef woad_FOUND

    if (0 == efferents_count++)
    {
        std::cout << "\n" << "efferent dependencies:" << std::endl;
    }

    {
        unsigned const libver = WOAD_VER;

        version(std::cout, "\t", "woad", "WOAD_VER", libver);
    }
#endif

    return EXIT_SUCCESS;
}


/* ///////////////////////////// end of file //////////////////////////// */

