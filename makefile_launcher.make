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
src_dirs=lib/src lib/Global/src lib/ATtiny861/src lib/Spi/src
inc_dirs=lib/inc lib/Global/inc lib/ATtiny861/inc lib/Spi/inc
lib_dirs=
obj_dir=obj
build_dir=build


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
TARGET=$(BUILD_DIR)/$(TARGET_NAME)
MODULE_DIR=$(call clean_path,$(ROOT_DIR)/$(MODULE))
include $(MODULE_DIR)/make_module_config.make

###################################
### Collect project directories ###
###################################
SRC_DIRS=$(src_dirs)
INC_DIRS=$(inc_dirs)
LIB_DIRS=$(lib_dirs)

#module_src_dirs, module_inc_dirs, and module_lib_dirs are user configured in make_module_config
SRC_DIRS+=$(call clean_path,$(module_src_dirs))
INC_DIRS+=$(call clean_path,$(module_inc_dirs))


#We'll get to libraries later
# LIB_DIRS=$(call clean_path,$(module_lib_dirs))
#LIB_LIST    User-configured in make_module_config

OBJ_DIR=$(call clean_path,$(ROOT_DIR)/$(obj_dir))
BUILD_DIR=$(call clean_path,$(ROOT_DIR)/$(build_dir))



##########################################
### Auto-detect production source code ###
##########################################
SRC=$(call get_src_from_dir_list,$(SRC_DIRS))
CLEAN_SRC=$(call clean_path,$(SRC))
SRC_OBJ=$(addprefix $(OBJ_DIR)/,$(call src_to_o,$(CLEAN_SRC)))
SRC_DEP=$(addprefix $(OBJ_DIR)/,$(call src_to_d,$(CLEAN_SRC)))
INC=$(call get_inc_from_dir_list,$(INC_DIRS))
LIBS=$(addprefix lib,$(addsuffix .a,$(LIB_LIST)))

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
#	$(LAUNCH_MAKE) makefile_production.make

clean:
	$(ECHO) "${Yellow}Cleaning project...${NoColor}"
#	$(SILENCE)rm -rf $(OBJ_DIR)
#	$(SILENCE)rm -rf $(BUILD_DIR)
	$(LAUNCH_MAKE) makefile_cpputest.make
	$(LAUNCH_MAKE) makefile_production.make
	$(ECHO) "${Green}...Clean finished!${NoColor}\n"

test:
	$(LAUNCH_MAKE) makefile_cpputest.make

production:
	$(LAUNCH_MAKE) makefile_avr.make

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
