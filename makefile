RAYLIB ?= ./vendor/raylib/src/
LIBRARIES = -lraylib
CCFLAGS = -std=c99 -Wall -Wpedantic

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

all: build
	echo "$(LIBRARIES)"
	cc\
		src/oruguru.c\
		-o build/oruguru-dev\
		-O1 $(CCFLAGS)\
		-I $(RAYLIB) -L $(RAYLIB)\
		$(LIBRARIES)

clean:
	rm build/*

build:
	mkdir -p build

raylib_desktop:
	pushd vendor/raylib/src &&\
	make PLATFORM=PLATFORM_DESKTOP &&\
	popd
