#This makefile defines the directory structure and then launches the appropriate sub-makefile

# Set this to @ to keep the makefiles quiet
ifndef SILENCE
	SILENCE =
endif

#########################################
### Define common directory structure ###
#########################################
ROOT_DIR=.
#MODULE_DIR  Passed into this makefile

include $(MODULE_DIR)/make_module_config.make
#SRC_DIRS    User-configured in make_module_conig
#INC_DIRS    User-configured in make_module_conig
#LIB_DIRS    User-configured in make_module_conig
#LIB_LIST    User-configured in make_module_conig

COMPILER_FLAGS=-Wall
INCLUDE_FLAGS=
#Linker flags for libraries will be handled automatically if make_module_config is set
LINKER_FLAGS=

### Targets ###
.PHONY: all test production
.PHONY: filelist dirlist flags

export
include make_helper_functions

all clean:
	$(LAUNCH_MAKE) MakefileCppUTest.make
	$(LAUNCH_MAKE) MakefileProduction.make

test:
	$(LAUNCH_MAKE) MakefileCppUTest.make

production:
	$(LAUNCH_MAKE) MakefileProduction.make

filelist:
	@echo "~~~ $(MODULE_DIR) $@"
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
