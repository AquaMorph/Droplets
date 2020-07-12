TARGET = main

CPP_SOURCES = src/main.cpp

LIBDAISY_DIR = ./lib/libDaisy
DAISYSP_DIR = ./lib/daisySP

SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

libdaisy:
	cd $(LIBDAISY_DIR) && make
daisysp:
	cd $(DAISYSP_DIR) && make
lib: libdaisy daisysp
