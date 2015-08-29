### Compiler tools ###
C_COMPILER=avr-gcc
C_LINKER=avr-gcc
ARCHIVER=ar
CPP_COMPILER=
CPP_LINKER=

.DEFAULT_GOAL:=all
.PHONY: all production clean

all:
	@echo MakefileProduction all

production:
	@echo MakefileProduction production

clean:
	@echo MakefileProduction clean
