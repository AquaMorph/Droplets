TARGET = droplets

SRC_DIR := ./src
CPP_SOURCES := $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp)

LIBDAISY_DIR = ./lib/libDaisy
DAISYSP_DIR = ./lib/daisySP

SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

libdaisy:
	cd $(LIBDAISY_DIR) && make
daisysp:
	cd $(DAISYSP_DIR) && make
lib: libdaisy daisysp
deploy: lib all program
updatelib:
	cd $(LIBDAISY_DIR) && make clean && git pull origin master
	cd $(DAISYSP_DIR) && make clean && git pull origin master
