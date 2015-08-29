# Set this to @ to keep the makefile quiet
ifndef SILENCE
	SILENCE =
endif

all:
	$(SILENCE)$(TARGET_NAME)
