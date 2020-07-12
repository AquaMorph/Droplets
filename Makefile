TARGET = Main

CPP_SOURCES = src/main.cpp

LIBDAISY_DIR = ./lib/libDaisy
DAISYSP_DIR = ./lib/daisySP

SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile
