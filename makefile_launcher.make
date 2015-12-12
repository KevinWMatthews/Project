

###############
###         ###
### Targets ###
###         ###
###############
.PHONY: all test
.PHONY: production
.PHONY: hex
.PHONY: filelist dirlist flags

all:
	$(LAUNCH_MAKE) makefile_cpputest.make
#	$(LAUNCH_MAKE) makefile_avr.make

clean:
	$(ECHO) "${Yellow}Cleaning project...${NoColor}"
#	$(SILENCE)rm -rf $(OBJ_DIR)
#	$(SILENCE)rm -rf $(BUILD_DIR)
	$(LAUNCH_MAKE) makefile_cpputest.make
	$(LAUNCH_MAKE) makefile_avr.make
	$(ECHO) "${Green}...Clean finished!${NoColor}\n"

test:
	$(LAUNCH_MAKE) makefile_cpputest.make

production:
	make --file makefile_avr.make all

hex:
	$(LAUNCH_MAKE) makefile_avr.make

flags:
	@echo "~~~ $(MODULE_DIR) Flags ~~~"
#	$(LAUNCH_MAKE) makefile_cpputest.make
	$(LAUNCH_MAKE) makefile_avr.make

dirlist:
	$(call color_echo,"~~~ $(MODULE_DIR) Directory structure ~~~",BoldCyan)
	$(call color_echo,"  $(MODULE_DIR) Common folders:",BoldPurple)
	$(call echo_with_header,ROOT_DIR)
	$(call echo_with_header,MODULE_DIR)
	$(call echo_with_header,SRC_DIRS)
	$(call echo_with_header,INC_DIRS)
	$(call echo_with_header,MOCKHW_DIR)
	$(call echo_with_header,OBJ_DIR)
	$(call echo_with_header,BUILD_DIR)
	$(call echo_with_header,LIB_DIRS)
	$(call echo_with_header,LIB_LIST)
	@echo
	$(call color_echo,"  $(MODULE_DIR) Production code:",BoldCyan)
	$(LAUNCH_MAKE) makefile_production.make
#	$(call color_echo,"  $(MODULE_DIR) Test code:",BoldCyan)
#	$(LAUNCH_MAKE) makefile_cpputest.make
	@echo



### Helpers ###
LAUNCH_MAKE=make $(MAKECMDGOALS) --file
