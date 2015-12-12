#This makefile spawns two submakes: production and test
#These are launched with a command of the form
#  make production MAKE_TARGET=<target>
#
#This is quite cumbersome to type, so it is recommended to put
#the following functions in your .bashrc:
#  makep() { make production MAKE_TARKET=$1; }
#  maket() { make test MAKE_TARGET=$1 MODULE=$2; }

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
ifeq ($(strip $(MAKE_MODULE)),)
	override MAKE_MODULE=$(ALL_MODULES)

	ifeq ($(strip $(MAKE_TARGET)),)
		override MAKE_TARGET=all
	endif
endif

ifeq ($(strip $(MAKE_TARGET)),help)
	override MAKE_MODULE=test_help
endif

MAKE=make $(NO_PRINT_DIRECTORY) --file
PRODUCTION_MAKEFILE=makefile_avr.make
TEST_MAKEFILE=makefile_cpputest.make

include make_colors

.DEFAULT_GOAL:=all
.PHONY: all clean help

.PHONY: production
.PHONY: test

.PHONY: compile run
.PHONY: $(MAKE_MODULE)

all:

clean:


production:
	$(SILENCE)$(MAKE) $(PRODUCTION_MAKEFILE) $(MAKE_TARGET)

#MODULE is defined in .bashrc and is passed from the command prompt
test: $(MAKE_MODULE)

$(MAKE_MODULE):
	$(SILENCE)$(MAKE) $(TEST_MAKEFILE) $(MAKE_TARGET) MODULE=$@

help:
	@echo "Type 'maket help' or 'makep help' to see help menus for test or production code."


### Documentation ###
# .DEFAULT_GOAL is a special makefile variable
# $@	the name of the target
# $<	the name of the first prerequisite
# $^	the names of all prerequisites separated by a space
