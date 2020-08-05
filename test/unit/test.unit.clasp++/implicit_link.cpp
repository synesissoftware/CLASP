/* /////////////////////////////////////////////////////////////////////////
 * File:        implicit_link.cpp
 *
 * Purpose:     Implicit link file for the test.unit.clasp++ project.
 *
 * Created:     16th July 2009
 * Updated:     5th August 2020
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* CLASP header files */
#include <clasp/implicit_link.h>

/* xTests header files */
#include <xtests/implicit_link.h>

/* recls header files */
#include <recls/implicit_link.h>

/* UNIXem header files */
#include <platformstl/platformstl.h>
#if defined(PLATFORMSTL_OS_IS_UNIX) && \
    defined(_WIN32)

# include <unixem/implicit_link.h>
#endif /* OS */

/* ///////////////////////////// end of file //////////////////////////// */

