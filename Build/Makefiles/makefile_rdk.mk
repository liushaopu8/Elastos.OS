#==========================================================================
# Copyright (c) 2000-2007,  Elastos, Inc.  All Rights Reserved.
#==========================================================================

##########################################################################
#
# File:     $XDK/DevKit/misc/makefile.rdk
# Purpose:  Generic makefile (GNU version) for most Elastos projects
# Usage:    emake [ all | clean | clobber ]
#

##########################################################################
#
# Abstract:
#   This is the standard makefile for most components of Elastos project.
#   It includes the following files:
#   .\sources   -- developer supplies this file.
#                  It defines the required TARGET_NAME, TARGET_TYPE
#                  and SOURCES as well as optional macros that
#                  control the behavior of the compiler and linker.
#   .\dirs      -- specify sub directories to build recursively
#   .\makefile.inc -- specify extra makefile rules, targets and macros
#
# Targets:
#   all         -- Recursively builds all targets under the directory (default)
#   clean       -- Delete all targets generated by make of the directory
#   clobber     -- Erase ALL targets that can be produced by this build
#                  environment, ignoring errors
#
# Useful variables to set:
#   XDK_SOURCE_PATH  -- Elastos project root, set by $/DevKit/misc/setenv.bat
#   XDK_USER_OBJ     -- Tree for generated files
#   EXTERN_SDK       -- Hosting OS SDK, e.g., inc, lib, bin, etc.
#   EXTERN_BIN       -- Hosting OS tools, eg, VS60 compliler, linker etc.
#   EXTERN_INC       -- Header directory from hosting OS SDK, eg, GNUSDK
#   EXTERN_LIB       -- Lib directory from hosting OS SDK, eg, GNUSDK
#   RELEASE=1        -- Build release bits, default is to build debug bits
#   XDK_TARGET_CPU   -- Specify target CPU (x86,arm)
#   XDK_TARGET_BOARD -- Specify target borad (pc,gingko)
#   XDK_TARGET_PLATFORM -- Specify target run platform (win32,zener)
#   XDK_TARGET_FORMAT   -- Specify target object file format
#
MAKE_TARGETS= all clean

##########################################################################
#
# Build environment (where to find: src, inc, lib, tools, etc.)
#
ifndef XDK_ROOT
$(error !!You must set XDK_ROOT environment variable first (see setenv.bat)!!)
endif

ifndef XDK_MAKEFILE_PATH
XDK_MAKEFILE_PATH= $(XDK_BUILD_PATH)/Makefiles
endif

ifndef EXTERN_SDK
EXTERN_SDK= $(XDK_COMPILER_PATH)
endif

ifndef EXTERN_BIN
EXTERN_BIN= $(EXTERN_SDK)/bin
endif

#ifndef EXTERN_INC
#EXTERN_INC=
#endif

#ifndef EXTERN_LIB
#EXTERN_LIB=
#endif

ifneq "$(XDK_TARGET_PRODUCT)" "devtools"
ifeq "$(XDK_TARGET_PLATFORM)" "linux"
      PREBUILD_LIB = /usr/lib32
endif
ifndef CERTIFICATE_PATH
ifeq "$(XDK_TARGET_PLATFORM)" "android"
      XDK_CERTIFICATE_PATH = $(XDK_BUILD_PATH)/Prebuilt/JavaFramework/security
      XDK_SIGNAPK_JAR = $(XDK_BUILD_PATH)/Prebuilt/JavaFramework/signapk.jar
endif
endif
ifndef PREBUILD_PATH
ifeq "$(XDK_TARGET_PLATFORM)" "android"
      ifeq "$(XDK_TARGET_CPU)" "arm"
            PREBUILD_PATH = $(XDK_BUILD_PATH)/Prebuilt/Linux
      endif
      ifeq "$(XDK_TARGET_CPU)" "x86"
            PREBUILD_PATH = $(XDK_BUILD_PATH)/Prebuilt_x86/Linux
      endif
endif
ifndef PREBUILD_INC
      PREBUILD_INC = $(PREBUILD_PATH)/usr/include
endif
ifndef PREBUILD_LIB
      PREBUILD_LIB = $(PREBUILD_PATH)/usr/lib
endif
endif
endif

##########################################################################
#
# turn on verbose mode if "emake -v" was specified (which sets BUILD_VERBOSE=1)
#
ifeq "$(BUILD_VERBOSE)" ""			# verbose is on
  ifeq "$(XDK_COMPILER)" "gnu"
    C_FLAGS:= -s $(C_FLAGS)			# add --slient flags to gcc
  endif
  MAKE_FLAGS:= -s $(MAKE_FLAGS)		# add --slient flags to make
  BLACKHOLE= 1>/dev/null			# do not display stdout messages
endif

# -r disable the built-in implicit rules
# -R disable the built-in variable settings
MAKE_FLAGS:= -f$(XDK_MAKEFILE) --no-print-directory -r -R $(MAKE_FLAGS)

##########################################################################
#
# set XDK_TARGET_CPU, XDK_TARGET_BOARD before including DIRS, SOURCES
#
ifeq "$(XDK_TARGET_CPU)" ""
$(error !!You must set XDK_TARGET_CPU  first (see setenv.bat)!!)
endif

ifeq "$(XDK_TARGET_PLATFORM)" ""
$(error !!You must set XDK_TARGET_PLATFORM  first (see setenv.bat)!!)
endif

##########################################################################
#
# Set TARGET paths
#
ifndef TARGET_PATH
TARGET_PATH= $(XDK_USER_OBJ)/$(XDK_BUILD_KIND)
endif

ifeq "$(DEBUG_INFO)" "1"
ifndef TARGET_DBG_INFO_PATH
TARGET_DBG_INFO_PATH = $(XDK_TARGETS)/dbg_info
endif
endif


ifndef TARGET_OBJ_PATH
TARGET_OBJ_PATH = $(TARGET_PATH)/mirror$(XDK_EMAKE_DIR)
endif

ifndef TARGET_PACK_PATH
TARGET_PACK_PATH = $(XDK_TARGETS)/package
endif

MAKEDIR= $(XDK_SOURCE_PATH)$(XDK_EMAKE_DIR)

# SDK PATH
ifeq "$(XDK_BUILD_ENV)" "rdk"
TARGET_XSL_C_PATH= $(XDK_SOURCE_PATH)/Documents/References/Chinese/xsl/xsl_c
TARGET_XSL_E_PATH= $(XDK_SOURCE_PATH)/Documents/References/English/xsl/xsl_e
endif

# SYSTEM INCLUDE PATH
ifeq "$(XDK_TARGET_PRODUCT)" "devtools"
INCLUDES = .; $(XDK_USER_INC); \
          $(MAKEDIR);
endif
ifeq "$(XDK_TARGET_PLATFORM)" "linux"
INCLUDES = .; $(XDK_USER_INC); $(XDK_INC_PATH); \
          $(MAKEDIR);
endif
ifeq "$(XDK_TARGET_PLATFORM)" "android"
INCLUDES = .; $(PREBUILD_INC); $(XDK_USER_INC); $(XDK_INC_PATH); \
          $(MAKEDIR);
endif
SYSTEM_INCLUDES := $(INCLUDES)

#$(warning makefile_rdk)
#$(warning PREBUILD_INC=$(PREBUILD_INC))
#$(warning INCLUDES=$(INCLUDES))

# default C_FLAGS
ifeq "$(XDK_COMPILER)" "gnu"
C_FLAGS += -fno-exceptions
endif


##########################################################################
#
# Find sub dirs/files to build
#
ifneq "$(_EMK_ROOT)" ""
ifneq "$(wildcard $(MAKEDIR)/dirs_dailybuild)" ""
$(error $(MAKEDIR)/dirs)
-include $(MAKEDIR)/dirs
-include $(MAKEDIR)/dirs_dailybuild
else
-include $(MAKEDIR)/dirs
endif
else
ifneq "$(TEST_TYPE)" ""
ifneq "$(wildcard $(MAKEDIR)/dirs_dailybuild)" ""
-include $(MAKEDIR)/dirs
-include $(MAKEDIR)/dirs_dailybuild
else
-include $(MAKEDIR)/dirs
endif
else
-include $(MAKEDIR)/dirs
endif
endif
-include $(MAKEDIR)/sources
ifneq "$(findstring .car,$(SOURCES))" ""
CAR_SOURCES=$(filter %.car,$(SOURCES))
CAR_OBJECTS := $(CAR_SOURCES:.car=.mk)
endif
ifeq "$(CAR_OBJECT_DISABLE)" ""
ifneq "$(CAR_OBJECTS)" ""
-include $(TARGET_OBJ_PATH)/$(CAR_OBJECTS)
endif
endif
##########################################################################
#
# DIRS SOURCES
#
DIRS:= $(filter-out \,$(DIRS))
SOURCES:= $(filter-out \,$(SOURCES))

TARGET_NAME:= $(strip $(TARGET_NAME))
TARGET_TYPE:= $(strip $(TARGET_TYPE))

ifneq "$(TARGET_NAME)" ""
  TARGET:= $(TARGET_NAME)
  ifneq "$(TARGET_TYPE)" ""
    TARGET:= $(TARGET).$(TARGET_TYPE)
  endif
endif

-include $(XDK_MAKEFILE_PATH)/makedefs_internal.mk
include $(XDK_MAKEFILE_PATH)/makedefs_$(XDK_COMPILER)_$(XDK_BUILD_ENV).mk

#
# Make being invoked twice in the current directory and then walk down
# sub-trees recursively.  MAKECMD is not set the first time, so we only
# setenv once during the make process
#
ifndef MAKECMD

.PHONY: all md_target_dir rebuild clean clobber

default: all

all: md_target_dir
	+$(XDK_MAKE) make_car MAKECMD=make_car -C $(TARGET_OBJ_PATH) $(MAKE_FLAGS)
	+$(XDK_MAKE) $@ MAKECMD=$@ -C $(TARGET_OBJ_PATH) $(MAKE_FLAGS)

md_target_dir:
	$(call create_dir,$(XDK_TARGETS))
	$(call create_dir,$(XDK_USER_LIB))
	$(call create_dir,$(XDK_USER_INC))
	$(call create_dir,$(TARGET_OBJ_PATH))
	$(call create_dir,$(TARGET_PACK_PATH))
ifeq "$(DEBUG_INFO)" "1"
	$(call create_dir,$(TARGET_DBG_INFO_PATH))
endif

rebuild: clean all

clean:
	$(call remove_dir,$(TARGET_OBJ_PATH))
	@echo Clean done...

clobber:
	$(call remove_dir,$(TARGET_PATH))
	$(call remove_dir,$(XDK_TARGETS))
	@echo Clobber done...

else # ifndef MAKECMD

ifeq "$(XDK_COMPILER)" "gnu"
  include $(XDK_MAKEFILE_PATH)/makerules_gnu_$(XDK_BUILD_ENV).mk
else
  include $(XDK_MAKEFILE_PATH)/makerules_win_$(XDK_BUILD_ENV).mk
endif

##########################################################################

all: $(IMPORTHS) $(APPPCK_LABLE) $(DIRS) $(FIRST_TARGET) $(EXPORT_HEADERS) $(RESOURCES_OBJECTS)\
     depend.mk $(OBJECTS) $(TARGET) $(SPECIAL_TARGET)

make_car : $(CAR_OBJECTS)

##########################################################################
#
# Create target directories if not already present
# cd to next make directory to confirm whether it is exist
# cd to target obj directory to compile object files
#
always:
ifneq "$(DIRS)" ""
$(DIRS) : always
	@echo .
	@echo Building $(MAKEDIR)/$@
	$(call create_dir,$(TARGET_OBJ_PATH)/$@)
	+$(COMPILE_JUMPERR_FORTEST) $(XDK_MAKE) make_car -C $(MAKEDIR)/$@ -C '$(TARGET_OBJ_PATH)/$@' \
		XDK_EMAKE_DIR=$(XDK_EMAKE_DIR)/$@ $(MAKE_FLAGS)
	+$(COMPILE_JUMPERR_FORTEST) $(XDK_MAKE) $(MAKECMD) -C $(MAKEDIR)/$@ -C '$(TARGET_OBJ_PATH)/$@' \
		XDK_EMAKE_DIR=$(XDK_EMAKE_DIR)/$@ $(MAKE_FLAGS)
endif

ifneq "$(IMPORTHS)" ""
$(IMPORTHS):
	@echo Generating H files from $(@:.h=.eco)
	$(LUBE)  -C$(@:.h=.eco) -f -T header2 -T headercpp
endif

##########################################################################
#
# Custom defined makefile rules, targets and macros
#
ifeq "$(XDK_COMPILER)" "gnu"
-include $(MAKEDIR)/makefile.inc
ifeq "$(NODEPEND)" ""
-include $(TARGET_OBJ_PATH)/depend.mk
endif
endif
ifeq "$(XDK_COMPILER)" "msvc"
-include $(MAKEDIR)/makefile.inc
ifeq "$(NODEPEND)" ""
-include $(TARGET_OBJ_PATH)/depend.mk
endif
endif
endif # MAKECMD

##########################################################################
#
# Functions for directory manipulation
#

define remove_dir
  $(Q)if [ -d '$1' ]; then \
    $(RMDIR) '$1'; \
  fi
endef

define create_dir
  $(Q)if [ ! -d '$1' ]; then \
    $(MKDIR) '$1'; \
  fi
endef
