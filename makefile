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
.PHONY: all test production clean
.PHONY: dirlist info
.PHONY: $(MODULES)

all: $(MODULES)

dirlist test production: $(MODULES)

clean: $(MODULES)



### Helpers ###
MAKE_LAUNCHER=make $(MAKECMDGOALS) --file make_launcher.make MODULE_DIR=$@ TARGET_NAME=$(@F)


### Documentation ###
# MAKECMDGOALS is a special variable that is set by make
# .DEFAULT_GOAL is a special variable that the user can set
