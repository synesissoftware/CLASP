############################################################################
# File: 	makefile
#
# Purpose:	Makefile for the SystemTools::CLASP project,
#           for the Visual C++ 15.0 compiler,
#           on Win32
#
# Created:	3rd August 2020
# Updated:	3rd August 2020
#
############################################################################


############################################################################
# environment check
#
# * to build without recls support make with the symbol CLASP_NO_RECLS
#   defined, e.g. "> nmake CLASP_NO_RECLS=1 build"

!ifdef CLASP_NO_RECLS
! message
! message WARNING: Building CLASP on Windows without recls : this will cause the preprocessor symbol CLASP_CMDLINE_ARGS_USE_RECLS to be defined, which will result in CLASP not performing command-line wildcard expansion. If this is not what you want, you must define an environment variable (or provide a MAKE argument) RECLS_ROOT, which specifies the root directory of your recls library tree.
! message
!else
! ifndef RECLS_ROOT
!  error RECLS_ROOT must be defined
! endif # !RECLS_ROOT
!endif

############################################################################
# pseudo-targets

#.SILENT:

############################################################################
# symbols

########################################
# project & compiler version

COMP_TAG			=	vc15
CLASP_MAKE_VC_NO_ST	=	1
ARCH_TAG			=	
OS_TAG				=	
PROJ_TAG			=	systemtools.clasp
PROJ_VER_MAJOR		=	0

########################################
# testing verbosity

TEST_VERBOSITY		=	2

########################################
# directories

PROJ_ROOT_DIR = ..\..
PROJ_INC_DIR = $(PROJ_ROOT_DIR)\include
PROJ_SRC_DIR = $(PROJ_ROOT_DIR)\src
PROJ_LIB_DIR = $(PROJ_ROOT_DIR)\lib
PROJ_BIN_DIR = $(PROJ_ROOT_DIR)\bin

########################################
# tools

AR		=   lib -nologo
CC		=	$(CC) -nologo
CPPC	=	$(CPP) -nologo
LD		=   link -nologo
RC		=   rc

CP		=   copy
MKDIR	=	mkdir
MV		=	rename
RM		=   del /f

########################################
# symbols

# configurations:
#
# 0 : multibyte / wide			:	M / W
# 1 : single / multi / dll		:	S / M / D
# 2 : debug / release / test	:	D / M / T	=> NOTE: Test not currently provided
# 

TARGET_LIB_CORE_ROOT_ = systemtools.clasp.0.core

CORE_LIB_BASE_ = $(PROJ_LIB_DIR)\$(TARGET_LIB_CORE_ROOT_).$(COMP_TAG)$(ARCH_TAG)__CONFIGURATION__.lib

!ifndef CLASP_MAKE_VC_NO_ST
CORE_LIB_CORE_MSD = $(CORE_LIB_BASE_:__CONFIGURATION__=.debug)
CORE_LIB_CORE_MSR = $(CORE_LIB_BASE_:__CONFIGURATION__=)
!endif # CLASP_MAKE_VC_NO_ST
CORE_LIB_CORE_MMD = $(CORE_LIB_BASE_:__CONFIGURATION__=.mt.debug)
CORE_LIB_CORE_MMR = $(CORE_LIB_BASE_:__CONFIGURATION__=.mt)
CORE_LIB_CORE_MDD = $(CORE_LIB_BASE_:__CONFIGURATION__=.dll.debug)
CORE_LIB_CORE_MDR = $(CORE_LIB_BASE_:__CONFIGURATION__=.dll)
!ifndef CLASP_MAKE_VC_NO_ST
CORE_LIB_CORE_WSD = $(CORE_LIB_BASE_:__CONFIGURATION__=.widestring.debug)
CORE_LIB_CORE_WSR = $(CORE_LIB_BASE_:__CONFIGURATION__=.widestring)
!endif # CLASP_MAKE_VC_NO_ST
CORE_LIB_CORE_WMD = $(CORE_LIB_BASE_:__CONFIGURATION__=.widestring.mt.debug)
CORE_LIB_CORE_WMR = $(CORE_LIB_BASE_:__CONFIGURATION__=.widestring.mt)
CORE_LIB_CORE_WDD = $(CORE_LIB_BASE_:__CONFIGURATION__=.widestring.dll.debug)
CORE_LIB_CORE_WDR = $(CORE_LIB_BASE_:__CONFIGURATION__=.widestring.dll)

CORE_LIBS=\
!ifndef CLASP_MAKE_VC_NO_ST
 $(CORE_LIB_CORE_MSD)\
 $(CORE_LIB_CORE_MSR)\
!endif # CLASP_MAKE_VC_NO_ST
 $(CORE_LIB_CORE_MMD)\
 $(CORE_LIB_CORE_MMR)\
 $(CORE_LIB_CORE_MDD)\
 $(CORE_LIB_CORE_MDR)\
!ifndef CLASP_MAKE_VC_NO_ST
 $(CORE_LIB_CORE_WSD)\
 $(CORE_LIB_CORE_WSR)\
!endif # CLASP_MAKE_VC_NO_ST
 $(CORE_LIB_CORE_WMD)\
 $(CORE_LIB_CORE_WMR)\
 $(CORE_LIB_CORE_WDD)\
 $(CORE_LIB_CORE_WDR)\
 \


CORE_SRCS_BASE=\
__SRCDIR__clasp.api__MODIFIER____EXT__\
__SRCDIR__clasp.core__MODIFIER____EXT__\
__SRCDIR__clasp.diagnostics__MODIFIER____EXT__\
__SRCDIR__clasp.memory__MODIFIER____EXT__\
__SRCDIR__clasp.string__MODIFIER____EXT__\
__SRCDIR__clasp.usage__MODIFIER____EXT__\
__SRCDIR__clasp.usage.FILE__MODIFIER____EXT__\
\

CORE_SRCS=$(CORE_SRCS_BASE)
CORE_SRCS=$(CORE_SRCS:__SRCDIR__=..\..\src\)
CORE_SRCS=$(CORE_SRCS:__MODIFIER__=)
CORE_SRCS=$(CORE_SRCS:__EXT__=.c)


CORE_OBJS_BASE=$(CORE_SRCS_BASE)
CORE_OBJS_BASE=$(CORE_OBJS_BASE:__SRCDIR__=.\)
CORE_OBJS_BASE=$(CORE_OBJS_BASE:__EXT__=obj)


!ifndef CLASP_MAKE_VC_NO_ST
CORE_OBJS_MSD=$(CORE_OBJS_BASE:__MODIFIER__=.msd_)
CORE_OBJS_MSR=$(CORE_OBJS_BASE:__MODIFIER__=.msr_)
!endif # CLASP_MAKE_VC_NO_ST
CORE_OBJS_MMD=$(CORE_OBJS_BASE:__MODIFIER__=.mmd_)
CORE_OBJS_MMR=$(CORE_OBJS_BASE:__MODIFIER__=.mmr_)
CORE_OBJS_MDD=$(CORE_OBJS_BASE:__MODIFIER__=.mdd_)
CORE_OBJS_MDR=$(CORE_OBJS_BASE:__MODIFIER__=.mdr_)
!ifndef CLASP_MAKE_VC_NO_ST
CORE_OBJS_WSD=$(CORE_OBJS_BASE:__MODIFIER__=.wsd_)
CORE_OBJS_WSR=$(CORE_OBJS_BASE:__MODIFIER__=.wsr_)
!endif # CLASP_MAKE_VC_NO_ST
CORE_OBJS_WMD=$(CORE_OBJS_BASE:__MODIFIER__=.wmd_)
CORE_OBJS_WMR=$(CORE_OBJS_BASE:__MODIFIER__=.wmr_)
CORE_OBJS_WDD=$(CORE_OBJS_BASE:__MODIFIER__=.wdd_)
CORE_OBJS_WDR=$(CORE_OBJS_BASE:__MODIFIER__=.wdr_)

CORE_OBJS=\
!ifndef CLASP_MAKE_VC_NO_ST
 $(CORE_OBJS_MSD)\
 $(CORE_OBJS_MSR)\
!endif # CLASP_MAKE_VC_NO_ST
 $(CORE_OBJS_MMD)\
 $(CORE_OBJS_MMR)\
 $(CORE_OBJS_MDD)\
 $(CORE_OBJS_MDR)\
!ifndef CLASP_MAKE_VC_NO_ST
 $(CORE_OBJS_WSD)\
 $(CORE_OBJS_WSR)\
!endif # CLASP_MAKE_VC_NO_ST
 $(CORE_OBJS_WMD)\
 $(CORE_OBJS_WMR)\
 $(CORE_OBJS_WDD)\
 $(CORE_OBJS_WDR)\
 \


LIBS=\
 $(CORE_LIBS)\
 \

OBJS=\
 $(CORE_OBJS)\
 \

############################################################################
# Targets

########################################
# Top-level targets

all:\
	build\
	\

build:\
	$(LIBS)\
	\

compile:\
	$(OBJS)\
	\

CLEAN_OBJ_COMMAND=-if exist *.__MODIFIER__obj $(RM) *.__MODIFIER__obj


clean:\
	clean.objs\
	clean.libs\
	\

clean.objs:
	@-if exist *.obj $(RM) *.obj
	@-if exist *.pdb $(RM) *.pdb
!ifndef CLASP_MAKE_VC_NO_ST
	@$(CLEAN_OBJ_COMMAND:__MODIFIER__=msd_)
	@$(CLEAN_OBJ_COMMAND:__MODIFIER__=msr_)
!endif # CLASP_MAKE_VC_NO_ST
	@$(CLEAN_OBJ_COMMAND:__MODIFIER__=mmd_)
	@$(CLEAN_OBJ_COMMAND:__MODIFIER__=mmr_)
	@$(CLEAN_OBJ_COMMAND:__MODIFIER__=mdd_)
	@$(CLEAN_OBJ_COMMAND:__MODIFIER__=mdr_)
!ifndef CLASP_MAKE_VC_NO_ST
	@$(CLEAN_OBJ_COMMAND:__MODIFIER__=wsd_)
	@$(CLEAN_OBJ_COMMAND:__MODIFIER__=wsr_)
!endif # CLASP_MAKE_VC_NO_ST
	@$(CLEAN_OBJ_COMMAND:__MODIFIER__=wmd_)
	@$(CLEAN_OBJ_COMMAND:__MODIFIER__=wmr_)
	@$(CLEAN_OBJ_COMMAND:__MODIFIER__=wdd_)
	@$(CLEAN_OBJ_COMMAND:__MODIFIER__=wdr_)

clean.libs:
!ifndef CLASP_MAKE_VC_NO_ST
	@-if exist $(CORE_LIB_CORE_MSD) $(RM) $(CORE_LIB_CORE_MSD)
	@-if exist $(CORE_LIB_CORE_MSR) $(RM) $(CORE_LIB_CORE_MSR)
!endif # CLASP_MAKE_VC_NO_ST
	@-if exist $(CORE_LIB_CORE_MMD) $(RM) $(CORE_LIB_CORE_MMD)
	@-if exist $(CORE_LIB_CORE_MMR) $(RM) $(CORE_LIB_CORE_MMR)
	@-if exist $(CORE_LIB_CORE_MDD) $(RM) $(CORE_LIB_CORE_MDD)
	@-if exist $(CORE_LIB_CORE_MDR) $(RM) $(CORE_LIB_CORE_MDR)
!ifndef CLASP_MAKE_VC_NO_ST
	@-if exist $(CORE_LIB_CORE_WSD) $(RM) $(CORE_LIB_CORE_WSD)
	@-if exist $(CORE_LIB_CORE_WSR) $(RM) $(CORE_LIB_CORE_WSR)
!endif # CLASP_MAKE_VC_NO_ST
	@-if exist $(CORE_LIB_CORE_WMD) $(RM) $(CORE_LIB_CORE_WMD)
	@-if exist $(CORE_LIB_CORE_WMR) $(RM) $(CORE_LIB_CORE_WMR)
	@-if exist $(CORE_LIB_CORE_WDD) $(RM) $(CORE_LIB_CORE_WDD)
	@-if exist $(CORE_LIB_CORE_WDR) $(RM) $(CORE_LIB_CORE_WDR)


########################################
# pseudo-targets

# need parentheses, otherwise subsequent commands (via && or &) will be taken as THEN of IF
CHECK_LIB_DIR	=	-(if not exist $(PROJ_LIB_DIR)\NUL mkdir $(PROJ_LIB_DIR))
check_lib_dir:
	$(CHECK_LIB_DIR)

########################################
# targets

CC_INCLUDES=\
 -I$(PROJ_INC_DIR)\
!ifndef CLASP_NO_RECLS
 -I$(RECLS_ROOT)/include\
!endif
 \

CC_DEFINES_BASE=\
 -DWIN32\
 \

CC_DEFINES_MULTIBYTE=\
 -UCLASP_USE_WIDE_STRINGS\
 \

CC_DEFINES_WIDE=\
 -DCLASP_USE_WIDE_STRINGS\
 -DUNICODE\
 -D_UNICODE\
 \

!ifndef CLASP_MAKE_VC_NO_ST
CC_DEFINES_MSD=$(CC_DEFINES_BASE) $(CC_DEFINES_MULTIBYTE)
CC_DEFINES_MSR=$(CC_DEFINES_BASE) $(CC_DEFINES_MULTIBYTE)
!endif # CLASP_MAKE_VC_NO_ST
CC_DEFINES_MMD=$(CC_DEFINES_BASE) $(CC_DEFINES_MULTIBYTE)
CC_DEFINES_MMR=$(CC_DEFINES_BASE) $(CC_DEFINES_MULTIBYTE)
CC_DEFINES_MDD=$(CC_DEFINES_BASE) $(CC_DEFINES_MULTIBYTE)
CC_DEFINES_MDR=$(CC_DEFINES_BASE) $(CC_DEFINES_MULTIBYTE)
!ifndef CLASP_MAKE_VC_NO_ST
CC_DEFINES_WSD=$(CC_DEFINES_BASE) $(CC_DEFINES_WIDE)
CC_DEFINES_WSR=$(CC_DEFINES_BASE) $(CC_DEFINES_WIDE)
!endif # CLASP_MAKE_VC_NO_ST
CC_DEFINES_WMD=$(CC_DEFINES_BASE) $(CC_DEFINES_WIDE)
CC_DEFINES_WMR=$(CC_DEFINES_BASE) $(CC_DEFINES_WIDE)
CC_DEFINES_WDD=$(CC_DEFINES_BASE) $(CC_DEFINES_WIDE)
CC_DEFINES_WDR=$(CC_DEFINES_BASE) $(CC_DEFINES_WIDE)

!ifndef CLASP_MAKE_VC_NO_ST
CC_THREADING_MSD=-MLd
CC_THREADING_MSR=-ML
!endif # CLASP_MAKE_VC_NO_ST
CC_THREADING_MMD=-MTd
CC_THREADING_MMR=-MT
CC_THREADING_MDD=-MDd
CC_THREADING_MDR=-MD
!ifndef CLASP_MAKE_VC_NO_ST
CC_THREADING_WSD=-MLd
CC_THREADING_WSR=-ML
!endif # CLASP_MAKE_VC_NO_ST
CC_THREADING_WMD=-MTd
CC_THREADING_WMR=-MT
CC_THREADING_WDD=-MDd
CC_THREADING_WDR=-MD

CC_ARGS_COMMON=
CC_ARGS_COMMON=$(CC_ARGS_COMMON) -WX
CC_ARGS_COMMON=$(CC_ARGS_COMMON) -W4

CC_ARGS_DEBUG=
CC_ARGS_DEBUG=$(CC_ARGS_DEBUG) $(CC_ARGS_COMMON)
CC_ARGS_DEBUG=$(CC_ARGS_DEBUG) -Od
CC_ARGS_DEBUG=$(CC_ARGS_DEBUG) -Zi

CC_ARGS_RELEASE=
CC_ARGS_RELEASE=$(CC_ARGS_RELEASE) $(CC_ARGS_COMMON)
CC_ARGS_RELEASE=$(CC_ARGS_RELEASE) -Ox

!ifndef CLASP_MAKE_VC_NO_ST
CC_ARGS_MSD=$(CC_THREADING_MSD) $(CC_ARGS_DEBUG)
CC_ARGS_MSR=$(CC_THREADING_MSR) $(CC_ARGS_RELEASE)
!endif # CLASP_MAKE_VC_NO_ST
CC_ARGS_MMD=$(CC_THREADING_MMD) $(CC_ARGS_DEBUG)
CC_ARGS_MMR=$(CC_THREADING_MMR) $(CC_ARGS_RELEASE)
CC_ARGS_MDD=$(CC_THREADING_MDD) $(CC_ARGS_DEBUG)
CC_ARGS_MDR=$(CC_THREADING_MDR) $(CC_ARGS_RELEASE)
!ifndef CLASP_MAKE_VC_NO_ST
CC_ARGS_WSD=$(CC_THREADING_WSD) $(CC_ARGS_DEBUG)
CC_ARGS_WSR=$(CC_THREADING_WSR) $(CC_ARGS_RELEASE)
!endif # CLASP_MAKE_VC_NO_ST
CC_ARGS_WMD=$(CC_THREADING_WMD) $(CC_ARGS_DEBUG)
CC_ARGS_WMR=$(CC_THREADING_WMR) $(CC_ARGS_RELEASE)
CC_ARGS_WDD=$(CC_THREADING_WDD) $(CC_ARGS_DEBUG)
CC_ARGS_WDR=$(CC_THREADING_WDR) $(CC_ARGS_RELEASE)


CC_CMD_RM_obj=(if exist *.obj $(RM) *.obj)

CC_CMD_MV_PRE_xxx=(if exist *.__LOWER___obj $(MV) *.__LOWER___obj *.obj)

CC_CMD_MV_POST_xxx=($(MV) *.obj *.__LOWER___obj)

!ifndef CLASP_MAKE_VC_NO_ST
CC_CMD_MV_PRE_MSD=$(CC_CMD_MV_PRE_xxx:__LOWER__=msd)
CC_CMD_MV_PRE_MSR=$(CC_CMD_MV_PRE_xxx:__LOWER__=msr)
!endif # CLASP_MAKE_VC_NO_ST
CC_CMD_MV_PRE_MMD=$(CC_CMD_MV_PRE_xxx:__LOWER__=mmd)
CC_CMD_MV_PRE_MMR=$(CC_CMD_MV_PRE_xxx:__LOWER__=mmr)
CC_CMD_MV_PRE_MDD=$(CC_CMD_MV_PRE_xxx:__LOWER__=mdd)
CC_CMD_MV_PRE_MDR=$(CC_CMD_MV_PRE_xxx:__LOWER__=mdr)
!ifndef CLASP_MAKE_VC_NO_ST
CC_CMD_MV_PRE_WSD=$(CC_CMD_MV_PRE_xxx:__LOWER__=wsd)
CC_CMD_MV_PRE_WSR=$(CC_CMD_MV_PRE_xxx:__LOWER__=wsr)
!endif # CLASP_MAKE_VC_NO_ST
CC_CMD_MV_PRE_WMD=$(CC_CMD_MV_PRE_xxx:__LOWER__=wmd)
CC_CMD_MV_PRE_WMR=$(CC_CMD_MV_PRE_xxx:__LOWER__=wmr)
CC_CMD_MV_PRE_WDD=$(CC_CMD_MV_PRE_xxx:__LOWER__=wdd)
CC_CMD_MV_PRE_WDR=$(CC_CMD_MV_PRE_xxx:__LOWER__=wdr)

!ifndef CLASP_MAKE_VC_NO_ST
CC_CMD_MV_POST_MSD=$(CC_CMD_MV_POST_xxx:__LOWER__=msd)
CC_CMD_MV_POST_MSR=$(CC_CMD_MV_POST_xxx:__LOWER__=msr)
!endif # CLASP_MAKE_VC_NO_ST
CC_CMD_MV_POST_MMD=$(CC_CMD_MV_POST_xxx:__LOWER__=mmd)
CC_CMD_MV_POST_MMR=$(CC_CMD_MV_POST_xxx:__LOWER__=mmr)
CC_CMD_MV_POST_MDD=$(CC_CMD_MV_POST_xxx:__LOWER__=mdd)
CC_CMD_MV_POST_MDR=$(CC_CMD_MV_POST_xxx:__LOWER__=mdr)
!ifndef CLASP_MAKE_VC_NO_ST
CC_CMD_MV_POST_WSD=$(CC_CMD_MV_POST_xxx:__LOWER__=wsd)
CC_CMD_MV_POST_WSR=$(CC_CMD_MV_POST_xxx:__LOWER__=wsr)
!endif # CLASP_MAKE_VC_NO_ST
CC_CMD_MV_POST_WMD=$(CC_CMD_MV_POST_xxx:__LOWER__=wmd)
CC_CMD_MV_POST_WMR=$(CC_CMD_MV_POST_xxx:__LOWER__=wmr)
CC_CMD_MV_POST_WDD=$(CC_CMD_MV_POST_xxx:__LOWER__=wdd)
CC_CMD_MV_POST_WDR=$(CC_CMD_MV_POST_xxx:__LOWER__=wdr)

!ifndef CLASP_MAKE_VC_NO_ST
{..\..\src}.c{.}.msd_obj:: ; $(CC_CMD_RM_obj) & $(CC_CMD_MV_PRE_MSD) & $(CC) -c $(CC_DEFINES_MSD) $(CC_ARGS_MSD) $(CC_INCLUDES) -Fdmsd.pdb $< && $(CC_CMD_MV_POST_MSD)
{..\..\src}.c{.}.msr_obj:: ; $(CC_CMD_RM_obj) & $(CC_CMD_MV_PRE_MSR) & $(CC) -c $(CC_DEFINES_MSR) $(CC_ARGS_MSR) $(CC_INCLUDES) -Fdmsr.pdb $< && $(CC_CMD_MV_POST_MSR)
!endif # CLASP_MAKE_VC_NO_ST
{..\..\src}.c{.}.mmd_obj:: ; $(CC_CMD_RM_obj) & $(CC_CMD_MV_PRE_MMD) & $(CC) -c $(CC_DEFINES_MMD) $(CC_ARGS_MMD) $(CC_INCLUDES) -Fdmmd.pdb $< && $(CC_CMD_MV_POST_MMD)
{..\..\src}.c{.}.mmr_obj:: ; $(CC_CMD_RM_obj) & $(CC_CMD_MV_PRE_MMR) & $(CC) -c $(CC_DEFINES_MMR) $(CC_ARGS_MMR) $(CC_INCLUDES) -Fdmmr.pdb $< && $(CC_CMD_MV_POST_MMR)
{..\..\src}.c{.}.mdd_obj:: ; $(CC_CMD_RM_obj) & $(CC_CMD_MV_PRE_MDD) & $(CC) -c $(CC_DEFINES_MDD) $(CC_ARGS_MDD) $(CC_INCLUDES) -Fdmdd.pdb $< && $(CC_CMD_MV_POST_MDD)
{..\..\src}.c{.}.mdr_obj:: ; $(CC_CMD_RM_obj) & $(CC_CMD_MV_PRE_MDR) & $(CC) -c $(CC_DEFINES_MDR) $(CC_ARGS_MDR) $(CC_INCLUDES) -Fdmdr.pdb $< && $(CC_CMD_MV_POST_MDR)
!ifndef CLASP_MAKE_VC_NO_ST
{..\..\src}.c{.}.wsd_obj:: ; $(CC_CMD_RM_obj) & $(CC_CMD_MV_PRE_WSD) & $(CC) -c $(CC_DEFINES_WSD) $(CC_ARGS_WSD) $(CC_INCLUDES) -Fdwsd.pdb $< && $(CC_CMD_MV_POST_WSD)
{..\..\src}.c{.}.wsr_obj:: ; $(CC_CMD_RM_obj) & $(CC_CMD_MV_PRE_WSR) & $(CC) -c $(CC_DEFINES_WSR) $(CC_ARGS_WSR) $(CC_INCLUDES) -Fdwsr.pdb $< && $(CC_CMD_MV_POST_WSR)
!endif # CLASP_MAKE_VC_NO_ST
{..\..\src}.c{.}.wmd_obj:: ; $(CC_CMD_RM_obj) & $(CC_CMD_MV_PRE_WMD) & $(CC) -c $(CC_DEFINES_WMD) $(CC_ARGS_WMD) $(CC_INCLUDES) -Fdwmd.pdb $< && $(CC_CMD_MV_POST_WMD)
{..\..\src}.c{.}.wmr_obj:: ; $(CC_CMD_RM_obj) & $(CC_CMD_MV_PRE_WMR) & $(CC) -c $(CC_DEFINES_WMR) $(CC_ARGS_WMR) $(CC_INCLUDES) -Fdwmr.pdb $< && $(CC_CMD_MV_POST_WMR)
{..\..\src}.c{.}.wdd_obj:: ; $(CC_CMD_RM_obj) & $(CC_CMD_MV_PRE_WDD) & $(CC) -c $(CC_DEFINES_WDD) $(CC_ARGS_WDD) $(CC_INCLUDES) -Fdwdd.pdb $< && $(CC_CMD_MV_POST_WDD)
{..\..\src}.c{.}.wdr_obj:: ; $(CC_CMD_RM_obj) & $(CC_CMD_MV_PRE_WDR) & $(CC) -c $(CC_DEFINES_WDR) $(CC_ARGS_WDR) $(CC_INCLUDES) -Fdwdr.pdb $< && $(CC_CMD_MV_POST_WDR)

AR_ARGS_DEBUG=\
 \

AR_ARGS_RELEASE=\
 \


!ifndef CLASP_MAKE_VC_NO_ST
AR_ARGS_MSD=$(AR_ARGS_DEBUG)
AR_ARGS_MSR=$(AR_ARGS_RELEASE)
!endif # CLASP_MAKE_VC_NO_ST
AR_ARGS_MMD=$(AR_ARGS_DEBUG)
AR_ARGS_MMR=$(AR_ARGS_RELEASE)
AR_ARGS_MDD=$(AR_ARGS_DEBUG)
AR_ARGS_MDR=$(AR_ARGS_RELEASE)
!ifndef CLASP_MAKE_VC_NO_ST
AR_ARGS_WSD=$(AR_ARGS_DEBUG)
AR_ARGS_WSR=$(AR_ARGS_RELEASE)
!endif # CLASP_MAKE_VC_NO_ST
AR_ARGS_WMD=$(AR_ARGS_DEBUG)
AR_ARGS_WMR=$(AR_ARGS_RELEASE)
AR_ARGS_WDD=$(AR_ARGS_DEBUG)
AR_ARGS_WDR=$(AR_ARGS_RELEASE)

!ifndef CLASP_MAKE_VC_NO_ST
$(CORE_LIB_CORE_MSD):	$(CORE_OBJS_MSD)	;	$(CHECK_LIB_DIR)	&&	$(AR) $(AR_ARGS_MSD) -out:$@ $**
$(CORE_LIB_CORE_MSR):	$(CORE_OBJS_MSR)	;	$(CHECK_LIB_DIR)	&&	$(AR) $(AR_ARGS_MSR) -out:$@ $**
!endif # CLASP_MAKE_VC_NO_ST
$(CORE_LIB_CORE_MMD):	$(CORE_OBJS_MMD)	;	$(CHECK_LIB_DIR)	&&	$(AR) $(AR_ARGS_MMD) -out:$@ $**
$(CORE_LIB_CORE_MMR):	$(CORE_OBJS_MMR)	;	$(CHECK_LIB_DIR)	&&	$(AR) $(AR_ARGS_MMR) -out:$@ $**
$(CORE_LIB_CORE_MDD):	$(CORE_OBJS_MDD)	;	$(CHECK_LIB_DIR)	&&	$(AR) $(AR_ARGS_MDD) -out:$@ $**
$(CORE_LIB_CORE_MDR):	$(CORE_OBJS_MDR)	;	$(CHECK_LIB_DIR)	&&	$(AR) $(AR_ARGS_MDR) -out:$@ $**
!ifndef CLASP_MAKE_VC_NO_ST
$(CORE_LIB_CORE_WSD):	$(CORE_OBJS_WSD)	;	$(CHECK_LIB_DIR)	&&	$(AR) $(AR_ARGS_WSD) -out:$@ $**
$(CORE_LIB_CORE_WSR):	$(CORE_OBJS_WSR)	;	$(CHECK_LIB_DIR)	&&	$(AR) $(AR_ARGS_WSR) -out:$@ $**
!endif # CLASP_MAKE_VC_NO_ST
$(CORE_LIB_CORE_WMD):	$(CORE_OBJS_WMD)	;	$(CHECK_LIB_DIR)	&&	$(AR) $(AR_ARGS_WMD) -out:$@ $**
$(CORE_LIB_CORE_WMR):	$(CORE_OBJS_WMR)	;	$(CHECK_LIB_DIR)	&&	$(AR) $(AR_ARGS_WMR) -out:$@ $**
$(CORE_LIB_CORE_WDD):	$(CORE_OBJS_WDD)	;	$(CHECK_LIB_DIR)	&&	$(AR) $(AR_ARGS_WDD) -out:$@ $**
$(CORE_LIB_CORE_WDR):	$(CORE_OBJS_WDR)	;	$(CHECK_LIB_DIR)	&&	$(AR) $(AR_ARGS_WDR) -out:$@ $**


################################ end of file ###############################
