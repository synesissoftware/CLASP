############################################################################
# File: 	makefile
#
# Purpose:	Makefile for the CLASP project,
#           for the GCC 4.2 compiler,
#           on UNIX
#
# Created:	4th June 2008
# Updated:	5th August 2020
#
############################################################################


############################################################################
# Environment check
#

############################################################################
# Pseudo-targets

############################################################################
# Symbols

########################################
# Project & compiler version

COMP_TAG = gcc42
ARCH_TAG =	
OS_TAG = unix
PROJ_TAG = systemtools.clasp
PROJ_VER_MAJOR = 0

########################################
# Testing verbosity

TEST_VERBOSITY = 2

########################################
# Directories

PROJ_ROOT_DIR = ../..
PROJ_INC_DIR = $(PROJ_ROOT_DIR)/include
PROJ_SRC_DIR = $(PROJ_ROOT_DIR)/src
PROJ_LIB_DIR = $(PROJ_ROOT_DIR)/lib
PROJ_BIN_DIR = $(PROJ_ROOT_DIR)/bin

vpath %.c $(PROJ_SRC_DIR)
vpath %.h $(PROJ_SRC_DIR)

########################################
# tools

CFLAGS = -I $(PROJ_INC_DIR) -DUNIX -Dunix -Wall -Werror -Wno-unused-function -Wno-unused-variable
CFLAGS_MSD = $(CFLAGS) -DDEBUG
CFLAGS_MSR = $(CFLAGS) -DNDEBUG
CFLAGS_MMD = $(CFLAGS_MSD) -D_REENTRANT
CFLAGS_MMR = $(CFLAGS_MSR) -D_REENTRANT

########################################
# symbols

# configurations:
#
# 0 : multibyte / wide          :   M / W
# 1 : single / multi / dll      :   S / M / D
# 2 : debug / release / test    :   D / M / T   => NOTE: Test not currently provided
# 

TARGET_LIB_CORE_ROOT_ = lib$(PROJ_TAG).0.core

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
	@rm -f $(OBJS)
	@rm -f $(LIBS)

$(TARGET_LIB_CORE_MSD):	$(OBJS_MSD)
	@mkdir -p $(PROJ_LIB_DIR)
	$(AR) -crs $@ $^

$(TARGET_LIB_CORE_MSR):	$(OBJS_MSR)
	@mkdir -p $(PROJ_LIB_DIR)
	$(AR) -crs $@ $^

$(TARGET_LIB_CORE_MMD):	$(OBJS_MMD)
	@mkdir -p $(PROJ_LIB_DIR)
	$(AR) -crs $@ $^

$(TARGET_LIB_CORE_MMR):	$(OBJS_MMR)
	@mkdir -p $(PROJ_LIB_DIR)
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
