#This makefile defines the directory structure and then launches the appropriate sub-makefile

#########################################
### Define common directory structure ###
#########################################
ROOT_DIR=.
#MODULE_DIR  Passed into this makefile

include $(MODULE_DIR)/make_module_config.make
#SRC_DIRS    User-configured in make_module_conig
#INC_DIRS    User-configured in make_module_conig
#LIB_DIRS    User-configured in make_module_conig
#LIB_LIST    User-configured in make_module_conig



### Targets ###
.PHONY: all test production
.PHONY: dirlist

all clean:
	$(LAUNCH_MAKE) MakefileCppUTest.make
	$(LAUNCH_MAKE) MakefileProduction.make

test:
	$(LAUNCH_MAKE) MakefileCppUTest.make

production:
	$(LAUNCH_MAKE) MakefileProduction.make

dirlist:
	@echo "~~~ $(MODULE_DIR) Directory structure ~~~"
	@echo "  $(MODULE_DIR) Common folders:"
	@echo ROOT_DIR: $(ROOT_DIR)
	@echo MODULE_DIR: $(MODULE_DIR)
	@echo SRC_DIRS: $(SRC_DIRS)
	@echo INC_DIRS: $(INC_DIRS)
	@echo LIB_DIRS: $(LIB_DIRS)
	@echo LIB_LIST: $(LIB_LIST)
	@echo
	@echo "  $(MODULE_DIR) Production code:"
	$(LAUNCH_MAKE) MakefileProduction.make
	@echo "  $(MODULE_DIR) Test code:"
	$(LAUNCH_MAKE) MakefileCppUTest.make
	@echo



### Helpers ###
LAUNCH_MAKE=make $(MAKECMDGOALS) --file
