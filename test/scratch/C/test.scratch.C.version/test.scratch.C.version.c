/* /////////////////////////////////////////////////////////////////////////
 * File:        test.scratch.C.version.c
 *
 * Purpose:     Implementation file for the test.scratch.C.version project.
 *
 * Created:     6th December 2011
 * Updated:     10th January 2021
 *
 * Status:      Wizard-generated
 *
 * License:     BSD (3-clause)
 *
 *              Copyright (c) 2019-2021, Synesis Information Systems Pty Ltd.
 *              Copyright (c) 2011-2019, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://github.com/synesissoftware/CLASP
 *
 * ////////////////////////////////////////////////////////////////////// */


/* CLASP header files */
#include <clasp/clasp.h>

/* Standard C header files */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* /////////////////////////////////////////////////////////////////////////
 * compatibility
 */

#if defined(_MSC_VER) && \
    _MSC_VER >= 1400
# pragma warning(push)
# pragma warning(disable : 4996)
#endif

/* ////////////////////////////////////////////////////////////////////// */

static clasp_specification_t const Specifications[] =
{
    CLASP_FLAG(NULL,    "--help",           "show usage and quit"),
    CLASP_FLAG("-v",    "--version",        "show version and quit"),

    CLASP_OPTION("-o",  "--output-file",    "specify the output-file", ""),

    CLASP_SPECIFICATION_ARRAY_TERMINATOR
};

/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char** argv)
{
    clasp_arguments_t const* args;

    int cr = clasp_parseArguments(0, argc, argv, Specifications, 0, &args);

    if (cr < 0)
    {
        fprintf(stderr, "failed to parse arguments : %s (%d)\n", strerror(errno), errno);

        return EXIT_FAILURE;
    }
    else
    {
        puts("");
        printf("flags:\t%lu\n", args->numFlags);

        { size_t i; for (i = 0; i != args->numFlags; ++i)
        {
            clasp_argument_t const* const flag = args->flags + i;

            printf("flag-%02d:\t%.*s\t%.*s\n", (int)i, (int)flag->givenName.len, flag->givenName.ptr, (int)flag->resolvedName.len, flag->resolvedName.ptr);
        }}


        puts("");
        printf("options:\t%lu\n", args->numOptions);

        { size_t i; for (i = 0; i != args->numOptions; ++i)
        {
            clasp_argument_t const* const option = args->options + i;

            printf("option-%02d:\t%.*s\t%.*s\t=\t%.*s\n", (int)i, (int)option->givenName.len, option->givenName.ptr, (int)option->resolvedName.len, option->resolvedName.ptr, (int)option->value.len, option->value.ptr);
        }}


        puts("");
        printf("values:\t%lu\n", args->numValues);

        { size_t i; for (i = 0; i != args->numValues; ++i)
        {
            clasp_argument_t const* const value = args->values + i;

            printf("value-%02d:\t%.*s\n", (int)i, (int)value->value.len, value->value.ptr);
        }}


        /* Now "use" the flags/options as we would in a real program */

        if (clasp_flagIsSpecified(args, "--help"))
        {
            ; /* show usage */
        }
        if (clasp_flagIsSpecified(args, "--version"))
        {
            ; /* show version */
        }
        {
            clasp_argument_t const* const ofile = clasp_findFlagOrOption(args, "--output-file", 0);

            if (NULL != ofile)
            {
                ; /* do something with output file */
            }
        }

        /* now check for unrecognised arguments */
#if 0
        if(0 != clasp_reportUnrecognisedFlagsAndOptions(args, Specifications, NULL, 0))
        {
            clasp_argument_t const* unrecognisedArg;
            size_t const            n     = clasp_reportUnrecognisedFlagsAndOptions(args, Specifications, &unrecognisedArg, 0);
            size_t                  nSkip = 0;

            fprintf(stderr, "%lu unrecognised argument(s):\n", n);
            do
            {
                fprintf(stderr, "\tunrecognised argument: %s\n", args->argv[unrecognisedArg->cmdLineIndex]);

            } while (0 != clasp_reportUnrecognisedFlagsAndOptions(args, Specifications, &unrecognisedArg, ++nSkip));
        }
#else
        {
clasp_argument_t const* arg;
unsigned nSkip = 0;
size_t const n = clasp_reportUnrecognisedFlagsAndOptions(args, Specifications, &arg, nSkip);
if(0 != n)
{
  fprintf(stderr, "%lu unrecognised argument(s):\n", n);
  do
  {
    fprintf(stderr, "\tunrecognised argument: %s\n", args->argv[arg->cmdLineIndex]);

  } while (0 != clasp_reportUnrecognisedFlagsAndOptions(args, Specifications, &arg, ++nSkip));
}
        }
#endif

        /* now check for unused arguments */
#if 0
        if (0 != clasp_reportUnusedFlagsAndOptions(args, NULL, 0))
        {
            clasp_argument_t const* unusedArg;
            size_t const            n     = clasp_reportUnusedFlagsAndOptions(args, &unusedArg, 0);
            size_t                  nSkip = 0;

            fprintf(stderr, "%lu unused argument(s):\n", n);
            do
            {
                fprintf(stderr, "\tunused argument: %s\n", args->argv[unusedArg->cmdLineIndex]);

            } while (0 != clasp_reportUnusedFlagsAndOptions(args, &unusedArg, ++nSkip));
        }
#else
        {
clasp_argument_t const* arg;
unsigned nSkip = 0;
size_t const n = clasp_reportUnusedValues(args, &arg, nSkip);
if (0 != n)
{
  fprintf(stderr, "%lu unused argument(s):\n", n);
  do
  {
    fprintf(stderr, "\tunused argument: %s\n", args->argv[arg->cmdLineIndex]);
  } while (0 != clasp_reportUnusedValues(args, &arg, ++nSkip));
}

        }
#endif


        clasp_releaseArguments(args);

        return EXIT_SUCCESS;
    }
}

/* ///////////////////////////// end of file //////////////////////////// */

