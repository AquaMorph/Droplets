TARGET = Main

CPP_SOURCES = src/main.cpp

LIBDAISY_DIR = ./libDaisy
DAISYSP_DIR = ./daisySP

SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile
