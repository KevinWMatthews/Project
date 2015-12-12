#This makefile defines the directory structure and then launches the appropriate sub-makefile

include make_colors
include make_helper_functions

####################################################
###                                              ###
### Configure your project's directory structure ###
###                                              ###
####################################################
TARGET_NAME=TheProject
ROOT_DIR=.
SRC_DIRS=src lib/src lib/Global/src lib/ATtiny861/src lib/Spi/src
INC_DIRS=lib/inc lib/Global/inc lib/ATtiny861/inc lib/Spi/inc
LIB_DIRS=
MOCKHW_DIR=mockHw
prod_obj_dir=obj
test_obj_dir=obj_test
prod_build_dir=build
test_build_dir=build_test


# # Custom flags for compiling code for testing
# TEST_COMPILER_FLAGS=-Wall
# TEST_INCLUDE_FLAGS=
# #Linker flags for libraries will be handled automatically if make_module_config is set
# TEST_LINKER_FLAGS=

# # Custom flags for compiling code for production
# PRODUCTION_COMPILER_FLAGS=
# PRODUCTION_INCLUDE_FLAGS=
# #Linker flags for libraries will be handled automatically if make_module_config is set
# PRODUCTION_LINKER_FLAGS=




#############################
###                       ###
### Auto-generated values ###
###                       ###
#############################
MODULE_DIR=$(call clean_path,$(ROOT_DIR)/$(MODULE))


#################################################
### Create list of all production source code ###
#################################################
dirty_src=$(call get_src_from_dir_list,$(SRC_DIRS))
dirty_inc=$(call get_inc_from_dir_list,$(INC_DIRS))
SRC=$(call clean_path,$(dirty_src))
INC=$(call clean_path,$(dirty_inc))
LIBS=$(addprefix lib,$(addsuffix .a,$(LIB_LIST)))


#module_src_dirs, module_inc_dirs, and module_lib_dirs are user configured in make_module_config
# SRC_DIRS+=$(call clean_path,$(module_src_dirs))
# INC_DIRS+=$(call clean_path,$(module_inc_dirs))


#We'll get to libraries later
# LIB_DIRS=$(call clean_path,$(module_lib_dirs))
#LIB_LIST    User-configured in make_module_config





export



###############
###         ###
### Targets ###
###         ###
###############
.PHONY: all test
.PHONY: production
.PHONY: hex
.PHONY: filelist dirlist flags

all:
	$(LAUNCH_MAKE) makefile_cpputest.make
#	$(LAUNCH_MAKE) makefile_avr.make

clean:
	$(ECHO) "${Yellow}Cleaning project...${NoColor}"
#	$(SILENCE)rm -rf $(OBJ_DIR)
#	$(SILENCE)rm -rf $(BUILD_DIR)
	$(LAUNCH_MAKE) makefile_cpputest.make
	$(LAUNCH_MAKE) makefile_avr.make
	$(ECHO) "${Green}...Clean finished!${NoColor}\n"

test:
	$(LAUNCH_MAKE) makefile_cpputest.make

production:
	make --file makefile_avr.make all

hex:
	$(LAUNCH_MAKE) makefile_avr.make

filelist:
	$(ECHO) "${BoldGreen}~~~ $(MODULE_DIR) $@ ~~~${NoColor}"
	$(ECHO) "\n${BoldCyan}Directory of makefile_launcher.make:${NoColor}"
	$(ECHO) "$(shell pwd)\n"
	@echo
	$(call echo_with_header,TARGET_NAME)
	$(call echo_with_header,TARGET)
	@echo
	$(ECHO) "\n${BoldCyan}Production code:${NoColor}"
	$(call echo_with_header,SRC)
	$(call echo_with_header,CLEAN_SRC)
	$(call echo_with_header,SRC_OBJ)
	$(call echo_with_header,SRC_DEP)
	$(call echo_with_header,INC)
	$(call echo_with_header,LIBS)
	@echo
	$(ECHO) "\n${BoldCyan}Mock Hardware code:${NoColor}"
	$(call echo_with_header,MOCKHW_SRC)
	$(call echo_with_header,MOCKHW_INC)
#	$(LAUNCH_MAKE) makefile_cpputest.make
	$(LAUNCH_MAKE) makefile_avr.make

flags:
	@echo "~~~ $(MODULE_DIR) Flags ~~~"
#	$(LAUNCH_MAKE) makefile_cpputest.make
	$(LAUNCH_MAKE) makefile_avr.make

dirlist:
	$(call color_echo,"~~~ $(MODULE_DIR) Directory structure ~~~",BoldCyan)
	$(call color_echo,"  $(MODULE_DIR) Common folders:",BoldPurple)
	$(call echo_with_header,ROOT_DIR)
	$(call echo_with_header,MODULE_DIR)
	$(call echo_with_header,SRC_DIRS)
	$(call echo_with_header,INC_DIRS)
	$(call echo_with_header,MOCKHW_DIR)
	$(call echo_with_header,OBJ_DIR)
	$(call echo_with_header,BUILD_DIR)
	$(call echo_with_header,LIB_DIRS)
	$(call echo_with_header,LIB_LIST)
	@echo
	$(call color_echo,"  $(MODULE_DIR) Production code:",BoldCyan)
	$(LAUNCH_MAKE) makefile_production.make
#	$(call color_echo,"  $(MODULE_DIR) Test code:",BoldCyan)
#	$(LAUNCH_MAKE) makefile_cpputest.make
	@echo



### Helpers ###
LAUNCH_MAKE=make $(MAKECMDGOALS) --file
