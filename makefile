### User config ###
#Add all tests to this list!
#To run specific test, execute
#  make test TEST=<name> from the terminal
#This will override all instances of TEST in this makefile (only?)
#Slick!
MODULES= \
  lib/BitManip \
  lib/ChipFunctions \

lib/BitManip lib/ChipFunctions:
	$(MAKE_LAUNCHER)




### Makefile targets ###
.DEFAULT_GOAL:=all
.PHONY: all clean
.PHONY: test compile run
.PHONY: production
.PHONY: filelist dirlist flags info
.PHONY: $(MODULES)

all: $(MODULES)

filelist dirlist flags test production: $(MODULES)

clean: $(MODULES)


### Helpers ###
MAKE_LAUNCHER=make $(MAKECMDGOALS) --file make_launcher.make MODULE=$@


### Documentation ###
# MAKECMDGOALS is a special variable that is set by make
# .DEFAULT_GOAL is a special variable that the user can set
