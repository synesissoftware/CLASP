/* /////////////////////////////////////////////////////////////////////////
 * File:    examples/cvu/prg/prg.c
 *
 * Purpose: Implementation file for the prg example project.
 *
 * Created: 8th December 2011
 * Updated: 11th March 2025
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* CLASP header files */
#include <clasp/clasp.h>

/* Standard C header files */
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


/* /////////////////////////////////////////////////////////////////////////
 * globals
 */

static clasp_specification_t const Specifications[] =
{
  /* Filtering behaviour flags/options */

  CLASP_GAP_SECTION("filtering:"),

  CLASP_FLAG("-a",          "--all",                          "equivalent to -bclt"),

  CLASP_OPTION(NULL,        "--strip-blanks=multiple",        "causes blank lines in the input to be stripped", "|all|multiple|no"),
  CLASP_OPTION_ALIAS("-b",  "--strip-blanks=all"),
  CLASP_OPTION_ALIAS("-B",  "--strip-blanks=no"),

  CLASP_OPTION(NULL,        "--strip-comments=yes",           "causes comments in the input to be stripped", "|yes|no"),
  CLASP_OPTION_ALIAS("-c",  "--strip-comments=yes"),
  CLASP_OPTION_ALIAS("-C",  "--strip-comments=no"),

  CLASP_OPTION(NULL,        "--trim-leading-whitespace=yes",  "causes leading whitespace to be trimmed", "|yes|no"),
  CLASP_OPTION_ALIAS("-l",  "--trim-leading-whitespace=yes"),
  CLASP_OPTION_ALIAS("-L",  "--trim-leading-whitespace=no"),

  CLASP_OPTION(NULL,        "--trim-trailing-whitespace=yes", "causes trailing whitespace to be trimmed", "|yes|no"),
  CLASP_OPTION_ALIAS("-t",  "--trim-trailing-whitespace=yes"),
  CLASP_OPTION_ALIAS("-T",  "--trim-trailing-whitespace=no"),

  /* History flags/options */

  CLASP_GAP_SECTION("history:"),

  CLASP_OPTION("-h",  "--histfile",                     "specifies a file into which will be written the history of each modification made to the input stream that will cause the output to differ", ""),
  CLASP_FLAG("-e",    "--relative",                     "use relative paths in history"),

  /* Standard flags */

  CLASP_GAP_SECTION("standard flags:"),

  CLASP_STOCK_FLAG_HELP,
  CLASP_STOCK_FLAG_VERSION,

  CLASP_SPECIFICATION_ARRAY_TERMINATOR
};


/* /////////////////////////////////////////////////////////////////////////
 * main()
 */

int main(int argc, char** argv)
{
  unsigned const            cflags  = 0;
  clasp_arguments_t const*  args;
  int const                 cr      = clasp_parseArguments(cflags, argc, argv, Specifications, NULL, &args);

  if (cr != 0)
  {
    fprintf(stderr, "failed to initialise : %s (%d)\n", strerror(cr), cr);

    return EXIT_FAILURE;
  }
  else
  {
    if (clasp_flagIsSpecified(args, "--help"))
    {
      clasp_showUsage(
        NULL
      , Specifications
      , "prg"
      , "SystemTools (http://systemtools.sourceforge.net/)"
      , "Copyright Matthew Wilson"
      , "Exercises CLASP (C) for CVu"
      , "!USAGE:!prg [... options ...] [<infile> | -] [<outfile> | -]"
      , 1, 0, 1 /* version: maj, min, rev */
      , clasp_showHeaderByFILE, clasp_showBodyByFILE, stdout
      , 0  /* flags */
      , 76 /* console width */
      , -2 /* indent size */
      , 1  /* blank line between args? */
      );
    }
    else
    {
      puts("");
      printf("flags:\t%lu\n", (unsigned long)args->numFlags);
      { size_t i; for (i = 0; i != args->numFlags; ++i)
      {
          clasp_argument_t const* const flag = args->flags + i;

          /* Treat strings as slices {len+ptr} */
          printf("flag-%02d:\t%.*s\t%.*s\n", (int)i, (int)flag->givenName.len, flag->givenName.ptr, (int)flag->resolvedName.len, flag->resolvedName.ptr);
      }}


      puts("");
      printf("options:\t%lu\n", (unsigned long)args->numOptions);

      { size_t i; for (i = 0; i != args->numOptions; ++i)
      {
          clasp_argument_t const* const option = args->options + i;

          /* Treat strings as C-style strings */
          printf("option-%02d:\t%s\t%s\t=\t%s\n", (int)i, option->givenName.ptr, option->resolvedName.ptr, option->value.ptr);
      }}


      puts("");
      printf("values:\t%lu\n", (unsigned long)args->numValues);

      { size_t i; for (i = 0; i != args->numValues; ++i)
      {
          clasp_argument_t const* const value = args->values + i;

#if 0 /* set this to one to test UNDEFINED, NON-PORTABLE succinct syntax, iff sizeof(int) == sizeof(size_t) !! */

          static_assert(sizeof(int) == sizeof(size_t));

          /* Treat strings as slices {len+ptr} in non-portable way! */
          printf("value-%02d:\t%.*s\n", (int)i, value->value);
#else /* ? 0 */

          /* Treat strings as slices {len+ptr}*/
          printf("value-%02d:\t%.*s\n", (int)i, (int)value->value.len, value->value.ptr);
#endif /* 0 */
      }}
    }

    clasp_releaseArguments(args);

    return EXIT_SUCCESS;
  }
}


/* ///////////////////////////// end of file //////////////////////////// */

