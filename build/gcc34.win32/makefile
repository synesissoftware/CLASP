############################################################################
# File: 	makefile
#
# Purpose:	Makefile for the CLASP project,
#           for the GCC 3.4 compiler,
#           on Win32
#
# Created:	4th June 2008
# Updated:	5th August 2020
#
############################################################################


############################################################################
# environment check
#
# * to build without recls support make with the symbol CLASP_NO_RECLS
#   defined, e.g. "> nmake CLASP_NO_RECLS=1 build"

ifdef CLASP_NO_RECLS
 message
 message WARNING: Building CLASP on Windows without recls : this will cause the preprocessor symbol CLASP_CMDLINE_ARGS_USE_RECLS to be defined, which will result in CLASP not performing command-line wildcard expansion. If this is not what you want, you must define an environment variable (or provide a MAKE argument) RECLS_ROOT, which specifies the root directory of your recls library tree.
 message
else
 ifndef RECLS_ROOT
  error RECLS_ROOT must be defined
 endif # !RECLS_ROOT
endif

############################################################################
# pseudo-targets

############################################################################
# symbols

########################################
# project & compiler version

COMP_TAG = gcc34
ARCH_TAG =
OS_TAG = unix
PROJ_TAG = systemtools.clasp
PROJ_VER_MAJOR = 0

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

vpath %.c $(PROJ_SRC_DIR)
vpath %.h $(PROJ_SRC_DIR)

########################################
# tools

AR		=   ar
CC		=	mingw32-gcc
CPPC	=	mingw32-g++
LD		=   ld
RC		=   rc

CP		=   copy
MKDIR	=	mkdir
MV		=	rename
RM		=   del /f


ifndef CLASP_NO_RECLS
CC_INCLUDE_RECLS_=-I $(RECLS_ROOT)\include
else
CC_INCLUDE_RECLS_=
endif

CC_INCLUDES=\
 -I $(PROJ_INC_DIR)\
 $(CC_INCLUDE_RECLS_)\
 \

CC_DEFS_MULTIBYTE=
CC_DEFS_WIDE=-DUNICODE -D_UNICODE

CFLAGS = $(CC_INCLUDES) -DUNIX -Dunix
CFLAGS_MSD = $(CFLAGS) -DDEBUG
CFLAGS_MSR = $(CFLAGS) -DNDEBUG
CFLAGS_MMD = $(CFLAGS_MSD) -D_REENTRANT
CFLAGS_MMR = $(CFLAGS_MSR) -D_REENTRANT
CFLAGS_WSD = $(CFLAGS_MSD) $(CC_DEFS_WIDE)
CFLAGS_WSR = $(CFLAGS_MSR) $(CC_DEFS_WIDE)
CFLAGS_WMD = $(CFLAGS_MMD) $(CC_DEFS_WIDE)
CFLAGS_WMR = $(CFLAGS_MMR) $(CC_DEFS_WIDE)

########################################
# symbols

# configurations:
#
# 0 : multibyte / wide			:	M / W
# 1 : single / multi / dll		:	S / M / D
# 2 : debug / release / test	:	D / M / T	=> NOTE: Test not currently provided
#

TARGET_LIB_CORE_ROOT_ = lib$(PROJ_TAG).0.core

TARGET_LIB_CORE_MSD = $(PROJ_LIB_DIR)\$(TARGET_LIB_CORE_ROOT_).$(COMP_TAG).debug.a
TARGET_LIB_CORE_MSR = $(PROJ_LIB_DIR)\$(TARGET_LIB_CORE_ROOT_).$(COMP_TAG).a
TARGET_LIB_CORE_MMD = $(PROJ_LIB_DIR)\$(TARGET_LIB_CORE_ROOT_).$(COMP_TAG).mt.debug.a
TARGET_LIB_CORE_MMR = $(PROJ_LIB_DIR)\$(TARGET_LIB_CORE_ROOT_).$(COMP_TAG).mt.a
TARGET_LIB_CORE_WSD = $(PROJ_LIB_DIR)\$(TARGET_LIB_CORE_ROOT_).$(COMP_TAG).widestring.debug.a
TARGET_LIB_CORE_WSR = $(PROJ_LIB_DIR)\$(TARGET_LIB_CORE_ROOT_).$(COMP_TAG).widestring.a
TARGET_LIB_CORE_WMD = $(PROJ_LIB_DIR)\$(TARGET_LIB_CORE_ROOT_).$(COMP_TAG).widestring.mt.debug.a
TARGET_LIB_CORE_WMR = $(PROJ_LIB_DIR)\$(TARGET_LIB_CORE_ROOT_).$(COMP_TAG).widestring.mt.a

LIBS=\
 $(TARGET_LIB_CORE_MSD)\
 $(TARGET_LIB_CORE_MSR)\
 $(TARGET_LIB_CORE_MMD)\
 $(TARGET_LIB_CORE_MMR)\
 $(TARGET_LIB_CORE_WSD)\
 $(TARGET_LIB_CORE_WSR)\
 $(TARGET_LIB_CORE_WMD)\
 $(TARGET_LIB_CORE_WMR)\
 \

OBJS_SUBS_SYM_=__CONFIGURATION__
OBJS_SYM_MSD_=msd
OBJS_SYM_MSR_=msr
OBJS_SYM_MMD_=mmd
OBJS_SYM_MMR_=mmr
OBJS_SYM_WSD_=wsd
OBJS_SYM_WSR_=wsr
OBJS_SYM_WMD_=wmd
OBJS_SYM_WMR_=wmr

OBJS_ROOT_=\
 clasp.api.$(OBJS_SUBS_SYM_).o\
 clasp.core.$(OBJS_SUBS_SYM_).o\
 clasp.diagnostics.$(OBJS_SUBS_SYM_).o\
 clasp.memory.$(OBJS_SUBS_SYM_).o\
 clasp.string.$(OBJS_SUBS_SYM_).o\
 clasp.usage.$(OBJS_SUBS_SYM_).o\
 clasp.usage.FILE.$(OBJS_SUBS_SYM_).o\
 \

OBJS_MSD=$(subst $(OBJS_SUBS_SYM_),$(OBJS_SYM_MSD_),$(OBJS_ROOT_))
OBJS_MSR=$(subst $(OBJS_SUBS_SYM_),$(OBJS_SYM_MSR_),$(OBJS_ROOT_))
OBJS_MMD=$(subst $(OBJS_SUBS_SYM_),$(OBJS_SYM_MMD_),$(OBJS_ROOT_))
OBJS_MMR=$(subst $(OBJS_SUBS_SYM_),$(OBJS_SYM_MMR_),$(OBJS_ROOT_))
OBJS_WSD=$(subst $(OBJS_SUBS_SYM_),$(OBJS_SYM_WSD_),$(OBJS_ROOT_))
OBJS_WSR=$(subst $(OBJS_SUBS_SYM_),$(OBJS_SYM_WSR_),$(OBJS_ROOT_))
OBJS_WMD=$(subst $(OBJS_SUBS_SYM_),$(OBJS_SYM_WMD_),$(OBJS_ROOT_))
OBJS_WMR=$(subst $(OBJS_SUBS_SYM_),$(OBJS_SYM_WMR_),$(OBJS_ROOT_))

OBJS=\
 $(OBJS_MSD)\
 $(OBJS_MSR)\
 $(OBJS_MMD)\
 $(OBJS_MMR)\
 $(OBJS_WSD)\
 $(OBJS_WSR)\
 $(OBJS_WMD)\
 $(OBJS_WMR)\
 \


build:\
	$(LIBS)\
	\

compile:\
	$(OBJS)\
	\

clean:
	@rm -f $(OBJS)
	@rm -f $(LIBS)

$(TARGET_LIB_CORE_MSD):	$(OBJS_MSD)
	@-if not exist $(PROJ_LIB_DIR) $(MKDIR) $(PROJ_LIB_DIR)
	$(AR) -crs $@ $^

$(TARGET_LIB_CORE_MSR):	$(OBJS_MSR)
	@-if not exist $(PROJ_LIB_DIR) $(MKDIR) $(PROJ_LIB_DIR)
	$(AR) -crs $@ $^

$(TARGET_LIB_CORE_MMD):	$(OBJS_MMD)
	@-if not exist $(PROJ_LIB_DIR) $(MKDIR) $(PROJ_LIB_DIR)
	$(AR) -crs $@ $^

$(TARGET_LIB_CORE_MMR):	$(OBJS_MMR)
	@-if not exist $(PROJ_LIB_DIR) $(MKDIR) $(PROJ_LIB_DIR)
	$(AR) -crs $@ $^

$(TARGET_LIB_CORE_WSD):	$(OBJS_WSD)
	@-if not exist $(PROJ_LIB_DIR) $(MKDIR) $(PROJ_LIB_DIR)
	$(AR) -crs $@ $^

$(TARGET_LIB_CORE_WSR):	$(OBJS_WSR)
	@-if not exist $(PROJ_LIB_DIR) $(MKDIR) $(PROJ_LIB_DIR)
	$(AR) -crs $@ $^

$(TARGET_LIB_CORE_WMD):	$(OBJS_WMD)
	@-if not exist $(PROJ_LIB_DIR) $(MKDIR) $(PROJ_LIB_DIR)
	$(AR) -crs $@ $^

$(TARGET_LIB_CORE_WMR):	$(OBJS_WMR)
	@-if not exist $(PROJ_LIB_DIR) $(MKDIR) $(PROJ_LIB_DIR)
	$(AR) -crs $@ $^

$(OBJS_MSD): %.$(OBJS_SYM_MSD_).o: %.c
	$(CC) -c $(CFLAGS_MSD) $< -o $@

$(OBJS_MSR): %.$(OBJS_SYM_MSR_).o: %.c
	$(CC) -c $(CFLAGS_MSR) $< -o $@

$(OBJS_MMD): %.$(OBJS_SYM_MMD_).o: %.c
	$(CC) -c $(CFLAGS_MMD) $< -o $@

$(OBJS_MMR): %.$(OBJS_SYM_MMR_).o: %.c
	$(CC) -c $(CFLAGS_MMR) $< -o $@

$(OBJS_WSD): %.$(OBJS_SYM_WSD_).o: %.c
	$(CC) -c $(CFLAGS_WSD) $< -o $@

$(OBJS_WSR): %.$(OBJS_SYM_WSR_).o: %.c
	$(CC) -c $(CFLAGS_WSR) $< -o $@

$(OBJS_WMD): %.$(OBJS_SYM_WMD_).o: %.c
	$(CC) -c $(CFLAGS_WMD) $< -o $@

$(OBJS_WMR): %.$(OBJS_SYM_WMR_).o: %.c
	$(CC) -c $(CFLAGS_WMR) $< -o $@


################################ end of file ###############################
