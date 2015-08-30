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



#"test" echo; used for checking makefile parameters
ECHO=@echo -e
echo_with_header=$(ECHO) "${BoldPurple}  $1:${NoColor}"; echo $2; echo;


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
	$(call echo_with_header,DEP_FILES,$(DEP_FILES))

	$(ECHO) "\n${BoldCyan}Production code:${NoColor}"
	$(call echo_with_header,SRC,$(SRC))
	$(call echo_with_header,SRC_OBJ,$(SRC_OBJ))
	$(call echo_with_header,SRC_DEP,$(SRC_DEP))
	$(call echo_with_header,INC,$(INC))
	$(call echo_with_header,LIBS,$(LIBS))

	$(ECHO) "\n${BoldCyan}Test code:${NoColor}"
	$(call echo_with_header,PRODUCTION_LIB,$(PRODUCTION_LIB))
	$(call echo_with_header,TEST_TARGET,$(TEST_TARGET))
	$(call echo_with_header,TEST_SRC,$(TEST_SRC))
	$(call echo_with_header,TEST_OBJ,$(TEST_OBJ))
	$(call echo_with_header,TEST_DEP,$(TEST_DEP))
	$(call echo_with_header,TEST_INC,$(TEST_INC))
	$(call echo_with_header,TEST_LIBS,$(TEST_LIBS))

	$(ECHO) "\n${BoldCyan}CppUTest code:${NoColor}"
	$(call echo_with_header,CPPUTEST_LIBS,$(CPPUTEST_LIBS))

dirlist:
	@echo TEST_DIR: $(TEST_DIR)
	@echo TEST_SRC_DIRS: $(TEST_SRC_DIRS)
	@echo TEST_INC_DIRS: $(TEST_INC_DIRS)
	@echo TEST_LIB_DIRS: $(TEST_LIB_DIRS)
	@echo TEST_LIB_LIST: $(TEST_LIB_LIST)
	@echo TEST_OBJ_DIR: $(TEST_OBJ_DIR)
	@echo TEST_TARGET_DIR: $(TEST_TARGET_DIR)
	@echo TEST_TARGET_NAME: $(TEST_TARGET_NAME)
	@echo
	@echo CPPUTEST_LIB_LIST: $(CPPUTEST_LIB_LIST)
	@echo CPPUTEST_LIB_DIR: $(CPPUTEST_LIB_DIR)
	@echo

flags:
	@echo COMPILER_FLAGS: $(COMPILER_FLAGS)
	@echo INCLUDE_FLAGS: $(INCLUDE_FLAGS)
	@echo LINKER_FLAGS: $(LINKER_FLAGS)
	@echo TEST_COMPILER_FLAGS: $(TEST_COMPILER_FLAGS)
	@echo TEST_INCLUDE_FLAGS: $(TEST_INCLUDE_FLAGS)
	@echo TEST_LINKER_FLAGS: $(TEST_LINKER_FLAGS)
	@echo CPPUTEST_LINKER_FLAGS: $(CPPUTEST_LINKER_FLAGS)
	@echo ARCHIVER_FLAGS: $(ARCHIVER_FLAGS)


### Color codes ###
Blue       =\033[0;34m
BoldBlue   =\033[1;34m
Gray       =\033[0;37m
DarkGray   =\033[1;30m
Green      =\033[0;32m
BoldGreen  =\033[1;32m
Cyan       =\033[0;36m
BoldCyan   =\033[1;36m
Red        =\033[0;31m
BoldRed    =\033[1;31m
Purple     =\033[0;35m
BoldPurple =\033[1;35m
Yellow     =\033[0;33m
BoldYellow =\033[1;33m
BoldWhite  =\033[1;37m
NoColor    =\033[0;0m
NC         =\033[0;0m
