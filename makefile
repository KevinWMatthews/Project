### User config ###
#Add all tests to this list!
#To run specific test, execute
#  make test TEST=<name> from the terminal
#This will override all instances of TEST in this makefile (only?)
#Slick!
ALL_MODULES= \
  lib/BitManip \
  lib/ChipFunctions \

lib/BitManip:
	$(MAKE_DIRECTORIES)
#	@echo $(MAKE_PRODUCTION) $@
#	@echo $(MAKE_LIBRARY) $@

lib/ChipFunctions:
	@echo $(MAKE_PRODUCTION) $@
	@echo $(MAKE_LIBRARY) $@
	@echo $(MAKE_TESTS) $@




### Makefile targets ###
.DEFAULT_GOAL:=all
.PHONY: all
.PHONY: dirlist
.PHONY: $(ALL_MODULES)

all: $(ALL_MODULES)

dirlist: $(ALL_MODULES)


### Helpers ###
MAKE_DIRECTORIES=make $(MAKECMDGOALS) --file $@/make_directories.make MODULE_DIR=$@ TARGET_NAME=$(@F)
MAKE_PRODUCTION=make --file ProductionMakefile.make -C
MAKE_LIBRARY=make --file LibraryMakefile.make -C
MAKE_TESTS=make --file MakefileCppUTest.make


### Documentation ###
# MAKECMDGOALS is a special variable that is set by make
# .DEFAULT_GOAL is a special variable that the user can set
