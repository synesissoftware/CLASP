/* /////////////////////////////////////////////////////////////////////////
 * File:        implicit_link.cpp
 *
 * Purpose:     Implicit link file for the test.unit.usage_width project.
 *
 * Created:     3rd April 2014
 * Updated:     9th January 2021
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/implicit_link.h>

#include <clasp/implicit_link.h>

#include <recls/implicit_link.h>

/* UNIXem header files */
#include <platformstl/platformstl.h>
#if defined(PLATFORMSTL_OS_IS_UNIX) && \
    defined(_WIN32)

# include <unixem/implicit_link.h>
#endif

/* ///////////////////////////// end of file //////////////////////////// */

