#Production code



.DEFAULT_GOAL:=all
.PHONY: all production clean
.PHONY: dirlist

include make_helper_functions

all:
	@echo MakefileProduction all
	@echo

production:
	$(LAUNCH_MAKE) makefile_avr.make all

clean:
	@echo MakefileProduction clean
	@echo

dirlist:
	@echo MakefileProduction dirlist
	@echo

LAUNCH_MAKE=make --file
