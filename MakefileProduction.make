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

production:
	@echo MakefileProduction production

clean:
	@echo MakefileProduction clean

dirlist:
	$(call echo_with_header,OBJ_DIR)
	$(call echo_with_header,TARGET_DIR)
	$(call echo_with_header,TARGET_NAME)
	@echo
