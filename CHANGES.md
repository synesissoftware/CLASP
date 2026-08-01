# **CLASP** Changes <!-- omit in toc -->


## 0.15.0 (rc 1) - 2nd August 2026

* improved definition of `CLASP_VER` (and associated preprocesor object-like macros);
* Added modular GitHub Actions CI (**ci.yml** / **ci-cell.yml**) with install-smoke coverage;
* Removed **HISTORY.md** (content merged into **CHANGES.md**);
* Modernised **CHANGES.md** (version-first headings; trailing semicolons);
* Trimmed **INSTALL.md** and **README.md** (badges; dependency links); README CI badge now targets **ci.yml**;
* CMake: added `option(BUILD_TESTING …)` for parity with peer libraries;
* **test.component.usage.resources.C**: corrected expanded-usage expectations (no trailing newline after final usage segment);
* Enhanced **run_all_unit_tests.sh** (`--unit-only` / `--component-only` and `--no-make` guard);
* Project boilerplate updates (**.gitattributes**, **.vimrc**, **.vscode/settings.json**);


## 0.15.0 (alpha 6) - 11th March 2025

* Added a _lot_ more tests of usage, and fixed several decent defects and missing bits of functionality;
* Renamed **test.unit.usage_width** to **test.unit.usage**, and added significantly more test coverage;
* Fixed defect whereby specifying multiple specifications with empty string, rather than `NULL`, as alias results in report of duplicates;
* Backwards-compatibility with C90;
* Improved documentation markup;


## 0.15.0 (alpha 5) - 10th March 2025

* **Visual C++** compatibility;


## 0.15.0 (alpha 4) - 10th March 2025

* added stock flag macros `CLASP_STOCK_FLAG_HELP()` and `CLASP_STOCK_FLAG_VERSION()`;


## 0.15.0 (alpha 3) - 9th March 2025

* fixed CMakeLists.txt such that it picks up `CLASP_VER_PATCH`;


## 0.15.0 (alpha 2) - 9th March 2025

* removed assertion left in **0.15.0-alpha1**;


## 0.15.0 (alpha 1) - 9th March 2025

* `clasp_showUsage()` and `clasp_showVersion()` now infer `clasp_usageinfo_t#toolName` if null;
* `clasp_showUsage()` handling of `usage` now accepts replacement null string, in which case will use suitable default;
* `clasp_showUsage()` handling of `usage` now accepts replacement sub-string `":program_name:"` and will replace with `toolName` value;
* `clasp_parseArguments()` now takes `argv` of type `char*[]` rather than `char const* const []`;
* added **minimal_usage** example;
* added **minimal_usage_xx** example;
* added **run_all_examples.sh**;
* added **CHANGES.md**;
* removed **build** directory and all manual makefiles within;
* removed Visual C++ project/solution files;
* CMake compatibility changes;
* GCC compatibility changes;
* Miscellaneous fixes to examples;


## 0.14.0 (beta 5) - 17th February 2025

* GCC / CMake compatibility;
* `clasp_parseArguments()` now takes `argv` of type `char*[]` rather than `char const* const []`;


## 0.14.0 (beta 4) - 23rd October 2024

* **INSTALL.md** : ~ typos;
* updated dependency on **xTests**;
* release notes;


## 0.14.0 (beta 3) - 18th October 2024

* CMake files fixes/improvements;
* CMake build script enhancements;
* numerous compiler warnings fixes;


## 0.14.0 (beta 2) - 12th February 2024

* CMake files fixes/improvements;
* added more test cases;


## 0.14.0 (beta 1) - 2nd February 2024

* added CMake support;
* various compiler compatibility improvements;


## 0.14.0 (alpha 5) - 16th February 2021

* added `clasp_getSpecifications()`;


## 0.14.0 (alpha 1) - 5th August 2020

* changed primary include directory to <clasp/*> from <systemtools/clasp/*>;


## 0.14.0 (alpha 0) - 5th August 2020

* Merge branch '0.14' of V:\git\freelibs\SystemTools\libraries\CLASP\CLASP into 0.14;


## 0.13.2 - 18th April 2019

* added several VC++ 10 project files;


## 0.13.1 - 29th January 2017

* numerous changes to 0.13;


## 0.11.10 - 29th January 2017

* fixed defect in `clasp_show_header_by_FILE()`;


## 0.11.9 - 29th January 2017

* `clasp_countAliases()` now requires non-NULL argument;


## 0.11.8 - 29th January 2017

* widestring compatibility;


## 0.11.7 - 29th January 2017

* removed vestigial files;


## 0.11.6 - 25th November 2016

* fixed defect in `clasp_show_header_by_FILE()` when usage is null/empty;


## 0.11.5 - 24th November 2016

* commit in haste, repent at leisure!;


## 0.11.4 - 24th November 2016

* `clasp_countAliases()` now tolerates NULL aliases parameter;


## 0.11.3 - 23rd November 2016

* fix to main `invoke()`;


## 0.11.2 - 28th September 2015

* `clasp_checkAllFlags()` now examines all possible matches until non-0 `bitFlags` member is found, which allows flag aliases for bit-flags to be specified in arbitrary order;


## 0.11.1 - 9th September 2015

* first GitHub version;


<!-- ########################### end of file ########################### -->
