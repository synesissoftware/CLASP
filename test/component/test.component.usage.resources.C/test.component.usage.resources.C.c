/* /////////////////////////////////////////////////////////////////////////
 * File:        test.component.usage.resources.C.c
 *
 * Purpose:     Implementation file for the test.component.usage.resources project.
 *
 * Created:     7th March 2012
 * Updated:     17th October 2019
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2012-2019, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////
 * preprocessor feature control and compatibility
 */

#ifndef _WIN32
# error This may only be compiled for Windows operating systems
#endif

#define _CRT_SECURE_NO_WARNINGS

/* /////////////////////////////////////////////////////////////////////////
 * test component header file include(s)
 */

#include <systemtools/clasp/clasp.h>

#include "resource.h"

/* /////////////////////////////////////////////////////////////////////////
 * includes
 */

/* SystemTools::CLASP header files */
#include <systemtools/clasp/clasp.h>

/* xTests header files */
#include <xtests/xtests.h>

/* STLSoft header files */
#include <stlsoft/string/string_slice.h>
#include <stlsoft/memory/auto_buffer.h>

/* Standard C header files */
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
# include <crtdbg.h>
#endif /* _MSC_VER */

/* /////////////////////////////////////////////////////////////////////////
 * forward declarations
 */

static void test_header_with_LLLLL(void);
static void test_header_with_RRRRR(void);
static void test_header_with_RLLLL(void);
static void test_header_with_LRLLL(void);
static void test_header_with_LLLRL(void);
static void test_header_with_rLLLL(void);
static void test_header_with_LLrLL(void);
static void test_header_with_LLLLr(void);
static void test_header_with_rRRRR(void);
static void test_header_with_RrRRR(void);
static void test_header_with_RRrRR(void);
static void test_header_with_RRRrR(void);
static void test_header_with_RRRRr(void);
static void test_1_9(void);
static void test_body_1(void);
static void test_body_2(void);
static void test_body_3(void);
static void test_body_4(void);
static void test_body_5(void);
static void test_1_15(void);
static void test_1_16(void);
static void test_expanded_usage_1(void);
static void test_expanded_usage_2(void);
static void test_1_19(void);
static void test_1_20(void);
static void test_1_21(void);
static void test_1_22(void);
static void test_1_23(void);
static void test_1_24(void);
static void test_1_25(void);
static void test_1_26(void);
static void test_1_27(void);
static void test_1_28(void);
static void test_1_29(void);
static void test_1_30(void);
static void test_1_31(void);
static void test_1_32(void);
static void test_1_33(void);
static void test_1_34(void);
static void test_1_35(void);
static void test_1_36(void);
static void test_1_37(void);
static void test_1_38(void);
static void test_1_39(void);
static void test_1_40(void);
static void test_1_41(void);
static void test_1_42(void);
static void test_1_43(void);
static void test_1_44(void);
static void test_1_45(void);
static void test_1_46(void);
static void test_1_47(void);
static void test_1_48(void);
static void test_1_49(void);

static int setup(void* param);
static int teardown(void* param);
static void* setupParam = NULL;

/* /////////////////////////////////////////////////////////////////////////
 * main
 */

static
int main_(int argc, char **argv);

int main(int argc, char **argv)
{
    int r;

#ifdef _MSC_VER
    _CrtMemState    memState;

# ifdef _DEBUG
    _CrtMemCheckpoint(&memState);
# else /* ? _DEBUG */
    STLSOFT_SUPPRESS_UNUSED(memState);
# endif /* _DEBUG */
#endif /* _MSC_VER */

    r = main_(argc, argv);

#ifdef _MSC_VER
    _CrtMemDumpAllObjectsSince(&memState);
#endif /* _MSC_VER */

    return r;
}

int main_(int argc, char **argv)
{
    int retCode = EXIT_SUCCESS;
    int verbosity = 2;

    XTESTS_COMMANDLINE_PARSEVERBOSITY(argc, argv, &verbosity);

    if(XTESTS_START_RUNNER_WITH_SETUP_FNS("test.component.usage.resources.C", verbosity, setup, teardown, setupParam))
    {
        XTESTS_RUN_CASE(test_header_with_LLLLL);
        XTESTS_RUN_CASE(test_header_with_RRRRR);
        XTESTS_RUN_CASE(test_header_with_RLLLL);
        XTESTS_RUN_CASE(test_header_with_LRLLL);
        XTESTS_RUN_CASE(test_header_with_LLLRL);
        XTESTS_RUN_CASE(test_header_with_rLLLL);
        XTESTS_RUN_CASE(test_header_with_LLrLL);
        XTESTS_RUN_CASE(test_header_with_LLLLr);
        XTESTS_RUN_CASE(test_header_with_rRRRR);
        XTESTS_RUN_CASE(test_header_with_RrRRR);
        XTESTS_RUN_CASE(test_header_with_RRrRR);
        XTESTS_RUN_CASE(test_header_with_RRRrR);
        XTESTS_RUN_CASE(test_header_with_RRRRr);
        XTESTS_RUN_CASE(test_1_9);
        XTESTS_RUN_CASE(test_body_1);
        XTESTS_RUN_CASE(test_body_2);
        XTESTS_RUN_CASE(test_body_3);
        XTESTS_RUN_CASE(test_body_4);
        XTESTS_RUN_CASE(test_body_5);
        XTESTS_RUN_CASE(test_1_15);
        XTESTS_RUN_CASE(test_1_16);
        XTESTS_RUN_CASE(test_expanded_usage_1);
        XTESTS_RUN_CASE(test_expanded_usage_2);
        XTESTS_RUN_CASE(test_1_19);
        XTESTS_RUN_CASE(test_1_20);
        XTESTS_RUN_CASE(test_1_21);
        XTESTS_RUN_CASE(test_1_22);
        XTESTS_RUN_CASE(test_1_23);
        XTESTS_RUN_CASE(test_1_24);
        XTESTS_RUN_CASE(test_1_25);
        XTESTS_RUN_CASE(test_1_26);
        XTESTS_RUN_CASE(test_1_27);
        XTESTS_RUN_CASE(test_1_28);
        XTESTS_RUN_CASE(test_1_29);
        XTESTS_RUN_CASE(test_1_30);
        XTESTS_RUN_CASE(test_1_31);
        XTESTS_RUN_CASE(test_1_32);
        XTESTS_RUN_CASE(test_1_33);
        XTESTS_RUN_CASE(test_1_34);
        XTESTS_RUN_CASE(test_1_35);
        XTESTS_RUN_CASE(test_1_36);
        XTESTS_RUN_CASE(test_1_37);
        XTESTS_RUN_CASE(test_1_38);
        XTESTS_RUN_CASE(test_1_39);
        XTESTS_RUN_CASE(test_1_40);
        XTESTS_RUN_CASE(test_1_41);
        XTESTS_RUN_CASE(test_1_42);
        XTESTS_RUN_CASE(test_1_43);
        XTESTS_RUN_CASE(test_1_44);
        XTESTS_RUN_CASE(test_1_45);
        XTESTS_RUN_CASE(test_1_46);
        XTESTS_RUN_CASE(test_1_47);
        XTESTS_RUN_CASE(test_1_48);
        XTESTS_RUN_CASE(test_1_49);

        XTESTS_PRINT_RESULTS();

        XTESTS_END_RUNNER_UPDATE_EXITCODE(&retCode);
    }

    return retCode;
}

/* /////////////////////////////////////////////////////////////////////////
 * test function implementations
 */

static int setup(void* param)
{
    ((void)param); /* TODO: Use the parameter, if you need to */

    return 0; /* Change to !0 to fail initialisation */
}

static int teardown(void* param)
{
    ((void)param); /* TODO: Use the parameter, if you need to */

    return 0; /* Currently ignored by xTests */
}


static
void
clasp_showHeaderIntoMemory(
    clasp_arguments_t const*    args
,   clasp_usageinfo_t const*    info
,   clasp_alias_t const*        aliases
)
{
    stlsoft_C_string_slice_a_t* const   sl  =   info->param;
    char* const                         p   =   (char*)sl->ptr;

    STLSOFT_SUPPRESS_UNUSED(args);
    STLSOFT_SUPPRESS_UNUSED(aliases);

    sprintf(
            p
        ,   "T=%s; S=%s; C=%s; D=%s; U=%s; v=%d.%d.%02d.%04d"
        ,   info->toolName
        ,   info->summary
        ,   info->copyright
        ,   info->description
        ,   info->usage
        ,   info->version.major
        ,   info->version.minor
        ,   info->version.revision
        ,   info->version.build
        );
}

static
void
clasp_showBodyIntoMemory(
    clasp_arguments_t const*    args
,   clasp_usageinfo_t const*    info
,   clasp_alias_t const*        aliases
)
{
    stlsoft_C_string_slice_a_t* const   sl          =   info->param;
    char*                               p           =   (char*)sl->ptr;
    size_t                              n;
    int                                 tabWidth    =   (info->assumedTabWidth < 0) ? -info->assumedTabWidth : 1;
    char const*                         ws          =   (info->assumedTabWidth < 0) ? "                            " : "\t";

    STLSOFT_SUPPRESS_UNUSED(args);

    for(n = 0; NULL != aliases->mappedArgument; ++aliases)
    {
        if( NULL != aliases->name &&
            '\0' != aliases->name[0])
        {
            int n = sprintf(p, "%.*s%s\n", tabWidth, ws, aliases->name);

            p += n;
        }

        if( NULL != aliases->mappedArgument &&
            '\0' != aliases->mappedArgument[0])
        {
            int n = sprintf(p, "%.*s%s\n", tabWidth, ws, aliases->mappedArgument);

            p += n;
        }

        if( NULL != aliases->help &&
            '\0' != aliases->help[0])
        {
            int n = sprintf(p, "%.*s%s\n", 2 * tabWidth, ws, aliases->help);

            p += n;
        }
    }
}

static void test_header_with_LLLLL()
{
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000];
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showHeader(
                    args
                ,   NULL
                ,   "toolname"
                ,   "summary"
                ,   "copyright"
                ,   "description"
                ,   "usage"
                ,   0, 1, 1
                ,   clasp_showHeaderIntoMemory
                ,   &sl
                ,   0
                ,   76
                ,   -4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("T=toolname; S=summary; C=copyright; D=description; U=usage; v=0.1.01.0000", buff);
    }
}

static void test_header_with_RRRRR()
{
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000];
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showHeader(
                    args
                ,   NULL
                ,   "@"STLSOFT_STRINGIZE(IDS_TOOLNAME)"@"
                ,   "@"STLSOFT_STRINGIZE(IDS_SUMMARY)"@"
                ,   "@"STLSOFT_STRINGIZE(IDS_COPYRIGHT)"@"
                ,   "@"STLSOFT_STRINGIZE(IDS_DESCRIPTION)"@"
                ,   "@"STLSOFT_STRINGIZE(IDS_USAGE)"@"
                ,   0, 1, 1
                ,   clasp_showHeaderIntoMemory
                ,   &sl
                ,   0
                ,   76
                ,   -4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("T=TOOLNAME; S=SUMMARY; C=COPYRIGHT; D=DESCRIPTION; U=USAGE; v=0.1.01.0000", buff);
    }
}

static void test_header_with_RLLLL()
{
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000];
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showHeader(
                    args
                ,   NULL
                ,   "@"STLSOFT_STRINGIZE(IDS_TOOLNAME)"@"
                ,   "summary"
                ,   "copyright"
                ,   "description"
                ,   "usage"
                ,   0, 1, 1
                ,   clasp_showHeaderIntoMemory
                ,   &sl
                ,   0
                ,   76
                ,   -4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("T=TOOLNAME; S=summary; C=copyright; D=description; U=usage; v=0.1.01.0000", buff);
    }
}

static void test_header_with_LRLLL()
{
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000];
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showHeader(
                    args
                ,   NULL
                ,   "toolname"
                ,   "@"STLSOFT_STRINGIZE(IDS_SUMMARY)"@"
                ,   "copyright"
                ,   "description"
                ,   "usage"
                ,   0, 1, 1
                ,   clasp_showHeaderIntoMemory
                ,   &sl
                ,   0
                ,   76
                ,   -4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("T=toolname; S=SUMMARY; C=copyright; D=description; U=usage; v=0.1.01.0000", buff);
    }
}

static void test_header_with_LLLRL()
{
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000];
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showHeader(
                    args
                ,   NULL
                ,   "toolname"
                ,   "summary"
                ,   "copyright"
                ,   "@"STLSOFT_STRINGIZE(IDS_DESCRIPTION)"@"
                ,   "usage"
                ,   0, 1, 1
                ,   clasp_showHeaderIntoMemory
                ,   &sl
                ,   0
                ,   76
                ,   -4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("T=toolname; S=summary; C=copyright; D=DESCRIPTION; U=usage; v=0.1.01.0000", buff);
    }
}

static void test_header_with_rLLLL()
{
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000];
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showHeader(
                    args
                ,   NULL
                ,   "@wrong@"
                ,   "summary"
                ,   "copyright"
                ,   "description"
                ,   "usage"
                ,   0, 1, 1
                ,   clasp_showHeaderIntoMemory
                ,   &sl
                ,   0
                ,   76
                ,   -4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("T=@unknown-identifier@; S=summary; C=copyright; D=description; U=usage; v=0.1.01.0000", buff);
    }
}

static void test_header_with_LLrLL()
{
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000];
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showHeader(
                    args
                ,   NULL
                ,   "toolname"
                ,   "summary"
                ,   "@wrong@"
                ,   "description"
                ,   "usage"
                ,   0, 1, 1
                ,   clasp_showHeaderIntoMemory
                ,   &sl
                ,   0
                ,   76
                ,   -4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("T=toolname; S=summary; C=@unknown-identifier@; D=description; U=usage; v=0.1.01.0000", buff);
    }
}

static void test_header_with_LLLLr()
{
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000];
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showHeader(
                    args
                ,   NULL
                ,   "toolname"
                ,   "summary"
                ,   "copyright"
                ,   "description"
                ,   "@wrong@"
                ,   0, 1, 1
                ,   clasp_showHeaderIntoMemory
                ,   &sl
                ,   0
                ,   76
                ,   -4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("T=toolname; S=summary; C=copyright; D=description; U=@unknown-identifier@; v=0.1.01.0000", buff);
    }
}

static void test_header_with_rRRRR(void)
{
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000];
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showHeader(
                    args
                ,   NULL
                ,   "@wrong@"
                ,   "@"STLSOFT_STRINGIZE(IDS_SUMMARY)"@"
                ,   "@"STLSOFT_STRINGIZE(IDS_COPYRIGHT)"@"
                ,   "@"STLSOFT_STRINGIZE(IDS_DESCRIPTION)"@"
                ,   "@"STLSOFT_STRINGIZE(IDS_USAGE)"@"
                ,   0, 1, 1
                ,   clasp_showHeaderIntoMemory
                ,   &sl
                ,   0
                ,   76
                ,   -4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("T=@unknown-identifier@; S=SUMMARY; C=COPYRIGHT; D=DESCRIPTION; U=USAGE; v=0.1.01.0000", buff);
    }
}

static void test_header_with_RrRRR(void)
{
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000];
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showHeader(
                    args
                ,   NULL
                ,   "@"STLSOFT_STRINGIZE(IDS_TOOLNAME)"@"
                ,   "@wrong@"
                ,   "@"STLSOFT_STRINGIZE(IDS_COPYRIGHT)"@"
                ,   "@"STLSOFT_STRINGIZE(IDS_DESCRIPTION)"@"
                ,   "@"STLSOFT_STRINGIZE(IDS_USAGE)"@"
                ,   0, 1, 1
                ,   clasp_showHeaderIntoMemory
                ,   &sl
                ,   0
                ,   76
                ,   -4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("T=TOOLNAME; S=@unknown-identifier@; C=COPYRIGHT; D=DESCRIPTION; U=USAGE; v=0.1.01.0000", buff);
    }
}

static void test_header_with_RRrRR(void)
{
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000];
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showHeader(
                    args
                ,   NULL
                ,   "@"STLSOFT_STRINGIZE(IDS_TOOLNAME)"@"
                ,   "@"STLSOFT_STRINGIZE(IDS_SUMMARY)"@"
                ,   "@wrong@"
                ,   "@"STLSOFT_STRINGIZE(IDS_DESCRIPTION)"@"
                ,   "@"STLSOFT_STRINGIZE(IDS_USAGE)"@"
                ,   0, 1, 1
                ,   clasp_showHeaderIntoMemory
                ,   &sl
                ,   0
                ,   76
                ,   -4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("T=TOOLNAME; S=SUMMARY; C=@unknown-identifier@; D=DESCRIPTION; U=USAGE; v=0.1.01.0000", buff);
    }
}

static void test_header_with_RRRrR(void)
{
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000];
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showHeader(
                    args
                ,   NULL
                ,   "@"STLSOFT_STRINGIZE(IDS_TOOLNAME)"@"
                ,   "@"STLSOFT_STRINGIZE(IDS_SUMMARY)"@"
                ,   "@"STLSOFT_STRINGIZE(IDS_COPYRIGHT)"@"
                ,   "@wrong@"
                ,   "@"STLSOFT_STRINGIZE(IDS_USAGE)"@"
                ,   0, 1, 1
                ,   clasp_showHeaderIntoMemory
                ,   &sl
                ,   0
                ,   76
                ,   -4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("T=TOOLNAME; S=SUMMARY; C=COPYRIGHT; D=@unknown-identifier@; U=USAGE; v=0.1.01.0000", buff);
    }
}

static void test_header_with_RRRRr(void)
{
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000];
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showHeader(
                    args
                ,   NULL
                ,   "@"STLSOFT_STRINGIZE(IDS_TOOLNAME)"@"
                ,   "@"STLSOFT_STRINGIZE(IDS_SUMMARY)"@"
                ,   "@"STLSOFT_STRINGIZE(IDS_COPYRIGHT)"@"
                ,   "@"STLSOFT_STRINGIZE(IDS_DESCRIPTION)"@"
                ,   "@wrong@"
                ,   0, 1, 1
                ,   clasp_showHeaderIntoMemory
                ,   &sl
                ,   0
                ,   76
                ,   -4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("T=TOOLNAME; S=SUMMARY; C=COPYRIGHT; D=DESCRIPTION; U=@unknown-identifier@; v=0.1.01.0000", buff);
    }
}

static void test_1_9()
{
}

static void test_body_1()
{
    clasp_alias_t const         aliases[] =
    {

        CLASP_ALIAS_ARRAY_TERMINATOR
    };
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000] = { 0 };
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showBody(
                    args
                ,   aliases
                ,   clasp_showBodyIntoMemory
                ,   &sl
                ,   0
                ,   100000
                ,   -4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("", buff);
    }
}

static void test_body_2()
{
    clasp_alias_t const         aliases[] =
    {
        CLASP_FLAG("-h", "--help", "shows this help and terminates"),

        CLASP_ALIAS_ARRAY_TERMINATOR
    };
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000] = { 0 };
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showBody(
                    args
                ,   aliases
                ,   clasp_showBodyIntoMemory
                ,   &sl
                ,   0
                ,   100000
                ,   -4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("    -h\n    --help\n        shows this help and terminates\n", buff);
    }
}

static void test_body_3()
{
    clasp_alias_t const         aliases[] =
    {
        CLASP_FLAG("-h", "--help", "@"STLSOFT_STRINGIZE(IDS_USAGE_HELP)"@"),

        CLASP_ALIAS_ARRAY_TERMINATOR
    };
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000] = { 0 };
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showBody(
                    args
                ,   aliases
                ,   clasp_showBodyIntoMemory
                ,   &sl
                ,   0
                ,   100000
                ,   -4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("    -h\n    --help\n        shows this help and terminates\n", buff);
    }
}

static void test_body_4()
{
    clasp_alias_t const         aliases[] =
    {
        CLASP_FLAG("-h", "--help", "@usage@"),
        CLASP_FLAG(NULL, "--version", "@"STLSOFT_STRINGIZE(IDS_USAGE_VERSION)"@"),

        CLASP_ALIAS_ARRAY_TERMINATOR
    };
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000] = { 0 };
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showBody(
                    args
                ,   aliases
                ,   clasp_showBodyIntoMemory
                ,   &sl
                ,   0
                ,   100000
                ,   -4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("    -h\n    --help\n        @unknown-identifier@\n    --version\n        shows version and terminates\n", buff);
    }
}

static void test_body_5()
{
    clasp_alias_t const         aliases[] =
    {
        CLASP_FLAG("-h", "--help", "@"STLSOFT_STRINGIZE(IDS_USAGE_HELP)"@"),
        CLASP_FLAG(NULL, "--version", "@usage@"),

        CLASP_ALIAS_ARRAY_TERMINATOR
    };
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000] = { 0 };
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showBody(
                    args
                ,   aliases
                ,   clasp_showBodyIntoMemory
                ,   &sl
                ,   0
                ,   100000
                ,   -4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("    -h\n    --help\n        shows this help and terminates\n    --version\n        @unknown-identifier@\n", buff);
    }
}

static void test_1_15()
{
}

static void test_1_16()
{
}

static void test_expanded_usage_1()
{
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000];
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showHeader(
                    args
                ,   NULL
                ,   "toolname"
                ,   "summary"
                ,   "copyright"
                ,   "description"
                ,   "@"STLSOFT_STRINGIZE(IDS_USAGE_X)"@"
                ,   0, 1, 1
                ,   clasp_showHeaderIntoMemory
                ,   &sl
                ,   0
                ,   76
                ,   -4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("T=toolname; S=summary; C=copyright; D=description; U=USAGE:\n\n    abc\n\n    def\n; v=0.1.01.0000", buff);
    }
}

static void test_expanded_usage_2()
{
    char* const                 argv[]  =
    {
        "program",

        NULL
    };
    int const                   argc    =   STLSOFT_NUM_ELEMENTS(argv) - 1;
    clasp_arguments_t const*    args;
    int const                   cr      =   clasp_parseArguments(0, argc, argv, NULL, NULL, &args);

    if(0 != cr)
    {
        XTESTS_TEST_FAIL_WITH_QUALIFIER("failed to initialise CLASP", strerror(cr));
    }
    else
    {
        char                        buff[2000];
        stlsoft_C_string_slice_a_t  sl = { STLSOFT_NUM_ELEMENTS(buff), &buff[0] };
        int const                   r =
            clasp_showHeader(
                    args
                ,   NULL
                ,   "toolname"
                ,   "summary"
                ,   "copyright"
                ,   "description"
                ,   "@"STLSOFT_STRINGIZE(IDS_USAGE_X)"@"
                ,   0, 1, 1
                ,   clasp_showHeaderIntoMemory
                ,   &sl
                ,   0
                ,   76
                ,   4
                ,   0
                );

        XTESTS_TEST_INTEGER_EQUAL(0, r);

        clasp_releaseArguments(args);

        XTESTS_TEST_MULTIBYTE_STRING_EQUAL("T=toolname; S=summary; C=copyright; D=description; U=USAGE:\n\n\tabc\n\n\tdef\n; v=0.1.01.0000", buff);
    }
}

static void test_1_19()
{
}

static void test_1_20()
{
}

static void test_1_21()
{
}

static void test_1_22()
{
}

static void test_1_23()
{
}

static void test_1_24()
{
}

static void test_1_25()
{
}

static void test_1_26()
{
}

static void test_1_27()
{
}

static void test_1_28()
{
}

static void test_1_29()
{
}

static void test_1_30()
{
}

static void test_1_31()
{
}

static void test_1_32()
{
}

static void test_1_33()
{
}

static void test_1_34()
{
}

static void test_1_35()
{
}

static void test_1_36()
{
}

static void test_1_37()
{
}

static void test_1_38()
{
}

static void test_1_39()
{
}

static void test_1_40()
{
}

static void test_1_41()
{
}

static void test_1_42()
{
}

static void test_1_43()
{
}

static void test_1_44()
{
}

static void test_1_45()
{
}

static void test_1_46()
{
}

static void test_1_47()
{
}

static void test_1_48()
{
}

static void test_1_49()
{
}

/* ///////////////////////////// end of file //////////////////////////// */

