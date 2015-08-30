#Test code
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

### Compiler tools ###
C_COMPILER=gcc
C_LINKER=gcc
ARCHIVER=ar
CPP_COMPILER=g++
CPP_LINKER=g++

.DEFAULT_GOAL:=all
.PHONY: all test clean
.PHONY: dirlist

all:
	@echo MakefileCppUTest all

test:
	@echo MakefileCppUTest test

clean:
	@echo MakefileCppUTest clean

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
