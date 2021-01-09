/* /////////////////////////////////////////////////////////////////////////
 * File:        implicit_link.cpp
 *
 * Purpose:     Implicit link file for the test.component.searchspecs.C project.
 *
 * Created:     12th September 2014
 * Updated:     9th January 2021
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* CLASP header files */
#include <clasp/implicit_link.h>

/* xTests header files */
#include <xtests/implicit_link.h>

/* UNIXem header files */
#include <platformstl/platformstl.h>
#if defined(PLATFORMSTL_OS_IS_UNIX) && \
    defined(_WIN32)

# include <unixem/implicit_link.h>
#endif

/* ///////////////////////////// end of file //////////////////////////// */

