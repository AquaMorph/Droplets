TARGET = cascade

CPP_SOURCES = src/main.cpp \
              src/util.cpp \
              src/menu.cpp \
              src/droplets/droplet.cpp \
              src/droplets/noise_droplet.cpp \
              src/droplets/vco_droplet.cpp \
              src/graphics/sprite.cpp \
              src/graphics/wave.cpp

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
