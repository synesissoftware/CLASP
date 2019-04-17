/* /////////////////////////////////////////////////////////////////////////
 * File:        src/clasp.memory.c
 *
 * Purpose:     CLASP memory facilities.
 *
 * Created:     4th June 2008
 * Updated:     18th April 2019
 *
 * Home:        https://github.com/synesissoftware/CLASP/
 *
 * Copyright (c) 2008-2019, Matthew Wilson
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name(s) of Matthew Wilson and Synesis Software nor the names of
 *   any contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

#include "clasp.internal.h"

#include <stdlib.h>

/* /////////////////////////////////////////////////////////////////////////
 * helper functions
 */

void* CLASP_CALLCONV clasp_stock_malloc_(void* context, size_t cb)
{
    ((void)context);

    return malloc(cb);
}
void* CLASP_CALLCONV clasp_stock_realloc_(void* context, void* pv, size_t cb)
{
    ((void)context);

    return realloc(pv, cb);
}
void CLASP_CALLCONV clasp_stock_free_(void* context, void* pv)
{
    ((void)context);

    free(pv);
}

void* clasp_malloc_(clasp_diagnostic_context_t const* ctxt, size_t cb)
{
    CLASP_ASSERT(NULL != ctxt);

    return ctxt->pfnMalloc(ctxt->context, cb);
}
void* clasp_realloc_(clasp_diagnostic_context_t const* ctxt, void* pv, size_t cb)
{
    CLASP_ASSERT(NULL != ctxt);

    return ctxt->pfnRealloc(ctxt->context, pv, cb);
}
void clasp_free_(clasp_diagnostic_context_t const* ctxt, void* pv)
{
    CLASP_ASSERT(NULL != ctxt);

    ctxt->pfnFree(ctxt->context, pv);
}

/* ///////////////////////////// end of file //////////////////////////// */

