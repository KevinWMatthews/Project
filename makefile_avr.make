########################
### AVR Dude options ###
########################
#Fill in the part number that avrdude uses
AVRDUDE_MCU=t861

AVRDUDE_PROGRAMMERID=avrispmkII

#port to which your debugger is attached
AVRDUDE_PORT=usb


#######################
### avr-gcc options ###
#######################
MCU=attiny861



#########################
#########################
### Basic Config Done ###
#########################
#########################
#All basic project configuration is above this line
#Look below to find compiler options



######################
### Compiler Tools ###
######################
C_COMPILER=avr-gcc
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
SIZE=avr-size
AVRDUDE=avrdude
REMOVE=rm -rf


#############
### Flags ###
#############
HEX_FORMAT=ihex

C_COMPILER_FLAGS=-g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-Wall -Wstrict-prototypes                    \
	-funsigned-bitfields -funsigned-char         \
	-fpack-struct -fshort-enums                  \
#	-Wa,-ahlms=$(firstword $(filter %.lst, $(<:.c=.lst)))

INCLUDE_FLAGS=$(addprefix -I,$(INC_DIRS))

#TODO add in library support
#use  -lm $(LIBS) ?
LINKER_FLAGS=-Wl,-Map,$(BUILD_DIR)/$(TARGET_NAME).map -mmcu=$(MCU)



###################
###################
### Config Done ###
###################
###################
#Edit below this mark only if:
#  You're adding a new makefile feature
#  You found a makefile bug
#  You're overconfident


#############################
###                       ###
### Auto-generated values ###
###                       ###
#############################


###################
### Directories ###
###################
OBJ_DIR=$(call clean_path,$(ROOT_DIR)/$(prod_obj_dir))
BUILD_DIR=$(call clean_path,$(ROOT_DIR)/$(prod_build_dir))


########################
### Test Directories ###
########################
TARGET=$(BUILD_DIR)/$(TARGET_NAME)
ELF_TARGET=$(TARGET).elf
DUMP_TARGET=$(TARGET_NAME).s

HEX_ROM_TARGET=$(BUILD_DIR)/$(TARGET_NAME).hex
HEX_TARGET=$(HEX_ROM_TARGET)


#############################
### Generate object files ###
#############################
SRC_OBJ=$(addprefix $(OBJ_DIR)/,$(call src_to_o,$(SRC)))
SRC_DEP=$(addprefix $(OBJ_DIR)/,$(call src_to_d,$(SRC)))



include make_helper_functions
include make_colors



####################
### Target Names ###
####################
.PHONY: all install writeflash hex disasm stats clean help
.PHONY: filelist dirlist

all: $(ELF_TARGET)

install: writeflash

writeflash: hex
	sudo $(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID) -p $(AVRDUDE_MCU) -P $(AVRDUDE_PORT) \
             -e -U flash:w:$(HEX_TARGET)

hex: $(HEX_TARGET)

disasm: $(DUMP_TARGET) stats

stats: $(ELF_TARGET)
	$(OBJDUMP) -h $(ELF_TARGET)
	$(SIZE) $(ELF_TARGET)

clean:
	$(REMOVE) $(BUILD_DIR)
	$(REMOVE) $(OBJ_DIR)


### Generate files ###
#Create .elf and .map files
$(ELF_TARGET): $(SRC_OBJ)
	$(SILENCE)mkdir -p $(dir $@)
	$(C_COMPILER) $(LINKER_FLAGS) -o $(ELF_TARGET) $(SRC_OBJ)

#Create disassembly for executable
$(DUMP_TARGET): $(ELF_TARGET)
	$(OBJDUMP) -S $< > $(BUILD_DIR)/$@


#Generate production code object files
# $(OBJ_DIR)/%.o: $(ROOT_DIR)/%.c
# 	$(SILENCE)mkdir -p $(dir $@)
# 	$(C_COMPILER) $(C_COMPILER_FLAGS) $(INCLUDE_FLAGS) -c $< -o $@

#Generate hwDemo object files
$(OBJ_DIR)/%.o: %.c
	@echo here
	@echo $(OBJ_DIR)
	$(SILENCE)mkdir -p $(dir $@)
	$(C_COMPILER) $(C_COMPILER_FLAGS) $(INCLUDE_FLAGS) -c $< -o $@

##Generate hwDemo assembly
$(OBJ_DIR)/%.s: %.c
	@echo here
	$(SILENCE)mkdir -p $(dir $@)
	$(C_COMPILER) -S $(C_COMPILER_FLAGS) $< -o $@

#Chip-readable .hex file from compiler's binary file output, .elf
%.hex: %.elf
	$(SILENCE)mkdir -p $(dir $@)
	$(OBJCOPY) -j .text -j .data -O $(HEX_FORMAT) $< $@


### Targets for Makefile debugging ###
filelist:
	$(ECHO) "${BoldGreen}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	$(ECHO)             "~~~ File List in AVR Makefile ~~~"
	$(ECHO)             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~${NoColor}"
	$(ECHO) "\n${BoldCyan}Targets:${NoColor}"
	$(call echo_with_header,TARGET_NAME)
	$(call echo_with_header,TARGET)
	$(call echo_with_header,ELF_TARGET)
	$(call echo_with_header,HEX_TARGET)
	$(call echo_with_header,DUMP_TARGET)
	@echo
	$(ECHO) "\n${BoldCyan}Production code:${NoColor}"
	$(call echo_with_header,SRC)
#	$(call echo_with_header,SRC_OBJ)
#	$(call echo_with_header,SRC_DEP)
	$(call echo_with_header,INC)
	$(call echo_with_header,LIBS)

dirlist:
	$(ECHO) "${BoldGreen}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	$(ECHO)             "~~~ Directory List in AVR Makefile ~~~"
	$(ECHO)             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~${NoColor}"
	$(call echo_with_header,ROOT_DIR)
	$(call echo_with_header,SRC_DIRS)
	$(call echo_with_header,INC_DIRS)
	$(call echo_with_header,OBJ_DIR)
	$(call echo_with_header,BUILD_DIR)
	$(call echo_with_header,LIB_DIRS)

flags:
	$(ECHO) "${BoldGreen}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	$(ECHO)             "~~~ Flags in AVR Makefile ~~~"
	$(ECHO)             "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~${NoColor}"
	$(call echo_with_header,C_COMPILER_FLAGS)
	$(call echo_with_header,INCLUDE_FLAGS)
	$(call echo_with_header,LINKER_FLAGS)

help:
	$(ECHO) "${BoldGreen}~~~~~~~~~~~~~~~~~~~~~~~~~~"
	$(ECHO)             "~~~  AVR Makefile Help ~~~"
	$(ECHO)             "~~~~~~~~~~~~~~~~~~~~~~~~~~${NoColor}"
	$(ECHO) "all        Compile and link all source code, generate an .elf file (binary)."
	$(ECHO) "install    Create an Intel Hex file from the .elf and write it to chip's flash."
	$(ECHO) "writeflash Same as install."
	$(ECHO) "hex        Generate Intel Hex file only."
	$(ECHO) "disasm     Generate disassembly."
	$(ECHO) "stats      Generate size and disassembly."
	$(ECHO) "flags      Display all flags used during the compilation process."
	$(ECHO) "filelist   List all files detected and created by the makefile."
	$(ECHO) "clean      Remove all files and folders that are generated by this makefile."
	$(ECHO) "help       This."


### Color codes ###
Blue       =\033[0;34m
BoldBlue   =\033[1;34m
Gray       =\033[0;37m
DarkGray   =\033[1;30m
Green      =\033[0;32m
BoldGreen  =\033[1;32m
Cyan       =\033[0;36m
BoldCyan   =\033[1;36m
Red        =\033[0;31m
BoldRed    =\033[1;31m
Purple     =\033[0;35m
BoldPurple =\033[1;35m
Yellow     =\033[0;33m
BoldYellow =\033[1;33m
BoldWhite  =\033[1;37m
NoColor    =\033[0;0m
NC         =\033[0;0m
