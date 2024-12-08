RAYLIB ?= ./vendor/raylib/src/
LIBRARIES = -lraylib
CCFLAGS = -std=c99 -Wall -Wpedantic
CCFILES = src/oruguru.c -o build/oruguru-dev

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

.PHONY: all dev release build clean raylib_desktop

all: build dev

dev:
	cc\
		$(CCFILES)\
		-O1 $(CCFLAGS)\
		-I $(RAYLIB) -L $(RAYLIB)\
		$(LIBRARIES)

release:
	cc\
		$(CCFILES)\
		-O3 $(CCFLAGS)\
		-I $(RAYLIB) -L $(RAYLIB)\
		$(LIBRARIES)

clean:
	rm -f build/*

build:
	mkdir -p build

raylib_desktop:
	cd vendor/raylib/src &&\
	make PLATFORM=PLATFORM_DESKTOP
