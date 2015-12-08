#Production code



.DEFAULT_GOAL:=all
.PHONY: all production clean
.PHONY: dirlist

include make_helper_functions.make

all:
	@echo MakefileProduction all
	@echo

production:
	$(LAUNCH_MAKE) makefile_avr.make all

clean:
	$(SILENCE)rm -rf $(OBJ_DIR)
	$(SILENCE)rm -rf $(BUILD_DIR)

dirlist:
	@echo MakefileProduction dirlist
	@echo

LAUNCH_MAKE=make --file
