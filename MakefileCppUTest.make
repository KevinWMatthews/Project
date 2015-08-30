# This makefile compiles all production code into a library.
# It then compiles and links all unit tests, using link-time substitution to override production files as needed.

# All source code should be auto-detected if the given directory structure is correct.

ifndef DEBUG
	DEBUG=Y
endif

### Generate and set flags ###
##User-entered flags
#Flags for user's unit tests written under CppUTest framework
TEST_COMPILER_FLAGS=
TEST_INCLUDE_FLAGS=
TEST_LINKER_FLAGS=

#Flags for CppUTest framework's source code
#(not the user's unit tests; the test framework itself)
CPPUTEST_LINKER_FLAGS=


##Auto-generated flags
# Production code
COMPILER_FLAGS+=-c -MMD -MP
ifeq ($(DEBUG),Y)
	COMPILER_FLAGS+=-g
endif
INCLUDE_FLAGS=$(addprefix -I,$(INC_DIRS))
LINKER_FLAGS=$(addprefix -L,$(LIB_DIRS))
LINKER_FLAGS+=$(addprefix -l,$(LIB_LIST))

#Flags for user's unit tests written under CppUTest framework
ifeq ($DEBUG,Y)
	TEST_COMPILER_FLAGS+=-g
endif
TEST_INCLUDE_FLAGS+=$(addprefix -I,$(TEST_INC_DIR))
#Link to any other libraries utilized by user tests
TEST_LINKER_FLAGS+=$(addprefix -L,$(TEST_LIB_DIR))
TEST_LINKER_FLAGS+=$(addprefix -l,$(TEST_LIB_LIST))
#Link to production source code library is included as a prerequisite in rule for building TEST_TARGET
# TEST_LINKER_FLAGS+=$(addprefix -L,$(TEST_TARGET_DIR))
# TEST_LINKER_FLAGS+=$(addprefix -l,$(TARGET_NAME))

#Flags for CppUTest framework's source code
#(not the user's unit tests; the test framework itself)
CPPUTEST_LINKER_FLAGS+=$(addprefix -l,$(CPPUTEST_LIB_LIST))
ifeq ("$(OSTYPE)","Cygwin")
CPPUTEST_LINKER_FLAGS+=$(addprefix -L,$(CPPUTEST_LIB_DIR))
endif

#Flags for archive tool
ifdef SILENCE
	ARCHIVER_FLAGS=rcs
else
	ARCHIVER_FLAGS=rcvs
endif



################################
### Test directory structure ###
################################
#If for some reason your tests have a library dependency, list it here
TEST_LIB_DIRS=
#Static library names without lib prefix and .a suffix
TEST_LIB_LIST=
TEST_TARGET_NAME=test_$(notdir $(MODULE_DIR))
TEST_DIR=$(MODULE_DIR)/test
TEST_SRC_DIRS=$(TEST_DIR)/src
TEST_INC_DIRS=$(TEST_DIR)/inc
TEST_OBJ_DIR=$(TEST_DIR)/obj
TEST_TARGET_DIR=$(TEST_DIR)/build
#PRODUCTION_LIB_DIR=$(TEST_ROOT_DIR)/build

# CppUTest test harness source code
CPPUTEST_LIB_LIST=CppUTest CppUTestExt
OSTYPE:=$(shell uname -o)
ifeq ("$(OSTYPE)","Cygwin")
# Cygwin's linker can't seem to find CppUTest libraries even though they're in the PATH...
CPPUTEST_LIB_DIR=/usr/local/lib
endif


include make_helper_functions

#########################################################
### Auto-detect source code and generate object files ###
#########################################################
# Production source code
SRC=$(call get_src_from_dir_list,$(SRC_DIRS))
CLEAN_SRC=$(call clean_path,$(SRC))
SRC_OBJ=$(addprefix $(OBJ_DIR)/,$(call src_to_o,$(CLEAN_SRC)))
SRC_DEP=$(addprefix $(OBJ_DIR)/,$(call src_to_d,$(CLEAN_SRC)))
INC=$(call get_inc_from_dir_list,$(INC_DIRS))
LIBS=$(addprefix lib,$(addsuffix .a,$(LIB_LIST)))

# Test code using CppUTest test harness
# User unit tests
TEST_TARGET=$(TEST_TARGET_DIR)/$(TEST_TARGET_NAME)_test
#Production code is compiled into a library
PRODUCTION_LIB=$(PRODUCTION_LIB_DIR)/$(addsuffix .a,$(addprefix lib,$(TARGET_NAME)))

TEST_SRC=$(call get_src_from_dir_list,$(TEST_SRC_DIRS))
CLEAN_TEST_SRC=$(call clean_path,$(TEST_SRC))
TEST_OBJ=$(addprefix $(TEST_OBJ_DIR)/,$(call src_to_o,$(CLEAN_TEST_SRC)))
TEST_DEP=$(addprefix $(TEST_OBJ_DIR)/,$(call src_to_d,$(CLEAN_TEST_SRC)))
TEST_INC=$(call get_inc_from_dir,$(TEST_INC_DIR))
TEST_LIBS=$(addprefix lib,$(addsuffix .a,$(TEST_LIB_LIST)))

# CppUTest test harness source code
CPPUTEST_LIBS=$(addprefix lib,$(addsuffix .a,$(CPPUTEST_LIB_LIST)))

DEP_FILES=$(SRC_DEP) $(TEST_DEP)

### Helper functions ###
get_subdirs = $(patsubst %/,%,$(sort $(dir $(wildcard $1*/))))
get_src_from_dir = $(wildcard $1/*.c) $(wildcard $1/*.cpp)
get_src_from_dir_list = $(foreach dir, $1, $(call get_src_from_dir,$(dir)))
get_inc_from_dir = $(wildcard $1/*.h)
get_inc_from_dir_list = $(foreach dir, $1, $(call get_inc_from_dir,$(dir)))
remove_dotdot=$(patsubst ../%,%,$1)
remove_dot=$(patsubst ./%,%,$1)
#Hahaha, need to loop this for as many subdirectories as we're going to support
#There must be a better way ;)
clean_path=$(call remove_dot,$(call remove_dotdot,$(call remove_dotdot,$(call remove_dotdot,$1))))
#nest calls so we don't get a repetition of .c and .cpp files
src_to=$(patsubst %.c,%$1,$(patsubst %.cpp,%$1,$2))
src_to_o=$(call src_to,.o,$1)
src_to_d=$(call src_to,.d,$1)




######################
### Compiler tools ###
######################
C_COMPILER=gcc
C_LINKER=gcc
ARCHIVER=ar
CPP_COMPILER=g++
CPP_LINKER=g++

.DEFAULT_GOAL:=all
.PHONY: all test clean
.PHONY: dirlist flags

all:
	@echo MakefileCppUTest all

test:
	@echo MakefileCppUTest test

clean:
	@echo MakefileCppUTest clean

filelist:
	$(ECHO) "\n${BoldCyan}Directory of MakefileWorker.make:${NoColor}"
	$(ECHO) "$(shell pwd)\n"

	$(call echo_with_header,TARGET,$(TARGET))

	$(ECHO) "\n${BoldCyan}All Dependencies:${NoColor}"
	$(call echo_with_header,DEP_FILES)

	$(ECHO) "\n${BoldCyan}Production code:${NoColor}"
	$(call echo_with_header,SRC)
	$(call echo_with_header,SRC_OBJ)
	$(call echo_with_header,SRC_DEP)
	$(call echo_with_header,INC)
	$(call echo_with_header,LIBS)

	$(ECHO) "\n${BoldCyan}Test code:${NoColor}"
	$(call echo_with_header,PRODUCTION_LIB)
	$(call echo_with_header,TEST_TARGET)
	$(call echo_with_header,TEST_SRC)
	$(call echo_with_header,TEST_OBJ)
	$(call echo_with_header,TEST_DEP)
	$(call echo_with_header,TEST_INC)
	$(call echo_with_header,TEST_LIBS)

	$(ECHO) "\n${BoldCyan}CppUTest code:${NoColor}"
	$(call echo_with_header,CPPUTEST_LIBS,$(CPPUTEST_LIBS))
	@echo

dirlist:
	$(call echo_with_header,TEST_DIR)
	$(call echo_with_header,TEST_SRC_DIRS)
	$(call echo_with_header,TEST_INC_DIRS)
	$(call echo_with_header,TEST_LIB_DIRS)
	$(call echo_with_header,TEST_LIB_LIST)
	$(call echo_with_header,TEST_OBJ_DIR)
	$(call echo_with_header,TEST_TARGET_DIR)
	$(call echo_with_header,TEST_TARGET_NAME)
	$(call echo_with_header,CPPUTEST_LIB_LIST)
	$(call echo_with_header,CPPUTEST_LIB_DIR)
	@echo

flags:
	$(call echo_with_header,COMPILER_FLAGS)
	$(call echo_with_header,INCLUDE_FLAGS)
	$(call echo_with_header,LINKER_FLAGS)
	$(call echo_with_header,TEST_COMPILER_FLAGS)
	$(call echo_with_header,TEST_INCLUDE_FLAGS)
	$(call echo_with_header,TEST_LINKER_FLAGS)
	$(call echo_with_header,CPPUTEST_LINKER_FLAGS)
	$(call echo_with_header,ARCHIVER_FLAGS)
	@echo
