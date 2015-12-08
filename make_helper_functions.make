#This file does not make anything!
#It contains helper functions for the various makefiles.

clean_path=$(call remove_leading_dot,$1)
remove_leading_dot=$(subst ./,,$1)
#Not sure I want to allow a directory structure with ../
#Must remove dotdot first because ./ produces a false positive when compared to ../
#clean_path=$(call remove_leading_dot,$(call remove_leading_dotdot,$1))
#remove_leading_dotdot=$(subst ../,,$1)


#Calls to these are easier to read
src_to_o=$(call src_to,$1,o)
src_to_d=$(call src_to,$1,d)
# $1 is variable
# $2 is extension without .
src_to=$(call convert_extension,$1,.$2)
#nest calls so we don't get a repetition of .c and .cpp files
convert_extension=$(patsubst %.c,%$2,$(patsubst %.cpp,%$2,$1))


#Auto-detect source code in folders
get_src_from_dir = $(wildcard $1/*.c) $(wildcard $1/*.cpp)
get_src_from_dir_list = $(foreach dir, $1, $(call get_src_from_dir,$(dir)))
get_inc_from_dir = $(wildcard $1/*.h)
get_inc_from_dir_list = $(foreach dir, $1, $(call get_inc_from_dir,$(dir)))

append_src_to_dir = $(foreach dir, $1, $(wildcard $(dir)/src))
append_inc_to_dir = $(foreach dir, $1, $(wildcard $(dir)/inc))

#"test" echo; used for checking makefile parameters
# $1 = text, $2 = text color
color_echo=$(ECHO) "${$2}$1${NoColor}"
echo_with_header=$(ECHO) "${BoldPurple}  $1:${NoColor}"; echo $($1); echo;
ECHO=@echo -e


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
