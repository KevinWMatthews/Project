

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

	$(call echo_with_header,LIB_LIST)
	@echo
	$(call color_echo,"  $(MODULE_DIR) Production code:",BoldCyan)
	$(LAUNCH_MAKE) makefile_production.make
#	$(call color_echo,"  $(MODULE_DIR) Test code:",BoldCyan)
#	$(LAUNCH_MAKE) makefile_cpputest.make
	@echo



### Helpers ###
LAUNCH_MAKE=make $(MAKECMDGOALS) --file
