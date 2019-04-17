/* /////////////////////////////////////////////////////////////////////////
 * File:        implicit_link.cpp
 *
 * Purpose:     Implicit link file for the test.unit.clasp++ project.
 *
 * Created:     16th July 2009
 * Updated:     18th April 2019
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2009-2019, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* SystemTools::CLASP header files */
#include <systemtools/clasp/implicit_link.h>

/* xTests header files */
#include <xtests/implicit_link.h>

/* recls header files */
#include <recls/implicit_link.h>

/* UNIXem header files */
#include <platformstl/platformstl.h>
#if defined(platformstl_OS_IS_UNIX) && \
    defined(_WIN32)
# include <unixem/implicit_link.h>
#endif /* OS */

/* ///////////////////////////// end of file //////////////////////////// */

