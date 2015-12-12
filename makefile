# Set this to @ to keep the makefiles quiet
SILENCE =

#Set to 'Y' to suppress makefile messages when entering and leaving sub-makes
SUPPRESS_ENTERING_DIRECTORY_MESSAGE=Y
ifeq ($(SUPPRESS_ENTERING_DIRECTORY_MESSAGE),Y)
	NO_PRINT_DIRECTORY=--no-print-directory
endif

### User config ###
#Add all tests to this list!
#To run specific test, execute
#  make test MODULES=<name> from the terminal
#Slick!
MODULES= \
  lib/Global/test/BitManip \
  lib/ATtiny861/test/ChipFunctions \
  lib/Spi/test/SpiApi \
  lib/Spi/test/SpiHw \
  lib/ATtiny861/test/Timer0 \


# PROJECTS= \
#   master \
  # slave

# master slave:
# 	$(MAKE_LAUNCHER)

#export??

### Makefile targets ###
.DEFAULT_GOAL:=all
.PHONY: all clean
.PHONY: test compile run
.PHONY: production
.PHONY: hex
.PHONY: filelist dirlist flags info
.PHONY: $(MODULES)
.PHONY: $(elf)

include make_colors

all: $(MODULES)

filelist dirlist flags test: $(MODULES)

production: avr

hex: $(MODULES)

clean: $(MODULES)

$(MODULES) avr:
	$(ECHO) "\n\n${BoldPurple}Launching Makefile for $@...${NoColor}"
	$(MAKE_LAUNCHER)


### Helpers ###
# MODULE is defined here and is passed into all other makefiles
MAKE_LAUNCHER=make $(MAKECMDGOALS) $(NO_PRINT_DIRECTORY) SILENCE=$(SILENCE) --file makefile_launcher.make MODULE=$@


### Documentation ###
# MAKECMDGOALS is a special variable that is set by make
# .DEFAULT_GOAL is a special variable that the user can set
