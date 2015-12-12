# Set this to @ to keep the makefiles quiet
SILENCE =

#Set to 'Y' to suppress makefile messages when entering and leaving sub-makes
SUPPRESS_ENTERING_DIRECTORY_MESSAGE=Y
ifeq ($(SUPPRESS_ENTERING_DIRECTORY_MESSAGE),Y)
	NO_PRINT_DIRECTORY=--no-print-directory
endif


###################################
###                             ###
###     Module Configuration    ###
### Add all tests to this list! ###
###                             ###
###################################
#To run specific test, execute
#  make test MODULE=<name> from the terminal
#Slick!
ALL_MODULES= \
  lib/Global/test/BitManip \
  lib/ATtiny861/test/ChipFunctions \
  lib/Spi/test/SpiApi \
  lib/Spi/test/SpiHw \
  lib/ATtiny861/test/Timer0 \



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



#############################
###                       ###
### Auto-generated values ###
###                       ###
#############################
include make_helper_functions

MODULE_DIR=$(call clean_path,$(ROOT_DIR)/$(MODULE))


#################################################
### Create list of all production source code ###
#################################################
dirty_src=$(call get_src_from_dir_list,$(SRC_DIRS))
dirty_inc=$(call get_inc_from_dir_list,$(INC_DIRS))
SRC=$(call clean_path,$(dirty_src))
INC=$(call clean_path,$(dirty_inc))
LIBS=$(addprefix lib,$(addsuffix .a,$(LIB_LIST)))

export




########################
###                  ###
### Makefile targets ###
###                  ###
########################
.DEFAULT_GOAL:=all
.PHONY: all all_clean

.PHONY: pfiles pdirs pflags
.PHONY: tfiles tdirs tflags

.PHONY: test compile run
.PHONY: production
.PHONY: hex
.PHONY: filelist dirlist flags info
.PHONY: $(ALL_MODULES)
.PHONY: $(elf)

include make_colors
MAKE=make $(NO_PRINT_DIRECTORY) SILENCE=$(SILENCE) --file
PRODUCTION_MAKEFILE=makefile_avr.make
TEST_MAKEFILE=makefile_cpputest.make

all:



pfiles:
	$(MAKE) $(PRODUCTION_MAKEFILE) filelist

pdirs:
	$(MAKE) $(PRODUCTION_MAKEFILE) dirlist

pflags:
	$(MAKE) $(PRODUCTION_MAKEFILE) flags

tfiles:
	$(MAKE) $(TEST_MAKEFILE) filelist MODULE=$(MODULE)

tdirs:
	$(MAKE) $(TEST_MAKEFILE) dirlist MODULE=$(MODULE)

tflags:
	$(MAKE) $(TEST_MAKEFILE) flags

test: $(ALL_MODULES)

production: avr

hex: $(ALL_MODULES)

clean: $(ALL_MODULES)

$(ALL_MODULES) avr:
	$(ECHO) "\n\n${BoldPurple}Launching Makefile for $@...${NoColor}"
	$(MAKE_LAUNCHER)


### Helpers ###
# MODULE is defined here and is passed into all other makefiles
MAKE_LAUNCHER=make $(MAKECMDGOALS) $(NO_PRINT_DIRECTORY) SILENCE=$(SILENCE) --file makefile_launcher.make MODULE=$@


### Documentation ###
# MAKECMDGOALS is a special variable that is set by make
# .DEFAULT_GOAL is a special variable that the user can set
