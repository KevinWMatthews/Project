# Set this to @ to keep the makefiles quiet
SILENCE = @

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
  lib/test/BitManip \
  lib/ATtiny861/test/ChipFunctions \
  lib/Spi/test/SpiApi \
  lib/Spi/test/SpiHw \
  lib/ATtiny861/test/Timer0 \


# PROJECTS= \
#   master \
  # slave

# master slave:
# 	$(MAKE_LAUNCHER)

### Makefile targets ###
.DEFAULT_GOAL:=all
.PHONY: all clean
.PHONY: test compile run
.PHONY: production
.PHONY: filelist dirlist flags info
.PHONY: $(MODULES)
# .PHONY: $(PROJECTS)

include make_colors.make

all: $(MODULES)

filelist dirlist flags test: $(MODULES)

# production: $(PROJECTS)

clean: $(MODULES)

$(MODULES):
	$(ECHO) "\n\n${BoldPurple}Launching Makefile for $@...${NoColor}"
	$(MAKE_LAUNCHER)


### Helpers ###
# MODULE is defined here and is passed into all other makefiles
MAKE_LAUNCHER=make $(MAKECMDGOALS) $(NO_PRINT_DIRECTORY) SILENCE=$(SILENCE) --file make_launcher.make MODULE=$@


### Documentation ###
# MAKECMDGOALS is a special variable that is set by make
# .DEFAULT_GOAL is a special variable that the user can set
