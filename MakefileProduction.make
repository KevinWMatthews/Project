#Production code
### Production-specific directory structure ###
TARGET_NAME=$(notdir $(MODULE_DIR))
OBJ_DIR=$(MODULE_DIR)/obj
TARGET_DIR=$(MODULE_DIR)/build


### Compiler tools ###
C_COMPILER=avr-gcc
C_LINKER=avr-gcc
ARCHIVER=ar
CPP_COMPILER=
CPP_LINKER=

.DEFAULT_GOAL:=all
.PHONY: all production clean
.PHONY: dirlist

all:
	@echo MakefileProduction all

production:
	@echo MakefileProduction production

clean:
	@echo MakefileProduction clean

dirlist:
	@echo OBJ_DIR: $(OBJ_DIR)
	@echo TARGET_DIR: $(TARGET_DIR)
	@echo TARGET_NAME: $(TARGET_NAME)
	@echo
