RAYLIB ?= ./vendor/raylib/src/
LIBRARIES = -lraylib
CCFLAGS = -std=c99 -Wall -Wpedantic
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
    CFLAGS += -O1 -g -D_DEBUG
endif

ifeq ($(BUILD_MODE),RELEASE)
	CFLAGS += -O3
endif

# Targets
.PHONY: all build builddir clean raylib_desktop

all: build

build: build_dir
ifneq ($(PLATFORM),)
	cd vendor/raylib/src && make PLATFORM=$(PLATFORM)
endif
	cc $(CCFILES) $(CCFLAGS) -I $(RAYLIB) -L $(RAYLIB) $(LIBRARIES)

clean:
	rm -f build/*

build_dir:
	mkdir -p build
