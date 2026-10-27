/* /////////////////////////////////////////////////////////////////////////
 * File:    test/scratch/versions/main.cpp
 *
 * Purpose: Scratch-test program for CLASP showing version(s).
 *
 * Created: 19th September 2026
 * Updated: 27th October 2026
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include <clasp/clasp.h>

#ifdef HAS_STLSoft
# include <stlsoft/stlsoft.h>
#endif

#include <woad/woad.h>

#ifdef HAS_xTests
# include <xtests/xtests.h>
#endif

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
,   char const* version_string = nullptr
)
{
    stm
        << prefix
        << WOAD_FG_BLUE
        << libname
        << WOAD_RESET
        << ": "
        << WOAD_FG_GREEN
        << "v"
        ;

    if (nullptr != version_string)
    {
        stm << version_string;
    }
    else
    {
        stm
            << ((libver >> 24) & 0xff)
            << '.'
            << ((libver >> 16) & 0xff)
            << '.'
            << ((libver >> 8) & 0xff)
            << '.'
            << ((libver >> 0) & 0xff)
            ;
    }

    stm
        << WOAD_RESET
        << " ("
        << WOAD_FG_CYAN
        << macroname
        << WOAD_RESET
        << " = "
        << WOAD_FG_GREEN
        << "0x"
        << std::hex << std::setfill('0') << std::setw(8)
        << static_cast<unsigned>(libver)
        << std::dec
        << WOAD_RESET
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

#ifdef HAS_STLSoft

    if (0 == efferents_count++)
    {
        std::cout << "\n" << "efferent dependencies:" << std::endl;
    }

    {
        unsigned const libver = _STLSOFT_VER;

        version(std::cout, "\t", "STLSoft", "_STLSOFT_VER", libver);
    }
#endif

    if (0 == efferents_count++)
    {
        std::cout << "\n" << "efferent dependencies:" << std::endl;
    }

    {
        unsigned const libver = WOAD_VER;

        version(std::cout, "\t", "woad", "WOAD_VER", libver, woad::version_string());
    }

#ifdef HAS_xTests

    if (0 == efferents_count++)
    {
        std::cout << "\n" << "efferent dependencies:" << std::endl;
    }

    {
        unsigned const libver = _XTESTS_VER;

        version(std::cout, "\t", "xTests", "_XTESTS_VER", libver);
    }
#endif

    return EXIT_SUCCESS;
}

/* ///////////////////////////// end of file //////////////////////////// */

