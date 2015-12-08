#This makefile defines the directory structure and then launches the appropriate sub-makefile

# Set this to @ to keep the makefiles quiet
ifndef SILENCE
	SILENCE =
endif

include make_helper_functions.make

####################################################
###                                              ###
### Configure your project's directory structure ###
###                                              ###
####################################################
TARGET_NAME=TheProject
ROOT_DIR=.
scr_dirs=
inc_dirs=
lib_dirs=lib lib/ATtiny861
obj_dir=obj/CppUTest
build_dir=build



TARGET=$(BUILD_DIR)/$(TARGET_NAME)
MODULE_DIR=$(call clean_path,$(ROOT_DIR)/$(MODULE))
include $(MODULE_DIR)/make_module_config.make

#module_src_dirs, module_inc_dirs, and module_lib_dirs are user configured in make_module_config
SRC_DIRS=$(src_dirs)
SRC_DIRS+=$(call append_src_to_dir,$(lib_dirs))
SRC_DIRS+=$(call clean_path,$(module_src_dirs))
INC_DIRS=$(inc_dirs)
INC_DIRS+=$(call append_inc_to_dir,$(lib_dirs))
INC_DIRS+=$(call clean_path,$(module_inc_dirs))
LIB_DIRS=$(lib_dirs)
#Wait, do we want to do this?
LIB_DIRS=$(call clean_path,$(module_lib_dirs))
#LIB_LIST    User-configured in make_module_config
OBJ_DIR=$(call clean_path,$(ROOT_DIR)/$(obj_dir))
BUILD_DIR=$(call clean_path,$(ROOT_DIR)/$(build_dir))



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
