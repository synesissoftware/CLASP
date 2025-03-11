/* /////////////////////////////////////////////////////////////////////////
 * File:    src/clasp.diagnostics.c
 *
 * Purpose: CLASP diagnostics facilities.
 *
 * Created: 4th June 2008
 * Updated: 11th March 2025
 *
 * Home:    https://github.com/synesissoftware/CLASP/
 *
 * Copyright (c) 2008-2025, Matthew Wilson
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer;
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution;
 * - Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include "clasp.internal.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

static
void
CLASP_CALLCONV clasp_default_log_fn_(
    void*               context
,   int                 severity
,   clasp_char_t const* fmt
,   va_list             args
)
{
    ((void)context);

    if (severity >= 0)
    {
        clasp_char_t  fmt_[1025];
        size_t const  n = clasp_strlen_(fmt);

        if (n + 1 < (sizeof(fmt_) / sizeof(fmt_[0])))
        {
            memcpy(fmt_, fmt, sizeof(clasp_char_t) * n);
            fmt_[n + 0] = '\n';
            fmt_[n + 1] = '\0';

            fmt = fmt_;
        }

#ifdef CLASP_USE_WIDE_STRINGS

        vfwprintf(stderr, fmt, args);
#else /* ? CLASP_USE_WIDE_STRINGS */

        vfprintf(stderr, fmt, args);
#endif /* CLASP_USE_WIDE_STRINGS */
        if (fmt != fmt_)
        {
            fputs("\n", stderr);
        }
    }
}

void
CLASP_LOG_PRINTF(
    clasp_diagnostic_context_t const*   ctxt
,   int                                 severityIndex
,   clasp_char_t const*                 fmt
,   ...
)
{
    if (NULL != ctxt->pfnLog)
    {
        va_list args;

        va_start(args, fmt);

        ctxt->pfnLog(ctxt->context, ctxt->severities[severityIndex], fmt, args);

        va_end(args);
    }
}

clasp_diagnostic_context_t const*
clasp_verify_context_(
    clasp_diagnostic_context_t const*   ctxt
,   clasp_diagnostic_context_t*         local
,   int*                                r
)
{
    CLASP_ASSERT(NULL != local);
    CLASP_ASSERT(NULL != r);

    local->context          =   NULL;
    local->pfnMalloc        =   clasp_stock_malloc_;
    local->pfnRealloc       =   clasp_stock_realloc_;
    local->pfnFree          =   clasp_stock_free_;
    local->pfnLog           =   clasp_default_log_fn_;
    local->severities[0]    =   -1; /* By default don't display any debug information */
    local->severities[1]    =   4;
    local->severities[2]    =   3;
    local->severities[3]    =   1;
    local->severities[4]    =   0;

    *r = 0;

    /* Check the context, and ensure that it specifies all the
     * memory functions, or none of them
     */
    if (NULL != ctxt)
    {
        int n = 0;

        n += (NULL != ctxt->pfnMalloc);
        n += (NULL != ctxt->pfnRealloc);
        n += (NULL != ctxt->pfnFree);

        if (0 != n &&
            3 != n)
        {
            *r = EINVAL;
        }

        /* If all ok, now copy over the three groups of
         * fields
         */

        local->context       =   NULL;

        if (NULL != ctxt->pfnMalloc)
        {
            local->pfnMalloc        =   ctxt->pfnMalloc;
            local->pfnRealloc       =   ctxt->pfnRealloc;
            local->pfnFree          =   ctxt->pfnFree;
        }

        if (NULL != ctxt->pfnLog)
        {
            local->pfnLog           =   ctxt->pfnLog;
            local->severities[0]    =   ctxt->severities[0];
            local->severities[1]    =   ctxt->severities[1];
            local->severities[2]    =   ctxt->severities[2];
            local->severities[3]    =   ctxt->severities[3];
            local->severities[4]    =   ctxt->severities[4];
        }
    }

    return local;
}


/* ///////////////////////////// end of file //////////////////////////// */

