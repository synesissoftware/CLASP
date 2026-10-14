
#include <clasp/clasp.h>

#include <woad/woad.h>

#include <iomanip>
#include <iostream>

#include <stdlib.h>


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
        << WOAD_FG_BLUE
        << libname
        << WOAD_RESET
        << ": "
        << WOAD_FG_GREEN
        << "v"
        << ((libver >> 24) & 0xff)
        << '.'
        << ((libver >> 16) & 0xff)
        << '.'
        << ((libver >> 8) & 0xff)
        << '.'
        << ((libver >> 0) & 0xff)
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


int main(int /* argc */, char* /* argv */[])
{
    {
        unsigned const libver = CLASP_VER;

        version(std::cout, "", "CLASP", "CLASP_VER", libver);
    }

    return EXIT_SUCCESS;
}
