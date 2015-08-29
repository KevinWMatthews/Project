

### Compiler tools ###
C_COMPILER=gcc
C_LINKER=gcc
ARCHIVER=ar
CPP_COMPILER=g++
CPP_LINKER=g++

.DEFAULT_GOAL:=all
.PHONY: all test clean

all:
	@echo MakefileCppUTest all

test:
	@echo MakefileCppUTest test

clean:
	@echo MakefileCppUTest clean
