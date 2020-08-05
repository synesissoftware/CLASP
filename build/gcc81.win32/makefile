############################################################################
# File: 	makefile
#
# Purpose:	Makefile for the SystemTools::CLASP project,
#           for the GCC 8.1 compiler,
#           on Win32
#
# Created:	16th October 2019
# Updated:	3rd August 2020
#
############################################################################


############################################################################
# environment check
#
# * to build without recls support make with the symbol CLASP_NO_RECLS
#   defined, e.g. "> make CLASP_NO_RECLS=1 build"

ifndef CLASP_NO_RECLS
ifndef RECLS_ROOT
$(error RECLS_ROOT must be defined)
endif # !RECLS_ROOT
endif # !CLASP_NO_RECLS

############################################################################
# pseudo-targets

############################################################################
# symbols

########################################
# project & compiler version

COMP_TAG = gcc81
ARCH_TAG =	
OS_TAG = 
PROJ_TAG = systemtools.clasp
PROJ_VER_MAJOR = 0

########################################
# testing verbosity

TEST_VERBOSITY = 2

########################################
# directories

PROJ_ROOT_DIR = ../..
PROJ_INC_DIR = $(PROJ_ROOT_DIR)/include
PROJ_SRC_DIR = $(PROJ_ROOT_DIR)/src
PROJ_LIB_DIR = $(PROJ_ROOT_DIR)/lib
PROJ_BIN_DIR = $(PROJ_ROOT_DIR)/bin

vpath %.c $(PROJ_SRC_DIR)
vpath %.h $(PROJ_SRC_DIR)

########################################
# tools

AR		=	ar
CC		=	gcc

CP		=	cp
MKDIR	=	mkdir -p
MV		=	mv
RM		=	rm -f

CLASP_CC_COMMON_INCLUDES=
CLASP_CC_COMMON_INCLUDES+=-I $(PROJ_INC_DIR)
ifndef CLASP_NO_RECLS
CLASP_CC_COMMON_INCLUDES+=-I "$(RECLS_ROOT)/include"
endif # !CLASP_NO_RECLS

CLASP_CC_COMMON_DEFINES=
CLASP_CC_COMMON_DEFINES+=-DWIN32
ifdef CLASP_NO_RECLS
CLASP_CC_COMMON_DEFINES+=-DCLASP_CMDLINE_ARGS_NO_RECLS_ON_WINDOWS
endif # CLASP_NO_RECLS

CLASP_CC_COMMON_FLAGS=
CLASP_CC_COMMON_FLAGS+=-Wall
CLASP_CC_COMMON_FLAGS+=-Werror
CLASP_CC_COMMON_FLAGS+=-Wno-unused-but-set-variable
CLASP_CC_COMMON_FLAGS+=-Wno-unused-function
CLASP_CC_COMMON_FLAGS+=-Wno-unused-variable

CLASP_CC_COMMON_CFLAGS =\
 $(CLASP_CC_COMMON_INCLUDES)\
 $(CLASP_CC_COMMON_DEFINES)\
 $(CLASP_CC_COMMON_FLAGS)\
 \

CFLAGS_CC_COMMON_CFLAGS_DEBUG =\
 $(CLASP_CC_COMMON_CFLAGS)\
 -D_DEBUG\
 -DDEBUG\
 \

CFLAGS_CC_COMMON_CFLAGS_RELEASE =\
 $(CLASP_CC_COMMON_CFLAGS)\
 -DNDEBUG\
 \

CFLAGS_ST_=-DUSE_THREAD=0 -DUSE_OPENMP=0
CFLAGS_MT_=-D_REENTRANT -DUSE_THREAD=1 -DUSE_OPENMP=1

CFLAGS_MSD = $(CFLAGS_CC_COMMON_CFLAGS_DEBUG)   $(CFLAGS_ST_)
CFLAGS_MSR = $(CFLAGS_CC_COMMON_CFLAGS_RELEASE) $(CFLAGS_ST_)
CFLAGS_MMD = $(CFLAGS_CC_COMMON_CFLAGS_DEBUG)   $(CFLAGS_MT_)
CFLAGS_MMR = $(CFLAGS_CC_COMMON_CFLAGS_RELEASE) $(CFLAGS_MT_)

########################################
# symbols

# configurations:
#
# 0 : multibyte / wide          :   M / W
# 1 : single / multi / dll      :   S / M / D
# 2 : debug / release / test    :   D / M / T   => NOTE: Test not currently provided
# 

TARGET_LIB_CORE_ROOT_ = libsystemtools.clasp.0.core

TARGET_LIB_CORE_MSD = $(PROJ_LIB_DIR)/$(TARGET_LIB_CORE_ROOT_).$(COMP_TAG).debug.a
TARGET_LIB_CORE_MSR = $(PROJ_LIB_DIR)/$(TARGET_LIB_CORE_ROOT_).$(COMP_TAG).a
TARGET_LIB_CORE_MMD = $(PROJ_LIB_DIR)/$(TARGET_LIB_CORE_ROOT_).$(COMP_TAG).mt.debug.a
TARGET_LIB_CORE_MMR = $(PROJ_LIB_DIR)/$(TARGET_LIB_CORE_ROOT_).$(COMP_TAG).mt.a

LIBS=\
 $(TARGET_LIB_CORE_MSD)\
 $(TARGET_LIB_CORE_MSR)\
 $(TARGET_LIB_CORE_MMD)\
 $(TARGET_LIB_CORE_MMR)\
 \

OBJS_SUBS_SYM_=__CONFIGURATION__
OBJS_SYM_MSD_=msd
OBJS_SYM_MSR_=msr
OBJS_SYM_MMD_=mmd
OBJS_SYM_MMR_=mmr

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

OBJS=\
 $(OBJS_MSD)\
 $(OBJS_MSR)\
 $(OBJS_MMD)\
 $(OBJS_MMR)\
 \


build:\
	$(LIBS)\
	\

compile:\
	$(OBJS)\
	\

clean:
	@$(RM) $(OBJS)
	@$(RM) $(LIBS)

$(TARGET_LIB_CORE_MSD):	$(OBJS_MSD)
	@$(MKDIR) $(PROJ_LIB_DIR)
	$(AR) -crs $@ $^

$(TARGET_LIB_CORE_MSR):	$(OBJS_MSR)
	@$(MKDIR) $(PROJ_LIB_DIR)
	$(AR) -crs $@ $^

$(TARGET_LIB_CORE_MMD):	$(OBJS_MMD)
	@$(MKDIR) $(PROJ_LIB_DIR)
	$(AR) -crs $@ $^

$(TARGET_LIB_CORE_MMR):	$(OBJS_MMR)
	@$(MKDIR) $(PROJ_LIB_DIR)
	$(AR) -crs $@ $^

$(OBJS_MSD): %.$(OBJS_SYM_MSD_).o: %.c
	$(CC) -c $(CFLAGS_MSD) $< -o $@

$(OBJS_MSR): %.$(OBJS_SYM_MSR_).o: %.c
	$(CC) -c $(CFLAGS_MSR) $< -o $@

$(OBJS_MMD): %.$(OBJS_SYM_MMD_).o: %.c
	$(CC) -c $(CFLAGS_MMD) $< -o $@

$(OBJS_MMR): %.$(OBJS_SYM_MMR_).o: %.c
	$(CC) -c $(CFLAGS_MMR) $< -o $@

################################ end of file ###############################

