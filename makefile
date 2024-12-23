RAYLIB ?= ./vendor/raylib/src/
LIBRARIES = -lraylib
CCFLAGS = -std=c99 -Wall -Wextra
CCFILES = src/oruguru.c -o build/oruguru-dev

# Machine Dependent
ifeq ($(OS),Windows_NT)
	LIBRARIES += -lgdi32 -lwinmm
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		LIBRARIES += -lGL -lm -lpthread -ldl -lrt -lX11
	endif
	ifeq ($(UNAME_S),Darwin)
		# WARN: uhhhhhh
		ERROR := $(error no support for darwin machines)
	endif
endif

# Build Options
ifeq ($(BUILD_MODE),DEBUG)
    CCFLAGS += -O1 -g -DDEBUG
endif

ifeq ($(BUILD_MODE),RELEASE)
	CCFLAGS += -O2
endif

# Targets
.PHONY: all build builddir clean vendor_clean

all: build

build: build_dir
ifneq ($(PLATFORM),)
	cd vendor/raylib/src &&\
		make PLATFORM=$(PLATFORM) RAYLIB_BUILD_MODE=$(BUILD_MODE)
endif
	cc $(CCFILES) $(CCFLAGS) -I $(RAYLIB) -L $(RAYLIB) $(LIBRARIES)

clean:
	rm -f build/*

vendor_clean:
	cd vendor/raylib/src &&\
		make clean

build_dir:
	mkdir -p build
