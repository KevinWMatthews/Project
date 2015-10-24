#This makefile defines the directory structure and then launches the appropriate sub-makefile

# Set this to @ to keep the makefiles quiet
ifndef SILENCE
	SILENCE =
endif

include make_helper_functions


#########################################
### Define common directory structure ###
#########################################
#TODO some of this needs to move to the CppUTest makefile
ROOT_DIR=.
LIB_DIR=lib
MODULE_DIR=$(call clean_path,$(ROOT_DIR)/$(MODULE))
### Production-specific directory structure ###
TARGET_NAME=TheProject
TARGET=$(BUILD_DIR)/$(TARGET_NAME)
#TODO move this to CPpUTest, make sure that clean gets the correct directories
#Don't launch the production build for every clean...
OBJ_DIR=$(call clean_path,$(ROOT_DIR)/obj/CppUTest)
#TODO
BUILD_DIR=$(call clean_path,$(ROOT_DIR)/build)
include $(MODULE_DIR)/make_module_config.make
#src_dirs, inc_dirs, and lib_dirs are user configured in make_module_config
SRC_DIRS=$(LIB_DIR)/src
SRC_DIRS+=$(call clean_path,$(src_dirs))
INC_DIRS=$(LIB_DIR)/inc
INC_DIRS+=$(call clean_path,$(inc_dirs))
LIB_DIRS=$(call clean_path,$(lib_dirs))
#LIB_LIST    User-configured in make_module_config

COMPILER_FLAGS=-Wall
INCLUDE_FLAGS=
#Linker flags for libraries will be handled automatically if make_module_config is set
LINKER_FLAGS=

export

### Targets ###
.PHONY: all test
.PHONY: production
.PHONY: filelist dirlist flags

all:
	$(LAUNCH_MAKE) MakefileCppUTest.make
	$(LAUNCH_MAKE) MakefileProduction.make

clean:
	$(ECHO) "${Yellow}Cleaning project...${NoColor}"
#	$(SILENCE)rm -rf $(OBJ_DIR)
#	$(SILENCE)rm -rf $(BUILD_DIR)
	$(LAUNCH_MAKE) MakefileCppUTest.make
	$(LAUNCH_MAKE) MakefileProduction.make
	$(ECHO) "${Green}...Clean finished!${NoColor}\n"

test:
	$(LAUNCH_MAKE) MakefileCppUTest.make

production:
	$(LAUNCH_MAKE) MakefileProduction.make

filelist:
	$(ECHO) "${BoldGreen}~~~ $(MODULE_DIR) $@ ~~~${NoColor}"
	$(ECHO) "\n${BoldCyan}Directory of makefile_launcher.make:${NoColor}"
	$(ECHO) "$(shell pwd)\n"
	@echo
	$(call echo_with_header,TARGET_NAME)
	$(call echo_with_header,TARGET)
	@echo
	$(LAUNCH_MAKE) MakefileCppUTest.make

flags:
	@echo "~~~ $(MODULE_DIR) Flags ~~~"
	$(LAUNCH_MAKE) MakefileCppUTest.make

dirlist:
	$(call color_echo,"~~~ $(MODULE_DIR) Directory structure ~~~",BoldCyan)
	$(call color_echo,"  $(MODULE_DIR) Common folders:",BoldPurple)
	$(call echo_with_header,ROOT_DIR)
	$(call echo_with_header,MODULE_DIR)
	$(call echo_with_header,SRC_DIRS)
	$(call echo_with_header,INC_DIRS)
	$(call echo_with_header,OBJ_DIR)
	$(call echo_with_header,BUILD_DIR)
	$(call echo_with_header,LIB_DIRS)
	$(call echo_with_header,LIB_LIST)
	@echo
	$(call color_echo,"  $(MODULE_DIR) Production code:",BoldCyan)
	$(LAUNCH_MAKE) MakefileProduction.make
	$(call color_echo,"  $(MODULE_DIR) Test code:",BoldCyan)
	$(LAUNCH_MAKE) MakefileCppUTest.make
	@echo



### Helpers ###
LAUNCH_MAKE=make $(MAKECMDGOALS) --file
