# This makefile compiles all production code into a library.
# It then compiles and links all unit tests, using link-time substitution to override production files as needed.

# All source code should be auto-detected if the given directory structure is correct.

ifndef DEBUG
	DEBUG=Y
endif

##############################
### Generate and set flags ###
##############################



######################
### Compiler tools ###
######################
C_COMPILER=gcc
C_LINKER=gcc
ARCHIVER=ar
CPP_COMPILER=g++
CPP_LINKER=g++


#############################
###                       ###
### Auto-generated values ###
###                       ###
#############################


###################
### Directories ###
###################
MODULE_DIR=$(call clean_path,$(ROOT_DIR)/$(MODULE))
OBJ_DIR=$(call clean_path,$(ROOT_DIR)/$(test_obj_dir))
BUILD_DIR=$(call clean_path,$(ROOT_DIR)/$(test_build_dir))


###############
### Targets ###
###############
TEST_TARGET_NAME=test_$(notdir $(MODULE_DIR))
TEST_TARGET=$(BUILD_DIR)/$(TEST_TARGET_NAME)
#Production code is compiled into a library
PRODUCTION_LIB=$(BUILD_DIR)/$(addsuffix .a,$(addprefix lib,$(TARGET_NAME)))

#######################################
### Auto-detect production source code
#######################################
dirty_mockhw_src=$(call get_src_from_dir,$(MOCKHW_DIR)/avr)
dirty_mockhw_inc=$(call get_inc_from_dir,$(MOCKHW_DIR)/avr)
MOCKHW_SRC=$(call clean_path, $(dirty_mockhw_src))
MOCKHW_INC=$(call clean_path, $(dirty_mockhw_inc))


#############################
### Generate object files ###
#############################
SRC_OBJ=$(addprefix $(OBJ_DIR)/,$(call src_to_o,$(SRC)))
SRC_DEP=$(addprefix $(OBJ_DIR)/,$(call src_to_d,$(SRC)))

MOCKHW_SRC_OBJ=$(addprefix $(OBJ_DIR)/,$(call src_to_o,$(MOCKHW_SRC)))
MOCKHW_SRC_DEP=$(addprefix $(OBJ_DIR)/,$(call src_to_d,$(MOCKHW_SRC)))

SRC_OBJ+=$(MOCKHW_SRC_OBJ)
SRC_DEP+=$(MOCKHW_SRC_DEP)

INC+=$(MOCKHW_INC)



########################
### Test Directories ###
########################
TEST_SRC_DIRS=$(MODULE_DIR)/src
TEST_INC_DIRS=$(MODULE_DIR)/inc
TEST_OBJ_DIR=$(OBJ_DIR)/CppUTest



#############################
### CppUTest test harness ###
#############################
CPPUTEST_LIB_LIST=CppUTest CppUTestExt
OSTYPE:=$(shell uname -o)
ifeq ("$(OSTYPE)","Cygwin")
# Cygwin's linker can't seem to find CppUTest libraries even though they're in the PATH...
CPPUTEST_LIB_DIR=/usr/local/lib
endif

# CppUTest test harness source code
CPPUTEST_LIBS=$(addprefix lib,$(addsuffix .a,$(CPPUTEST_LIB_LIST)))



##############################################################
### Auto-detect test source code and generate object files ###
##############################################################
# User unit tests
dirty_test_src=$(call get_src_from_dir_list,$(TEST_SRC_DIRS))
#I don't think that this step is needed
TEST_SRC=$(call clean_path,$(dirty_test_src))
TEST_OBJ=$(addprefix $(TEST_OBJ_DIR)/,$(call src_to_o,$(TEST_SRC)))
TEST_DEP=$(addprefix $(TEST_OBJ_DIR)/,$(call src_to_d,$(TEST_SRC)))
TEST_INC=$(call get_inc_from_dir_list,$(TEST_INC_DIRS))
TEST_LIBS=$(addprefix lib,$(addsuffix .a,$(TEST_LIB_LIST)))

DEP_FILES=$(SRC_DEP) $(TEST_DEP)



include make_helper_functions
include make_colors



############################
### Auto-generated flags ###
############################
# Production code
COMPILER_FLAGS+=-c -MMD -MP -DCPPUTEST
ifeq ($(DEBUG),Y)
	COMPILER_FLAGS+=-g
endif
COMPILER_FLAGS+=$(TEST_COMPILER_FLAGS)

INCLUDE_FLAGS+=$(addprefix -I,$(INC_DIRS))
INCLUDE_FLAGS+=$(addprefix -I,$(MOCKHW_DIR))

LINKER_FLAGS+=$(addprefix -L,$(LIB_DIRS))
LINKER_FLAGS+=$(addprefix -l,$(LIB_LIST))

# User unit tests
TEST_INCLUDE_FLAGS=$(addprefix -I,$(TEST_INC_DIRS))

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



###############
### Targets ###
###############
.DEFAULT_GOAL:=all
.PHONY: all compile clean rebuild help
.PHONY: test run
.PHONY: dirlist filelist flags
.PHONY: shallow_clean


all: test

module: test

rebuild: clean all

compile: $(TEST_TARGET)

run: compile
	$(TEST_TARGET)

clean:
	$(ECHO) "${Yellow}Removing all CppUTest objects and directories for module $(MODULE)...${NoColor}"
	$(SILENCE)$(REMOVE) $(OBJ_DIR)
	$(SILENCE)$(REMOVE) $(BUILD_DIR)
	$(ECHO) "${Green}...Module clean finished!${NoColor}\n"

shallow_clean:
	$(ECHO) "${Yellow}Cleaning CppUTest files for module $(MODULE)...${NoColor}"
	@echo
	$(ECHO) "${Yellow}Cleaning Production code files...${NoColor}"
	$(SILENCE)$(REMOVE) $(PRODUCTION_LIB) $(dir $(SRC_OBJ))
	$(ECHO) "${Green}...Clean finished!${NoColor}\n"
	$(ECHO) "${Yellow}Cleaning Test code files...${NoColor}"
	$(SILENCE)$(REMOVE) $(TEST_TARGET) $(TEST_OBJ_DIR)/$(MODULE_DIR)
	$(ECHO) "${Green}...Clean finished!${NoColor}\n"
	$(ECHO) "${Green}...Module clean finished!${NoColor}\n"

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
	$(SILENCE)$(CPP_LINKER) -o $@ $^ $(LINKER_FLAGS) $(CPPUTEST_LINKER_FLAGS)

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

$(TEST_OBJ_DIR)/%.o: %.cpp
	@echo
	$(ECHO) "\n${Yellow}Compiling $(notdir $<)...${NoColor}"
	$(SILENCE)mkdir -p $(dir $@)
	$(ECHO) "${DarkGray}Module test code${NoColor}"
	$(SILENCE)$(CPP_COMPILER) $(COMPILER_FLAGS) $< -o $@ $(INCLUDE_FLAGS) $(TEST_INCLUDE_FLAGS)


# MAKECMDGOALS is a special variable that is set by Make
#For some reason this needs to be below the targets.
ifneq ("$(SUBMAKE_TARGET)","clean")
-include $(DEP_FILES)
endif

filelist:
	$(ECHO) "${BoldGreen}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	$(ECHO)             "~~~ File List in CppUTest Makefile ~~~"
	$(ECHO)             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	$(ECHO)             "$(MODULE_DIR)${NoColor}"
	$(ECHO) "\n${BoldCyan}Targets:${NoColor}"
	$(call echo_with_header,TARGET_NAME)
	$(call echo_with_header,TEST_TARGET)
	@echo
	$(ECHO) "\n${BoldCyan}Production code:${NoColor}"
	$(call echo_with_header,SRC)
#	$(call echo_with_header,SRC_OBJ)
#	$(call echo_with_header,SRC_DEP)
	$(call echo_with_header,INC)
	$(call echo_with_header,LIBS)
	@echo
	$(ECHO) "\n${BoldCyan}Mock Hardware code:${NoColor}"
	$(call echo_with_header,MOCKHW_SRC)
	$(call echo_with_header,MOCKHW_INC)
	@echo
	$(ECHO) "\n${BoldCyan}Test code:${NoColor}"
	$(call echo_with_header,PRODUCTION_LIB)
	$(call echo_with_header,TEST_TARGET_NAME)
	$(call echo_with_header,TEST_TARGET)
	$(call echo_with_header,TEST_SRC)
#	$(call echo_with_header,TEST_OBJ)
#	$(call echo_with_header,TEST_DEP)
	$(call echo_with_header,TEST_INC)
	$(call echo_with_header,TEST_LIBS)
	@echo
	$(ECHO) "\n${BoldCyan}CppUTest code:${NoColor}"
	$(call echo_with_header,CPPUTEST_LIBS,$(CPPUTEST_LIBS))
	@echo
	$(ECHO) "\n${BoldCyan}All Dependencies:${NoColor}"
	$(call echo_with_header,DEP_FILES)

dirlist:
	$(ECHO) "${BoldGreen}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	$(ECHO)             "~~~ Dirctory List in CppUTest Makefile ~~~"
	$(ECHO)             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	$(ECHO)             "$(MODULE_DIR)${NoColor}"
	@echo
	$(call echo_with_header,SRC_DIRS)
	$(call echo_with_header,INC_DIRS)
	$(call echo_with_header,OBJ_DIR)
	$(call echo_with_header,TEST_SRC_DIRS)
	$(call echo_with_header,TEST_INC_DIRS)
	$(call echo_with_header,TEST_OBJ_DIR)
	$(call echo_with_header,TEST_BUILD_DIR)
	$(call echo_with_header,CPPUTEST_LIB_LIST)
	$(call echo_with_header,CPPUTEST_LIB_DIR)
	@echo

flags:
	$(ECHO) "${BoldGreen}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	$(ECHO)             "~~~ Flags in CppUTest Makefile ~~~"
	$(ECHO)             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	$(ECHO)             "$(MODULE_DIR)${NoColor}"
	$(call echo_with_header,COMPILER_FLAGS)
	$(call echo_with_header,INCLUDE_FLAGS)
	$(call echo_with_header,LINKER_FLAGS)
	$(call echo_with_header,CPPUTEST_LINKER_FLAGS)
	$(call echo_with_header,ARCHIVER_FLAGS)
	@echo

help:
	$(ECHO) "${BoldGreen}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	$(ECHO)             "~~~  CppUTest Makefile Help ~~~"
	$(ECHO)             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~${NoColor}"
	@echo
	$(ECHO) "${BoldRed} TODO ${NoColor}"
	@echo
	@echo "talk about modules, etc"

#shallow_clean Does not remove all parent directories that were created
