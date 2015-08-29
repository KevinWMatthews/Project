#This makefile defines the directory structure and then launches the appropriate sub-makefile

##################################
### Define directory structure ###
##################################
ROOT_DIR=.



#Production code
#TARGET_NAME Passed into this makefile
#MODULE_DIR  Passed into this makefile
include $(MODULE_DIR)/make_module_config.make
#SRC_DIRS    User-configured in make_module_conig
#INC_DIRS    User-configured in make_module_conig
#LIB_DIRS    User-configured in make_module_conig
#LIB_LIST    User-configured in make_module_conig
OBJ_DIR=$(MODULE_DIR)/obj
TARGET_DIR=$(MODULE_DIR)/build

#Test code
#If for some reason your tests have a library dependency, list it here
TEST_LIB_DIRS=
#Static library names without lib prefix and .a suffix
TEST_LIB_LIST=
TEST_TARGET_NAME=test_$(TARGET_NAME)
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



### Targets ###
.PHONY: all test production
.PHONY: dirlist

all clean:
	$(LAUNCH_MAKE) MakefileCppUTest.make
	$(LAUNCH_MAKE) MakefileProduction.make

test:
	$(LAUNCH_MAKE) MakefileCppUTest.make

production:
	$(LAUNCH_MAKE) MakefileProduction.make


dirlist:
	@echo "~~~ Directory structure ~~~"
	@echo "Production code:"
	@echo ROOT_DIR: $(ROOT_DIR)
	@echo MODULE_DIR: $(MODULE_DIR)
	@echo SRC_DIRS: $(SRC_DIRS)
	@echo INC_DIRS: $(INC_DIRS)
	@echo LIB_DIRS: $(LIB_DIRS)
	@echo LIB_LIST: $(LIB_LIST)
	@echo OBJ_DIR: $(OBJ_DIR)
	@echo TARGET_DIR: $(TARGET_DIR)
	@echo TARGET_NAME: $(TARGET_NAME)
	@echo
	@echo "Test code:"
	@echo TEST_DIR: $(TEST_DIR)
	@echo TEST_SRC_DIRS: $(TEST_SRC_DIRS)
	@echo TEST_INC_DIRS: $(TEST_INC_DIRS)
	@echo TEST_LIB_DIRS: $(TEST_LIB_DIRS)
	@echo TEST_LIB_LIST: $(TEST_LIB_LIST)
	@echo TEST_OBJ_DIR: $(TEST_OBJ_DIR)
	@echo TEST_TARGET_DIR: $(TEST_TARGET_DIR)
	@echo TEST_TARGET_NAME: $(TEST_TARGET_NAME)
	@echo
	@echo "CppUTest code:"
	@echo CPPUTEST_LIB_LIST: $(CPPUTEST_LIB_LIST)
	@echo CPPUTEST_LIB_DIR: $(CPPUTEST_LIB_DIR)
	@echo


### Helpers ###
LAUNCH_MAKE=make $(MAKECMDGOALS) --file
