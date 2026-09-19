# CLASP <!-- omit in toc -->

**C**ommand-**L**ine **A**rgument **S**orting and **P**arsing, for C (and C++)

![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat&logo=c%2B%2B&logoColor=white)
[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
[![GitHub release](https://img.shields.io/github/v/release/synesissoftware/CLASP.svg)](https://github.com/synesissoftware/CLASP/releases/latest)
[![CI](https://github.com/synesissoftware/CLASP/actions/workflows/ci.yml/badge.svg)](https://github.com/synesissoftware/CLASP/actions/workflows/ci.yml)
[![Last Commit](https://img.shields.io/github/last-commit/synesissoftware/CLASP)](https://github.com/synesissoftware/CLASP/commits/master)


## Table of Contents <!-- omit in toc -->


- [Introduction](#introduction)
- [Installation](#installation)
- [Components](#components)
  - [C API / core library](#c-api--core-library)
  - [C++ API](#c-api)
- [Examples](#examples)
- [Project Information](#project-information)
  - [Where to get help](#where-to-get-help)
  - [Contribution guidelines](#contribution-guidelines)
  - [Dependencies](#dependencies)
    - [Development Dependencies (required for testing)](#development-dependencies-required-for-testing)
  - [Related projects](#related-projects)
  - [License](#license)


## Introduction

**CLASP** - **C**ommand-**L**ine **A**rgument **S**orting and **P**arsing -
is a small, simple C-language library for parsing command-line arguments,
along with a C++ header-only API.

The features of the library are:

- **ARGUMENTS** are parsed according to the following taxonomy:
  - **FLAGS**, which express yes/no (or true/false, or on/off) choices, and begin with one or more hyphens and have no associated value, e.g. ```--verbose```, ```-v```;
  - **VALUES**, which express an unnamed value, and do not begin with a hyphen, e.g. ```..```, ```makefile```;
  - **OPTIONS**, which express a named value, and take one of the forms:
    - a single argument comprising a hyphen-prefixed name separated from a value by ```=```, e.g.  ```--root-dir=~```; or
    - a pair of consecutive (i.e. space-separated) arguments comprising a hyphen-prefixed name and a value, e.g. ```-r ~```. (This option requires use of **SPECIFICATIONS**;)
- support for the standard UNIX ```--``` argument, which causes all subsequent arguments to be interpreted as values;
- support for the standard UNIX ```-``` argument, allowing it to be interpreted as a value, despite beginning with a hyphen. This is commonly used by a program to stand for the standard-input or standard-output streams (rather than a named file input/output path);
- a simple protocol whereby *FLAGS* and *OPTIONS* may have *ALIASES*, e.g. specifying the alias ```-v``` for the flag ```--verbose``` allows either to be specified on the command-line, while the discriminating code need only check for the ```--verbose``` full form;
- combination of FLAGS' single letter forms (or aliases) for succinct, e.g. if ```-x``` is an alias for ```--extract```, ```-l``` is an alias for ```--form=list```, and ```-p``` for ```---include-all-patterns```, and the command line contains the composite argument ```-xpl```, this is equivalent to and processed as if the program received ```--extract ---include-all-patterns --form=list```. NOTE: if a flag or option exists with the name ```-xpl``` then the combined interpretation is not considered;
- wildcards may be expanded on Windows (since its batch command-interpreter does not do wildcard expansion);
- library functions that automatically provide usage and version functionality based on the program's SPECIFICATIONS, including flag/option, aliases, help string, and valid values, facilitating implementation of standard ```--help``` and ```--version``` flags;
- an overarching principle of the design is that command-line processing must be separable from the rest of the program logic, hence:
  - the specification of flags and options is done declaratively, in an array of `clasp_specification_t`;
  - there is a rich set of functions for discovering flags, options, and values, and eliciting their _values_ in different data types;
- apart from memory allocation (of which there is only one), the library is no-fail, so can never be a source of program failure, allowing it to form a reliable part of C/C++ CLI program frameworks;
- has minimal or no dependencies:
  - the core (C) library has no non-standard dependencies on UNIX; on Windows, wildcard expansion may optionally use [**recls**](https://github.com/synesissoftware/recls/) (disabled by default in the CMake build via `CLASP_CMDLINE_ARGS_NO_RECLS_ON_WINDOWS`);
  - the C++ API depends on the [**STLSoft**](https://github.com/synesissoftware/STLSoft/) library;


The design of the library is discussed in detail in the article "_An Introduction to CLASP, part 1: C_", Matthew Wilson, [CVu](http://accu.org/index.php/journals/c77/), January 2012. (For those of you not subscribers to the [ACCU](http://accu.org/)'s [CVu](http://accu.org/index.php/journals/c77/) journal, this article will be made available on the new Synesis Information Systems website before end of 2026.)


## Installation

Detailed instructions — via **CMake** — are provided in the accompanying
[INSTALL.md](./INSTALL.md) file.


## Components

### C API / core library

```C
/* examples/C/minimal_usage/main.c */
#include <clasp/main.h>
#include <stdio.h>

static clasp_specification_t const Specifications[] =
{
    CLASP_GAP_SECTION("standard flags:"),
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
        ,   NULL /* toolName inferred from process */
        ,   "CLASP (http://github.com/synesissoftware/CLASP)"
        ,   "Copyright Matthew Wilson and Synesis Information Systems"
        ,   "illustrates minimal usage functionality"
        ,   NULL /* toolName inferred from process/specifications */
        ,   0, 0, 0
        ,   clasp_showHeaderByFILE, clasp_showBodyByFILE, stdout
        ,   0  /* flags */
        ,   0  /* console width */
        ,   -2 /* indent size */
        ,   1  /* blank line between args? */
        );
    }

    if (clasp_flagIsSpecified(args, "--version"))
    {
        return clasp_showVersion(
            args
        ,   NULL /* toolName inferred from process */
        ,   0, 0, 0
        ,   clasp_showHeaderByFILE, stdout
        ,   0 /* flags */
        );
    }


    printf("args={ numArguments=%zu, numFlagsAndOptions=%zu, numFlags=%zu, numOptions=%zu, numValues=%zu, }\n"
    ,   args->numArguments
    ,   args->numFlagsAndOptions
    ,   args->numFlags
    ,   args->numOptions
    ,   args->numValues
    );


    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    unsigned const cflags = 0;

    return clasp_main_invoke(argc, argv, main1, "minimal_usage", Specifications, cflags, NULL);
}
```


### C++ API

```C++
// examples/C++/minimal_usage_xx/main.cpp
#include <clasp/main.hpp>
#include <cstdio>
#include <cstdlib>
#include <iostream>

static clasp::specification_t const Specifications[] =
{
    CLASP_GAP_SECTION("standard flags:"),
    CLASP_STOCK_FLAG_HELP,
    CLASP_STOCK_FLAG_VERSION,

    CLASP_SPECIFICATION_ARRAY_TERMINATOR
};

int main(int argc, char* argv[])
{
    return clasp::main::invoke(argc, argv, Specifications, [](clasp::arguments_t const& args) {

        if (clasp::flag_specified(args, "--help"))
        {
            return clasp::showUsage(
                args
            ,   NULL /* toolName inferred from process */
            ,   "CLASP (http://github.com/synesissoftware/CLASP)"
            ,   "Copyright Matthew Wilson and Synesis Information Systems"
            ,   "illustrates minimal usage functionality"
            ,   NULL /* toolName inferred from process/specifications */
            ,   PROGRAM_VER_ARGLIST
            );
        }

        if (clasp::flag_specified(args, "--version"))
        {
            return clasp::showVersion(args, PROGRAM_VER_ARGLIST);
        }


        std::cout << "args=" << args << std::endl;


        return EXIT_SUCCESS;
    });
}
```


## Examples

Examples are provided in the ```examples``` directory, along with a markdown description for each.


## Project Information

### Where to get help

[GitHub Page](https://github.com/synesissoftware/CLASP "GitHub Page")


### Contribution guidelines

Defect reports, feature requests, and pull requests are welcome on https://github.com/synesissoftware/CLASP.


### Dependencies

* [STLSoft 1.11](https://github.com/synesissoftware/STLSoft/)


#### Development Dependencies (required for testing)

* [xTests](https://github.com/synesissoftware/xTests/)


### Related projects

Projects in which **CLASP** is used include:

* [chomp](https://github.com/sistools/chomp/)
* [lstrip](https://github.com/sistools/lstrip/)
* [rstrip](https://github.com/sistools/rstrip/)
* [libCLImate](https://github.com/synesissoftware/libCLImate/)


### License

**CLASP** is released under the 3-clause BSD license. See [LICENSE](./LICENSE) for details.


<!-- ########################### end of file ########################### -->

