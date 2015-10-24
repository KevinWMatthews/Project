### User config ###
#Add all tests to this list!
#To run specific test, execute
#  make test MODULES=<name> from the terminal
#Slick!
MODULES= \
  lib/test/BitManip \
  lib/test/ChipFunctions \
  lib/test/Spi \
  lib/test/SpiHw \
  lib/test/Timer0 \

lib/test/BitManip lib/test/ChipFunctions lib/test/Spi lib/test/SpiHw lib/test/Timer0:
	$(MAKE_LAUNCHER)

PROJECTS= \
  master \
  # slave

master slave:
	$(MAKE_LAUNCHER)

### Makefile targets ###
.DEFAULT_GOAL:=all
.PHONY: all clean
.PHONY: test compile run
.PHONY: production
.PHONY: filelist dirlist flags info
.PHONY: $(MODULES)
.PHONY: $(PROJECTS)


all: $(MODULES)

filelist dirlist flags test: $(MODULES)

production: $(PROJECTS)

clean: $(MODULES)


### Helpers ###
MAKE_LAUNCHER=make $(MAKECMDGOALS) --file make_launcher.make MODULE=$@


### Documentation ###
# MAKECMDGOALS is a special variable that is set by make
# .DEFAULT_GOAL is a special variable that the user can set
