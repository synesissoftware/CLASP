/* /////////////////////////////////////////////////////////////////////////
 * File:    test/scratch/versions/main.cpp
 *
 * Purpose: Scratch-test program for CLASP showing version(s).
 *
 * Created: 19th September 2026
 * Updated: 4th November 2026
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

#ifdef woad_FOUND
# include <woad/woad.h>
# if (WOAD_VER_MAJOR > 0) || (WOAD_VER_MINOR >= 3)
#  define CLASP_SCRATCH_VERSIONS_HAVE_WOAD_IOSTREAMS_
#  include <woad/iostreams.hpp>
# endif /* woad 0.3+ IOStreams */
#endif /* woad_FOUND */

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
#ifdef CLASP_SCRATCH_VERSIONS_HAVE_WOAD_IOSTREAMS_
        << woad::blue(libname)
#else /* ? CLASP_SCRATCH_VERSIONS_HAVE_WOAD_IOSTREAMS_ */
        << WOAD_FG_BLUE << libname << WOAD_RESET
#endif /* CLASP_SCRATCH_VERSIONS_HAVE_WOAD_IOSTREAMS_ */
        << ": "
#ifdef CLASP_SCRATCH_VERSIONS_HAVE_WOAD_IOSTREAMS_
        << woad::green
#else /* ? CLASP_SCRATCH_VERSIONS_HAVE_WOAD_IOSTREAMS_ */
        << WOAD_FG_GREEN
#endif /* CLASP_SCRATCH_VERSIONS_HAVE_WOAD_IOSTREAMS_ */
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
#ifdef CLASP_SCRATCH_VERSIONS_HAVE_WOAD_IOSTREAMS_
        << woad::reset
#else /* ? CLASP_SCRATCH_VERSIONS_HAVE_WOAD_IOSTREAMS_ */
        << WOAD_RESET
#endif /* CLASP_SCRATCH_VERSIONS_HAVE_WOAD_IOSTREAMS_ */
        << " ("
#ifdef CLASP_SCRATCH_VERSIONS_HAVE_WOAD_IOSTREAMS_
        << woad::cyan(macroname)
#else /* ? CLASP_SCRATCH_VERSIONS_HAVE_WOAD_IOSTREAMS_ */
        << WOAD_FG_CYAN << macroname << WOAD_RESET
#endif /* CLASP_SCRATCH_VERSIONS_HAVE_WOAD_IOSTREAMS_ */
        << " = "
#ifdef CLASP_SCRATCH_VERSIONS_HAVE_WOAD_IOSTREAMS_
        << woad::green
#else /* ? CLASP_SCRATCH_VERSIONS_HAVE_WOAD_IOSTREAMS_ */
        << WOAD_FG_GREEN
#endif /* CLASP_SCRATCH_VERSIONS_HAVE_WOAD_IOSTREAMS_ */
        << "0x"
        << std::hex << std::setfill('0') << std::setw(8)
        << static_cast<unsigned>(libver)
        << std::dec
#ifdef CLASP_SCRATCH_VERSIONS_HAVE_WOAD_IOSTREAMS_
        << woad::reset
#else /* ? CLASP_SCRATCH_VERSIONS_HAVE_WOAD_IOSTREAMS_ */
        << WOAD_RESET
#endif /* CLASP_SCRATCH_VERSIONS_HAVE_WOAD_IOSTREAMS_ */
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

        version(std::cout, "\t", "woad", "WOAD_VER", libver, woad::version_string());
    }
#endif /* woad_FOUND */

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

