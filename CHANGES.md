# CLASP - CHANGES list <!-- omit in toc -->

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




0.14.0-beta1
commit da33482fc7f4e176002a42945e8fa90b8ae78402
Author: Matt Wilson <matthew@synesis.com.au>
Date:   Fri Feb 2 19:29:24 2024 +1100

    Merged '0.14-cmake' into 'dev'

    Squashed commit of the following:

    commit da9d663e6b175b3e72b359fee1fe5f38d5de767b
    Author: Matt Wilson <matthew@synesis.com.au>
    Date:   Fri Feb 2 19:20:37 2024 +1100

        ~ boilerplate

    commit ffc349ff20526f5437e49900c61126b29047a7e2
    Author: Matt Wilson <matthew@synesis.com.au>
    Date:   Fri Feb 2 18:09:36 2024 +1100

        CMake and C++14 support:
        + C++11, C++14, C++17 support;
        + all example and test CMake projects;
        + project boilerplate;
        ~ Visual C++ 16 compatibility;
        ~ defect fix, allowing null specifications;
        ~ test.unit.usage_width now compatible with UNIX (as well as Windows), by using `platformstl::basic_file_lines<>` class template

    commit 9b6a14abf9d31e13ed092ed738aa91dd357f22bc
    Author: Matt Wilson <matthew@synesis.com.au>
    Date:   Thu Feb 1 19:18:13 2024 +1100

        ~ updated boilerplate scripts

    commit 1f068a73770ccb2e9cd46d3d83a8dc5dd0b22526
    Author: Matt Wilson <matthew@synesis.com.au>
    Date:   Wed Jan 17 20:31:47 2024 +1100

        - removed old CMake support files

    commit 269c1128c73fde69c8f7256ce043e37e9d31b245
    Author: mwsis <152443343+mwsis@users.noreply.github.com>
    Date:   Sun Dec 31 16:02:36 2023 +1100

        ~ improved CMake handling (#5)

    commit 69ccc7d2cb1a98f1977d4f118ac762fb4ad11d55
    Author: Matt Wilson <matthew@synesis.com.au>
    Date:   Sun Dec 31 15:19:45 2023 +1100

        Merge '0.14' into '0.14-cmake'

        Squashed commit of the following:

        commit 3f8b4e4b8d783efb4e81aba1b8476600ea62a696
        Author: mwsis <152443343+mwsis@users.noreply.github.com>
        Date:   Sun Dec 31 15:17:33 2023 +1100

            0.14 foss changes (#4)

            * ~ ignores

            * ~ foss changes

            * ~ license

            * ~ whitespace

    commit c4e0803eeb564865e1452699d27437a31d241783
    Author: Matt Wilson <matthew@synesis.com.au>
    Date:   Mon Mar 29 18:16:57 2021 +1100

        ~ GCC compatibility

    commit 50b9f2a150883f018977e85c89ad67400f17abaf
    Author: Matt <matthew@synesis.com.au>
    Date:   Tue Mar 23 14:14:48 2021 +1100

        ~ tidying

    commit 5a2a65b1ae8d0fc69ba5b7a8fdae1019e73889bc
    Merge: 7e97660 831e68f
    Author: Matt <matthew@synesis.com.au>
    Date:   Mon Mar 22 14:28:32 2021 +1100

        merge 0.14

    commit 7e976603d91a060295cb42698e640d48c4786a56
    Author: Matt <matthew@synesis.com.au>
    Date:   Mon Mar 22 14:14:22 2021 +1100

        + added 'install' macro to top-level

    commit 7f3f1bfff88e6eedf0fbe2b602143124a1a6d693
    Author: Matt <matthew@synesis.com.au>
    Date:   Tue Mar 16 13:23:00 2021 +1100

        ~ minor mods

    commit b26fdbdabf1a59526d87e09cad28802359a2fe48
    Merge: 8d10136 5a8a480
    Author: Matt <matthew@synesis.com.au>
    Date:   Tue Mar 16 13:22:16 2021 +1100

        Merge tag '0.14.0-alpha5' into 0.14-cmake

    commit 831e68f241ac1944f8b7ab3df9220fe98a8d5971
    Merge: 5a8a480 c2e1db5
    Author: synesissoftware <matthew@synesis.com.au>
    Date:   Tue Feb 16 10:52:03 2021 +1100

        Merge pull request #1 from stlsoft/0.14

        ~ fix

    commit c2e1db50ef2fad6461b741e775e3ada15c841fd2
    Author: Matt Wilson <stlsoft@gmail.com>
    Date:   Tue Feb 16 10:30:45 2021 +1100

        ~ fix

    commit 5a8a4807b74f3c600dfcc324a52fc9c28fef0ad1
    Author: Matt <Wilson>
    Date:   Tue Feb 16 10:10:05 2021 +1100

        + added clasp_getSpecifications()

    commit 8d10136b1a106d54337a4521788370456bbcf7d5
    Merge: 6cfe4d0 8c0bff3
    Author: Matt <Wilson>
    Date:   Sun Jan 10 09:33:42 2021 +1100

        Merge branch '0.14' into 0.14-cmake

    commit 8c0bff35a3cf7846064a45c064f39d981c307366
    Author: Matt <Wilson>
    Date:   Sun Jan 10 09:33:16 2021 +1100

        ~ platform neutral allowed

    commit 6cfe4d0847df3ba198a7760b2eaed3214554b60f
    Merge: 02f3f8c 8b75c0f
    Author: Matt <Wilson>
    Date:   Sun Jan 10 09:13:04 2021 +1100

        Merge branch '0.14' into 0.14-cmake

    commit 8b75c0feba78b261d03e51b2d1293ca74b065448
    Merge: d68ddbb ffc96ab
    Author: Matt <Wilson>
    Date:   Sun Jan 10 09:12:55 2021 +1100

        merge

    commit 02f3f8c0593d698076a98716e5ba53ddd4aecd7f
    Merge: 558f068 d68ddbb
    Author: Matt <Wilson>
    Date:   Sun Jan 10 09:03:57 2021 +1100

        Merge branch '0.14' into 0.14-cmake

    commit d68ddbbae362ae5ee2cb69ea2ad1ec9cdaaddd4b
    Author: Matt <Wilson>
    Date:   Sun Jan 10 09:03:44 2021 +1100

        - removal of dead code; ~ changed from deprecated to non-deprecated API functions

    commit 558f068e699d6cc0863c5b63b9f86356fb2931e6
    Merge: 5e2a46b f6280d6
    Author: Matt <Wilson>
    Date:   Sun Jan 10 08:56:27 2021 +1100

        merge

    commit f6280d6231fa36d00c8a0a8fd2912d0be4d52354
    Author: Matt <Wilson>
    Date:   Sun Jan 10 08:52:24 2021 +1100

        ~ GCC warnings

    commit c6a2115d8990a54246465e2f290eb2e86aa9c892
    Author: Matt <Wilson>
    Date:   Sun Jan 10 08:51:56 2021 +1100

        ~ tidying

    commit 5e2a46be09054cacedbf8eef8cfb80c2d294b6c8
    Merge: f63f632 08baa9a
    Author: Matt <Wilson>
    Date:   Sun Jan 10 08:13:58 2021 +1100

        merge 0.14

    commit 08baa9a19a14b3baf86cd0d1113e4f760f503ade
    Author: Matt <Wilson>
    Date:   Sun Jan 10 08:08:11 2021 +1100

        ~ tidying up project files, and removing old solution files

    commit 49bf4b742e7378fd9bc4c41791f91a925e80bf29
    Author: Matt <Wilson>
    Date:   Sun Jan 10 07:59:44 2021 +1100

        + added check_all_flags()

    commit bbdaafa9a24078cacabd8f0bb7eff80624127b92
    Author: Matt <Wilson>
    Date:   Sun Jan 10 07:59:11 2021 +1100

        ~ generalising the copying of generated .lib files to the $(SolutionDir)lib directory with the Synesis naming convention

    commit 279c2a5b57fcde9a3a3db9ebfa1b77dbd48d8e84
    Author: Matt <Wilson>
    Date:   Sun Jan 10 07:57:31 2021 +1100

        ~ specifications now remembered in (hidden field in) arguments

    commit 54f351b12e7af6a1255bfe3816050f516ed78c4a
    Author: Matt <Wilson>
    Date:   Sun Jan 10 07:57:06 2021 +1100

        + clasp_show_version_by_FILE() now includes build-number, unless it is <0

    commit 450818484bab0454d9dc18136dcff4a1262ca43d
    Author: Matt <Wilson>
    Date:   Sun Jan 10 07:56:05 2021 +1100

        ~ various props files improvements

    commit ab3c0984598915109e65185764312fdda814cfed
    Author: Matt <Wilson>
    Date:   Sun Jan 10 07:50:04 2021 +1100

        ~ improved arguments passed to check_option() and check_next_option()

    commit 75866b5abdf0a484c381e60ae7a8a13b7fc96c05
    Author: Matt <Wilson>
    Date:   Sun Jan 10 07:47:06 2021 +1100

        ~ clasp_show_body_by_FILE() now prefixes flag/option list with "Flags:", or "Options:", or "Flags and options:", depending on contents of specifications

    commit 60a4124d46337edd723faba94b5ecdbf5095dd71
    Author: Matt <Wilson>
    Date:   Sun Jan 10 07:27:17 2021 +1100

        ~ sorting and simplification of project/props files
        + added discrimination (borrowed from recls) of operating system and architecture, in the form of
         - CLASP_PLATFORM_IS_UNIX, CLASP_PLATFORM_IS_WIN64, CLASP_PLATFORM_IS_WIN32, CLASP_PLATFORM_IS_WINDOWS; and
         - CLASP_ARCH_IS_X64, CLASP_ARCH_IS_IA64, CLASP_ARCH_IS_X86

    commit 081fa39b2f03f11d6bfce47991ef36e126b185b0
    Author: Matt <Wilson>
    Date:   Sun Jan 10 07:17:41 2021 +1100

        ~ fixed configuration

    commit d1250a9e9c48113d5bf06b7ff991bf7448ea4387
    Author: Matt <Wilson>
    Date:   Sun Jan 10 07:09:18 2021 +1100

        ~ STLSoft compatibility

    commit a2333450b0b48da4d3e0fc35b9f4df9c2848125b
    Author: Matt <Wilson>
    Date:   Sun Jan 10 07:08:42 2021 +1100

        ~ using args->argv[0] for specifying the program path from which to obtain module handle when loading string resources

    commit 616d2800bc0808dfa4267f60c34c6d94ad8cf333
    Author: Matt <Wilson>
    Date:   Sun Jan 10 07:05:26 2021 +1100

        ~ clasp_countSpecifications() precondition weakened to allow null specifications, in which case return s0

    commit 27a4fff9c3113622aa41fc894725406e80687d26
    Author: Matt <Wilson>
    Date:   Sun Jan 10 07:05:03 2021 +1100

        - removed clasp_count_specifications_() in favour of clasp_countSpecifications()

    commit afccfe44cd7e97bcc4b0e536ae7f1e2bc1b25fc9
    Author: Matt <Wilson>
    Date:   Sun Jan 10 07:01:00 2021 +1100

        ~ fixed loading strings from Windows resources in wide character encoding

    commit 62fdd8fd22714c380ab3d7cb778358e74cb95419
    Author: Matt <Wilson>
    Date:   Sun Jan 10 06:59:14 2021 +1100

        ~ changed uses of deprecated clasp_alias_t typedef to clasp_specification_t

    commit 7dc6287971d6a94fc11989ae5415a7b1d819b501
    Author: Matt <Wilson>
    Date:   Sun Jan 10 06:56:47 2021 +1100

        - removed unncessary compile-time dependency on recls

    commit 239495e88790c16b8485211120dafe97bd8a7f6f
    Author: Matt <Wilson>
    Date:   Sun Jan 10 06:54:22 2021 +1100

        ~ prep

    commit 3c142f42ad562b99eacaef2b96726d715c80e579
    Author: Matt <Wilson>
    Date:   Sun Jan 10 06:51:47 2021 +1100

        ~ preparatory mods

    commit c770bc57c7b964ad5e1f1a22db151254b08851f8
    Author: Matt <Wilson>
    Date:   Sun Jan 10 06:42:03 2021 +1100

        merge

    commit 2011c17262ef720aafc1bbe5b383ef3410ce5158
    Author: Matt <Wilson>
    Date:   Sun Jan 10 06:39:14 2021 +1100

        ~ ignores

    commit f63f632764c1a93803dc4ef727acc390cf535e72
    Author: Matt <Wilson>
    Date:   Sun Jan 10 06:39:14 2021 +1100

        ~ ignores

    commit ffe47a4f591dd1ad3c4ce082f51b73f2fa902306
    Author: Matt <Wilson>
    Date:   Fri Jan 8 15:46:17 2021 +1100

        ~ preparatory refactoring

    commit 0669c59891c7dbfbff00d3663ad05a949eec2811
    Author: Matt <Wilson>
    Date:   Fri Jan 8 15:45:57 2021 +1100

        ~ VC++ 16 compatibility

    commit ae824e22425d9c67cf10dda4707f1116468f33f0
    Merge: ec904a8 fb39659
    Author: Matt <matthew@synesis.com.au>
    Date:   Fri Jan 8 08:22:44 2021 +1100

        merged in cmake branch

    commit fb3965948107c624de12b7a25e47c6306fb9dd55
    Author: Matt <matthew@synesis.com.au>
    Date:   Fri Jan 8 07:18:45 2021 +1100

        + added CMake support

    commit 095944cb0e43f8439266549dd3dbb99c479719ef
    Author: Matt <matthew@synesis.com.au>
    Date:   Fri Jan 8 07:17:42 2021 +1100

        ~ warnings

    commit 986141abe8308e72ed25c38d1e0ee5c515e99ffa
    Author: Matt <matthew@synesis.com.au>
    Date:   Fri Jan 8 07:12:28 2021 +1100

        ~ warnings

    commit b95d8530c52c8923480d6564efa4ab3c64775309
    Author: Matt <matthew@synesis.com.au>
    Date:   Fri Jan 8 06:41:32 2021 +1100

        ~ fixes to warnings

    commit 58ea3ee2dd504bb912fdc06bce7e04bf285a2a77
    Author: Matt <Wilson>
    Date:   Wed Oct 28 16:25:25 2020 +1100

        merge

    commit 96aebdc0bb9417548814d858c5102b4d9119d267
    Author: Matt <Wilson>
    Date:   Wed Oct 28 16:24:38 2020 +1100

        ~ ignores

    commit b51a535bec95ade3ff0f2f81b00acf71a7725873
    Author: Matt <Wilson>
    Date:   Wed Oct 28 16:09:22 2020 +1100

        ~ layout

    commit 100899fe14fed1d935334c9bf4f2436af884ec64
    Author: Matt <Wilson>
    Date:   Wed Oct 28 16:05:32 2020 +1100

        ~ whitespace

    commit ffc96ab0e9815c2b65b9ecbead0347ac634603be
    Author: Matt Wilson <matthew@synesis.com.au>
    Date:   Mon Sep 28 16:22:55 2020 +1100

        + added resource replacement for version (as it is for header)

    commit ec904a87439858c8d0172663fd6336eb4aa8d01a
    Author: Matt <Wilson>
    Date:   Wed Aug 5 13:00:07 2020 +1000

        ~ changed primary include directory to <clasp/*> from <systemtools/clasp/*>

    commit 47622c3418b92dc2b53ae04da9206f6347c8b47d
    Merge: d27adc2 cb46197
    Author: Matt <Wilson>
    Date:   Wed Aug 5 11:17:24 2020 +1000

        Merge branch '0.14' of V:\git\freelibs\SystemTools\libraries\CLASP\CLASP into 0.14

    commit d27adc2fade3e66f1e3c32f92b0b28eb0f9aefe1
    Author: Matt <Wilson>
    Date:   Wed Aug 5 10:39:10 2020 +1000

        + initial (redirecting) versions of API headers; ~ renaming of alias => specification

    commit cb46197cc99d341256faa7c6957298806c9e561a
    Author: Matt <Wilson>
    Date:   Wed Aug 5 10:39:10 2020 +1000

        + initial (redirecting) versions of API headers; ~ renaming of alias => specification

    commit 35ebecd60ef25c9b0e441cdc572ea69b4ee5518e
    Author: Matt <Wilson>
    Date:   Wed Aug 5 10:34:49 2020 +1000

        + added support for Visual C++ 15 and 15; ~ various makefile improvements

    commit 3cbbcd894dc2829db30bddc2997ae783c7fd3b53
    Author: Matt <Wilson>
    Date:   Wed Aug 5 10:33:16 2020 +1000

        ~ ignores

    commit 87a8f212f5272a32f2ca6b727ebdf1a841254acf
    Author: Matt <matthew@synesis.com.au>
    Date:   Thu Jul 30 19:33:47 2020 +1000

        clasp_show_version_by_FILE() : ~ now elides revision (aka patch) if < 0

    commit abac3bc8c3cade03947100bd0e683caf25b88377
    Author: Matt <matthew@synesis.com.au>
    Date:   Thu Jul 30 19:33:14 2020 +1000

        + added .vimrc

    commit 2500d31f88ad9e555aa9ecd07567d2e0e2e497fc
    Author: Matt <matthew@synesis.com.au>
    Date:   Thu Jul 30 19:14:09 2020 +1000

        ~ corrections

    commit 2dcce21f3891ef5fbd8edb9b6e17fc2968313fa3
    Author: Matt <Wilson>
    Date:   Thu Jul 30 19:02:21 2020 +1000

        + generic stream inserters for clasp_slice_t and clasp_argument_t
        + added string access shims for clasp_alias_t (based on mappedArgument)

    commit 5dd842f8037f54d470b0ace6d5751fde8c69ed02
    Author: Matt <Wilson>
    Date:   Thu Jul 30 19:00:38 2020 +1000

        ~ fixing up handling of option value constraints for unsigned types
        ~ the callback-function form of check_option() now accepts heterogenous types of optionName parameter and defaultValue parameter (e.g. can now specify for defaultValue an enumerator from the enumeration matching the result parameter rather than a string)

    commit 8fa685ec88a6ca10963eaf5c285db3acbd528fe3
    Author: Matt <Wilson>
    Date:   Thu Jul 30 18:55:59 2020 +1000

        ~ fixed program-name evaluation

    commit 85ab2bb10e681e8965616212fa89524acbfe4205
    Author: Matt <Wilson>
    Date:   Thu Jul 30 18:55:03 2020 +1000

        ~ abstracting strerror()

    commit ac8984960293afbd4ab81f758c2ead1f445d19e2
    Author: Matt <Wilson>
    Date:   Thu Jul 30 18:53:34 2020 +1000

        ~ various test improvements; + added VC10 project files

    commit ad37af5755c56eb06b1cbd930e6b9186d93069a3
    Author: Matt <Wilson>
    Date:   Thu Jul 30 18:50:29 2020 +1000

        + added makefile for gcc81 for MinGW

    commit 14f74a88828ca14a25eab3290f93b0783d616259
    Author: Matt <Wilson>
    Date:   Thu Jul 30 18:50:09 2020 +1000

        ~ tidying / cleaning up .dsp files

    commit 17d607143572e3823f027a850b664d6136de8d2a
    Author: Matt <Wilson>
    Date:   Thu Jul 30 18:47:46 2020 +1000

        ~ fix
