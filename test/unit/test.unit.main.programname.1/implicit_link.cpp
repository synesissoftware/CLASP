/* /////////////////////////////////////////////////////////////////////////
 * File:        implicit_link.cpp
 *
 * Purpose:     Implicit link file for the test.unit.main.programname.1 project.
 *
 * Created:     9th March 2013
 * Updated:     9th January 2021
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* CLASP header files */
#include <clasp/implicit_link.h>

/* recls header files */
#include <recls/implicit_link.h>

/* xTests header files */
#include <xtests/implicit_link.h>

/* UNIXem header files */
#include <platformstl/platformstl.h>
#if defined(PLATFORMSTL_OS_IS_UNIX) && \
    defined(_WIN32)

# include <unixem/implicit_link.h>
#endif

/* ///////////////////////////// end of file //////////////////////////// */

