#Production code


### Compiler tools ###
C_COMPILER=avr-gcc
C_LINKER=avr-gcc
ARCHIVER=ar
CPP_COMPILER=
CPP_LINKER=

.DEFAULT_GOAL:=all
.PHONY: all production clean
.PHONY: dirlist

include make_helper_functions

all:
	@echo MakefileProduction all
	@echo

production:
	@echo MakefileProduction production
	@echo

clean:
	@echo MakefileProduction clean
	@echo

dirlist:
	@echo MakefileProduction dirlist
	@echo
