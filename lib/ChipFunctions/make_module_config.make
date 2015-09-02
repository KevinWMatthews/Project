### Module configuration ###
#Define library dependenies and the location of this module's source code

src_dirs=$(ROOT_DIR)/mockHw/avr
inc_dirs=$(ROOT_DIR)/mockHw $(LIB_DIR)/inc lib/BitManip/inc

#List any libraries that this module depends on
lib_dirs=
#Static library names without lib prefix and .a suffix
LIB_LIST=
