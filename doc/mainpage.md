# CLASP {#mainpage}

**CLASP** (**C**ommand-**L**ine **A**rgument **S**orting and **P**arsing) is
a small C library for parsing command-line arguments, with a header-only
**C++** API. Arguments are classified as **flags**, **options**, and
**values**, with aliasing, combined short flags, standard `--` / `-`
handling, and library-provided usage and version output.


## Components

| Module | Header | Summary |
| ------ | ------ | ------- |
| \ref group__clasp__common | `<clasp/clasp.h>` | Shared types, specifications, and version macros |
| \ref group__clasp__api_parsing | `<clasp/clasp.h>` | Parse and query flags, options, and values |
| \ref group__clasp__api_usage | `<clasp/clasp.h>` | Usage and version display (`clasp_showUsage()`, `clasp_showVersion()`) |
| main() helper | `<clasp/main.h>` | `clasp_main_invoke()` for C programs |
| C++ API | `<clasp/clasp.hpp>` | `clasp::` wrappers (requires **STLSoft**) |
| C++ main() helper | `<clasp/main.hpp>` | `clasp::main::invoke()` |
| SearchSpecs | `<clasp/util/searchspecs.h>` | Directory/pattern search-specification helpers |


## Quick start

```c
#include <clasp/main.h>
#include <stdio.h>
#include <stdlib.h>

static clasp_specification_t const Specifications[] =
{
    CLASP_STOCK_FLAG_HELP,
    CLASP_STOCK_FLAG_VERSION,

    CLASP_SPECIFICATION_ARRAY_TERMINATOR
};

static
int main1(clasp_arguments_t const* args)
{
    if (clasp_flagIsSpecified(args, "--help"))
    {
        return clasp_showUsage(
            args
        ,   Specifications
        ,   NULL
        ,   "CLASP (http://github.com/synesissoftware/CLASP)"
        ,   "Copyright Matthew Wilson and Synesis Information Systems"
        ,   "illustrates minimal usage functionality"
        ,   NULL
        ,   0, 0, 0
        ,   clasp_showHeaderByFILE, clasp_showBodyByFILE, stdout
        ,   0
        ,   0
        ,   -2
        ,   1
        );
    }

    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    return clasp_main_invoke(argc, argv, main1, "tool", Specifications, 0, NULL);
}
```

The **C** core has no non-standard dependencies on UNIX. The **C++** API
depends on [**STLSoft**](https://github.com/synesissoftware/STLSoft/).
Consumer **CMake** projects may use `find_package(CLASP)` and link
`CLASP::core`. See
[INSTALL.md](https://github.com/synesissoftware/CLASP/blob/master/INSTALL.md)
for build and install instructions.


## Related projects

Projects in which **CLASP** is used include:

* [chomp](https://github.com/sistools/chomp/)
* [lstrip](https://github.com/sistools/lstrip/)
* [rstrip](https://github.com/sistools/rstrip/)
* [libCLImate](https://github.com/synesissoftware/libCLImate/)


<!-- ########################### end of file ########################### -->
