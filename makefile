#This makefile spawns two submakes: production and test
#These are launched with a command of the form
#  make production MAKE_TARGET=<target>
#
#This is quite cumbersome to type, so it is recommended to put
#the following functions in your .bashrc:
#  makep() { make production MAKE_TARKET=$1; }
#  maket() { make test MAKE_TARGET=$1; }

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
# ALL_MODULES= \
#   lib/Global/test/BitManip \
#   lib/ATtiny861/test/ChipFunctions \
#   lib/Spi/test/SpiApi \
#   lib/Spi/test/SpiHw \
#   lib/ATtiny861/test/Timer0 \



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
.PHONY: all all_clean clean

.PHONY: production
.PHONY: test

.PHONY: compile run

include make_colors

MAKE=make $(NO_PRINT_DIRECTORY) --file
PRODUCTION_MAKEFILE=makefile_avr.make
TEST_MAKEFILE=makefile_cpputest.make

all:

all_clean clean:
	$(SILENCE)$(MAKE) $(PRODUCTION_MAKEFILE) clean
	$(SILENCE)$(MAKE) $(TEST_MAKEFILE) clean

production:
	$(SILENCE)$(MAKE) $(PRODUCTION_MAKEFILE) $(MAKE_TARGET)

test:
#MODULE is defined in .bashrc and is passed from the command prompt
	$(SILENCE)$(MAKE) $(TEST_MAKEFILE) $(MAKE_TARGET) $(MODULE)


### Documentation ###
# .DEFAULT_GOAL is a special makefile variable
