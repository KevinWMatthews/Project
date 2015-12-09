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



################################
### Test directory structure ###
################################
TEST_DIR=$(call clean_path,$(MODULE_DIR))
TEST_TARGET_NAME=test_$(notdir $(MODULE_DIR))
TEST_TARGET=$(BUILD_DIR)/$(TEST_TARGET_NAME)
TEST_SRC_DIRS=$(TEST_DIR)/src
TEST_INC_DIRS=$(TEST_DIR)/inc
#If for some reason your tests have a library dependency, list it here
TEST_LIB_DIRS=
#Static library names without lib prefix and .a suffix
TEST_LIB_LIST=
#TEST_OBJ_DIR=$(OBJ_DIR)
#TEST_BUILD_DIR=$(BUILD_DIR)
#Production code is compiled into a library
PRODUCTION_LIB=$(BUILD_DIR)/$(addsuffix .a,$(addprefix lib,$(TARGET_NAME)))

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
TEST_SRC=$(call get_src_from_dir_list,$(TEST_SRC_DIRS))
CLEAN_TEST_SRC=$(call clean_path,$(TEST_SRC))
TEST_OBJ=$(addprefix $(OBJ_DIR)/,$(call src_to_o,$(CLEAN_TEST_SRC)))
TEST_DEP=$(addprefix $(OBJ_DIR)/,$(call src_to_d,$(CLEAN_TEST_SRC)))
TEST_INC=$(call get_inc_from_dir_list,$(TEST_INC_DIRS))
TEST_LIBS=$(addprefix lib,$(addsuffix .a,$(TEST_LIB_LIST)))

# CppUTest test harness source code
CPPUTEST_LIBS=$(addprefix lib,$(addsuffix .a,$(CPPUTEST_LIB_LIST)))

DEP_FILES=$(SRC_DEP) $(TEST_DEP)



############################
### Auto-generated flags ###
############################
# Production code
COMPILER_FLAGS+=-c -MMD -MP
ifeq ($(DEBUG),Y)
	COMPILER_FLAGS+=-g
endif
#This may move up to the launcher
INCLUDE_FLAGS+=$(addprefix -I,$(INC_DIRS))
LINKER_FLAGS+=$(addprefix -L,$(LIB_DIRS))
LINKER_FLAGS+=$(addprefix -l,$(LIB_LIST))

#Flags for user's unit tests written under CppUTest framework
ifeq ($DEBUG,Y)
	TEST_COMPILER_FLAGS+=-g
endif
TEST_INCLUDE_FLAGS+=$(addprefix -I,$(TEST_INC_DIRS))
#Link to any other libraries utilized by user tests
TEST_LINKER_FLAGS+=$(addprefix -L,$(TEST_LIB_DIR))
TEST_LINKER_FLAGS+=$(addprefix -l,$(TEST_LIB_LIST))
#Link to production source code library is included as a prerequisite in rule for building TEST_TARGET
# TEST_LINKER_FLAGS+=$(addprefix -L,$(TEST_BUILD_DIR))
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



######################
### Compiler tools ###
######################
C_COMPILER=gcc
C_LINKER=gcc
ARCHIVER=ar
CPP_COMPILER=g++
CPP_LINKER=g++



###############
### Targets ###
###############
.DEFAULT_GOAL:=all
.PHONY: all rebuild run compile clean
.PHONY: test
.PHONY: dirlist filelist flags


all: test

rebuild: clean all

clean:
	$(SILENCE)rm -rf $(OBJ_DIR)
	$(SILENCE)rm -rf $(BUILD_DIR)


### Test code rules ###
test: $(TEST_TARGET)
	$(ECHO) "\n${BoldRed}Executing $(notdir $<)...${BoldBlue}"
	$(ECHO)
	$(SILENCE)$(TEST_TARGET)
	$(ECHO) "\n${BoldGreen}...Tests executed!${NoColor}\n"

# Be SURE to link the test objects before the source code library!!
# This is what enables link-time substitution
$(TEST_TARGET): $(TEST_OBJ) $(PRODUCTION_LIB)
	$(ECHO) "\n${Yellow}Linking $(notdir $@)...${NoColor}"
	$(ECHO) "${DarkGray}Module test code${NoColor}"
	$(SILENCE)mkdir -p $(dir $@)
	$(SILENCE)$(CPP_LINKER) -o $@ $^ $(LINKER_FLAGS) $(TEST_LINKER_FLAGS) $(CPPUTEST_LINKER_FLAGS)

#Target source code library is placed in the test folder because the production build doesn't use it
$(PRODUCTION_LIB): $(SRC_OBJ)
	$(ECHO) "\n${Yellow}Archiving all production code into $(notdir $@)... ${NoColor}"
	$(SILENCE)mkdir -p $(dir $@)
	$(SILENCE)$(ARCHIVER) $(ARCHIVER_FLAGS) $@ $^

$(OBJ_DIR)/%.o: %.c
	$(ECHO) "\n${Yellow}Compiling $(notdir $<)...${NoColor}"
	$(SILENCE)mkdir -p $(dir $@)
	$(ECHO) "${DarkGray}Module production code${NoColor}"
	$(SILENCE)$(C_COMPILER) $(COMPILER_FLAGS) $< -o $@ $(INCLUDE_FLAGS) $(TEST_INCLUDE_FLAGS)

$(OBJ_DIR)/%.o: %.cpp
	@echo
	$(ECHO) "\n${Yellow}Compiling $(notdir $<)...${NoColor}"
	$(SILENCE)mkdir -p $(dir $@)
	$(ECHO) "${DarkGray}Module test code${NoColor}"
	$(SILENCE)$(CPP_COMPILER) $(COMPILER_FLAGS) $< -o $@ $(INCLUDE_FLAGS) $(TEST_INCLUDE_FLAGS)


filelist:
	$(ECHO) "\n${BoldCyan}Directory of MakefileCppUTest.make:${NoColor}"
	$(ECHO) "$(shell pwd)\n"

	$(ECHO) "\n${BoldCyan}All Dependencies:${NoColor}"
	$(call echo_with_header,DEP_FILES)

	$(ECHO) "\n${BoldCyan}Production code:${NoColor}"
	$(call echo_with_header,SRC)
	$(call echo_with_header,CLEAN_SRC)
	$(call echo_with_header,SRC_OBJ)
	$(call echo_with_header,SRC_DEP)
	$(call echo_with_header,INC)
	$(call echo_with_header,LIBS)

	$(ECHO) "\n${BoldCyan}Test code:${NoColor}"
	$(call echo_with_header,PRODUCTION_LIB)
	$(call echo_with_header,TEST_TARGET_NAME)
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
	$(ECHO) "\n${BoldCyan}Test code:${NoColor}"
	$(call echo_with_header,TEST_DIR)
	$(call echo_with_header,TEST_SRC_DIRS)
	$(call echo_with_header,TEST_INC_DIRS)
	$(call echo_with_header,TEST_LIB_DIRS)
	$(call echo_with_header,TEST_LIB_LIST)
#	$(call echo_with_header,TEST_OBJ_DIR)
#	$(call echo_with_header,TEST_BUILD_DIR)
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
