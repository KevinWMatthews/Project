#This makefile spawns two submakes: production and test
#These are launched with a command of the form
#  make production SUBMAKE_TARGET=<target>
#
#This is quite cumbersome to type, so it is recommended to put
#the following functions in your .bashrc:
#  makep() { make production SUBSUBMAKE_TARGET=$1; }
#  maket() { make test SUBMAKE_TARGET=$1 MODULE=$2; }

# Set this to @ to keep the makefiles quiet
SILENCE =

#Some systems need the -e flag (interpret backslash-escaped characters) for colors to display correctly.
#Others already display colors properly and will instead output -e to the terminal.
#If colors are not properly displaying add/remove -e here.
ECHO_INTERPRETATION=

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
#  maket module <name>
#from the terminal. Tab completetion works. Slick!
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




#######################################
###                                 ###
###         Makefile details        ###
### Sort out make, makep, and maket ###
###                                 ###
#######################################
#The targets are configured to respond best to maket and makep,
#so we need to force things when using standard make
ifeq ($(MAKECMDGOALS),clean)
	SUBMAKE_TARGET=clean
endif
ifeq ($(MAKECMDGOALS),help)
	SUBMAKE_TARGET=help
endif

#maket and makep need a bit of help because .DEFAULT_GOAL doesn't change
#our custom SUBMAKE_TARGET
ifeq ($(strip $(SUBMAKE_TARGET)),)
	override SUBMAKE_TARGET=all
endif
#The test makefile hits once for each module. Suppress this duplication
#by defining a dummy module
ifeq ($(strip $(SUBMAKE_TARGET)),help)
	override TEST_MODULE=test_help
endif

#If no test module is specified, make all of them
ifeq ($(strip $(TEST_MODULE)),)
	override TEST_MODULE=$(ALL_MODULES)
endif


MAKE=make $(NO_PRINT_DIRECTORY) --file
PRODUCTION_MAKEFILE=makefile_avr.make
TEST_MAKEFILE=makefile_cpputest.make

include make_colors


########################
###                  ###
### Makefile targets ###
###                  ###
########################
.DEFAULT_GOAL:=all
.PHONY: all clean help
.PHONY: production
.PHONY: test

#Private to tests
.PHONY: $(TEST_MODULE)

all: production test

clean: production test

production:
	$(SILENCE)$(MAKE) $(PRODUCTION_MAKEFILE) $(SUBMAKE_TARGET)

#TEST_MODULE is defined in .bashrc and is passed from the command prompt
test: $(TEST_MODULE)

$(TEST_MODULE):
	$(SILENCE)$(MAKE) $(TEST_MAKEFILE) $(SUBMAKE_TARGET) MODULE=$@

help: production test



### Documentation ###
# .DEFAULT_GOAL is a special makefile variable
# $@	the name of the target
# $<	the name of the first prerequisite
# $^	the names of all prerequisites separated by a space
