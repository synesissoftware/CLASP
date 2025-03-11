# CLASP - CHANGES list <!-- omit in toc -->


## 11th March 2025 - 0.15.0-alpha6

* Added a _lot_ more tests of usage, and fixed several decent defects and missing bits of functionality;
* Renamed **test.unit.usage_width** to **test.unit.usage**, and added significantly more test coverage;
* Fixed defect whereby specifying multiple specifications with empty string, rather than `NULL`, as alias results in report of duplicates;
* Backwards-compatibility with C90;
* Improved documentation markup;


## 10th March 2025 - 0.15.0-alpha5

* **Visual C++** compatibility;


## 10th March 2025 - 0.15.0-alpha4

* added stock flag macros `CLASP_STOCK_FLAG_HELP()` and `CLASP_STOCK_FLAG_VERSION()`;


## 9th March 2025 - 0.15.0-alpha3

* fixed CMakeLists.txt such that it picks up `CLASP_VER_PATCH`;


## 9th March 2025 - 0.15.0-alpha2

* removed assertion left in **0.15.0-alpha1**;


## 9th March 2025 - 0.15.0-alpha1

* `clasp_showUsage()` and `clasp_showVersion()` now infer `clasp_usageinfo_t#toolName` if null;
* `clasp_showUsage()` handling of `usage` now accepts replacement null string, in which case will use suitable default;
* `clasp_showUsage()` handling of `usage` now accepts replacement sub-string `":program_name:"` and will replace with `toolName` value;
* `clasp_parseArguments()` now takes `argv` of type `char*[]` rather than `char const* const []`;
* added **minimal_usage** example;
* added **minimal_usage_xx** example;
* added **run_all_examples.sh**;
* added **CHANGES.md**;
* removed **build** directory and all manual makefiles within
* removed Visual C++ project/solution files
* CMake compatibility changes;
* GCC compatibility changes;
* Miscellaneous fixes to examples;


## 23rd October 2024 - 0.14.0-beta4

* **INSTALL.md** : ~ typos;
* ~ updated dependency on **xTests**;
* ~ release notes;


## 18th October 2024 - 0.14.0-beta3

* CMake files fixes/improvements;
* CMake build script enhancements;
* numerous compiler warnings fixes;


## 12th February 2024 - 0.14.0-beta2

* CMake files fixes/improvements;
* added more test cases;


## 2nd February 2024 - 0.14.0-beta1

* added CMake support;
* various compiler compatibility improvements;


## 16th February 2021 - 0.14.0-alpha5

* + added `clasp_getSpecifications()`;


## 5th August 2020 - 0.14.0-alpha1

* ~ changed primary include directory to <clasp/*> from <systemtools/clasp/*>;


## 5th August 2020 - 0.14.0-alpha0

* Merge branch '0.14' of V:\git\freelibs\SystemTools\libraries\CLASP\CLASP into 0.14;


## 18th April 2019 - 0.13.2

* + added several VC++ 10 project files;


## 29th January 2017 - 0.13.1

* + numerous changes to 0.13;


## 29th January 2017 - 0.11.10

* ~ fixed defect in `clasp_show_header_by_FILE()`;


## 29th January 2017 - 0.11.9

* ~ `clasp_countAliases()` now requires non-NULL argument;


## 29th January 2017 - 0.11.8

* ~ widestring compatibility;


## 29th January 2017 - 0.11.7

* - removed vestigial files;


## 25th November 2016 - 0.11.6

* ~ fixed defect in `clasp_show_header_by_FILE()` when usage is null/empty;


## 24th November 2016 - 0.11.5

* commit in haste, repent at leisure!;


## 24th November 2016 - 0.11.4

* `clasp_countAliases()` now tolerates NULL aliases parameter;


## 23rd November 2016 - 0.11.3

* ~ fix to main `invoke()`;


## 28th September 2015 - 0.11.2

* ~ `clasp_checkAllFlags()` now examines all possible matches until non-0 `bitFlags` member is found, which allows flag aliases for bit-flags to be specified in arbitrary order;


## 9th September 2015 - 0.11.1

* first GitHub version;


<!-- ########################### end of file ########################### -->

