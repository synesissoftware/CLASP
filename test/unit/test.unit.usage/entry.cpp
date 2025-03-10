/* /////////////////////////////////////////////////////////////////////////
 * File:    test.unit.usage/entry.cpp
 *
 * Purpose: Unit-tests usage-width functionality
 *
 * Created: 3rd April 2014
 * Updated: 10th March 2025
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* /////////////////////////////////////
 * test component header file include(s)
 */

#include <clasp/clasp.h>

/* /////////////////////////////////////
 * general includes
 */

/* xTests header files */
#include <xtests/terse-api.h>
#include <xtests/util/temp_file.hpp>

/* STLSoft header files */
#include <platformstl/platformstl.h>
#include <platformstl/filesystem/file_lines.hpp>
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

    static void TEST_showBody_null_specifications();
    static void TEST_showBody_empty_specifications();
    static void TEST_showBody_single_flag();
    static void TEST_showBody_single_option();
    static void TEST_showBody_one_flag_one_option();
    static void TEST_showBody_one_flag_one_option_infinite_length();
    static void TEST_showBody_one_flag_one_option_zero_length();
    static void TEST_showBody_one_option_one_flag();
    static void TEST_showBody_single_flag_changing_positiveTabSizes();
    static void TEST_showBody_single_flag_changing_consoleWidths();

    static void TEST_clasp_showUsage_AND_clasp_show_usage_NORMAL_1_ZERO_TABS_AND_NO_BLANK_LINES();
    static void TEST_clasp_showUsage_AND_clasp_show_usage_NORMAL_1_neg2_TABS_AND_NO_BLANK_LINES();
} // anonymous namespace


/* /////////////////////////////////////////////////////////////////////////
 * main
 */

int main(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if (XTESTS_START_RUNNER("test.unit.usage", verbosity))
    {
        XTESTS_RUN_CASE(TEST_showBody_null_specifications);
        XTESTS_RUN_CASE(TEST_showBody_empty_specifications);
        XTESTS_RUN_CASE(TEST_showBody_single_flag);
        XTESTS_RUN_CASE(TEST_showBody_single_option);
        XTESTS_RUN_CASE(TEST_showBody_one_flag_one_option);
        XTESTS_RUN_CASE(TEST_showBody_one_flag_one_option_infinite_length);
        XTESTS_RUN_CASE(TEST_showBody_one_flag_one_option_zero_length);
        XTESTS_RUN_CASE(TEST_showBody_one_option_one_flag);
        XTESTS_RUN_CASE(TEST_showBody_single_flag_changing_positiveTabSizes);
        XTESTS_RUN_CASE(TEST_showBody_single_flag_changing_consoleWidths);

        XTESTS_RUN_CASE(TEST_clasp_showUsage_AND_clasp_show_usage_NORMAL_1_ZERO_TABS_AND_NO_BLANK_LINES);
        XTESTS_RUN_CASE(TEST_clasp_showUsage_AND_clasp_show_usage_NORMAL_1_neg2_TABS_AND_NO_BLANK_LINES);

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
    typedef std::string                                     string_t;
    typedef std::vector<string_t>                           strings_t;

    static
    strings_t
    get_body_lines(
        clasp_specification_t const specifications[]
    ,   int                         tabSize
    ,   int                         consoleWidth
    ,   int                         showBlanksBetweenItems
    )
    {
        using namespace ::xtests::cpp::util;

        temp_file   temp(temp_file::DeleteOnOpen | temp_file::DeleteOnClose);
        FILE* const stm = ::fopen(temp.c_str(), "w");

        if (NULL == stm)
        {
            throw std::runtime_error("could not open file");
        }
        else
        {
            stlsoft::scoped_handle<FILE*> scoper(stm, ::fclose);

            clasp_showBody(
                NULL
            ,   specifications
            ,   clasp_showBodyByFILE
            ,   stm
            ,   0
            ,   tabSize
            ,   consoleWidth
            ,   showBlanksBetweenItems
            );

            scoper.close();

            typedef platformstl::basic_file_lines<
                char
            ,   string_t
            >                                               file_lines_t;

            file_lines_t    file_lines(temp.c_str());
            strings_t       lines;

            lines.reserve(file_lines.size());

            for (file_lines_t::const_iterator i = file_lines.begin(); file_lines.end() != i; ++i)
            {
                lines.push_back(*i);
            }

            return lines;
        }
    }

    static
    strings_t
    get_showUsage_lines(
        clasp_specification_t const specifications[]
    ,   clasp_char_t const*         toolName
    ,   clasp_char_t const*         summary
    ,   clasp_char_t const*         copyright
    ,   clasp_char_t const*         description
    ,   clasp_char_t const*         usage
    ,   int                         major
    ,   int                         minor
    ,   int                         revision
    ,   int                         flags
    ,   int                         consoleWidth
    ,   int                         tabSize
    ,   int                         blanksBetweenItems
    )
    {
        using namespace ::xtests::cpp::util;

        temp_file   temp(temp_file::DeleteOnOpen | temp_file::DeleteOnClose);
        FILE* const stm = ::fopen(temp.c_str(), "w");

        if (NULL == stm)
        {
            throw std::runtime_error("could not open file");
        }
        else
        {
            stlsoft::scoped_handle<FILE*> scoper(stm, ::fclose);

            clasp_showUsage(
                NULL
            ,   specifications
            ,   toolName
            ,   summary
            ,   copyright
            ,   description
            ,   usage
            ,   major, minor, revision
            ,   clasp_showHeaderByFILE
            ,   clasp_showBodyByFILE
            ,   stm
            ,   flags
            ,   consoleWidth
            ,   tabSize
            ,   blanksBetweenItems
            );


            scoper.close();

            typedef platformstl::basic_file_lines<
                char
            ,   string_t
            >                                               file_lines_t;

            file_lines_t    file_lines(temp.c_str());
            strings_t       lines;

            lines.reserve(file_lines.size());

            for (file_lines_t::const_iterator i = file_lines.begin(); file_lines.end() != i; ++i)
            {
                lines.push_back(*i);
            }

            return lines;
        }
    }

    static
    strings_t
    get_show_usage_lines(
        clasp_specification_t const specifications[]
    ,   clasp_char_t const*         toolName
    ,   clasp_char_t const*         summary
    ,   clasp_char_t const*         copyright
    ,   clasp_char_t const*         description
    ,   clasp_char_t const*         usage
    ,   int                         major
    ,   int                         minor
    ,   int                         revision
    ,   int                         flags
    ,   int                         consoleWidth
    ,   int                         tabSize
    ,   int                         blanksBetweenItems
    )
    {
        using namespace ::xtests::cpp::util;

        temp_file   temp(temp_file::DeleteOnOpen | temp_file::DeleteOnClose);
        FILE* const stm = ::fopen(temp.c_str(), "w");

        if (NULL == stm)
        {
            throw std::runtime_error("could not open file");
        }
        else
        {
            stlsoft::scoped_handle<FILE*> scoper(stm, ::fclose);

            {
#if 0
#elif defined(__GNUC__)

# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#else
#endif

                {
                    clasp_show_usage(
                        NULL
                    ,   specifications
                    ,   toolName
                    ,   summary
                    ,   copyright
                    ,   description
                    ,   usage
                    ,   major, minor, revision
                    ,   clasp_show_header_by_FILE
                    ,   clasp_show_body_by_FILE
                    ,   stm
                    ,   flags
                    ,   consoleWidth
                    ,   tabSize
                    ,   blanksBetweenItems
                    );
                }

#if 0
#elif defined(__GNUC__)

# pragma GCC diagnostic pop
#else
#endif
                }



            scoper.close();

            typedef platformstl::basic_file_lines<
                char
            ,   string_t
            >                                               file_lines_t;

            file_lines_t    file_lines(temp.c_str());
            strings_t       lines;

            lines.reserve(file_lines.size());

            for (file_lines_t::const_iterator i = file_lines.begin(); file_lines.end() != i; ++i)
            {
                lines.push_back(*i);
            }

            return lines;
        }
    }


static void TEST_showBody_null_specifications()
{
    clasp_specification_t const* const specifications = NULL;
    int consoleWidth = 80;
    int tabSize = 8;
    int showBlanksBetweenItems = 0;

    strings_t lines = get_body_lines(specifications, consoleWidth, tabSize, showBlanksBetweenItems);

    XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(0u, lines.size()));
}

static void TEST_showBody_empty_specifications()
{
    clasp_specification_t const specifications[] =
    {
        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };
    int consoleWidth = 80;
    int tabSize = 8;
    int showBlanksBetweenItems = 0;

    strings_t lines = get_body_lines(specifications, consoleWidth, tabSize, showBlanksBetweenItems);

    XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(0u, lines.size()));
}

static void TEST_showBody_single_flag()
{
    clasp_specification_t const specifications[] =
    {
        CLASP_FLAG(NULL, "--flag1", "this is a flag"),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };
    int consoleWidth            =   80;
    int tabSize                 =   0;
    int showBlanksBetweenItems  =   0;

    strings_t lines = get_body_lines(specifications, consoleWidth, tabSize, showBlanksBetweenItems);

    XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(4u, lines.size()));
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Flags:", lines[0]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--flag1", lines[2]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("this is a flag", lines[3]);
}

static void TEST_showBody_single_option()
{
    clasp_specification_t const specifications[] =
    {
        CLASP_OPTION(NULL, "--option1", "this is an option", ""),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };
    int consoleWidth            =   80;
    int tabSize                 =   0;
    int showBlanksBetweenItems  =   0;

    strings_t lines = get_body_lines(specifications, consoleWidth, tabSize, showBlanksBetweenItems);

    XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(4u, lines.size()));
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Options:", lines[0]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--option1=<value>", lines[2]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("this is an option", lines[3]);
}

static void TEST_showBody_one_flag_one_option()
{
    clasp_specification_t const specifications[] =
    {
        CLASP_FLAG(NULL, "--flag1", "this is a flag"),
        CLASP_OPTION(NULL, "--option1", "this is an option", ""),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };
    int consoleWidth            =   80;
    int tabSize                 =   0;
    int showBlanksBetweenItems  =   0;

    strings_t lines = get_body_lines(specifications, consoleWidth, tabSize, showBlanksBetweenItems);

    XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(6u, lines.size()));
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Flags and options:", lines[0]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--flag1", lines[2]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("this is a flag", lines[3]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--option1=<value>", lines[4]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("this is an option", lines[5]);
}

static void TEST_showBody_one_flag_one_option_infinite_length()
{
    clasp_specification_t const specifications[] =
    {
        CLASP_FLAG(NULL, "--flag1", "this is a flag"),
        CLASP_OPTION(NULL, "--option1", "this is an option", ""),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };
    int consoleWidth            =   -1;
    int tabSize                 =   0;
    int showBlanksBetweenItems  =   0;

    strings_t lines = get_body_lines(specifications, consoleWidth, tabSize, showBlanksBetweenItems);

    XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(6u, lines.size()));
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Flags and options:", lines[0]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--flag1", lines[2]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("this is a flag", lines[3]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--option1=<value>", lines[4]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("this is an option", lines[5]);
}

static void TEST_showBody_one_flag_one_option_zero_length()
{
    clasp_specification_t const specifications[] =
    {
        CLASP_FLAG(NULL, "--flag1", "this is a flag"),
        CLASP_OPTION(NULL, "--option1", "this is an option", ""),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };
    int consoleWidth            =   0;
    int tabSize                 =   0;
    int showBlanksBetweenItems  =   0;

    strings_t lines = get_body_lines(specifications, consoleWidth, tabSize, showBlanksBetweenItems);

    XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(6u, lines.size()));
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Flags and options:", lines[0]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--flag1", lines[2]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("this is a flag", lines[3]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--option1=<value>", lines[4]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("this is an option", lines[5]);
}

static void TEST_showBody_one_option_one_flag()
{
    clasp_specification_t const specifications[] =
    {
        CLASP_OPTION(NULL, "--option1", "this is an option", ""),
        CLASP_FLAG(NULL, "--flag1", "this is a flag"),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };
    int consoleWidth            =   80;
    int tabSize                 =   0;
    int showBlanksBetweenItems  =   0;

    strings_t lines = get_body_lines(specifications, consoleWidth, tabSize, showBlanksBetweenItems);

    XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(6u, lines.size()));
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Flags and options:", lines[0]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--option1=<value>", lines[2]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("this is an option", lines[3]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--flag1", lines[4]);
    XTESTS_TEST_MULTIBYTE_STRING_EQUAL("this is a flag", lines[5]);
}

static void TEST_showBody_single_flag_changing_positiveTabSizes()
{
    clasp_specification_t const specifications[] =
    {
        CLASP_FLAG(NULL, "--flag1", "this is a flag"),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };
    int consoleWidth            =   80;
    int tabSize                 =   0;
    int showBlanksBetweenItems  =   0;

    {
        strings_t lines = get_body_lines(specifications, consoleWidth, tabSize, showBlanksBetweenItems);

        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(4u, lines.size()));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Flags:", lines[0]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("--flag1", lines[2]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("this is a flag", lines[3]);
    }

    for (tabSize = 1; 34 != tabSize; ++tabSize)
    {
        strings_t lines = get_body_lines(specifications, consoleWidth, tabSize, showBlanksBetweenItems);

        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(4u, lines.size()));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Flags:", lines[0]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t--flag1", lines[2]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tthis is a flag", lines[3]);
    }
    for (tabSize = 34; 36 != tabSize; ++tabSize)
    {
        strings_t lines = get_body_lines(specifications, consoleWidth, tabSize, showBlanksBetweenItems);

        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(5u, lines.size()));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Flags:", lines[0]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t--flag1", lines[2]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tthis is a", lines[3]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tflag", lines[4]);
    }
    for (tabSize = 36; 37 != tabSize; ++tabSize)
    {
        strings_t lines = get_body_lines(specifications, consoleWidth, tabSize, showBlanksBetweenItems);

        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(5u, lines.size()));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Flags:", lines[0]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t--flag1", lines[2]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tthis is", lines[3]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\ta flag", lines[4]);
    }
    for (tabSize = 37; 38 != tabSize; ++tabSize)
    {
        strings_t lines = get_body_lines(specifications, consoleWidth, tabSize, showBlanksBetweenItems);

        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(6u, lines.size()));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Flags:", lines[0]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t--flag1", lines[2]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tthis", lines[3]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tis a", lines[4]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tflag", lines[5]);
    }
    for (tabSize = 38; 80 != tabSize; ++tabSize)
    {
        strings_t lines = get_body_lines(specifications, consoleWidth, tabSize, showBlanksBetweenItems);

        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(7u, lines.size()));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Flags:", lines[0]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t--flag1", lines[2]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tthis", lines[3]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tis", lines[4]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\ta", lines[5]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("\t\tflag", lines[6]);
    }
}

static void TEST_showBody_single_flag_changing_consoleWidths()
{
    clasp_specification_t const specifications[] =
    {
        CLASP_FLAG(NULL, "--flag1", "this is a flag"),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };
    int consoleWidth;
    int tabSize                 =   -1;
    int showBlanksBetweenItems  =   0;

    for (consoleWidth = 16; consoleWidth != 1000; ++consoleWidth)
    {
        strings_t lines = get_body_lines(specifications, consoleWidth, tabSize, showBlanksBetweenItems);

        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(4u, lines.size()));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Flags:", lines[0]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL(" --flag1", lines[2]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("  this is a flag", lines[3]);
    }
    for (consoleWidth = 12; consoleWidth != 16; ++consoleWidth)
    {
        strings_t lines = get_body_lines(specifications, consoleWidth, tabSize, showBlanksBetweenItems);

        XTESTS_REQUIRE(XTESTS_TEST_INTEGER_EQUAL(5u, lines.size()));
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("Flags:", lines[0]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", lines[1]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL(" --flag1", lines[2]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("  this is a", lines[3]);
        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("  flag", lines[4]);
    }
}

static void TEST_clasp_showUsage_AND_clasp_show_usage_NORMAL_1_ZERO_TABS_AND_NO_BLANK_LINES()
{
    clasp_specification_t const specifications[] =
    {
        CLASP_FLAG(NULL, "--flag1", "this is a flag"),
        CLASP_OPTION(NULL, "--option1", "this is an option", ""),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };
    clasp_char_t const* const   toolName            =   "myapp";
    clasp_char_t const* const   summary             =   "My tools";
    clasp_char_t const* const   copyright           =   "Copyright (c) Me! 2025";
    clasp_char_t const* const   description         =   "This app does things";
    clasp_char_t const* const   usage               =   "USAGE: myapp [ ... flags / options ...] <value-1> [ ... <value-N> ]";
    int const                   major               =   1;
    int const                   minor               =   2;
    int const                   revision            =   3;
    int const                   flags               =   0;
    int const                   consoleWidth        =   2000;
    int const                   tabSize             =   0;
    int const                   blanksBetweenItems  =   0;

    // `clasp_showUsage()`
    {
        strings_t lines = get_showUsage_lines(
            specifications
        ,   toolName
        ,   summary
        ,   copyright
        ,   description
        ,   usage
        ,   major
        ,   minor
        ,   revision
        ,   flags
        ,   consoleWidth
        ,   tabSize
        ,   blanksBetweenItems
        );

        REQUIRE(TEST_INTEGER_EQUAL(13u, lines.size()));
        TEST_MS_EQ("My tools", lines[0]);
        TEST_MS_EQ("myapp version 1.2.3.0", lines[1]);
        TEST_MS_EQ("Copyright (c) Me! 2025", lines[2]);
        TEST_MS_EQ("This app does things", lines[3]);
        TEST_MS_EQ("", lines[4]);
        TEST_MS_EQ("USAGE: myapp [ ... flags / options ...] <value-1> [ ... <value-N> ]", lines[5]);
        TEST_MS_EQ("", lines[6]);
        TEST_MS_EQ("Flags and options:", lines[7]);
        TEST_MS_EQ("", lines[8]);
        TEST_MS_EQ("--flag1", lines[9]);
        TEST_MS_EQ("this is a flag", lines[10]);
        TEST_MS_EQ("--option1=<value>", lines[11]);
        TEST_MS_EQ("this is an option", lines[12]);
    }

    // `get_show_usage_lines()`
    {
        strings_t lines = get_show_usage_lines(
            specifications
        ,   toolName
        ,   summary
        ,   copyright
        ,   description
        ,   usage
        ,   major
        ,   minor
        ,   revision
        ,   flags
        ,   consoleWidth
        ,   tabSize
        ,   blanksBetweenItems
        );

        REQUIRE(TEST_INTEGER_EQUAL(13u, lines.size()));
        TEST_MS_EQ("My tools", lines[0]);
        TEST_MS_EQ("myapp version 1.2.3.0", lines[1]);
        TEST_MS_EQ("Copyright (c) Me! 2025", lines[2]);
        TEST_MS_EQ("This app does things", lines[3]);
        TEST_MS_EQ("", lines[4]);
        TEST_MS_EQ("USAGE: myapp [ ... flags / options ...] <value-1> [ ... <value-N> ]", lines[5]);
        TEST_MS_EQ("", lines[6]);
        TEST_MS_EQ("Flags and options:", lines[7]);
        TEST_MS_EQ("", lines[8]);
        TEST_MS_EQ("--flag1", lines[9]);
        TEST_MS_EQ("this is a flag", lines[10]);
        TEST_MS_EQ("--option1=<value>", lines[11]);
        TEST_MS_EQ("this is an option", lines[12]);
    }
}

static void TEST_clasp_showUsage_AND_clasp_show_usage_NORMAL_1_neg2_TABS_AND_NO_BLANK_LINES()
{
    clasp_specification_t const specifications[] =
    {
        CLASP_FLAG(NULL, "--flag1", "this is a flag"),
        CLASP_OPTION(NULL, "--option1", "this is an option", ""),

        CLASP_SPECIFICATION_ARRAY_TERMINATOR
    };
    clasp_char_t const* const   toolName            =   "myapp";
    clasp_char_t const* const   summary             =   "My tools";
    clasp_char_t const* const   copyright           =   "Copyright (c) Me! 2025";
    clasp_char_t const* const   description         =   "This app does things";
    clasp_char_t const* const   usage               =   "USAGE: myapp [ ... flags / options ...] <value-1> [ ... <value-N> ]";
    int const                   major               =   1;
    int const                   minor               =   2;
    int const                   revision            =   3;
    int const                   flags               =   0;
    int const                   consoleWidth        =   2000;
    int const                   tabSize             =   -2;
    int const                   blanksBetweenItems  =   0;

    // `clasp_showUsage()`
    {
        strings_t lines = get_showUsage_lines(
            specifications
        ,   toolName
        ,   summary
        ,   copyright
        ,   description
        ,   usage
        ,   major
        ,   minor
        ,   revision
        ,   flags
        ,   consoleWidth
        ,   tabSize
        ,   blanksBetweenItems
        );

        REQUIRE(TEST_INTEGER_EQUAL(13u, lines.size()));
        TEST_MS_EQ("My tools", lines[0]);
        TEST_MS_EQ("myapp version 1.2.3.0", lines[1]);
        TEST_MS_EQ("Copyright (c) Me! 2025", lines[2]);
        TEST_MS_EQ("This app does things", lines[3]);
        TEST_MS_EQ("", lines[4]);
        TEST_MS_EQ("USAGE: myapp [ ... flags / options ...] <value-1> [ ... <value-N> ]", lines[5]);
        TEST_MS_EQ("", lines[6]);
        TEST_MS_EQ("Flags and options:", lines[7]);
        TEST_MS_EQ("", lines[8]);
        TEST_MS_EQ("  --flag1", lines[9]);
        TEST_MS_EQ("    this is a flag", lines[10]);
        TEST_MS_EQ("  --option1=<value>", lines[11]);
        TEST_MS_EQ("    this is an option", lines[12]);
    }

    // `get_show_usage_lines()`
    {
        strings_t lines = get_show_usage_lines(
            specifications
        ,   toolName
        ,   summary
        ,   copyright
        ,   description
        ,   usage
        ,   major
        ,   minor
        ,   revision
        ,   flags
        ,   consoleWidth
        ,   tabSize
        ,   blanksBetweenItems
        );

        REQUIRE(TEST_INTEGER_EQUAL(13u, lines.size()));
        TEST_MS_EQ("My tools", lines[0]);
        TEST_MS_EQ("myapp version 1.2.3.0", lines[1]);
        TEST_MS_EQ("Copyright (c) Me! 2025", lines[2]);
        TEST_MS_EQ("This app does things", lines[3]);
        TEST_MS_EQ("", lines[4]);
        TEST_MS_EQ("USAGE: myapp [ ... flags / options ...] <value-1> [ ... <value-N> ]", lines[5]);
        TEST_MS_EQ("", lines[6]);
        TEST_MS_EQ("Flags and options:", lines[7]);
        TEST_MS_EQ("", lines[8]);
        TEST_MS_EQ("  --flag1", lines[9]);
        TEST_MS_EQ("    this is a flag", lines[10]);
        TEST_MS_EQ("  --option1=<value>", lines[11]);
        TEST_MS_EQ("    this is an option", lines[12]);
    }
}
} // anonymous namespace


/* ///////////////////////////// end of file //////////////////////////// */

