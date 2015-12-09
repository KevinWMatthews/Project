### User config ###
#Add all tests to this list!
#To run specific test, execute
#  make test MODULES=<name> from the terminal
#Slick!
MODULES= \
  lib/ATtiny861/test/Timer0 \
  # lib/ATtiny861/test/ChipFunctions \
  # lib/Spi/test/SpiApi \
  # lib/Spi/test/SpiHw \
  # lib/test/BitManip \


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


all: $(MODULES)

filelist dirlist flags test: $(MODULES)

# production: $(PROJECTS)

clean: $(MODULES)

$(MODULES):
	$(MAKE_LAUNCHER)


### Helpers ###
# MODULE is defined here and is passed into all other makefiles
MAKE_LAUNCHER=make $(MAKECMDGOALS) --file make_launcher.make MODULE=$@


### Documentation ###
# MAKECMDGOALS is a special variable that is set by make
# .DEFAULT_GOAL is a special variable that the user can set
