# CLASP <!-- omit in toc -->

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
  - [Related projects](#related-projects)
  - [License](#license)


## Introduction

**CLASP** - **C**ommand-**L**ine **A**rgument **S**orting and **P**arsing - is a small, simple
C-language library for parsing command-line arguments, along with a C++
header-only API.

The features of the library are:

- arguments are parsed according to the taxonomy:
 - **flags**, which express yes/no (or true/false, or on/off) choices, and begin with one or more hyphens and have no value, e.g. ```--verbose```, ```-v```;
 - **values**, which express an unnamed value, and do not begin with a hyphen, e.g. ```.```, ```makefile```;
 - **options**, which express a named value, and take one of the forms:
    - a single argument comprising a hyphen-prefixed name ```=```-separated from a value, e.g.  ```--root-dir=~```; or
    - a pair of consecutive arguments comprising a hyphen-prefixed name and a value, e.g. ```-r ~```. (This option requires use of aliases;)
- support for the standard UNIX ```--``` argument, which causes all subsequent arguments to be interpreted as values;
- support for the standard UNIX ```-``` argument, allowing it to be interpreted as a value, despite beginning with a hyphen;
- a simple protocol whereby flags and options may have aliases, e.g. specifying alias ```-v``` for ```--verbose``` allows either to be specified on the command-line, while the discriminating code need only check for the ```--verbose``` full form;
- combination of flags' single letter forms (or aliases) for succinct, e.g. if ```-x``` is an alias for ```--extract```, ```-l``` is an alias for ```--form=list```, and ```-p``` for ```---include-all-patterns```, and the command line contains the composite argument ```-xpl```, this is equivalent to ```--extract ---include-all-patterns --form=list```;
- wildcards are expanded on Windows (since its command-interpreter does not do wildcard expansion);
- library functions that automatically provide usage and version functionality, including flag/option, aliases, help string, and valid values, facilitating implenentation of standard ```--help``` and ```--version``` flags;
- an overarching principal of the design is that command-line processing must be separable from the rest of the program logic, hence:
 - the specification of the aliases is done declaratively, in an array of alias definitions;
 - there is a rich set of functions for discovering flags, options, and values, and eliciting their _values_ in different data types
- apart from memory allocation (of which there is only one), the library is no-fail, so can never be a source of program failure, allowing it to form a reliable part of C/C++ CLI program frameworks;
- the core (C) library has no non-standard dependencies on UNIX; on Windows it depends on the [**recls**](http://sourceforge.net/projects/recls/) library;
- the C++ API depends on the [**STLSoft**](http://sourceforge.net/projects/stlsoft/) library;


The design of the library is discussed in detail in the article _An Introduction to CLASP, part 1: C_, Matthew Wilson, [CVu](http://accu.org/index.php/journals/c77/), January 2012. (For those of you not subscribers to the [ACCU](http://accu.org/)'s [CVu](http://accu.org/index.php/journals/c77/) journal, this article will be made available on the [Synesis Software](http://www.synesis.com.au) website before end of September.)


## Installation

Detailed instructions - via **CMake**, via bundling, via custom makefile
parameters - are provided in the accompanying [INSTALL.md](./INSTALL.md)
file.


## Components

### C API / core library

T.B.C.


### C++ API

T.B.C.


## Examples

Examples are provided in the ```examples``` directory, along with a markdown description for each.


## Project Information

### Where to get help

[GitHub Page](https://github.com/synesissoftware/CLASP "GitHub Page")


### Contribution guidelines

Defect reports, feature requests, and pull requests are welcome on https://github.com/synesissoftware/CLASP.


### Dependencies

#### STLSoft (optional) <!-- omit in toc -->

The original (~2005) implementation used **STLSoft** for discrimination of compilers and for library support. For modern compilers with broad support for the latest language standards this is not necessary. Hence, if the preprocessor symbol `SHWILD_NO_STLSOFT` is specified then all dependencies on **STLSoft** are removed and basic **C++-14** features are used instead. (This is done in the **CMake** configuration provided - see [INSTALL.md](./INSTALL.md).)

If you _do_ need **STLSoft**, then version 1.10.6 or later is recommended. If you're using a _very_ old compiler you may wish to use STLSoft-1.9, for which version 1.9.136 is recommended. Further, the makefiles require definition of the environment variable `STLSOFT` that should be set to the root directory of a clone of **STLSoft**.

* [STLSoft 1.9](http://github.com/synesissoftware/STLSoft-1.9/)
* [STLSoft 1.10](http://github.com/synesissoftware/STLSoft-1.10/) (Recommended)


### Related projects

Projects in which **CLASP** is used include:

T.B.C.


### License

**CLASP** is released under the 3-clause BSD license. See [LICENSE](./LICENSE) for details.


<!-- ########################### end of file ########################### -->

