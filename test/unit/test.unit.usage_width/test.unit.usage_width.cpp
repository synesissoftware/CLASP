/* /////////////////////////////////////////////////////////////////////////
 * File:        test.unit.usage_width.cpp
 *
 * Purpose:     Implementation file for the test.unit.usage_width project.
 *
 * Created:     3rd April 2014
 * Updated:     18th April 2019
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2014-2019, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <systemtools/clasp/clasp.h>

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* xTests header files */
#include <xtests/xtests.h>
#include <xtests/util/temp_file.hpp>

/* STLSoft header files */
#include <winstl/filesystem/file_functions.hpp>
#include <stlsoft/smartptr/scoped_handle.hpp>
#include <stlsoft/stlsoft.h>

/* Standard C++ header files */
#include <string>
#include <vector>

/* Standard C header files */
#include <stdlib.h>

/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

namespace
{

    static void test_empty_aliases(void);
    static void test_single_flag_changing_positiveTabSizes(void);
    static void test_single_flag_changing_consoleWidths(void);
    static void test_1_3(void);
    static void test_1_4(void);
    static void test_1_5(void);
    static void test_1_6(void);
    static void test_1_7(void);
    static void test_1_8(void);
    static void test_1_9(void);
    static void test_1_10(void);
    static void test_1_11(void);
    static void test_1_12(void);
    static void test_1_13(void);
    static void test_1_14(void);
    static void test_1_15(void);
    static void test_1_16(void);
    static void test_1_17(void);
    static void test_1_18(void);
    static void test_1_19(void);

} // anonymous namespace

/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if(XTESTS_START_RUNNER("test.unit.usage_width", verbosity))
    {
        XTESTS_RUN_CASE(test_empty_aliases);
        XTESTS_RUN_CASE(test_single_flag_changing_positiveTabSizes);
        XTESTS_RUN_CASE(test_single_flag_changing_consoleWidths);
        XTESTS_RUN_CASE(test_1_3);
        XTESTS_RUN_CASE(test_1_4);
        XTESTS_RUN_CASE(test_1_5);
        XTESTS_RUN_CASE(test_1_6);
        XTESTS_RUN_CASE(test_1_7);
        XTESTS_RUN_CASE(test_1_8);
        XTESTS_RUN_CASE(test_1_9);
        XTESTS_RUN_CASE(test_1_10);
        XTESTS_RUN_CASE(test_1_11);
        XTESTS_RUN_CASE(test_1_12);
        XTESTS_RUN_CASE(test_1_13);
        XTESTS_RUN_CASE(test_1_14);
        XTESTS_RUN_CASE(test_1_15);
        XTESTS_RUN_CASE(test_1_16);
        XTESTS_RUN_CASE(test_1_17);
        XTESTS_RUN_CASE(test_1_18);
        XTESTS_RUN_CASE(test_1_19);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

namespace
{
    typedef std::string             string_t;
    typedef std::vector<string_t>   strings_t;

    static
    strings_t
    get_body_lines(
        clasp_alias_t const*    aliases
    ,   int                     tabSize
    ,   int                     consoleWidth
    ,   int                     showBlanksBetweenItems
    )
    {
        using namespace ::xtests::cpp;

        temp_file   temp(temp_file::DeleteOnOpen | temp_file::DeleteOnClose);
        FILE*       stm = ::fopen(temp.c_str(), "w");

        if(NULL == stm)
        {
            throw std::runtime_error("could not open file");
        }
        else
        {
            stlsoft::scoped_handle<FILE*> scoper(stm, ::fclose);

            clasp_showBody(
                    NULL
                ,   aliases
                ,   clasp_showBodyByFILE
                ,   stm
                ,   0
                ,   tabSize
                ,   consoleWidth
                ,   showBlanksBetweenItems
                );

            scoper.close();

            strings_t   lines;

            winstl::readlines(string_t(temp.c_str()), lines);

            return lines;
        }
    }

static void test_empty_aliases()
{
    clasp_alias_t const aliases[] =
    {

        CLASP_ALIAS_ARRAY_TERMINATOR
    };
    int consoleWidth = 80;
    int tabSize = 8;
    int showBlanksBetweenItems = 0;

    strings_t lines = get_body_lines(aliases, consoleWidth, tabSize, showBlanksBetweenItems);

    XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(2u, lines.size()));
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Options:", lines[0]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
}

static void test_single_flag_changing_positiveTabSizes()
{
    clasp_alias_t const aliases[] =
    {
        CLASP_FLAG(NULL, "--flag1", "this is a flag"),

        CLASP_ALIAS_ARRAY_TERMINATOR
    };
    int consoleWidth            =   80;
    int tabSize                 =   0;
    int showBlanksBetweenItems  =   0;

    strings_t lines = get_body_lines(aliases, consoleWidth, tabSize, showBlanksBetweenItems);

    XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(4u, lines.size()));
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Options:", lines[0]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--flag1", lines[2]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("this is a flag", lines[3]);

    for(tabSize = 1; 34 != tabSize; ++tabSize)
    {
        strings_t lines = get_body_lines(aliases, consoleWidth, tabSize, showBlanksBetweenItems);

        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(4u, lines.size()));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Options:", lines[0]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t--flag1", lines[2]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tthis is a flag", lines[3]);
    }
    for(tabSize = 34; 36 != tabSize; ++tabSize)
    {
        strings_t lines = get_body_lines(aliases, consoleWidth, tabSize, showBlanksBetweenItems);

        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(5u, lines.size()));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Options:", lines[0]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t--flag1", lines[2]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tthis is a", lines[3]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tflag", lines[4]);
    }
    for(tabSize = 36; 37 != tabSize; ++tabSize)
    {
        strings_t lines = get_body_lines(aliases, consoleWidth, tabSize, showBlanksBetweenItems);

        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(5u, lines.size()));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Options:", lines[0]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t--flag1", lines[2]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tthis is", lines[3]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\ta flag", lines[4]);
    }
    for(tabSize = 37; 38 != tabSize; ++tabSize)
    {
        strings_t lines = get_body_lines(aliases, consoleWidth, tabSize, showBlanksBetweenItems);

        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(6u, lines.size()));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Options:", lines[0]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t--flag1", lines[2]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tthis", lines[3]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tis a", lines[4]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tflag", lines[5]);
    }
    for(tabSize = 38; 80 != tabSize; ++tabSize)
    {
        strings_t lines = get_body_lines(aliases, consoleWidth, tabSize, showBlanksBetweenItems);

        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(7u, lines.size()));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Options:", lines[0]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t--flag1", lines[2]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tthis", lines[3]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tis", lines[4]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\ta", lines[5]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tflag", lines[6]);
    }
}

static void test_single_flag_changing_consoleWidths()
{
    clasp_alias_t const aliases[] =
    {
        CLASP_FLAG(NULL, "--flag1", "this is a flag"),

        CLASP_ALIAS_ARRAY_TERMINATOR
    };
    int consoleWidth;
    int tabSize                 =   -1;
    int showBlanksBetweenItems  =   0;

    for(consoleWidth = 16; consoleWidth != 1000; ++consoleWidth)
    {
        strings_t lines = get_body_lines(aliases, consoleWidth, tabSize, showBlanksBetweenItems);

        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(4u, lines.size()));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Options:", lines[0]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL(" --flag1", lines[2]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("  this is a flag", lines[3]);
    }
    for(consoleWidth = 12; consoleWidth != 16; ++consoleWidth)
    {
        strings_t lines = get_body_lines(aliases, consoleWidth, tabSize, showBlanksBetweenItems);

        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(5u, lines.size()));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Options:", lines[0]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL(" --flag1", lines[2]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("  this is a", lines[3]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("  flag", lines[4]);
    }
}

static void test_1_3()
{
}

static void test_1_4()
{
}

static void test_1_5()
{
}

static void test_1_6()
{
}

static void test_1_7()
{
}

static void test_1_8()
{
}

static void test_1_9()
{
}

static void test_1_10()
{
}

static void test_1_11()
{
}

static void test_1_12()
{
}

static void test_1_13()
{
}

static void test_1_14()
{
}

static void test_1_15()
{
}

static void test_1_16()
{
}

static void test_1_17()
{
}

static void test_1_18()
{
}

static void test_1_19()
{
}


} // anonymous namespace

/* ///////////////////////////// end of file //////////////////////////// */

