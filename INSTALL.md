# CLASP - Installation and Use <!-- omit in toc -->

**CLASP** is a classic-form C library (with a C++ API), insofar as it has
implementation files in its **src** directory and header files in its
**include/clasp** directory. Thus, once "installed", one must simply include
**clasp/clasp.h** (or one of the utility headers), and compile-in or link-in
the implementation.

The **C** API / core library has no non-standard dependencies (on Windows,
wildcard expansion may optionally use **recls**, which is disabled by default
in the CMake build). The **C++** API depends on **STLSoft** 1.11 (or later);
as of **0.16.0-alpha1**, C++ helpers such as **`clasp::main::invoke()`**,
**`clasp::flag_specified()`**, **`clasp::showUsage()`**, and
**`clasp::showVersion()`** accept **`arguments_t`** by reference as well as
by pointer. Building the project's tests additionally requires **xTests**
0.25 (or later).


## Table of Contents <!-- omit in toc -->

- [CMake](#cmake)



## CMake

The primary choice for installation is by use of **CMake**.

1. Obtain the latest distribution of **CLASP**, from
   https://github.com/synesissoftware/CLASP/, e.g.

   ```bash
   $ mkdir -p ~/open-source
   $ cd ~/open-source
   $ git clone https://github.com/synesissoftware/CLASP/
   ```

2. Prepare the CMake configuration, via the **prepare_cmake.sh** script.

   For a minimal **C** API-only install (no **STLSoft** / **xTests**
   required):

   ```bash
   $ cd ~/open-source/CLASP
   $ ./prepare_cmake.sh --no-cpp --disable-testing -v
   ```

   For a full build including the **C++** API, examples, and tests, install
   **STLSoft** 1.11 (and **xTests** for tests) via their own **CMake**
   scripts first, then:

   ```bash
   $ cd ~/open-source/CLASP
   $ ./prepare_cmake.sh -v
   ```

   If **STLSoft** is available as a source tree rather than an installed
   **CMake** package, pass its root with `--stlsoft-root-dir` / `-s`.

   (**Hint**: execute `$ ./prepare_cmake.sh --help` for more information.)

3. Run a build of the generated **CMake**-derived build files via the
   **build_cmake.sh** script, as in:

   ```bash
   $ ./build_cmake.sh
   ```

   (**NOTE**: if you provide the flag `--run-make` (=== `-m`) in step 2 then
   you do not need this step.)

4. As a check (when testing was not disabled), execute the built test
   programs via **run_all_unit_tests.sh**, as in:

   ```bash
   $ ./run_all_unit_tests.sh
   ```

5. Install the library on the host, via `cmake`, as in:

   ```bash
   $ sudo cmake --install ${SIS_CMAKE_BUILD_DIR:-./_build} --config Release
   ```

6. Then to use the library, it is a simple matter as follows:

   1. Assuming a simplest possible program to verify the installation:

        ```cpp
        // main.cpp
        #include <clasp/clasp.h>
        #include <stdio.h>
        #include <stdlib.h>

        int main(int argc, char* argv[])
        {
          ((void)&argc);
          ((void)&argv);

          clasp_countSpecifications(NULL);

          printf("using CLASP (minimally)\n");

          return EXIT_SUCCESS;
        }
        ```

   2. Compile your project against **CLASP**:

      Due to the installation step (Step 5 above) there is no requirement
      for an explicit include directory for **CLASP**:

      ```bash
      $ g++ -c -std=c++11 -D UNIX main.cpp
      ```

   3. Link your project against **CLASP**:

      Due to the installation step (Step 5 above) there is no requirement
      for an explicit library directory for **CLASP**:

      ```bash
      $ g++ main.o -lclasp
      ```

   4. Test your project:

      Then you can run, as in:

      ```bash
      $ ./a.out
      using CLASP (minimally)
      $
      ```


<!-- ########################### end of file ########################### -->
